#ifndef C_JMPGT_H
#define C_JMPGT_H

#include "MIS.h"

#ifdef JMPGTGUARD
    extern "C" C_Instruction * F_GetInstruction();
#endif

class MIS;

/**A child of C_Instruction**/
class C_JMPGT : public C_Instruction
{
    public:
        C_JMPGT(MIS *mis, int &P_PC = def);
        /**Pure Virtual in the parent class**/
        void F_CheckSyntax();
        void F_Execute();
        C_Instruction * F_Clone(MIS *mis, int &P_PC);
        ~C_JMPGT();
};

#endif // C_JMPGT_H
