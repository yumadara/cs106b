// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "grid.h"
#include "stack.h"
#include "vector.h"
#include "maze.h"
#include "mazegraphics.h"
#include "testing/SimpleTest.h"
#include "queue.h"
#include <set>
#include "map.h"
#include <math.h>

using namespace std;

// TODO: Add a function header comment here to explain the 
// behavior of the function and how you implemented this behavior
bool checkSolution(Grid<bool>& g, Stack<GridLocation> path)
{
    GridLocation exit = {g.numRows()-1,  g.numCols()-1};
    if (path.peek() != exit) {
        error("path does not end at exit");

    }
    // TODO: check rest of path is valid (see writeup)
    // if find a problem, call error() to report
    // if all checks out, return true

    GridLocation entry={0,0};

    set<GridLocation> check_set;

    while(!path.isEmpty()){

        GridLocation s=path.pop();

        int row=s.row;
        int col=s.col;
        // check if the path starts at the entry
        if (path.isEmpty()){
            if(row!=0 || col!=0){
                error("The path doesn't start at the entry");
            }
        }
        if (!path.isEmpty()){

            GridLocation temp=path.peek();

            int r=temp.row;
            int c=temp.col;
            double distance=pow(pow(row-r,2)+pow(col-c,2),0.5);
            if (distance!=1){
                error("Not one caridinal step from the next in path");
            }
        }
        // check if the path contains loop
        if (check_set.find(s)!=check_set.end()){
            error("The path contains loop.");
        }
        //check if the location is within the maze bound
        if(row>g.numRows()-1 || col>g.numCols()-1){
            error("This location is not within the maze bound.");
        }
        // check if the location is wall
        if(g[row][col]==false){
            error("This location is not an open corridor.");
        }
        // check with neighborhood
        check_set.insert(s);
    }

    return true;
}

/*
 * The given readMazeFile function correctly reads a well-formed
 * maze from a file. However, there are various malformed
 * inputs which it does not correctly handle. You are to add
 * complete error-checking so that the function is fully robust.
 * See writeup.
 */
bool readMazeFile(string filename, Grid<bool>& maze)
{
    ifstream in;

    if (!openFile(in, filename))
        error("Cannot open file named " + filename);

    Vector<string> lines;
    readEntireFile(in, lines);
    string lastLine = lines.removeBack(); // last line is solution if present

    int numRows = lines.size();        // rows is count of lines
    int numCols = lines[0].length();   // cols is length of line
    maze.resize(numRows, numCols);     // resize grid dimensions

    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            int num_col=lines[r].length();
            if (num_col!=numCols){
                error("Error! Each maze row is required to have same length as all the others!");
            }
            char ch = lines[r][c];
            if (ch == '@') {        // wall
                maze[r][c] = false;
            } else if (ch == '-') { // corridor
                maze[r][c] = true;
            }
            else{
                error("Error! The valid options for a location are open or wall. Anything else is an error!");
            }
        }
    }
    Stack<GridLocation> solution;
    istringstream istr(lastLine); // Stack read does its own error-checking
    if (istr >> solution) {// if successfully read
        return checkSolution(maze, solution);
    }
    return true; // else no solution; nothing more to check
 }

// TODO: Add a function header comment here to explain the 
// behavior of the function and how you implemented this behavior
Stack<GridLocation> solveMaze(Grid<bool>& maze)
{
    Stack<GridLocation> p;
    // TODO: your code here
    // create a queue of paths
    Queue<Stack<GridLocation>> queue;
    //MazeGraphics::highlightPath( p, "blue");
    GridLocation entry=GridLocation(0,0);
    p.push(entry);
    queue.enqueue(p);
    int Rows=maze.numRows();
    int Cols=maze.numCols();

    while(1)
    {
        Stack<GridLocation> path=queue.dequeue();
        Stack<GridLocation> copy_path=path;
        set<GridLocation> myset;
        while(!copy_path.isEmpty()){
            myset.insert(copy_path.pop());
        }



        int r=path.peek().row;
        int c=path.peek().col;

        // figure out if this current_path is "the path"

        // if the end of path is exit , then check the solution
        if(r==Rows-1 && c==Cols-1){
            p=path;
            return p;
            }

        // if the end of path is not exit, then add grid, which is not wall in that gird
        //into path
        if(r+1<Rows){
            if(maze[r+1][c]==true){

                GridLocation new_path_element=GridLocation(r+1,c);

                if(myset.find(new_path_element)==myset.end()){
                    Stack<GridLocation> copy=path;
                    copy.push(new_path_element); // a new path is created
                    queue.enqueue(copy);
                }

            }
        }
        if(c+1<Cols){
            if(maze[r][c+1]==true){
                GridLocation new_path_element=GridLocation(r,c+1);
                if(myset.find(new_path_element)==myset.end()){
                Stack<GridLocation> copy=path;
                copy.push(new_path_element); // a new path is created
                queue.enqueue(copy);
                }
            }
        }

        if(r-1>=0){
            if (maze[r-1][c]==true){
                GridLocation new_path_element=GridLocation(r-1,c);
                if(myset.find(new_path_element)==myset.end()){
                Stack<GridLocation> copy=path;
                copy.push(new_path_element); // a new path is created
                queue.enqueue(copy);
                }
            }
        }
        if(c-1>=0){
            if (maze[r][c-1]==true){
                GridLocation new_path_element=GridLocation(r,c-1);
                if(myset.find(new_path_element)==myset.end()){
                Stack<GridLocation> copy=path;
                copy.push(new_path_element); // a new path is created
                queue.enqueue(copy);
                }
            }
        }


    }
}
    //return p;




/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("Test readMazeFile on valid file 2x2.maze") {
    Grid<bool> g;

    EXPECT(readMazeFile("res/2x2.maze", g));
}

PROVIDED_TEST("Test readMaze on valid file 5x7.maze") {
    Grid<bool> g;

    EXPECT(readMazeFile("res/5x7.maze", g));
}

PROVIDED_TEST("readMazeFile on nonexistent file should raise an error") {
    Grid<bool> g;

    EXPECT_ERROR(readMazeFile("res/nonexistent_file", g));
}

PROVIDED_TEST("readMazeFile on malformed file should raise an error") {
    Grid<bool> g;

    EXPECT_ERROR(readMazeFile("res/malformed.maze", g));
}

PROVIDED_TEST("checkSolution on correct path") {
    Grid<bool> g = {{true, false}, {true, true}};
    Stack<GridLocation> soln = { {0 ,0}, {1, 0}, {1, 1} };

    EXPECT(checkSolution(g, soln));
}

PROVIDED_TEST("checkSolution on invalid path should raise error") {
    Grid<bool> g = {{true, false}, {true, true}};
    Stack<GridLocation> not_end_at_exit = { {1, 0}, {0, 0} };
    Stack<GridLocation> not_begin_at_entry = { {1, 0}, {1, 1} };
    Stack<GridLocation> go_through_wall = { {0 ,0}, {0, 1}, {1, 1} };
    Stack<GridLocation> teleport = { {0 ,0}, {1, 1} };

    EXPECT_ERROR(checkSolution(g, not_end_at_exit));
    EXPECT_ERROR(checkSolution(g, not_begin_at_entry));
    EXPECT_ERROR(checkSolution(g, go_through_wall));
    EXPECT_ERROR(checkSolution(g, teleport));
}


PROVIDED_TEST("solveMaze on file 5x7") {
    Grid<bool> g;
    readMazeFile("res/5x7.maze", g);
    Stack<GridLocation> soln = solveMaze(g);

    EXPECT(checkSolution(g,soln));
}

PROVIDED_TEST("solveMaze on file 21x37") {
    Grid<bool> g;
    readMazeFile("res/21x37.maze", g);
    Stack<GridLocation> soln = solveMaze(g);

    EXPECT(checkSolution(g,soln));
}
