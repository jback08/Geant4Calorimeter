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
// $Id: G4TPCRunAction.hh 74265 2013-10-02 14:41:20Z gcosmo $
// 
/// \file G4TPCRunAction.hh
/// \brief Definition of the G4TPCRunAction class

#ifndef G4TPCRunAction_h
#define G4TPCRunAction_h 1

#include "G4MCParticleUserAction.hh"
#include "G4UserRunAction.hh"

#include "globals.hh"

class G4Run;

class G4TPCRunAction : public G4UserRunAction
{
public:
    /**
    *  @brief  Constructor
    *
    *  @param  pEventContainer event information
    *  @param  pG4MCParticleUserAction MCParticle user actions
    */
    G4TPCRunAction(EventContainer *pEventContainer, G4MCParticleUserAction *pG4MCParticleUserAction);

    /**
    *  @brief  Destructor
    */
    ~G4TPCRunAction() override;

    /**
    *  @brief  Start of run action
    *
    *  @param  pG4Run the current run
    */
    void BeginOfRunAction(const G4Run *pG4Run) override;

    /**
    *  @brief  End of run action
    *
    *  @param  pG4Run the current run
    */
    void EndOfRunAction(const G4Run *pG4Run) override;

private:
    EventContainer         *m_pEventContainer;          ///< Event information
    G4MCParticleUserAction *m_pG4MCParticleUserAction;  ///< MCParticle user actions
};

#endif
