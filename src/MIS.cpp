#include "MIS.h"
#include "C_JMP.h"
#include "C_JMPZ.h"
#include "C_JMPNZ.h"
#include "C_JMPGT.h"
#include "C_JMPLT.h"
#include "C_JMPGTE.h"
#include "C_JMPLTE.h"
#include "C_OUT.h"
#include "C_ADD.h"
#include "C_VAR.h"
#include "C_LABEL.h"
#include "C_SLEEP.h"
#include "C_DIV.h"
#include "C_ASSIGN.h"
#include "C_SUB.h"
#include "C_MUL.h"
#include "C_SET_STR_CHAR.h"
#include "C_GET_STR_CHAR.h"


MIS::MIS(): V_PC(0),error(false)
{
    V_LabelError = false;
    /** Initializing the main instructions in the Instruction Map **/
    InstrucionsMap["ADD"]    = new C_ADD     (this);
    InstrucionsMap["SUB"]    = new C_SUB     (this);
    InstrucionsMap["MUL"]    = new C_MUL     (this);
    InstrucionsMap["DIV"]    = new C_DIV     (this);
    InstrucionsMap["VAR"]    = new C_VAR     (this);
    InstrucionsMap["OUT"]    = new C_OUT     (this);
    InstrucionsMap["JMP"]    = new C_JMP     (this);
    InstrucionsMap["JMPGT"]  = new C_JMPGT   (this);
    InstrucionsMap["JMPNZ"]  = new C_JMPNZ   (this);
    InstrucionsMap["JMPZ"]   = new C_JMPZ    (this);
    InstrucionsMap["JMPLT"]  = new C_JMPLT   (this);
    InstrucionsMap["JMPGTE"] = new C_JMPGTE  (this);
    InstrucionsMap["JMPLTE"] = new C_JMPLTE  (this);
    InstrucionsMap["ASSIGN"] = new C_ASSIGN  (this);
    InstrucionsMap["SLEEP"]  = new C_SLEEP   (this);
    InstrucionsMap["LABEL"]  = new C_LABEL   (this);
    InstrucionsMap["SET_STR_CHAR"] = new C_SET_STR_CHAR(this);
    InstrucionsMap["GET_STR_CHAR"] = new C_GET_STR_CHAR(this);
    V_ThreadCollector = new C_ThreadCollector();
    pthread_mutex_init (&V_OutMutex , NULL);

}


MIS::~MIS()
{
    if(MainParser!=0){
        delete MainParser;
    }
    /** Deletes the values of the InstructionMap,
    which are objects of type C_Instruction **/
    for(auto &it : InstrucionsMap){
        delete it.second;
    }
    for(auto &it : RealMap){
        delete it.second;
    }
    for(auto &it : NumericMap){
        delete it.second;
    }
    for(auto &it : StringMap){
        delete it.second;
    }
    for(auto &it : CharMap){
        delete it.second;
    }
}

/** Adds all labels before execution**/
void MIS::F_AddLabels(){
    int PC = 0;
    while(PC < V_FileSize){
        /** Get the name of the first instruction **/
        string temp=(*(MainParser->LinesInstrcts[PC]))[1];
        if( temp == "LABEL" ){
            C_Instruction * Instruction = InstrucionsMap[temp]->F_Clone(this, PC);
            /** Check the label syntax first **/
            V_LabelError = false;
            Instruction->F_CheckSyntax();
            /** Add label to LabelMap **/
            if(!error && !V_LabelError) {
                Instruction->F_Execute();
            }
            delete Instruction;
        }
        PC++; /** Advance program counter **/
    }
    PC = 0; /** Reached end of file **/
}

/** Main system method; Gets instructions, checks syntax and executes **/
void MIS::Run(vector<string>*P_InstructVec, ostringstream* P_Out,ostringstream* P_Error){
    V_OutStream   = P_Out;
    V_ErrorStream = P_Error;

    /** Parsing all instructions to the Instruction vector **/
    MainParser = new C_FileParser(P_InstructVec);

    /** MainParser object failed **/
    if (MainParser == 0){
        V_ErrorMessage = "Error! Cannot parse instructions.";
        V_ErrorLine = -1;
        F_ReportError();
        return;
    }
    V_FileSize = MainParser->GetFileSize();

    /** Adds all labels before execution **/
    F_AddLabels();
    Run(0, V_FileSize,-1);
}

void MIS::Run(int P_Start, int P_End, int P_ID){
    cout << "Run()" << endl;
    /** Array of booleans to check if this line has been checked on before (in loops)**/
    bool V_Checked[V_FileSize];
    memset(V_Checked,0,sizeof(V_Checked));
    int PC = P_Start;
    /** Did not reach the end of the file **/
    while(PC < P_End){
        /**Instruction Name**/
        string temp = (*(MainParser->LinesInstrcts[PC]))[1];
        /** Instruction exists **/
        if (temp == "THREAD_BEGIN" ){
            int V_end = 0;
            for (int j = PC+1; j < V_FileSize; j++){
                temp = (*(MainParser->LinesInstrcts[j]))[1];
                if (temp == "THREAD_END"){
                   V_end = j;
                   break;
               }
           }
           if (V_end != 0 ){
                V_ThreadCollector->cleanup();
                C_MISThread * misthread = new C_MISThread(this, PC+1, V_end);
                misthread->F_StartThread();
                V_ThreadCollector->addThread(misthread);
                PC = V_end;
            }
            else{
                V_ErrorMessage = "In function THREAD_BEGIN: Cannot find THREAD_END, or syntax error.";
                V_ErrorLine    = PC;
                F_ReportError();
                return;
            }
        }
        else if (temp == "BARRIER" ){
            if (true ){
                delete V_ThreadCollector;
                C_MISThread::F_ResetIDs();
            }
            else{
                V_ErrorMessage = "In function Barrier: Called from inside a thread or syntax error.";
                V_ErrorLine    = PC;
                F_ReportError();
                return;
            }
        }
        else if (temp == "LOCK" ){
            if (!F_Lock((*(MainParser->LinesInstrcts[PC]))[2], P_ID)){
                V_ErrorMessage = "In function LOCK: Called from outside a thread, variable does not exist or syntax error.";
                V_ErrorLine    = PC;
                F_ReportError();
                return;
            }
        }
        else if (temp == "UNLOCK"){
            if (!F_Unlock((*(MainParser->LinesInstrcts[PC]))[2], P_ID)){
                V_ErrorMessage = "In function UNLOCK: Called from outside a thread, variable does not exist or syntax error.";
                V_ErrorLine    = PC;
                F_ReportError();
                return;
            }
        }
        else if (InstrucionsMap[temp] != 0 && temp != "LABEL" && temp!= "THREAD_END"){
            C_Instruction* Instruction = InstrucionsMap[temp]->F_Clone(this, PC);
            /** if this line was not checked before, check it **/
            if(!V_Checked[PC]) Instruction->F_CheckSyntax();
            if(this->error) break;
            V_Checked[PC] = true;
            Instruction->F_Execute(); /** execute **/
            delete Instruction;
        }
        else if (temp == "LABEL"){
            C_Instruction* Instruction = InstrucionsMap[temp]->F_Clone(this, PC);
            if(!V_Checked[PC]){
                V_LabelError = false;
                Instruction->F_CheckSyntax();
            }
            if (V_LabelError){
                V_ErrorMessage = "In function LABEL: Syntax Error.";
                V_ErrorLine = PC;
                F_ReportError();
                return;
            }
            if(this->error) break;
            V_Checked[PC] = true;
        delete Instruction;
        }
        /** Instruction not found **/
        else if (InstrucionsMap[temp] == 0){
            V_ErrorMessage = "Function is not defined.";
            V_ErrorLine = PC;
            F_ReportError();
            return;
        }
        /** Advance program counter**/
        PC++;
    }
    return;
}

void MIS::F_WriteToOut(string variableName, char type)
{
    cout << "Got here " << variableName<< " " << type << endl;
    if (type == 'A'){
    pthread_mutex_lock(&V_OutMutex);
    (*V_OutStream) << variableName;
    cout << type << " "<< pthread_mutex_unlock(&V_OutMutex)<<endl;
    return;
    }
    if (type == 'S'){
    pthread_mutex_lock(&V_OutMutex);
    (*V_OutStream) << F_GetStringV(variableName);
    cout << type << " "<< pthread_mutex_unlock(&V_OutMutex);
    return;
    }
    if (type == 'N'){
    pthread_mutex_lock(&V_OutMutex);
    (*V_OutStream) << F_GetNumericV(variableName);
    cout << type << " "<< pthread_mutex_unlock(&V_OutMutex);
    return;
    }
    if (type == 'R'){
    pthread_mutex_lock(&V_OutMutex);
    (*V_OutStream) << F_GetRealV(variableName);
    cout << type << " "<< pthread_mutex_unlock(&V_OutMutex);
    return;
    }
    if (type == 'C'){
    pthread_mutex_lock(&V_OutMutex);
    (*V_OutStream) << F_GetCharV(variableName);
    cout << type << " " <<pthread_mutex_unlock(&V_OutMutex);
    return;
    }
}

bool MIS::F_Lock(string variableName, int P_ID){
    if (P_ID == -1) return false;
    if (F_NumericVExists(variableName)){
        NumericMap[variableName]->F_Lock(P_ID);
        return true;
    }
    else if (F_RealVExists(variableName)){
        RealMap[variableName]->F_Lock(P_ID);
        return true;
    }
    else if (F_StringVExists(variableName)){
        StringMap[variableName]->F_Lock(P_ID);
        return true;
    }
    else if (F_CharVExists(variableName)){
        CharMap[variableName]->F_Lock(P_ID);
        return true;
    }
    else {
        return false;
    }
}

bool MIS::F_Unlock(string variableName, int P_ID){
    if (P_ID == -1) return false;
    if (F_NumericVExists(variableName)){
        NumericMap[variableName]->F_Unlock(P_ID);
        return true;
    }
    else if (F_RealVExists(variableName)){
        RealMap[variableName]->F_Unlock(P_ID);
        return true;
    }
    else if (F_StringVExists(variableName)){
        StringMap[variableName]->F_Unlock(P_ID);
        return true;
    }
    else if (F_CharVExists(variableName)){
        CharMap[variableName]->F_Unlock(P_ID);
        return true;
    }
    else {
        return false;
    }
}

void MIS::F_SetLabelError(){
    V_LabelError = true;
}

/**Sets the error to 1 if an error is found**/
void MIS::F_SetError(bool state){
    error = state;
}
/** Changes the value of program counter (in jumps)**/
void MIS::F_SetPC(int num){
    V_PC = num;
}
/** Returns the line we're executing**/
int MIS::F_GetPC(){
    return V_PC;
}

/**Checks if a NUMERIC variable exists in NumericMap**/
bool MIS::F_NumericVExists(string variableName){
    if (NumericMap.find(variableName) != NumericMap.end()) {
            return true;
            }
    return false;
}
/**Checks if a REAL variable exists in RealMap**/
bool MIS::F_RealVExists(string variableName){
    if (RealMap.find(variableName) != RealMap.end())return true;
    return false;
}
/**Checks if a CHAR variable exists in CharMap**/
bool MIS::F_CharVExists(string variableName){
    if (CharMap.find(variableName) != CharMap.end()) return true;
    return false;
}
/**Checks if a STRING variable exists in StringMap**/
bool MIS::F_StringVExists(string variableName){
    if (StringMap.find(variableName) != StringMap.end()) return true;
    return false;
}
/**Returns the value of a NUMERIC variable**/
int MIS::F_GetNumericV(string variableName){
    return NumericMap[variableName]->F_GetValue();
}
/**Returns the value of a REAL variable**/
double MIS::F_GetRealV(string variableName){
    return RealMap[variableName]->F_GetValue();
}
/**Returns the value of a CHAR variable**/
char MIS::F_GetCharV(string variableName){
    return CharMap[variableName]->F_GetValue();
}
/**Returns the value of a STRING variable**/
string MIS::F_GetStringV(string variableName){
    return StringMap[variableName]->F_GetValue();
}
/** Creates a new NUMERIC variable, and changes its value if exists **/
void MIS::F_SetNumericV(string variableName, int    value){
    if (!F_NumericVExists(variableName)){
        NumericMap[variableName] = new C_NUMERIC(value);
        return;
    }
    NumericMap[variableName]->F_SetValue(value);
}
/** Creates a new REAL variable, and changes its value if exists **/
void MIS::F_SetRealV   (string variableName, double value){
    if (!F_RealVExists(variableName)){
        RealMap[variableName] = new C_REAL(value);
        return;
    }
    RealMap[variableName]->F_SetValue(value);
}
/** Creates a new CHAR variable, and changes its value if exists **/
void MIS::F_SetCharV   (string variableName, char   value){
    if (!F_CharVExists(variableName)){
        CharMap[variableName] = new C_CHAR(value);
        return;
    }
    CharMap[variableName]->F_SetValue(value);
}
/** Creates a new STRING variable, and changes its value if exists **/
void MIS::F_SetStringV (string variableName, string value, int p_size){
    if (!F_StringVExists(variableName)){
        StringMap[variableName] = new C_STRING(value, p_size);
        return;
    }
    StringMap[variableName]->F_SetValue(value, p_size);
}
/** Changes a specific CHAR in a STRING**/
void MIS::F_SetStringChar (string variableName, int index, char character){
    StringMap[variableName]->F_SetStrChar(index, character);
}
/** Gets a specific CHAR in a STRING**/
char MIS::F_GetStringChar (string variableName, int index){
    return StringMap[variableName]->F_GetStrChar(index);
}
/**Returns the maximum size of a STRING variable **/
int MIS::F_GetStringSize(string variableName){
    return StringMap[variableName]->F_GetStrSize();
}
/** Returns the MainParser object **/
C_FileParser* MIS::F_GetMainParser(){
    return MainParser;
}
/** Checks if label exists **/
bool MIS::F_LabelExists(string label){
    if(LabelsMap.find(label) != LabelsMap.end()) return true;
    return false;
}
/** Gets label line number **/
int MIS::F_LabelLine(string label){
    return LabelsMap[label];
}
void MIS::F_SetLabel(string label, int line){
    LabelsMap[label] = line;
}
/** Creates a new instance of C_ErrorHandler and reports the error**/
void MIS::F_ReportError(){
    C_ErrorHandler error(this, V_ErrorLine, V_ErrorMessage);
    error.C_WriteError();
    return;
}
