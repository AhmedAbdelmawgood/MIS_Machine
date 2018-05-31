#include "C_ADD.h"

C_ADD::C_ADD(MIS *mis, int &P_PC)
{
    if (mis != nullptr && P_PC != -1) {
        misInst = mis;
        V_PC = &P_PC;
    }
}

C_Instruction * C_ADD::F_Clone(MIS *mis, int &P_PC){
    C_ADD * add = new C_ADD(mis, P_PC);
    return add;
}

/** Checks all syntax errors and calls ReportError if theres an error**/
void C_ADD::F_CheckSyntax(){
    /** Loading instruction string vector into params**/
    params  = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];
    /**Checking Regex for the desired format**/
    regex add ("(ADD)(\\s)(\\$[A-Za-z][_A-Za-z0-9]{0,255})((\\,\\$[A-Za-z]+[_A-Za-z0-9]{0,255})|\\,([-]?([0-9]*[.])?[0-9]+)){2,12}");
    if (!regex_match((*params)[0], add)){
        V_ErrorMessage = "Syntax Error: In function ADD.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /**2nd argument is the variable name**/
    V_VariableName = (*params)[2];
    /** Params less than 3 or greater than 13 **/
    if (params->size() < MIN_OPERANDS_NO+2 || params->size() > MAX_OPERANDS_NO+2){
        V_ErrorMessage = "In function ADD: The number of parameters passed to ADD must be between 3 to 13.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /** VariableName does not exists in NUMERIC or REAL variables**/
    if (!misInst->F_NumericVExists(V_VariableName) && !misInst->F_RealVExists(V_VariableName)){
        V_ErrorMessage = "In function ADD: The variable you want to assign to does not exist, or is not of type NUMERIC nor REAL.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /**Variable parameters do not exist in NUMERIC nor REAL maps**/
    for (unsigned int i = 3; i < params->size(); i++){
        if ((*params)[i][0] == '$'){
            if (!misInst->F_NumericVExists((*params)[i]) && !misInst->F_RealVExists((*params)[i])){
            V_ErrorMessage = "In function ADD: One of the variables you want to add does not exist, or do not accept addition";
            V_ErrorLine = (*V_PC);
            F_ReportError();
            return;
            }
        }
    }
}

/**Does the actual addition**/
void C_ADD::F_Execute(){
    /** Loading instruction string vector into params**/
    params  = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];
    V_VariableName = (*params)[2];
    V_Result = 0;
    /**Loops through all parameters to be added**/
    for (unsigned int i = 3; i < params->size(); i++){
        /** if parameter is a variable**/
        if ((*params)[i][0] == '$'){
            /** Variable is REAL, get it from REAL map**/
            if (misInst->F_RealVExists((*params)[i])){
                V_Result += misInst->F_GetRealV((*params)[i]);
            }
            /** Variable is NUMERIC, get it from NUMERIC map**/
            else if (misInst->F_NumericVExists((*params)[i])){
                V_Result += misInst->F_GetNumericV((*params)[i]);
            }
        }
        /** parameter is not a variable, add it as a double**/
        else V_Result += stod((*params)[i]);
    }
    /**Put the value in the VariableName**/
    F_SetResult();
}

/**Puts the result of addition in the VariableName**/
void C_ADD::F_SetResult(){
    /** If VariableName is REAL, put it as it is **/
    if (misInst->F_RealVExists(V_VariableName)) {
        misInst->F_SetRealV(V_VariableName, V_Result);
        return;
    }
    /** If VariableName is NUMERIC, cast to int first **/
    else if (misInst->F_NumericVExists(V_VariableName)){
        misInst->F_SetNumericV(V_VariableName, (int) V_Result);
    }
}
C_ADD::~C_ADD(){}

#ifdef ADDGUARD
    extern "C" C_Instruction * F_GetInstruction() {return new C_ADD(nullptr);}
#endif
