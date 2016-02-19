/**
 *  ReyPIC – Math Source
 * ======================
 *  Loosely based on: http://www.codeproject.com/Articles/345888/How-to-write-a-simple-interpreter-in-JavaScript
 */

#include "clsMath.hpp"

using namespace std;
using namespace reypic;

// ********************************************************************************************** //

/**
 *  Class Constructor
 * ===================
 */

Math::Math() {

}

// ********************************************************************************************** //
//                                      Setters and Getters                                       //
// ********************************************************************************************** //

/**
 *  Set the Equation
 * ==================
 */

void Math::setVariables(vstring_t vsVariable) {

    m_WVariable = vsVariable;

    return;
}

// ********************************************************************************************** //

/**
 *  Set the Equation
 * ==================
 */

bool Math::setEquation(string_t sEquation) {

    // Append a space to make sure last character is evaluated
    m_Equation = sEquation + " ";

    bool okLexer  = eqLexer();
    if(!okLexer) return false;

    bool okParser = eqParser();
    if(!okParser) return false;

    m_Parsed = true;
    return true;
}

// ********************************************************************************************** //
//                                       Main Class Methods                                       //
// ********************************************************************************************** //

/**
 *  Evaluate the Parsed Function
 * ==============================
 *  Takes vector of variables and vector of values as input
 *  Using Reverse Polish notation
 *  https://en.wikipedia.org/wiki/Reverse_Polish_notation
 */

bool Math::Eval(vdouble_t vdValues, double* pReturn) {

    vdouble_t vdStack;
    double    dValue;

    if(!m_Parsed) {
        printf("  Math Eval Error: No valid equation to evaluate\n");
        return false;
    }

    if(m_WVariable.size() != vdValues.size()) {
        printf("  Math Eval Error: Values vector must be the same length as variables vector\n");
        return false;
    }

    for(auto tItem : m_ParseTree) {

        switch(tItem.type) {

            case MP_NUMBER:
                vdStack.push_back(tItem.value);
                break;

            case MP_VARIABLE:
                dValue = 0.0;
                if(evalVariable(tItem.content, &vdValues, &dValue)) {
                    vdStack.push_back(dValue);
                } else {
                    printf("  Math Eval Error: Unknown variable %s\n",tItem.content.c_str());
                    return false;
                }
                break;

            case MP_CONST:
                dValue = 0.0;
                if(evalConstant(tItem.content, &dValue)) {
                    vdStack.push_back(dValue);
                } else {
                    printf("  Math Eval Error: Unknown constant %s\n",tItem.content.c_str());
                    return false;
                }
                break;

            case MP_FUNC:
                dValue = 0.0;
                if(evalFunction(tItem.content, &vdStack, &dValue)) {
                    vdStack.push_back(dValue);
                } else {
                    printf("  Math Eval Error: Unknown function %s\n",tItem.content.c_str());
                    return false;
                }
                break;

            case MP_LOGICAL:
                dValue = 0.0;
                if(evalLogical(tItem.content, &vdStack, &dValue)) {
                    vdStack.push_back(dValue);
                } else {
                    printf("  Math Eval Error: Unknown logic operator %s\n",tItem.content.c_str());
                    return false;
                }
                break;

            case MP_MATH:
                dValue = 0.0;
                if(evalMath(tItem.content, &vdStack, &dValue)) {
                    vdStack.push_back(dValue);
                } else {
                    printf("  Math Eval Error: Unknown operator %s\n",tItem.content.c_str());
                    return false;
                }
                break;
        }

        cout << "  Stack: ";
        for(auto dValue : vdStack) {
            cout << dValue << " ";
        }
        cout << "| Current: " << tItem.content << endl;
    }
    cout << endl;

    *pReturn = vdStack.front();

    return true;
}

// ********************************************************************************************** //
//                                        Member Functions                                        //
// ********************************************************************************************** //

/**
 *  The Equation Lexer
 * ====================
 */

bool Math::eqLexer() {

    int           idCurr;
    int           idPrev  = MT_NONE;
    char          cPrev   = '#';
    string_t      sBuffer = "";
    vector<token> vTokens;

    for(char cCurr : m_Equation) {

        // Get specific type
        idCurr = MT_NONE;
        if(isdigit(cCurr)) idCurr = MT_NUMBER;
        if(isalpha(cCurr)) idCurr = MT_WORD;
        if(ispunct(cCurr)) idCurr = MT_OPERATOR;

        // Numbers following characters are part of words
        if(idCurr == MT_NUMBER && idPrev == MT_WORD) idCurr = MT_WORD;
        // '.' is always part of a number
        if(cCurr == '.') idCurr = MT_NUMBER;
        // 'd' or 'e' following a number denotes exponent
        if((cCurr == 'd' || cCurr == 'e') && idPrev == MT_NUMBER) {
            idCurr = MT_NUMBER;
        }
        // '-' after an 'e' or 'd' that is a number, is also a part of a number
        if(cCurr == '-' && (cPrev == 'd' || cPrev == 'e') && idPrev == MT_NUMBER) {
            idCurr = MT_NUMBER;
        }
        // Check if operator is actually a separataor
        if(cCurr == '(' || cCurr == ')' || cCurr == ',') {
            idCurr = MT_SEPARATOR;
        }
        // Check if unary minus
        if( cCurr == '-' &&
            !(idPrev == MT_NUMBER || idPrev == MT_WORD || (idPrev == MT_NONE && cPrev != '#')) ) {
            cCurr = '_';
        }

        // If a new type was encountered, push the previous onto the lexer
        if(idCurr != idPrev || idPrev == MT_SEPARATOR) {
            if(idPrev != MT_NONE) {
                vTokens.push_back(token({.type=idPrev, .content=sBuffer, .value=0.0}));
            }
            sBuffer = "";
        }
        sBuffer += cCurr;

        // Set previous values for next loop
        idPrev = idCurr;
        cPrev  = cCurr;
    }

    // Clean up lexer and check for invalid entries
    idPrev = MP_NONE;
    for(auto tItem : vTokens) {

        int    idType = MP_NONE;
        double dValue = 0.0;

        switch(tItem.type) {
            case MT_OPERATOR:
                idType = validOperator(&tItem.content);
                dValue = 0.0;
                break;
            case MT_NUMBER:
                idType = validNumber(&tItem.content, &tItem.value);
                dValue = tItem.value;
                break;
            case MT_WORD:
                idType = validWord(&tItem.content);
                dValue = 0.0;
                break;
            case MT_SEPARATOR:
                idType = validSeparator(&tItem.content);
                dValue = 0.0;
                break;
        }

        if( idType == MP_INVALID || (idType == idPrev && !(
            idType == MP_LBRACK || idType == MP_RBRACK ))) {
            printf("  Math Error: Unknown entry '%s'\n", tItem.content.c_str());
            return false;
        } else {
            m_Tokens.push_back(token({.type=idType, .content=tItem.content, .value=dValue}));
        }

        idPrev = idType;
    }

    // Add end token
    m_Tokens.push_back(token({.type=MP_END, .content="end", .value=0.0}));

    // Echo lexer for debug
    // cout << endl;
    // for(auto tItem : m_Tokens) {
    //     cout << "  Type " << tItem.type << " : Content " << tItem.content << " : Value " << tItem.value << endl;
    // }
    // cout << endl;

    return true;
}

// ********************************************************************************************** //

/**
 *  The Equation Parser
 * =====================
 *  Using the Shunting-yard algorithm
 *  https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 */

bool Math::eqParser() {

    vector<token> vtOutput;
    vector<token> vtStack;

    for(auto tItem : m_Tokens) {

        int  itemPrec   = 0;
        int  itemAssoc  = 0;
        int  stackPrec  = 0;
        int  stackAssoc = 0;
        int  iErase     = 0;
        bool isClosed   = false;

        switch(tItem.type) {

            case MP_NUMBER:
                vtOutput.push_back(tItem);
                break;

            case MP_VARIABLE:
                vtOutput.push_back(tItem);
                break;

            case MP_CONST:
                vtOutput.push_back(tItem);
                break;

            case MP_FUNC:
                vtStack.insert(vtStack.begin(), tItem);
                break;

            case MP_LOGICAL:
                iErase = 0;

                precedenceLogical(tItem.content,&itemPrec,&itemAssoc);
                for(auto tStack : vtStack) {
                    precedenceLogical(tStack.content,&stackPrec,&stackAssoc);
                    if( tStack.type == MP_MATH &&
                        ( (itemAssoc == ASSOC_L && itemPrec <= stackPrec) ||
                          (itemAssoc == ASSOC_R && itemPrec <  stackPrec) ) ) {
                        vtOutput.push_back(tStack);
                        iErase++;
                    } else {
                        break;
                    }
                }

                if(iErase > 0) {
                    vtStack.erase(vtStack.begin(),vtStack.begin()+iErase);
                }
                vtStack.insert(vtStack.begin(), tItem);

                break;

            case MP_MATH:
                iErase = 0;

                precedenceMath(tItem.content,&itemPrec,&itemAssoc);
                for(auto tStack : vtStack) {
                    precedenceMath(tStack.content,&stackPrec,&stackAssoc);
                    if( tStack.type == MP_MATH &&
                        ( (itemAssoc == ASSOC_L && itemPrec <= stackPrec) ||
                          (itemAssoc == ASSOC_R && itemPrec <  stackPrec) ) ) {
                        vtOutput.push_back(tStack);
                        iErase++;
                    } else {
                        break;
                    }
                }

                if(iErase > 0) {
                    vtStack.erase(vtStack.begin(),vtStack.begin()+iErase);
                }
                vtStack.insert(vtStack.begin(), tItem);

                break;

            case MP_LBRACK:
                vtStack.insert(vtStack.begin(), tItem);
                break;

            case MP_RBRACK:
                iErase   = 0;
                isClosed = false;

                for(auto tStack : vtStack) {
                    if(tStack.type != MP_LBRACK) {
                        vtOutput.push_back(tStack);
                        iErase++;
                    } else {
                        isClosed = true;
                        break;
                    }
                }

                if(iErase > 0) {
                    vtStack.erase(vtStack.begin(),vtStack.begin()+iErase);
                }

                // Check if brackets were closed
                if(isClosed) {
                    vtStack.erase(vtStack.begin());
                } else {
                    printf("  Math Error: Paranthesis mismatch\n");
                    return false;
                }

                // Check if the next token on stack is a function
                if(vtStack.front().type == MP_FUNC) {
                    vtOutput.push_back(vtStack.front());
                    vtStack.erase(vtStack.begin());
                }

                break;

            case MP_COMMA:
                iErase   = 0;
                isClosed = false;

                for(auto tStack : vtStack) {
                    if(tStack.type != MP_LBRACK) {
                        vtOutput.push_back(tStack);
                        iErase++;
                    } else {
                        isClosed = true;
                        break;
                    }
                }

                if(iErase > 0) {
                    vtStack.erase(vtStack.begin(),vtStack.begin()+iErase);
                }

                break;

            case MP_END:
                iErase = 0;

                if( vtStack.front().type == MP_LBRACK ||
                    vtStack.front().type == MP_RBRACK ) {
                   printf("  Math Error: Paranthesis mismatch\n");
                   return false;
                }

                for(auto tStack : vtStack) {
                    vtOutput.push_back(tStack);
                    iErase++;
                }
                if(iErase > 0) {
                    vtStack.erase(vtStack.begin(),vtStack.begin()+iErase);
                }

                vtOutput.push_back(tItem);
                m_ParseTree = vtOutput;

                // cout << "  Output: ";
                // for(auto tTemp : vtOutput) {
                //     cout << tTemp.content << " ";
                // }
                // cout << "| Stack: ";
                // for(auto tTemp : vtStack) {
                //     cout << tTemp.content << " ";
                // }
                // cout << "| Current: " << tItem.content;
                // cout << endl;

                return true;
                break;
        }

        // cout << "  Output: ";
        // for(auto tTemp : vtOutput) {
        //     cout << tTemp.content << " ";
        // }
        // cout << "| Stack: ";
        // for(auto tTemp : vtStack) {
        //     cout << tTemp.content << " ";
        // }
        // cout << "| Current: " << tItem.content;
        // cout << endl;
    }

    return false;
}

// ********************************************************************************************** //

/**
 *  Function :: validOperator
 * ===========================
 *  Checks if string is a valid operator, and returns its type
 */

int Math::validOperator(string_t* pVar) {

    for(string_t sItem : m_OMath) {
        if(sItem == *pVar) {
            return MP_MATH;
        }
    }

    for(string_t sItem : m_OLogical) {
        if(sItem == *pVar) {
            return MP_LOGICAL;
        }
    }

    return MP_INVALID;
}

// ********************************************************************************************** //

/**
 *  Function :: validWord
 * =======================
 *  Checks if string is a valid word, and returns its type
 */

int Math::validWord(string_t* pVar) {

    for(string_t sItem : m_WVariable) {
        if(sItem == *pVar) {
            return MP_VARIABLE;
        }
    }

    for(string_t sItem : m_WFunc) {
        if(sItem == *pVar) {
            return MP_FUNC;
        }
    }

    for(string_t sItem : m_WConst) {
        if(sItem == *pVar) {
            return MP_CONST;
        }
    }

    return MP_INVALID;
}

// ********************************************************************************************** //

/**
 *  Function :: validNumber
 * =========================
 *  Checks if string is a valid number, and returns its type
 */

int Math::validNumber(string_t* pVar, double* pValue) {

    try {
        *pValue = stof(*pVar);
        return MP_NUMBER;
    } catch(...) {
        *pValue = 0.0;
        return MP_INVALID;
    }
}

// ********************************************************************************************** //

/**
 *  Function :: validSeparator
 * ============================
 *  Checks if string is a valid separataor, and returns its type
 */

int Math::validSeparator(string_t* pVar) {

    if(*pVar == "(") {
        return MP_LBRACK;
    }

    if(*pVar == ")") {
        return MP_RBRACK;
    }

    if(*pVar == ",") {
        return MP_COMMA;
    }

    return MP_INVALID;
}

// ********************************************************************************************** //

/**
 *  Function :: precedenceLogical
 * ===============================
 *  Returns precedence and associativity of operator
 */

void Math::precedenceLogical(string_t sOperator, int* pPrecedence, int* pAssoc) {

    if(sOperator == "&&") {
        *pPrecedence = 3;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == "||") {
        *pPrecedence = 2;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == "==") {
        *pPrecedence = 9;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == "<") {
        *pPrecedence = 9;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == ">") {
        *pPrecedence = 9;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == ">=") {
        *pPrecedence = 9;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == "<=") {
        *pPrecedence = 9;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == "!=") {
        *pPrecedence = 9;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == "<>") {
        *pPrecedence = 9;
        *pAssoc = ASSOC_L;
    }

    return;
}

// ********************************************************************************************** //

/**
 *  Function :: precedenceMath
 * ============================
 *  Returns precedence and associativity of operator
 */

void Math::precedenceMath(string_t sOperator, int* pPrecedence, int* pAssoc) {

    if(sOperator == "^") {
        *pPrecedence = 5;
        *pAssoc = ASSOC_R;
    } else
    if(sOperator == "_") {
        *pPrecedence = 4;
        *pAssoc = ASSOC_R;
    } else
    if(sOperator == "*") {
        *pPrecedence = 3;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == "/") {
        *pPrecedence = 3;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == "+") {
        *pPrecedence = 2;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == "-") {
        *pPrecedence = 2;
        *pAssoc = ASSOC_L;
    }

    return;
}

// ********************************************************************************************** //

/**
 *  Function :: evalVariable
 * ==========================
 *  Evaluate input variable set by setVariables()
 */

bool Math::evalVariable(string_t sVariable, vdouble_t* pValues, double* pReturn) {

    int iPos = 0;

    for(auto sItem : m_WVariable) {
        if(sItem == sVariable) {
            *pReturn = pValues->at(iPos);
            return true;
        }
        iPos++;
    }

    return false;
}

// ********************************************************************************************** //

/**
 *  Function :: evalConstant
 * ==========================
 *  Evaluate constant
 */

bool Math::evalConstant(string_t sVariable, double* pReturn) {

    if(sVariable == "pi") {
        *pReturn = M_PI;
        return true;
    }

    return false;
}

// ********************************************************************************************** //

/**
 *  Function :: evalFunction
 * ==========================
 *  Evaluate math function
 */

bool Math::evalFunction(string_t sVariable, vdouble_t* pStack, double* pReturn) {

    if(pStack->size() < 1) return false;

    bool isValid = false;

    if(sVariable == "sin") {
        *pReturn = sin(pStack->back());
        pStack->pop_back();
        isValid = true;
    } else
    if(sVariable == "cos") {
        *pReturn = cos(pStack->back());
        pStack->pop_back();
        isValid = true;
    } else
    if(sVariable == "tan") {
        *pReturn = tan(pStack->back());
        pStack->pop_back();
        isValid = true;
    } else
    if(sVariable == "exp") {
        *pReturn = exp(pStack->back());
        pStack->pop_back();
        isValid = true;
    } else
    if(sVariable == "log") {
        *pReturn = log(pStack->back());
        pStack->pop_back();
        isValid = true;
    } else
    if(sVariable == "mod") {

        if(pStack->size() < 2) return false;

        double dValL = pStack->back(); pStack->pop_back();
        double dValR = pStack->back(); pStack->pop_back();

        if(dValL == floor(dValL) && dValR == floor(dValR)) {
            *pReturn = (int)floor(dValL)%(int)floor(dValR);
            isValid = true;
        } else {
            isValid = false;
        }
    } else
    if(sVariable == "if") {

        if(pStack->size() < 3) return false;

        double dFalse = pStack->back(); pStack->pop_back();
        double dTrue  = pStack->back(); pStack->pop_back();
        double dBool  = pStack->back(); pStack->pop_back();

        if(dBool == EVAL_TRUE) {
            *pReturn = dTrue;
        } else {
            *pReturn = dFalse;
        }

        isValid = true;
    }

    return isValid;
}

// ********************************************************************************************** //

/**
 *  Function :: evalLogical
 * =========================
 *  Evaluate logic operator
 */

bool Math::evalLogical(string_t sVariable, vdouble_t* pStack, double* pReturn) {

    if(pStack->size() < 2) {
        return false;
    }

    bool   isValid = false;
    double dValR   = pStack->back(); pStack->pop_back();
    double dValL   = pStack->back(); pStack->pop_back();

    if(sVariable == "&&") {
        if(dValL && dValR) {
            *pReturn = EVAL_TRUE;
        } else {
            *pReturn = EVAL_FALSE;
        }
        isValid = true;
    } else
    if(sVariable == "||") {
        if(dValL || dValR) {
            *pReturn = EVAL_TRUE;
        } else {
            *pReturn = EVAL_FALSE;
        }
        isValid = true;
    } else
    if(sVariable == "==") {
        if(dValL == dValR) {
            *pReturn = EVAL_TRUE;
        } else {
            *pReturn = EVAL_FALSE;
        }
        isValid = true;
    } else
    if(sVariable == "<") {
        if(dValL < dValR) {
            *pReturn = EVAL_TRUE;
        } else {
            *pReturn = EVAL_FALSE;
        }
        isValid = true;
    } else
    if(sVariable == ">") {
        if(dValL > dValR) {
            *pReturn = EVAL_TRUE;
        } else {
            *pReturn = EVAL_FALSE;
        }
        isValid = true;
    } else
    if(sVariable == ">=") {
        if(dValL >= dValR) {
            *pReturn = EVAL_TRUE;
        } else {
            *pReturn = EVAL_FALSE;
        }
        isValid = true;
    } else
    if(sVariable == "<=") {
        if(dValL <= dValR) {
            *pReturn = EVAL_TRUE;
        } else {
            *pReturn = EVAL_FALSE;
        }
        isValid = true;
    } else
    if(sVariable == "!=" || sVariable == "<>") {
        if(dValL != dValR) {
            *pReturn = EVAL_TRUE;
        } else {
            *pReturn = EVAL_FALSE;
        }
        isValid = true;
    }

    return isValid;
}

// ********************************************************************************************** //

/**
 *  Function :: evalMath
 * ======================
 *  Evaluate math operator
 */

bool Math::evalMath(string_t sVariable, vdouble_t* pStack, double* pReturn) {

    bool isValid = false;

    if(sVariable == "_") {
        if(pStack->size() < 1) return false;
        double dVal  = pStack->back(); pStack->pop_back();
        *pReturn     = -dVal;
        isValid      = true;
    } else
    if(sVariable == "+") {
        if(pStack->size() < 2) return false;
        double dValR = pStack->back(); pStack->pop_back();
        double dValL = pStack->back(); pStack->pop_back();
        *pReturn     = dValL + dValR;
        isValid      = true;
    } else
    if(sVariable == "-") {
        if(pStack->size() < 2) return false;
        double dValR = pStack->back(); pStack->pop_back();
        double dValL = pStack->back(); pStack->pop_back();
        *pReturn     = dValL - dValR;
        isValid      = true;
    } else
    if(sVariable == "*") {
        if(pStack->size() < 2) return false;
        double dValR = pStack->back(); pStack->pop_back();
        double dValL = pStack->back(); pStack->pop_back();
        *pReturn     = dValL * dValR;
        isValid      = true;
    } else
    if(sVariable == "/") {
        if(pStack->size() < 2) return false;
        double dValR = pStack->back(); pStack->pop_back();
        double dValL = pStack->back(); pStack->pop_back();
        *pReturn     = dValL / dValR;
        isValid      = true;
    } else
    if(sVariable == "^") {
        if(pStack->size() < 2) return false;
        double dValR = pStack->back(); pStack->pop_back();
        double dValL = pStack->back(); pStack->pop_back();
        *pReturn     = pow(dValL,dValR);
        isValid      = true;
    }

    return isValid;
}

// ********************************************************************************************** //

// End Class Math
