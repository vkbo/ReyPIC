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

error_t Physics::Setup(Input_t* simInput) {

    error_t errVal = ERR_NONE;

    if(m_isMaster) {
        printf("\n");
        printf("  Species Setup\n");
        printf(" ===============\n");
    }

    for(int32_t indSpecies=0; indSpecies<m_NumSpecies; indSpecies++) {
        simSpecies.push_back(indSpecies);
        error_t errSpecies = simSpecies[indSpecies].Setup(&simInput, &simGrid);
        if(errSpecies != ERR_NONE) return errSpecies;
    }

    if(m_isMaster) {
        printf("\n");
    }

    return ERR_NONE;
}

// ********************************************************************************************** //

// End Class Input
