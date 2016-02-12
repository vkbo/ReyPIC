/**
 * ReyPIC – Input Source
 */

#include "clsInput.hpp"

using namespace std;
using namespace reypic;

// ********************************************************************************************** //

/**
 *  Class Constructor
 * ===================
 */

Input::Input() {

    // Read MPI setup
    MPI_Comm_size(MPI_COMM_WORLD, &m_MPISize);
    MPI_Comm_rank(MPI_COMM_WORLD, &m_MPIRank);
    m_isMaster = (m_MPIRank == 0);

}

// ********************************************************************************************** //
//                                      Setters and Getters                                       //
// ********************************************************************************************** //

/**
 *  Method :: getNumSpecies
 * =========================
 *  Returns number of species defined in input file
 */

int Input::getNumSpecies() {

    return (int)m_Species.size();
}

// ********************************************************************************************** //
//                                       Main Class Methods                                       //
// ********************************************************************************************** //

/**
 *  Method :: ReadFile
 * ====================
 *  Reads the input file into buffer and strips comments and line endings.
 */

int Input::ReadFile(char* cFile) {

    // Read File into buffer
    ifstream tmpFile(cFile);
    tmpFile.seekg(0, ios::end);
    size_t iSize = tmpFile.tellg();
    string_t tmpBuffer(iSize, ' ');
    tmpFile.seekg(0);
    tmpFile.read(&tmpBuffer[0], iSize);

    // Check for closed quotes
    size_t nQuotes = count(tmpBuffer.begin(),tmpBuffer.end(),'"');
    if(nQuotes%2 == 1) {
        if(m_isMaster) {
            printf("  Input file malformed. Check that all strings have been closed.\n");
        }
        return ERR_INPUTFILE;
    }

    // Check for closed sections
    size_t nSecStart = count(tmpBuffer.begin(),tmpBuffer.end(),'{');
    size_t nSecEnd   = count(tmpBuffer.begin(),tmpBuffer.end(),'}');
    if(nSecStart != nSecEnd) {
        if(m_isMaster) {
            printf("  Input file malformed. Check that all ections have been closed.\n");
        }
        return ERR_INPUTFILE;
    }

    // Strip comments, line endings and redundant spaces
    regex rxComments("#.*?\n");
    regex rxEndLine("\r?\n|\r");
    regex rxSpaces(" +(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)");
    regex rxOther("\t");

    tmpBuffer = regex_replace(tmpBuffer,rxComments,"");
    tmpBuffer = regex_replace(tmpBuffer,rxEndLine,"");
    tmpBuffer = regex_replace(tmpBuffer,rxSpaces,"");
    tmpBuffer = regex_replace(tmpBuffer,rxOther,"");

    // Set class buffer and return
    m_Buffer = tmpBuffer;

    return ERR_NONE;
}

// ********************************************************************************************** //

/**
 *  Method :: SplitSections
 * =========================
 *  Splits the input file buffer into root sections
 */

int Input::SplitSections() {

    int      iLev = 0;
    size_t   nLen;
    string_t sTemp;

    int    iSection   = INPUT_NONE;
    bool   hasConf    = false;
    bool   hasSim     = false;
    bool   hasGrid    = false;
    bool   hasEMF     = false;
    bool   hasSpecies = false;

    for(char& cChar : m_Buffer) {

        sTemp += cChar;

        if(cChar == '{') {
            iLev++;
            if(iLev == 1) {
                if(sTemp.compare("config{") == 0)     iSection = INPUT_CONF;
                if(sTemp.compare("simulation{") == 0) iSection = INPUT_SIM;
                if(sTemp.compare("grid{") == 0)       iSection = INPUT_GRID;
                if(sTemp.compare("emf{") == 0)        iSection = INPUT_EMF;
                if(sTemp.compare("species{") == 0)    iSection = INPUT_SPECIES;
                sTemp = "";
            }
        }

        if(cChar == '}') {
            iLev--;
            if(iLev == 0) {
                nLen  = sTemp.length();
                sTemp = sTemp.substr(0,nLen-1);
                switch(iSection) {
                    case INPUT_CONF:
                        m_Config = sTemp;
                        if(m_isMaster) {
                            printf("  Found config section\n");
                        }
                        hasConf = true;
                        break;
                    case INPUT_SIM:
                        m_Simulation = sTemp;
                        if(m_isMaster) {
                            printf("  Found simulation section\n");
                        }
                        hasSim = true;
                        break;
                    case INPUT_GRID:
                        m_Grid = sTemp;
                        if(m_isMaster) {
                            printf("  Found grid section\n");
                        }
                        hasGrid = true;
                        break;
                    case INPUT_EMF:
                        m_EMF = sTemp;
                        if(m_isMaster) {
                            printf("  Found emf section\n");
                        }
                        hasEMF = true;
                        break;
                    case INPUT_SPECIES:
                        m_Species.push_back(sTemp);
                        if(m_isMaster) {
                            printf("  Found species section (%d)\n", (int)m_Species.size());
                        }
                        hasSpecies = true;
                        break;
                }
                sTemp    = "";
                iSection = INPUT_NONE;
            }
        }
    }

    if(hasConf && hasSim && hasGrid && hasEMF && hasSpecies) {
        if(m_isMaster) {
            printf("\n");
        }
        return ERR_NONE;
    } else {
        return ERR_INPUTFILE;
    }
}

// ********************************************************************************************** //

/**
 *  Method :: ReadFile
 * ====================
 *  Reads the input file into buffer and strips comments and line endings.
 */

int Input::ReadVariable(int iSection, int iIndex, string_t sVar, void *pReturn, int iType) {

    string_t sBuffer, sSection, sTemp, sValue;
    bool     getVal = false;

    // Get correct buffer
    switch(iSection) {
        case INPUT_CONF:
            sBuffer  = m_Config;
            sSection = "config";
            break;
        case INPUT_SIM:
            sBuffer  = m_Simulation;
            sSection = "simulation";
            break;
        case INPUT_GRID:
            sBuffer  = m_Grid;
            sSection = "grid";
            break;
        case INPUT_EMF:
            sBuffer  = m_EMF;
            sSection = "emf";
            break;
        case INPUT_SPECIES:
            sBuffer  = m_Species[iIndex];
            sSection = "species("+to_string(iIndex)+")";
            break;
        case INPUT_NONE:
            return ERR_ANY;
            break;
    }

    // Find variable
    for(char& cChar : sBuffer) {

        sTemp += cChar;

        if(cChar == '=') {
            if(sTemp.compare(sVar+"=") == 0) {
                getVal = true;
                sTemp  = "";
            }
        }

        if(cChar == ';') {
            if(getVal) {
                sValue = sTemp;
            }
            sTemp  = "";
            getVal = false;
        }
    }

    // Check value
    size_t nLen = sValue.length();
    if(nLen < 1) return ERR_ANY;
    sValue = sValue.substr(0,nLen-1);

    if(m_isMaster) {
        cout << "  Value: " << sValue << " (" << nLen << ")" << endl;
    }

    error_t errParse = ERR_NONE;
    switch(iType) {

        case INVAR_INT:
            try {
                *(int*)pReturn = stoi(sValue);
            } catch(...) {
                errParse = ERR_INPUTVAR;
            }
            break;

        case INVAR_DOUBLE:
            try {
                *(double*)pReturn = stof(sValue);
            } catch(...) {
                errParse = ERR_INPUTVAR;
            }
            break;

        case INVAR_STRING:
            if(nLen < 2) {
                errParse = ERR_INPUTVAR;
                break;
            }
            try {
                *(string_t*)pReturn = stripQuotes(sValue);
            } catch(...) {
                errParse = ERR_INPUTVAR;
            }
            break;

        case INVAR_VINT:
            try {
                vstring_t vsValue = strExplode(sValue);
                vint_t    tmpVal(vsValue.size());

                int i = 0;
                for(string_t sElem : vsValue) {
                    tmpVal[i++] = stoi(sElem);
                }
                *(vint_t*)pReturn = tmpVal;
            } catch(...) {
                errParse = ERR_INPUTVAR;
            }
            break;

        case INVAR_VDOUBLE:
            try {
                vstring_t vsValue = strExplode(sValue);
                vdouble_t tmpVal(vsValue.size());

                int i = 0;
                for(string_t sElem : vsValue) {
                    tmpVal[i++] = stof(sElem);
                }
                *(vdouble_t*)pReturn = tmpVal;
            } catch(...) {
                errParse = ERR_INPUTVAR;
            }
            break;

        case INVAR_VSTRING:
            try {
                vstring_t vsValue = strExplode(sValue);
                *(vstring_t*)pReturn = vsValue;
            } catch(...) {
                errParse = ERR_INPUTVAR;
            }
            break;
    }

    if(errParse != ERR_NONE && m_isMaster) {
        printf("  Error reading value %s->%s\n",sSection.c_str(),sVar.c_str());
    }

    return errParse;
}

// ********************************************************************************************** //
//                                        Member Functions                                        //
// ********************************************************************************************** //

/**
 *  Function :: strExplode
 * ========================
 *  Splits a string into a vector of strings by commas outside of quotes
 */

vstring_t Input::strExplode(const string_t& sString) {
    
    vstring_t vsReturn;
    regex     rxCSV(",(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
    
    sregex_token_iterator rxIt(sString.begin(), sString.end(), rxCSV, -1);
    sregex_token_iterator reg_end;
    for(; rxIt != reg_end; ++rxIt) {
        vsReturn.push_back(stripQuotes(rxIt->str()));
    }
    
    return vsReturn;
}

// ********************************************************************************************** //

/**
 *  Function :: stripQuotes
 * =========================
 *  Strips quotes from a string
 */

string_t Input::stripQuotes(const string_t& sString) {
    
    regex    rxQuote("\"");
    string_t sReturn = regex_replace(sString,rxQuote,"");

    return sReturn;
}

// ********************************************************************************************** //

// End Class Input
