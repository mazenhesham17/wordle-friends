cmake_minimum_required(VERSION 3.22)
project(Backend)

set(CMAKE_CXX_STANDARD 17)

find_package(SQLite3 REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(${SQLite3_INCLUDE_DIRS})


add_executable(
        Backend Database/constants.h
        Database/dml.cpp
        Database/dml.h
        Database/dql.cpp
        Database/dql.h
        Model/User.cpp
        Model/User.h
        Model/Player.cpp
        Model/Player.h
        Model/Admin.cpp
        Model/Admin.h
        Model/Response.cpp
        Model/Response.h
        Controller/PlayerController.cpp
        Controller/PlayerController.h
        Controller/UserController.cpp
        Controller/UserController.h
        Controller/AdminController.cpp
        Controller/AdminController.h
        Controller/ResponseController.cpp
        Controller/ResponseController.h
        API/UserAPI.cpp
        API/UserAPI.h
        API/PlayerAPI.cpp
        API/PlayerAPI.h
        API/AdminAPI.cpp
        API/AdminAPI.h
        WebView/TokenWebView.cpp
        WebView/TokenWebView.h
        WebView/AdminWebView.cpp
        WebView/AdminWebView.h
        WebView/PlayerWebView.cpp
        WebView/PlayerWebView.h
        main.cpp
        Controller/TokenController.cpp
        Controller/TokenController.h
        Controller/BaseController.h
        Controller/ServerController.cpp
        Controller/ServerController.h
        Controller/SocketController.cpp
        Controller/SocketController.h
        Controller/GameController.cpp
        Controller/GameController.h
        Controller/RoomController.cpp
        Controller/RoomController.h
        Model/Room.cpp
        Model/Room.h
        Model/RoomContainer.cpp
        Model/RoomContainer.h
        Session/Session.cpp
        Session/Session.h
        Session/SingleGameSession.cpp
        Session/SingleGameSession.h
        Session/DuoGameSession.cpp
        Session/DuoGameSession.h
        WebView/RoomWebView.cpp
        WebView/RoomWebView.h
        Controller/AuthenticationController.cpp
        Controller/AuthenticationController.h
        Session/GameSession.cpp
        Session/GameSession.h
)

add_executable(
        Initialize_Database Database/constants.h
        Database/ddl.cpp
)

target_link_libraries(Initialize_Database ${SQLite3_LIBRARIES})
target_link_libraries(Backend ${SQLite3_LIBRARIES} OpenSSL::Crypto)