/**
 * ReyPIC – Time Source
 */

#include "clsTime.hpp"

using namespace std;
using namespace reypic;

// ********************************************************************************************** //

/**
 *  Class Constructor
 * ===================
 */

Time::Time() {

    // Read MPI setup
    MPI_Comm_size(MPI_COMM_WORLD, &m_MPISize);
    MPI_Comm_rank(MPI_COMM_WORLD, &m_MPIRank);
    m_isMaster = (m_MPIRank == 0);

    return;
}

// ********************************************************************************************** //
//                                      Setters and Getters                                       //
// ********************************************************************************************** //

/**
 *  Set Time
 * ==========
 *  Move simulation to specific time step
 */

void Time::setTime(index_t moveTo) {

    m_Step = moveTo;
    m_Time = m_TMin + moveTo*m_TimeStep;

    return;
}

// ********************************************************************************************** //

/**
 *  Check if simulation is at last time step
 */

bool Time::atEnd() {

    if(m_Time > m_NMax) {
        return true;
    } else {
        return false;
    }
}

// ********************************************************************************************** //
//                                       Main Class Methods                                       //
// ********************************************************************************************** //

/**
 *  Setup
 */

error_t Time::Setup(Input_t* simInput) {

    error_t errVal = ERR_NONE;

    errVal = simInput->ReadVariable(INPUT_SIM, 0, "dt", &m_TimeStep, INVAR_DOUBLE);
    if(errVal != ERR_NONE) return errVal;

    errVal = simInput->ReadVariable(INPUT_SIM, 0, "tmin", &m_TMin, INVAR_DOUBLE);
    if(errVal != ERR_NONE) return errVal;

    errVal = simInput->ReadVariable(INPUT_SIM, 0, "tmax", &m_TMax, INVAR_DOUBLE);
    if(errVal != ERR_NONE) return errVal;

    // Calculate other values
    double_t sumTime = m_TMax - m_TMin;
    index_t  sumSteps = ceil(sumTime/m_TimeStep);

    m_Step = 0;
    m_Time = 0.0;
    m_NMin = 0;
    m_NMax = sumSteps;
    m_TMax = sumSteps*m_TimeStep;

    if(m_isMaster) {
        printf("  Start time:        %.2f\n", m_TMin);
        printf("  End time:          %.2f\n", m_TMax);
        printf("  Time step:         %.4f\n", m_TimeStep);
        printf("  Simulation steps:  %d\n",   (int)m_NMax);
    }

    return ERR_NONE;
}

// ********************************************************************************************** //

/**
 *  Advance simulation one time step
 */

void Time::Advance(index_t nSteps) {

    m_Step += nSteps;
    m_Time += nSteps*m_TimeStep;

    return;
}

// ********************************************************************************************** //
//                                        Member Functions                                        //
// ********************************************************************************************** //

// End Class Time
