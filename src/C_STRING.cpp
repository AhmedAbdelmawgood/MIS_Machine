#include "C_STRING.h"

C_STRING::C_STRING(string P_Var, int P_Size) :  V_Value(P_Var), V_Size(10){}

/** Gets STRING variable's value **/
string C_STRING::F_GetValue(){
    /** The lock is to check that no other thread is setting the value of the variable and acquire the lock **/
	pthread_mutex_lock (&V_UpdateMutex);
    /** Unlock the mutex to allow other getters **/
	pthread_mutex_unlock (&V_UpdateMutex);
    return V_Value;
}

/** Sets STRING variable's value **/
void C_STRING::F_SetValue(string P_Value, int p_size){
    /** Mutex to ban any other thread from setting or getting the variable's value **/
    pthread_mutex_lock (&V_UpdateMutex);
    /** Set variable's value **/
    V_Value = P_Value;
    V_Size  = p_size;
    /** Unlock the mutex to allow other setters and getters **/
    pthread_mutex_unlock (&V_UpdateMutex);
}

/** Returns type of the variable **/
char C_STRING::F_GetType(){
    return 'S';
}

/** Changes a specific char in a string **/
void C_STRING::F_SetStrChar(int P_Index, char P_Char){
    pthread_mutex_lock (&V_UpdateMutex);
	V_Value[P_Index] = P_Char;
    pthread_mutex_unlock (&V_UpdateMutex);
}

/** Gets the size of a string variable **/
int C_STRING::F_GetStrSize(){
    return V_Size;
}

/** Gets a specific char in a string **/
char C_STRING::F_GetStrChar(int P_Index){
    pthread_mutex_lock (&V_UpdateMutex);
	pthread_mutex_unlock (&V_UpdateMutex);
    return V_Value[P_Index];
}

C_STRING::~C_STRING(){}
