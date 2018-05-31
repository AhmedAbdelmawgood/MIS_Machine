#ifndef C_STRING_H
#define C_STRING_H
#include "bits/stdc++.h"
#include "C_Variable.h"

using namespace std;

class C_STRING : public C_Variable
{
    public:
        C_STRING(string P_Var, int P_Size);
        string F_GetValue();
        void   F_SetValue(string P_Value, int p_size);
        char   F_GetType();
        void   F_SetStrChar(int P_Index, char P_Char);
        int    F_GetStrSize();
        char   F_GetStrChar(int P_Index);
        virtual ~C_STRING();

    private:
        string V_Value;
        int V_Size;
};

#endif // C_STRING_H
