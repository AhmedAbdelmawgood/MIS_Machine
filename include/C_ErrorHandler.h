#ifndef C_ERRORHANDLER_H
#define C_ERRORHANDLER_H
#include "MIS.h"

class MIS;
class C_ErrorHandler
{
    public:
        C_ErrorHandler(MIS *mis, int line, string message);
        C_ErrorHandler(string message);
        /** Writes the error to the .err file **/
        void C_WriteError();
        //static void F_INIT();
        virtual ~C_ErrorHandler();

    private:
        /** Error details **/
        string V_ErrorMessage;
        int    V_ErrorLine;
        MIS    *misInst;
        //static pthread_mutex_t V_ErrorMutex;
};

#endif // C_ERRORHANDLER_H
