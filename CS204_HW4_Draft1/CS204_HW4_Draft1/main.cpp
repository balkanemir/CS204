/*  --------Introduction-----------*/
// Name Surname: Emir Balkan
// No: 27787
// Submission date: 28.11.2021
/*  -------------------------------*/

// The header and cpp file which i have written were submitted.

// footnote: Please note that i wrote my code in Xcode on mac, so i do not have a chance to check whether it works in VS12.




#include "Stack_and_Queues.hpp"

void addInstructorRequest(serviceNode* h, InstructorQueue &InstructorQueue){
    InstructorStudentNode* NewInstructor;
    string func, i_name;
    int i_ID;
    bool exist_func = true;
    cout << "Add a service <function> that the instructor want to use:" << endl;
    cin >> func;
    /*  ---------Check whether the given function exist in the main linked list-----------*/
    while (h != NULL) {
        if (func == h->info) {
            exist_func = false;
            break;
        }
        h = h->next;
    }
    if (exist_func) {
        cout << "The requested service <function> does not exist." << endl << "GOING BACK TO PREVIOUS MENU";
    }
    else {
        cout << "Give instructor's name: "; cin >> i_name;
        cout << "Give instructor's ID <an int>: "; cin >> i_ID;
        /*  --------create an new instructor node and assign the given items into it-----------*/
        NewInstructor = new InstructorStudentNode;
        NewInstructor->name = i_name;
        NewInstructor->ID = i_ID;
        NewInstructor->function = func;
        /*  ---------Enqueue them----------*/
        InstructorQueue.enqueue(NewInstructor);
    }
}

void addStudentRequest(serviceNode* h, StudentsQueue &StudentsQueue) {
    InstructorStudentNode* NewStudent;
    string func, s_name;
    int s_ID;
    bool exist_func = true;
    cout << "Add a service <function> that the student want to use:" << endl;
    cin >> func;
    /*  ---------Check whether the given function exist in the main linked list-----------*/
    while (h != NULL) {
        if (func == h->info) {
            exist_func = false;
        }
        h = h->next;
    }
    if (exist_func) {
        cout << "The requested service <function> does not exist." << endl << "GOING BACK TO PREVIOUS MENU";
    }
    else {
        cout << "Give student's name: "; cin >> s_name;
        cout << "Give student's ID <an int>: "; cin >> s_ID;
        /*  --------create an new student node and assign the given items into it-----------*/
        NewStudent = new InstructorStudentNode;
        NewStudent->name = s_name;
        NewStudent->ID = s_ID;
        NewStudent->function = func;
        /*  ---------Enqueue them--------*/
        StudentsQueue.enqueue(NewStudent);
    }
}

void processARequest(string & functionName, serviceNode* h, SharedStack &SharedStack) {
    Node* j;
    serviceNode* save_h;
    save_h = h;
    
    string currentCommand, command, what, anykey;
    while (h != NULL) {
        if (h->info == functionName) {
            j = h->nodes;
            while (j != NULL) {
                currentCommand = j->info;
                istringstream c(currentCommand);
                c >> command >> what;
                if (command == "define") {
                    SharedStack.push(currentCommand, functionName);
                    j = j->next;
                }
                else if (command == "call") {
                    currentCommand = j->info.substr(5,10);
                    h = save_h;
                    cout << "Calling " << what << " from " << functionName << endl;
                    processARequest(currentCommand, h, SharedStack);
                    j = j->next;
                }
                else {
                    SharedStack.PrintStack();
                    j = j->next;
                }
                
            }
            cout<< functionName << " is finished. Clearing the stack from it's data... " << endl;
            SharedStack.pop(functionName);
            cout << "Press any key to continue..." << endl;
            cin >> anykey;
            break;
        }
        h = h->next;
    }
}

void processARequest(serviceNode* h, InstructorQueue &InstructorQueue ,StudentsQueue &StudentsQueue, vector<InstructorStudentNode>* InstructorVectorPointer) {
    string function;
    SharedStack SharedStack;
    if (!InstructorQueue.isEmpty()) {
        for (int i = 0; i < InstructorQueue.numItems; i++) {
            function = (*InstructorVectorPointer)[i].function;
            cout << "Processing prof. " << (*InstructorVectorPointer)[i].name << "'s request <with ID " << (*InstructorVectorPointer)[i].ID << "> of serivce <function>:" << endl << (*InstructorVectorPointer)[i].function << endl << "-------------------------------------------------------------" << endl;
            processARequest(function, h, SharedStack);
        }
        cout << "GOING BACK TO MAIN MENU" << endl;
    }
    if(!StudentsQueue.isEmpty()) {
        for (int i = 0; i < StudentsQueue.numItems; i++) {
            cout << "Processing " << StudentsQueue.h->name << "'s request <with ID " << StudentsQueue.h->ID << "> of serivce <function>:" << endl << StudentsQueue.h->function << endl << "-------------------------------------------------------------" << endl;
            processARequest(StudentsQueue.h->function, h, SharedStack);
            StudentsQueue.h = StudentsQueue.h->next;
        }
        cout << "GOING BACK TO MAIN MENU" << endl;
    }
    else {
        cout << "Both instructor's and student's queue is empty.\nNo request is processed." << endl << "GOING BACK TO MAIN MENU" << endl;
    }
}

int main() {
        
    /*  --------DECLARATIONS------------*/
    
    string choice, filename;
    bool once = true;
    bool save_h_bool = true; // to save the head of initial linked list once.
    serviceNode* h; // head will stuck in first serviceNode (function node) through save_h_bool.
    serviceNode* n; // helps to create new Servicenode (which stores function name).
    serviceNode* t; // helps to bond new Servicenode to linked list.
    Node* nn = nullptr; // helps to create new command nodes.
    Node* tt = nullptr; // helps to bond new command nodes to previous one and also associated serviceNode
    /*  ----------Create new instructor vector----------*/
    vector<InstructorStudentNode>* InstructorVectorPointer = new vector<InstructorStudentNode>(10);
    /*  ---------Set initial values via constructors-------*/
    InstructorQueue InstructorQueue(InstructorVectorPointer);
    StudentsQueue StudentsQueue;
    
    n = new serviceNode;
    h = n;
    t = n;
    serviceNode* save_h; // to save head.
    
    cout << "If you want to open a service <funtion> defining file, then press <Y/y> for 'yes', otherwise press any single key" << endl;
    cin >> choice;
    
    while (choice == "y" || choice == "Y") {
        ifstream file;
        cout << "Enter the input file name: ";
        cin >> filename;
        file.open(filename.c_str());
        if (file.fail()) {
            cout << "File could not be opened..." << endl;
            return 0;
        }
        else {
            once = true;
            h = createLinkList(once, n, t, nn, tt, file, h);
            if (save_h_bool) {
                save_h = h;
                save_h_bool = false;
            }
            
        }
        cout << "Do you want to open another service defining file? Press <Y/y> for 'yes', otherwise press any single key" << endl;
        cin >> choice;
        if (choice == "y" || choice == "Y") {
            // if user still wants to add input file, create a new service node for function and bond it to previous once; and reset the pointers which related to command nodes to construct them again to below of new service node.
            n = new serviceNode;
            t->next = n;
            t = n;
            tt = nullptr;
            nn = nullptr;
        }
        else {
            cout << "-------------------------------------------------------------------" << endl;
            cout << "PRINTING AVAILABLE SERVICES <FUNCTIONS> TO BE CHOSEN FROM THE USERS" << endl;
            cout << "-------------------------------------------------------------------" << endl;
            h = save_h;
            printLinkedlist(h);
            break;
        }
    }
        
    while (true){
        cout << endl;
        cout<<"**********************************************************************"<<endl
            <<"**************** 0 - EXIT PROGRAM                        *************"<<endl
            <<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST   *************"<<endl
            <<"**************** 2 - ADD A STUDENT SERVICE REQUEST       *************"<<endl
            <<"**************** 3 - SERVE (PROCESS) A REQUEST           *************"<<endl
            <<"**********************************************************************"<<endl;
            cout << endl;
            int option;
            cout << "Pick an option from above (int number from 0 to 3): "; cin>>option;
            switch (option)
            {
            case 0:
            cout<<"PROGRAM EXITING ... "<<endl; system("pause");
            exit(0);
                        case 1:
                                 addInstructorRequest(h, InstructorQueue); //h: initial linked list's head to check whether given function name to process is exist or not, InstructorQueue: Object of InstructorQueue, to be protect values which are set up via constructor.
                                break;
                        case 2:
                                 addStudentRequest(h ,StudentsQueue); //h: initial linked list's head to check whether given function name to process is exist or not, StudentsQueue: Object of StudentsQueue, to be protect values which are set up via constructor.
                                break;
                        case 3:
                                 processARequest(h, InstructorQueue, StudentsQueue, InstructorVectorPointer); //h: initial linked list's head to check whether given function name to process is exist or not, StudentsQueue: Object of StudentsQueue, to be protect values which are set up via constructor, InstructorQueue: Object of InstructorQueue, to be protect values which are set up via constructor, InstructorVectorPointer: to reach vector of Instructors(Instructor's Queue) and extract the nodes from it to use the values to process.
                                break;
                        default:
                            cout<<"INVALID OPTION!!! Try again"<<endl;
            }//switch
    }//while (true)
    return 0;
}
