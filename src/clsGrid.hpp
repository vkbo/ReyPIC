/**
 * ReyPIC – Grid Header
 */

#include "config.hpp"

namespace reypic {

class Grid {

    public:

    /**
     *  Constructor & Destructor
     */
     
    Grid();
    ~Grid() {};

    /**
     * Properties
     */

    /**
     *  Methods
     */

    void Setup();

// ****************************************************************************************************************** //

    private:

    /**
     * Properties
     */

    double aDeltaMin[3] = {1.0, 1.0, 1.0}; // Smallest allowed cell size
    double aDeltaMax[3] = {1.0, 1.0, 1.0}; // Largest allowed cell size
    double aGridMin[3]  = {0.0, 0.0, 0.0}; // Lower bound of grid axes
    double aGridMax[3]  = {1.0, 1.0, 1.0}; // Upper bound of grid axes
    int    aGridSize[3] = {1,   1,   1};   // Number of grid cells
    double aGrid[];                        // The grid

    /**
     *  Methods
     */


}; // End Class Grid

} // End NameSpace
