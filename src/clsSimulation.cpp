/**
 *  ReyPIC – Simulation Class Source
 * ==================================
 *  This class wraps the entire simulation.
 * 
 *  Sequence:
 *  1. Read input file.
 *  2. Setup simulation. This creates the grid and the particle arrays.
 *  3. Read restart information. Only if restart is specified. Exits if restart files do not match
 *     the setup from previous stage.
 *  4. Main simulation loop.
 */

#include "clsSimulation.hpp"

using namespace std;
using namespace reypic;

// ********************************************************************************************** //

/**
 * Simulation Class Constructor
 */

Simulation::Simulation() {

    // Default Values
    m_RunMode = RUN_MODE_FULL;

    return;
}

// ********************************************************************************************** //

/**
 *  Set Input File
 * ================
 *  Related to the switch -i.
 *  Sets the InputFile variable.
 */

bool Simulation::setInputFile(char* cFile) {

    m_InputFile = cFile;

    return true;
}

// ********************************************************************************************** //

/**
 *  Set Run Mode
 * ==============
 *  Related to switch -t.
 *  In test mode the simulation is set up, but exits before the solver starts.
 */

bool Simulation::setRunMode(int iRunMode) {

    switch(iRunMode) {
        case RUN_MODE_TEST:
            m_RunMode = RUN_MODE_TEST;
            return true;
            break;
        case RUN_MODE_FULL:
            m_RunMode = RUN_MODE_FULL;
            return true;
            break;
    }

    return false;
}

// ********************************************************************************************** //

/**
 *  Read Input File
 * =================
 *  Creates SimConfig and loads the input file
 */

int Simulation::ReadInput() {
    
    bool isValid    = SimConfig.ReadFile(m_InputFile);
    bool isComplete = SimConfig.SplitSections();
    
    if(!(isValid && isComplete)) {
        return ERR_INPUT;
    }
    
    m_NumSpecies = SimConfig.getNumSpecies();
    
    return ERR_NONE;
}

// ********************************************************************************************** //

/**
 *  Setup
 * =======
 *  Sets up simulation
 */

int Simulation::Setup() {
    
    int nErr = 0;
    
    // Parallelisation
    nErr += SimConfig.ReadVariable(INPUT_SIM, 0, "nodes",   &m_Nodes,    INVAR_INT);
    nErr += SimConfig.ReadVariable(INPUT_SIM, 0, "threads", &m_Threads,  INVAR_INT);

    // Physics
    nErr += SimConfig.ReadVariable(INPUT_SIM, 0, "n0",      &m_N0,       INVAR_DOUBLE);
    
    // Time
    nErr += SimConfig.ReadVariable(INPUT_SIM, 0, "dt",      &m_TimeStep, INVAR_DOUBLE);
    nErr += SimConfig.ReadVariable(INPUT_SIM, 0, "tmin",    &m_TMin,     INVAR_DOUBLE);
    nErr += SimConfig.ReadVariable(INPUT_SIM, 0, "tmax",    &m_TMax,     INVAR_DOUBLE);
    
    cout << "  Errors:   " << nErr << endl;
    cout << "  Nodes:    " << m_Nodes << endl;
    cout << "  Threads:  " << m_Threads << endl;
    cout << "  N0:       " << m_N0 << endl;
    cout << "  TimeStep: " << m_TimeStep << endl;
    cout << "  TMin:     " << m_TMin << endl;
    cout << "  TMax:     " << m_TMax << endl;
    cout << endl;
    
    return ERR_NONE;
}

// ********************************************************************************************** //

// End Class Input
