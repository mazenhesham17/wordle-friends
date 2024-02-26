#include "Response.h"

bool Response::isSuccess() const
{
    return status;
}

void Response::setStatus(bool status)
{
    Response::status = status;
}

const std::string &Response::getJson() const
{
    return json;
}

void Response::setJson(const std::string &json)
{
    Response::json = json;
}
