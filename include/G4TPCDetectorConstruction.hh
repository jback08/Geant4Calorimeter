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
// $Id: G4TPCDetectorConstruction.hh 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file G4TPCDetectorConstruction.hh
/// \brief Definition of the G4TPCDetectorConstruction class

#ifndef G4TPCDetectorConstruction_h
#define G4TPCDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "Cell.hh"

#include "globals.hh"
#include <math.h>

class G4VPhysicalVolume;
class G4UserLimits;
class G4Step;
class InputParameters;

class G4TPCDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    /**
    *  @brief  Constructor
    *
    *  @param  inputParameters configurable parameters
    */
    G4TPCDetectorConstruction(const InputParameters &inputParameters);

    /**
    *  @brief  Destrucctor
    */
    ~G4TPCDetectorConstruction() override;

    /**
    *  @brief  Define materials and build volumes
    *
    *  @return the world volume
    */
    G4VPhysicalVolume *Construct() override;

    /**
    *  @brief  Get the LArTPC physical volume
    *
    *  @return physical volume
    */
    const G4VPhysicalVolume *GetLArPV() const;

    /**
    *  @brief  Get the index of the cell for the given position
    *
    *  @param  pG4Step the step depositing energy
    *
    *  @return cell index
    */
    Cell GetCell(const G4Step *pG4Step) const;

private:
    /**
    *  @brief  Create materials used in simulation
    */
    void DefineMaterials();

    /**
    *  @brief  Create volumes used in simulation
    *
    *  @return the world volume
    */
    G4VPhysicalVolume *DefineVolumes();

    G4double             m_xCenter;              ///< X center of LArTPC
    G4double             m_yCenter;              ///< Y center of LArTPC
    G4double             m_zCenter;              ///< Z center of LArTPC
    G4double             m_xWidth;               ///< X width of LArTPC
    G4double             m_yWidth;               ///< Y width of LArTPC
    G4double             m_zWidth;               ///< Z width of LArTPC
    G4double             m_xLow;                 ///< Low x point in detector
    G4double             m_yLow;                 ///< Low y point in detector
    G4double             m_zLow;                 ///< Low z point in detector
    G4int                m_nLayers;              ///< Number of layers in detector
    G4VPhysicalVolume*   m_pG4LogicalVolumeLAr;  ///< The absorber physical volume
    G4bool               m_checkOverlaps;        ///< Option to activate checking of volumes overlaps
};

//------------------------------------------------------------------------------

inline const G4VPhysicalVolume *G4TPCDetectorConstruction::GetLArPV() const
{
    return m_pG4LogicalVolumeLAr;
}

#endif

