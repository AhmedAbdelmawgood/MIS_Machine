#ifndef C_FileParser_H
#define C_FileParser_H
//#include "MIS.h"
//#include "C_ErrorHandler.h"
#include<bits/stdc++.h>
using namespace std;

class MIS;
class C_ErrorHandler;
class C_FileParser
{
    public:
        C_FileParser(vector<string> *P_Lines);
        //C_FileParser(string FileName);
        C_FileParser();
        ~C_FileParser();
        void F_ReportError();
        void ParseLines();
        int GetFileSize();
        string trimString(string token);
        vector<string> * V_Lines;
        vector<vector<string>*> LinesInstrcts;


    protected:

    private:
//        ifstream InputFile;
        int FileSize;
        string V_ErrorMessage;

};


#endif // C_FileParser_H
