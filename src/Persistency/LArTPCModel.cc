/**
 *  @file   src/LArTPCModel.cc
 *
 *  @brief  Implementation of the LArTPCModel class.
 *
 *  $Log: $
 */

#include "Persistency/LArTPCModel.hh"

LArTPCModel::LArTPCModel(const InputParameters *pInputParameters) :
    m_pInputParameters(pInputParameters)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void LArTPCModel::SaveLArTPCModelOutput(const CellListVector &cellListVector, const MCParticleListVector &mcParticleListVector)
{
    return;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

float YZtoU(const float y, const float z)
{
    return (z * std::cos(m_pInputParameters->GetWireAngleU()) - y * std::sin(m_pInputParameters->GetWireAngleU()));
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

float YZtoV(const float y, const float z)
{
    return (z * std::cos(m_pInputParameters->GetWireAngleV()) - y * std::sin(m_pInputParameters->GetWireAngleV()));
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

float YZtoW(const float y, const float z)
{
    return (z * std::cos(m_pInputParameters->GetWireAngleW()) - y * std::sin(m_pInputParameters->GetWireAngleW()));
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

void LArTPCModel::DownsampleHits(ProtoHitVector &protoHitVector)
{
    bool isU(protoHitVector.front()->m_hitType == U_VIEW);
    bool isV(protoHitVector.front()->m_hitType == V_VIEW);
    bool isW(protoHitVector.front()->m_hitType == W_VIEW);

    if (!isU && !isV && !isW)
    {
        std::cout << "LArTPCModel::DownsampleHits : Unknown view type encoutered" << std::endl;
        return;
    }

    const float hitPitch(isU ? m_pInputParameters->GetWirePitchU() : isV ? m_pInputParameters->GetWirePitchV() : m_pInputParameters->GetWirePitchW());

    if (hitPitch < std::numeric_limits<float>::epsilon())
    {
        std::cout << "LArTPCModel::DownsampleHits : Unfeasibly pitch requested" << std::endl;
        return;
    }

    IntProtoHitVectorMap intProtoHitVectorMap;

    // ATTN : Begin by ordering wire number
    for (ProtoHit *pProtoHit : protoHitVector)
    {
        if ((isU && pProtoHit->m_hitType != U_VIEW) || (isV && pProtoHit->m_hitType != V_VIEW) || (isW && pProtoHit->m_hitType != W_VIEW))
        {
            std::cout << "LArTPCModel::DownsampleHits : Mixed hit types in downsampling requested" << std::endl;
            return;
        }

        const int wireId(std::floor((pProtoHit->m_z + 0.5f * hitPitch) / hitPitch));
        pProtoHit->m_z = static_cast<float>(wireId) * hitPitch;

        if (intProtoHitVectorMap.find(wireId) != intProtoHitVectorMap.end())
        {
            intProtoHitVectorMap.at(wireId).push_back(pProtoHit);
        }
        else
        {
            ProtoHitVector activeProtoHitVector = {pProtoHit};
            intProtoHitVectorMap.insert(IntProtoHitVectorMap::value_type(wireId, activeProtoHitVector));
        }
    }

    protoHitVector.clear();

    // Merge along x, but only considering hits on same wire at any given time
    for (auto iter : intProtoHitVectorMap)
    {
        ProtoHitVector activeProtoHitVector(iter.second);
        ProtoHit *pProtoHit1(nullptr);
        ProtoHit *pProtoHit2(nullptr);
        std::sort(activeProtoHitVector.begin(), activeProtoHitVector.end(), this->SortProtoHits);

        while (this->IdentifyMerge(activeProtoHitVector, pProtoHit1, pProtoHit2))
        {
            ProtoHit *pMergedHit = new ProtoHit();

            // ATTN : Merged hit on same wire
            pMergedHit->m_z = pProtoHit1->m_z;
            // ATTN : Energy weighted mean drift position
            pMergedHit->m_x = (pProtoHit1->m_x * pProtoHit1->m_energy + pProtoHit2->m_x * pProtoHit2->m_energy)/(pProtoHit1->m_energy + pProtoHit2->m_energy);
            pMergedHit->m_energy = pProtoHit1->m_energy + pProtoHit2->m_energy;
            pMergedHit->m_hitType = pProtoHit1->m_hitType;
            pMergedHit->m_id = (pProtoHit1->m_energy > pProtoHit2->m_energy ? pProtoHit1->m_id : pProtoHit2->m_id);
            pMergedHit->m_mcId = (pProtoHit1->m_energy > pProtoHit2->m_energy ? pProtoHit1->m_mcId : pProtoHit2->m_mcId);

            activeProtoHitVector.erase(std::remove(activeProtoHitVector.begin(), activeProtoHitVector.end(), pProtoHit1));
            activeProtoHitVector.erase(std::remove(activeProtoHitVector.begin(), activeProtoHitVector.end(), pProtoHit2));

            delete pProtoHit1;
            delete pProtoHit2;

            // ATTN: Either 1 hit and just push back, or more than one and insert such that x position ordering is preserved
            if (activeProtoHitVector.size() == 0)
            {
                activeProtoHitVector.push_back(pMergedHit);
            }
            else
            {
                bool addedMergedHit(false);

                for (ProtoHitVector::iterator iter2 = activeProtoHitVector.begin(); iter2 != activeProtoHitVector.end(); iter2++)
                {
                    if ((*iter2)->m_x > pMergedHit->m_x)
                    {
                        addedMergedHit = true;
                        activeProtoHitVector.insert(iter2, pMergedHit);
                        break;
                    }
                }

                if (!addedMergedHit)
                    activeProtoHitVector.push_back(pMergedHit);
            }
        }

        protoHitVector.insert(protoHitVector.end(), activeProtoHitVector.begin(), activeProtoHitVector.end());
        activeProtoHitVector.clear();
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

bool LArTPCModel::IdentifyMerge(ProtoHitVector &protoHitVector, ProtoHit *&pProtoHitA, ProtoHit *&pProtoHitB)
{
    for (unsigned int i = 0; i < protoHitVector.size() - 1; i++)
    {
        ProtoHit *pProtoHit1(protoHitVector.at(i));
        ProtoHit *pProtoHit2(protoHitVector.at(i+1));

        if (std::fabs(pProtoHit1->m_z - pProtoHit2->m_z) < std::numeric_limits<float>::epsilon() && (std::fabs(pProtoHit1->m_x - pProtoHit2->m_x) < m_pInputParameters->GetDriftTimeWidth()))
        {
            pProtoHitA = pProtoHit1;
            pProtoHitB = pProtoHit2;
            return true;
        }
    }

    return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

bool LArTPCModel::SortProtoHits(const ProtoHit *pProtoHit1, const ProtoHit *pProtoHit2)
{
    if (std::fabs(pProtoHit2->m_z - pProtoHit1->m_z) > std::numeric_limits<float>::epsilon())
        return pProtoHit2->m_z > pProtoHit1->m_z;

    if (std::fabs(pProtoHit2->m_x - pProtoHit1->m_x) > std::numeric_limits<float>::epsilon())
        return pProtoHit2->m_x > pProtoHit1->m_x;

    return pProtoHit2->m_energy > pProtoHit1->m_energy;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------------------------------------------------------------------ 

LArTPCModel::ProtoHit::ProtoHit() :
    m_x(std::numeric_limits<float>::max()),
    m_z(std::numeric_limits<float>::max()),
    m_energy(std::numeric_limits<float>::max()),
    m_hitType(3D),
    m_id(std::numeric_limits<int>::max()),
    m_mcId(std::numeric_limits<int>::max())
{
}
