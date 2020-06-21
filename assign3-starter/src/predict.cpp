// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include "predict.h"
#include "lexicon.h"
#include "set.h"
#include "testing/SimpleTest.h"
using namespace std;


// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
void predict(string digits, Set<string>& suggestions, Lexicon& lex, string sofar)
{
    Map<int, string> keypad = {{2,"abc"}, {3,"def"}, {4,"ghi"}, {5,"jkl"},
                               {6,"mno"}, {7,"pqrs"},{8,"tuv"}, {9,"wxyz"}};
      // TODO your code here

}

/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("Predict intended words for digit sequence 6263, example from writeup") {
    string digits = "6263";
    Lexicon lex("res/EnglishWords.txt");
    Set<string> expected = {"name", "mane", "oboe"};
    Set<string> suggestions;

    predict(digits, suggestions, lex);
    EXPECT_EQUAL(suggestions, expected);
}

