#include "NotificationSession.h"
#include "../Controller/SocketController.h"

NotificationSession::NotificationSession(tcp::socket &&socket, const std::string &roomId, int playerId)
	: Session(std::move(socket), roomId, playerId) {}

void NotificationSession::launchSession()
{
	try
	{
		accept();

		asyncReceive();

		SocketController::getInstance()->waitForAsyncOperations();
	}
	catch (beast::system_error const &se)
	{
		if (se.code() != websocket::error::closed)
		{
			std::cerr << "Beast error: " << se.code().message() << std::endl;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception error: " << e.what() << std::endl;
	}
}

bool NotificationSession::isFinished()
{
	return false;
}
