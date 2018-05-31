#include "C_JMP.h"


C_JMP::C_JMP(MIS *mis, int &P_PC){
    if (mis != nullptr && P_PC != -1) {
        misInst = mis;
        V_PC = &P_PC;
    }
}

C_Instruction * C_JMP::F_Clone(MIS *mis, int &P_PC){
    C_JMP * jmp = new C_JMP(mis, P_PC);
    return jmp;
}

/** Checks all syntax errors and calls ReportError if theres an error**/
void C_JMP::F_CheckSyntax(){

    params = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];
    /** Label not found or parameters > 1**/
    if((*params).size() != 3 || !misInst->F_LabelExists((*params)[2])){
        V_ErrorMessage = "In function JMP: Too many parameters or label is not defined.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
}

/** Jump to the specific label **/
void C_JMP::F_Execute(){
    /** Loading instruction string vector into params**/
    params = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];
    *(V_PC) = misInst->F_LabelLine((*params)[2]);
}

C_JMP::~C_JMP(){}

#ifdef JMPGUARD
    extern "C" C_Instruction * F_GetInstruction() {return new C_JMP(nullptr);}
#endif
