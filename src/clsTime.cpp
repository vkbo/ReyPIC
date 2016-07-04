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
