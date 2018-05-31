#include "C_GET_STR_CHAR.h"

C_GET_STR_CHAR::C_GET_STR_CHAR(MIS *mis, int &P_PC)
{
     if (mis != nullptr && P_PC != -1) {
        misInst = mis;
        V_PC = &P_PC;
    }
}

C_Instruction * C_GET_STR_CHAR::F_Clone(MIS *mis, int &P_PC){
    C_GET_STR_CHAR * get = new C_GET_STR_CHAR(mis, P_PC);
    return get;
}

/** Checks all syntax errors and calls ReportError if theres an error**/
void C_GET_STR_CHAR::F_CheckSyntax(){
    /** Loading instruction string vector into params**/
    params  = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];
    /**Checking Regex for the desired format**/
    regex getstrchar ("(GET_STR_CHAR)\\s(\\$[A-Za-z][_A-Za-z0-9]{0,255})\\,((\\$[A-Za-z][_A-Za-z0-9]{0,255})|([0-9]{1,3}))\\,((\\$[A-Za-z][_A-Za-z0-9]{0,255}))");
    if (!regex_match((*params)[0], getstrchar)){
        V_ErrorMessage = "In function GET_STR_CHAR: Syntax Error.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /** Number of parameters passed is not 3 **/
    if (params->size() != 5){
        V_ErrorMessage = "In function GET_STR_CHAR: GET_STR_CHAR takes exactly 3 parameters";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /** STRING variable does not exist **/
    if (!misInst->F_StringVExists((*params)[2])){ //1-2
        V_ErrorMessage = "In function GET_STR_CHAR: This string does not exist.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /** Index is a variable that does not exist in NUMERIC map **/
    if ((*params)[3][0] == '$' && !misInst->F_NumericVExists((*params)[3])){
        V_ErrorMessage = "In function GET_STR_CHAR: The index you entered is not valid.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /** CHAR variable is a variable that does not exist in CHAR map **/
    if (!misInst->F_CharVExists((*params)[4])){
        V_ErrorMessage = "In function GET_STR_CHAR: CHAR variable does not exist.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /** Index exceeds the size of the string or is a negative number **/
    if ( ((*params)[3][0] == '$' && (misInst->F_GetNumericV((*params)[3]) > misInst->F_GetStringSize((*params)[2])|| misInst->F_GetNumericV((*params)[3]) < 0)) ||
        ((*params)[3][0] != '$' && (stod((*params)[3]) > misInst->F_GetStringSize((*params)[2]) || stod((*params)[3]) < 0)) ){
        V_ErrorMessage = "In function GET_STR_CHAR: The index you entered is not valid";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
}
/** Gets the char and alters the char variable **/
void C_GET_STR_CHAR::F_Execute(){
    /** Index is a variable **/
    if ((*params)[3][0] == '$'){
        misInst->F_SetCharV( (*params)[4],   misInst->F_GetStringChar((*params)[2],misInst->F_GetNumericV((*params)[3])) );//3-4,1-2,2-3
        return;
    }
    /** Index is an integer **/
    else{
    misInst->F_SetCharV( (*params)[4],   misInst->F_GetStringChar((*params)[2], stoi((*params)[3])));
    }
}



C_GET_STR_CHAR::~C_GET_STR_CHAR(){}

#ifdef GETGUARD
    extern "C" C_Instruction * F_GetInstruction() {return new C_GET_STR_CHAR(nullptr);}
#endif
