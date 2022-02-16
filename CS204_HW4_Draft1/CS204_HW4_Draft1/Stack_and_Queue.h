#ifndef Stack_and_Queue_h
#define Stack_and_Queue_h

class IntStack
{
private:
    int *stackArray;
    int stackSize;
    int top;

public:
    IntStack(int);
    void push(int);
    void pop(int &);
    bool isFull(void);
    bool isEmpty(void);
};

#endif /* Stack_and_Queue_h */
