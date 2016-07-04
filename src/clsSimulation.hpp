/**
 * ReyPIC – Simulation Header
 */

#ifndef CLASS_SIMULATION
#define CLASS_SIMULATION

#include "config.hpp"

#include "clsInput.hpp"
#include "clsTime.hpp"
#include "clsGrid.hpp"
#include "clsSpecies.hpp"

typedef reypic::Input                Input_t;
typedef reypic::Time                 Time_t;
typedef reypic::Grid                 Grid_t;
typedef std::vector<reypic::Species> Species_t;

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

    bool setInputFile(char*);
    bool setRunMode(value_t);

    bool isMaster();

   /**
    * Methods
    */

    error_t ReadInput();    // Read input file
    error_t Setup();
    void    ReadRestart();
    void    MainLoop();
    error_t AbortExec(error_t);
    error_t Finalize(error_t);

   /**
    * Properties
    */

    Input_t   simInput;
    Time_t    simTime;
    Grid_t    simGrid;
    Species_t simSpecies;

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
