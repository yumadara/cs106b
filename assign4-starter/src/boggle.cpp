// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "boggle.h"
#include "gridlocation.h"
#include "grid.h"
#include "set.h"
#include "lexicon.h"
#include "testing/SimpleTest.h"
using namespace std;


int points(string str)
{
    // TODO your code here
        if (str.length() < 4)
        {
            return 0;
        }
        return str.length()-3;
        //return 0;
}

void scoreBoardhelper(Grid<char>& board, Lexicon& lex, Vector<GridLocation> vec, Vector<char>& choosen, Vector<int>& score, string sofar)
{
    if ( lex.contains(sofar)){
        int point = points(sofar);
        score.add(point);
    }
    if (lex.containsPrefix(sofar))
    {
        GridLocation loc = vec.back();
        for (GridLocation nbr: loc.neighbors())
        {

            if ((nbr.col>-1) && (nbr.row >-1) && nbr.row<board.numRows() && nbr.col< board.numCols())
            {
                int row_for_nbr = nbr.row;
                int col_for_nbr= nbr.col;
                char nbr2char = board[row_for_nbr][col_for_nbr];

                string nbr2str = "";
                nbr2str+= nbr2char;

                // check if it is a marked grid
                if (!choosen.contains(nbr2char))
                {
                     choosen.add(nbr2char);
                     vec.add(nbr);
                    string check = sofar + nbr2str;
                    if (lex.containsPrefix(check))
                     {
                        scoreBoardhelper(board, lex, vec, choosen, score, check);
                    }
                    else
                    {
                        choosen.removeBack();
                    }
                }

            }

    }
    }
    else
    {
        for (GridLocation loc : board.locations())
        {

            char loc2char = board[loc.row][loc.col];

            string loc2str = "";
            loc2str+=loc2char;

            choosen.add(loc2char);
            vec.add(loc);

            sofar = loc2str;

           for (GridLocation nbr: loc.neighbors())
           {

               if ((nbr.col>-1) && (nbr.row >-1) && nbr.row<board.numRows() && nbr.col< board.numCols())
               {
                   int row_for_nbr = nbr.row;
                   int col_for_nbr= nbr.col;
                   char nbr2char = board[row_for_nbr][col_for_nbr];

                   string nbr2str = "";
                   nbr2str+= nbr2char;

                   // check if it is a marked grid
                   if (!choosen.contains(nbr2char))
                   {
                        choosen.add(nbr2char);
                        vec.add(nbr);
                       string check = sofar + nbr2str;
                       if (lex.containsPrefix(check))
                        {
                           scoreBoardhelper(board, lex, vec, choosen, score, check);
                       }
                       else
                       {
                           choosen.removeBack();
                       }
                   }

               }

           }
        }
    }



}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
int scoreBoard(Grid<char>& board, Lexicon& lex)
{
        Vector<int> score;
        Vector<char> choosen;
        Vector<GridLocation> vec;
        int sum = 0;
        scoreBoardhelper(board, lex, vec, choosen, score,"");
        while (score.size() > 0) {

            sum+= score.pop_front();
        }

        return sum;
}

/* * * * * * Test Cases * * * * * */

/* Test helper function to return shared copy of Lexicon. Use to
 * avoid (expensive) re-load of word list on each test case. */
Lexicon& sharedLexicon()
{
    static Lexicon lex("res/EnglishWords.txt");
    return lex;
}

PROVIDED_TEST("Load shared Lexicon, confirm number of words")
{
    Lexicon lex = sharedLexicon();
    EXPECT_EQUAL(lex.size(), 127145);
}

PROVIDED_TEST("Test point scoring") {
    EXPECT_EQUAL(points("and"), 0);
    EXPECT_EQUAL(points("quad"), 1);
    EXPECT_EQUAL(points("quint"), 2);
    EXPECT_EQUAL(points("sextet"), 3);
    EXPECT_EQUAL(points("seventh"), 4);
    EXPECT_EQUAL(points("supercomputer"), 10);
}
/*
PROVIDED_TEST("Test scoreBoard, board contains no words, score of zero") {
    Grid<char> board = {{'B','C','D','F'}, //no vowels, no words
                        {'G','H','J','K'},
                        {'L','M','N','P'},
                        {'Q','R','S','T'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 0);
}


PROVIDED_TEST("Test scoreBoard, board contains one word, score of 1") {
    Grid<char> board = {{'C','_','_','_'},
                        {'Z','_','_','_'},
                        {'_','A','_','_'},
                        {'_','_','R','_'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 1);
}

PROVIDED_TEST("Test scoreBoard, alternate paths for same word, still score of 1") {
    Grid<char> board = {{'C','C','_','_'},
                        {'C','Z','C','_'},
                        {'_','A','_','_'},
                        {'R','_','R','_'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 1);
}
*/
PROVIDED_TEST("Test scoreBoard, small number of words in corner of board") {
    Grid<char> board = {{'L','I','_','_'},
                        {'M','E','_','_'},
                        {'_','S','_','_'},
                        {'_','_','_','_'}};
    Set<string> words = {"SMILE", "LIMES", "MILES", "MILE", "MIES", "LIME", "LIES", "ELMS", "SEMI"};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()),  2 + 2 + 2 + 1 + 1 + 1 + 1 + 1 + 1);
}

PROVIDED_TEST("Test scoreBoard, full board, small number of words") {
    Grid<char> board = {{'E','Z','R','R'},
                        {'O','H','I','O'},
                        {'N','J','I','H'},
                        {'Y','A','H','O'}};
    Set<string> words = { "HORIZON", "OHIA", "ORZO", "JOHN", "HAJI"};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 4 + 1 + 1 + 1 + 1);
}

PROVIDED_TEST("Test scoreBoard, full board, medium number of words") {
    Grid<char> board = {{'O','T','H','X'},
                        {'T','H','T','P'},
                        {'S','S','F','E'},
                        {'N','A','L','T'}};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 76);
}

PROVIDED_TEST("Test scoreBoard, full board, large number of words") {
    Grid<char> board = {{'E','A','A','R'},
                        {'L','V','T','S'},
                        {'R','A','A','N'},
                        {'O','I','S','E'}};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 234);
}
