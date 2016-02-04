/**
 * ReyPIC – Input Header
 */

#ifndef CLASS_INPUT
#define CLASS_INPUT

#include "config.hpp"
#include <regex>

namespace reypic {

class Input {

    public:

    Input();
    ~Input() {};
    
    // Methods
    bool ReadFile(char*);


    private:

    // Member Variables
    std::string m_Buffer;

};

} // End NameSpace

#endif
