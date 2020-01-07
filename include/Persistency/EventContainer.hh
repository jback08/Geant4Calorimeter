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

#include "ControlFlow/InputParameters.hh"

#include "Objects/Cell.hh"
#include "Objects/MCParticle.hh"

#include "Xml/tinyxml.hh"

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
     *  @brief  Increment variables for current event
     */
    void BeginOfEventAction();

    /**
     *  @brief  Increment variables for next event
     */
    void EndOfEventAction();

    /**
     *  @brief  Create file on run start
     */  
    void BeginOfRunAction();

    /**
     *  @brief  Save and close file on run end
     */  
    void EndOfRunAction();

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
     *  @return m_currentEvent
     */
    int GetEventNumber() const;

    /**
     *  @brief  Set the event number
     */
    void SetEventNumber(G4int eventNumber);

private:
    const InputParameters     *m_pInputParameters;  ///< Input parameters

    G4int m_currentEvent;
    CellList m_cells;
    MCParticleList m_mcParticles;

    TiXmlDocument* m_pTiXmlDocument;
    TiXmlElement*  m_pTiXmlRunElement;
};

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline CellList &EventContainer::GetCurrentCellList()
{
    return m_cells;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline MCParticleList &EventContainer::GetCurrentMCParticleList()
{
    return m_mcParticles;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline void EventContainer::SetCurrentMCParticleList(const MCParticleList &mcParticleList)
{
    m_mcParticles = mcParticleList;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int EventContainer::GetEventNumber() const
{
   return m_currentEvent;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline void EventContainer::SetEventNumber(G4int eventNumber)
{
   m_currentEvent = eventNumber;
}

#endif // #ifndef EVENT_CONTAINER_H
