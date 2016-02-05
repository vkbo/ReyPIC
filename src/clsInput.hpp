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
    
    // Getters
    int getNumSpecies();
    
    // Methods
    bool ReadFile(char*);
    bool SplitSections();

    private:

    // Member Variables
    std::string              m_Buffer;
    std::string              m_Simulation;
    std::string              m_Grid;
    std::string              m_EMF;
    std::vector<std::string> m_Species;

};

} // End NameSpace

#endif
