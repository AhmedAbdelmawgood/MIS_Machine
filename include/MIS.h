#ifndef MIS_H
#define MIS_H

#include<bits/stdc++.h>
using namespace std;

#include "C_Instruction.h"
#include "C_REAL.h"
#include "C_NUMERIC.h"
#include "C_CHAR.h"
#include "C_STRING.h"
#include "C_FileParser.h"
#include "C_ErrorHandler.h"
#include "C_MISThread.h"
#include "C_ThreadCollector.h"

class C_Instruction;
class C_FileParser;
class C_ErrorHandler;
class C_ThreadCollector;
class MIS
{
    public:
        MIS();
        ~MIS();
        void   Run(vector<string>*P_InstructVec,ostringstream* P_Out,ostringstream* P_Error);   /** Parses files, adds labels, checks syntaxes and executes **/
        void   Run(int P_Start, int V_End, int P_ID = -1);
        void   F_SetError(bool state);              /** Modifies error state **/
        void   F_SetPC(int num);                    /** Alters the Program Counter **/
        void   F_AddLabels();                       /** Adds labels to the Labels Map **/
        int    F_GetPC();                           /** Returns Instruction Number **/
        void   F_ReportError();                     /** Writes error to .err file **/
        void   F_SetLabelError();
        /** Check if variable exists **/
        bool   F_NumericVExists(string variableName);
        bool   F_RealVExists   (string variableName);
        bool   F_CharVExists   (string variableName);
        bool   F_StringVExists (string variableName);
        /** Get Variable Value **/
        int    F_GetNumericV(string variableName);
        double F_GetRealV   (string variableName);
        char   F_GetCharV   (string variableName);
        string F_GetStringV (string variableName);
        /** Set Variable Value **/
        void   F_SetNumericV(string variableName, int    value);
        void   F_SetRealV   (string variableName, double value);
        void   F_SetCharV   (string variableName, char   value);
        void   F_SetStringV (string variableName, string value, int p_size);
        /** Sets and gets a CHAR in a STRING **/
        void   F_SetStringChar (string variableName, int index, char character);
        char   F_GetStringChar (string variableName, int index);
        /** Gets the maximum size of a STRING **/
        int    F_GetStringSize(string variableName);
        /** Returns the MainParser object **/
        C_FileParser* F_GetMainParser();
        /** Checks if label exists and gets its line number **/
        bool F_LabelExists(string label);
        int  F_LabelLine  (string label);
        void F_SetLabel   (string label, int line);
        /** Explicit Locking and Locking **/
        bool F_Lock(string variableName, int P_ID);
        bool F_Unlock(string variableName, int P_ID);
        /** Writes to Out stream **/
        void F_WriteToOut (string variableName, char type = 'A');
        string V_FileName = "Machine";
        /** Out and Error streams **/
        ostringstream *V_OutStream;
        ostringstream *V_ErrorStream;

    private:
        /** Labels Map **/
        map<string,int> LabelsMap;
        /** Variables Map **/
        map<string, C_NUMERIC*> NumericMap;
        map<string,    C_REAL*>    RealMap;
        map<string,    C_CHAR*>    CharMap;
        map<string,  C_STRING*>  StringMap;
        /** Map of Instructions **/
        map<string,C_Instruction*> InstrucionsMap;
        vector <C_MISThread *> ThreadVector;
        /** Program Counter **/
        int  V_PC;
        int  V_FileSize;
        int  V_EOF;
        atomic<bool> error;
        bool V_LabelError;
        /** Error line and error message **/
        int  V_ErrorLine;
        string V_ErrorMessage;
        /** Main Parser **/
        C_FileParser *MainParser;
        /** Thread Collector to keep track of MISThreads **/
        C_ThreadCollector *V_ThreadCollector;
        /** Out stream mutex **/
        pthread_mutex_t V_OutMutex;
        //SHAIMOU2A *SHOSHO;
};

#endif // MIS_H
