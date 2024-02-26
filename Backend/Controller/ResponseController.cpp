#include "ResponseController.h"

ResponseController *ResponseController::instance = nullptr;

ResponseController *ResponseController::getInstance()
{
    if (instance == nullptr)
        instance = new ResponseController();
    return instance;
}

void ResponseController::setSuccess(Response &response, const std::string &json)
{
    response.setStatus(true);
    response.setJson(json);
}

void ResponseController::setFailure(Response &response, const std::string &error)
{
    response.setStatus(false);
    response.setJson(R"( { "error" : ")" + error + R"(" } )");
}

bool ResponseController::isSuccess(const Response &response)
{
    return response.isSuccess();
}