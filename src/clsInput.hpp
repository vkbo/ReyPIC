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
    int  ReadVariable(int,int,std::string,void*,int);

    private:

    // Member Variables
    string_t  m_Buffer;
    string_t  m_Simulation;
    string_t  m_Grid;
    string_t  m_EMF;
    vstring_t m_Species;

};

} // End NameSpace

#endif
