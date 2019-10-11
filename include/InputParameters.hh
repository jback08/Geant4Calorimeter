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
     *  Constructor
     */
    InputParameters();

    /**
     *  Destructor
     */
    ~InputParameters();

    /**
    *  @brief  Check if input parameters are valid
    *
    *  @return bool are parameters valid
    */
    bool Valid();

    std::string          m_species;               ///< Particle type to simulate if using particle gun
    std::string          m_outputFileName;        ///< Output file (xml) to write to
    double               m_energy;                ///< Energy (total) of particles to simulate
    int                  m_nEvents;               ///< Number of events to simulate
    int                  m_nParticlesPerEvent;    ///< Number of particles per event
    bool                 m_keepEMShowerDaughters; ///< Should keep/discard em shower daughter mc particles
    double               m_energyCut;             ///< Energy threshold for tracking
};

#endif // #ifndef INPUT_PARAMETERS_H
