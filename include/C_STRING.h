#ifndef C_STRING_H
#define C_STRING_H
#include "bits/stdc++.h"
#include "C_Variable.h"

using namespace std;

/** A descendant of C_Variable **/
class C_STRING : public C_Variable
{
    public:
        C_STRING(string P_Var, int P_Size);
        /** Gets STRING variable's value **/
        string F_GetValue();
        /** Sets STRING variable's value **/
        void   F_SetValue(string P_Value, int p_size);
        /** Returns type of the variable **/
        char   F_GetType();
        /** Changes a specific char in a string **/
        void   F_SetStrChar(int P_Index, char P_Char);
        /** Gets a specific char in a string **/
        char   F_GetStrChar(int P_Index);
        /** Gets the size of a string variable **/
        int    F_GetStrSize();
        virtual ~C_STRING();

    private:
        /** String Variable's value **/
        string V_Value;
        /** String Maximum size **/
        int V_Size;
};

#endif // C_STRING_H
