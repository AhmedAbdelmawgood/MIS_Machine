#include "C_MUL.h"

C_MUL::C_MUL(MIS *mis, int &P_PC)
{
    if (mis != nullptr && P_PC != -1) {
        misInst = mis;
        V_PC = &P_PC;
    }
}
C_Instruction * C_MUL::F_Clone(MIS *mis, int &P_PC){
    C_MUL * mul = new C_MUL(mis, P_PC);
    return mul;
}
/** Checks all syntax errors and calls ReportError if theres an error**/
void C_MUL::F_CheckSyntax(){
    /** Loading instruction string vector into params**/
    params  = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];
    /**Checking Regex for the desired format**/
    regex mul ("(MUL)(\\s)(\\$[A-Za-z][_A-Za-z0-9]{0,255})((\\,\\$[A-Za-z]+[_A-Za-z0-9]{0,255})|\\,([-]?([0-9]*[.])?[0-9]+)){2,12}");
    if (!regex_match((*params)[0], mul)){
        V_ErrorMessage = "Syntax Error: In MUL function.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /**2nd argument is the variable name**/
    V_VariableName = (*params)[2];//1-2
    /** Params less than 3 or greater than 13 **/
    if (params->size() < MIN_OPERANDS_NO+2 || params->size() > MAX_OPERANDS_NO+2){
        V_ErrorMessage = "In function MUL: MUL takes between 3 and 13 parameters.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /** VariableName does not exists in NUMERIC or REAL variables**/
    if (!misInst->F_NumericVExists(V_VariableName) && !misInst->F_RealVExists(V_VariableName)){
        V_ErrorMessage = "In function MUL: The variable you want to assign to does not exist.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /**Variable parameters do not exist in NUMERIC nor REAL maps**/
    for (unsigned int i = 3; i < params->size(); i++){
        if ((*params)[i][0] == '$'){
            if (!misInst->F_NumericVExists((*params)[i]) && !misInst->F_RealVExists((*params)[i])){//1-i
            V_ErrorMessage = "In function MUL: One of the variables you want to multiply does not exist, or does not accept multiplication";
            V_ErrorLine = (*V_PC);
            F_ReportError();
            return;
            }
        }
    }
}

/**Does the actual multiplication**/
void C_MUL::F_Execute(){
        V_Result = 1;
        /** Loading instruction string vector into params**/
        V_VariableName = (*params)[2];
        params  = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];
        /**Loops through all parameters to be added**/
        for (unsigned int i = 3; i< params->size(); i++){//2-3
            /** if parameter is a variable**/
            if ((*params)[i][0] == '$'){
                /** Variable is REAL, get it from REAL map**/
                if (misInst->F_RealVExists((*params)[i])){
                    V_Result *= misInst->F_GetRealV((*params)[i]);
                }
                /** Variable is NUMERIC, get it from NUMERIC map**/
                else if (misInst->F_NumericVExists((*params)[i])){
                    V_Result *= misInst->F_GetNumericV((*params)[i]);
                }
            }
            /** parameter is not a variable, add it as a double**/
            else V_Result *= stod((*params)[i]);
            }
        /**Put the value in the VariableName**/
        F_SetResult();
}

/**Puts the result of multiplication in the VariableName**/
void C_MUL::F_SetResult(){
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

C_MUL::~C_MUL(){}

#ifdef MULGUARD
    extern "C" C_Instruction * F_GetInstruction() {return new C_MUL(nullptr);}
#endif
