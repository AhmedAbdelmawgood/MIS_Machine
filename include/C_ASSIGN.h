#ifndef C_ASSIGN_H
#define C_ASSIGN_H
#include "MIS.h"
#ifdef ASSIGNGUARD
    extern "C" C_Instruction * F_GetInstruction();
#endif
class MIS;

/**A child of C_Instruction**/
class C_ASSIGN : public C_Instruction
{
    public:
        C_ASSIGN(MIS *mis, int &P_PC = def);
        /**Pure Virtual in the parent class**/
        void F_CheckSyntax();
        void F_Execute();

        bool F_CheckSemantics();
        C_Instruction * F_Clone(MIS *mis, int &P_PC);
        virtual ~C_ASSIGN();

    private:

        float value;
        string valueS="";
};

#endif // C_ASSIGN_H
