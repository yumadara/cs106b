#include "listnode.h"
#include "vector.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
 * TODO: Replace this comment with a descriptive function
 * header comment about your implementation of the function.
 */
void mergeSort(ListNode*& front) {
    /* TODO: Fill in this function. */
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment about your implementation of the function.
 */
void quickSort(ListNode*& front) {
    /* TODO: Fill in this function. */
}


/* * * * * * Test Code Below This Point * * * * * */

/* TODO: Write your own student tests below to test your sorting helper
 * functions and overall sorting algorithm correctness. We have provided
 * the skeleton of some tests below to help you get started with this
 * process.
 *
 * As part of this process, you are also strongly recommedned to fill in
 * the function prototypes we have defined below.
 */

/*
 * We have provided this helper function as a convenience. This
 * function traverses the linked list represented by the provided
 * front pointer and prints out the data stored in the list along
 * the way in a convenient format. You may find it to be helpful to
 * use this function as a debugging aid.
 */
void printList(ListNode* front) {
   cout << "{";
   while (front != nullptr) {
       cout << front->data;
       if (front->next != nullptr){
           cout << ", ";
       }
       front = front->next;
   }
   cout << "}" << endl;
}

/*
 * This helper function is provided a pointer to the front of the list
 * and is responsible for deallocating all of the memory being used
 * to store nodes in that list.
 */
void deallocateList(ListNode* front) {
    /* TODO: Fill in this function. */
}

/*
 * This helper function is provided a vector of integer values and
 * returns a pointer to the beginning of a linked list containing
 * those values in the specified order.
 */
ListNode* createList(Vector<int> values){
    /* TODO: Fill in this function. */
    return nullptr;
}

/*
 * This helper function is provided a vector of integer values
 * and a pointer to the beginning of a linked list. If these two structures
 * contain the same values in the same order, the function returns
 * true, otherwise it returns false.
 */
bool checkListVectorEquality(ListNode* front, Vector<int> v){
    /* TODO: Fill in this function. */
    return false;
}

STUDENT_TEST("This is a skeleton for what your overall student tests should look like."){
    /* Initialize the values and list for this test case. */
    Vector<int> values = {1, 2, 3, 4};
    ListNode* list = createList(values);

    /* Sort the linked list. */
    mergeSort(list);

    /* Sort the vector. */
    values.sort();

    /* Check to make sure that the list is now in the correct order. */
    EXPECT(checkListVectorEquality(list, values));

    /* Avoid memory leaks by deallocating list. */
    deallocateList(list);
}

PROVIDED_TEST("This tests some of the testing helper functions you are recommended to implement."){
    /* Creates a small test list containing the values 1->2->3. */
    ListNode* testList = nullptr;
    testList = new ListNode(3, testList);
    testList = new ListNode(2, testList);
    testList = new ListNode(1, testList);

    /* Test equality comparison function. */
    EXPECT(checkListVectorEquality(testList, {1, 2, 3}));
    EXPECT(!checkListVectorEquality(testList, {1, 2}));
    EXPECT(!checkListVectorEquality(testList, {1, 2, 3, 4}));
    EXPECT(!checkListVectorEquality(testList, {1, 3, 2}));

    /* Test create list function. */
    ListNode* studentList = createList({1, 2, 3, 4});
    printList(studentList);
    ListNode* cur = studentList;
    for (int i = 1; i <= 4; i++){
        EXPECT(cur != nullptr);
        EXPECT_EQUAL(cur->data, i);
        cur = cur->next;
    }

    /* Test deallocate list functions. There should be no memory leaks from this test. */
    deallocateList(studentList);
    deallocateList(testList);
}

/*
 * The provided test case demonstrates a comparsion between the same
 * algorithm (quicksort) operating on a linked list versus a vector.
 */
PROVIDED_TEST("Time linked list quicksort vs vector quicksort") {
    int startSize = 50000;

    for(int n = startSize; n < 10*startSize; n *= 2) {
        Vector<int> v;
        ListNode* list = nullptr;

        /* Insert the same random values into linked list and vector. */
        for (int i = 0; i < n; i++) {
            int val = randomInteger(-10000, 10000);
            v.add(val);
            list = new ListNode(val, list);
        }

        /* The vector values are currently in the reverse order than the
         * linked list values – let's fix that so we have a fair comparison. */
        v.reverse();

        /* NOTE: This test does not check correctness of the linked list sort
         * function. It only times the two operations to generate a comparison. */
        TIME_OPERATION(n, quickSort(list));
        TIME_OPERATION(n, v.sort());        /* Standard vector sort operation is backed
                                               with quicksort algorithm. */

        deallocateList(list);
    }
}

