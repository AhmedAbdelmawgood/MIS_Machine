#include "C_LABEL.h"

C_LABEL::C_LABEL(MIS *mis, int &P_PC){
   if (mis != nullptr && P_PC != -1) {
        misInst = mis;
        V_PC = &P_PC;
    }
}
C_Instruction * C_LABEL::F_Clone(MIS *mis, int &P_PC){
    C_LABEL * lab = new C_LABEL(mis, P_PC);
    return lab;
}
/** Checks all syntax errors and calls ReportError if theres an error**/
void C_LABEL::F_CheckSyntax(){
    /** Loading instruction string vector into params **/
    params = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];
    /** Parameters not equal to 1 or label name does not start with an alphabetic CHAR**/
    if(params->size() !=3 || !(isalpha((*params)[2][0])) ){
        misInst->F_SetLabelError();
        return;
    }
}

/** Adds label to the LabelsMap **/
void C_LABEL::F_Execute(){
    misInst->F_SetLabel(((*params)[2]), (*V_PC));
}

C_LABEL::~C_LABEL(){}

#ifdef LABELGUARD
    extern "C" C_Instruction * F_GetInstruction() {return new C_LABEL(nullptr);}
#endif
