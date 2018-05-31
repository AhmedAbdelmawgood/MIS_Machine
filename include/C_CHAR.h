#ifndef C_CHAR_H
#define C_CHAR_H

#include "bits/stdc++.h"
#include "C_Variable.h"

using namespace std;
class C_CHAR : public C_Variable
{
    public:
        C_CHAR(char P_Var);
        char  F_GetValue();
        void  F_SetValue(char P_Value);
        char  F_GetType();
        virtual ~C_CHAR();

    private:
        char V_Value;
};

#endif // C_CHAR_H
