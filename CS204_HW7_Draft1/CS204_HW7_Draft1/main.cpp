#include <iostream>

using namespace std;

class shape {
public:
    string myName;

    virtual double perimeter() {
        return 0.0;
    }
    
    virtual double area() {
        return 0.0;
    }
    
    virtual double volume() {
        return 0.0;
    }
    
    string getName() {
        return myName;
    }
};


class TwoDShape : public shape {
public:
    double volume() {
        return 0.0;
    }
};


class ThreeDShape : public shape {
public:
    double perimeter() {
        return 0.0;
    }
};


class rectangle : public TwoDShape {
public:
    double width, length;
    double area() {
        return width*length;
    }
    double perimeter() {
        return 2*(width + length);
    }
    
};

class box : public ThreeDShape {
public:
    double width, length, height;
    double area() {
        return 2*(width*length+width*height+length*height);
    }
    
    double volume() {
        return width*length*height;
    }
   
};






/*include all the necessary files, libraries, etc. here, if any*/

/*if you choose not to write the 5 required classes in seperate .h and .cpp files, then write them here*/

shape* getShape() {
    shape* shape_ptr = nullptr;
    rectangle* rec_ptr;
    box* box_ptr;
    string option, choosen_shape, name;
    double length, width, height;
    cout << "Choose an option <1 or 2>: " << endl
    << "1. Rectangle " << endl
    << "2. Box " << endl;
    cin >> option;
    if (option == "1") {
        choosen_shape = "rectangle";
        cout << "You choose " << choosen_shape << ". Give its width, length and name: " << endl;
        cin >> width;
        cin >> length;
        cin >> name;
        height = 0;
        
        rec_ptr = new rectangle;
        rec_ptr->length = length;
        rec_ptr->width = width;
        rec_ptr->myName = name;
        shape_ptr = rec_ptr;
        
    }
    if (option == "2") {
        choosen_shape = "box";
        cout << "You choose " << choosen_shape << ". Give its width, length, height and name: " << endl;
        cin >> width;
        cin >> length;
        cin >> height;
        cin >> name;
        
        box_ptr = new box;
        
        box_ptr->myName = name;
        box_ptr->length = length;
        box_ptr->width = width;
        box_ptr->height = height;
        shape_ptr = box_ptr;
        
    }
    return shape_ptr;
    
}//getShape()


int main()
{
    cout<<"WELCOME TO THE SHAPE COMPARISONN PROGRAM"<<endl;
    cout<<"FOR EXITIING PRESS Y/y, OTHERWISE PRESS ANY KEY"<<endl;
    shape *shape_1, *shape_2; /* define two varibles, named shape_1 and shape_2 of the class shape.*/
    /*What should they be in order to enable proper polymorphism?*/
    char c;
    while (tolower(c = getchar())!='y')
    {
        cout<<"Defining (getting) shape 1..."<<endl;
        
        shape_1 = getShape();
        cout<<"Defining (getting) shape 2..."<<endl;
        shape_2 = getShape();
        cout<<"********************************************************************"<<endl;
        cout<<"PRINTING SHAPE_1 INFOS:"<<endl<<"Name: "<<shape_1->getName()<<", perimeter: "
            <<shape_1->perimeter()<<", area: "<<shape_1->area()<<", volume: "<<shape_1->volume()<<endl<<endl;
        cout<<"PRINTING SHAPE_2 INFOS:"<<endl<<"Name: "<<shape_2->getName()<<", perimeter: "
            <<shape_2->perimeter()<<", area: "<<shape_2->area()<<", volume: "<<shape_2->volume()<<endl;
        bool nothingInCommon=true; // to check whether they have anything in common (perimeter, area, volume)
        if(shape_1->perimeter()==shape_2->perimeter())
        {
            nothingInCommon = false;
            cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same perimeter, which is: "
                <<shape_1->perimeter()<<" cm."<<endl;
        }
        if(shape_1->area()==shape_2->area())
        {
            nothingInCommon = false;
            cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same area, which is: "
                <<shape_1->area()<<" cm^2."<<endl;
        }
        if(shape_1->volume()==shape_2->volume())
        {
            nothingInCommon = false;
            cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same volume, which is: "
                <<shape_1->volume()<<" cm^3."<<endl;
        }
        if (nothingInCommon)
            cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" don't have anything in common."<<endl;
        cout<<"********************************************************************"<<endl;
        cout<<"FOR EXITIING PRESS Y/y, OTHERWISE, FOR ANOTHER COMPARISON PRESS ANY KEY"<<endl<<endl;
        cin.ignore();//flushing the buffer for remaining character(s), in order getchar() to work
      }//while(tolower(c = getchar())!='y')
    cout<<"PROGRAM EXITING. THANKS FOR USING IT."<<endl;
    system("pause");
    return 0;
}

