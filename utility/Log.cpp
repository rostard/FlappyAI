//
// Created by rostard on 26.01.18.
//

#include "Log.h"

LOG_TYPE Log::filter = LOG_INFO;

std::ostream& operator<<(std::ostream& out, const LOG_TYPE value){
    const char* s = 0;
#define PROCESS_VAL(p) case(p): s = #p; break;
    switch(value){
        PROCESS_VAL(LOG_INFO);
        PROCESS_VAL(LOG_WARNING);
        PROCESS_VAL(LOG_ERROR);
    }
#undef PROCESS_VAL

    return out << s;
}