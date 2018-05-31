#include "C_REAL.h"

C_REAL::C_REAL(double P_Var) :  V_Value(P_Var){}

/** Gets REAL variable's value **/
double C_REAL::F_GetValue(){
    /** The lock is to check that no other thread is setting the value of the variable and acquire the lock **/
    pthread_mutex_lock (&V_UpdateMutex);
    /** Unlock the mutex to allow other getters **/
	pthread_mutex_unlock (&V_UpdateMutex);
    return V_Value;
}

/** Sets REAL variable's value **/
void C_REAL::F_SetValue(double P_Value){
    /** Mutex to ban any other thread from setting or getting the variable's value **/
    pthread_mutex_lock (&V_UpdateMutex);
    /** Set variable's value **/
    V_Value = P_Value;
    /** Unlock the mutex to allow other setters and getters **/
    pthread_mutex_unlock (&V_UpdateMutex);
}

/** Returns type of the variable **/
char C_REAL::F_GetType(){
    return 'R';
}

C_REAL::~C_REAL(){}
