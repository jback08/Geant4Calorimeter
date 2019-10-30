/**
 *  @file   src/GenieEvent.cc
 *
 *  @brief  Implementation of the GenieEvent class.
 *
 *  $Log: $
 */
#include <string>
#include <iostream>

#include "Objects/GenieEvent.hh"

GenieEvent::GenieEvent() :
    m_pNeutrinoTrack(nullptr),
    m_daughterTracks(TrackList()),
    m_vertexX(std::numeric_limits<double>::max()),
    m_vertexY(std::numeric_limits<double>::max()),
    m_vertexZ(std::numeric_limits<double>::max())
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

GenieEvent::GenieEvent(const GenieEvent &rhs) :
    m_nuanceCode(rhs.m_nuanceCode),
    m_vertexX(rhs.m_vertexX),
    m_vertexY(rhs.m_vertexY),
    m_vertexZ(rhs.m_vertexZ)
{
    m_pNeutrinoTrack = new Track(*(rhs.m_pNeutrinoTrack));

    for (const Track *pDaughterTrack : rhs.m_daughterTracks)
        m_daughterTracks.push_back(new Track(*pDaughterTrack));
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

GenieEvent &GenieEvent::operator=(const GenieEvent &rhs)
{
    if (this != &rhs)
    {
        m_nuanceCode = rhs.m_nuanceCode;
        m_vertexX = rhs.m_vertexX;
        m_vertexY = rhs.m_vertexY;
        m_vertexZ = rhs.m_vertexZ;
        m_pNeutrinoTrack = (rhs.m_pNeutrinoTrack ?  new Track(*(rhs.m_pNeutrinoTrack)) : nullptr);

        for (const Track *pDaughterTrack : rhs.m_daughterTracks)
            m_daughterTracks.push_back(new Track(*pDaughterTrack));
    }

    return *this;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

GenieEvent::~GenieEvent()
{
    delete m_pNeutrinoTrack;

    for (const Track *pDaughterTrack : m_daughterTracks)
        delete pDaughterTrack;

    m_daughterTracks.clear();
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

GenieEvent::Track::Track(const StringVector &tokens) :
    m_pdg(std::atoi(tokens.at(1).c_str())),
    m_energy(std::stod(tokens.at(2).c_str())/1000.),
    m_directionX(std::stod(tokens.at(3).c_str())),
    m_directionY(std::stod(tokens.at(4).c_str())),
    m_directionZ(std::stod(tokens.at(5).c_str()))
{
    // ATTN : Genie standard hass enenrgy in MeV, convert to GeV here.
    // ATTN : Nuance-style pdg code for argon, PDG standard: 100ZZZAAAI:, ZZZ = 018, AAA = 040, hence argon = 1000180400
    if (m_pdg == 18040)
        m_pdg = 1000180400;
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
