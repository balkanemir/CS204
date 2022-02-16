#ifndef Car_h
#define Car_h

#include <iostream>

using namespace std;

class Car {
private:
   
public:
    double insurance_fee;
    double total_distance;
    double fuel_level;
    Car(double, double, double);
    void display();
};

#endif /* Car_h */
