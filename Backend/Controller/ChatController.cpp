#include "ChatController.h"

ChatController *ChatController::instance = nullptr;

ChatController::ChatController()
{
    chatWebView = ChatWebView::getInstance();
}

ChatController *ChatController::getInstance()
{
    if (instance == nullptr)
    {
        instance = new ChatController();
    }
    return instance;
}

bool ChatController::isChatExist(const int &chatID)
{
    return dbIsChatExist(chatID);
}

bool ChatController::isPlayerInChat(const int &chatID, const int &playerID)
{
    return dbIsPlayerInChat(chatID, playerID);
}

Message ChatController::retrieveMessageFromDB(const int &messageID)
{
    Message message;
    try
    {
        message.setMessageId(messageID);
        message.setChatId(getChatIDByMessageID(messageID));
        message.setSenderId(getSenderIDByMessageID(messageID));
        message.setMessage(getContentByMessageID(messageID));
        message.setSendTime(getSendTimeByMessageID(messageID));
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception error :" << e.what() << std::endl;
    }
    return message;
}

std::string ChatController::getChat(const int &chatID)
{
    std::vector<std::pair<int, std::pair<std::string, std::string>>> messages;
    std::vector<int> messageIDs = getChatListByChatID(chatID);
    for (auto &messageID : messageIDs)
    {
        Message message = retrieveMessageFromDB(messageID);
        messages.emplace_back(message.getSenderId(), std::make_pair(message.getMessage(), message.getSendTime()));
    }
    try
    {
        std::string chat = chatWebView->getChat(messages);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception error :" << e.what() << std::endl;
    }
    return ChatWebView::getInstance()->getChat(messages);
}

int ChatController::getChatID(const int &playerID, const int &friendID)
{
    int chatID = getChatIDByPlayerID(playerID, friendID);
    if (chatID == -1)
    {
        return addChat(playerID, friendID);
    }
    return chatID;
}

int ChatController::getChatID(const std::string &roomID)
{
    return std::stoi(roomID.substr(roomID.find("C") + 1));
}

int ChatController::addChat(const int &playerID, const int &friendID)
{
    int chatID = dbAddChat();
    addPlayerToChat(playerID, chatID);
    addPlayerToChat(friendID, chatID);
    return chatID;
}

std::string ChatController::addMessage(const int &senderID, const int &chatID, const std::string &content)
{
    int messageID = addMessageToChat(senderID, chatID, content.c_str());
    return ChatWebView::getInstance()->message(senderID, content, getSendTimeByMessageID(messageID));
}