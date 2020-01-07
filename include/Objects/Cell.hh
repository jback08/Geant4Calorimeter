/**
 *  @file   include/Cell.cc
 *
 *  @brief  Header file for the Cell class.
 *
 *  $Log: $
 */

#ifndef CELL_H
#define CELL_H 1

#include <map>
#include <vector>

/**
 *  @brief Cell class
 */
class Cell
{
public:
    /**
     *  @brief  Constructor for cell class
     *
     *  @param  x position of energy deposit
     *  @param  y position of energy deposit
     *  @param  z position of energy deposit
     *  @param  idx cell index
     */
    Cell(const float x, const float y, const float z, const int idx);

    /**
     *  @brief  Destructor
     */
    ~Cell();

    /**
    *  @brief  Get the cell index
    *
    *  @return cell index
    */
    int GetIdx() const;

    /**
    *  @brief  Get the cell x position
    *
    *  @return x position of cell
    */
    float GetX() const;

    /**
    *  @brief  Get the cell y position
    *
    *  @return y position of cell
    */
    float GetY() const;

    /**
    *  @brief  Get the cell z position
    *
    *  @return z position of cell
    */
    float GetZ() const;

    /**
    *  @brief  Return energy in cell
    *
    *  @return energy in cell
    */
    float GetEnergy() const;

    /**
     *  @brief  Add energy deposit to cell
     *
     *  @param  energy to add
     */
    void AddEnergy(const float energy);

private:
    int   m_idx;    ///< Index
    float m_x;      ///< X position
    float m_y;      ///< Y position
    float m_z;      ///< Z position
    float m_energy; ///< Enegry
};

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int Cell::GetIdx() const
{
    return m_idx;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline float Cell::GetX() const
{
    return m_x;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline float Cell::GetY() const
{
    return m_y;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline float Cell::GetZ() const
{
    return m_z;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline float Cell::GetEnergy() const
{
    return m_energy;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline void Cell::AddEnergy(const float energy)
{
    m_energy += energy;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------------------------------------------------------------------ 

typedef std::map<int, Cell*> IntCellMap;
typedef std::pair<int, float> IntFloatPair;
typedef std::vector<IntFloatPair> IntFloatVector;
typedef std::map<int, IntFloatVector> MCComponents;

/**
 *  @brief CellList class
 */
class CellList
{
public:
    /**
     *  Constructor
     */
    CellList();

    /**
     *  Destructor
     */
    ~CellList();

    /**
     *  @brief  Add the energy deposit in a given cell with a givne geant track ID to the cell list
     *
     *  @param  pCell cell energy to add
     *  @param  geantTrackId track ID creating the energy deposit
     */
    void AddEnergyDeposition(Cell *pCell, const int geantTrackId);

    /** 
     *  @brief Clear up all of the cells to avoid memory leak
     */
    void ClearCellList();

    IntCellMap     m_idCellMap;     ///< Cell Id to cell map
    MCComponents   m_mcComponents;  ///< Cell Id to vector of geantIds to energies pairs
};

#endif // #ifndef CELL_H
