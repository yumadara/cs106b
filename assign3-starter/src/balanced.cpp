// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "balanced.h"
#include "testing/SimpleTest.h"

using namespace std;

bool isBalanced(string str) {
    string ops = operatorsOnly(str);
    return checkOperators(ops);
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
string operatorsOnly(string s)
{
    // TODO your code here
    //string copy=s;
    if (s.length()==0)
    {
    }
    else{
        if(s[0]=='{' || s[0]=='}' ||s[0]=='(' ||s[0]==')' || s[0]=='[' ||s[0] == ']' )
        {
            string substring=s.substr(1,string::npos-1);
            s= s[0] + operatorsOnly(substring);
            return s;
        }
        else{
            string substring=s.substr(1,string::npos-1);
            s=operatorsOnly(substring);
            return s;
        }
    }
    return s;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
bool checkOperators(string s)
{
    // TODO your code here
    if (s.length()==0)
    {
        return true;
    }
    else if(s.length()==1)
    {
        return false;
    }
    else{
        for(int i=0; i<s.length()-1; i++)
        {
            if((s[i]== '(' && s[i+1] ==')') ||(s[i] =='{' && s[i+1] =='}') ||( s[i]=='[' && s[i+1]== ']'))
            {
                s.erase( s.begin()+i);
                s.erase( s.begin()+i);
                bool a = checkOperators( s);
                //break;
                return a;
            }

        }
        return false;
    }

}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("operatorsOnly on example from writeup")
{
    string example ="int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";

    string only = "(){([])(())}";
    EXPECT_EQUAL(operatorsOnly(example), only);
}

PROVIDED_TEST("checkOperators on example from writeup")
{
    string only = "(){([])(())}";
    //string only= "[](){][}";
    EXPECT(checkOperators(only));
}

PROVIDED_TEST("checkOperators on example from writeup")
{
    //string only = "(){([])(())}";
    string only= "[](){][}";
    EXPECT(!checkOperators(only));
}

PROVIDED_TEST("checkOperators on example from writeup")
{
    //string only = "(){([])(())}";
    //string only= "[](){][}";
    string only="([)";
    EXPECT(!checkOperators(only));
}

PROVIDED_TEST("checkOperators on example from writeup")
{
    //string only = "(){([])(())}";
    //string only= "[](){][}";
    string only="{(][][)}";
    EXPECT(!checkOperators(only));
}

PROVIDED_TEST("isBalanced on example from writeup")
{
    string example ="int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";
    EXPECT(isBalanced(example));
}

PROVIDED_TEST("isBalanced on illegal examples from writeup")
{
    EXPECT(!isBalanced("( ( [ a ] )"));
    EXPECT(!isBalanced("3 ) ("));
    EXPECT(!isBalanced("{ ( x } y )"));
}
