/**
 *  ReyPIC – Particles Class Header
 * =================================
 *  Holds an array of all simulation particle species.
 */

#ifndef CLASS_PARTICLES
#define CLASS_PARTICLES

#include "config.hpp"
#include "functions.hpp"

#include "clsInput.hpp"
#include "clsGrid.hpp"
#include "clsSpecies.hpp"

typedef reypic::Input                Input_t;
typedef reypic::Grid                 Grid_t;
typedef std::vector<reypic::Species> VSpecies_t;

namespace reypic {

class Particles {

public:

   /**
    * Constructor/Destructor
    */

    Particles();
    ~Particles() {};

   /**
    * Methods
    */

    error_t Setup(Input_t*, Grid_t*);
    error_t Create();
    error_t Push();
    error_t Boundary();

   /**
    * Properties
    */

    VSpecies_t simSpecies; // Vector of species objects

private:

   /**
    * Member Functions
    */


   /**
    * Member Variables
    */

    // Parallelisation
    int32_t  m_MPISize    =  0;    // Number of nodes
    int32_t  m_MPIRank    = -1;    // Node number
    bool     m_isMaster   = false; // True if this node is master

    int32_t  m_NumSpecies = 0;     // Number of species

};

} // End NameSpace

#endif

