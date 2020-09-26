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
string operatorsOnlyhelper(string s, int index)
{
    string res;
    if (index == s.length())
    {
        return res;
    }
    else{
        if (s[index]=='('  || s[index]==')' || s[index]=='[' || s[index]==']' || s[index]=='{' ||s[index]=='}')
        {
            res+= s[index];
            index++;
            return res+operatorsOnlyhelper(s, index);

        }
        else{
            index++;
            return res + operatorsOnlyhelper(s, index);

        }
    }
    return res;
}
string operatorsOnly(string s)
{
    // TODO your code here
    // process the first character of the string and seee if it should be kept
    // recursively process the rest of the string

    return operatorsOnlyhelper(s, 0);


}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
bool checkOperatorshelper(string s, int index){
    if (s.length() ==0){
        return true;
    }
    else if (s.length() ==1)
    {
        return false;
    }
    else{
        if (index >-1 && index< s.length())
        {
            if (    (s[index] =='(' && s[index +1]== ')') ||
                        (s[index] =='[' && s[index +1]== ']') ||
                        (s[index] =='{' && s[index +1]== '}')
                         )
                {
                    s=s.erase(index,2);

                    return checkOperatorshelper(s, 0);
                }
                else{
                    index ++;
                    return checkOperatorshelper(s, index);
                }
        }
    }

    return false;
}
bool checkOperators(string s)
{
    // TODO your code here
    // string is empty

    return checkOperatorshelper(s, 0);
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
    EXPECT(checkOperators(only));
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
