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
    vstring_t vsGridVars = {"n"};

    errVal += simInput->ReadVariable(INPUT_GRID, 0, "ngrid",    &m_NGrid,    INVAR_VINT);
    errVal += simInput->ReadVariable(INPUT_GRID, 0, "xmin",     &m_XMin,     INVAR_VDOUBLE);
    errVal += simInput->ReadVariable(INPUT_GRID, 0, "xmax",     &m_XMax,     INVAR_VDOUBLE);

    errVal += simInput->ReadVariable(INPUT_GRID, 0, "gridres",  &m_GridRes,  INVAR_VSTRING);
    errVal += simInput->ReadVariable(INPUT_GRID, 0, "gridmin",  &m_GridMin,  INVAR_VDOUBLE);
    errVal += simInput->ReadVariable(INPUT_GRID, 0, "gridfunc", &m_GridFunc, INVAR_VSTRING);

    // Set up grid resolution vectors
    int nErr = 0;
    for(int iDim=0; iDim<3; iDim++) {

        vdouble_t vEval;

        double    delMin  = m_GridMin[iDim];
        double    xMin    = m_XMin[iDim];
        double    xMax    = m_XMax[iDim];
        int       nGrid   = m_NGrid[iDim];
        double    xSpan   = xMax - xMin;

        if(m_GridRes[iDim] == "fixed") {
            vEval.assign(nGrid, xSpan/nGrid);
        } else
        if(m_GridRes[iDim] == "func") {

            Math mFunc;

            if(!mFunc.setVariables(vsGridVars)) nErr++;
            if(!mFunc.setEquation(m_GridFunc[iDim])) nErr++;

            if(nErr > 0) {
                return ERR_SETUP;
            }

            // Evaluate function by normalisint it to the span of the grid (xMax - xMin)
            // including an offset determined by delMin

            vdouble_t vdEval = {0.0};
            double    aEval[nGrid] = {0.0};
            double    dScale, valMax, valSum;

            for(int i=0; i<nGrid; i++) {
                vdEval[0] = i+0.5;
                if(!mFunc.Eval(vdEval,&aEval[i])) {
                    return ERR_SETUP;
                }
            }

            // Invert array so that highest value gives highest density, and offset to max value
            valMax = m::max(aEval, nGrid);
            m::scale(aEval, nGrid, -1);
            m::offset(aEval, nGrid, valMax);

            // Normalise to size of domain and offset by minimum grid size
            valSum = m::sum(aEval, nGrid);
            dScale = xSpan - nGrid*delMin;
            m::scale(aEval, nGrid, dScale/valSum);
            m::offset(aEval, nGrid, delMin);

            vEval.assign(aEval, aEval+nGrid);
        }

        m_DeltaX.push_back(vEval);
    }

    if(nErr > 0) {
        return ERR_SETUP;
    }

    return ERR_NONE;
}

// ********************************************************************************************** //

// End Class Grid
