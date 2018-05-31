#include "C_STRING.h"

C_STRING::C_STRING(string P_Var, int P_Size) :  V_Value(P_Var), V_Size(10){}

string C_STRING::F_GetValue(){
	pthread_mutex_lock (&V_UpdateMutex);
	pthread_mutex_unlock (&V_UpdateMutex);
    return V_Value;
}

void C_STRING::F_SetValue(string P_Value, int p_size){
    pthread_mutex_lock (&V_UpdateMutex);
    V_Value = P_Value;
    V_Size  = p_size;
    pthread_mutex_unlock (&V_UpdateMutex);
}

char C_STRING::F_GetType(){
    return 'S';
}

void C_STRING::F_SetStrChar(int P_Index, char P_Char){
    pthread_mutex_lock (&V_UpdateMutex);
	V_Value[P_Index] = P_Char;
    pthread_mutex_unlock (&V_UpdateMutex);
}

int C_STRING::F_GetStrSize(){
    return V_Size;
}

char C_STRING::F_GetStrChar(int P_Index){
    pthread_mutex_lock (&V_UpdateMutex);
	pthread_mutex_unlock (&V_UpdateMutex);
    return V_Value[P_Index];
}

C_STRING::~C_STRING(){}
