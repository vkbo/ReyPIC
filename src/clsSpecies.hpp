/**
 * ReyPIC – Species Header
 */

#ifndef CLASS_SPECIES
#define CLASS_SPECIES

#include "config.hpp"
#include "functions.hpp"

#include "clsInput.hpp"
#include "clsGrid.hpp"
#include "clsMath.hpp"

typedef reypic::Input Input_t;
typedef reypic::Grid  Grid_t;
typedef reypic::Math  Math_t;

namespace reypic {

class Species {

public:

   /**
    * Constructor/Destructor
    */

    Species(int);
    ~Species() {};

   /**
    * Methods
    */

    int Setup(Input_t*, Grid_t*);

   /**
    * Properties
    */

    double X[];   // Particle position
    double V[];   // Particle velocity
    double W[];   // Particle weight
    int    Tag[]; // Particle tag

private:

   /**
    * Member Functions
    */

    bool setupSpeciesProfile();
    bool createParticles();
    bool validProfile(string_t);

   /**
    * Member Variables
    */

    // Parallelisation
    int       m_MPISize     =  0;              // Number of nodes
    int       m_MPIRank     = -1;              // Node number
    bool      m_isMaster    = false;           // True if this node is master

    vdouble_t m_GridXMin    = {0.0, 0.0, 0.0}; // Grid lower boundaries
    vdouble_t m_GridXMax    = {0.0, 0.0, 0.0}; // Grid upper boundaries

    string_t  m_Name        = "";              // Species name
    int       m_Number      = -1;              // Species number
    string_t  m_ProfileType = "uniform";       // Species profile
    Math_t    m_ProfileFunc;                   // Species profile function

    double    m_Charge      = 0;               // Species charge
    double    m_Mass        = 1;               // Species mass
    vint_t    m_PerCell     = {1, 1, 1};       // Particles per cell

    double    m_Thermal[3]  = {0.0, 0.0, 0.0}; // Thermal distribution
    double    m_Fluid[3]    = {0.0, 0.0, 0.0}; // Fluid momentum

    // Options
    vstring_t m_okProfiles = {"uniform","func"};

};

} // End NameSpace

#endif
