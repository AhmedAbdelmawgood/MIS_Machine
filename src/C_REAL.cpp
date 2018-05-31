#include "C_REAL.h"

C_REAL::C_REAL(double P_Var) :  V_Value(P_Var){}

double C_REAL::F_GetValue(){
    pthread_mutex_lock (&V_UpdateMutex);
	pthread_mutex_unlock (&V_UpdateMutex);
    return V_Value;
}

void C_REAL::F_SetValue(double P_Value){
    pthread_mutex_lock (&V_UpdateMutex);
    V_Value = P_Value;
    pthread_mutex_unlock (&V_UpdateMutex);
}

char C_REAL::F_GetType(){
    return 'R';
}

C_REAL::~C_REAL(){}
