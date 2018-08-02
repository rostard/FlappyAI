//
// Created by rostard on 26.01.18.
//

#ifndef TRON_LOG_H
#define TRON_LOG_H

#include <map>
#include <iostream>
#include <string>

enum LOG_TYPE{
    LOG_INFO = 0,
    LOG_WARNING,
    LOG_ERROR
};



class Log {
public:
    static void Message(std::string message, LOG_TYPE type)
    {
        if(type >= filter){
            std::cerr<<type<<": "<<message<<std::endl;
        }
    }
    static void SetFilter(LOG_TYPE filter){
        Log::filter = filter;
    }
private:
    static LOG_TYPE filter;
};

#endif //TRON_LOG_H
