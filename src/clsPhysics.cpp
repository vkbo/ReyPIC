/**
 *  ReyPIC – Physics Class Source
 * ===============================
 */

#include "clsPhysics.hpp"

using namespace std;
using namespace reypic;

// ****************************************************************************************************************** //

/**
 *  Class Constructor
 * ===================
 */

Physics::Physics() {

    // Read MPI setup
    MPI_Comm_size(MPI_COMM_WORLD, &m_MPISize);
    MPI_Comm_rank(MPI_COMM_WORLD, &m_MPIRank);
    m_isMaster = (m_MPIRank == 0);

}

// ****************************************************************************************************************** //
//                                                 Main Class Methods                                                 //
// ****************************************************************************************************************** //

/**
 *  Method :: Setup
 * =================
 */

error_t Physics::Setup(Input_t* simInput, Grid_t* simGrid) {

    error_t errVal = ERR_NONE;

    errVal = simParticles.Setup(simInput, simGrid);
    if(errVal != ERR_NONE) return errVal;

    return ERR_NONE;
}

// ****************************************************************************************************************** //

// End Class Physics
