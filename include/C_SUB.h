#ifndef C_SUB_H
#define C_SUB_H
#include "MIS.h"

#define NO_OF_OPERANDS 3

#ifdef SUBGUARD
    extern "C" C_Instruction * F_GetInstruction();
#endif

class MIS;

class C_SUB : public C_Instruction
{
    public:
        C_SUB(MIS *mis, int &P_PC = def);
        /**Pure Virtual in the parent class**/
        void F_CheckSyntax();
        void F_Execute();
        /** puts the result value in a specified variable**/
        void F_SetResult();
        C_Instruction * F_Clone(MIS *mis, int &P_PC);
        virtual ~C_SUB();

    private:
        /** Variable name to store the result**/
        string V_VariableName;
        double V_Result;

};

#endif // C_SUB_H
