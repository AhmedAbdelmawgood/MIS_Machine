#include "C_MISThread.h"
int C_MISThread::id = -1;

C_MISThread::C_MISThread(MIS *mis, int P_Start, int P_End) : Thread()
{
    V_Machine   = mis;
    /** Line to start executing from **/
    V_Start     = P_Start;
    /** Line to end executing before **/
    V_End       = P_End;
    /** pointer to the next MIS thread **/
    next_thread = NULL; // Set the next pointer to NULL
    /** Sets thread ID **/
    V_ID        = ++id;
}

/** Resets static ID in MISThread to 0 after all threads terminate **/
 void C_MISThread::F_ResetIDs(){
    /** sets id to -1 **/
    id = -1;
}

/** Starts an MIS thread and sets the core its running on **/
void C_MISThread::F_StartThread(){
    /** starts the thread main body **/
    start();
    /** Gets number of cores **/
    int cores = getCoreCount();
    /** sets the running thread to the specified core **/
    setToCore(V_ID% cores);
}

/** Gets MISThread ID **/
int C_MISThread::F_GetID(){
    return V_ID;
}

/** Thread mainbody **/
void * C_MISThread::threadMainBody (void * arg){	/** Main thread body that serves the thread **/
    /** Rund the MIS machine method Run with the starting line, ending line and thread ID **/
    V_Machine->Run(V_Start, V_End, V_ID);
}

/** Set the next pointer: used by the Garbage Collector **/
void C_MISThread::setNextThread(C_MISThread * thread){
    next_thread = thread;
}

/** Get a pointer to the next connection **/
C_MISThread * C_MISThread::getNextThread (){
    return next_thread;
}

C_MISThread::~C_MISThread(){
    cout << "LOL";
}
