#include "C_Variable.h"

C_Variable::C_Variable()
{
    pthread_mutex_init (&V_VariableMutex,NULL);
    pthread_mutex_init (&V_UpdateMutex,NULL);
    V_LockerID = -1;
    V_Locked   = false;
 }

void C_Variable::F_Lock(int P_ID){
    pthread_mutex_lock(&V_VariableMutex);
    V_LockerID = P_ID;
    V_Locked   = true;
}

void C_Variable::F_Unlock(int P_ID){
    if (V_Locked){
        if (P_ID == V_LockerID){
            pthread_mutex_unlock(&V_VariableMutex);
            V_LockerID = -1;
        }
    }
}

C_Variable::~C_Variable(){
    pthread_mutex_destroy(&V_VariableMutex);
    pthread_mutex_destroy(&V_UpdateMutex);
}
