/*  --------------------------------------------------
Name: Emir
Surname: BALKAN
ID: 27787
 --------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "strutils.h"
#include <ctype.h>
using namespace std;

struct courseNode
{
  string courseCode, courseName;
  vector<int> studentsAttendingIDs;
  courseNode * next;
    
    courseNode() {}
    
    courseNode(string & CC, string & CN, courseNode* n) {
        courseCode = CC;
        courseName = CN;
        n = NULL;
    }
    
    void printVector(vector<int> & studentsAttendingIDs, string & choice) {
        if (choice == "0" || choice == "3") {
            sort(studentsAttendingIDs.begin(), studentsAttendingIDs.end());
            for (int k = 0; k < studentsAttendingIDs.size(); k++) {
                cout << studentsAttendingIDs[k] << " ";
            }
        }
        if (choice == "4") {
            int a = 0;
            for (int k = 0; k < studentsAttendingIDs.size(); k++) {
                a++;
                
            }
            if (a < 3) {
                cout << "-> This course will be closed";
            }
            else {
                for (int k = 0; k < studentsAttendingIDs.size(); k++) {
                    cout << studentsAttendingIDs[k] << " ";
                }
            }
        }
       
    }
    /*  -----------SORT LINKED LIST (NOT WORKING)-----------*/
    
    /*courseNode* sortlinkedlist(courseNode* h) {
        courseNode* i;
        courseNode* k;
        i = h->next;
        k = i;
        
        while (k != NULL) {
            cout << h->courseName[0] << "   " << i->courseName[0] << endl;
            if (i->courseName[0] > h->courseName[0]) {
                h = h->next;
                i = i->next;
                k = k->next;
            }
            else {
                h->next = i->next;
                i->next = h;
               
                i = h;
                h = k;
                k = i;
                
                cout << h->courseName[0] << "   " << i->courseName[0] << endl;
                
                
                h = h->next;
                i = i->next;
                k = k->next;
               
                
            }
          
        }
        return h;
       
    }*/
    /*  -----------SORT LINKED LIST (NOT WORKING)-----------*/
    
    /*  -----------PRINTING LINKED LIST--------------------*/
    void print(courseNode* h, string & choice){
        if (h == NULL) {
            cout << "List is empty" << endl;
        }
        else {
            //h = sortlinkedlist(h);
            while (h != NULL) {
                /*  ----------CHOICE 0 or 3 DO NOT DROP LESS THAN 3 ID COURSES-------*/
                if (choice == "0" || choice == "3") {
                    cout << h->courseCode << " ";
                    cout << h->courseName << ": ";
                    printVector(h->studentsAttendingIDs, choice);
                    cout << endl;
                    h = h->next;
                }
                /*  ----------CHOICE 0 or 3 DO NOT DROP LESS THAN 3 ID COURSES-------*/
                
                /*  ----------CHOICE 4 DO DROP LESS THAN 3 ID COURSES-------*/
                if (choice == "4") {
                    cout << h->courseCode << " ";
                    cout << h->courseName << ": ";
                    printVector(h->studentsAttendingIDs, choice);
                    cout << endl;
                    h = h->next;
                }
                /*  ----------CHOICE 4 DO DROP LESS THAN 3 ID COURSES-------*/
              
              
            }
        }
    }
    /*  -----------PRINTING LINKED LIST--------------------*/
    
    
    /*  -----------REMOVING SAME NODES (IN TXT THERE ARE SAME NODES WITH SAME COURSENAMEs-----*/
    courseNode* removeNode(courseNode* h) {
        bool nextornot = true;
        courseNode* save_h;
        courseNode* d;
        courseNode* p;
        courseNode* b;
        d = h;
        p = h;
        b = h;
        save_h = h;
        if (h == NULL) {
            cout << "List is empty" << endl;
        }
        else {
            while (h !=NULL) {
                while (p != NULL) {
                    if (nextornot) {
                        p = p->next;
                        d = d->next;
                    }
                    nextornot = true;
                    if (p != NULL) {
                        if (p->courseCode == h->courseCode) {
                            p = p->next;
                            b->next = d->next;
                            delete d;
                            d = p;
                            nextornot = false;
                        }
                        if (nextornot) {
                            b = b->next;
                        }
                    }
                }
                h = h->next;
                d = h;
                p = h;
                b = h;
                nextornot = true;
            }
            h = save_h;
            d = h;
            p = h;
            b = h;
        }
        return h;
    }
    /*  -----------REMOVING SAME NODES (IN TXT THERE ARE SAME NODES WITH SAME COURSENAMEs-----*/
    
    /*--------------INSERTIING SPECIFIC ID--------------*/
    courseNode* insertID(courseNode* h, int & ID, string & CC, string & CN, bool & introduction, int & line_counter, int & line_counter2) {
        bool approve = true, dont_exist = true;
        courseNode* j = h;
        courseNode* n = h;
        courseNode* t = h;
        while (j != NULL) {
            if (j->courseCode == CC) {
                dont_exist = false;
                /*  ---------introduction: when the program first time comes here, it should push_back all ID because they are initial. */
                if (introduction) {
                    j->studentsAttendingIDs.push_back(ID);
                }
                else {
                    for (int k = 0; k < j->studentsAttendingIDs.size(); k++) {
                        if (j->studentsAttendingIDs[k] == ID) {
                            cout << "Student with id " << ID << " already is enrolled to " << CC << ". No action taken." << endl;
                            approve = false;
                            break;
                        }
                    }
                    if (approve) {
                        j->studentsAttendingIDs.push_back(ID);
                        cout << "Student with id "<< ID << " is enrolled to "<< CC << "." << endl;
                    }
                    approve = true;
                }
            }
            n = j;
            t = j;
            j = j->next;
           
        }
        /*  -----------IF COURSE DO NOT EXIST----------*/
        if (dont_exist) {
           
            n = new courseNode;
            t->next = n;
            t = t->next;
            t->courseCode = CC;
            t->courseName = CN;
            cout << CC << " does not exist in the list of Courses. It is added up." << endl;
            n->studentsAttendingIDs.push_back(ID);
            n->next = NULL;
            cout << "Student with id "<< ID << " is enrolled to "<< CC << "." << endl;
        }
        /*  -----------IF COURSE DO NOT EXIST----------*/
        
      
        j = h;
        t = h;
        n = h;
        return h;
    }
    /*--------------INSERTIING SPECIFIC ID--------------*/
    
    /*  -------------REMOVE SPECIFIC ID---------------*/
    courseNode* removeID(courseNode* h, int & ID, string & CC, string & CN, bool & introduction, int & line_counter, int & line_counter2) {
        bool approve = true;
        courseNode* j = h;
        courseNode* n = j;
        courseNode* t = j;
        while (j != NULL) {
            if (j->courseCode == CC) {
                if (introduction) {
                    j->studentsAttendingIDs.push_back(ID);
                }
                else {
                    for (int k = 0; k < j->studentsAttendingIDs.size(); k++) {
                        if (j->studentsAttendingIDs[k] == ID) {
                            if (j->studentsAttendingIDs.size() == 1) {
                                j->studentsAttendingIDs.clear();
                            }
                            j->studentsAttendingIDs.erase(remove(j->studentsAttendingIDs.begin(),   j->studentsAttendingIDs.end(), ID ),  j->studentsAttendingIDs.end());
                            cout << "Student with id "<< ID << " has dropped to "<< CC << "." << endl;
                           
                            approve = false;
                            break;
                        }
                    }
                    if (approve) {
                        
                        cout << "Student with id " << ID << " is not enrolled to " << CC << ", thus he can't drop that course." << endl;
                    }
                    approve = true;
                }
            }
            j = j->next;
        }
      
        j = h;
        t = h;
        n = h;
        return h;
    }
    /*  -------------REMOVE SPECIFIC ID---------------*/
    
    };

/*  ------------------IDinsertion: Decision of whether ID will be removed or inserted-----------------*/
courseNode* IDinsertion(ifstream & file, string & line, string & item, string & CC, string & CN, int & counter, int & ID, courseNode* h, bool  & info, int & line_counter, bool & introduction, bool & id_remove) {
    int line_counter2 = 0;
    while (getline(file, line)) {
        line_counter2++;
        stringstream s(line);
        while (s >> item) {
            if (counter == 0) {
                CC = item;
            }
            if (counter == 1) {
                CN = item;
            }
            if (counter > 1) {
                if (introduction) {
                    ID = atoi(item);
                    courseNode COURSENODE;
                    if (id_remove) {
                        h = COURSENODE.removeID(h, ID, CC, CN, introduction, line_counter, line_counter2);
                    }
                    else {
                        
                        h = COURSENODE.insertID(h, ID, CC, CN, introduction, line_counter, line_counter2);
                    }
                   
                }
                else if (info && line_counter2 > line_counter) {
                    ID = atoi(item);
                    courseNode COURSENODE;
                    if (id_remove) {
                        h = COURSENODE.removeID(h, ID, CC, CN, introduction, line_counter, line_counter2);
                    }
                    else {
                        
                        h = COURSENODE.insertID(h, ID, CC, CN, introduction, line_counter, line_counter2);
                    }
                   
                }
            }
            
            counter++;
        }
        counter = 0;
       
    }
    return h;
}
/*  ------------------IDinsertion: Decision of whether ID will be removed or inserted-----------------*/


/*  --------------------creatingLinkedList: All lines in TXT file becomes nodes here----------------*/
courseNode* creatingLinkedList(ifstream & file, string & line, string & CC, string & CN, bool & once, courseNode* n, courseNode* t, courseNode* h, bool & precaution, int & ID, int & counter, string & item, bool & introduction, bool & info, int & line_counter, bool & id_remove) {
    string choice = "0";
    while (getline(file, line)) {
        istringstream s(line);
        s >> CC >> CN;
        
        /*  ---------DO IT ONCE (for head)-----------*/
        if (once) {
            n = new courseNode;
            t = n;
            h = n;
            once = false;
            precaution = false;
        }
        /*  -----------DO IT ONCE (for head)----------*/
        
        if (precaution) {
            n = new courseNode;
            t->next = n;
            t = t->next;
            
        }
        precaution = true;
        
        n->courseCode = CC;
        n->courseName = CN;
       
    }//----END OF LOOP----//
    n->next = NULL;
    courseNode COURSENODE;
    h = COURSENODE.removeNode(h); // ---> Same nodes will be removed (look above)
    if (introduction) {
        cout << "The linked list is created." << endl;
        info = false;
        file.clear();
        file.seekg(0);
        h = IDinsertion(file, line ,item, CC, CN, counter, ID, h, info, line_counter, introduction, id_remove);
    }
    else {
        file.clear();
        file.seekg(0);
        h = IDinsertion(file, line ,item, CC, CN, counter, ID, h, info, line_counter, introduction, id_remove);
    }
   
    if (introduction) {
        cout << "The initial list is:" << endl;
        courseNode COURSENODE;
        COURSENODE.print(h, choice);
    }
    else {
        
    }
    return h;
    //COURSENODE.print(h);
}
/*  --------------------creatingLinkedList: All lines in TXT file becomes nodes here----------------*/



int main() {
    /*  ---------- DECLARATIONS --------------*/
    ifstream file;
    ofstream FILE;
    string filename = "coursesAndStudents.txt", line, CC, CN, item, choice, input_line, input, emptystring = "", emptystring2 = "", add_coursecode;
    bool once = true, precaution = true, introduction = true, info = true, id_remove = true;
    int ID, counter = 0, counter2 = 0, counter3 = 0, line_counter = 0;
    courseNode* h;
    courseNode* t;
    courseNode* n;
    /*  ------------ DECLARATIONS---------------*/
    
    
    /*  -----------------OPENING A FILE-------------*/
    //cout << "Please enter file name: ";
    //cin >> filename;
    file.open(filename.c_str());
    cout << "Successfully opened file " << filename << endl;
    /*  ----------------OPENING A FILE-----------------*/
    
    /*  -------------------LINE COUNTER : required because skip the lines that already processed in the functions. Only new lines which will be received are necessary.---------------*/
    while (getline(file, line)) {
        line_counter++;
    }
    file.clear();
    file.seekg(0);
    /*  -------------------LINE COUNTER : required because skip the lines that already processed in the functions. Only new lines which will be received are necessary.---------------*/
 
    
    /*  -----------------CREATING LINKED LIST---------------------*/
    id_remove = false; // ---> do not want remove ids in initial step.
    h = creatingLinkedList(file, line, CC, CN, once, n, t, h, precaution, ID, counter, item, introduction, info, line_counter, id_remove);
    /*  ------------------CREATING LINKED LIST------------------------*/
    
    
    /*  ----------------DECISION----------------*/
    cout << endl;
    cout << "Please select one of the choices:" << endl;
    cout << "1. Add to List" << endl;
    cout << "2. Drop from List" << endl;
    cout << "3. Display List" << endl;
    cout << "4. Finish Add/Drop and Exit" << endl;
    cin >> choice;
    /*  ----------------DECISION----------------*/
    while (choice != "4") {
        
        /*  -------------------ADD LIST----------------------*/
        if (choice == "1") {
            cout << "Give the student ID and the course names and course codes that he/she wants to add: " << endl;
            /*  ----------ADD LINE TO TXT FILE-----------*/
            ofstream file_out;
            file_out.open(filename, std::ios_base::app);// ---> (std::ios_base::app) :to reach end of the txt file.
            cin.ignore(); // ---> to recieve input in first step of loop.
            getline(cin, input_line);
            
            stringstream X(input_line);
            
                
            while (getline(X, input, ' ')) {
                
                counter2++;
                if (counter2 > 2) {
                    char ch = input[0], ch2 = input[4];
                    if (isalpha(ch) && isdigit(ch2)) {
                        emptystring = emptystring + "\n" + input + " "; // ---> puts \n between each input line.
                        continue;
                    }
                    else{
                        emptystring = emptystring + input + " ";
                    }
                }
                else {
                    emptystring = emptystring + input + " ";
                }
            }
        file_out << emptystring << endl; // ---> importing lines
        
        /*  ----------ADD LINE TO TXT FILE-----------*/
            
        file.clear();
        file.seekg(0);
      
        once = true;
        introduction = false;
        info = true;
        id_remove = false;
       
        /*  -------------ID INSERTION-------------------*/
        h = IDinsertion(file, line ,item, CC, CN, counter, ID, h, info, line_counter, introduction, id_remove);
        courseNode COURSENODE;
        //COURSENODE.print(h);
        /*  -------------ID INSERTION-------------------*/
        
        /*  -------------------ADD LIST-------------------------*/
        /*  ----------------DECISION----------------*/
        cout << endl;
        cout << "Please select one of the choices:" << endl;
        cout << "1. Add to List" << endl;
        cout << "2. Drop from List" << endl;
        cout << "3. Display List" << endl;
        cout << "4. Finish Add/Drop and Exit" << endl;
        cin >> choice;
        /*  ----------------DECISION----------------*/
        }
    if (choice == "2") {
        line_counter = 0;
        file.clear();
        file.seekg(0);
        
        /*  -------------------LINE COUNTER : required because skip the lines that already processed in the functions. Only new lines which will be received are necessary.---------------*/
        while (getline(file, line)) {
            line_counter++;
        }
        file.clear();
        file.seekg(0);
        /*  -------------------LINE COUNTER  : required because skip the lines that already processed in the functions. Only new lines which will be received are necessary.---------------*/

        cout << "Give the student ID and the course names and course codes that he/she wants to drop: " << endl;
        /*  ----------ADD LINE TO TXT FILE-----------*/
        ofstream file_out;
       
        file_out.open(filename, std::ios_base::app);// std::ios_base::app :to reach end of the txt file.
        cin.ignore();
        getline(cin, input_line);
        
        stringstream X(input_line);
        
            
        while (getline(X, input, ' ')) {
            
            counter3++;
            if (counter3 > 2) {
                char ch = input[0], ch2 = input[4];
                if (isalpha(ch) && isdigit(ch2)) {
                    emptystring2 = emptystring2 + "\n" + input + " ";
                    continue;
                }
                else{
                    emptystring2 = emptystring2 + input + " ";
                }
            }
            else {
                emptystring2 = emptystring2 + input + " ";
            }
        }
        file_out << emptystring2 << endl;
    /*  ----------ADD LINE TO TXT FILE-----------*/
        
        
    file.clear();
    file.seekg(0);
    once = true;
    introduction = false;
    info = true;
    id_remove = true;
        
 
    /*  -------------ID INSERTION-------------------*/
    h = IDinsertion(file, line ,item, CC, CN, counter, ID, h, info, line_counter, introduction, id_remove);
    courseNode COURSENODE;
    //COURSENODE.print(h);
    /*  -------------ID INSERTION-------------------*/
        
        
        
    /*  ----------------DECISION----------------*/
    cout << endl;
    cout << "Please select one of the choices:" << endl;
    cout << "1. Add to List" << endl;
    cout << "2. Drop from List" << endl;
    cout << "3. Display List" << endl;
    cout << "4. Finish Add/Drop and Exit" << endl;
    cin >> choice;
    /*  ----------------DECISION----------------*/
    }
        
        
    if (choice == "3") {
        cout << "The current list of course and the students attending them: " << endl;
        courseNode COURSENODE;
        COURSENODE.print(h, choice);
        /*  ----------------DECISION----------------*/
        cout << endl;
        cout << "Please select one of the choices:" << endl;
        cout << "1. Add to List" << endl;
        cout << "2. Drop from List" << endl;
        cout << "3. Display List" << endl;
        cout << "4. Finish Add/Drop and Exit" << endl;
        cin >> choice;
        /*  ----------------DECISION----------------*/
    }
    }
    cout << "The add/drop period is finished. Printing the final list of courses and students attending them." << endl;
    cout << "NOTE: Courses with less than 3 students will be closed this semester." << endl;
    courseNode COURSENODE;
    COURSENODE.print(h, choice);
    return 0;
}
