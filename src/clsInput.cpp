/**
 * ReyPIC – Input Source
 */

#include "clsInput.hpp"

using namespace std;
using namespace reypic;

/**
 *  Input Class Constructor
 * =========================
 */

Input::Input() {
    
    
}

/**
 *  Method :: ReadFile
 * ====================
 *  Reads the input file and strips comments and line endings.
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

    cout << m_Buffer << endl;
    
    return true;
}
