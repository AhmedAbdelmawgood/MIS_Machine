#include "C_NUMERIC.h"

C_NUMERIC::C_NUMERIC(int P_Var) :  V_Value(P_Var){}

/** Gets NUMERIC variable's value **/
int C_NUMERIC::F_GetValue(){
    /** The lock is to check that no other thread is setting the value of the variable and acquire the lock **/
    pthread_mutex_lock (&V_UpdateMutex);
    /** Unlock the mutex to allow other getters **/
	pthread_mutex_unlock (&V_UpdateMutex);
    return V_Value;
}

/** Sets NUMERIC variable's value **/
void C_NUMERIC::F_SetValue(int P_Value){
    /** Mutex to ban any other thread from setting or getting the variable's value **/
    pthread_mutex_lock (&V_UpdateMutex);
    /** Set variable's value **/
    V_Value = P_Value;
    /** Unlock the mutex to allow other setters and getters **/
    pthread_mutex_unlock (&V_UpdateMutex);
}

/** Returns type of the variable **/
char C_NUMERIC::F_GetType(){
    return 'N';
}

C_NUMERIC::~C_NUMERIC(){}
