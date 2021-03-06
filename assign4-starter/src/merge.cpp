// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "queue.h"
#include "testing/SimpleTest.h"
using namespace std;

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
bool mergeChecker(Queue<int> a){
    Queue<int> b=a;
    if (b.size()!=0)
    {
        int min=b.peek();
        while(b.size()!=0)
        {

            if(b.peek()< min){
                error("This queue is not sorted in order!");
                return false;
            }
            min = b.dequeue();

        }
    }

    return true;
}
Queue<int> merge(Queue<int> a, Queue<int> b)
{
    Queue<int> result;
    // TODO your code here
    if (mergeChecker(a) && mergeChecker(b)){
        while (a.size()!=0 && b.size()!=0){
            int ele = a.peek() > b.peek() ? b.dequeue() : a.dequeue();
            result.add(ele);
        }
        while (a.size()!=0)
        {
            result.add(a.dequeue());
        }
        while (b.size()!=0)
        {
            result.add(b.dequeue());
        }
}
    return result;
}

Queue<int> multiMerge(Vector<Queue<int>>& all)
{
    Queue<int> result;
    if (all.size()!=0) {
        for (Queue<int>& q : all) {
               result = merge(q, result);
        }
    }

    return result;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
Queue<int> recMultiMerge(Vector<Queue<int>>& all)
{
    Queue<int> result;
    // TODO your code here

    return result;
}


/* * * * * * Test Cases * * * * * */

Queue<int> createSequence(int size);
void distribute(Queue<int> input, Vector<Queue<int>>& all);

PROVIDED_TEST("Test binary merge, two short sequences") {
    Queue<int> a = {2, 4, 5};
    Queue<int> b = {1, 3, 3};
    Queue<int> expected = {1, 2, 3, 3, 4, 5};
    EXPECT_EQUAL(merge(a, b), expected);
    EXPECT_EQUAL(merge(b, a), expected);
}

PROVIDED_TEST("Test binary merge, two short sequences") {
    Queue<int> a = {2, 4, 5,7};
    Queue<int> b = {1, 3, 3,8, 10};
    Queue<int> expected = {1, 2, 3, 3, 4, 5, 7, 8, 10};
    EXPECT_EQUAL(merge(a, b), expected);
    EXPECT_EQUAL(merge(b, a), expected);
}


PROVIDED_TEST("Test multiMerge, small collection of short sequences") {
    Vector<Queue<int>> all = {{3, 6, 9, 9, 100},
                             {1, 5, 9, 9, 12},
                             {5},
                             {},
                             {-5, -5},
                             {3402}
                            };
    Queue<int> expected = {-5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402};
    EXPECT_EQUAL(multiMerge(all), expected);
}

PROVIDED_TEST("Test recMultiMerge by compare to multiMerge") {
    int n = 1000;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(n);
    distribute(input, all);
    EXPECT_EQUAL(multiMerge(all), recMultiMerge(all));
}

PROVIDED_TEST("Time binary merge operation") {
    int n = 1500000;
    Queue<int> a = createSequence(n);
    Queue<int> b = createSequence(n);
    TIME_OPERATION(a.size(), merge(a, b));
}

PROVIDED_TEST("Time multiMerge operation") {
    int n = 11000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), multiMerge(all));
}
PROVIDED_TEST("Time multiMerge operation") {
    int n = 90000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}


/* Test helper to fill queue with sorted sequence */
Queue<int> createSequence(int size)
{
    Queue<int> q;
    for (int i = 0; i < size; i++) {
        q.enqueue(i);
    }
    return q;
}

/* Test helper to distribute elements of sorted sequence across k sequences,
   k is size of Vector */
void distribute(Queue<int> input, Vector<Queue<int>>& all)
{
    while (!input.isEmpty()) {
        all[randomInteger(0, all.size()-1)].add(input.dequeue());
    }
}
