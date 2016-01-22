/**
 * ReyPIC – ReyPIC Core Header
 */

#include "config.hpp"

namespace reypic {

class ReyPIC {

    public:

    ReyPIC();
    ~ReyPIC() {};

    // Properties
    char* InputFile;
    int   RunMode;

    // Setters
    bool SetInputFile(char*);
    bool SetRunMode(int);
    
    // Methods
    int ParseArgs(int,char*);
    int AbortExec(int);

};

} // End NameSpace
