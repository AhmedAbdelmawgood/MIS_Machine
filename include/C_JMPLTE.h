#ifndef C_JMPLTE_H
#define C_JMPLTE_H

#include "MIS.h"

#ifdef JMPLTEGUARD
    extern "C" C_Instruction * F_GetInstruction();
#endif

class MIS;

/**A child of C_Instruction**/
class C_JMPLTE : public C_Instruction
{
    public:
        C_JMPLTE(MIS *mis, int &P_PC = def);
        /**Pure Virtual in the parent class**/
        void F_CheckSyntax();
        void F_Execute();
        C_Instruction * F_Clone(MIS *mis, int &P_PC);
        ~C_JMPLTE();

};

#endif // C_JMPLTE_H
