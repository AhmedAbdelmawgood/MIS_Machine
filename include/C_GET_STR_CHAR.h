#ifndef C_GET_STR_CHAR_H
#define C_GET_STR_CHAR_H
#include "MIS.h"
#include "C_ErrorHandler.h"

#ifdef GETGUARD
    extern "C" C_Instruction * F_GetInstruction();
#endif

class MIS;

/**A child of C_Instruction**/
class C_GET_STR_CHAR : public C_Instruction
{
    public:
        C_GET_STR_CHAR(MIS *mis, int &P_PC = def);
        /**Pure Virtual in the parent class**/
        void F_CheckSyntax();
        void F_Execute();
        C_Instruction * F_Clone(MIS *mis, int &P_PC);
        virtual ~C_GET_STR_CHAR();
    private:

};

#endif // C_GET_STR_CHAR_H
