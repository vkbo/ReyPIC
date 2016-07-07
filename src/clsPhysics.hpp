/**
 * ReyPIC – Physics Header
 */

#ifndef CLASS_PHYSICS
#define CLASS_PHYSICS

#include "config.hpp"

#include "clsInput.hpp"
#include "clsGrid.hpp"
#include "clsSpecies.hpp"

typedef reypic::Input                Input_t;
typedef reypic::Grid                 Grid_t;
typedef std::vector<reypic::Species> Species_t;

namespace reypic {

class Physics {

public:

   /**
    * Constructor/Destructor
    */

    Physics();
    ~Physics() {};

   /**
    * Setters/Getters/Checks
    */

   /**
    * Methods
    */

    error_t Setup(Input_t*, Grid_t*);

   /**
    * Properties
    */

    Species_t simSpecies;

private:

   /**
    * Member Variables
    */

    // General

    // Parallelisation
    int32_t  m_MPISize     =  0;              // Number of nodes
    int32_t  m_MPIRank     = -1;              // Node number
    bool     m_isMaster    = false;           // True if this node is master

    int32_t  m_NumSpecies = 0;

};

} // End NameSpace

#endif