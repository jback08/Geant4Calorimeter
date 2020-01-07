/**
 *  @file   src/InputParameters.cc
 *
 *  @brief  Implementation of the InputParameters class.
 *
 *  $Log: $
 */
#include <fstream>
#include <algorithm>

#include "G4SystemOfUnits.hh"

#include "Xml/tinyxml.hh"
#include "ControlFlow/InputParameters.hh"

InputParameters::InputParameters() :
    m_useParticleGun(false),
    m_energy(-1.),
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
    m_nLayers(1000),
    m_maxNEventsToProcess(std::numeric_limits<int>::max())
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

InputParameters::InputParameters(const std::string &inputXmlFileName)
{
    this->LoadViaXml(inputXmlFileName);

    if (m_useGenieInput)
        this->LoadGenieEvents();
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

        if (m_maxNEventsToProcess <= 0 || m_nParticlesPerEvent <= 0)
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
        else if (pHeadTiXmlElement->ValueStr() == "MaxNEventsToProcess")
        {
            m_maxNEventsToProcess = std::stoi(pHeadTiXmlElement->GetText());
        }
    }
    return;
}

//------------------------------------------------------------------------------

void InputParameters::LoadGenieEvents()
{
    std::ifstream inputFile(m_genieTrackerFile);

    if (!inputFile.is_open())
    {
        std::cout << "Unable to load genie event from the following file : " << m_genieTrackerFile << std::endl;
    }

    std::string line;
    StringVector tokens;
    unsigned int eventStatus(0);

    GenieEvent *pGenieEvent(nullptr);

    while(std::getline(inputFile, line))
    {
        tokens = TokeniseLine(line, " $");

        if(eventStatus == 0 && tokens[0] == "begin")
        {
            pGenieEvent = new GenieEvent();
            eventStatus = 1;
        }
        else if(eventStatus == 1 && tokens[0] == "nuance")
        {
            pGenieEvent->SetNuanceCode(std::atoi(tokens[1].c_str()));
            eventStatus = 2;
        }
        else if(eventStatus == 2 && tokens[0] == "vertex")
        {
            pGenieEvent->SetVertex(std::stod(tokens[1].c_str()), std::stod(tokens[2].c_str()), std::stod(tokens[3].c_str()));
            //currentEvent.fTime = helpers::atof(tokens[4]);
            eventStatus = 3;
        }
        else if(eventStatus == 3 && tokens[0] == "track")
        {
            const GenieEvent::Track neutrinoTrack(tokens);
            pGenieEvent->SetNeutrinoTrack(&neutrinoTrack);
            eventStatus = 4;
        }
        else if(eventStatus == 4 && tokens[0] == "track")
        {
            // If the final token is not equal to zero then we don't want to consider this particle
            if(tokens[6] == "0")
            {
                const GenieEvent::Track daughterTrack(tokens);
                pGenieEvent->AddDaughterTrack(&daughterTrack);
            }
        }
        else if(eventStatus == 4 && tokens[0] == "end")
        {
            // We have reached the end of this event, so save the event and move on
            m_genieEvents.push_back(*pGenieEvent);
            delete pGenieEvent;
            eventStatus = 0;
        }
        else if(eventStatus == 0 && tokens[0] == "stop")
        {
            std::cout << "Finished reading input file " << m_genieTrackerFile << std::endl;
        }
        else
        {
            std::cout << "Something has gone wrong in the file. Event status = " << eventStatus << " but line token = " << tokens[0] << std::endl;
        }
    }
}

//------------------------------------------------------------------------------

StringVector InputParameters::TokeniseLine(const std::string &line, const std::string &sep)
{
    std::size_t startToken = 0, endToken = 0;
    StringVector tokens;

    if(sep.size() == 0 || line.size() == 0)
        return tokens;

    while(startToken < line.size())
    {
        // Find the first character that isn't a separator
        startToken = line.find_first_not_of(sep,startToken);

        if(startToken == line.npos)
        {
            endToken = line.size();
        }
        else
        {
            //Find end of token
            endToken = line.find_first_of(sep, startToken);

            if (endToken == line.npos)
            {
                // If there was no end of token, assign it to the end of string
                endToken = line.size();
            }

            // Add this token to our vector
            tokens.push_back(line.substr(startToken,endToken-startToken));

            // We want to start looking from the end of this substring next iteration
            startToken = endToken;
        }
    }
    return tokens;
}

