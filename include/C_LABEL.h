#ifndef C_LABEL_H
#define C_LABEL_H

#include "MIS.h"

#ifdef LABELGUARD
    extern "C" C_Instruction * F_GetInstruction();
#endif

class MIS;

/**A child of C_Instruction**/
class C_LABEL : public C_Instruction
{
    public:
        C_LABEL(MIS *mis, int &P_PC = def);
        /**Pure Virtual in the parent class**/
        void F_CheckSyntax();
        void F_Execute();
        C_Instruction * F_Clone(MIS *mis, int &P_PC);
        ~C_LABEL();

    protected:

    private:
};

#endif // C_LABEL_H
