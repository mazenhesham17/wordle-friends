#ifndef BACKEND_RESPONSE_H
#define BACKEND_RESPONSE_H

#include <string>

class Response
{
    bool status;
    std::string json;

public:
    bool isStatus() const;

    void setStatus(bool status);

    const std::string &getJson() const;

    void setJson(const std::string &json);
};

#endif // BACKEND_RESPONSE_H
