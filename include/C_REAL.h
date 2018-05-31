#ifndef C_REAL_H
#define C_REAL_H

#include "bits/stdc++.h"
#include "C_Variable.h"

using namespace std;

class C_REAL : public C_Variable
{
    public:
        C_REAL(double P_Var);
        double F_GetValue();
        void   F_SetValue(double P_Value);
        char   F_GetType();
        virtual ~C_REAL();

    private:
        double V_Value;
};

#endif // C_REAL_H
