/**
 *  @file   include/EventContainer.hh
 *
 *  @brief  Header file for the EventContainer class.
 *
 *  $Log: $
 */

#ifndef EVENT_CONTAINER_H
#define EVENT_CONTAINER_H 1

#include <iostream>

#include "ControlFlow/InputParameters.hh"

#include "Objects/Cell.hh"
#include "Objects/MCParticle.hh"

/**
 *  @brief EventContainer class
 */
class EventContainer
{
public:
    /**
     *  @brief  Constructor
     *
     *  @param  pInputParameters input parameters
     */
    EventContainer(const InputParameters *pInputParameters);

    /**
     *  @brief  Destructor
     */
    ~EventContainer();

    /**
     *  @brief  Increment variables for current event
     */
    void BeginOfEventAction();

    /**
     *  @brief  Increment variables for next event
     */
    void EndOfEventAction();

    /**
     *  @brief  Save events to xml
     */
    void SaveXml();

    /**
    *  @brief  Get the current cell list
    *
    *  @return the current list of cells
    */
    CellList &GetCurrentCellList();

    /**
     *  @brief  Get the current MCParticle list
     *
     *  @return the current list of MCParticles
     */
    MCParticleList &GetCurrentMCParticleList();

    /**
     *  @brief  Set the current MCParticle list
     *
     *  @param  mcParticleList particle list to set
     */
    void SetCurrentMCParticleList(const MCParticleList &mcParticleList);

    /**
     *  @brief  Get the event number
     *
     *  @return m_eventNumber
     */
    int GetEventNumber() const;

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

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int EventContainer::GetEventNumber() const
{
   return m_eventNumber;
}

#endif // #ifndef EVENT_CONTAINER_H
