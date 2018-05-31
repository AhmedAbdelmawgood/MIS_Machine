#include "C_ErrorHandler.h"

/** Constructor for MIS, C_Instruction and its descendants **/
C_ErrorHandler::C_ErrorHandler(MIS *mis, int line, string message) : misInst(mis),V_ErrorLine(line),V_ErrorMessage(message)
{
	//pthread_mutex_init (&V_ErrorMutex,NULL);
}
/** Constructor for FileParser class **/
C_ErrorHandler::C_ErrorHandler(string message) : V_ErrorLine(-1),V_ErrorMessage(message){
	//pthread_mutex_init (&V_ErrorMutex,NULL);
}

//void C_ErrorHandler::F_INIT(){
//	pthread_mutex_init (&V_ErrorMutex,NULL);
//}
void C_ErrorHandler::C_WriteError(){
    /** If error is in one of the instruction lines **/
    //pthread_mutex_lock(&V_ErrorMutex);
    if (V_ErrorLine >= 0){
    *(misInst->V_ErrorStream)<< "Error in line number: " << V_ErrorLine << "\n" << V_ErrorMessage << "\n";
    misInst->F_SetError(true);
    }
    /** Error is in parsing **/
    else if (V_ErrorLine < 0){
        *(misInst->V_ErrorStream) << V_ErrorMessage << "\n";
    }
    //pthread_mutex_lock(&V_ErrorMutex);
}

C_ErrorHandler::~C_ErrorHandler(){}

