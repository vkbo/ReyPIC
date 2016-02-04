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

    Simulation();
    ~Simulation() {};

    // Setters
    bool setInputFile(char*);
    bool setRunMode(int);
    
    // Methods
    int  ReadInput();
    void Setup();
    void ReadRestart();
    void MainLoop();
    int  AbortExec(int);
    
    // Properties
    Input SimConfig;

    private:

    // Member Variables
    char* m_InputFile;
    int   m_RunMode;

};

} // End NameSpace

#endif
