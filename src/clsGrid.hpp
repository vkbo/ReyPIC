/**
 * ReyPIC – Grid Header
 */

#ifndef CLASS_GRID
#define CLASS_GRID

#include "config.hpp"

#include "clsInput.hpp"
#include "clsMath.hpp"

namespace reypic {

class Grid {

public:

   /**
    * Constructor/Destructor
    */

    Grid();
    ~Grid() {};

   /**
    * Methods
    */

    int Setup(Input*);

   /**
    * Properties
    */

private:

   /**
    * Member Variables
    */

    // General
    double    m_Grid[];                        // The grid

    // Parallelisation
    int       m_MPISize  =  0;              // Number of nodes
    int       m_MPIRank  = -1;              // Node number
    bool      m_isMaster = false;           // True if this node is master

    vint_t    m_NGrid    = {1,   1,   1};   // [grid]       Number of grid cells
    vdouble_t m_XMin     = {0.0, 0.0, 0.0}; // [gridmin]    Lower bound of grid axes
    vdouble_t m_XMax     = {1.0, 1.0, 1.0}; // [gridmax]    Input Upper bound of grid axes

    vstring_t m_GridRes  = {"","",""};      // [resolution] Grid resolution type
    vdouble_t m_DeltaMin = {1.0, 1.0, 1.0}; // [gridmin]    Smallest allowed cell size
    vdouble_t m_DeltaMax = {1.0, 1.0, 1.0}; // [gridmax]    Largest allowed cell size
    vstring_t m_GridFunc = {"","",""};      // [gridfuncX]  Function for grid cell sixe

}; // End Class Grid

} // End NameSpace

#endif
