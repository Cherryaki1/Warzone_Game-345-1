#ifndef LOGGINGOBSERVER_H
#define LOGGINGOBSERVER_H

#include <string>
#include <vector>
using std::string;
using std::vector;

class Observer{
public:
    Observer() = default;
    ~Observer() = default;
    virtual void update() = 0;
};


#endif //LOGGINGOBSERVER_H
