/**
 * ReyPIC – Species Source
 */

#include "clsSpecies.hpp"

using namespace std;
using namespace reypic;

// ********************************************************************************************** //

/**
 *  Class Constructor
 * ===================
 */

Species::Species(int indNumber) {

    // Read MPI setup
    MPI_Comm_size(MPI_COMM_WORLD, &m_MPISize);
    MPI_Comm_rank(MPI_COMM_WORLD, &m_MPIRank);
    m_isMaster = (m_MPIRank == 0);

    m_Number = indNumber;

    return;
}

// ********************************************************************************************** //
//                                       Main Class Methods                                       //
// ********************************************************************************************** //

/**
 *  Setup
 * =======
 *  Sets up the species
 */

int Species::Setup(Input_t* simInput) {

    error_t errVal;

    errVal = simInput->ReadVariable(INPUT_SPECIES, m_Number, "name", &m_Name, INVAR_STRING);
    if(errVal != ERR_NONE) return errVal;

    errVal = simInput->ReadVariable(INPUT_SPECIES, m_Number, "mass", &m_Mass, INVAR_DOUBLE);
    if(errVal != ERR_NONE) return errVal;

    errVal = simInput->ReadVariable(INPUT_SPECIES, m_Number, "charge", &m_Charge, INVAR_DOUBLE);
    if(errVal != ERR_NONE) return errVal;

    if(m_isMaster) {
        printf("  Species by name '%s' created\n", m_Name.c_str());
    }

    if(floor(m_Charge) != m_Charge) {
        if(m_isMaster) {
            printf("  Species Error: Invalid species charge %.1f\n", m_Charge);
        }
        return ERR_SETUP;
    }

    return ERR_NONE;
}

// ********************************************************************************************** //

// End Class Species
