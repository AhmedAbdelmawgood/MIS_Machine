#include "C_VAR.h"

C_VAR::C_VAR(MIS *mis, int &P_PC)
{
    if (mis != nullptr && P_PC != -1) {
        misInst = mis;
        V_PC = &P_PC;
    }
}

C_Instruction * C_VAR::F_Clone(MIS *mis, int &P_PC){
    C_VAR * var = new C_VAR(mis, P_PC);
    return var;
}

void C_VAR::F_CheckSyntax(){
    params  = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];

    std::regex var("VAR\\s(\\$\\w(\\w|\\d)*),((STRING(,\\d+)?,\\s*\\\".*\\\")|(NUMERIC,([-])?\\d+)|(REAL,([-])?(\\d+(\\.)){0,}\\d+)|(CHAR\\s*,\\s*'.*'\\s*))");
    if(!std::regex_match((*params)[0], var)){
        V_ErrorMessage = "In function VAR: Syntax error";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /** Variable already exists **/
    if (misInst->F_NumericVExists((*params)[2]) || misInst->F_RealVExists((*params)[2])
     || misInst->F_CharVExists((*params)[2]) || misInst->F_StringVExists((*params)[2])){

        V_ErrorMessage = "In function VAR: Variable exists.";
        V_ErrorLine = (*V_PC);
        F_ReportError();

        return;
    }
}

void C_VAR::F_Execute(){
    params  = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];
    string type = (*params)[3];
    string variableName = (*params)[2];
    if( type == "STRING"){
        string value = ( (*params)[5] ).substr(1, ( (*params)[5].length() )-2) ;
        misInst->F_SetStringV(variableName, value, (int)stoi( (*params)[4] ));
     }
     else if(type == "NUMERIC"){
        misInst->F_SetNumericV( variableName, std::stoi((*params)[4]) );
     }
     else if(type == "CHAR"){
        misInst->F_SetCharV( variableName , (*params)[4][1] );
     }
     else if(type == "REAL"){
        misInst->F_SetRealV( variableName , (double)stod((*params)[4]) );
     }
}

C_VAR::~C_VAR(){}

#ifdef VARGUARD
    extern "C" C_Instruction * F_GetInstruction() {return new C_VAR(nullptr);}
#endif
