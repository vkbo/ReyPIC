/**
 * ReyPIC – Grid Header
 */

#ifndef CLASS_GRID
#define CLASS_GRID

#include "config.hpp"

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

    int Setup();

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
    int       m_MPISize     =  0;              // Number of nodes
    int       m_MPIRank     = -1;              // Node number
    bool      m_isMaster    = false;           // True if this node is master

    double    m_GridMin[3]  = {0.0, 0.0, 0.0}; // [gridmin]    Lower bound of grid axes
    double    m_GridMax[3]  = {1.0, 1.0, 1.0}; // [gridmax]    Input Upper bound of grid axes
    int       m_GridSize[3] = {1,   1,   1};   // [grid]       Number of grid cells

    vstring_t m_GridType    = {"","",""};      // [resolution] Grid resolution type
    double    m_DeltaMin[3] = {1.0, 1.0, 1.0}; // [gridmin]    Smallest allowed cell size
    double    m_DeltaMax[3] = {1.0, 1.0, 1.0}; // [gridmax]    Largest allowed cell size
    vstring_t m_GridFunc    = {"","",""};      // [gridfuncX]  Function for grid cell sixe

}; // End Class Grid

} // End NameSpace

#endif
