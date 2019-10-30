/**
 *  @file   src/G4TPCMCParticleUserAction.cc
 *
 *  @brief  Implementation of the geant4 MCParticle user action class.
 *
 *  $Log: $
 */

#include "G4Event.hh"
#include "G4VProcess.hh"
#include "G4Run.hh"
#include "G4Step.hh"
#include "G4TPCMCParticleUserAction.hh"

G4TPCMCParticleUserAction::G4TPCMCParticleUserAction(EventContainer *pEventContainer, const InputParameters *pInputParameters) :
    m_pEventContainer(pEventContainer),
    m_pInputParameters(pInputParameters),
    m_keepEMShowerDaughters(pInputParameters->GetKeepEMShowerDaughters()),
    m_energyCut(pInputParameters->GetHitEnergyThreshold() * CLHEP::GeV),
    m_currentPdgCode(0),
    m_currentTrackId(std::numeric_limits<int>::max()),
    m_trackIdOffset(0)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

G4TPCMCParticleUserAction::~G4TPCMCParticleUserAction()
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void G4TPCMCParticleUserAction::BeginOfRunAction(const G4Run * /*pG4Run*/)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void G4TPCMCParticleUserAction::EndOfRunAction(const G4Run * /*pG4Run*/)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void G4TPCMCParticleUserAction::BeginOfEventAction(const G4Event * /*pG4Event*/)
{
    m_currentMCParticleInfo.Clear();
    m_mcParticleList.Clear();
    m_currentTrackId = std::numeric_limits<int>::max();
    m_parentIdMap.clear();
    m_currentPdgCode = 0;

    if (m_pInputParameters->GetUseGenieInput())
    {
        const GenieEvent genieEvent(m_pInputParameters->GetGenieEvents().at(m_pEventContainer->GetEventNumber()));
        const int pdg(genieEvent.GetNeutrinoTrack()->GetPDG());
        const double mass(0.0);

        // ATTN : Neutrino track id set to 0, mass set to 0.0, time 0.f, parent set to -1.  Setting id to 0 means all primaries generated by
        //        particle gun will appear as daughters.
        MCParticle *pMCParticle = new MCParticle(0, pdg, -1, mass);

        const TLorentzVector vtxTLV(genieEvent.GetVertexX(), genieEvent.GetVertexY(), genieEvent.GetVertexZ(), 0.f);
        const double energy(genieEvent.GetNeutrinoTrack()->GetEnergy());
        const TVector3 direction(genieEvent.GetNeutrinoTrack()->GetDirectionX(), genieEvent.GetNeutrinoTrack()->GetDirectionY(), genieEvent.GetNeutrinoTrack()->GetDirectionZ());
        // ATTN : Assume zero neutrino mass
        const TLorentzVector momentumTLV(direction.Unit() * energy, energy);

        pMCParticle->AddTrajectoryPoint(vtxTLV, momentumTLV);
        m_mcParticleList.Add(pMCParticle, -1);
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void G4TPCMCParticleUserAction::EndOfEventAction(const G4Event * /*pG4Event*/)
{
    for (auto iter : m_mcParticleList.m_mcParticles)
    {
        const int trackId(iter.first);
        MCParticle *pMCParticle(iter.second);

        const int parentTrackId(pMCParticle->GetParent());
        // ATTN : Note the neutrino MCParticle does not pass this cut, but the daughters do and the links set
        if (parentTrackId < 0 || parentTrackId == std::numeric_limits<int>::max())
            continue;

        IntMCParticleMap::iterator parentIter(m_mcParticleList.m_mcParticles.find(parentTrackId));
        if (parentIter != m_mcParticleList.m_mcParticles.end())
        {
             MCParticle *pParentParticle((*parentIter).second);
             pParentParticle->AddDaughter(trackId);
        }
    }

    m_mcParticleList.m_parentIdMap = m_parentIdMap;
    m_pEventContainer->SetCurrentMCParticleList(m_mcParticleList);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

int G4TPCMCParticleUserAction::GetParent(const int trackId) const
{
    int parentId(std::numeric_limits<int>::max());

    IntIntMap::const_iterator iter = m_parentIdMap.find(trackId);

    while (iter != m_parentIdMap.end())
    {
        parentId = (*iter).second;
        iter = m_parentIdMap.find(parentId);
    }

     return parentId;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

bool G4TPCMCParticleUserAction::KnownParticle(const int trackId) const
{
    return m_mcParticleList.KnownParticle(trackId);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void G4TPCMCParticleUserAction::PreUserTrackingAction(const G4Track *pG4Track)
{
    G4ParticleDefinition *pG4ParticleDefinition = pG4Track->GetDefinition();
    int pdgCode(pG4ParticleDefinition->GetPDGEncoding());
    int trackID(pG4Track->GetTrackID() + m_trackIdOffset);
    int parentTrackId(pG4Track->GetParentID() + m_trackIdOffset);

    m_currentPdgCode = pdgCode;

    const G4DynamicParticle *pG4DynamicParticle(pG4Track->GetDynamicParticle());
    const G4PrimaryParticle *pG4PrimaryParticle(pG4DynamicParticle->GetPrimaryParticle());

    std::string processName("");

    if (pG4PrimaryParticle)
    {
        processName = "primary";
        parentTrackId = 0;
    }
    else
    {
        processName = pG4Track->GetCreatorProcess()->GetProcessName();
        // ATTN : Scrap EM shower daughters
        if (!m_keepEMShowerDaughters
                && (processName.find("conv")           != std::string::npos
                || processName.find("LowEnConversion") != std::string::npos
                || processName.find("Pair")            != std::string::npos
                || processName.find("compt")           != std::string::npos
                || processName.find("Compt")           != std::string::npos
                || processName.find("Brem")            != std::string::npos
                || processName.find("phot")            != std::string::npos
                || processName.find("Photo")           != std::string::npos
                || processName.find("Ion")             != std::string::npos
                || processName.find("annihil")         != std::string::npos))
        {
            m_currentMCParticleInfo.Clear();
            m_parentIdMap[trackID] = parentTrackId;
            return;
        }

        // ATTN : Energy Cut
        double energy(pG4Track->GetKineticEnergy());
        if (energy < m_energyCut)
        {
            m_currentMCParticleInfo.Clear();
            m_parentIdMap[trackID] = parentTrackId;
        }

        if (!this->KnownParticle(parentTrackId))
        {
            m_parentIdMap[trackID] = parentTrackId;
            int pid(this->GetParent(parentTrackId));

            if (!this->KnownParticle(pid))
            {
                std::cout << "Unknown parent" << std::endl;
            }
            else
            {
                parentTrackId = pid;
            }
        }
    }

    double mass(pG4DynamicParticle->GetMass()/CLHEP::GeV);
    m_currentMCParticleInfo.Clear();
    m_currentMCParticleInfo.m_pMCParticle = new MCParticle(trackID, pdgCode, parentTrackId, mass);
    m_currentMCParticleInfo.m_generatedParticleIndex = 0;
    m_currentMCParticleInfo.m_keep = true;

    m_mcParticleList.Add(m_currentMCParticleInfo.m_pMCParticle, pG4Track->GetTrackID());
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void G4TPCMCParticleUserAction::PostUserTrackingAction(const G4Track * /*pG4Track*/)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void G4TPCMCParticleUserAction::UserSteppingAction(const G4Step *pG4Step)
{
    if (!m_currentMCParticleInfo.m_pMCParticle)
        return;

    const G4StepPoint *pPreStepPoint(pG4Step->GetPreStepPoint());

    const G4ThreeVector position(pPreStepPoint->GetPosition());
    const double time(pPreStepPoint->GetGlobalTime());
    const TLorentzVector fourPos(position.x() / CLHEP::mm, position.y() / CLHEP::mm, position.z() / CLHEP::mm, time / CLHEP::ns);

    const G4ThreeVector momentum(pPreStepPoint->GetMomentum());
    const double energy(pPreStepPoint->GetTotalEnergy());
    const TLorentzVector fourMom(momentum.x() / CLHEP::GeV, momentum.y() / CLHEP::GeV, momentum.z() / CLHEP::GeV, energy / CLHEP::GeV);

    m_currentMCParticleInfo.m_pMCParticle->AddTrajectoryPoint(fourPos, fourMom);
}
