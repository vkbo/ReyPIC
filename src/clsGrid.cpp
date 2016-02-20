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

    error_t   errVal;
    vstring_t vsGridVars = {"x1","x2","x3"};

    errVal += simInput->ReadVariable(INPUT_GRID, 0, "grid",     &m_NGrid,    INVAR_VINT);
    errVal += simInput->ReadVariable(INPUT_GRID, 0, "xmin",     &m_XMin,     INVAR_VDOUBLE);
    errVal += simInput->ReadVariable(INPUT_GRID, 0, "xmax",     &m_XMax,     INVAR_VDOUBLE);

    errVal += simInput->ReadVariable(INPUT_GRID, 0, "gridres",  &m_GridRes,  INVAR_VSTRING);
    errVal += simInput->ReadVariable(INPUT_GRID, 0, "gridfunc", &m_GridFunc, INVAR_VSTRING);

    // Set up grid resolution vectors
    int nErr = 0;
    for(int iDim=0; iDim<3; iDim++) {

        if(m_GridRes[iDim] == "fixed") {

        } else
        if(m_GridRes[iDim] == "func") {

            Math mFunc;

            if(!mFunc.setVariables(vsGridVars)) nErr++;
            if(!mFunc.setEquation(m_GridFunc[iDim])) nErr++;

            double dDelta = (m_XMax[iDim]-m_XMin[iDim])/(m_NGrid[iDim]-1);
            cout << "  Resolution: " << dDelta << endl;

            vdouble_t vdEval = {0.0, 0.0, 0.0};
            double    dValue;
            for(int iStep=0; iStep<m_NGrid[iDim]; iStep++) {
                vdEval[iDim] = (iStep*dDelta+m_XMin[iDim]);
                mFunc.Eval(vdEval,&dValue);
                cout << "  Eval: " << (iStep*dDelta+m_XMin[iDim]) << " Value: " << dValue << endl;
            }
        }
    }

    if(nErr > 0) {
        return ERR_SETUP;
    }

    return ERR_NONE;
}

// ********************************************************************************************** //

// End Class Grid
