#ifndef LOGGINGOBSERVER_H
#define LOGGINGOBSERVER_H

#include <string>
#include <vector>
using std::string;
using std::vector;

class ILoggable{
public:
    ILoggable() = default;
    virtual ~ILoggable() = default;
    virtual string stringToLog() = 0;
};

class Observer{
public:
    Observer() = default;
    ~Observer() = default;
    virtual void update(ILoggable* i) = 0;
};

class Subject{
private:
    vector<Observer*> observers;
public:
    Subject() = default;
    ~Subject() = default;
    void attach(Observer* o);
    void detach(Observer* o);
    void notify(ILoggable* i);
};

class LogObserver: public Observer{
    void update(ILoggable* i) override;
};

#endif //LOGGINGOBSERVER_H
