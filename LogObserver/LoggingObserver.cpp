
#include "LoggingObserver.h"
#include <fstream>
#include <iostream>


void Subject::attach(Observer *o) {
    observers.push_back(o);
}

void Subject::detach(Observer *o) {
    observers.remove(o);
}

void Subject::notify(ILoggable *i) {
    for(auto& observer : observers){
        observer->update(i);
    }
}

Subject::~Subject() {
//    for (auto &&o:observers) {
//        delete o;
//    }
}

void LogObserver::update(ILoggable *i) {
    std::ofstream file;
    file.open("../gamelog.txt", std::ios::app);
    if(file.is_open()){
        file << i->stringToLog() << "\n";
    } else {
        std::cout<<"FILE DID NOT OPEN! "<< std::endl;
    }
    file.flush();
    file.close();
}
