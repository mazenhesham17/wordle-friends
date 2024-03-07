#include "Response.h"

bool Response::isSuccess() const
{
    return status;
}

void Response::setStatus(bool status)
{
    this->status = status;
}

const std::string &Response::getJson() const
{
    return json;
}

void Response::setJson(const std::string &json)
{
    this->json = json;
}
