/**
 *  @file   include/GenieEvent.cc
 *
 *  @brief  Header file for the GenieEvent class.
 *
 *  $Log: $
 */
#ifndef GENIE_EVENT_H
#define GENIE_EVENT_H 1

#include <list>
#include <vector>

typedef std::vector<std::string> StringVector;

/**
 *  @brief GenieEvent class
 */
class GenieEvent
{
public:
    /**
     *  @brief  Default constructor
     */
    GenieEvent();

    /**
     *  @brief  Copy constructor
     *
     *  @param  rhs the GenieEvent to copy
     */
    GenieEvent(const GenieEvent &rhs);

    /**
     *  @brief  Assignment operator
     *
     *  @param  rhs the GenieEvent to assign
     */
    GenieEvent &operator=(const GenieEvent &rhs);

    /**
     *  @brief  Destructor
     */
    ~GenieEvent();

    /**
     *  @brief  Track class
     */
    class Track
    {
    public:
        /**
         *  @brief  Default Constructor
         */
        Track();

        /**
         *  @brief  Constructor using defined inputs
         *
         *  @param  pdg
         *  @param  energy
         *  @param  directionX
         *  @param  directionY
         *  @param  directionZ
         */
        Track(int pdg, double energy, double directionX, double directionY, double directionZ);

        /**
         *  @brief  Constructor to use for parsing tracker file
         *
         *  @param  tokens
         */
        Track(const StringVector &tokens);

        /**
         *  @brief  Get tracck pdg code
         *
         *  @return m_pdg
         */
        int GetPDG() const;

        /**
         *  @brief  Get track energy
         *
         *  @return m_energy
         */
        double GetEnergy() const;

        /**
         *  @brief  Get track direction along x
         *
         *  @return m_directionX
         */
        double GetDirectionX() const;

        /**
         *  @brief  Get track direction along y
         *
         *  @return m_directionY
         */
        double GetDirectionY() const;

        /**
         *  @brief  Get track direction along z
         *
         *  @return m_directionY
         */
        double GetDirectionZ() const;

    private:
        int      m_pdg;         ///< Track particle pdg code
        double   m_energy;      ///< Particle energy
        double   m_directionX;  ///< Particle direction along x
        double   m_directionY;  ///< Particle direction along y
        double   m_directionZ;  ///< Particle direction along z
    };

    typedef std::list<const Track*> TrackList;

    /**
     *  @brief  Add daughter track to event
     *
     *  @param  track to add
     */
    void AddDaughterTrack(const Track *pTrack);

    /**
     *  @brief  Get daughter track list
     *
     *  @return m_daughterTracks
     */
    TrackList GetDaughterTracks() const;

    /**
     *  @brief  Set neutrino track parameters
     *
     *  @param  pTrack neutrino track
     */
    void SetNeutrinoTrack(const Track *pTrack);

    /**
     *  @brief  Get neutrino track
     *
     *  @return m_neutrinoTrack
     */
    const Track *GetNeutrinoTrack() const;

    /**
     *  @brief  Set neutrino nuance code
     *
     *  @param  nuanceCode
     */
    void SetNuanceCode(const int nuanceCode);

    /**
     *  @brief  Get nuance code
     *
     *  @return m_nuanceCode
     */
    int GetNuanceCode() const;

    /**
     *  @brief  Set neutrino vertex
     *
     *  @param  vertexX
     *  @param  vertexY
     *  @param  vertexZ
     */
    void SetVertex(const double vertexX, const double vertexY, const double vertexZ);

    /**
     *  @brief  Get vertex position x
     *
     *  @return m_vertexX
     */
    double GetVertexX() const;

    /**
     *  @brief  Get vertex position y
     *
     *  @return m_vertexY
     */
    double GetVertexY() const;

    /**
     *  @brief  Get vertex position z
     *
     *  @return m_vertexZ
     */
    double GetVertexZ() const;

private:
    const Track   *m_pNeutrinoTrack;   ///< Neutrino particle track
    TrackList      m_daughterTracks;   ///< Daughter particle tracks
    int            m_nuanceCode;       ///< Neutrino nuance code
    double         m_vertexX;          ///< Neutrino interaction vertex x
    double         m_vertexY;          ///< Neutrino interaction vertex y
    double         m_vertexZ;          ///< Neutrino interaction vertex z
};

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline void GenieEvent::AddDaughterTrack(const Track *pTrack)
{
    m_daughterTracks.push_back(new Track(*pTrack));
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline GenieEvent::TrackList GenieEvent::GetDaughterTracks() const
{
    return m_daughterTracks;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline void GenieEvent::SetNeutrinoTrack(const Track *pTrack)
{
    m_pNeutrinoTrack = new Track(*pTrack);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline const GenieEvent::Track *GenieEvent::GetNeutrinoTrack() const
{
    return m_pNeutrinoTrack;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline void GenieEvent::SetNuanceCode(const int nuanceCode)
{
    m_nuanceCode = nuanceCode;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int GenieEvent::GetNuanceCode() const
{
   return m_nuanceCode;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline void GenieEvent::SetVertex(const double vertexX, const double vertexY, const double vertexZ)
{
    m_vertexX = vertexX;
    m_vertexY = vertexY;
    m_vertexZ = vertexZ;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double GenieEvent::GetVertexX() const
{
    return m_vertexX;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double GenieEvent::GetVertexY() const
{
    return m_vertexY;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double GenieEvent::GetVertexZ() const
{
    return m_vertexZ;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int GenieEvent::Track::GetPDG() const
{
    return m_pdg;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double GenieEvent::Track::GetEnergy() const
{
    return m_energy;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double GenieEvent::Track::GetDirectionX() const
{
    return m_directionX;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double GenieEvent::Track::GetDirectionY() const
{
    return m_directionY;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double GenieEvent::Track::GetDirectionZ() const
{
    return m_directionZ;
}

#endif // #ifndef GENIE_EVENT_H
