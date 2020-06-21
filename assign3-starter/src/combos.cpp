// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>     // for cout, endl
#include <string>       // for string class
#include "error.h"
#include "set.h"
#include "warmup.h"     // for factorial
#include "combos.h"
#include "testing/SimpleTest.h"
using namespace std;

// Returns the number of ways to choose k things from a set of size N
// using the formula based on factorial. Because an int type can only hold
// value of factorial up to n = 12, this formula only works correctly for
// small values of n and k.
int combo_formula(int n, int k)
{
    return factorial(n)/(factorial(k)*factorial(n-k));
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
int count_combos(int n, int k)
{
    //TODO your code here
    if( n==k )
    {
        return 0;
    }
    else{

    }

    return 0;
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("Compare count_combos to combo_formula") {
    for (int i = 0; i < 25; i++) {
        int n = randomInteger(1, 12);
        int k = randomInteger(1, n);
        EXPECT_EQUAL(count_combos(n, k), combo_formula(n, k));
    }
}
