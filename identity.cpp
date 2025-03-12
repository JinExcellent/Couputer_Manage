#include "identity.h"
#include <fstream>

bool operator>>(std::ifstream & is, string & val){
    if(is >> val)
        return true;

    return false;
}
