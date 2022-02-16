/*  ------------INTRODUCTION-----------------
NAME, SURNAME: EMIR BALKAN
STUDENT ID: 27787
SUBMISSION DATE: 11.11.2021

- (BONUS) PART WAS DONE.
- NOT EVERY PART INCLUDE COMMENTS BECAUSE ROUGHLY SAME PROCESS ARE DONE. THEREFORE COMMENTS ADDED FOR MOST DETAILED PARTS CLEARLY. (ALSO TO AVOID TO INCREASE LINE COUNT.)
 ------------INTRODUCTION-----------------*/

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct busStop {
       string busStopName;
       busStop *left;
       busStop *right;
};
struct busLine {
       string busLineName;
       busLine *next;
       busStop *busStops;
};
 busLine* head = nullptr;

void processMainMenu(busLine* h);

void printMainMenu() {
    cout << endl;
    cout <<"I***********************************************I"<<endl <<"I 0 - EXIT PROGRAM I"<<endl
    <<"I 1 - PRINT LINES I"<<endl
    <<"I 2 - ADD BUS LINE I"<<endl
    <<"I 3 - ADD BUS STOP I"<<endl
    <<"I 4 - DELETE BUS LINE I"<<endl
    <<"I 5 - DELETE BUS STOP I"<<endl
    <<"I 6 - PATH FINDER I"<<endl <<"I***********************************************I"<<endl <<">>";
cout << endl;
}


void printBusLines(busLine* h, bool & only_one_line) {
    busStop* k;
    while (h != NULL ) {
        k = h->busStops;
        cout << h->busLineName << ": ";
        while (k != NULL) {
            cout << k->busStopName;
            if (k->right != NULL) {
                cout << " <-> ";
            }
            else {
                cout << endl;
            }
            k = k->right;
        }
        if (only_one_line) {
            break;
        }
        else {
            h = h->next;
        }
        
        
    }
   
}

busLine* check_same_busline(busLine* h, busLine* save_h, string & newbusline, bool & noerror) {
    while (h != NULL) {
        noerror = true;
        if (newbusline == h->busLineName) {
            cout << "Bus line already exists: enter a new one (0 for exit)" << endl;
            cin >> newbusline;
            h = save_h;
            noerror = false;
        }
        if (noerror) {
            h = h->next;
        }
    }
    h = save_h;
    return h;
}

busStop* check_same_busstop(busStop* k, busStop* save_k, string & newbusstop, bool & noerror) {
    while (k != NULL) {
        noerror = true;
        if (k->busStopName == newbusstop) {
            cout << "Bus stop already exists in the line" << endl;
            cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
            cin >> newbusstop;
            k = save_k;
            noerror = false;
        }
        if (noerror) {
            k = k->right;
        }
    }
    k = save_k;
    return k;
}


void addBusLine(busLine* h) {
    busLine* save_h = h;
    busLine* n;
    busStop* nn;
    busStop* tt;
    busStop* pp;
    busStop* k;
    busStop* save_k;
    bool once = true, noerror = true, only_one_line = true;
    string newbusline, newbusstop, y_n;
    cout << "Enter the name of the new bus line (0 for exit to main menu)." << endl;
    cin >> newbusline;
    if (newbusline == "0") {
        cout << "finish" << endl;
    }
    else {
        h = check_same_busline(h, save_h, newbusline, noerror);
        n = new busLine;
        k = n->busStops;
        save_k = k;
        n->busLineName = newbusline;
        cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
        cin >> newbusstop;
        k = check_same_busstop(k, save_k, newbusstop, noerror);
        while (newbusstop != "0") {
            if (once) {
                nn = new busStop;
                tt = nn;
                pp = nn;
                n->busStops = nn;
                k = nn;
                save_k = k;
                tt->busStopName = newbusstop;
                tt->left = NULL;
                once = false;
                cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
                cin >> newbusstop;
                k = check_same_busstop(k, save_k, newbusstop, noerror);
            }
            else {
                nn = new busStop;
                tt->right = nn;
                tt = nn;
                tt->busStopName = newbusstop;
                tt->right = NULL;
                tt->left = pp;
                pp = nn;
                cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
                cin >> newbusstop;
                k = check_same_busstop(k, save_k, newbusstop, noerror);
            }
        }
    }
    cout << "The bus line information is shown below" << endl;
    printBusLines(n, only_one_line);
    cout << "Are you sure? Enter (y/Y) for yes (n/N) for no?" << endl;
    cin >> y_n;
    if (y_n == "Y" || y_n == "y") {
        while (h->next != NULL) {
            h = h->next;
        }
        h->next = n;
    }
    h = save_h;
    printBusLines(h, only_one_line = false);
    
}

void addBusStop(busLine* h) {
    /*---------DECLARATIONS---------------*/
    string busline, newbusstop, prevbusstop;
    busStop* k;
    busStop* save_k;
    busStop* t;
    busStop* nn;
    busLine* save_h;
    bool only_one_line = true, no_busline = true, no_prev_busstop = true, no_exist_busstop = true;
    /*---------DECLARATIONS---------------*/
    
    /*---------GET BUSLINE----------------*/
    cout << "Enter the name of the bus line to insert a new bus stop (0 for main menu)" << endl;
    cin >> busline;
    if (busline == "0") {
        processMainMenu(h);
    }
    /*---------GET BUSLINE----------------*/
    
    /*---------SAVE HEAD TO USE İT REPEATEDLY-----------*/
    save_h = h;
    /*---------SAVE HEAD TO USE İT REPEATEDLY-----------*/
    
    
    while (h != NULL) {
        /*----------IF BUSLINE EXİST-------------*/
        if (h->busLineName == busline) {
            /*-------INACTIVATE NO_BUSLINE BOOL------*/
            no_busline = false;
            /*-------INACTIVATE NO_BUSLINE BOOL------*/
            
            /*  ---------INFO -----------------------*/
            cout << "The bus line information is shown below" << endl;
            printBusLines(h, only_one_line);
            /*  ---------INFO -----------------------*/
            
            /*  --------GET NEW BUS STOP-------------*/
            cout << "Enter the name of the new bus stop" << endl;
            cin >> newbusstop;
            /*  --------GET NEW BUS STOP-------------*/
            
            /*  -------MERGE K TO BUS STOPS----------*/
            k = h->busStops;
            /*  -------MERGE K TO BUS STOPS----------*/
            
            /*  --------SAVE K TO USE IT REPEATEDLY----*/ //because k is head of busstops.
            save_k = k;
            /*  --------SAVE K TO USE IT REPEATEDLY----*/
            
            /*  --------T and NN WHİCH ARE SUPPORTIVE POINTERS POINT TO K---------*/
            t = k;
            nn = k;
            /*  --------T and NN WHİCH ARE SUPPORTIVE POINTERS POINT TO K---------*/
            
            /*  ---------CHECK NEW BUS STOP NAME IS NOT ALREADY EXİSTS----------- */
            while (k != NULL) {
                if (k->busStopName == newbusstop) {
                    no_exist_busstop = false;
                    cout << "Bus stop already exists. Going back to previous menu." << endl;
                }
                k = k->right;
            }
            /*  ---------CHECK NEW BUS STOP NAME IS NOT ALREADY EXİSTS----------- */
            
            /*  ----------IF THERE İS NO EXİSTED (NEW) BUS STOP-------------------------*/
            if (no_exist_busstop) {
                /*  -------RESET K, T AND NN TO USE IT AGAIN------------*/
                k = save_k;
                t = k;
                nn = k;
                /*  -------RESET K, T AND NN TO USE IT AGAIN------------*/
                
                /*  -----------GET PREVIOUS BUS STOP--------------------*/
                cout << "Enter the name of the previous bus stop to put the new one after it (0 to put the new one as the first bus stop)" << endl;
                cin >> prevbusstop;
                /*  -----------GET PREVIOUS BUS STOP--------------------*/
                
                /*  ----------CHECK (PREVIOUS) BUS STOP İS ALREADY EXİSTED-------*/
                while (k != NULL) {
                    no_prev_busstop = true;
                    /*  --------IF PREVIOUS IS ALREADY EXİSTED----------------*/
                    if (k->busStopName == prevbusstop) {
                        /*---------NO_PREV_BUSSTOP INACTIVATED--------*/
                        no_prev_busstop = false;
                        /*---------NO_PREV_BUSSTOP INACTIVATED--------*/
                        
                        /*--------T AND NN SET UP TO CURRENT K WHİCH İS PREVIOUS BUS STOP---------*/
                        t = k;
                        nn = k;
                        /*--------T AND NN SET UP TO CURRENT K WHİCH İS PREVIOUS BUS STOP---------*/
                        
                        /*  ----------K IS SET UP TO BUS STOP WHICH WILL BE NEXT BUS STOP AFTER ADDITION---------*/
                        k = k->right;
                        /*  ----------K IS SET UP TO BUS STOP WHICH WILL BE NEXT BUS STOP AFTER ADDITION---------*/
                        
                        /*  --------CREATE NEW BUS STOP---------*/
                        nn = new busStop;
                        /*  --------CREATE NEW BUS STOP---------*/
                        
                        /*  -----------T (POINTS TO PREVIOUS) BOUND TO NEW BUS STOP-------*/
                        t->right = nn;
                        /*  -----------T (POINTS TO PREVIOUS) BONDS TO NEW BUS STOP-------*/
                        
                        /*  -----------NEW BUS STOP BONDS TO PREVIOUS BUS STOP (T)----------- */
                        nn->left = t;
                        /*  -----------NEW BUS STOP BONDS TO PREVIOUS BUS STOP (T)----------- */
                        
                        /*  ---------NEW BUS STOP BONDS BONDS TO K WHICH IS SET UP TO NEXT BUS STOP BEFOREHAND------*/
                        nn->right = k;
                        /*  ---------NEW BUS STOP BONDS BONDS TO K WHICH IS SET UP TO NEXT BUS STOP BEFOREHAND------*/
                        
                        /*  ----------NAME NEW BUS STOP-------*/
                        nn->busStopName = newbusstop;
                        /*  ----------NAME NEW BUS STOP-------*/
                        
                        /*  -------IF K NOT NULL BOND IT TO NEW NODE FROM LEFT------*/
                        if (k != NULL) {
                            k->left = nn;
                        }
                        /*  -------IF K NOT NULL BOND IT TO NEW NODE FROM LEFT------*/
                    }
                    /*  --------IF PREVIOUS IS ALREADY EXİSTED----------------*/
                    
                    /*  ---------INACTIVATED NO_PREV_BUSSTOP ENDS THE PROCESS-------*/
                    if (!no_prev_busstop) {
                        break;
                    }
                    /*  ---------INACTIVATED NO_PREV_BUSSTOP ENDS THE PROCESS-------*/
                    
                    /*  ------------IF PROCESS DOES NOT END AND CAME HERE, IT MEANS PREVIOUS BUS LINE NOT EXİSTED-------*/
                    if (k->right == NULL) {
                        cout << "Bus stop does not exist. Typo? Enter again (0 for main menu)" << endl;
                        cin >> prevbusstop;
                        if (prevbusstop == "0") {
                            processMainMenu(h);
                        }
                        /*  -------REQUIRED FOR REPEAT PROCESS----------*/
                        k = save_k;
                        /*  -------REQUIRED FOR REPEAT PROCESS----------*/
                    }
                    /*  ------------IF PROCESS DOES NOT END AND CAME HERE, IT MEANS PREVIOUS BUS LINE NOT EXİSTED-------*/
                    
                    if (no_prev_busstop) {
                        k = k->right;
                    }
                    
                    t = k;
                    nn = k;
                }
                /*  ----------CHECK (PREVIOUS) BUS STOP İS ALREADY EXİSTED-------*/
            }
            /*  ----------IF THERE İS NO EXİSTED (NEW) BUS STOP-------------------------*/
        }
        /*  ----------IF BUSLINE EXİST------------*/
        h = h->next;
    }
    /*  ----------IF BUSLINE NOT EXİST------------*/
    if (no_busline) {
        cout << "Bus line cannot be found. Going back to previous menu." << endl;
        printBusLines(h, only_one_line);
    }
    /*  ----------IF BUSLINE NOT EXİST------------*/
    else {
        if (no_exist_busstop) {
            h = save_h;
            only_one_line = false;
            printBusLines(h, only_one_line);
        }
    }
}

void deleteBusLine(busLine* h) {
    string delete_busline;
    bool busline_exist = false, only_one_line = false;
    int counter = 0;
    busLine* save_h;
    save_h = h;
    busLine* d;
    busLine* p;
    d = h;
    p = h;
    cout << "Enter the name of the bus line to delete" << endl;
    cin >> delete_busline;
    while (h != NULL) {
        if (h->busLineName == delete_busline) {
            busline_exist = true;
        }
        h = h->next;
    }
    h = save_h;
    if (busline_exist) {
        while (h != NULL) {
            counter++;
            if (h->busLineName == delete_busline) {
                if (counter == 1) {
                    h = h->next;
                    p->next = h->next;
                    p = h;
                    delete d;
                    break;
                }
                else {
                    while (p->next != d) {
                        p = p->next;
                    }
                    h = h->next;
                    p->next = h;
                    delete d;
                    h = save_h;
                    break;
                }
            }
            h = h->next;
            d = h;
        }
        counter = 0;
    }
    else {
        cout << "Bus line cannot be found. Going back to the previous (main) menu." << endl;
        processMainMenu(h);
    }
    printBusLines(h, only_one_line);
}

void  deleteBusStop(busLine* h) {
    string delete_busstop ,busline;
    bool busline_exist = false, busstop_exist = false, only_one_line = false;
    int counter = 0;
    busLine* save_h;
    save_h = h;
    busStop* k;
    busStop* save_k;
    busStop* d;
    busStop* p;
    
    cout << "Enter the name of the bus line to delete a new bus stop (0 for main menu)" << endl;
    cin >> busline;
    if (busline == "0") {
        processMainMenu(h);
    }
    while (h != NULL) {
        if (h->busLineName == busline) {
            busline_exist = true;
        }
        h = h->next;
    }
    h = save_h;
    if (busline_exist) {
        while (h != NULL) {
            if (h->busLineName == busline) {
                k = h->busStops;
                d = k;
                p = k;
                save_k = k;
                break;
            }
            h = h->next;
        }
       
        cout << "The bus line information is shown below" << endl;
        printBusLines(h, only_one_line = true);
        cout << "Enter the name of the bus stop to delete (0 for main menu)" << endl;
        cin >> delete_busstop;
        if (delete_busstop == "0") {
            processMainMenu(h);
        }
        while (k != NULL) {
            if (k->busStopName == delete_busstop) {
                busstop_exist = true;
            }
            k = k->right;
        }
        k = save_k;
        while (!busstop_exist) {
            cout << "Bus stop cannot be found. Enter the name of the bus stop to delete (0 for main menu)" << endl;
            cin >> delete_busstop;
            if (delete_busstop == "0") {
                processMainMenu(h);
            }
            while (k != NULL) {
                if (k->busStopName == delete_busstop) {
                    busstop_exist = true;
                }
                k = k->right;
            }
            k = save_k;
        }
        k = save_k;
        if (busstop_exist) {
            while (k != NULL) {
                counter++;
                if (k->busStopName == delete_busstop) {
                    if (counter == 1) {
                        k = k->right;
                        h->busStops = k;
                        k->left = NULL;
                        delete d;
                        d = k;
                        p = k;
                        h = save_h;
                        printBusLines(h, only_one_line = false);
                        break;
                    }
                    else {
                        while (p->right != k) {
                            p = p->right;
                        }
                        k = d->right;
                        p->right = k;
                        if (k != NULL) {
                            k->left = p;
                        }
                        delete d;
                        k = save_k;
                        d = k;
                        p = k;
                        h = save_h;
                        printBusLines(h, only_one_line = false);
                        break;
                    }
                }
                k = k->right;
                d = k;
            }
        }
    }
    else {
        cout << "Bus line cannot be found. Going back to previous (main) menu." << endl;
        h = save_h;
        processMainMenu(h);
    }
    
}

void pathfinder(busLine* h) {
    /*  ----------DECLARATIONS-----------------*/
    string current_loc, destination, busline1, busline2;
    bool busstop_exist, rotation_exist = false, s1_left = false, s2_left = false;
    int current_loc_counter = 0, destination_counter = 0;
    busLine* save_h;
    busLine* b1; // RESPONSIBLE FOR BUS LINE THAT CURRENT LOC. BELONGS.
    busLine* b2; // RESPONSIBLE FOR BUS LINE THAT DESTINATION BELONGS.
    save_h = h; // RESPONSIBLE FOR RETURNING H IN INITIAL POSITION.
    busStop* k; // RESPOSIBLE FOR FIRST CHECK TO FIND DESTINATION'S POSITION.
    busStop* save_k; // RESPONSIBLE FOR RETURNING K IN INITIAL POSITION.
    save_k = k;
    busStop* c; // SUPPLEMENTARY POINTER.
    busStop* d; //SUPPLEMENTARY POINTER.
    busStop* s1; // RESPONSIBLE FOR BUS STOPS WHERE BUSLINE THAT CURRENT LOC. BELONGS. && TO POINT MUTUAL BUSSTOP.
    busStop* s2; // RESPONSIBLE FOR BUS STOPS WHERE BUSLINE THAT DESTINATION BELONGS. && TO POINT MUTUAL BUSSTOP.
    busStop* CUR = nullptr; // TO KEEP CURRENT LOC. POSITION.
    busStop* DES = nullptr; // TO KEEP DESTINATOIN POSITION.
    /*  ----------DECLARATIONS-----------------*/
    
    /*  ---------GET CURRENT LOCATION----------*/
    cout << "Where are you now?" << endl;
    cin >> current_loc;
    /*  ---------GET CURRENT LOCATION----------*/
    
    /*  ---------CHECK WHETHER CURRENT LOCATION EXİST-------*/
    while (h != NULL) {
        k = h->busStops;
        while (k != NULL) {
            current_loc_counter++;
            if (current_loc == k->busStopName) {
                CUR = k;
                busstop_exist = true;
                c = k;
                break;
            }
            if (busstop_exist) {
                break;
            }
            k = k->right;
        }
        if (busstop_exist) {
            break;
        }
        else {
            h = h->next;
            current_loc_counter = 0;
        }
    }
    /*  ---------CHECK WHETHER CURRENT LOCATION EXİST-------*/
    
    /*  ----------SAVE K TO USE IT AGAIN && ASSIGN busline1 AS A CURRENT LOC.'s BUSLINE (DURİNG CHECKİNG H STOPPED WHERE BUSLİNE THAT CUR. LOC. BELONGS-----*/
    k = save_k;
    busline1 = h->busLineName;
    b1 = h;
    /*  ----------SAVE K TO USE IT AGAIN && ASSIGN busline1 AS A CURRENT LOC.'s BUSLINE (DURİNG CHECKİNG H STOPPED WHERE BUSLİNE THAT CUR. LOC. BELONGS-----*/
    
    /*  --------- IF CURRENT LOC. EXİST---------*/
    if (busstop_exist) {
        busstop_exist = false;
        
        /*  -----------GET DESTİNATION--------------*/
        cout << "Where do you want to go?" << endl;
        cin >> destination;
        /*  -----------GET DESTİNATION--------------*/
        
        /*  ---------CHECK WHETHER DESTINATION EXİST-------*/
        while (h != NULL) {
            k = h->busStops;
            while (k != NULL) {
                destination_counter++;
                if (destination == k->busStopName) {
                    busstop_exist = true;
                    d = k;
                }
                k = k->right;
                if (busstop_exist) {
                    break;
                }
            }
            if (busstop_exist) {
                break;
            }
            else {
                h = h->next;
                destination_counter = 0;
            }
        }
        /*  ---------CHECK WHETHER DESTINATION EXİST-------*/
        
        /*----------SAVE K TO USE IT AGAIN-----------------*/
        k = save_k;
        /*----------SAVE K TO USE IT AGAIN-----------------*/
        
        /*  ---------IF DESTINATION EXİST------------------*/
        if (busstop_exist) {
            /*  -----------IF DESTINATION COUNTER > CURRENT LOC. COUNTER: MEANS THAT DESTINATION İS IN RIGHT SIDE OF CURRENT LOC. ------*/
            if (destination_counter > current_loc_counter) {
                cout << "You can go there by " << busline1 << ": ";
                while (c != d) {
                    cout << c->busStopName << "->";
                    c = c->right;
                }
                if (c->busStopName == d->busStopName) {
                    cout << c->busStopName;
                }
            }
            /*  -----------ENDIF DESTINATION COUNTER > CURRENT LOC. COUNTER: MEANS THAT DESTINATION İS IN RIGHT SIDE OF CURRENT LOC. ------*/
            
            /*  -----------IF DESTINATION COUNTER < CURRENT LOC. COUNTER: MEANS THAT DESTINATION İS IN LEFT SIDE OF CURRENT LOC. -------*/
            if (destination_counter < current_loc_counter) {
                cout << "You can go there by " << busline1 << ": ";
                while (c->busStopName != d->busStopName) {
                    cout << c->busStopName << "->";
                    c = c->left;
                }
                if (c->busStopName == d->busStopName) {
                    cout << c->busStopName;
                }
            }
            /*  -----------ENDIF DESTINATION COUNTER < CURRENT LOC. COUNTER: MEANS THAT DESTINATION İS IN LEFT SIDE OF CURRENT LOC. -------*/
        }
        /*  ---------ENDIF DESTINATION EXİST------------------*/
        
        /*  ----------IF DESTINATION DO NOT EXIST IN THE SAME BUSSTOP WİTH CURRENT LOC.----------*/
        else {
            
            busStop* save_s2; // TO SAVE s2.
            busStop* save_s1; // TO SAVE s1.
            busline1 = b1->busLineName; // BUSLINE1 ASSIGNED: b1 WAS POINTING H WHICH IS STOPPED IN CURRENT LOC's BUS LINE.
            s1 = b1->busStops; // S1 IS REPONSIBLE TO CHECK BUSLINE1's (CURRENT LOC's BUS LINE) BUS STOPS.
            h = save_h; //SAVE H TO USE IT AGAIN.
            k = save_k; //SAVE K TO USE IT AGAIN.
            b2 = h; // b2 IS INITAL POSITION AS WELL AS H.
            
            /*  TASK OF WHILE: FIND DESTINATION && ASSIGN b2 TO DESTINATION's BUSLINE && POINT DES TO WHERE DESTINATION IS--------*/
            while (b2 != NULL) {
                k = b2->busStops;
                while (k != NULL) {
                    if (k->busStopName == destination) {
                        DES = k;
                        busstop_exist = true;
                        busline2 = b2->busLineName;
                        b2->busLineName = busline2;
                        s2 = b2->busStops;
                    }
                    if (busstop_exist) {
                        break;
                    }
                    k = k->right;
                }
                if (busstop_exist) {
                    break;
                }
                b2 = b2->next;
            }
            /*  TASK OF WHILE: FIND DESTINATION && ASSIGN b2 TO DESTINATION's BUSLINE && POINT DES TO WHERE DESTINATION IS--------*/
            if (!busstop_exist) {
                cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
                h = save_h;
                processMainMenu(h);
            }
            h = save_h;
            k = save_k;
            
            /*  -----------NOW s1 AND s2 SET UP CORRECTLY----------------*/
            s1 = b1->busStops; // WAS ALREADY ASSIGNED.
            s2 = b2->busStops; // b2 WAS STOPPED WHERE BUSLINE THAT DESTINATION BELONGS IN PREVIOUS WHILE LOOP.
            /*  -----------NOW s1 AND s2 SET UP CORRECTLY----------------*/
            
            
            save_s2 = s2; // TO DO NOT FORGET INITIAL POSTION.
            save_s1 = s1; // TO DO NOT FORGET INITIAL POSTION.
            
            /*  ----TASK OF WHILE: SCAN EACH OF THE BUSLINES WHERE DESTINATION AND CURRENT LOC BELONG (2 BUSLINE) AND DETERMINE WHETHER THERE IS SAME BUS STOP THAT PROVIDE PASSING FROM ONE TO OTHER BUS LINE. */
            while (s1 != NULL) {
                if (s1->busStopName == current_loc) {
                    s1_left = true; // S1_LEFT DETERMINES THAT WHICH SIDE SHOULD POINTERS GO TO DISPLAY THE PATH IN CURRENT LOCATION's BUSLINE.
                }
                while (s2 != NULL) {
                    if (s2->busStopName == destination) {
                        s2_left = true; // S2_LEFT DETERMINES THAT WHICH SIDE SHOULD POINTERS GO TO DISPLAY THE PATH IN DESTINATION's BUSLINE.
                    }
                    if (s1->busStopName == s2->busStopName) {
                        rotation_exist = true;
                    }
                    if (rotation_exist) {
                        break;
                    }
                    s2 = s2->right;
                }
                if (rotation_exist) {
                    break;
                }
                s2_left = false;
                s1 = s1->right;
                s2 = save_s2;
            }
            /*  ----TASK OF WHILE: SCAN EACH OF THE BUSLINES WHERE DESTINATION AND CURRENT LOC BELONG (2 BUSLINE) AND DETERMINE WHETHER THERE IS SAME BUS STOP THAT PROVIDE PASSING FROM ONE TO OTHER BUS LINE. */
            
            // NOTE: s1 AND s2 POINTS TO MUTUAL BUS STOP RIGHT HERE BECAUSE WHEN IT IS EQUAL WHILE LOOP STOPPED WITH BREAK.
            
            /*  -------------IF ROTATION EXIST: THERE IS PATH THAT PROVIDE TRANSPORTATION BETWEEN DIFFERENT BUSLINES----------. */
            if (rotation_exist) {
                /*  -------DETERMINE THE ROTATION BY USING S1_LEFT AND S2_LEFT BOOLEANS WHICH ARE SET UP IN PREVIOUS LOOP.--------*/
                /*  ---NOTE: S1_LEFT AND S2_LEFT ARE OPPOSITE BECAUSE: IN CURRENT LOC's BUSLINE, CUR POINTER PROGRESS FROM CUR TO s1;  IN DESTINATION's BUSLINE, s2 POINTER PROGRESS FROM s2 TO DES. */
                if (s1_left) {
                    cout << "You can go there by " << b1->busLineName << ": ";
                    while (CUR->busStopName != s1->busStopName) {
                        cout << CUR->busStopName << "->";
                        CUR = CUR->right;
                    }
                    if (CUR->busStopName == s1->busStopName) {
                        cout << s1->busStopName << endl;
                    }
                    if (s2_left) {
                        cout << b2->busLineName << ": ";
                        while (DES->busStopName != s2->busStopName) {
                            cout << s2->busStopName << "->";
                            s2 = s2->left;
                        }
                        if (DES->busStopName == s2->busStopName) {
                            cout << DES->busStopName;
                        }
                    }
                    else {
                        cout << b2->busLineName << ": ";
                        while (DES->busStopName != s2->busStopName) {
                            cout << s2->busStopName << "->";
                            s2 = s2->right;
                        }
                        if (DES->busStopName == s2->busStopName) {
                            cout << DES->busStopName;
                        }
                    }
                }
                else {
                    cout << "You can go there by " << b1->busLineName << ": ";
                    while (CUR->busStopName != s1->busStopName) {
                        cout << CUR->busStopName << "->";
                        CUR = CUR->left;
                    }
                    if (CUR->busStopName == s1->busStopName) {
                        cout << s1->busStopName << endl;
                    }
                    if (s2_left) {
                        cout << b2->busLineName << ": ";
                        while (DES->busStopName != s2->busStopName) {
                            cout << s2->busStopName << "->";
                            s2 = s2->left;
                        }
                        if (DES->busStopName == s2->busStopName) {
                            cout << DES->busStopName;
                        }
                    }
                    else {
                        cout << b2->busLineName << ": ";
                        while (DES->busStopName != s2->busStopName) {
                            cout << s2->busStopName << "->";
                            s2 = s2->right;
                        }
                        if (DES->busStopName == s2->busStopName) {
                            cout << DES->busStopName;
                        }
                    }
                }
                /*  -------DETERMINE THE ROTATION BY USING S1_LEFT AND S2_LEFT BOOLEANS WHICH ARE SET UP IN PREVIOUS LOOP.--------*/
                
            }
            /*  -------------ENDIF ROTATION EXIST: THERE IS PATH THAT PROVIDE TRANSPORTATION BETWEEN DIFFERENT BUSLINES----------. */
            
            else {
                cout << "Sorry no path from " << current_loc << " to " << destination << " could be found." << endl;
            }
        
        }
        /*  ----------ENDIF DESTINATION DO NOT EXIST IN THE SAME BUSSTOP WİTH CURRENT LOC.----------*/
    }
    /*  --------- ENDIF CURRENT LOC. EXİST---------*/
    else {
        cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
        h = save_h;
        processMainMenu(h);
    }
}


bool consistencyCheck(busLine* head) {
    busLine* currBL = head; //a global variable while(currBL) {
    while(currBL) {
        busStop* currBS = currBL->busStops;
        while(currBS) {
            busStop* rightBS = currBS->right;
            if(rightBS && rightBS->left != currBS) {
                cout << "Inconsistency for " << currBL->busLineName << " " << currBS->busStopName << endl;
                return false;
            }
            currBS = currBS->right;
        }
        currBL = currBL->next;
    }
    return true;
}

void processMainMenu(busLine* h) {
    char input;
    bool only_one_line = true;
    do
    {
        if (!consistencyCheck(h)) {
            cout << "There are inconsistencies. Exit." << endl;
            return;
        }
        printMainMenu();
        cout << "Please enter your option " << endl;
        cin >> input;
        switch (input) {
            case '0':
                cout << "Thanks for using our program" << endl;
                return;
            case '1':
                only_one_line = false;
                printBusLines(h, only_one_line);
                break;
            case '2':
                addBusLine(h);
                break;
            case '3':
                addBusStop(h);
                break;
            case '4':
                deleteBusLine(h);
                break;
            case '5':
                deleteBusStop(h);
                break;
            case '6':
                pathfinder(h);
                break;
            default:
                cout << "Invalid option: please enter again" << endl;
        }
    } while(true);
}

int main() {
    /*------------DECLARATIONS-------------------------*/
    ifstream file;
    string filename = "busLines.txt", line, item, busline, busstop;
    int counter = 0;
    bool once = true;
    busLine* n;
    busLine* h;
    busLine* t;
    busStop* tt;
    busStop* nn;
    busStop* pp;
    busStop* hh;
    /*------------DECLARATIONS--------------------------*/
    
    n = new busLine();
    h = n;
    t = n;
    
    /*  ------------------OPEN THE FILE---------*/
    file.open(filename.c_str());
    /*  ------------------OPEN THE FILE---------*/
    
    while (getline(file, line)) {
        counter++;
        /*  -----------CREATE BUSLINE AND BUSSTOP-----------*/
        nn = new busStop();
        pp = nn;
        tt = nn;
        hh = nn;
        /*  -----------CREATE BUSLINE AND BUSSTOP-----------*/
        if (counter > 1) {
            n = new busLine();
            t->next = n;
            t = n;
            
        }
        
        istringstream s(line);
        s >> busline;
        n->busLineName = busline.substr(0, busline.size()-1);
        
        while (s >> busstop) {
            if (once) {
                /*  ------MERGE BUSLİNE WİTH FIRST BUSSTOP----------*/
                t->busStops = nn;
                /*  ------MERGE BUSLİNE WİTH FIRST BUSSTOP----------*/
                
                /*  ---------LEFT OF FIRST BUSSTOP IS NULL----------*/
                tt->left = NULL;
                /*  ---------LEFT OF FIRST BUSSTOP IS NULL----------*/
                
                tt->busStopName = busstop;
                once = false;
            }
            else {
                nn = new busStop();
                tt->right= nn;
                pp = tt;
                tt = nn;
                tt->left = pp;
                tt->busStopName = busstop;
            }
        }
          
        nn->right = NULL;
        nn = hh;
        tt = hh;
        pp = hh;
        once = true;
    }
    t->next = NULL;
    processMainMenu(h);

    return 0;
}
