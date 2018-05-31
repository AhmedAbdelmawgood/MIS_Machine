#include "C_ASSIGN.h"

C_ASSIGN::C_ASSIGN(MIS *mis, int &P_PC)
{
    if (mis != nullptr && P_PC != -1) {
        misInst = mis;
        V_PC = &P_PC;
    }
}

C_Instruction * C_ASSIGN::F_Clone(MIS *mis, int &P_PC){
    C_ASSIGN * ass = new C_ASSIGN(mis, P_PC);
    return ass;
}

void C_ASSIGN::F_Execute(){
    params  = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];

    std::regex isVariable("//$.*");
    if( misInst->F_NumericVExists((*params)[2]) ){
        misInst->F_SetNumericV((*params)[2], value );
    }
    else if( misInst->F_CharVExists((*params)[2]) ){
        misInst->F_SetCharV( (*params)[2] ,valueS[0]);
    }
    else if(misInst->F_RealVExists((*params)[2]) ){
        misInst->F_SetRealV( (*params)[2] , value );
    }
    else if ( misInst->F_StringVExists( (*params)[2] ) ) {
        misInst->F_SetStringV( (*params)[2], valueS.substr(1,valueS.size()-2),valueS.length());
    }
}

void C_ASSIGN::F_CheckSyntax(){
    params  = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];
    regex assignn("ASSIGN\\s(\\$\\w(\\w|\\d)*),.*");
    if(!std::regex_match((*params)[0],assignn)){
        V_ErrorMessage = "In function ASSIGN: Syntax Error.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    if(!F_CheckSemantics()){
        V_ErrorMessage = "In function ASSIGN: Value is not of the variable type or Variable does not exist.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
}

bool C_ASSIGN::F_CheckSemantics(){
    regex test1("ASSIGN\\s\\$\\w(\\w|\\d)*,\\$\\w(\\w|\\d)*");
    regex testChar("ASSIGN\\s\\$\\w(\\w|\\d)*,\\'.*\\'");
    regex testNumeric("ASSIGN\\s\\$\\w(\\w|\\d)*,([-])?\\d+");
    regex testReal("ASSIGN\\s\\$\\w(\\w|\\d)*,([-])?(\\d+\\.)?\\d+");
    regex testString("ASSIGN\\s\\$\\w(\\w|\\d)*,\\\".*\\\"");

    if( misInst->F_NumericVExists((*params)[2])){
        if( !misInst->F_NumericVExists((*params)[3]) && !std::regex_match((*params)[0], testNumeric) )return 0;
        value = (misInst->F_NumericVExists( (*params)[3]) ) ? misInst->F_GetNumericV( (*params)[3]) : std::stoi((*params)[3]) ;//2-3,2-3,2-3
	//cout << "got here"<<endl;
    }
    else if(misInst->F_RealVExists( (*params)[2]) ){
        if( !misInst->F_RealVExists( (*params)[3])&& !std::regex_match((*params)[0],testReal))return 0;
            value = misInst->F_RealVExists( (*params)[3]) ? misInst->F_GetRealV( (*params)[3])  : std::stod((*params)[3]);
    }
    else if(misInst->F_CharVExists((*params)[2]) ){
        if( !misInst->F_CharVExists( (*params)[3])&& !std::regex_match((*params)[0] , testChar))return 0;
            valueS = misInst->F_CharVExists( (*params)[3]) ? misInst->F_GetCharV( (*params)[3]) : (*params)[3][1];
    }
    else if(misInst->F_StringVExists((*params)[2])){
        if( !misInst->F_StringVExists( (*params)[3])&& !std::regex_match((*params)[0],testString))return 0;
            valueS = misInst->F_StringVExists( (*params)[3]) ? misInst->F_GetStringV( (*params)[3]) : (*params)[3];
    }
    /** No semantics error **/
    else{
        return 0;
    }
    return 1;
}
C_ASSIGN::~C_ASSIGN(){}

#ifdef ASSIGNGUARD
    extern "C" C_Instruction * F_GetInstruction() {return new C_ASSIGN(nullptr);}
#endif
