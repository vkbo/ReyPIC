/**
 * ReyPIC – Species Header
 */

#ifndef CLASS_SPECIES
#define CLASS_SPECIES

#include "config.hpp"

namespace reypic {

class Species {

public:

   /**
    * Constructor/Destructor
    */

    Species();
    ~Species() {};

   /**
    * Methods
    */

    int Setup();

   /**
    * Properties
    */

    double X[];   // Particle position
    double V[];   // Particle velocity
    double W[];   // Particle weight
    int    Tag[]; // Particle tag

private:

   /**
    * Member Variables
    */

    char*  m_Name;
    double m_Charge = 0; // Species charge
    double m_Mass   = 1; // Species mass

    double m_Thermal[3] = {0.0, 0.0, 0.0}; // Thermal distribution
    double m_Fluid[3]   = {0.0, 0.0, 0.0}; // Fluid momentum

};

} // End NameSpace

#endif
