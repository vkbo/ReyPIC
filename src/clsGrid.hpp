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

    double aDeltaMin[3];
    double aDeltaMax[3];
    double aGridMin[3];
    double aGridMax[3];
    int    aGridSize[3];
    double aGrid[];

    /**
     *  Methods
     */


}; // End Class Grid

} // End NameSpace
