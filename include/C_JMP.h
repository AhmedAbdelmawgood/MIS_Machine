#ifndef C_JMP_H
#define C_JMP_H

#include "MIS.h"

#ifdef JMPGUARD
    extern "C" C_Instruction * F_GetInstruction();
#endif

class MIS;

/**A child of C_Instruction**/
class C_JMP : public C_Instruction
{
    public:
        C_JMP(MIS *mis, int &P_PC = def);
        /**Pure Virtual in the parent class**/
        void F_CheckSyntax();
        void F_Execute();
        C_Instruction * F_Clone(MIS *mis, int &P_PC);


        ~C_JMP();
    private:
};

#endif // C_JMP_H
