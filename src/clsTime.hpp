/**
 * ReyPIC – Time Header
 */

#ifndef CLASS_TIME
#define CLASS_TIME

#include "config.hpp"
#include "functions.hpp"

#include "clsInput.hpp"

typedef reypic::Input Input_t;

namespace reypic {

class Time {

public:

   /**
    * Constructor/Destructor
    */

    Time();
    ~Time() {};

   /**
    * Setters/Getters/Checks
    */

    void     setTime(index_t moveTo);

    index_t  getStep()     {return m_Step;};
    double_t getTime()     {return m_Time;};
    double_t getTimeStep() {return m_TimeStep;};

    bool     atEnd();

   /**
    * Methods
    */

    error_t Setup(Input_t*);
    void    Advance(index_t);

   /**
    * Properties
    */

private:

   /**
    * Member Functions
    */

   /**
    * Member Variables
    */

    // Parallelisation
    int32_t  m_MPISize  =  0;    // Number of nodes
    int32_t  m_MPIRank  = -1;    // Node number
    bool     m_isMaster = false; // True if this node is master

    // Time Steps
    index_t  m_Step     = 0;
    double_t m_Time     = 0.0;
    double_t m_TimeStep = 0.0;
    double_t m_TMin     = 0.0;
    double_t m_TMax     = 0.0;
    index_t  m_NMin     = 0;
    index_t  m_NMax     = 0;

};

} // End NameSpace

#endif
