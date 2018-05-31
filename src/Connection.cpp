#include "Connection.h"


//Constructor: Call parent Thread Constructor
Connection::Connection(TCPSocket * p_tcpSocket): Thread()
{
    V_Socket = p_tcpSocket; // Set the TCP socket
    next_connection = NULL; // Set the next pointer to NULL
}

/** Receives Instructions from client, and pass them to MIS, which passes them to FileParser **/
bool Connection::F_ReceiveFromClient(){
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
void Connection::F_RunMIS(){
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

/** Method that sends the out stream or the error stream to the client **/
void Connection::F_SendToClient(char Type){
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

/** Writes server specific errors to server.err **/
void Connection::F_WriteError(){
    fstream ErrorFile;
    ErrorFile.open("Connection.err", fstream::out);
    ErrorFile << V_ErrorMessage;
    ErrorFile.close();
}

void * Connection::threadMainBody (void * arg)
{
    while(true){

        bool tempor = F_ReceiveFromClient();
        
        /** No more instructions to receive **/
        if(!tempor){
            break;
        }
    }
    /** Runs the MIS machine with the V_Lines vector, OutBuffer and ErrorBuffer **/
    F_RunMIS();
    //MainServer->V_Machine->Run(&(MainServer->V_Lines),&(MainServer->V_OutBuffer),&(MainServer->V_ErrorBuffer));
    
    /** Send Out **/
    F_SendToClient('o');

    /** Send Err **/
    F_SendToClient('e');

    //Shutdown the Socket;

    V_Socket->shutDown();
}
// A modifier that sets the pointer of the next connection
void Connection::setNextConnection(Connection * connection){next_connection = connection;}
// A Selectot that returned a pointer to the next connection
Connection * Connection::getNextConnection (){return next_connection;}
// Destructor: delete the TCP socket if set
Connection::~Connection(){
    if ( V_Socket != NULL ) delete (V_Socket);
    if(V_Machine!= NULL)delete V_Machine;
    }
