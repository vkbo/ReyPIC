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

    errVal += simInput->ReadVariable(INPUT_GRID, 0, "grid",    &m_NGrid,    INVAR_VINT);
    errVal += simInput->ReadVariable(INPUT_GRID, 0, "xmin",    &m_XMin,     INVAR_VDOUBLE);
    errVal += simInput->ReadVariable(INPUT_GRID, 0, "xmax",    &m_XMax,     INVAR_VDOUBLE);

    errVal += simInput->ReadVariable(INPUT_GRID, 0, "gridres",  &m_GridRes,  INVAR_VSTRING);

    vstring_t vsGridFunc = {"","",""};
    errVal += simInput->ReadVariable(INPUT_GRID, 0, "gridfunc", &vsGridFunc, INVAR_VSTRING);

    if(m_isMaster) {
        for(auto dVal : m_NGrid) {
            cout << "  NGrid: " << dVal << endl;
        }
        for(auto dVal : m_XMin) {
            cout << "  XMin:  " << dVal << endl;
        }
        for(auto dVal : m_XMax) {
            cout << "  XMax:  " << dVal << endl;
        }
        for(auto dVal : m_GridRes) {
            cout << "  Res:   " << dVal << endl;
        }
        for(auto dVal : vsGridFunc) {
            cout << "  Func:  " << dVal << endl;
        }
    }

    vstring_t vsVariables = {"x1","x2","x3"};
    vdouble_t vdValues    = {0.1, 0.2, 0.3};
    double    dEval;

    m_GridFunc[0].setVariables(vsVariables);
    m_GridFunc[0].setEquation(vsGridFunc[0]);
    m_GridFunc[0].Eval(vdValues, &dEval);

    cout << "  Eval: " << dEval << endl << endl;

    return ERR_NONE;
}

// ********************************************************************************************** //

// End Class Grid
