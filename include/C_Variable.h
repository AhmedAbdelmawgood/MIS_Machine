#ifndef C_VARIABLE_H
#define C_VARIABLE_H
#include <bits/stdc++.h>
#include "includes.h"

using namespace std;
class C_Variable
{
    public:
        C_Variable();
        void F_Lock(int P_ID);
        void F_Unlock(int P_ID);
        virtual ~C_Variable();
    private:
        atomic<bool> V_Locked;
        atomic <int> V_LockerID;
        pthread_mutex_t V_VariableMutex;
    protected:
        pthread_mutex_t V_UpdateMutex;

};

#endif // C_VARIABLE_H
