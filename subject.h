#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
// #include "observer.h"

class Observer;

class Subject {
    std::vector<Observer *> observers;

public:
    void attach(Observer *o);
    void detach(Observer *o);
    void notifyObservers();
    virtual std::string getState(int row, int col) const = 0;
    virtual ~Subject() = default;
};

#endif