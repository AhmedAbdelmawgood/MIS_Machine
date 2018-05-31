#ifndef C_JMPGTE_H
#define C_JMPGTE_H

#include "MIS.h"

#ifdef JMPGTEGUARD
    extern "C" C_Instruction * F_GetInstruction();
#endif

class MIS;

/**A child of C_Instruction**/
class C_JMPGTE : public C_Instruction
{
    public:
        C_JMPGTE(MIS *mis, int &P_PC = def);
        /**Pure Virtual in the parent class**/
        void F_CheckSyntax();
        void F_Execute();
        C_Instruction * F_Clone(MIS *mis, int &P_PC);
        ~C_JMPGTE();

};

#endif // C_JMPGTE_H
