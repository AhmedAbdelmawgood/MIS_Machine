#include "C_CHAR.h"

C_CHAR::C_CHAR(char P_Var) :  V_Value(P_Var){}

char C_CHAR::F_GetValue(){
	 pthread_mutex_lock (&V_UpdateMutex);
	 pthread_mutex_unlock (&V_UpdateMutex);
    return V_Value;
}

void C_CHAR::F_SetValue(char P_Value){
    pthread_mutex_lock (&V_UpdateMutex);
    V_Value = P_Value;
    pthread_mutex_unlock (&V_UpdateMutex);
}

char C_CHAR::F_GetType(){
    return 'C';
}

C_CHAR::~C_CHAR(){}
