/**
 * @file LoggingObserver.cpp
 * @brief This file contains the class and function implementations for the logging observer pattern.
 * 
 * This file is part of the Warzone Game Team Project for COMP 345 - D (Advanced Program Design, C++).
 * It includes the implementation of the Subject and LogObserver classes, which are used to log game events.
 * 
 * Team Members (Team 36):
 * - Amir Vala Khalilzadeh (40253211)
 * - Abdulah Ghulam Ali (40281857)
 * - Arturo Sanchez Escobar (40283236)
 * - Gregory Lajoie (40276231)
 * - Botao Yang (40213554)
 */

#include "LoggingObserver.h"
#include <fstream>
#include <iostream>

//**************************SUBJECT**************************

/**
 * @class Subject
 * @brief Represents the subject in the observer pattern.
 * 
 * The Subject class maintains a list of observers and notifies them of any changes.
 */

/**
 * @brief Attaches an observer to the subject.
 * @param o The observer to attach.
 */
void Subject::attach(Observer *o) {
    observers.push_back(o);
}

/**
 * @brief Detaches an observer from the subject.
 * @param o The observer to detach.
 */
void Subject::detach(Observer *o) {
    observers.remove(o);
}

/**
 * @brief Notifies all attached observers of a change.
 * @param i The loggable object to notify observers about.
 */
void Subject::notify(ILoggable *i) {
    for(auto& observer : observers){
        observer->update(i);
    }
}

/**
 * @brief Destructor for the Subject class.
 */
Subject::~Subject() {
//    for (auto &&o:observers) {
//        delete o;
//    }
}

//**************************LOG OBSERVER**************************

/**
 * @class LogObserver
 * @brief Represents the observer in the observer pattern.
 * 
 * The LogObserver class writes loggable events to a file.
 */

/**
 * @brief Updates the observer with a loggable event.
 * @param i The loggable object to log.
 */
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
