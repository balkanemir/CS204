#include "Driver.h"
#include <stdio.h>

bool Driver::constructor_bool = true;

Driver::Driver(Car & car, double driver_budget)
:sharedCar(car) {
    if (constructor_bool) {
        this->driver_budget = driver_budget;
        driver_name = "driver1";
        constructor_bool = false; //required for determining name of the driver (when the program calculate the budgets, it will distinguish the drivers.)
    }
    else {
        this->driver_budget = driver_budget;
        driver_name = "driver2";
    }
}

void Driver::drive(int &km) {
    sharedCar.total_distance += km;
    sharedCar.fuel_level -= km * 0.25;
}

void Driver::repairCar(string & size) {
    if (size == "SMALL") {
        if (driver_name == "driver1") {
            driver_budget -= 50;
            sharedCar.insurance_fee *= 1.05;
            cout << "50$ is reduced from the driver's budget because of the " << size << " accident" << endl;
            cout << "Yearly insurance fee is increased to " << sharedCar.insurance_fee << " because of the " << size << " accident" << endl;
        }
        else {
            driver_budget -= 50;
            sharedCar.insurance_fee *= 1.05;
            cout << "50$ is reduced from the driver's budget because of the " << size << " accident" << endl;
            cout << "Yearly insurance fee is increased to " << sharedCar.insurance_fee << " because of the " << size << " accident" << endl;
        }
        
    }
    if (size == "MEDIUM") {
        if (driver_name == "driver1") {
            driver_budget -= 150;
            sharedCar.insurance_fee *= 1.1;
            cout << "150$ is reduced from the driver's budget because of the " << size << " accident" << endl;
            cout << "Yearly insurance fee is increased to " << sharedCar.insurance_fee << " because of the " << size << " accident" << endl;
        }
        else {
            driver_budget -= 150;
            sharedCar.insurance_fee *= 1.2;
            cout << "150$ is reduced from the driver's budget because of the " << size << " accident" << endl;
            cout << "Yearly insurance fee is increased to " << sharedCar.insurance_fee << " because of the " << size << " accident" << endl;
        }

    }
    if (size == "LARGE") {
        if (driver_name == "driver1") {
            driver_budget -= 300;
            sharedCar.insurance_fee *= 1.2;
            cout << "300$ is reduced from the driver's budget because of the " << size << " accident" << endl;
            cout << "Yearly insurance fee is increased to " << sharedCar.insurance_fee << " because of the " << size << " accident" << endl;
        }
        else {
            driver_budget -= 300;
            sharedCar.insurance_fee *= 1.2;
            cout << "300$ is reduced from the driver's budget because of the " << size << " accident" << endl;
            cout << "Yearly insurance fee is increased to " << sharedCar.insurance_fee << " because of the " << size << " accident" << endl;
        }

    }
}

void Driver::display() {
    if (driver_name == "driver1") {
        cout << "Driver Budget: " << driver_budget;
    }
    else {
        cout << "Driver Budget: " << driver_budget;
    }
}

void Driver::fullFuel() {
    double consume_level, cost;
    if (driver_name == "driver1") {
        consume_level = 300 - sharedCar.fuel_level;
        cost = consume_level;
        driver_budget -= cost;
        sharedCar.fuel_level = 300;
        cout << "Fuel is full" << endl << endl;
    }
    else {
        consume_level = 300 - sharedCar.fuel_level;
        cost = consume_level;
        driver_budget -= cost;
        sharedCar.fuel_level = 300;
        cout << "Fuel is full" << endl << endl;
    }
}


