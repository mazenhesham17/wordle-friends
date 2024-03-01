#include "Session.h"

Session::Session()
{
    gameController = GameController::getInstance();
    roomController = RoomController::getInstance();
}
