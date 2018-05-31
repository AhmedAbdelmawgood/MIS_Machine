#ifndef C_JMPNZ_H
#define C_JMPNZ_H
#include "MIS.h"

#ifdef JMPNZGUARD
    extern "C" C_Instruction * F_GetInstruction();
#endif

class MIS;

/**A child of C_Instruction**/
class C_JMPNZ : public C_Instruction
{
    public:
        C_JMPNZ(MIS *mis, int &P_PC = def);
        /**Pure Virtual in the parent class**/
        void F_CheckSyntax();
        void F_Execute();
        C_Instruction * F_Clone(MIS *mis, int &P_PC);
        ~C_JMPNZ();

};

#endif // C_JMPNZ_H
