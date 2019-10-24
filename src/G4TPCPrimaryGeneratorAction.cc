//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: G4TPCPrimaryGeneratorAction.cc 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file G4TPCPrimaryGeneratorAction.cc
/// \brief Implementation of the G4TPCPrimaryGeneratorAction class

#include <chrono>
#include <random>

#include "G4TPCPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"

//------------------------------------------------------------------------------

G4TPCPrimaryGeneratorAction::G4TPCPrimaryGeneratorAction(const InputParameters &parameters) :
    G4VUserPrimaryGeneratorAction(),
    m_pG4ParticleGun(nullptr),
    m_parameters(parameters),
    m_eventCouter(0)
{
    m_pG4ParticleGun = new G4ParticleGun();

    if (m_parameters.GetUseGenieInput())
        this->LoadGenieEvents();
}

//------------------------------------------------------------------------------

G4TPCPrimaryGeneratorAction::~G4TPCPrimaryGeneratorAction()
{
    if (m_pG4ParticleGun != nullptr)
        delete m_pG4ParticleGun;
}

//------------------------------------------------------------------------------

void G4TPCPrimaryGeneratorAction::GeneratePrimaries(G4Event *pG4Event)
{
    m_eventCouter++;

    G4LogicalVolume *worlLV = G4LogicalVolumeStore::GetInstance()->GetVolume("World");
    G4LogicalVolume *tpcLV = G4LogicalVolumeStore::GetInstance()->GetVolume("Calorimeter");
    G4Box *worldBox = nullptr;
    G4Box *tpcBox = nullptr;

    if (worlLV)
        worldBox = dynamic_cast<G4Box*>(worlLV->GetSolid());

    if (tpcLV)
        tpcBox = dynamic_cast<G4Box*>(tpcLV->GetSolid());

    if (!worldBox || !tpcBox)
    {
        G4ExceptionDescription msg;
        msg << "Unable to cast G4LogicalVolume to G4Box for world and TPC volumes." << G4endl;
        G4Exception("G4TPCPrimaryGeneratorAction::GeneratePrimaries()", "MyCode0002", EventMustBeAborted, msg);
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    CLHEP::HepRandom::setTheSeed(seed);

    if (m_parameters.GetUseParticleGun())
    {
        for (int particle = 0; particle < m_parameters.GetParticleGunNParticlesPerEvent(); particle++)
        {
            G4ThreeVector startPoint(tpcBox->GetPointOnSurface());
            G4ThreeVector endPoint(tpcBox->GetPointOnSurface());

            while (std::fabs(startPoint.x() - endPoint.x()) < std::numeric_limits<double>::epsilon() ||
                   std::fabs(startPoint.y() - endPoint.y()) < std::numeric_limits<double>::epsilon() ||
                   std::fabs(startPoint.z() - endPoint.z()) < std::numeric_limits<double>::epsilon())
            {
                endPoint = tpcBox->GetPointOnSurface();
            }

            G4ThreeVector direction(endPoint - startPoint);

            G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle(m_parameters.GetParticleGunSpecies().c_str());
            m_pG4ParticleGun->SetParticleDefinition(particleDefinition);
            m_pG4ParticleGun->SetParticlePosition(startPoint);
            m_pG4ParticleGun->SetParticleMomentumDirection(direction);
            m_pG4ParticleGun->SetParticleEnergy(m_parameters.GetParticleGunEnergy()*GeV);
            m_pG4ParticleGun->GeneratePrimaryVertex(pG4Event);
        }
    }
/*
    else if (m_parameters->GetUseGenieInput())
    {

  // File has the following format, repeated n_event times
   // $ begin
   // $ nuance <nuance_code>
   // $ vertex <x> <y> <z> <t>
   // $ track <pdg> <energy> <dir_x> <dir_y> <dir_z> <tracking_status>
   // $ track ... (repeat as necessary)
   // $ end

$ begin
$ nuance 1
$ vertex 0 0 0 0
$ track 14 3244 0 0 1 -1
$ track 18040 37215.5 -999 -999 -999 -1
$ track 2112 909.404 -0.303744 0.348279 0.886815 -1
$ track 2212 997.185 0.278017 0.437414 0.855205 -2
$ track 13 3156.22 -0.0508622 -0.0226286 0.998449 0
$ track 2212 943.662 -0.802833 -0.171477 0.571012 0
$ track 2212 1014.54 0.0325571 0.760753 0.648224 0
$ end

        this->LoadGenieEvents();
    }
*/
}

//------------------------------------------------------------------------------

void G4TPCPrimaryGeneratorAction::LoadGenieEvents()
{
    std::ifstream inputFile(m_parameters.GetGenieTrackerFile());

    if (!inputFile.is_open())
    {
        std::cout << "Unable to load genie event from the following file : " << m_parameters.GetGenieTrackerFile() << std::endl;
    }

    std::string line;
    std::vector<std::string> tokens;
    unsigned int eventStatus(0);

    GenieEvent genieEvent;

    while(std::getline(inputFile, line))
    {
        tokens = TokeniseLine(line, " $");

        if(eventStatus == 0 && tokens[0] == "begin")
        {
            genieEvent = GenieEvent();
            eventStatus = 1;
        }
        else if(eventStatus == 1 && tokens[0] == "nuance")
        {
            genieEvent.SetNuanceCode(std::atoi(tokens[1].c_str()));
            eventStatus = 2;
        }
        else if(eventStatus == 2 && tokens[0] == "vertex")
        {
            genieEvent.SetVertex(std::stod(tokens[1].c_str()), std::stod(tokens[2].c_str()), std::stod(tokens[3].c_str()));
            //currentEvent.fTime = helpers::atof(tokens[4]);
            eventStatus = 3;
        }
        else if(eventStatus == 3 && tokens[0] == "track")
        {
            const GenieEvent::Track neutrinoTrack = ParseTrackLine(tokens);
            genieEvent.SetNeutrinoTrack(neutrinoTrack);
            eventStatus = 4;
        }
        else if(eventStatus == 4 && tokens[0] == "track")
        {
            // If the final token is not equal to zero then we don't want to consider this particle
            if(tokens[6] == "0")
            {
                genieEvent.AddDaughterTrack(ParseTrackLine(tokens));
            }
        }
        else if(eventStatus == 4 && tokens[0] == "end")
        {
            // We have reached the end of this event, so save the event and move on
            m_genieEvents.push_back(genieEvent);
            eventStatus = 0;
        }
        else if(eventStatus == 4 && tokens[0] == "stop")
        {
            std::cout << "Finished reading input file " << m_parameters.GetGenieTrackerFile()  << std::endl;
        }
        else
        {
            std::cout << "Something has gone wrong in the file. Event status = " << eventStatus << " but line token = " << tokens[0] << std::endl;
        }
    }
}

//------------------------------------------------------------------------------

GenieEvent::Track G4TPCPrimaryGeneratorAction::ParseTrackLine(const std::vector<std::string> &tokens) const
{
    int pdg(std::atoi(tokens[1].c_str()));

    // ATTN: Nuance-style pdg code for argon, PDG standard: 100ZZZAAAI:, ZZZ = 018, AAA = 040, hence argon = 1000180400
    if (pdg == 18040)
        pdg = 1000180400;

    const double energy(std::stod(tokens[2].c_str()));
    const double directionX(std::stod(tokens[3].c_str()));
    const double directionY(std::stod(tokens[4].c_str()));
    const double directionZ(std::stod(tokens[5].c_str()));

    return GenieEvent::Track(pdg, energy, directionX, directionY, directionZ);
}

//------------------------------------------------------------------------------

StringVector G4TPCPrimaryGeneratorAction::TokeniseLine(const std::string &line, const std::string &sep)
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
