#include "includes.h"
#include "Thread.h"
#include "TCPSocket.h"
#include "MIS.h"
#include<bits/stdc++.h>

#ifndef C_MISTHREAD_H
#define C_MISTHREAD_H


class C_MISThread : public Thread
{
    public:
        C_MISThread(MIS *mis, int P_Start, int P_End);
        void * threadMainBody (void * arg);	// Main thread body that serves the connection
        void setNextThread(C_MISThread * thread); // Set the next pointer: used by the Garbage Collector
        C_MISThread * getNextThread (); // Get a pointer to the next connection
        int F_GetID();
        static void F_ResetIDs();
        void F_StartThread();
        virtual ~C_MISThread();

    private:
        /** MIS Machine object **/
        static int id;
        MIS *V_Machine;
        int V_Start = 0;
        int V_End   = 0;
        int V_ID;
        C_MISThread * next_thread;  // A way to build a linked list of connections for the garbage collector to be able to track the threads
};

#endif // C_MISTHREAD_H
