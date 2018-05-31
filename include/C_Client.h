#ifndef C_CLIENT_H
#define C_CLIENT_H
#include "TCPSocket.h"
#include<bits/stdc++.h>

using namespace std;

class C_Client
{
    public:
        C_Client(char * P_Address, int P_Port);
        /** Opens MIS files in reading mode **/
        bool F_OpenFile(string P_FileName);
        /** Puts Instruction by Instruction in V_Lines **/
        void F_ParseLines();
        /** Send Instruction By Instruction to server **/
        void F_SendToServer();
        /** Receives from server out and error and write them to files **/
        void F_ReceiveFromServer(char Type);
        /** Writes Client specific errors to client.err **/
        void F_WriteError();
        ~C_Client();

    private:
        TCPSocket *V_Socket;
        /** Vector of instructions parsed from MIS files **/
        vector<string> V_Lines;
        /** Fstream of the MIS instructions file **/
        fstream V_MisFile;
        string V_ErrorMessage;

};

#endif // C_CLIENT_H
