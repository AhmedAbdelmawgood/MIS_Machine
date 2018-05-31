#ifndef C_OUT_H
#define C_OUT_H

#include "MIS.h"

#ifdef OUTGUARD
    extern "C" C_Instruction * F_GetInstruction();
#endif

class MIS;

/**A child of C_Instruction**/
class C_OUT : public C_Instruction
{
    public:
        C_OUT(MIS *mis, int &P_PC = def);
        /**Pure Virtual in the parent class**/
        void F_CheckSyntax();
        void F_Execute();
        C_Instruction * F_Clone(MIS *mis, int &P_PC);
        ~C_OUT();

};

#endif // C_OUT_H
