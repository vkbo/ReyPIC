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

    Species(int32_t);
    ~Species() {};

   /**
    * Methods
    */

    int Setup(Input_t*, Grid_t*);

   /**
    * Properties
    */

    double_t X[];   // Particle position
    double_t V[];   // Particle velocity
    double_t W[];   // Particle weight
    index_t  Tag[]; // Particle tag

private:

   /**
    * Member Functions
    */

    bool setupSpeciesProfile();
    bool createParticles();

   /**
    * Member Variables
    */

    // Parallelisation
    int32_t   m_MPISize      =  0;              // Number of nodes
    int32_t   m_MPIRank      = -1;              // Node number
    bool      m_isMaster     = false;           // True if this node is master

    vdouble_t m_GridXMin     = {0.0, 0.0, 0.0}; // Grid lower boundaries
    vdouble_t m_GridXMax     = {0.0, 0.0, 0.0}; // Grid upper boundaries

    string_t  m_Name         = "";              // Species name
    int32_t   m_Number       = -1;              // Species number
    value_t   m_ProfileType  = PROF_UNIFORM;    // Species profile
    Math_t    m_ProfileFunc;                   // Species profile function

    double_t  m_Charge       = 0;               // Species charge
    double_t  m_Mass         = 1;               // Species mass
    vint_t    m_PerCell      = {1, 1, 1};       // Particles per cell

    value_t   m_DistMode     = MOM_THERMAL;     // Initiate particles using thermal or twiss

    double_t  m_Fluid[3]     = {0.0, 0.0, 0.0}; // Fluid momentum
    double_t  m_Thermal[3]   = {0.0, 0.0, 0.0}; // Thermal distribution

    double_t  m_Emittance[3] = {0.0, 0.0, 0.0}; // Initial rms emittance, normalised
    double_t  m_Alpha0[3]    = {0.0, 0.0, 0.0}; // Initial alpha function value
    double_t  m_Beta0[3]     = {0.0, 0.0, 0.0}; // Initial beta function value
    double_t  m_Gamma0[3]    = {0.0, 0.0, 0.0}; // Initial gamma function value

    // Options

};

} // End NameSpace

#endif
