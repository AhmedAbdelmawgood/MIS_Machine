#ifndef C_DIV_H
#define C_DIV_H
#include "MIS.h"
#include "C_ErrorHandler.h"
#define NO_OF_OPERANDS 3
#ifdef DIVGUARD
    extern "C" C_Instruction * F_GetInstruction();
#endif

class MIS;

/**A child of C_Instruction**/
class C_DIV : public C_Instruction
{
    public:
        C_DIV(MIS *mis, int &P_PC = def);
        /**Pure Virtual in the parent class**/
        void F_CheckSyntax();
        void F_Execute();
        /** puts the result value in a specified variable**/
        void F_SetResult();
        C_Instruction * F_Clone(MIS *mis, int &P_PC);
        virtual ~C_DIV();

    private:
        /** Variable name to store the result**/
        string V_VariableName;
        double V_Result;
};

#endif // C_DIV_H
