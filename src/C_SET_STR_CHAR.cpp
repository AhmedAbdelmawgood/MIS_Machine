#include "C_SET_STR_CHAR.h"

C_SET_STR_CHAR::C_SET_STR_CHAR(MIS *mis, int &P_PC)
{
    if (mis != nullptr && P_PC != -1) {
        misInst = mis;
        V_PC = &P_PC;
    }
}

C_Instruction * C_SET_STR_CHAR::F_Clone(MIS *mis, int &P_PC){
    C_SET_STR_CHAR * sett = new C_SET_STR_CHAR(mis, P_PC);
    return sett;
}
/** Checks all syntax errors and calls ReportError if theres an error**/
void C_SET_STR_CHAR::F_CheckSyntax(){
    /** Loading instruction string vector into params**/
    params  = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];
    /**Checking Regex for the desired format**/
    regex setstrchar ("(SET_STR_CHAR)\\s(\\$[A-Za-z][_A-Za-z0-9]{0,255})\\,((\\$[A-Za-z][_A-Za-z0-9]{0,255})|([0-9]{1,3}))\\,((\\$[A-Za-z][_A-Za-z0-9]{0,255})|(\\'[_a-zA-Z0-9]\\'))");
    if (!regex_match((*params)[0], setstrchar)){
        V_ErrorMessage = "Syntax Error!";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /** Number of parameters passed is not 3 **/
    if (params->size() != 5){
        V_ErrorMessage = "In function SET_STR_CHAR: SET_STR_CHAR takes exactly 3 parameters";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /** STRING variable does not exist **/
    if (!misInst->F_StringVExists((*params)[2])){
        V_ErrorMessage = "In function SET_STR_CHAR: This string does not exist.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /** Index is a variable that does not exist in NUMERIC map **/
    if ((*params)[3][0] == '$' && !misInst->F_NumericVExists((*params)[3])){
        V_ErrorMessage = "In function SET_STR_CHAR: The index you entered is not valid.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /** 3rd parameter is a variable but not of CHAR type **/
    if ((*params)[4][0] == '$' && !misInst->F_CharVExists((*params)[4])){
        V_ErrorMessage = "In function SET_STR_CHAR: The character passed to SET_STR_CHAR can not be found.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /** Index exceeds the size of the string or is a negative number **/
    if (( (*params)[3][0] == '$' && (misInst->F_GetNumericV((*params)[3]) > misInst->F_GetStringSize((*params)[2]) || misInst->F_GetNumericV((*params)[3]) < 0)) ||
        ( (*params)[3][0] != '$' && (stod((*params)[3]) > misInst->F_GetStringSize((*params)[2]) || stod((*params)[3]) < 0)) ){
        V_ErrorMessage = "In function SET_STR_CHAR: The index you entered is a valid index.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
}

/**Changes the CHAR of a STRING at a specific INDEX**/
void C_SET_STR_CHAR::F_Execute(){
    /** INDEX is a variable **/
    if ((*params)[3][0] == '$'){
        /** CHAR is a variable **/
        if ((*params)[4][0] == '$'){
            misInst->F_SetStringChar((*params)[2], misInst->F_GetNumericV((*params)[3]),misInst->F_GetCharV((*params)[4]));
            return;
        }
        /** CHAR is not a variable **/
        else{
            misInst->F_SetStringChar((*params)[2], misInst->F_GetNumericV((*params)[3]), (*params)[4][1]);
            return;
        }
    }
    /** INDEX is not a variable **/
    else{
        /** CHAR is a variable **/
        if ((*params)[4][0] == '$'){
            misInst->F_SetStringChar((*params)[2], stoi((*params)[3]),misInst->F_GetCharV((*params)[4]));
            return;
        }
        /** CHAR is not a variable **/
        else{
            misInst->F_SetStringChar((*params)[2], stoi((*params)[3]),(*params)[4][1]);
            return;
        }
    }
}


C_SET_STR_CHAR::~C_SET_STR_CHAR(){}

#ifdef SETGUARD
    extern "C" C_Instruction * F_GetInstruction() {return new C_SET_STR_CHAR(nullptr);}
#endif
