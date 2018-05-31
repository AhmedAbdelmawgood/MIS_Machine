#ifndef C_REAL_H
#define C_REAL_H

#include "bits/stdc++.h"
#include "C_Variable.h"

using namespace std;

/** A descendant of C_Variable **/
class C_REAL : public C_Variable
{
    public:
        C_REAL(double P_Var);
        /** Gets REAL variable's value **/
        double F_GetValue();
        /** Sets REAL variable's value **/
        void   F_SetValue(double P_Value);
        /** Returns type of the variable **/
        char   F_GetType();
        virtual ~C_REAL();

    private:
        /** Value of REAL variable **/
        double V_Value;
};

#endif // C_REAL_H
