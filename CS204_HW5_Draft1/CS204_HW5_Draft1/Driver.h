#ifndef Driver_h
#define Driver_h
#include <iostream>
#include "Car.h"
using namespace std;

class Driver {
private:
    
    double driver_budget;
    Car &sharedCar; //required for object sharing with Driver class.
    static bool constructor_bool;
    string driver_name;
public:
    Driver(Car& ,double);
    void drive (int&);
    void repairCar(string&);
    void display();
    void fullFuel();

};

#endif /* Driver_h */
