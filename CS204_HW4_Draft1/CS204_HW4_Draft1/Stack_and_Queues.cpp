#include "Stack_and_Queues.hpp"

/*  --------Declaration of vector pointer which is assigned in main function---*/
vector<InstructorStudentNode>* InstructorVectorPointer;


InstructorQueue::InstructorQueue() {};
    
InstructorQueue::InstructorQueue(vector<InstructorStudentNode>* InstructorVectorP) {
        QueueSize = 10;
        front = -1;
        rear = -1;
        numItems = 0;
        InstructorVectorPointer = InstructorVectorP;
    }
    
void InstructorQueue::enqueue(InstructorStudentNode* NewInstructor) {
        if (isFull()) {
            cout << "The Instructors' queue is full. " << NewInstructor->name << "'s request not enqueued." << endl;
        }
        else {
            rear = (rear + 1) % QueueSize;
            (*InstructorVectorPointer)[rear] = *NewInstructor;
            numItems++;
            cout << "Prof. " << NewInstructor->name << "'s service request of " << NewInstructor->function << " has been put in the instructor's queue." << endl << "Waiting to be served." << endl;
        }
    }
    
void InstructorQueue::dequeue(InstructorStudentNode* DeleteInstructor) {
        if (isEmpty()) {
            cout << "Attempting to dequeue on empty Instructor's queue, exiting program..." << endl;
            exit(1);
        }
        else {
            front = (front + 1) % QueueSize;
            *DeleteInstructor = (*InstructorVectorPointer)[front];
            numItems--;
        }
    }
    
bool InstructorQueue::isFull() const {
        if (numItems < QueueSize) {
            return false;
        }
        else {
            return true;
        }
    }
    
bool InstructorQueue::isEmpty() {
        if (numItems > 0) {
            return false;
        }
        else {
            return true;
        }
    }
    
void InstructorQueue::clear() {
        front = -1;
        rear = -1;
        numItems = 0;
        cout << "Instructors' queue cleared." << endl;
    }

StudentsQueue::StudentsQueue() {
        numItems = 0;
    }

void StudentsQueue::enqueue(InstructorStudentNode* NewStudent) {
    if (isEmpty()) {
        h = NewStudent;
        h->next = NULL;
        numItems++;
        cout << NewStudent->name << "'s service request of " << NewStudent->function << " has been put in the student's queue." << endl << "Waiting to be served.";
    }
    else {
        while (h->next != NULL) {
            h = h->next;
        }
        h->next = NewStudent;
        numItems++;
        cout << NewStudent->name << "'s service request of " << NewStudent->function << " has been put in the student's queue." << endl << "Waiting to be served.";
    }
}

void StudentsQueue::dequeue(InstructorStudentNode* DeleteStudent) {
    t = h->next;
    delete h;
    h = t;
}

bool StudentsQueue::isEmpty() {
    if (numItems > 0) {
        return false;
    }
    else {
        return true;
    }
}

void StudentsQueue::clear() {
    while (h == NULL) {
        t = h->next;
        delete h;
        h = t;
    }
    cout << "Students' queue cleared." << endl;
}

SharedStack::SharedStack() {
    top = NULL;
}

void SharedStack::push(string & functionitem, string &functionName) {
    StackNode* n;
    n = new StackNode;
    n->item = functionitem;
    n->functionname = functionName;
    if (isEmpty()) {
        top = n;
        n->next = NULL;
        h = n;
        bottom = h;
        bottom->next = NULL;
    }
    else {
        n->next = top;
        top->previous = n;
        top = n;
        top->previous = NULL;
    }
}

void SharedStack::pop(string &functionName) {
    StackNode* t;
    if (isEmpty()) {
        cout << "Stack is empty.";
    }
    else {
        while (top->functionname == functionName) {
            t = top->next;
            delete top;
            top = t;
            if (top != NULL) {
                top->previous = NULL;
            }
            else {
                break;
            }
        }
    }
}

bool SharedStack::isEmpty() {
    bool status;
    if (top == NULL) {
        status = true;
    }
    else {
        status = false;
    }
    return status;
}

void SharedStack::PrintStack() {
    cout << "PRINTING THE STACK TRACE:" << endl;
    if (isEmpty()) {
        cout << "The stack is empty." << endl;
    }
    else {
        while (bottom != NULL) {
            cout << bottom->functionname << ": " << bottom->item << endl;
            bottom = bottom->previous;
        }
        bottom = h;
    }
}

serviceNode* createLinkList(bool & once, serviceNode* n, serviceNode* t, Node* nn, Node* tt, ifstream & file, serviceNode* h) {
    string line;
    bool once2 = false;
    while (getline(file, line)) {
        line = line.substr(0, line.length() - 2);
        if (once2) {
            tt->info = line;
            nn = tt;
            once2 = false;
            continue;
        }
        if (once) {
            tt = new Node;
            n->info = line;
            n->nodes = tt;
            h = n;
            once = false;
            once2 = true;
        }
        else {
            nn = new Node;
            nn->info = line;
            tt->next = nn;
            tt = nn;
            nn->next = NULL;
        }
    }
    return h;
}

void printLinkedlist(serviceNode* h) { //prints initial linkedlist: Something is weird about this function because it sometimes give an error in running but everything works in debugging. If it does not work in running in first time, try again please. I think this situtation is associated with punctiation.
    Node* m = nullptr;
    while (h != NULL) {
        cout << h->info << ":" << endl;
        m = h->nodes;
        while (m != NULL) {
            cout << m->info;
            if (m->next != NULL) {
                cout << ", ";
            }
            m = m->next;
        }
        h = h->next;
        cout << "." << endl;
    }
}

