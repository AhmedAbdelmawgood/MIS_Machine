#ifndef C_MUL_H
#define C_MUL_H
#include "MIS.h"

#define MAX_OPERANDS_NO 13
#define MIN_OPERANDS_NO 3

#ifdef MULGUARD
    extern "C" C_Instruction * F_GetInstruction();
#endif

class MIS;

/**A child of C_Instruction**/
class C_MUL : public C_Instruction
{
    public:
        C_MUL(MIS *mis, int &P_PC = def);
        /**Pure Virtual in the parent class**/
        void F_CheckSyntax();
        void F_Execute();
        /** puts the result value in a specified variable**/
        void F_SetResult();
        C_Instruction * F_Clone(MIS *mis, int &P_PC);
        ~C_MUL();

    private:
        /** Variable name to store the result**/
        string V_VariableName;
        double V_Result;

};

#endif // C_MUL_H
