#ifndef C_ADD_H
#define C_ADD_H
#include "MIS.h"

#define MAX_OPERANDS_NO 13
#define MIN_OPERANDS_NO 3

#ifdef ADDGUARD
    extern "C" C_Instruction * F_GetInstruction();
#endif

class MIS;

/**A child of C_Instruction**/
class C_ADD : public C_Instruction
{
    public:
        C_ADD(MIS *mis, int &P_PC  = def);
        /**Pure Virtual in the parent class**/
        void F_CheckSyntax();
        void F_Execute();
        /** puts the result value in a specified variable**/
        void F_SetResult();
        C_Instruction * F_Clone(MIS *mis, int &P_PC);
        ~C_ADD();

    private:

        /** Variable name to store the result**/
        string V_VariableName;
        double V_Result;

};

#endif // C_ADD_H
