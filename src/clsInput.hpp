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
    bool SplitSections();

    private:

    // Member Variables
    std::string              m_Buffer;
    std::string              m_Simulation;
    std::string              m_EMF;
    std::vector<std::string> m_Species;

};

} // End NameSpace

#endif
