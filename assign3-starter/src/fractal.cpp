// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "fractal.h"
#include "error.h"
#include "testing/SimpleTest.h"
using namespace std;



/**
 * Fill a triangle defined by the corner GPoints one, two, and three.
 */
void fillBlackTriangle(GWindow& window, GPoint one, GPoint two, GPoint three) {
    window.setColor("black");
    window.fillPolygon( {one, two, three} );
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
void drawSierpinskiTriangle(GWindow& window, GPoint one, GPoint two, GPoint three, int order=3) {
   // TODO your code here
    if (order==0)
    {
        fillBlackTriangle(window, one, two, three);

    }
    else {
            GPoint new_two_1 = GPoint( one.getX()*0.5 + two.getX()*0.5, one.getY()*0.5 + two.getY()*0.5);
            GPoint new_three_1 = GPoint( one.getX()*0.5 + three.getX()*0.5, one.getY()*0.5 + three.getY()*0.5);
            fillBlackTriangle(window, one, new_two_1, new_three_1);

            GPoint new_one_2 = GPoint( one.getX()*0.5 + two.getX()*0.5, one.getY()*0.5 + two.getY()*0.5);
            GPoint new_three_2 = GPoint( two.getX()*0.5 + three.getX()*0.5, two.getY()*0.5 + three.getY()*0.5);
            fillBlackTriangle(window, new_one_2, two, new_three_2 );

            GPoint new_one_3 = GPoint( one.getX()*0.5 + three.getX()*0.5, one.getY()*0.5 + three.getY()*0.5);
            GPoint new_two_3 = GPoint( two.getX()*0.5 + three.getX()*0.5, two.getY()*0.5 + three.getY()*0.5);
            fillBlackTriangle(window, new_one_3, new_two_3, three);
            drawSierpinskiTriangle(window, one, new_two_1, new_three_1, order-1);
            drawSierpinskiTriangle(window, new_one_2, two, new_three_2, order-1);
            drawSierpinskiTriangle(window, new_one_3, new_two_3, three, order-1);



    }
}

/* * * * * * Test Cases * * * * * */

void runDemos();

PROVIDED_TEST("Test fractal drawing interactively using graphical demo") {
    runDemos();
}

