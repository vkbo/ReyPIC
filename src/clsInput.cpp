/**
 * ReyPIC – Input Source
 */

#include "clsInput.hpp"

using namespace std;
using namespace reypic;

// ********************************************************************************************** //

/**
 *  Input Class Constructor
 * =========================
 */

Input::Input() {
    
    
}

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

/**
 *  Method :: ReadFile
 * ====================
 *  Reads the input file into buffer and strips comments and line endings.
 */

bool Input::ReadFile(char* cFile) {
    
    // Read File into buffer
    ifstream tmpFile(cFile);
    tmpFile.seekg(0, ios::end);
    size_t iSize = tmpFile.tellg();
    string tmpBuffer(iSize, ' ');
    tmpFile.seekg(0);
    tmpFile.read(&tmpBuffer[0], iSize);
    
    // Check for closed quotes
    size_t nQuotes = count(tmpBuffer.begin(),tmpBuffer.end(),'"');
    if(nQuotes%2 == 1) {
        printf("  Input file malformed. Check that all strings have been closed.\n");
        return false;
    }

    // Check for closed sections
    size_t nSecStart = count(tmpBuffer.begin(),tmpBuffer.end(),'{');
    size_t nSecEnd   = count(tmpBuffer.begin(),tmpBuffer.end(),'}');
    if(nSecStart != nSecEnd) {
        printf("  Input file malformed. Check that all ections have been closed.\n");
        return false;
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
    
    return true;
}

// ********************************************************************************************** //

/**
 *  Method :: SplitSections
 * =========================
 *  Splits the input file buffer into root sections
 */

bool Input::SplitSections() {
    
    int    iLev = 0;
    size_t nLen ;
    string sTemp;

    int    iSection   = INPUT_NONE;
    bool   hasSim     = false;
    bool   hasGrid    = false;
    bool   hasEMF     = false;
    bool   hasSpecies = false;
    
    for(char& cChar : m_Buffer) {

        sTemp += cChar;
        
        if(cChar == '{') {
            iLev++;
            if(iLev == 1) {
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
                    case INPUT_SIM:
                        m_Simulation = sTemp;
                        printf("  Found simulation section\n");
                        hasSim = true;
                        break;
                    case INPUT_GRID:
                        m_Simulation = sTemp;
                        printf("  Found grid section\n");
                        hasGrid = true;
                        break;
                    case INPUT_EMF:
                        m_EMF = sTemp;
                        printf("  Found emf section\n");
                        hasEMF = true;
                        break;
                    case INPUT_SPECIES:
                        m_Species.push_back(sTemp);
                        printf("  Found species section (%d)\n", (int)m_Species.size());
                        hasSpecies = true;
                        break;
                }
                sTemp = "";
            }
        }
    }
    
    if(hasSim && hasGrid && hasEMF && hasSpecies) {
        printf("\n");
        return true;
    } else {
        return false;
    }
}
