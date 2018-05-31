#include "includes.h"
#include "Thread.h"
#include "TCPSocket.h"
#include "MIS.h"
#include<bits/stdc++.h>

// A class representing a single connection form a client
class Connection : public Thread //Inherit from Thread
{
    private:
        TCPSocket * V_Socket; // TCP Socket for communication with client
        Connection * next_connection;  // A way to build a linked list of connections for the garbage collector to be able to track them
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
    public:
        Connection(TCPSocket * p_tcpSocket); // Constructor: Set client connected TCP socket
        void * threadMainBody (void * arg);	// Main thread body that serves the connection
        void setNextConnection(Connection * connection); // Set the next pointer: used by the Garbage Collector
        Connection * getNextConnection (); // Get a pointer to the next connection

        bool F_ReceiveFromClient();
        void F_RunMIS();
        void F_SendToClient(char Type);
        void F_WriteError();
        ~Connection(); // Destructor
};

