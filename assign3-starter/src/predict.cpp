// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include "predict.h"
#include "lexicon.h"
#include "set.h"
#include "testing/SimpleTest.h"
using namespace std;


// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
void predictHelper(string digits, Set<string>& suggestions, Lexicon& lex, string sofar,
                   int index_digits, int index_str, Map<int,string> keypad)
{
    if(digits.length()==0){

    }
    else{
        int num = digits[index_digits]-'0';
        string str = keypad[num];
        if (index_digits< digits.length()){

        if( index_str < str.length()){
            sofar = sofar+ str[index_str];
            if (lex.containsPrefix(sofar)){
                if (lex.contains(sofar)){
                    suggestions.add(sofar);
                }
            }
            index_str++;

        predictHelper(digits, suggestions, lex, sofar, index_digits, index_str, keypad);

        }
        index_digits++;
        predictHelper(digits, suggestions, lex, sofar, index_digits, 0, keypad);
        }
    }
}
void predict(string digits, Set<string>& suggestions, Lexicon& lex, string sofar)
{
    Map<int, string> keypad = {{2,"abc"}, {3,"def"}, {4,"ghi"}, {5,"jkl"},
                               {6,"mno"}, {7,"pqrs"},{8,"tuv"}, {9,"wxyz"}};
      // TODO your code here
    // whichever of those letter sequqences that is a valid word according to the Lexicon is added to the set of suggestions
    predictHelper( digits, suggestions, lex, sofar, 0,0, keypad);

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

