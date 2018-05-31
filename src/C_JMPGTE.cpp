#include "C_JMPGTE.h"

C_JMPGTE::C_JMPGTE(MIS *mis, int &P_PC)
{
    if (mis != nullptr && P_PC != -1) {
        misInst = mis;
        V_PC = &P_PC;
    }
}
C_Instruction * C_JMPGTE::F_Clone(MIS *mis, int &P_PC){
    C_JMPGTE * jmpgte = new C_JMPGTE(mis, P_PC);
    return jmpgte;
}
/** Checks all syntax errors and calls ReportError if theres an error**/
void C_JMPGTE::F_CheckSyntax(){
    /** Loading instruction string vector into params**/
    params = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];
    /**Checking Regex for the desired format (for each parameter)**/
    regex V_test("(\\$[A-Za-z][A-Za-z0-9]{0,255}|([-]?([0-9]*[.])?[0-9]+))");
    if((*params).size() != 5 || !misInst->F_LabelExists((*params)[2])){//4-5,1-2
        misInst->F_SetError(1);
        V_ErrorMessage = "In function JMPGTE: Too many arguments passed to JMPGT or label does not exist.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /** 1st and 2nd parameters are variables that do not exist in MUMERIC and REAL maps **/
    for(unsigned int idx = 3; idx < params->size(); idx++){ //2-3
        if (!regex_match((*params)[idx],V_test) |
            (*params)[idx][0] == '$' &&(!misInst->F_NumericVExists((*params)[idx])
                                        && !misInst->F_RealVExists((*params)[idx]))){
            V_ErrorMessage = "In function JMPGTE: Syntax does not match or variable does not exist.";
            V_ErrorLine = (*V_PC);
            F_ReportError();
            return;
        }
    }
}

/** Checks if the condition is true to jump or not **/
void C_JMPGTE::F_Execute(){
    /** Loading instruction string vector into params**/
    params = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];
    /** double Array for comparison **/
    double V_valueArray[2];
    for(unsigned int idx = 3; idx < params->size();idx++){
        /** Parameter is a variable **/
        if ((*params)[idx][0] == '$'){
            string varName = (*params)[idx];
            /** parameter is a NUMERIC variable **/
            if(misInst->F_NumericVExists((*params)[idx])){
                V_valueArray[idx-3] = misInst->F_GetNumericV(varName);
            }
            /** parameter is a REAL variable **/
            else if(misInst->F_RealVExists((*params)[idx])){
                 V_valueArray[idx-3] = misInst->F_GetRealV(varName);
            }
        }
        /** parameter is not a variable **/
        else{
            V_valueArray[idx-3] = stod((*params)[idx]);
        }
    }
    /** Checks if the condition is true **/
    if(V_valueArray[0] >= V_valueArray[1]){
        /** Jump to a specific label **/
        (*V_PC) = misInst->F_LabelLine((*params)[2]);
    }
}

C_JMPGTE::~C_JMPGTE(){}

#ifdef JMPGTEGUARD
    extern "C" C_Instruction * F_GetInstruction() {return new C_JMPGTE(nullptr);}
#endif
