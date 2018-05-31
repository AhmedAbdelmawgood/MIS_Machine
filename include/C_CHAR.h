#ifndef C_CHAR_H
#define C_CHAR_H

#include "bits/stdc++.h"
#include "C_Variable.h"

using namespace std;

/** A descendant of C_Variable **/
class C_CHAR : public C_Variable
{
    public:
        C_CHAR(char P_Var);
        /** Gets CHAR variable's value **/
        char  F_GetValue();
        /** Sets CHAR variable's value **/
        void  F_SetValue(char P_Value);
        /** Returns type of the variable **/
        char  F_GetType();
        virtual ~C_CHAR();

    private:
        /** Value of CHAR variable **/
        char V_Value;
};

#endif // C_CHAR_H
