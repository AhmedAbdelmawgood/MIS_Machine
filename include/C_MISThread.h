#include "includes.h"
#include "Thread.h"
#include "TCPSocket.h"
#include "MIS.h"
#include<bits/stdc++.h>

#ifndef C_MISTHREAD_H
#define C_MISTHREAD_H

/** A descendant of Thread **/
class C_MISThread : public Thread
{
    public:
        C_MISThread(MIS *mis, int P_Start, int P_End);
        /** Main thread body that serves the thread **/
        void * threadMainBody (void * arg);
        /** Set the next pointer: used by the Thread Collector **/
        void setNextThread(C_MISThread * thread);
        /** Get a pointer to the next thread **/
        C_MISThread * getNextThread ();
        /** Gets MISThread ID **/
        int F_GetID();
        /** Resets static ID in MISThread to 0 after all threads terminate **/
        static void F_ResetIDs();
        /** Starts an MIS thread and sets the core its running on **/
        void F_StartThread();
        virtual ~C_MISThread();

    private:
        /** MIS Machine object **/
        MIS *V_Machine;
        /** ID Tracker **/
        static int id;
        /** Line to start executing from **/
        int V_Start = 0;
        /** Line to end executing at **/
        int V_End   = 0;
        /** Thread id **/
        int V_ID;
        /** A way to build a linked list of connections for the thread collector to be able to track the threads **/
        C_MISThread * next_thread;
};

#endif // C_MISTHREAD_H
