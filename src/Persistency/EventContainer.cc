/**
 *  @file   src/EventContainer.cc
 *
 *  @brief  Implementation of the EventContainer class.
 *
 *  $Log: $
 */

#include "Persistency/EventContainer.hh"
#include "Xml/tinyxml.hh"

EventContainer::EventContainer(const InputParameters *pInputParameters) :
    m_pInputParameters(pInputParameters),
    m_currentEvent(0)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

EventContainer::~EventContainer()
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void EventContainer::BeginOfEventAction()
{
//    m_mcParticles = MCParticleList();
//    m_cells = CellList();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void EventContainer::EndOfEventAction()
{
    this->SaveXml();
    m_cells.ClearCellList();
    m_mcParticles.Clear();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void EventContainer::BeginOfRunAction()
{
    // XML document
    if(m_pTiXmlDocument != 0x0)
    {
      delete m_pTiXmlDocument;
      m_pTiXmlDocument = 0x0;
    }
    // Element for the run
    if(m_pTiXmlDocument != 0x0)
    {
      delete m_pTiXmlDocument;
      m_pTiXmlDocument = 0x0;
    }
  
    m_pTiXmlDocument = new TiXmlDocument();
    m_pTiXmlRunElement = new TiXmlElement("Run");
    m_pTiXmlDocument->LinkEndChild(m_pTiXmlRunElement);

    m_mcParticles = MCParticleList();
    m_cells = CellList();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void EventContainer::EndOfRunAction()
{
    m_pTiXmlDocument->SaveFile(m_pInputParameters->GetOutputXmlFileName());
    m_pTiXmlDocument->Clear();
    // XML document
    if(m_pTiXmlDocument != 0x0)
    {
      delete m_pTiXmlDocument;
      m_pTiXmlDocument = 0x0;
    }
    // Element for the run
    if(m_pTiXmlDocument != 0x0)
    {
      delete m_pTiXmlDocument;
      m_pTiXmlDocument = 0x0;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void EventContainer::SaveXml()
{
//    TiXmlDocument tiXmlDocument;

//    TiXmlElement *pRunTiXmlElement = new TiXmlElement("Run");
//    tiXmlDocument.LinkEndChild(pRunTiXmlElement);

//    for (int eventNumber = 0; eventNumber < m_currentEvent; eventNumber++)
//    {
      TiXmlElement *pEventTiXmlElement = new TiXmlElement("Event");
      m_pTiXmlRunElement->LinkEndChild(pEventTiXmlElement);

//      const CellList &cellList(m_cells.at(eventNumber));
//      const MCParticleList &m_mcParticles(m_mcParticles.at(eventNumber));

      // Cells
      for (const auto iter : m_cells.m_idCellMap)
      {
          const Cell *pCell(iter.second);

          // If below threshold then don't write out this cell
          if (pCell->GetEnergy() < m_pInputParameters->GetCellEnergyThreshold())
          {
              continue;
          }

          IntFloatVector trackIdToEnergy(m_cells.m_mcComponents.at(pCell->GetIdx()));

          // ATTN : Doesn't account for track ID offset, but not using for now
          int mainMCTrackId(-1);
          float largestEnergyContribution(0.f);
          for (const auto contribution : trackIdToEnergy)
          {
              if (contribution.second > largestEnergyContribution)
              {
                  largestEnergyContribution = contribution.second;
                  mainMCTrackId = contribution.first;
              }
          }

          if (largestEnergyContribution < std::numeric_limits<float>::epsilon())
              continue;

          int mainVisibleMCTrackId(mainMCTrackId);
          while (!m_mcParticles.KnownParticle(mainVisibleMCTrackId))
          {
              if (m_mcParticles.m_trackIdParentMap.find(mainVisibleMCTrackId) != m_mcParticles.m_trackIdParentMap.end())
              {
                  mainVisibleMCTrackId = m_mcParticles.m_trackIdParentMap.at(mainVisibleMCTrackId);
              }
              else
              {
                  mainVisibleMCTrackId = 0;
                  break;
              }
          }

          TiXmlElement *pTiXmlElement = new TiXmlElement("Cell");
          pTiXmlElement->SetAttribute("Id", pCell->GetIdx());
          pTiXmlElement->SetAttribute("MCId", mainVisibleMCTrackId);
          pTiXmlElement->SetDoubleAttribute("X", pCell->GetX());
          pTiXmlElement->SetDoubleAttribute("Y", pCell->GetY());
          pTiXmlElement->SetDoubleAttribute("Z", pCell->GetZ());
          pTiXmlElement->SetDoubleAttribute("Energy", pCell->GetEnergy());
          pEventTiXmlElement->LinkEndChild(pTiXmlElement);
      }

      // MCParticles
      for (const auto iter : m_mcParticles.m_mcParticles)
      {
          const MCParticle *pMCParticle(iter.second);

          TiXmlElement *pTiXmlElement = new TiXmlElement("MCParticle");
          pTiXmlElement->SetAttribute("Id", pMCParticle->GetTrackId());
          pTiXmlElement->SetAttribute("PDG", pMCParticle->GetPDGCode());
          pTiXmlElement->SetAttribute("ParentId", pMCParticle->GetParent());
          pTiXmlElement->SetDoubleAttribute("Mass", pMCParticle->GetMass());
          pTiXmlElement->SetDoubleAttribute("Energy", pMCParticle->GetEnergy());
          pTiXmlElement->SetDoubleAttribute("StartX", pMCParticle->GetPositionX());
          pTiXmlElement->SetDoubleAttribute("StartY", pMCParticle->GetPositionY());
          pTiXmlElement->SetDoubleAttribute("StartZ", pMCParticle->GetPositionZ());
          pTiXmlElement->SetDoubleAttribute("EndX", pMCParticle->GetEndPositionX());
          pTiXmlElement->SetDoubleAttribute("EndY", pMCParticle->GetEndPositionY());
          pTiXmlElement->SetDoubleAttribute("EndZ", pMCParticle->GetEndPositionZ());
          pTiXmlElement->SetDoubleAttribute("MomentumX", pMCParticle->GetMomentumX());
          pTiXmlElement->SetDoubleAttribute("MomentumY", pMCParticle->GetMomentumY());
          pTiXmlElement->SetDoubleAttribute("MomentumZ", pMCParticle->GetMomentumZ());
          pEventTiXmlElement->LinkEndChild(pTiXmlElement);
      }
//    }

//    tiXmlDocument.SaveFile(m_pInputParameters->GetOutputXmlFileName());
//    tiXmlDocument.Clear();
}

