#ifndef C_SERVER_H
#define C_SERVER_H
#include "TCPServerSocket.h"
#include "MIS.h"
#include<bits/stdc++.h>

using namespace std;

class C_Server
{
    public:
        C_Server(const char * P_Address, int P_Port, int P_Backlog );
        /** Receives from client, and pushes instruction to V_Lines **/
        bool F_ReceiveFromClient();
        /** Runs the MIS machine and passes V_Lines **/
        void F_RunMIS();
        /** Sends OutBuffer and ErrorBuffer to client **/
        void F_SendToClient(char Type);
        /** Writes Server specific errors to server.err **/
        void F_WriteError();
        /** V_TCPServerSocket getter **/
        TCPServerSocket * F_GetTCPServerSocket();
        /** V_Socket getter and setter **/
        void F_SetTCPSocket(TCPSocket* soc);
        TCPSocket* F_GetTCPSocket();
        ~C_Server();

    private:
        TCPServerSocket* V_TcpServerSocket;
        TCPSocket *V_Socket;
        /** MIS Machine object **/
        MIS *V_Machine;
        /** Vector of Instructions received from Client **/
        vector<string> V_Lines;
        /** Output buffer to send to client **/
        ostringstream V_OutBuffer;
        /** Error buffer to send to client **/
        ostringstream V_ErrorBuffer;
        /** Error message to be written to Server.err **/
        string V_ErrorMessage;

};

#endif // C_SERVER_H
