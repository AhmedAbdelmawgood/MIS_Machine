#include "C_SLEEP.h"
#include <chrono>
#include <thread>

C_SLEEP::C_SLEEP(MIS *mis, int &P_PC)
{
    if (mis != nullptr && P_PC != -1) {
        misInst = mis;
        V_PC = &P_PC;
    }
}

C_Instruction * C_SLEEP::F_Clone(MIS *mis, int &P_PC){
    C_SLEEP * sleep = new C_SLEEP(mis, P_PC);
    return sleep;
}

/** Checks all syntax errors and calls ReportError if theres an error**/
void C_SLEEP::F_CheckSyntax(){
    /** Loading instruction string vector into params**/
    params = misInst->F_GetMainParser()->LinesInstrcts[(*V_PC)];
    /**Checking Regex for the desired format**/
    regex sleep ("(SLEEP)\\s((\\$[A-Za-z][_A-Za-z0-9]{0,255})|(([0-9]*[.])?[0-9]+))");
    if (!regex_match((*params)[0], sleep)){
        V_ErrorMessage = "In function SLEEP: SLEEP takes a positive number.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /** Too many arguments **/
    if(params->size()!=3){
        V_ErrorMessage = "In function SLEEP: Syntax Error.";
        V_ErrorLine = (*V_PC);
        F_ReportError();
        return;
    }
    /** Parameter is a variable **/
    if((*params)[2][0] == '$'){
        /** Variable is not a number or does not exist **/
        if (!misInst->F_NumericVExists((*params)[2]) && !misInst->F_RealVExists((*params)[2])){
            V_ErrorMessage = "In function SLEEP: Variable does not exist or is not of type Numeric or Real in function SLEEP.";
            V_ErrorLine = (*V_PC);
            F_ReportError();
            return;
        }
    }
}

/** Does the actual sleeping **/
void C_SLEEP::F_Execute(){
    int sec;
    /** Parameter is a variable **/
    if((*params)[2][0] == '$'){
        sec = max(misInst->F_GetNumericV((*params)[2]),(int)misInst->F_GetRealV((*params)[2]));
    }
    /** Parameter is not a variable **/
    else{
        sec = stoi((*params)[2]);
    }
    /** SLEEEEEEEP **/
    this_thread::sleep_for(chrono::seconds(sec));
}

C_SLEEP::~C_SLEEP(){}

#ifdef SLEEPGUARD
    extern "C" C_Instruction * F_GetInstruction() {return new C_SLEEP(nullptr);}
#endif
