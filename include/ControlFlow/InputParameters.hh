/**
 *  @file   include/InputParameters.cc
 *
 *  @brief  Header file for the InputParameters class.
 *
 *  $Log: $
 */

#ifndef INPUT_PARAMETERS_H
#define INPUT_PARAMETERS_H 1

#include <iostream>
#include <vector>

#include "Objects/GenieEvent.hh"

typedef std::vector<GenieEvent> GenieEvents;

class TiXmlElement;

/**
 *  @brief InputParameters class
 */
class InputParameters
{
public:
    /**
     *  @brief  Default Constructor
     */
    InputParameters();

    /**
     *  @brief  Constructor
     *
     *  @param  configuration xml
     */
    InputParameters(const std::string &inputXmlFileName);

    /**
     *  @brief  Destructor
     */
    ~InputParameters();

    /**
     *  @brief  Check if input parameters are valid
     *
     *  @return bool are parameters valid
     */
    bool Valid() const;

    /**
     *  @brief  Get use particle gun
     *
     *  @return m_useParticleGun
     */
    bool GetUseParticleGun() const;

    /**
     *  @brief  Get particle gun species
     *
     *  @return m_species
     */
    std::string GetParticleGunSpecies() const;

    /**
     *  @brief  Get output xml file name
     *
     *  @return m_outputFileName
     */
    std::string GetOutputXmlFileName() const;

    /**
     *  @brief  Get particle gun energy
     *
     *  @return m_energy
     */
    double GetParticleGunEnergy() const;

    /**
     *  @brief  Get number of particles to simulate (via particle gun) per event
     *
     *  @return m_nParticlesPerEvent
     */
    int GetParticleGunNParticlesPerEvent() const;

    /**
     *  @brief  Get keep em shower daughter
     *
     *  @return m_keepEMShowerDaughters 
     */
    bool GetKeepEMShowerDaughters() const;

    /**
     *  @brief  Get hit energy threshold
     *
     *  @return m_energyCut
     */
    double GetHitEnergyThreshold() const;

    /**
     *  @brief  Whether to use genie input
     *
     *  @return m_useGenieInput
     */
    bool GetUseGenieInput() const;

    /**
     *  @brief  Get genie tracker file
     *
     *  @return m_genieTrackerFile
     */
    std::string GetGenieTrackerFile() const;

    /**
     *  @brief  Get number of events in genie tracker file
     *
     *  @return m_nGenieEvents
     */
    int GetGenieNEvents() const;

    /**
     *  @brief  Get the x center of the detector
     *
     *  @return m_xCenter
     */
    double GetCenterX() const;

    /**
     *  @brief  Get the y center of the detector
     *
     *  @return m_yCenter
     */
    double GetCenterY() const;

    /**
     *  @brief  Get the z center of the detector
     *
     *  @return m_zCenter
     */
    double GetCenterZ() const;

    /**
     *  @brief  Get the x width of the detector
     *
     *  @return m_xWidth
     */
    double GetWidthX() const;

    /**
     *  @brief  Get the y width of the detector
     *
     *  @return m_yWidth
     */
    double GetWidthY() const;

    /**
     *  @brief  Get the z width of the detector
     *
     *  @return m_zWidth
     */
    double GetWidthZ() const;

    /**
     *  @brief  Get the number of layers for 3D binning
     *
     *  @return m_nLayers
     */
    int GetNLayers() const;

    /**
     *  @brief  Get vector of genie events
     *
     *  @return m_genieEvents
     */
    GenieEvents GetGenieEvents() const;

    /**
     *  @brief  Get maximum number of events to process
     *
     *  @return m_maxNEventsToProcess
     */
    int GetMaxNEventsToProcess() const;

    /**
     *  @brief  Get should write LArTPC 2D hits
     *
     *  @return m_shouldWriteLArTPCHits;
     */
    bool GetShouldWriteLArTPCHits() const;

    /**
     *  @brief  Get dual phase mode
     *
     *  @return m_dualPhaseMode
     */
    bool GetDualPhaseMode() const;

    /**
     *  @brief  Get wire angle for the U view
     *
     *  @return m_wireAngleU
     */
    double GetWireAngleU() const;

    /**
     *  @brief  Get wire angle for the V view
     *
     *  @return m_wireAngleV
     */
    double GetWireAngleV() const;

    /**
     *  @brief  Get wire angle for the W view
     *
     *  @return m_wireAngleW
     */
    double GetWireAngleW() const;

    /**
     *  @brief  Get the wire pitch for the U view
     *
     *  @return m_wirePitchU
     */
    double GetWirePitchU() const;

    /**
     *  @brief  Get the wire pitch for the V view
     *
     *  @return m_wirePitchV
     */
    double GetWirePitchV() const;

    /**
     *  @brief  Get the wire pitch for the W view
     *
     *  @return m_wirePitchW
     */
    double GetWirePitchW() const;

    /**
     *  @brief  Get the hit width in the drift time direction
     *
     *  @return m_driftTimeWidth
     */
    double GetDriftTimeWidth() const;

    /**
     *  @brief  Get the LArTPC 2D hit energy threshold
     *
     *  @return m_larTPCHitEnergyThreshold
     */
    double GetLArTPCHitEnergyThreshold() const;

private:
    /**
     *  @brief  Load input parameters via xml
     *
     *  @param  inputXmlFileName
     */
    void LoadViaXml(const std::string &inputXmlFileName);

    /**
     *  @brief  Parse tiny xml element containing a bool
     *
     *  @param  pHeadTiXmlElement element to parse
     */
    bool ParseBoolArgument(TiXmlElement *pHeadTiXmlElement);

    /**
     *  @brief  Load events from genie tracker file
     */
    void LoadGenieEvents();

    /**
     *  @brief  Divide string into series based on deliminator location
     *
     *  @param  line input
     *  @param  sep deliminator
     *
     *  @return tokenized string
     */
    static StringVector TokeniseLine(const std::string &line, const std::string &sep);

    // Particle gun setup
    bool                 m_useParticleGun;             ///< Should generate events using G4 particle gun
    std::string          m_species;                    ///< Particle type to simulate if using particle gun
    double               m_energy;                     ///< Energy (total) of particles to simulate
    int                  m_nParticlesPerEvent;         ///< Number of particles per event

    // Genie input
    bool                 m_useGenieInput;              ///< Should use genie input
    std::string          m_genieTrackerFile;           ///< Genie tracker file
    GenieEvents          m_genieEvents;                ///< Genie events

    // Geant4 parameters
    std::string          m_outputFileName;             ///< Output file (xml) to write to
    bool                 m_keepEMShowerDaughters;      ///< Should keep/discard em shower daughter mc particles
    double               m_energyCut;                  ///< Energy threshold for tracking

    // Detector properties
    double               m_xCenter;                    ///< X center of detector (mm)
    double               m_yCenter;                    ///< Y center of detector (mm)
    double               m_zCenter;                    ///< Z center of detector (mm)
    double               m_xWidth;                     ///< Detector width along x (mm)
    double               m_yWidth;                     ///< Detector width along y (mm)
    double               m_zWidth;                     ///< Detector width along z (mm)
    int                  m_nLayers;                    ///< Number of layers for defining 3D hit binning
    int                  m_maxNEventsToProcess;        ///< Maximum number of events to process

    // Writing out images
    bool                 m_shouldWriteLArTPCHits;      ///< Whether to write out the LArTPC model hits
    bool                 m_dualPhaseMode;              ///< Whether to write out the U/W or the U/V/W views
    double               m_wireAngleU;                 ///< Wire angle (to vertical y) for U view
    double               m_wireAngleV;                 ///< Wire angle (to vertical y) for V view
    double               m_wireAngleW;                 ///< Wire angle (to vertical y) for W view
    double               m_wirePitchU;                 ///< Wire pitch for U view
    double               m_wirePitchV;                 ///< Wire pitch for V view
    double               m_wirePitchW;                 ///< Wire pitch for W view
    double               m_driftTimeWidth;             ///< Width of hit in drift time
    double               m_larTPCHitEnergyThreshold;   ///< Threshold to apply to the spoof LArTPC model (2D) hits
};

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline bool InputParameters::GetUseParticleGun() const
{
    return m_useParticleGun;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline std::string InputParameters::GetParticleGunSpecies() const
{
    return m_species;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline std::string InputParameters::GetOutputXmlFileName() const
{
    return m_outputFileName;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double InputParameters::GetParticleGunEnergy() const
{
    return m_energy;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int InputParameters::GetParticleGunNParticlesPerEvent() const
{
    return m_nParticlesPerEvent;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline bool InputParameters::GetKeepEMShowerDaughters() const
{
    return m_keepEMShowerDaughters;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double InputParameters::GetHitEnergyThreshold() const
{
    return m_energyCut;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline bool InputParameters::GetUseGenieInput() const
{
    return m_useGenieInput;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline std::string InputParameters::GetGenieTrackerFile() const
{
    return m_genieTrackerFile;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int InputParameters::GetGenieNEvents() const
{
    return m_genieEvents.size();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double InputParameters::GetCenterX() const
{
    return m_xCenter;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double InputParameters::GetCenterY() const
{
    return m_yCenter;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double InputParameters::GetCenterZ() const
{
    return m_zCenter;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double InputParameters::GetWidthX() const
{
    return m_xWidth;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double InputParameters::GetWidthY() const
{
    return m_yWidth;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double InputParameters::GetWidthZ() const
{
    return m_zWidth;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int InputParameters::GetNLayers() const
{
    return m_nLayers;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline GenieEvents InputParameters::GetGenieEvents() const
{
    return m_genieEvents;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int InputParameters::GetMaxNEventsToProcess() const
{
    return m_maxNEventsToProcess;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline bool InputParameters::GetShouldWriteLArTPCHits() const
{
    return m_shouldWriteLArTPCHits;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline bool InputParameters::GetDualPhaseMode() const
{
    return m_dualPhaseMode;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double InputParameters::GetWireAngleU() const
{
    return m_wireAngleU;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double InputParameters::GetWireAngleV() const
{
    return m_wireAngleV;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double InputParameters::GetWireAngleW() const
{
    return m_wireAngleW;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double InputParameters::GetWirePitchU() const
{
    return m_wirePitchU;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double InputParameters::GetWirePitchV() const
{
    return m_wirePitchV;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double InputParameters::GetWirePitchW() const
{
    return m_wirePitchW;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double InputParameters::GetDriftTimeWidth() const
{
    return m_driftTimeWidth;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double InputParameters::GetLArTPCHitEnergyThreshold() const
{
    return m_larTPCHitEnergyThreshold;
}

#endif // #ifndef INPUT_PARAMETERS_H
