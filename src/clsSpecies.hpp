/**
 * ReyPIC – Species Header
 */

#ifndef CLASS_SPECIES
#define CLASS_SPECIES

#include "config.hpp"
#include "functions.hpp"

#include "clsInput.hpp"
#include "clsMath.hpp"

typedef reypic::Input Input_t;

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

    int Setup(Input_t*);

   /**
    * Properties
    */

    double X[];   // Particle position
    double V[];   // Particle velocity
    double W[];   // Particle weight
    int    Tag[]; // Particle tag

private:

   /**
    * Member Variables
    */

    // Parallelisation
    int      m_MPISize    =  0;              // Number of nodes
    int      m_MPIRank    = -1;              // Node number
    bool     m_isMaster   = false;           // True if this node is master

    string_t m_Name       = "";              // Species name
    int      m_Number     = -1;              // Species number

    double   m_Charge     = 0;               // Species charge
    double   m_Mass       = 1;               // Species mass
    vint_t   m_PerCell    = {1, 1, 1};       // Particles per cell

    double   m_Thermal[3] = {0.0, 0.0, 0.0}; // Thermal distribution
    double   m_Fluid[3]   = {0.0, 0.0, 0.0}; // Fluid momentum

};

} // End NameSpace

#endif
