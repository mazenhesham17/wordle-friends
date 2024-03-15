# API

## User

### Login

POST `/api/login`

The request body needs to be in JSON format and include the following properties:

- `identifier` - String - Required
- `password` - String - Required

Example

```
POST /api/login
{
    "identifier" : "admin@wordle.com",
    "password" : "8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918"
}
```

**Note:** the password should be hashed

Response Example

```json
{
  "token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJpc3MiOiJzZXJ2ZXIiLCJ1c2VySUQiOiIxIiwidXNlclR5cGUiOiJhZG1pbiJ9.qPwyN_FJ06KBq0fF0e8ocsCy7vHEF9LhS1kpwHnObgw",
  "userType": "admin"
}
```

### Register

POST `/api/register`

The request body needs to be in JSON format and include the following properties:

- `username` - String - Required
- `firstName` - String - Required
- `lastName` - String - Required
- `email` - String - Required
- `password` - String - Required

Example

```
POST /api/register
{
    "username" : "mazen",
    "firstName" : "mazen",
    "lastName" : "hesham",
    "email" : "mazen@lgh.com",
    "password" : "5994471abb01112afcc18159f6cc74b4f511b99806da59b3caf5a9c173cacfc5"
}
```

**Note:** the password should be hashed

Response Example

```json
{
  "token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJpc3MiOiJzZXJ2ZXIiLCJ1c2VySUQiOiIxIiwidXNlclR5cGUiOiJhZG1pbiJ9.qPwyN_FJ06KBq0fF0e8ocsCy7vHEF9LhS1kpwHnObgw",
  "userType": "player"
}
```

### User info

GET `/api/info`

Example

```
GET /api/info
Authorization: <token>
```

**Authorization header is required**

Response Example

```json
{
  "username": "mazen",
  "firstName": "Mazen",
  "lastName": "Hesham",
  "userType": "Player"
}
```

## Player

### Search by username

GET `/api/search/:query`

Example

```
GET /api/search/a
Authorization: <token>
```

**Authorization header is required**

Response Example

```json
{
  "players": [
    {
      "firstName": "hazem",
      "lastName": "adel",
      "username": "hazem",
      "playerID": 3,
      "isFriend": 1
    },
    {
      "firstName": "abdelrahman",
      "lastName": "gamal",
      "username": "gamal",
      "playerID": 5,
      "isFriend": 1
    }
  ]
}
```

### Add friend

POST `api/add-friend/:friendID`

Example

```
POST /api/add-friend/5
Authorization: <token>
```

**Authorization header is required**

Response Example

```json
{ "message": "success" }
```
