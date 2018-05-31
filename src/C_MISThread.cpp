#include "C_MISThread.h"
int C_MISThread::id = -1;

C_MISThread::C_MISThread(MIS *mis, int P_Start, int P_End) : Thread()
{
    V_Machine   = mis;
    V_Start     = P_Start;
    V_End       = P_End;
    next_thread = NULL; // Set the next pointer to NULL
    V_ID        = ++id;
}

 void C_MISThread::F_ResetIDs(){
    id = -1;
}

void C_MISThread::F_StartThread(){
    start();
    int cores = getCoreCount();
    cout << "no of cores: "<< cores << endl;
    setToCore(V_ID% cores);
    cout << "set to core elamdulillah" << endl;
}

int C_MISThread::F_GetID(){
    return V_ID;
}
void * C_MISThread::threadMainBody (void * arg){	// Main thread body that serves the connection
    cout << V_ID << endl;
    V_Machine->Run(V_Start, V_End, V_ID);
}

void C_MISThread::setNextThread(C_MISThread * thread){ // Set the next pointer: used by the Garbage Collector
    next_thread = thread;
}

C_MISThread * C_MISThread::getNextThread (){ // Get a pointer to the next connection
    return next_thread;
}

C_MISThread::~C_MISThread(){}
