#ifndef C_SET_STR_CHAR_H
#define C_SET_STR_CHAR_H
#include "C_ErrorHandler.h"
#include "MIS.h"

#ifdef SETGUARD
    extern "C" C_Instruction * F_GetInstruction();
#endif

class MIS;

/**A child of C_Instruction**/
class C_SET_STR_CHAR : public C_Instruction
{
    public:
        C_SET_STR_CHAR(MIS *mis, int &P_PC = def);
        /**Pure Virtual in the parent class**/
        void F_CheckSyntax();
        void F_Execute();
        C_Instruction * F_Clone(MIS *mis, int &P_PC);
        virtual ~C_SET_STR_CHAR();
};

#endif // C_SET_STR_CHAR_H
