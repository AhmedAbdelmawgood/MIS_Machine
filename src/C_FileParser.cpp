#include "C_FileParser.h"
#include "C_ErrorHandler.h"

C_FileParser::C_FileParser(vector<string> *P_Lines): V_Lines(P_Lines){
    ParseLines();
}

/** Creates a new instance of C_ErrorHandler and reports the error**/
void C_FileParser::F_ReportError(){
    C_ErrorHandler error(V_ErrorMessage);
    error.C_WriteError();
    return;
}
/** Gets the number of lines in the file **/
int C_FileParser::GetFileSize(){
    return FileSize;
}
string C_FileParser::trimString(string token){
    string Token = token;
    size_t endpos = Token.find_last_not_of(" \t");
    size_t startpos = Token.find_first_not_of(" \t");
    Token = Token.substr( 0, endpos+1 );
    Token = Token.substr( startpos );
    return Token;
}
/** Parses line by line to the LineInstructs **/
void C_FileParser::ParseLines(){
    /** Variable to store each line **/
    string line;
    int lineSize = 0;
    /** Did not reach end of file**/
    //cout<<(*V_Lines).size();
    for(int i = 0; i < (*V_Lines).size() ;i++){
        line = (*V_Lines)[i];
        if(line.length() > 1024){
            V_ErrorMessage = "Maximum Number of Characters exceeded\n";
            F_ReportError();
            return;
        }
        /**In Case of indentation, it'll ignore spaces**/
        size_t StartIndex,EndIndex;
        if(line.find_first_not_of(" \t") == string::npos)continue;
        /**Finds first non whitespace character**/
        if((StartIndex = line.find_first_not_of(" ")) != string::npos){
            if((EndIndex = line.find(" ",StartIndex)) != string::npos){
                /** Vector to store Instruction and parameters **/

                vector<string> *InstrcVec = new vector<string>;
                /** whole instruction without indentation**/
                InstrcVec->push_back(line.substr(StartIndex));
                string Instruction = line.substr(StartIndex,EndIndex-StartIndex);
                /** Function name **/
                InstrcVec->push_back(Instruction);
                StartIndex = EndIndex+1;
                while((EndIndex=line.find(",",StartIndex))!=string::npos){
                    /** parameter by parameter**/

                    string Token = trimString( line.substr(StartIndex,EndIndex-StartIndex) );/*Triming leading and lagging spaces*/
                    InstrcVec->push_back(Token);
                    StartIndex=EndIndex+1;
                }
                string fullLine = "";
                for(int i = 1;i< InstrcVec->size();i++){
                   fullLine += (*InstrcVec)[i] + ( (i==1) ? " "  : ",");
                }
                /**Last parameter**/
                string lastParmToken = trimString(line.substr(StartIndex));
                InstrcVec->push_back( lastParmToken );
                fullLine+= lastParmToken;
                (*InstrcVec)[0] = fullLine; //reconstruct the full line paramtmer on the perfect form
                /** Push vector to LineInstructs**/
                LinesInstrcts.push_back(InstrcVec);
            }else{
                vector<string> *InstrcVec = new vector<string>;
                /** whole instruction without indentation**/
                InstrcVec->push_back(line);
                /** Function name **/
                InstrcVec->push_back(trimString(line));
                LinesInstrcts.push_back(InstrcVec);
            }
        }
        lineSize++;
    }
    FileSize = lineSize;
}

C_FileParser::~C_FileParser(){
    for(auto &it:LinesInstrcts){
        delete it;
    }
}
