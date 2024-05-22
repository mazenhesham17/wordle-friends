#include "GameController.h"

GameController *GameController::instance = nullptr;

GameController *GameController::getInstance()
{
    if (instance == nullptr)
    {
        // Create an input filestream
        std::ifstream jsonFile("words.json");
        // Initialize the json object
        nlohmann::json jsonData;
        // Read the json file into the json object
        jsonFile >> jsonData;
        // Close the filestream
        jsonFile.close();

        instance = new GameController();
        instance->words = jsonData;
    }
    return instance;
}

bool GameController::isPlayerInGame(const int &playerID)
{
    return dbIsPlayerInGame(playerID);
}

int GameController::newGame(const std::string &word)
{
    int gameID = addGame(word.c_str());
    return gameID;
}

void GameController::joinGame(const int &gameId, const int &playerId)
{
    addPlayerToGame(playerId, gameId);
}

void GameController::startGame(const int &gameId)
{
    dbStartGame(gameId);
}

std::string GameController::getRandomWord()
{
    return words[rand() % words.size()];
}

std::string GameController::submitGuess(const std::string &guess, const int &gameId)
{
    std::string word = getWordByGameID(gameId);
    std::string result(word.size(), '_');
    for (int i = 0; i < word.size(); i++)
    {
        word[i] = tolower(word[i]);
        if (word[i] == tolower(guess[i]))
        {
            result[i] = '+';
        }
        else if (word.find(tolower(guess[i])) != -1)
        {
            result[i] = '-';
        }
    }
    result = "Result: " + result;
    return result;
}

void GameController::winGame(const int &gameId, const int &playerId)
{
    dbWinGame(playerId, gameId);
}

bool GameController::match(const std::string &guess, const int &gameId)
{
    std::string word = getWordByGameID(gameId);
    std::string copyGuess = guess;
    for (int i = 0; i < word.size(); i++)
    {
        word[i] = tolower(word[i]);
        copyGuess[i] = tolower(copyGuess[i]);
    }
    return word == copyGuess;
}

void GameController::endGame(const int &gameId)
{
    dbEndGame(gameId);
}

std::string GameController::getMergedTemplate(const std::vector<std::string> &history, const int &gameId)
{
    std::string word = getWordByGameID(gameId);
    std::string result(word.size(), '_');
    std::set<char> matched, unmatched, mismatched;
    std::set<int> idx;
    for (int i = 0; i < word.size(); i++)
    {
        bool isMatched = false;
        for (int j = 0; j < history.size(); j++)
        {
            if (tolower(history[j][i]) == tolower(word[i]))
            {
                isMatched = true;
                break;
            }
        }
        if (isMatched)
        {
            result[i] = '+';
            matched.insert(tolower(word[i]));
        }
        else
        {
            unmatched.insert(tolower(word[i]));
            idx.insert(i);
        }
    }

    for (int i = 0; i < word.size(); i++)
    {
        for (int j = 0; j < history.size(); j++)
        {
            if (matched.find(tolower(history[j][i])) == matched.end() && unmatched.find(tolower(history[j][i])) != unmatched.end())
            {
                mismatched.insert(tolower(history[j][i]));
            }
        }
    }

    while (!idx.empty() && !mismatched.empty())
    {
        int i = *idx.begin();
        result[i] = '-';
        idx.erase(i);
        mismatched.erase(mismatched.begin());
    }
    result = "Opponent's result: " + result;
    return result;
}

void GameController::deleteGame(const int &gameId)
{
    dbDeleteGame(gameId);
}
