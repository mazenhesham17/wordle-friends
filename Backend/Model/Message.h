#ifndef BACKEND_MESSAGE_H
#define BACKEND_MESSAGE_H

#include <string>

class Message
{
    int messageID;
    int chatID;
    int senderID;
    std::string message;
    std::string sendTime;

public:
    int getMessageId() const;

    void setMessageId(int messageId);

    int getChatId() const;

    void setChatId(int chatId);

    int getSenderId() const;

    void setSenderId(int senderId);

    const std::string &getMessage() const;

    void setMessage(const std::string &message);

    const std::string &getSendTime() const;

    void setSendTime(const std::string &sendTime);
};

#endif // BACKEND_MESSAGE_H
