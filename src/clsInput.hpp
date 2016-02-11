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

   /**
    * Constructor/Destructor
    */

    Input();
    ~Input() {};

   /**
    * Setters/Getters
    */

    int  getNumSpecies();

   /**
    * Methods
    */

    int  ReadFile(char*);
    int  SplitSections();
    int  ReadVariable(int,int,std::string,void*,int);

private:

   /**
    * Member Variables
    */

    // Parallelisation
    int       m_MPISize     =  0;    // Number of nodes
    int       m_MPIRank     = -1;    // Node number
    bool      m_isMaster    = false; // True if this node is master

    // Buffers
    string_t  m_Buffer;              // Full input file buffer
    string_t  m_Config;              // Config section
    string_t  m_Simulation;          // Simulation section
    string_t  m_Grid;                // Grid section
    string_t  m_EMF;                 // EMF section
    vstring_t m_Species;             // Vector of species sections

};

} // End NameSpace

#endif
