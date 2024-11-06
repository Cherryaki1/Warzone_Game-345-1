
#include "LoggingObserver.h"
#include <fstream>
#include <iostream>


void Subject::attach(Observer *o) {
    observers.push_back(o);
}

void Subject::detach(Observer *o) {
    for(auto it = observers.begin(); it != observers.end(); it++){
        if(*it == o){
            observers.erase(it);
            return;
        }
    }
}

void Subject::notify(ILoggable *i) {
    for(auto& observer : observers){
        observer->update(i);
    }
}

void LogObserver::update(ILoggable *i) {
    std::ofstream file;
    file.open("gamelog.txt", std::ios::app);
    file << i->stringToLog() << "\n";
    file.close();
}
