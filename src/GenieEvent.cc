/**
 *  @file   src/GenieEvent.cc
 *
 *  @brief  Implementation of the GenieEvent class.
 *
 *  $Log: $
 */
#include "GenieEvent.hh"

GenieEvent::GenieEvent() :
    m_neutrinoTrack(Track()),
    m_nuanceCode(0),
    m_vertexX(std::numeric_limits<double>::max()),
    m_vertexY(std::numeric_limits<double>::max()),
    m_vertexZ(std::numeric_limits<double>::max())
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------------------------------------------------------------------ 

GenieEvent::Track::Track() :
    m_pdg(0),
    m_energy(std::numeric_limits<double>::max()),
    m_directionX(std::numeric_limits<double>::max()),
    m_directionY(std::numeric_limits<double>::max()),
    m_directionZ(std::numeric_limits<double>::max())
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

GenieEvent::Track::Track(int pdg, double energy, double directionX, double directionY, double directionZ) :
    m_pdg(pdg),
    m_energy(energy),
    m_directionX(directionX),
    m_directionY(directionY),
    m_directionZ(directionZ)
{
}
