/**
 *  ReyPIC – Simulation Class Header
 * ==================================
 *  Holds simulation specific information and handles parallelisation and load distribution
 */

#ifndef CLASS_SIMULATION
#define CLASS_SIMULATION

#include "config.hpp"

#include "clsInput.hpp"

typedef reypic::Input Input_t;

namespace reypic {

class Simulation {

public:

   /**
    * Constructor/Destructor
    */

    Simulation();
    ~Simulation() {};

   /**
    * Setters/Getters/Checks
    */

    bool setRunMode(value_t);

   /**
    * Methods
    */

    error_t Setup(Input_t*);

   /**
    * Properties
    */

private:

   /**
    * Member Variables
    */

    // General
    char*    m_InputFile;
    value_t  m_RunMode    = RUN_MODE_FULL;
    int32_t  m_NumSpecies = 0;

    // Parallelisation
    int32_t  m_MPISize     =  0;              // Number of nodes
    int32_t  m_MPIRank     = -1;              // Node number
    bool     m_isMaster    = false;           // True if this node is master

    int32_t  m_Nodes      =  1;
    int32_t  m_Threads    =  1;

    // Physics
    double_t m_N0         = 1.0;

};

} // End NameSpace

#endif
