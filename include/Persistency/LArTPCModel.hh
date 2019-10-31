/**
 *  @file   include/LArTPCModel.hh
 *
 *  @brief  Header file for the LArTPCModel class.
 *
 *  $Log: $
 */

#ifndef LARTPC_MODEL_H
#define LARTPC_MODEL_H 1

enum HitType {U_VIEW, V_VIEW, W_VIEW, 3D};

/**
 *  @brief LArTPCModel class
 */
class LArTPCModel
{
public:
    /**
     *  @brief  Constructor
     *
     *  @param  pInputParameters input parameters
     */
    LArTPCModel(const InputParameters *pInputParameters);

    /**
     *  @brief  Save the 2D hit positions made by propagating the geant hits through a LArTPC model
     *
     *  @param  cellListVector cell information to save
     *  @param  mcParticleListVector mc particle information to save
     */
    void SaveLArTPCModelOutput(const CellListVector &cellListVector, const MCParticleListVector &mcParticleListVector);

private:
    /**
     *  @brief  ProtoHit class
     */
    class ProtoHit
    {
    public:
        /**
         *  @brief Default constructor
         */
        ProtoHit();

        float      m_x;                            ///< Drift position
        float      m_z;                            ///< Wire number
        float      m_energy;                       ///< Energy
        HitType    m_hitType;                      ///< Hit type
        int        m_id;                           ///< Hit id
        int        m_mcId;                         ///< Track id of MC particle depositing most energy
    };

    typedef std::vector<ProtoHit*> ProtoHitVector;
    typedef std::map<int, ProtoHitVector> IntProtoHitVectorMap;

    /**
     *  @brief  Downsample hits
     *
     *  @param  protoHitVector vector of protoHits
     */
    void DownsampleHits(ProtoHitVector &protoHitVector);

    /**
     *  @brief  Search and return hits to merge
     *
     *  @param  protoHitVector vector of protoHits
     *  @param  pProtoHit1 merge candidate one
     *  @param  pProtoHit2 merge candidate two
     *
     *  @return is a merge is present
     */
    bool IdentifyMerge(ProtoHitVector &protoHitVector, ProtoHit *&pProtoHit1, ProtoHit *&pProtoHit2);

    /**
     *  @brief  Convert the YZ position to a U
     *
     *  @param  y position
     *  @param  z position
     *
     *  @return the u position
     */
    float YZtoU(const float y, const float z);

    /**
     *  @brief  Convert the YZ position to a V
     *
     *  @param  y position
     *  @param  z position
     *
     *  @return the v position
     */
    float YZtoV(const float y, const float z);

    /**
     *  @brief  Convert the YZ position to a V
     *
     *  @param  y position
     *  @param  z position
     *
     *  @return the w position
     */
    float YZtoW(const float y, const float z);

    /**
     *  @brief  Sort ProtoHits by position
     *
     *  @param  pProtoHit1 first hit
     *  @param  pProtoHit2 second hit
     *
     *  @return is pProtoHit1 sorted above pProtoHit2
     */
    bool SortProtoHits(const ProtoHit *pProtoHit1, const ProtoHit *pProtoHit2);

    const InputParameters *m_pInputParameters; ///< Input parameters
};

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int EventContainer::GetEventNumber() const
{
   return m_eventNumber;
}

#endif // #ifndef LARTPC_MODEL_H
