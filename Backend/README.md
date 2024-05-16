# API Endpoints Documentation

## Table of Contents

- [User](#user)
  - [User Login](#user-login)
  - [Register User](#register-user)
  - [Get User Info](#get-user-info)
- [Admin](#admin)
  - [Get Dashboard](#get-dashboard)
- [Player](#player)
  - [Profile](#profile)
    - [Get Personal Profile](#get-personal-profile)
    - [Update Personal Profile](#update-personal-profile)
    - [Get Games Info](#get-games-info)
    - [Get Friends](#get-friends)
  - [Game](#game)
    - [Check Room Availability](#check-room-availability)
    - [Create New Game](#create-new-game)
    - [Start Game in Room](#start-game-in-room)
  - [Chat](#chat)
    - [Enable Chat Notifications](#enable-chat-notifications)
    - [Get Friends Chat](#get-friends-chat)
    - [Get Chat Room](#get-chat-room)
    - [Get Chat Messages](#get-chat-messages)
    - [Start Chat Session](#start-chat-session)
  - [Search](#search)
    - [Search by Username](#search-by-username)
    - [Add Friend](#add-friend)

## User

### User Login

Logs in a user.

- URL: `/api/login`
- Method: `POST`
- URL Params: None
- Request Body: JSON
  - `identifier` - (string) - username or email of the user
  - `password` - (string) - password of the user
    **Note:** the password should be hashed
- Example:
  ```
  POST /api/login
  {
    "identifier" : "example",
    "password" : "<hashed_password>"
  }
  ```
- Response:
  - Success:
    - Code: 200
    - Content:
    ```json
    {
      "token": "<authentication_token>",
      "userType": "player"
    }
    ```
  - Error:
    - Code: 200
    - Content:
    ```json
    {
      "error": "Invalid email or username"
    }
    ```

### Register User

Registers a new user.

- URL: `/api/register`
- Method: `POST`
- URL Params: None
- Request Body: JSON
  - `username` - (string) - username of the user
  - `firstName` - (string) - first name of the user
  - `lastName` - (string) - last name of the user
  - `email` - (string) - email of the user
  - `password` - (string) - password of the user
    **Note:** the password should be hashed
- Example:
  ```
  POST /api/register
  {
    "username" : "example",
    "firstName" : "example",
    "lastName" : "example",
    "email" : "example@example.com",
    "password" : "<hashed_password>"
  }
  ```
- Response:
  - Success:
    - Code: 200
    - Content:
    ```json
    {
      "token": "<authentication_token>",
      "userType": "player"
    }
    ```
  - Error:
    - Code: 200
    - Content:
    ```json
    {
      "error": "Username already exists"
    }
    ```

### Get User Info

Retrieves information about the authenticated user.

- URL: `/api/info`
- Method: `GET`
- Headers:
  - `Authorization` - (string) - authentication token
- Example:
  ```
  GET /api/info
  Authorization: <authentication_token>
  ```
- Response:
  - Success:
    - Code: 200
    - Content:
    ```json
    {
      "username": "example",
      "firstName": "example",
      "lastName": "example",
      "userType": "player"
    }
    ```
  - Error:
    - Code: 401
    - Content:
    ```json
    {
      "error": "Unauthorized"
    }
    ```

## Admin

### Get Dashboard

Retrieves the dashboard for an admin user.

- URL: `/api/admin/dashboard/:offset`
- Method: `GET`
- URL Params:
  - `offset` - (int) - offset for the time zone
- Headers:
  - `Authorization` - (string) - authentication token
- Example:
  ```
  GET /api/admin/dashboard/2
  Authorization: <authentication_token>
  ```
- Response:
  - Success:
    - Code: 200
    - Content:
    ```json
    {
      "totalPlayers": 0,
      "totalGames": 0,
      "totalWins": 0,
      "totalMessages": 0,
      "games": [],
      "messages": [],
      "players": []
    }
    ```
  - Error:
    - Code: 401

## Player

### Profile

#### Get Personal Profile

Retrieves the personal profile of the authenticated user.

- URL: `/api/profile/personal-info`
- Method: `GET`
- Headers:
  - `Authorization` - (string) - authentication token
- Example:
  ```
  GET /api/profile/personal-info
  Authorization: <authentication_token>
  ```
- Response:
  - Success:
    - Code: 200
    - Content:
    ```json
    {
      "username": "example",
      "firstName": "example",
      "lastName": "example",
      "email": "example@example.com",
      "userType": "player"
    }
    ```
  - Error:
    - Code: 401
    - Content:
    ```json
    {
      "error": "Unauthorized"
    }
    ```

#### Update Personal Profile

Updates the personal profile of the authenticated user.

- URL: `/api/profile/personal-info`
- Method: `PUT`
- Headers:
  - `Authorization` - (string) - authentication token
- Request Body: JSON
  Fields to be updated (e.g., firstname, username, password)
  **Note:** the password should be hashed
- Example:
  ```
  PUT /api/profile/personal-info
  {
    "firstName" : "example"
  }
  Authorization: <authentication_token>
  ```
- Response:
  - Success:
    - Code: 200
    - Content:
    ```json
    {
      "username": "example",
      "firstName": "example",
      "lastName": "example",
      "email": "example@example.com",
      "userType": "player"
    }
    ```
  - Error:
    - Code: 200
    - Content:
    ```json
    {
      "error": "Player update failed"
    }
    ```
    - Code: 401
    - Content:
    ```json
    {
      "error": "Unauthorized"
    }
    ```

#### Get Games Info

Retrieves information about the games played by the authenticated user.

- URL: `/api/profile/games-info/:offset`
- Method: `GET`
- URL Params:
  - `offset` - (int) - offset for the time zone
- Headers:
  - `Authorization` - (string) - authentication token
- Example:
  ```
  GET /api/profile/games-info/2
  Authorization: <authentication_token>
  ```
- Response:
  - Success:
    - Code: 200
    - Content:
    ```json
    {
      "games": [
        {
          "Date": "2024-03-08",
          "wins": 1,
          "loses": 1
        }
      ]
    }
    ```
  - Error:
    - Code: 401
    - Content:
    ```json
    {
      "error": "Unauthorized"
    }
    ```

#### Get Friends

Retrieves the profiles of friends of the authenticated user.

- URL: `/api/profile/friends`
- Method: `GET`
- Headers:
  - `Authorization` - (string) - authentication token
- Example:
  ```
  GET /api/profile/friends
  Authorization: <authentication_token>
  ```
- Response:
  - Success:
    - Code: 200
    - Content:
    ```json
    {
      "friends": [
        {
          "label": "EE"
        }
      ]
    }
    ```
  - Error:
    - Code: 401
    - Content:
    ```json
    {
      "error": "Unauthorized"
    }
    ```

### Game

#### Check Room Availability

Checks if a room is available.

- URL: `/api/game/check-room/:roomID`
- Method: `GET`
- URL Params:
  - `roomID` - (string) - ID of the room to check
- Headers:
  - `Authorization` - (string) - authentication token
- Example:
  ```
  GET /api/game/check-room/2D13G13
  Authorization: <authentication_token>
  ```
- Response:
  - Success:
    - Code: 200
    - Content:
    ```json
    {
      "message": "success"
    }
    ```
  - Error:
    - Code: 200
    - Content:
    ```json
    {
      "error": "there is no room with this ID"
    }
    ```
    - Code: 200
    - Content:
    ```json
    {
      "error": "there is no place in the room"
    }
    ```
    - Code: 401
    - Content:
    ```json
    {
      "error": "Unauthorized"
    }
    ```

#### Create New Game

Creates a new game.

- URL: `/api/game/new/:type`
- Method: `POST`
- URL Params:
  - `type` - (string) - type of the game
- Headers:
  - `Authorization` - (string) - authentication token
- Example:
  ```
  POST /api/game/new/S
  Authorization: <authentication_token>
  ```
- Response:
  - Success:
    - Code: 200
    - Content:
    ```json
    {
      "roomID": "2S11G11"
    }
    ```
  - Error:
    - Code: 200
    - Content:
    ```json
    {
      "error": "you are already in a game"
    }
    ```
    - Code: 401
    - Content:
    ```json
    {
      "error": "Unauthorized"
    }
    ```

#### Start Game in Room

Starts a game in a specific room.

- URL: `/api/game/start/:roomID`
- Method: `POST`
- URL Params:
  - `roomID` - (string) - ID of the room to start the game in
- Headers:
  - `Authorization` - (string) - authentication token
- Example:
  ```
  POST /api/game/start/2D13G13
  Authorization: <authentication_token>
  ```
- Response:
  - Success:
    - Code: 200
    - Content:
    ```json
    {
      "message": "success"
    }
    ```
  - Error:
  - Code: 200
    - Content:
    ```json
    {
      "error": "you are already in a game"
    }
    ```
    - Code: 200
    - Content:
    ```json
    {
      "error": "there is no room with this ID"
    }
    ```
    - Code: 401
    - Content:
    ```json
    {
      "error": "Unauthorized"
    }
    ```

### Chat

#### Enable Chat Notifications

Enables chat notifications for the authenticated user.

- URL: `/api/chat/notifications`
- Method: `POST`
- Headers:
  - `Authorization` - (string) - authentication token
- Example:
  ```
  POST /api/chat/notifications
  Authorization: <authentication_token>
  ```
- Response:
  - Success:
    - Code: 200
    - Content:
    ```json
    {
      "message": "success"
    }
    ```
  - Error:
    - Code: 401
    - Content:
    ```json
    {
      "error": "Unauthorized"
    }
    ```

#### Get Friends Chat

Retrieves friends of the authenticated user.

- URL: `/api/chat/friends`
- Method: `GET`
- Headers:
  - `Authorization` - (string) - authentication token
- Example:
  ```
  GET /api/chat/friends
  Authorization: <authentication_token>
  ```
- Response:
  - Success:
    - Code: 200
    - Content:
    ```json
    {
      "friends": [
        {
          "firstName": "example",
          "lastName": "example",
          "read": 1,
          "friendID": 1
        }
      ]
    }
    ```
  - Error:
    - Code: 401
    - Content:
    ```json
    {
      "error": "Unauthorized"
    }
    ```

#### Get Chat Room

Retrieves the chat room ID for communication with a specific friend.

- URL: `/api/chat/room/:friendID`
- Method: `GET`
- URL Params:
  - `friendID` - (int) - ID of the friend
- Headers:
  - `Authorization` - (string) - authentication token
- Example:
  ```
  GET /api/chat/room/3
  Authorization: <authentication_token>
  ```
- Response:
  - Success:
    - Code: 200
    - Content:
    ```json
    {
      "roomID": "2F3C1"
    }
    ```
  - Error:
    - Code: 200
    - Content:
    ```json
    {
      "error": "there is no friend with this ID"
    }
    ```
    - Code: 401
    - Content:
    ```json
    {
      "error": "Unauthorized"
    }
    ```

#### Get Chat Messages

Retrieves chat messages from a specific chat.

- URL: `/api/chat/:chatID`
- Method: `GET`
- URL Params:
  - `chatID` - (int) - ID of the chat
- Headers:
  - `Authorization` - (string) - authentication token
- Example:
  ```
  GET /api/chat/1
  Authorization: <authentication_token>
  ```
- Response:
  - Success:
    - Code: 200
    - Content:
    ```json
    {
      "messages": [
        {
          "message": "hello",
          "playerID": "2",
          "sendTime": "2024-03-08 00:49:25"
        }
      ]
    }
    ```
  - Error:
  - Code: 200
    - Content:
    ```json
    {
      "error": "there is no chat with this ID"
    }
    ```
    - Code: 200
    - Content:
    ```json
    {
      "error": "you are not in this chat"
    }
    ```
    - Code: 401
    - Content:
    ```json
    {
      "error": "Unauthorized"
    }
    ```

#### Start Chat Session

Initiates a chat session in a specific chat room.

- URL: `/api/chat/start/:roomID`
- Method: `POST`
- URL Params:
  - `roomID` - (string) - ID of the chat room
- Headers:
  - `Authorization` - (string) - authentication token
- Example:
  ```
  POST /api/chat/start/2F3C1
  Authorization: <authentication_token>
  ```
- Response:
  - Success:
    - Code: 200
    - Content:
    ```json
    {
      "message": "success"
    }
    ```
  - Error:
    - Code: 200
    - Content:
    ```json
    {
      "error": "there is no room with this ID"
    }
    ```
    - Code: 200
    - Content:
    ```json
    {
      "error": "you are not in this chat"
    }
    ```
    - Code: 401
    - Content:
    ```json
    {
      "error": "Unauthorized"
    }
    ```

### Search

#### Search by Username

Searches for users based on a query string.

- URL: `/api/search/:query`
- Method: `GET`
- URL Params:
  - `query` - (string) - query string to search for
- Headers:
  - `Authorization` - (string) - authentication token
- Example:
  ```
  GET /api/search/a
  Authorization: <authentication_token>
  ```
- Response:
  - Success:
    - Code: 200
    - Content:
    ```json
    {
      "players": [
        {
          "firstName": "example",
          "lastName": "example",
          "username": "example",
          "playerID": 3,
          "isFriend": 1
        }
      ]
    }
    ```
  - Error:
    - Code: 401
    - Content:
    ```json
    {
      "error": "Unauthorized"
    }
    ```

#### Add Friend

Adds a user as a friend.

- URL: `/api/add-friend/:friendID`
- Method: `POST`
- URL Params:
  - `friendID` - (int) - ID of the friend to add
- Headers:

  - `Authorization` - (string) - authentication token

- Example:
  ```
  POST /api/add-friend/3
  Authorization: <authentication_token>
  ```
- Response:
  - Success:
    - Code: 200
    - Content:
    ```json
    {
      "message": "success"
    }
    ```
  - Error:
  - Code: 200
    - Content:
    ```json
    {
      "error": "there is no user with this ID"
    }
    ```
    - Code: 200
    - Content:
    ```json
    {
      "error": "you can't add yourself as a friend"
    }
    ```
    - Code: 200
    - Content:
    ```json
    {
      "error": "you are already friend with this user"
    }
    ```
    - Code: 401
    - Content:
    ```json
    {
      "error": "Unauthorized"
    }
    ```
