#include "C_NUMERIC.h"

C_NUMERIC::C_NUMERIC(int P_Var) :  V_Value(P_Var){}

int C_NUMERIC::F_GetValue(){
    pthread_mutex_lock (&V_UpdateMutex);
	pthread_mutex_unlock (&V_UpdateMutex);
    return V_Value;
}

void C_NUMERIC::F_SetValue(int P_Value){
    pthread_mutex_lock (&V_UpdateMutex);
    V_Value = P_Value;
    pthread_mutex_unlock (&V_UpdateMutex);
    V_Value = P_Value;
}

char C_NUMERIC::F_GetType(){
    return 'N';
}

C_NUMERIC::~C_NUMERIC(){}
