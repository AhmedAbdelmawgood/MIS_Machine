#ifndef C_NUMERIC_H
#define C_NUMERIC_H
#include "bits/stdc++.h"

#include "C_Variable.h"
using namespace std;

/** A descendant of C_Variable **/
class C_NUMERIC : public C_Variable
{
    public:
        C_NUMERIC(int P_Var);
        /** Gets NUMERIC variable's value **/
        int   F_GetValue();
        /** Sets NUMERIC variable's value **/
        void  F_SetValue(int P_Value);
        /** Returns type of the variable **/
        char  F_GetType();
        virtual ~C_NUMERIC();

    private:
        /** Value of NUMERIC variable **/
        int V_Value;
};

#endif // C_NUMERIC_H
