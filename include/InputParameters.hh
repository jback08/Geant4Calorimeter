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
     *  @brief  Get number of event to simulate
     *
     *  @return m_nEvents
     */
    int GetParticleGunNEvents() const;

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

private:
    /**
     *  @brief  Load input parameters via xml
     *
     *  @param  inputXmlFileName
     */
    void LoadViaXml(const std::string &inputXmlFileName);

    // Particle gun setup
    bool                 m_useParticleGun;        ///< Should generate events using G4 particle gun
    std::string          m_species;               ///< Particle type to simulate if using particle gun
    double               m_energy;                ///< Energy (total) of particles to simulate
    int                  m_nEvents;               ///< Number of events to simulate
    int                  m_nParticlesPerEvent;    ///< Number of particles per event

    // Genie input
    bool                 m_useGenieInput;         ///< Should use genie input
    std::string          m_genieTrackerFile;      ///< Genie tracker file

    // Geant4 parameters
    std::string          m_outputFileName;        ///< Output file (xml) to write to
    bool                 m_keepEMShowerDaughters; ///< Should keep/discard em shower daughter mc particles
    double               m_energyCut;             ///< Energy threshold for tracking

    // Detector properties
    double               m_xCenter;               ///< X center of detector (mm)
    double               m_yCenter;               ///< Y center of detector (mm)
    double               m_zCenter;               ///< Z center of detector (mm)
    double               m_xWidth;                ///< Detector width along x (mm)
    double               m_yWidth;                ///< Detector width along y (mm)
    double               m_zWidth;                ///< Detector width along z (mm)
    int                  m_nLayers;               ///< Number of layers for defining 3D hit binning
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

inline int InputParameters::GetParticleGunNEvents() const
{
    return m_nEvents;
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

#endif // #ifndef INPUT_PARAMETERS_H
