/**
 * ReyPIC – Grid Header
 */

#ifndef CLASS_GRID
#define CLASS_GRID

#include "config.hpp"

namespace reypic {

class Grid {

    public:

    // Constructor & Destructor
    Grid();
    ~Grid() {};

    // Methods
    void Setup();

    private:

    // Member Variables
    double m_DeltaMin[3] = {1.0, 1.0, 1.0}; // Smallest allowed cell size
    double m_DeltaMax[3] = {1.0, 1.0, 1.0}; // Largest allowed cell size
    double m_GridMin[3]  = {0.0, 0.0, 0.0}; // Lower bound of grid axes
    double m_GridMax[3]  = {1.0, 1.0, 1.0}; // Upper bound of grid axes
    int    m_GridSize[3] = {1,   1,   1};   // Number of grid cells
    double m_Grid[];                        // The grid

}; // End Class Grid

} // End NameSpace

#endif
