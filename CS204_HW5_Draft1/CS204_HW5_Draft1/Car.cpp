#include "Car.h"
#include <stdio.h>



Car::Car(double fuel, double fee, double distance) {
    fuel_level = fuel;
    insurance_fee = fee;
    total_distance = distance;
}

void Car::display() {
    cout << "Fuel Level: " << fuel_level << endl;
    cout << "Insurance Fee: " << insurance_fee << endl;
    cout << "Total distance that the car has travelled: " << total_distance << endl << endl;
}
