#ifndef LOGGINGOBSERVER_H
#define LOGGINGOBSERVER_H

#include <string>
#include <vector>
#include <list>
using std::string;
using std::vector;
using std::list;

class ILoggable{
public:
    ILoggable() = default;
    virtual ~ILoggable() = default;
    virtual string stringToLog() const = 0;
};

class Observer{
public:
    Observer() = default;
    virtual ~Observer() = default;
    virtual void update(ILoggable* i) = 0;
};

class Subject{
private:
    list<Observer*> observers;
public:
    Subject() = default;
    ~Subject();
    void attach(Observer* o);
    void detach(Observer* o);
    void notify(ILoggable* i);
};

class LogObserver: public Observer{
    void update(ILoggable* i) override;
};

#endif //LOGGINGOBSERVER_H
