#include "C_OUT.h"

C_OUT::C_OUT(MIS *mis, int &P_PC){
    if (mis != nullptr && P_PC != -1) {
        misInst = mis;
        V_PC = &P_PC;
    }
}
C_Instruction * C_OUT::F_Clone(MIS *mis, int &P_PC){
    C_OUT * out = new C_OUT(mis, P_PC);
    return out;
}
void C_OUT::F_CheckSyntax(){
    /** Loading instruction string vector into params**/
    params  = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];
    /** Too many arguments **/
    regex out ("(OUT)\\s((\\$[A-Za-z][_A-Za-z0-9]{0,255})|([-]?([0-9]*[.])?[0-9]+)|(\\\"[_\\sA-Za-z0-9\\\\]+\\\")|(\\'[A-Za-z0-9_]\\'))(\\,(\\$[A-Za-z][_A-Za-z0-9]{0,255})|(\\,[-]?([0-9]*[.])?[0-9]+)|(\\,\\\"[\\sA-Za-z0-9_]+\\\")|(\\,\\'[A-Za-z0-9_]\\')){0,11}");
    if (!regex_match((*params)[0], out)){
        V_ErrorMessage = "In function OUT: Syntax Error.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    if(params->size() < 3 || params->size() > 14){ /** Too many arguments **/
        V_ErrorLine = (*V_PC);
        V_ErrorMessage = "In function OUT: Too many parameters passed to OUT which accepts 1-12 parameters";
        F_ReportError();
        return;
    }
    /** Check that variables exist **/
    for(unsigned int i = 2; i < params->size(); i++){
        /** Parameter is a variable and does not exist **/
        if((*params)[i][0] == '$'){
            if (!misInst->F_NumericVExists((*params)[i]) && !misInst->F_RealVExists((*params)[i])
                && !misInst->F_CharVExists((*params)[i]) && !misInst->F_StringVExists((*params)[i])){
                V_ErrorMessage = "In function OUT: Variable passed to OUT does not exist.";
                V_ErrorLine = (*V_PC);
                F_ReportError();
                return;
            }
        }
    }
}
/** Writes to the .out file **/
void C_OUT::F_Execute(){
    /** Loading instruction string vector into params**/
    params  = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];
    /** Looping through the parameters **/
    for(unsigned int idx = 2; idx < params->size(); idx++){
        /** Parameter is a variable **/
        if ((*params)[idx][0] == '$'){
            string varName = (*params)[idx];
            /** Variable is NUMERIC **/
            if(misInst->F_NumericVExists(varName)){
                misInst->F_WriteToOut((varName), 'N');
            }
            /** Variable is REAL **/
            else if(misInst->F_RealVExists(varName)){
                 misInst->F_WriteToOut(varName, 'R');
            }
            /** Variable is STRING **/
            else if(misInst->F_StringVExists(varName)){
                misInst->F_WriteToOut(varName, 'S');
            }
            /** Variable is CHAR **/
            else if(misInst->F_CharVExists(varName)){
                misInst->F_WriteToOut(varName, 'C');
            }
        }
        /** Parameter is not a variable **/
        else{
            /** Parameter is STRING **/
            if ((*params)[idx][0] == '"'){
                if ((*params)[idx] == "\"ENDLINE\""){
                    misInst->F_WriteToOut("\n");
                }
                else {
                    misInst->F_WriteToOut((*params)[idx].substr(1,((*params)[idx]).size()-2));
                }
            }
            /** Parameter is CHAR **/
            else if ((*params)[idx][0] == '\''){
                string temp(1, ((*params)[idx][1]));
               misInst->F_WriteToOut(temp);
            }
            /** Parameter is a number **/
            else{
                misInst->F_WriteToOut((*params)[idx]);
            }
        }
        }
}

C_OUT::~C_OUT(){}

#ifdef OUTGUARD
    extern "C" C_Instruction * F_GetInstruction() {return new C_OUT(nullptr);}
#endif
