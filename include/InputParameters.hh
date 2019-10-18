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

private:
    /**
     *  @brief  Load input parameters via xml
     *
     *  @param  inputXmlFileName
     */
    void LoadViaXml(const std::string &inputXmlFileName);

    bool                 m_useParticleGun;        ///< Should generate events using G4 particle gun
    std::string          m_species;               ///< Particle type to simulate if using particle gun
    std::string          m_outputFileName;        ///< Output file (xml) to write to
    double               m_energy;                ///< Energy (total) of particles to simulate
    int                  m_nEvents;               ///< Number of events to simulate
    int                  m_nParticlesPerEvent;    ///< Number of particles per event
    bool                 m_keepEMShowerDaughters; ///< Should keep/discard em shower daughter mc particles
    double               m_energyCut;             ///< Energy threshold for tracking
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

#endif // #ifndef INPUT_PARAMETERS_H
