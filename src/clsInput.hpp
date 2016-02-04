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

    void ParseFile(char* cFile);

    private:

    std::string m_Buffer;

};

} // End NameSpace

#endif
