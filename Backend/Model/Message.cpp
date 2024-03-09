#include "Message.h"

int Message::getMessageId() const
{
    return messageID;
}

void Message::setMessageId(int messageId)
{
    messageID = messageId;
}

int Message::getChatId() const
{
    return chatID;
}

void Message::setChatId(int chatId)
{
    chatID = chatId;
}

int Message::getSenderId() const
{
    return senderID;
}

void Message::setSenderId(int senderId)
{
    senderID = senderId;
}

const std::string &Message::getMessage() const
{
    return message;
}

void Message::setMessage(const std::string &message)
{
    Message::message = message;
}

const std::string &Message::getSendTime() const
{
    return sendTime;
}

void Message::setSendTime(const std::string &sendTime)
{
    Message::sendTime = sendTime;
}
