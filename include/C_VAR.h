#ifndef C_VAR_H
#define C_VAR_H
#include "MIS.h"

#ifdef VARGUARD
    extern "C" C_Instruction * F_GetInstruction();
#endif

class MIS;
class C_VAR : public C_Instruction
{
    public:
        C_VAR(MIS *mis, int &P_PC = def);
        void F_CheckSyntax();
        void F_Execute();
        C_Instruction * F_Clone(MIS *mis, int &P_PC);
        virtual ~C_VAR();

    protected:

    private:
};

#endif // C_VAR_H
