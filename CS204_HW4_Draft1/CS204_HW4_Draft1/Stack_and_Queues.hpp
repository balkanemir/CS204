#ifndef Stack_and_Queues_hpp
#define Stack_and_Queues_hpp

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct InstructorStudentNode { //for storing of instructors and students' data.
    string name;
    int ID;
    string function;
    InstructorStudentNode* next;
};

struct Node { //for input's linked lists. (commands).
    string info;
    Node* next;
};

struct serviceNode { //for input's function name. (functions).
    string info;
    serviceNode* next;
    Node* nodes;
};

struct StackNode { // for stack's linkedlist.
    string item;
    string functionname;
    StackNode* next;
    StackNode* previous;
};


serviceNode* createLinkList(bool & once, serviceNode* n, serviceNode* t, Node* nn, Node* tt, ifstream & file, serviceNode* h); // for creating initial linkedlist.

void printLinkedlist(serviceNode* h); //for printing initial linked list.


class InstructorQueue { // origin: vector.
private:
    int QueueSize;
    int front;
    int rear;
    
public:
    int numItems; // it is public because it is used in processARequest function.
    InstructorQueue(); // default constructor
    InstructorQueue(vector<InstructorStudentNode>* InstructorVectorP);//constructor
    void enqueue(InstructorStudentNode* NewInstructor);//adds new instructor node to instructor vector by using instructor vector's pointer.
    void dequeue(InstructorStudentNode* DeleteInstructor); //deletes node from vector. (not using in this hw.)
    bool isFull() const; //check vector is full or not.
    bool isEmpty(); // check vector is empty or not.
    void clear(); // clears the vector. (not using)
};

class StudentsQueue { // origin: linkedlist.
private:
    InstructorStudentNode* t;
public:
    InstructorStudentNode* h; //head
    int numItems;
    StudentsQueue(); //default constructor.
    void enqueue(InstructorStudentNode* NewStudent); //adds a new node to student's linkedllist.
    void dequeue(InstructorStudentNode* DeleteStudent); //deletes nodes.
    bool isEmpty(); //check whether there is node in linked list (i.e. whether there is a head, or created linked list.)
    void clear();
};

class SharedStack { // origin: linkedlist.
private:
    StackNode* top;
    StackNode* bottom;
    StackNode* h;
public:
    SharedStack(); //default constructor
    void push(string & functionitem, string &functionName); //adds command of the input and input's function name. to stack.
    void pop(string &functionName); //deletes commands from stack when the related function ends.
    bool isEmpty(); //check whether stack is empty or not.
    void PrintStack(); //prints stack.
};


#endif
