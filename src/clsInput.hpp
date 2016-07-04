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

    int32_t getNumSpecies();

   /**
    * Methods
    */

    error_t ReadFile(char*);
    error_t ReadVariable(value_t, index_t, string_t, void*, value_t);

private:

   /**
    * Member Variables
    */

    // Parallelisation
    int32_t   m_MPISize     =  0;    // Number of nodes
    int32_t   m_MPIRank     = -1;    // Node number
    bool      m_isMaster    = false; // True if this node is master

    // Buffers
    string_t  m_Config;              // Config section
    string_t  m_Simulation;          // Simulation section
    string_t  m_Grid;                // Grid section
    string_t  m_EMF;                 // EMF section
    vstring_t m_Species;             // Vector of species sections

   /**
    * Member Functions
    */

    vstring_t strExplode(const string_t&);
    string_t  stripQuotes(const string_t&);

};

} // End NameSpace

#endif
