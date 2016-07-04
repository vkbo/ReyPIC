/**
 *  ReyPIC – Physics Class Source
 * ===============================
 */

#include "clsPhysics.hpp"

using namespace std;
using namespace reypic;

// ********************************************************************************************** //

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

// ********************************************************************************************** //
//                                      Setters and Getters                                       //
// ********************************************************************************************** //

// ********************************************************************************************** //
//                                       Main Class Methods                                       //
// ********************************************************************************************** //

/**
 *  Physics Setup
 */

error_t Physics::Setup(Input_t* simInput, Grid_t* simGrid) {

    error_t errVal = ERR_NONE;

    if(m_isMaster) {
        printf("  Species Setup\n");
        printf(" ===============\n");
    }

    // Get number of species
    m_NumSpecies = simInput->getNumSpecies();

    for(int32_t indSpecies=0; indSpecies<m_NumSpecies; indSpecies++) {
        simSpecies.push_back(indSpecies);
        errVal = simSpecies[indSpecies].Setup(simInput, simGrid);
        if(errVal != ERR_NONE) {
            return errVal;
        }
    }

    if(m_isMaster) {
        printf("\n");
    }

    return ERR_NONE;
}

// ********************************************************************************************** //

// End Class Input
