#ifndef C_JMPZ_H
#define C_JMPZ_H

#include "MIS.h"

#ifdef JMPZGUARD
    extern "C" C_Instruction * F_GetInstruction();
#endif

class MIS;

/**A child of C_Instruction**/
class C_JMPZ : public C_Instruction
{
    public:
        C_JMPZ(MIS *mis, int &P_PC = def);
        /**Pure Virtual in the parent class**/
        void F_CheckSyntax();
        void F_Execute();
        C_Instruction * F_Clone(MIS *mis, int &P_PC);
        ~C_JMPZ();

};

#endif // C_JMPZ_H
