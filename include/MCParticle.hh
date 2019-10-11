/**
 *  @file   include/MCParticle.cc
 *
 *  @brief  Header file for the MCParticle class.
 *
 *  $Log: $
 */

#ifndef MCPARTICLE_H
#define MCPARTICLE_H 1

#include <map>

#include <TLorentzVector.h>

typedef std::vector<int> IntVector;
typedef std::vector<float> FloatVector;
typedef std::pair<TLorentzVector, TLorentzVector> TrajectoryPoint;
typedef std::vector<TrajectoryPoint> TrajectoryPointVector;
typedef std::vector<int, std::string> TrajectoryProcessVector;

/**
 *  @brief MCParticle class
 */
class MCParticle
{
public:
    /**
    *  @brief  Default constructor
    */
    MCParticle();

    /**
     *  @brief  Constructor
     *
     *  @param  trackId
     *  @param  pdg
     *  @param  parent id
     *  @param  mass
     *  @param  status
     */
    MCParticle(const int trackId, const int pdg, const int parent, const double mass, const int status = 1);

    /**
     *  @brief  Destructor
     */
    ~MCParticle();

    /**
     *  @brief Trajectory class
     */
    class Trajectory
    {
    public:
        /**
         *  @brief  Default constructor
         */
        Trajectory();

	/**
	 *  @brief  Constructor
	 *
	 *  @param  vtxTLV position of particle at the start of the trajectory
	 *  @param  momentumTLV momentum of particle at the start of the trajectory
	 */
        Trajectory(const TLorentzVector &vtxTLV, const TLorentzVector &momentumTLV);

	/**
	 *  @brief  Get the position at a given trajectory point
	 *
	 *  @param  i the trajectory point of interest
	 *
	 *  @return position at the point of interest
	 */
        const TLorentzVector &GetPosition(const int i) const;

	/**
	 *  @brief  Get the momentum at a given trajectory point
	 *
	 *  @param  i the trajectory point of interest
	 *
	 *  @return momentum at the point of interest
	 */
        const TLorentzVector &GetMomentum(const int i) const;

	/**
	 *  @brief  Get the x position at a given trajectory point
	 *
	 *  @param  i the trajectory point of interest
	 *
	 *  @return x position at the point of interest
	 */
        double GetPositionX(const int i) const;

	/**
	 *  @brief  Get the y position at a given trajectory point
	 *
	 *  @param  i the trajectory point of interest
	 *
	 *  @return y position at the point of interest
	 */
	double GetPositionY(const int i) const;

	/**
	 *  @brief  Get the z position at a given trajectory point
	 *
	 *  @param  i the trajectory point of interest
	 *
	 *  @return z position at the point of interest
	 */
	double GetPositionZ(const int i) const;

	/**
	 *  @brief  Get the x momentum component at a given trajectory point
	 *
	 *  @param  i the trajectory point of interest
	 *
	 *  @return x momentum component at the point of interest
	 */
	double GetMomentumX(const int i) const;

	/**
	 *  @brief  Get the y momentum component at a given trajectory point
	 *
	 *  @param  i the trajectory point of interest
	 *
	 *  @return y momentum component at the point of interest
	 */
	double GetMomentumY(const int i) const;

	/**
	 *  @brief  Get the z momentum component at a given trajectory point
	 *
	 *  @param  i the trajectory point of interest
	 *
	 *  @return z momentum component at the point of interest
	 */
	double GetMomentumZ(const int i) const;

	/**
	 *  @brief  Get the energy at a given trajectory point
	 *
	 *  @param  i the trajectory point of interest
	 *
	 *  @return energy at the point of interest
	 */
	double GetEnergy(const int i) const;

	/**
	 *  @brief  Get the number of trajecctory points in total
	 *
	 *  @return The number of trajecctory points
	 */
	int GetNumberOfTrajectoryPoints() const;

	/**
	 *  @brief  Add a trajectory point to the trajectory
	 *
	 *  @param  vtxTLV the position to add
	 *  @param  momentumTLV the momentim to add
	 */
	void AddTrajectoryPoint(const TLorentzVector &vtxTLV, const TLorentzVector &momentumTLV);

    private:
        TrajectoryPointVector m_trajectoryPointVector; ///< Vector of trajectory points
    };

    /**
     *  @brief  Get the MC particle status
     *
     *  @return MC particle status
     */
    int GetStatus() const;

    /**
     *  @brief  Get MC particle geant track id
     *
     *  @return track id
     */
    int GetTrackId() const;

    /**
     *  @brief  Get MC particle PDG code
     *
     *  @return PDG code
     */
    int GetPDGCode() const;

    /**
     *  @brief  Get parent MC particle track id
     *
     *  @return parent track id
     */
    int GetParent() const;

    /**
     *  @brief  Get MC particle mass
     *
     *  @return mass
     */
    double GetMass() const;

    /**
     *  @brief  Add daughter MC particle
     *
     *  @param  trackId of daughter
     */
    void AddDaughter(const int trackId);

    /**
     *  @brief  Get geant track id for a specific daughter MC particle
     *
     *  @param  daughterId the ith daughter of the current MC particle
     *
     *  @return the track id of the ith daughter
     */
    int GetDaughter(const int daughterId) const;

    /**
     *  @brief  Get the number of daughter particles
     *
     *  @return the number of daughter particles
     */
    int GetNumberOfDaughters() const;

    /**
     *  @brief  Get the number of trajectory points for this MC particle
     *
     *  @return the number of trajectory points for this MC particle
     */
    int GetNumberOfTrajectoryPoints() const;

    /**
     *  @brief  Get the position of this MC particle at the ith trajectory point
     *
     *  @param  i the trajetory point index
     *
     *  @return position at the ith trajectory point
     */
    const TLorentzVector &GetPosition(const int i = 0) const;

    /**
     *  @brief  Get the x position of this MC particle at the ith trajectory point
     *
     *  @param  i the trajetory point index
     *
     *  @return x position of this MC particle at the ith trajectory point
     */
    double GetPositionX(const int i = 0) const;

    /**
     *  @brief  Get the y position of this MC particle at the ith trajectory point
     *
     *  @param  i the trajetory point index
     *
     *  @return y position of this MC particle at the ith trajectory point
     */
    double GetPositionY(const int i = 0) const;

    /**
     *  @brief  Get the z position of this MC particle at the ith trajectory point
     *
     *  @param  i the trajetory point index
     *
     *  @return z position of this MC particle at the ith trajectory point
     */
    double GetPositionZ(const int i = 0) const;

    /**
     *  @brief  Get the time of this MC particle at the ith trajectory point
     *
     *  @param  i the trajetory point index
     *
     *  @return time of this MC particle at the ith trajectory point
     */
    double GetTime(const int i = 0) const;

    /**
     *  @brief  Get the position of this MC particle at the end of the trajectory
     *
     *  @return end position
     */
    const TLorentzVector &GetEndPosition() const;

    /**
     *  @brief  Get the x position of this MC particle at the end of the trajectory
     *
     *  @return end x position
     */
    double GetEndPositionX() const;

    /**
     *  @brief  Get the y position of this MC particle at the end of the trajectory
     *
     *  @return end y position
     */
    double GetEndPositionY() const;

    /**
     *  @brief  Get the z position of this MC particle at the end of the trajectory
     *
     *  @return end z position
     */
    double GetEndPositionZ() const;

    /**
     *  @brief  Get the time of this MC particle at the end of the trajectory
     *
     *  @return end time
     */
    double GetEndTime() const;

    /**
     *  @brief  Get the momentum of this MC particle at the ith trajetory point
     *
     *  @param  i the trajetory point index
     *
     *  @return the momentum of this MC particle at the ith trajetory point
     */
    const TLorentzVector &GetMomentum(const int i = 0) const;

    /**
     *  @brief  Get the x momentum component of this MC particle at the ith trajetory point
     *
     *  @param  i the trajetory point index
     *
     *  @return x momentum component of this MC particle at the ith trajetory point
     */
    double GetMomentumX(const int i = 0) const;

    /**
     *  @brief  Get the y momentum component of this MC particle at the ith trajetory point
     *
     *  @param  i the trajetory point index
     *
     *  @return y momentum component of this MC particle at the ith trajetory point
     */
    double GetMomentumY(const int i = 0) const;

    /**
     *  @brief  Get the z momentum component of this MC particle at the ith trajetory point
     *
     *  @param  i the trajetory point index
     *
     *  @return z momentum component of this MC particle at the ith trajetory point
     */
    double GetMomentumZ(const int i = 0) const;

    /**
     *  @brief  Get the energy of this MC particle at the ith trajetory point
     *
     *  @param  i the trajetory point index
     *
     *  @return energy of this MC particle at the ith trajetory point
     */
    double GetEnergy(const int i = 0) const;

    /**
     *  @brief  Get the momentum of this MC particle at the ith trajetory point
     *
     *  @param  i the trajetory point index
     *
     *  @return the momentum of this MC particle at the ith trajetory point
     */
    double GetStepMomentum(const int i = 0) const;

    /**
     *  @brief  Get the momentum of this MC particle at the end of the trajectory
     *
     *  @return end momentum
     */
    const TLorentzVector &GetEndMomentum() const;

    /**
     *  @brief  Get the x momentum component of this MC particle at the end of the trajectory
     *
     *  @return end x momentum
     */
    double GetEndMomentumX() const;

    /**
     *  @brief  Get the y momentum component of this MC particle at the end of the trajectory
     *
     *  @return end y momentum
     */
    double GetEndMomentumY() const;

    /**
     *  @brief  Get the z momentum component of this MC particle at the end of the trajectory
     *
     *  @return end z momentum
     */
    double GetEndMomentumZ() const;

    /**
     *  @brief  Get the energy of this MC particle at the end of the trajectory
     *
     *  @return end energy
     */
    double GetEndEnergy() const;

    /**
     *  @brief  Add a trajectory point to this MC particle
     *
     *  @param  vtxTLV position to add
     *  @param  momentumTLV momentum to add
     */
    void AddTrajectoryPoint(const TLorentzVector &vtxTLV, const TLorentzVector &momentumTLV);

private:
    int         m_status;        ///< MC particle status
    int         m_trackId;       ///< Geant track id
    int         m_pdgCode;       ///< PDG code
    int         m_parent;        ///< Parent track id
    std::string m_process;       ///< Start process
    std::string m_endProcess;    ///< End process
    Trajectory  m_trajectory;    ///< Trajectory of particle
    float       m_mass;          ///< Mass of particle
    IntVector   m_daughters;     ///< Vector of daughter track ids
};

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int MCParticle::GetStatus() const
{
    return m_status;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int MCParticle::GetTrackId() const
{
    return m_trackId;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int MCParticle::GetPDGCode() const
{
    return m_pdgCode;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int MCParticle::GetParent() const
{
    return m_parent;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetMass() const
{
    return m_mass;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline void MCParticle::AddDaughter(const int trackId)
{
    m_daughters.push_back(trackId);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int MCParticle::GetDaughter(const int daughterId) const
{
    if (daughterId < static_cast<int>(m_daughters.size()))
        m_daughters.at(daughterId);

    return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int MCParticle::GetNumberOfDaughters() const
{
    return m_daughters.size();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int MCParticle::GetNumberOfTrajectoryPoints() const
{
    return m_trajectory.GetNumberOfTrajectoryPoints();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline const TLorentzVector &MCParticle::GetPosition(const int i) const
{
    return m_trajectory.GetPosition(i);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetPositionX(const int i) const
{
    return m_trajectory.GetPosition(i).X();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetPositionY(const int i) const
{
    return m_trajectory.GetPosition(i).Y();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetPositionZ(const int i) const
{
    return m_trajectory.GetPosition(i).Z();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetTime(const int i) const
{
    return m_trajectory.GetPosition(i).T();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline const TLorentzVector &MCParticle::GetEndPosition() const
{
    return m_trajectory.GetPosition(m_trajectory.GetNumberOfTrajectoryPoints() - 1);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetEndPositionX() const
{
    return m_trajectory.GetPosition(m_trajectory.GetNumberOfTrajectoryPoints() - 1).X();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetEndPositionY() const
{
    return m_trajectory.GetPosition(m_trajectory.GetNumberOfTrajectoryPoints() - 1).Y();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetEndPositionZ() const
{
    return m_trajectory.GetPosition(m_trajectory.GetNumberOfTrajectoryPoints() - 1).Z();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetEndTime() const
{
    return m_trajectory.GetPosition(m_trajectory.GetNumberOfTrajectoryPoints() - 1).T();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline const TLorentzVector &MCParticle::GetMomentum(const int i) const
{
    return m_trajectory.GetMomentum(i);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetMomentumX(const int i) const
{
    return m_trajectory.GetMomentum(i).Px();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetMomentumY(const int i) const
{
    return m_trajectory.GetMomentum(i).Py();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetMomentumZ(const int i) const
{
    return m_trajectory.GetMomentum(i).Pz();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetEnergy(const int i) const
{
    return m_trajectory.GetMomentum(i).E();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetStepMomentum(const int i) const
{
    return std::sqrt(std::pow(m_trajectory.GetMomentum(i).E(), 2) - std::pow(m_mass, 2));
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline const TLorentzVector &MCParticle::GetEndMomentum() const
{
    return m_trajectory.GetMomentum(m_trajectory.GetNumberOfTrajectoryPoints() - 1);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetEndMomentumX() const
{
    return m_trajectory.GetMomentum(m_trajectory.GetNumberOfTrajectoryPoints() - 1).Px();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetEndMomentumY() const
{
    return m_trajectory.GetMomentum(m_trajectory.GetNumberOfTrajectoryPoints() - 1).Py();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetEndMomentumZ() const
{
    return m_trajectory.GetMomentum(m_trajectory.GetNumberOfTrajectoryPoints() - 1).Pz();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetEndEnergy() const
{
    return m_trajectory.GetMomentum(m_trajectory.GetNumberOfTrajectoryPoints() - 1).E();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline void MCParticle::AddTrajectoryPoint(const TLorentzVector &vtxTLV, const TLorentzVector &momentumTLV)
{
    m_trajectory.AddTrajectoryPoint(vtxTLV, momentumTLV);
    return;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::Trajectory::GetPositionX(const int i) const
{
    return this->GetPosition(i).X();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::Trajectory::GetPositionY(const int i) const
{
    return this->GetPosition(i).Y();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::Trajectory::GetPositionZ(const int i) const
{
    return this->GetPosition(i).Z();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::Trajectory::GetMomentumX(const int i) const
{
    return this->GetMomentum(i).X();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::Trajectory::GetMomentumY(const int i) const
{
    return this->GetMomentum(i).Y();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::Trajectory::GetMomentumZ(const int i) const
{
    return this->GetMomentum(i).Z();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::Trajectory::GetEnergy(const int i) const
{
    return this->GetMomentum(i).E();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int MCParticle::Trajectory::GetNumberOfTrajectoryPoints() const
{
    return m_trajectoryPointVector.size();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------------------------------------------------------------------ 

/**
  *  @brief MCParticleInfo class
  */
class MCParticleInfo
{
public:
    /**
     *  Constructor
     */
    MCParticleInfo();

    void Clear();
    bool HasParticle();
    bool IsPrimary();
    bool KeepParticle();

    MCParticle *m_pMCParticle;
    bool        m_keep;
    int         m_generatedParticleIndex;
};

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline void MCParticleInfo::Clear()
{
    m_pMCParticle = nullptr;
    m_keep = false;
    m_generatedParticleIndex = std::numeric_limits<int>::max();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline bool MCParticleInfo::HasParticle()
{
    return m_pMCParticle;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline bool MCParticleInfo::IsPrimary()
{
    return false; // Fix.
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline bool MCParticleInfo::KeepParticle()
{
    return (this->HasParticle() && m_keep);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------------------------------------------------------------------ 

typedef std::map<int, int> IntIntMap;
typedef std::map<int, MCParticle*> IntMCParticleMap;

/**
 *  @brief MCParticleList class
 */
class MCParticleList
{
public:
    /**
     *  Constructor
     */
    MCParticleList();

    /**
    *  @brief  Add MCParticle to list
    *
    *  @param  pMCParticle to add
    *  @param  geantTrackId track id of particle being added
    */
    void Add(MCParticle *pMCParticle, const int geantTrackId);

    /**
    *  @brief  Wipe all MCParticles from list
    */
    void Clear();

    /**
    *  @brief  Is MCParticle present in list
    *
    *  @param  trackId of target MCParticle
    *
    *  @return bool is MCParticle in list
    */
    bool KnownParticle(const int trackId) const;

    IntMCParticleMap m_mcParticles;          ///< Map of Id to MCParticle (includes offset for each event)
    IntMCParticleMap m_trackIdToMCParticles; ///< Map of geant4 trackId to MCParticle (no offset)
    IntIntMap        m_parentIdMap;          ///< Map of geant4 trackId to parent MCParticle trackId
};

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline void MCParticleList::Add(MCParticle *pMCParticle, const int geantTrackId)
{
    const int trackId(pMCParticle->GetTrackId());

    if (m_mcParticles.find(trackId) != m_mcParticles.end())
        return;

    m_mcParticles.insert(IntMCParticleMap::value_type(trackId, pMCParticle));
    m_trackIdToMCParticles.insert(IntMCParticleMap::value_type(geantTrackId, pMCParticle));
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline void MCParticleList::Clear()
{
    m_mcParticles.clear();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline bool MCParticleList::KnownParticle(const int trackId) const
{
    if (m_mcParticles.find(trackId) != m_mcParticles.end())
        return true;

    return false;
}

#endif // #ifndef MCPARTICLE_H
