#include "C_SUB.h"

C_SUB::C_SUB(MIS *mis, int &P_PC)
{
    if (mis != nullptr && P_PC != -1) {
        misInst = mis;
        V_PC = &P_PC;
    }
}
C_Instruction * C_SUB::F_Clone(MIS *mis, int &P_PC){
    C_SUB * sub = new C_SUB(mis, P_PC);
    return sub;
}
/** Checks all syntax errors and calls ReportError if theres an error**/
void C_SUB::F_CheckSyntax(){
    /** Loading instruction string vector into params**/
    params  = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];
     /**Checking Regex for the desired format**/
    regex sub("SUB(\\s)(\\$[A-Za-z][_A-Za-z0-9]{0,255})((\\,\\$[A-Za-z]+[_A-Za-z0-9]{0,255})|\\,([-]?([0-9]*[.])?[0-9]+)){2}");
    if (!regex_match((*params)[0], sub)){
        V_ErrorMessage = "Syntax Error in function SUB.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /**2nd argument is the variable name**/
    V_VariableName = (*params)[2];//1-2
    if (params->size() != NO_OF_OPERANDS+2){ /** Params not equal 3**/
        V_ErrorMessage = "Function Arguments missing. SUB takes exactly 3 Parameters.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
     /** VariableName does not exists in NUMERIC or REAL variables**/
    if (!misInst->F_NumericVExists(V_VariableName) && !misInst->F_RealVExists(V_VariableName)){ //1-2,1-2
        V_ErrorMessage = "In function SUB, the variable you want to assign to does not exist.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /**Variable parameters do not exist in NUMERIC nor REAL maps**/
    for (int i = 3; i < 5; i++){//2-3,4-5
        if ((*params)[i][0] == '$'){
            if (!misInst->F_NumericVExists((*params)[i]) && !misInst->F_RealVExists((*params)[i])){ //1-2,1-2
            V_ErrorMessage = "One of the variables you want to subtract does not exist, or do not accept subtraction";
            V_ErrorLine = (*V_PC);
            F_ReportError();
            return;
            } // if
        } // if
    } // for
} // F_CheckSyntax()

/**Does the actual addition**/
void C_SUB::F_Execute(){
    V_VariableName = (*params)[2];
    V_Result = 0;
    /** Loading instruction string vector into params**/
    params  = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];
    /**2nd parameter is a variable **/
    if ((*params)[3][0] == '$'){
        /** Variable is REAL, get it from REAL map**/
        if (misInst->F_RealVExists((*params)[3])){
            V_Result += misInst->F_GetRealV((*params)[3]);
        }
        /** Variable is NUMERIC, get it from NUMERIC map**/
        else if (misInst->F_NumericVExists((*params)[3])){
            V_Result += misInst->F_GetNumericV((*params)[3]);
        }
    }
    /**2nd parameter is not a variable, treat it as a double**/
    else V_Result += stod((*params)[3]);

    /**3rd parameter is a variable **/
    if ((*params)[4][0] == '$'){
        /** Variable is REAL, get it from REAL map**/
        if (misInst->F_RealVExists((*params)[4])){
            V_Result -= misInst->F_GetRealV((*params)[4]);
        }
        /** Variable is NUMERIC, get it from NUMERIC map**/
        else if (misInst->F_NumericVExists((*params)[4])){
            V_Result -= misInst->F_GetNumericV((*params)[4]);
        }
    }
    /**3rd parameter is not variable, treat it as a double **/
    else V_Result -= stod((*params)[4]);
    /**Put the value in the VariableName**/
    F_SetResult();
}

/**Puts the result of subtraction in the VariableName**/
void C_SUB::F_SetResult(){
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

C_SUB::~C_SUB(){}

#ifdef SUBGUARD
    extern "C" C_Instruction * F_GetInstruction() {return new C_SUB(nullptr);}
#endif
