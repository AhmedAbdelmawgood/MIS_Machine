#ifndef C_INSTRUCTION_H
#define C_INSTRUCTION_H

#include "MIS.h"

class MIS;

/** Parent class of all instruction classes **/
class C_Instruction
{
    public:
        C_Instruction();
        /**Pure Virtual methods, must be implemented in descendant classes**/
        virtual void F_CheckSyntax() = 0;
        virtual void F_Execute    () = 0;
        virtual C_Instruction* F_Clone(MIS *mis, int &P_PC) = 0;
        /**Final method to be used by all classes**/
        virtual void F_ReportError() final;
        virtual ~C_Instruction();

    protected:
        static int def;
        /**An instance of MIS to access it**/
        MIS          *misInst;
        /**Instruction line broken into string vectors**/
        vector<string> *params;
        int *V_PC;
        /**Error line and message to be used by the ReportError method**/
        string V_ErrorMessage;
        int    V_ErrorLine;

    private:
};

#endif // C_INSTRUCTION_H
