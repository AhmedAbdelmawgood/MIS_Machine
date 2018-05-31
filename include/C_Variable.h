#ifndef C_VARIABLE_H
#define C_VARIABLE_H
#include <bits/stdc++.h>
#include "includes.h"

using namespace std;
class C_Variable
{
    public:
        C_Variable();
         /** Lock explicitly with an invoking thread **/
        void F_Lock(int P_ID);
        /** UnLock explicitly with an invoking thread **/
        void F_Unlock(int P_ID);
        virtual ~C_Variable();
    private:
        /** Determines if a variable is locked or not **/
        atomic<bool> V_Locked;
        /** if variable is locked, stores locking thread ID, else stores -1 **/
        atomic <int> V_LockerID;
        /** Mutex for explicit locking **/
        pthread_mutex_t V_VariableMutex;
    protected:
        /** Mutex for implicit locking **/
        pthread_mutex_t V_UpdateMutex;


};

#endif // C_VARIABLE_H
