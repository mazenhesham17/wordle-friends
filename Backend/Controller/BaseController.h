#ifndef BACKEND_BASECONTROLLER_H
#define BACKEND_BASECONTROLLER_H
#include <string>
#include "../Model/User.h"

class BaseController {
    public:
    virtual std::string profile( const User *user ) = 0;
};


#endif //BACKEND_BASECONTROLLER_H
