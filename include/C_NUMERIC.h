#ifndef C_NUMERIC_H
#define C_NUMERIC_H
#include "bits/stdc++.h"

#include "C_Variable.h"
using namespace std;

class C_NUMERIC : public C_Variable
{
    public:
        C_NUMERIC(int P_Var);
        int   F_GetValue();
        void  F_SetValue(int P_Value);
        char  F_GetType();
        virtual ~C_NUMERIC();

    private:
        int V_Value;
};

#endif // C_NUMERIC_H
