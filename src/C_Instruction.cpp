#include "C_Instruction.h"

int C_Instruction::def = -1;
C_Instruction::C_Instruction(){}

C_Instruction::~C_Instruction(){}

/** Creates a new instance of C_ErrorHandler and reports the error**/
void C_Instruction::F_ReportError(){
    C_ErrorHandler error(misInst, V_ErrorLine, V_ErrorMessage);
    error.C_WriteError();
    return;
}
