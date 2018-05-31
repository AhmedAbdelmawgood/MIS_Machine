#include "C_Client.h"

C_Client::C_Client(char * P_Address, int P_Port)
{
    V_Socket = new TCPSocket(P_Address,P_Port);
    /** Failed to create TCP socket **/
    if ( V_Socket == NULL ){
        V_ErrorMessage = "Error creating a new TCP Socket/n";
        F_WriteError();
    }
}

C_Client::~C_Client()
{
    if(V_Socket!=0) delete V_Socket;
}

/** Opens MIS file to read from it **/
bool C_Client::F_OpenFile(string P_FileName){
    V_MisFile.open(P_FileName);
    /** Failed to load file**/
    if(V_MisFile.fail()){
        V_ErrorMessage = "Failed to open file/n";
        F_WriteError();
        return false;
    }
    /** Incorrect file name **/
    if(P_FileName.length() < 5 || P_FileName.substr(P_FileName.length()-4,4) !=".mis"){
        V_ErrorMessage = "Incorrect Input File Extension\n";
        F_WriteError();
        return false;
    }
    F_ParseLines();
    return true;
}

/** Appends Lines to V_Lines vector **/
void C_Client::F_ParseLines(){
    string V_Line;
    while(getline(V_MisFile,V_Line)){
        if(V_Line != "\n" && V_Line != "\r" && V_Line != "\n\r" && V_Line != "\r\n" ){
            V_Lines.push_back(V_Line);
        }
    }
}

/** Sends Instruction vector to Server one by one **/
void C_Client::F_SendToServer(){
    for(auto &it : V_Lines){
        int bytes = V_Socket->writeToSocket(it.c_str(),1024);
        if (bytes != 1024){
            V_ErrorMessage = "Some bytes were lost./n";
            F_WriteError();
            return;
        }
    }
    V_Socket->writeToSocket("STOP",1024);
}

/** Receives from server OUT,ERR streams **/
void C_Client::F_ReceiveFromServer(char Type = 'n'){
    char InBuffer[1024];
	int V_ByteNumber = V_Socket->readFromSocket(InBuffer,1024);
	fstream V_File;
    switch (Type){
    case 'o':
        V_File.open("Machine.out", fstream::out);
        V_File << InBuffer;
        V_File.close();
        break;

    case 'e':
        V_File.open("Machine.err", fstream::out);
        V_File << InBuffer;
        V_File.close();
        break;
    }
}

/** Writes Client specific errors to client.err **/
void C_Client::F_WriteError(){
    fstream ErrorFile;
    ErrorFile.open("Client.err", fstream::out);
    ErrorFile << V_ErrorMessage;
    ErrorFile.close();
    exit(0);
}

int main(int argc, char *argv[]){

    if(argc!=4){
        fstream ErrorFile;
        ErrorFile.open("Client.err", fstream::out);
        ErrorFile << "Required : client_misvm <server IP address> <server port> distributed_parallel_hello.mis";
        ErrorFile.close();
        return 0;
    }
    regex ipValid("\\d+.\\d+.\\d+.\\d+");
    regex validPort("\\d+");
    string ipParam( argv[1] ) ;
    if(!regex_match(ipParam,ipValid)){
        perror("invalid ip");
        return 0;
    }
    string portParam( argv[2] ) ;
    if(!regex_match(portParam,validPort)){
        perror("invalid Port");
        return 0;
    }
    /** Creating a client with address and a port number **/
    C_Client *FirstClient = new C_Client(argv[1],stoi(argv[2]));

    /** Checks that the file has been successfully opened and parsed **/
    if (!FirstClient->F_OpenFile(argv[3])) return 0;

    /** Send Instruction by Instruction to Server **/
    FirstClient->F_SendToServer();
    /** Receive out **/
    FirstClient->F_ReceiveFromServer('o');
    /** Receive err **/
    FirstClient->F_ReceiveFromServer('e');

    delete FirstClient;

    return 1;
}
