#include "C_Server.h"

C_Server::C_Server(const char * P_Address, int P_Port, int P_Backlog)
{
    V_TcpServerSocket = new TCPServerSocket(P_Address,P_Port,P_Backlog);
    /** Failed to create TCP Server Socket **/
    if (V_TcpServerSocket == NULL){
        V_ErrorMessage = "Failed to create TCP Server Socket./n";
        F_WriteError();
        return;
    }
    V_TcpServerSocket->initializeSocket();
}

C_Server::~C_Server()
{
    if(V_TcpServerSocket!=0) delete V_TcpServerSocket;
    if(V_Machine!=0)         delete V_Machine;

}

/** A getter for V_TcpServerSocket **/
TCPServerSocket* C_Server::F_GetTCPServerSocket(){
    return V_TcpServerSocket;
}

/** A getter for V_Socket **/
TCPSocket* C_Server::F_GetTCPSocket(){
    return V_Socket;
}
/** A setter for V_Socket **/
void C_Server::F_SetTCPSocket(TCPSocket* soc){
    V_Socket = soc;
}

/** Method that sends the out stream or the error stream to the client **/
void C_Server::F_SendToClient(char Type){
    switch (Type){
        /** Out Stream **/
        case 'o':
            V_Socket->writeToSocket((V_OutBuffer.str()).c_str(),1024);
            return;
        /** Error Stream **/
        case 'e':
            V_Socket->writeToSocket((V_ErrorBuffer.str()).c_str(),1024);
            return;
    }
}

/** Receives Instructions from client, and pass them to MIS, which passes them to FileParser **/
bool C_Server::F_ReceiveFromClient(){
    /** To store instruction by instruction **/
    char InBuffer[1024];
	int V_ByteNumber = V_Socket->readFromSocket(InBuffer,1024);
	string temp = InBuffer;
	/** Check the end of instructions **/
	if(temp == "STOP") return 0;
	/** Line is not empty **/
	else if (temp != "") {
        /** Add instruction to V_Lines vector **/
        V_Lines.push_back(temp);
	}
    return true;
}

/** Runs the MIS machine **/
void C_Server::F_RunMIS(){
    /** Creating an instance of MIS machine **/
    V_Machine = new MIS();
    if (V_Machine == NULL){
        V_ErrorMessage = "Failed to load MIS machine./n";
        F_WriteError();
        return;
    }
    /** Running the machine **/
    V_Machine->Run(&(V_Lines),&(V_OutBuffer),&(V_ErrorBuffer));
}

/** Writes server specific errors to server.err **/
void C_Server::F_WriteError(){
    fstream ErrorFile;
    ErrorFile.open("Server.err", fstream::out);
    ErrorFile << V_ErrorMessage;
    ErrorFile.close();
}

int main(int argc, char *argv[]){
    /** Constructing a server with address, port number and backlog **/

    C_Server *MainServer = new C_Server("0.0.0.0",9888,100);

    /** Failed to create Server **/
    if (!MainServer){
        fstream ErrorFile;
        ErrorFile.open("Server.err", fstream::out);
        ErrorFile << "Failed to create Server./n";
        ErrorFile.close();
        return 0;
    }

    /** Get Connection (makes the 3 way handshake), returns a TCP socket **/
    TCPSocket *s= (MainServer->F_GetTCPServerSocket())->getConnection(15,10000,-1,-1);
    if(s==NULL){
        //cout << "TimeOut"
        return 0;
    }
	MainServer->F_SetTCPSocket(s);

    /** if Socket = NULL **/
    if (MainServer->F_GetTCPServerSocket() == NULL ){
        fstream ErrorFile;
        ErrorFile.open("Server.err", fstream::out);
        ErrorFile << "Could not get connection./n";
        ErrorFile.close();
        return 0;
    }

    /** Receiving from client instruction by instruction **/
    while(true){

        bool tempor = MainServer->F_ReceiveFromClient();

        /** No more instructions to receive **/
        if(!tempor){
            break;
        }
    }

    /** Runs the MIS machine with the V_Lines vector, OutBuffer and ErrorBuffer **/
    MainServer->F_RunMIS();
    //MainServer->V_Machine->Run(&(MainServer->V_Lines),&(MainServer->V_OutBuffer),&(MainServer->V_ErrorBuffer));

    /** Send Out **/
    MainServer->F_SendToClient('o');

    /** Send Err **/
    MainServer->F_SendToClient('e');

    delete MainServer;

    return 0;
}
