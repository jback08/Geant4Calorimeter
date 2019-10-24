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
// $Id: G4TPCPrimaryGeneratorAction.hh 68058 2013-03-13 14:47:43Z gcosmo $
// 
/// \file G4TPCPrimaryGeneratorAction.hh
/// \brief Definition of the G4TPCPrimaryGeneratorAction class

#ifndef G4TPCPrimaryGeneratorAction_h
#define G4TPCPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

#include "InputParameters.hh"
#include "GenieEvent.hh"

class G4Event;
class G4ParticleGun;

typedef std::vector<std::string> StringVector;

/**
*  @brief  G4TPCPrimaryGeneratorAction class
*/
class G4TPCPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    /**
    *  @brief  Constructor
    *
    *  @param  parameters input information
    */
    G4TPCPrimaryGeneratorAction(const InputParameters &parameters);

    /**
    *  @brief  Destructor
    */
    ~G4TPCPrimaryGeneratorAction() override;

    /**
    *  @brief  Generate particles in the detector
    *
    *  @param  pG4Event the current event
    */
    void GeneratePrimaries(G4Event *pG4Event) override;

private:
    /**
     *  @brief  Load events from genie tracker file
     */
    void LoadGenieEvents();

    /**
     *  @brief  Convert genie track line into track object
     *
     *  @param  tokens line to convert
     *
     *  @return output track
     */
    GenieEvent::Track ParseTrackLine(const std::vector<std::string> &tokens) const;

    /**
     *  @brief  Divide string into series based on deliminator location
     *
     *  @param  line input
     *  @param  sep deliminator
     *
     *  @return tokenized string
     */
    static StringVector TokeniseLine(const std::string &line, const std::string &sep);

    typedef std::vector<GenieEvent> GenieEvents;

    G4ParticleGun   *m_pG4ParticleGun; ///< G4 particle gun
    InputParameters  m_parameters;     ///< Input parameters
    int              m_eventCouter;    ///< Event couter
    GenieEvents      m_genieEvents;    ///< Genie events
};

#endif


