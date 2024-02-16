#ifndef BACKEND_RESPONSECONTROLLER_H
#define BACKEND_RESPONSECONTROLLER_H

#include "../Model/Response.h"

class ResponseController
{
    static ResponseController *instance;

    ResponseController() {}

public:
    static ResponseController *getInstance();

    void setSuccess(Response &response, const std::string &json);

    void setFailure(Response &response, const std::string &error);
};

#endif // BACKEND_RESPONSECONTROLLER_H
