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

Species::Species(int32_t indNumber) {

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

int Species::Setup(Input_t* simInput, Grid_t* simGrid) {

    error_t  errVal;
    string_t tmpVal;

    // Species Name
    errVal = simInput->ReadVariable(INPUT_SPECIES, m_Number, "name", &m_Name, INVAR_STRING);
    if(errVal != ERR_NONE) return errVal;
    if(m_Name == "") {
        if(m_isMaster) {
            printf("  Species Error: Invalid species name for species %d\n", m_Number);
        }
        return ERR_SETUP;
    }

    // Species Profile Type
    tmpVal = "uniform";
    errVal = simInput->ReadVariable(INPUT_SPECIES, m_Number, "profile", &tmpVal, INVAR_STRING);
    if(errVal != ERR_NONE) return errVal;
    if(tmpVal == "uniform") {
        m_ProfileType = PROF_UNIFORM;
    } else
    if(tmpVal == "func") {
        m_ProfileType = PROF_FUNC;
    } else {
        if(m_isMaster) {
            printf("  Species Error: Invalid species profile type '%s'\n", tmpVal.c_str());
        }
        return ERR_SETUP;
    }
    tmpVal = "";

    // Species Charge
    errVal = simInput->ReadVariable(INPUT_SPECIES, m_Number, "charge", &m_Charge, INVAR_DOUBLE);
    if(errVal != ERR_NONE) return errVal;
    if(floor(m_Charge) != m_Charge) {
        if(m_isMaster) {
            printf("  Species Error: Invalid species charge %.1f\n", m_Charge);
        }
        return ERR_SETUP;
    }

    // Species Mass
    errVal = simInput->ReadVariable(INPUT_SPECIES, m_Number, "mass", &m_Mass, INVAR_DOUBLE);
    if(errVal != ERR_NONE) return errVal;
    if(m_Mass <= 0.0) {
        if(m_isMaster) {
            printf("  Species Error: Invalid species mass %.2f\n", m_Mass);
        }
        return ERR_SETUP;
    }

    // Particles per cell
    errVal = simInput->ReadVariable(INPUT_SPECIES, m_Number, "percell", &m_PerCell, INVAR_VINT);
    if(errVal != ERR_NONE) return errVal;
    if(m_PerCell[0] < 1 || m_PerCell[1] < 1 || m_PerCell[2] < 1) {
        if(m_isMaster) {
            printf("  Species Error: Must have at least 1 particle per cell\n");
        }
        return ERR_SETUP;
    }

    if(m_isMaster) {
        printf("  Species by name '%s' created\n", m_Name.c_str());
    }

    /**
     *  Momentum Distribution
     */

    // Species Profile Type
    tmpVal = "none";
    errVal = simInput->ReadVariable(INPUT_SPECIES, m_Number, "distmode", &tmpVal, INVAR_STRING);
    if(errVal != ERR_NONE) return errVal;
    if(tmpVal == "none") {
        m_ProfileType = MOM_NONE;
    } else
    if(tmpVal == "thermal") {
        m_ProfileType = MOM_THERMAL;
    } else
    if(tmpVal == "twiss") {
        m_ProfileType = MOM_TWISS;
    } else {
        if(m_isMaster) {
            printf("  Species Error: Invalid species momentum distribution '%s'\n", tmpVal.c_str());
        }
        return ERR_SETUP;
    }
    tmpVal = "";

    // Species Fluid Momentum
    errVal = simInput->ReadVariable(INPUT_SPECIES, m_Number, "fluid", &m_Fluid, INVAR_VDOUBLE);
    if(errVal != ERR_NONE) return errVal;

    // Species Thermal Momentum
    errVal = simInput->ReadVariable(INPUT_SPECIES, m_Number, "thermal", &m_Thermal, INVAR_VDOUBLE);
    if(errVal != ERR_NONE) return errVal;

    // Species Emittance
    errVal = simInput->ReadVariable(INPUT_SPECIES, m_Number, "emittance", &m_Emittance, INVAR_VDOUBLE);
    if(errVal != ERR_NONE) return errVal;

    // Species Twiss Alpha
    errVal = simInput->ReadVariable(INPUT_SPECIES, m_Number, "alpha0", &m_Alpha0, INVAR_VDOUBLE);
    if(errVal != ERR_NONE) return errVal;

    // Species Twiss Beta
    errVal = simInput->ReadVariable(INPUT_SPECIES, m_Number, "beta0", &m_Beta0, INVAR_VDOUBLE);
    if(errVal != ERR_NONE) return errVal;

    // Species Twiss Gamma
    for(int i=0; i<3; i++) {
        if(m_Beta0[i] != 0.0) {
            m_Gamma0[i] = 1 + pow(m_Alpha0[i], 2) / m_Beta0[i];
        }
    }

    // Extract grid info
    m_GridXMin = simGrid->getBoxMin();
    m_GridXMax = simGrid->getBoxMax();

    // Create particles
    if(!setupSpeciesProfile()) {
        if(m_isMaster) {
            printf("  Species Error: Failed to evaulate species profile\n");
        }
        return ERR_SETUP;
    }

    return ERR_NONE;
}

// ********************************************************************************************** //
//                                        Member Functions                                        //
// ********************************************************************************************** //

/**
 *  Setup of Species Profile
 * ==========================
 */

bool Species::setupSpeciesProfile() {

    vstring_t vsGridVars = {"x1","x2","x3","l1","l2","l3","u1","u2","u3"};
    // vdouble_t vdGridVals = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    //
    // for(int i=0; i<3; i++) {
    //     vdGridVals[3+i] = m_GridXMin[i];
    //     vdGridVals[6+i] = m_GridXMax[i];
    // }


    return true;
}

// ********************************************************************************************** //

// End Class Species
