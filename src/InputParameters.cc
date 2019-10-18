/**
 *  @file   src/InputParameters.cc
 *
 *  @brief  Implementation of the InputParameters class.
 *
 *  $Log: $
 */

#include "Xml/tinyxml.hh"
#include "InputParameters.hh"

InputParameters::InputParameters() :
    m_useParticleGun(false),
    m_species(""),
    m_outputFileName(""),
    m_energy(-1.),
    m_nEvents(1),
    m_nParticlesPerEvent(1),
    m_keepEMShowerDaughters(false),
    m_energyCut(0.001)
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
    if (m_energy < 0.)
    {
        std::cout << "Energy not specified" << std::endl;
        return false;
    }

    if (m_species.empty())
    {
        std::cout << "Particles species not specified" << std::endl;
        return false;
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
    }
    return;
}
