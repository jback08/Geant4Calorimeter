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
// $Id: exampleG4TPC.cc 86065 2014-11-07 08:51:15Z gcosmo $
//
/// \file exampleG4TPC.cc
/// \brief Main program of the G4TPC example

#include "G4TPCDetectorConstruction.hh"
#include "G4TPCActionInitialization.hh"
#include "InputParameters.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "G4StepLimiterPhysics.hh"
#include "FTFP_BERT.hh"
#include "QGSP_BERT.hh"

#include "Randomize.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

//------------------------------------------------------------------------------

namespace
{

void PrintUsage()
{
    std::cout << " Usage: " << G4endl;
    std::cout << " G4TPC ConfigFile.xml" << G4endl;
}

}

//------------------------------------------------------------------------------

int main(int argc,char** argv)
{
    // Evaluate arguments
    if ( argc != 2 )
    {
        PrintUsage();
        return 1;
    }

    const InputParameters inputParameters(argv[1]);

    if (!inputParameters.Valid())
    {
        PrintUsage();
        return 1;
    }

    // Choose the Random engine
    G4Random::setTheEngine(new CLHEP::RanecuEngine);

    // Construct the default run manager
    G4RunManager *pG4RunManager = new G4RunManager;

    // Set mandatory and optional initialization classes
    G4TPCDetectorConstruction *pG4TPCDetectorConstruction = new G4TPCDetectorConstruction(&inputParameters);
    pG4RunManager->SetUserInitialization(pG4TPCDetectorConstruction);

    G4VModularPhysicsList *pG4VModularPhysicsList = new QGSP_BERT;
    pG4VModularPhysicsList->RegisterPhysics(new G4StepLimiterPhysics());
    pG4RunManager->SetUserInitialization(pG4VModularPhysicsList);

    G4TPCActionInitialization *pG4TPCActionInitialization = new G4TPCActionInitialization(pG4TPCDetectorConstruction, &inputParameters);
    pG4RunManager->SetUserInitialization(pG4TPCActionInitialization);

    // Initialize visualization
    G4VisManager* pG4VisManager = new G4VisExecutive;
    pG4VisManager->Initialize();

    // Get the pointer to the User Interface manager
    G4UImanager* pG4UImanager = G4UImanager::GetUIpointer();
    pG4UImanager->ApplyCommand("/run/initialize");

    unsigned int nEventsToProcess(inputParameters.GetUseParticleGun() ? inputParameters.GetMaxNEventsToProcess() :
        std::min(inputParameters.GetGenieNEvents(), inputParameters.GetMaxNEventsToProcess()));

    pG4UImanager->ApplyCommand("/run/beamOn " + std::to_string(nEventsToProcess));

    delete pG4VisManager;
    delete pG4RunManager;
}

//------------------------------------------------------------------------------
