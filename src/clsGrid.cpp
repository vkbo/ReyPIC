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

    errVal += simInput->ReadVariable(INPUT_GRID, 0, "ngrid",    &m_NGrid,    INVAR_VINT);
    errVal += simInput->ReadVariable(INPUT_GRID, 0, "xmin",     &m_XMin,     INVAR_VDOUBLE);
    errVal += simInput->ReadVariable(INPUT_GRID, 0, "xmax",     &m_XMax,     INVAR_VDOUBLE);

    errVal += simInput->ReadVariable(INPUT_GRID, 0, "gridres",  &m_GridRes,  INVAR_VSTRING);
    errVal += simInput->ReadVariable(INPUT_GRID, 0, "gridmin",  &m_DeltaMin, INVAR_VDOUBLE);
    errVal += simInput->ReadVariable(INPUT_GRID, 0, "gridmax",  &m_DeltaMax, INVAR_VDOUBLE);
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

            double delMin = m_DeltaMin[iDim];
            double delMax = m_DeltaMax[iDim];
            double xMin   = m_XMin[iDim];
            double xMax   = m_XMax[iDim];
            double xSpan  = xMax - xMin;
            int    nGrid  = m_NGrid[iDim];
            int    nMin   = ceil(xSpan/delMin);
            int    nMax   = floor(xSpan/delMax);
            double adjMin = xSpan/nMin;
            double adjMax = xSpan/nMax;

            cout << "  delMin = " << delMin << endl;
            cout << "  delMax = " << delMax << endl;
            cout << "  xMin   = " << xMin << endl;
            cout << "  xMax   = " << xMax << endl;
            cout << "  xSpan  = " << xSpan << endl;
            cout << "  nGrid  = " << nGrid << endl;
            cout << "  nMin   = " << nMin << endl;
            cout << "  nMax   = " << nMax << endl;
            cout << "  adjMin = " << adjMin << endl;
            cout << "  adjMax = " << adjMax << endl;

            if(nGrid < nMax || nGrid > nMin) {
                printf("  Grid Error: Number of grid cells must correspond to maximum and\n");
                printf("              minimum resolution for dimension %d.\n", iDim);
                return ERR_SETUP;
            }



            vdouble_t vdEval = {0.0, 0.0, 0.0};
            double    aEval[nMin+1] = {0.0};

            linspace(xMin, xMax, nMin+1, aEval);

            for(auto dVal : aEval) {
                cout << "  Value: " << dVal << endl;
            }

            // for(int i=0; i<=nMin; i++) {
            //     vdEval[iDim] = i*adjMin+xMin;
            //     mFunc.Eval(vdEval,&aEval[i]);
            //     cout << "  Eval: " << (i*adjMin+xMin) << " Value: " << aEval[i] << endl;
            // }
        }
    }

    if(nErr > 0) {
        return ERR_SETUP;
    }

    return ERR_NONE;
}

// ********************************************************************************************** //

// End Class Grid
