/**
 * ReyPIC – Simulation Header
 */

#ifndef CLASS_SIMULATION
#define CLASS_SIMULATION

#include "config.hpp"

// Dependent Classes
#include "clsInput.hpp"

namespace reypic {

class Simulation {

public:

   /**
    * Constructor/Destructor
    */

    Simulation();
    ~Simulation();

   /**
    * Setters/Getters
    */

    bool setInputFile(char*);
    bool setRunMode(int);
    
   /**
    * Methods
    */

    int  ReadInput();
    int  Setup();
    void ReadRestart();
    void MainLoop();
    int  AbortExec(int);
    
   /**
    * Properties
    */

    Input SimConfig;

private:

    // Member Variables
    char*  m_InputFile;
    int    m_RunMode    = RUN_MODE_FULL;
    int    m_NumSpecies = 0;
    
    // Parallelisation
    int    m_Nodes   = 1;
    int    m_Threads = 1;
    
    // Physics
    double m_N0   = 1.0;
    
    // Time
    double m_TimeStep = 1.0;
    double m_TMin     = 0.0;
    double m_TMax     = 1.0;

};

} // End NameSpace

#endif
