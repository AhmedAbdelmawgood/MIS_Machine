#ifndef C_SLEEP_H
#define C_SLEEP_H

#include "MIS.h"

#ifdef SLEEPGUARD
    extern "C" C_Instruction * F_GetInstruction();
#endif

class MIS;

/**A child of C_Instruction**/
class C_SLEEP : public C_Instruction
{
    public:
        C_SLEEP(MIS *mis, int &P_PC = def);
        /**Pure Virtual in the parent class**/
        void F_CheckSyntax();
        void F_Execute();

        void F_WriteError(string errorScent);
        C_Instruction * F_Clone(MIS *mis, int &P_PC);
        ~C_SLEEP();

    protected:

    private:

};

#endif // C_SLEEP_H
