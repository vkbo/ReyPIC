/**
 *  ReyPIC – Particles Class Header
 * =================================
 *  Holds an array of all simulation particle species.
 */

#ifndef CLASS_SPECIES
#define CLASS_SPECIES

#include "config.hpp"
#include "functions.hpp"

#include "clsInput.hpp"
#include "clsSpecies.hpp"

typedef reypic::Input   Input_t;
typedef reypic::Species Species_t

namespace reypic {

class Particles {

public:

   /**
    * Constructor/Destructor
    */

    Particles(int32_t);
    ~Particles() {};

   /**
    * Methods
    */

    error_t Setup(Input_t*);

   /**
    * Properties
    */

    Species_t simSpecies[]; // Array of species objects

private:

   /**
    * Member Functions
    */


   /**
    * Member Variables
    */

    // Parallelisation
    int32_t   m_MPISize      =  0;              // Number of nodes
    int32_t   m_MPIRank      = -1;              // Node number
    bool      m_isMaster     = false;           // True if this node is master


    // Options

};

} // End NameSpace

#endif

