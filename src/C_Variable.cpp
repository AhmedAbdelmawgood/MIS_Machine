#include "C_Variable.h"

C_Variable::C_Variable()
{
    /** For explicit locking **/
    pthread_mutex_init (&V_VariableMutex,NULL);
    /** For implicit locking **/
    pthread_mutex_init (&V_UpdateMutex,NULL);
    /** Locking thread ID **/
    V_LockerID = -1;
    /** Not locked yet **/
    V_Locked   = false;
 }

 /** Lock explicitly with an invoking thread **/
void C_Variable::F_Lock(int P_ID){
    pthread_mutex_lock(&V_VariableMutex);
    /** Locking thread ID **/
    V_LockerID = P_ID;
    /** Variable is now locked **/
    V_Locked   = true;
}

/** UnLock explicitly with an invoking thread **/
void C_Variable::F_Unlock(int P_ID){
    /** Check the thread is locked first **/
    if (V_Locked){
        /** Locking thread is the invoking one **/
        if (P_ID == V_LockerID){
            pthread_mutex_unlock(&V_VariableMutex);
            /** set Locker ID to -1, variable is unlocked**/
            V_LockerID = -1;
        }
    }
}

C_Variable::~C_Variable(){
    /** destroy mutex **/
    pthread_mutex_destroy(&V_VariableMutex);
    pthread_mutex_destroy(&V_UpdateMutex);
}
