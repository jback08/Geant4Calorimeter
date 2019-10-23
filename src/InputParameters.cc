/**
 *  @file   src/InputParameters.cc
 *
 *  @brief  Implementation of the InputParameters class.
 *
 *  $Log: $
 */
#include "G4SystemOfUnits.hh"

#include "Xml/tinyxml.hh"
#include "InputParameters.hh"

InputParameters::InputParameters() :
    m_useParticleGun(false),
    m_energy(-1.),
    m_nEvents(1),
    m_nParticlesPerEvent(1),
    m_useGenieInput(false),
    m_keepEMShowerDaughters(false),
    m_energyCut(0.001f),
    m_xCenter(0*mm),
    m_yCenter(0*mm),
    m_zCenter(0*mm),
    m_xWidth(1000*mm),
    m_yWidth(1000*mm),
    m_zWidth(1000*mm),
    m_nLayers(1000)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

InputParameters::InputParameters(const std::string &inputXmlFileName)
{
    this->LoadViaXml(inputXmlFileName);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

InputParameters::~InputParameters()
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

bool InputParameters::Valid() const
{
    if ((m_useParticleGun && m_useGenieInput) || (!m_useParticleGun && !m_useGenieInput))
    {
        std::cout << "Must use the particle gun or genie input" << std::endl;
        return false;
    }

    if (m_useParticleGun)
    {
        if (m_energy < 0.)
        {
            std::cout << "Energy not specified" << std::endl;
            return false;
        }

        if (m_species.empty())
        {
            std::cout << "Particle species not specified" << std::endl;
            return false;
        }

        if (m_nEvents <= 0 || m_nParticlesPerEvent <= 0)
        {
            std::cout << "Must specify positive number of events and particles per event to simulate" << std::endl;
            return false;
        }
    }

    if (m_useGenieInput)
    {
        if (m_genieTrackerFile.empty())
        {
            std::cout << "Genie tracker file not specified" << std::endl;
            return false;
        }
    }

    if (m_outputFileName.empty())
    {
        std::cout << "Missing output file name" << std::endl;
        return false;
    }

    if (m_energyCut < 0.)
    {
        std::cout << "Invalid energy cut specified" << std::endl;
        return false;
    }

    if (m_xWidth < 0.f || m_yWidth < 0.f || m_zWidth < 0.f)
    {
        std::cout << "Detector must not have negative width" << std::endl;
        return false;
    }

    if (m_nLayers <= 0)
    {
        std::cout << "3D energy binning requires positive number of layers" << std::endl;
        return false;
    }

    return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void InputParameters::LoadViaXml(const std::string &inputXmlFileName)
{
    TiXmlDocument *pTiXmlDocument = new TiXmlDocument();

    if (!pTiXmlDocument->LoadFile(inputXmlFileName.c_str()))
    {
        std::cerr << pTiXmlDocument->ErrorDesc() << std::endl;
        return;
    }

    TiXmlElement *pDocumentTiXmlElement = pTiXmlDocument->RootElement();

    for (TiXmlElement *pHeadTiXmlElement = pDocumentTiXmlElement->FirstChildElement(); pHeadTiXmlElement != nullptr; pHeadTiXmlElement = pHeadTiXmlElement->NextSiblingElement())
    {
        if (!pHeadTiXmlElement)
        {
            std::cout << "Failed to load file: No root element." << std::endl;
            pTiXmlDocument->Clear();
        }

        if (pHeadTiXmlElement->ValueStr() == "Output3DXmlFileName")
        {
            m_outputFileName = pHeadTiXmlElement->GetText();
        }
        else if (pHeadTiXmlElement->ValueStr() == "HitThresholdEnergy")
        {
            m_energyCut = std::stod(pHeadTiXmlElement->GetText());
        }
        else if (pHeadTiXmlElement->ValueStr() == "KeepMCEmShowerDaughters")
        {
            std::string keepEMShowerDaughtersString(pHeadTiXmlElement->GetText());
            std::transform(keepEMShowerDaughtersString.begin(), keepEMShowerDaughtersString.end(), keepEMShowerDaughtersString.begin(), [](unsigned char c){ return std::tolower(c);});
            if ((keepEMShowerDaughtersString == "0") || (keepEMShowerDaughtersString == "false"))
            {
                m_keepEMShowerDaughters = false;
            }
            else
            {
                m_keepEMShowerDaughters = true;
            }
        }
        else if (pHeadTiXmlElement->ValueStr() == "ParticleGun")
        {
            for (TiXmlElement *pParticleGunTiXmlElement = pHeadTiXmlElement->FirstChildElement(); pParticleGunTiXmlElement != nullptr; pParticleGunTiXmlElement = pParticleGunTiXmlElement->NextSiblingElement())
            {
                if (pParticleGunTiXmlElement->ValueStr() == "Use")
                {
                    std::string useParticleGunString(pParticleGunTiXmlElement->GetText());
                    std::transform(useParticleGunString.begin(), useParticleGunString.end(), useParticleGunString.begin(), [](unsigned char c){ return std::tolower(c);});
                    if ((useParticleGunString == "0") || (useParticleGunString == "false"))
                    {
                        m_useParticleGun = false;
                    }
                    else
                    {
                        m_useParticleGun = true;
                    }
                }
                else if (pParticleGunTiXmlElement->ValueStr() == "Species")
                {
                    m_species = pParticleGunTiXmlElement->GetText();
                }
                else if (pParticleGunTiXmlElement->ValueStr() == "Energy")
                {
                    m_energy = std::stod(pParticleGunTiXmlElement->GetText());
                }
                else if (pParticleGunTiXmlElement->ValueStr() == "NEvents")
                {
                    m_nEvents = std::stoi(pParticleGunTiXmlElement->GetText());
                }
                else if (pParticleGunTiXmlElement->ValueStr() == "ParticlePerEvent")
                {
                    m_nParticlesPerEvent = std::stoi(pParticleGunTiXmlElement->GetText());
                }
            }
        }
        else if (pHeadTiXmlElement->ValueStr() == "GenieInput")
        {
            for (TiXmlElement *pGenieTiXmlElement = pHeadTiXmlElement->FirstChildElement(); pGenieTiXmlElement != nullptr; pGenieTiXmlElement = pGenieTiXmlElement->NextSiblingElement())
            {
                if (pGenieTiXmlElement->ValueStr() == "Use")
                {
                    std::string useGenieString(pGenieTiXmlElement->GetText());
                    std::transform(useGenieString.begin(), useGenieString.end(), useGenieString.begin(), [](unsigned char c){ return std::tolower(c);});
                    if ((useGenieString == "0") || (useGenieString == "false"))
                    {
                        m_useGenieInput = false;
                    }
                    else
                    {
                        m_useGenieInput = true;
                    }
                }
                else if (pGenieTiXmlElement->ValueStr() == "TrackerFile")
                {
                    m_genieTrackerFile = pGenieTiXmlElement->GetText();
                }
            }
        }
        else if (pHeadTiXmlElement->ValueStr() == "CenterX")
        {
            m_xCenter = std::stod(pHeadTiXmlElement->GetText());
        }
        else if (pHeadTiXmlElement->ValueStr() == "CenterY")
        {
            m_yCenter = std::stod(pHeadTiXmlElement->GetText());
        }
        else if (pHeadTiXmlElement->ValueStr() == "CenterZ")
        {
            m_zCenter = std::stod(pHeadTiXmlElement->GetText());
        }
        else if (pHeadTiXmlElement->ValueStr() == "WidthX")
        {
            m_xWidth = std::stod(pHeadTiXmlElement->GetText());
        }
        else if (pHeadTiXmlElement->ValueStr() == "WidthY")
        {
            m_yWidth = std::stod(pHeadTiXmlElement->GetText());
        }
        else if (pHeadTiXmlElement->ValueStr() == "WidthZ")
        {
            m_zWidth = std::stod(pHeadTiXmlElement->GetText());
        }
        else if (pHeadTiXmlElement->ValueStr() == "NLayers")
        {
            m_nLayers = std::stoi(pHeadTiXmlElement->GetText());
        }
    }
    return;
}
