/**
 *  @file   include/EventContainer.cc
 *
 *  @brief  Header file for the EventContainer class.
 *
 *  $Log: $
 */

#ifndef EVENT_CONTAINER_H
#define EVENT_CONTAINER_H 1

#include <iostream>

#include "Cell.hh"
#include "InputParameters.hh"
#include "MCParticle.hh"

/**
 *  @brief EventContainer class
 */
class EventContainer
{
public:
    /**
     *  @brief  Default constructor
     *
     *  @param  pInputParameters input parameters
     */
    EventContainer(const InputParameters *pInputParameters);

    /**
     *  @brief  Destructor
     */
    ~EventContainer();

    /**
     *  Increment variables for current event
     */
    void BeginOfEventAction();

    /**
     *  Increment variables for next event
     */
    void EndOfEventAction();

    /**
     *  Save events to xml
     */
    void SaveXml();

    /**
    *  @brief  Get the current cell list
    *
    *  @return the current list of cells
    */
    CellList &GetCurrentCellList();

    /**
     *  Get the current MCParticle list
     *
     *  @return the current list of MCParticles
     */
    MCParticleList &GetCurrentMCParticleList();

    /**
     *  Set the current MCParticle list
     */
    void SetCurrentMCParticleList(const MCParticleList &mcParticleList);

private:
    typedef std::vector<MCParticleList> MCParticleListVector;
    typedef std::vector<CellList> CellListVector;

    int                        m_eventNumber;       ///< Event number
    MCParticleListVector       m_mcParticles;       ///< MCParticle list
    CellListVector             m_cells;             ///< Cell list
    const InputParameters     *m_pInputParameters;  ///< Input parameters
};

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline CellList &EventContainer::GetCurrentCellList()
{
    return m_cells.at(m_eventNumber);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline MCParticleList &EventContainer::GetCurrentMCParticleList()
{
    return m_mcParticles.at(m_eventNumber);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline void EventContainer::SetCurrentMCParticleList(const MCParticleList &mcParticleList)
{
    m_mcParticles.at(m_eventNumber) = mcParticleList;
}

#endif // #ifndef EVENT_CONTAINER_H
