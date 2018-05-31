#ifndef C_JMPLT_H
#define C_JMPLT_H

#include "MIS.h"

#ifdef JMPLTGUARD
    extern "C" C_Instruction * F_GetInstruction();
#endif

class MIS;

/**A child of C_Instruction**/
class C_JMPLT : public C_Instruction
{
    public:
        C_JMPLT(MIS *mis, int &P_PC = def);
        /**Pure Virtual in the parent class**/
        void F_CheckSyntax();
        void F_Execute();
        C_Instruction * F_Clone(MIS *mis, int &P_PC);
        ~C_JMPLT();


};

#endif // C_JMPLT_H
