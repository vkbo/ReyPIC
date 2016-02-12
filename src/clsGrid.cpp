/**
 * ReyPIC – Grid Source
 */

#include "clsGrid.hpp"

using namespace std;
using namespace reypic;

// ********************************************************************************************** //

/**
 *  Class Constructor
 * ===================
 */

Grid::Grid() {

    // Read MPI setup
    MPI_Comm_size(MPI_COMM_WORLD, &m_MPISize);
    MPI_Comm_rank(MPI_COMM_WORLD, &m_MPIRank);
    m_isMaster = (m_MPIRank == 0);

}

// ********************************************************************************************** //

/**
 *  Setup
 * =======
 *  Sets up the grid
 */

int Grid::Setup(Input* simInput) {
    
    error_t errVal;
    
    errVal += simInput->ReadVariable(INPUT_GRID, 0, "grid",   &m_NGrid,   INVAR_VINT);
    errVal += simInput->ReadVariable(INPUT_GRID, 0, "xmin",   &m_XMin,    INVAR_VDOUBLE);
    errVal += simInput->ReadVariable(INPUT_GRID, 0, "xmax",   &m_XMax,    INVAR_VDOUBLE);

    errVal += simInput->ReadVariable(INPUT_GRID, 0, "gridres", &m_GridRes, INVAR_VSTRING);
    
    if(m_isMaster) {
        for(auto dVal : m_NGrid) {
            cout << "NGrid: " << dVal << endl;
        }
        for(auto dVal : m_XMin) {
            cout << "XMin:  " << dVal << endl;
        }
        for(auto dVal : m_XMax) {
            cout << "XMax:  " << dVal << endl;
        }
        for(auto dVal : m_GridRes) {
            cout << "Res:   " << dVal << endl;
        }
    }


    return ERR_NONE;
}

// ********************************************************************************************** //

// End Class Grid
