#ifndef DORMENGINE_SID_H
#define DORMENGINE_SID_H

#include <string>

#define SID(string) simple_hash(string)

inline unsigned int simple_hash(const std::string& string){
    unsigned int hash = 0;

    for(auto i: string){
        hash = 37 * hash + 17 * i;
    }

    return hash;
}

#endif //DORMENGINE_SID_H
