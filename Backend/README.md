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
  "token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJpc3MiOiJzZXJ2ZXIiLCJ1c2VySUQiOiIxIiwidXNlclR5cGUiOiJhZG1pbiJ9.qPwyN_FJ06KBq0fF0e8ocsCy7vHEF9LhS1kpwHnObgw"
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
  "token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJpc3MiOiJzZXJ2ZXIiLCJ1c2VySUQiOiIxIiwidXNlclR5cGUiOiJhZG1pbiJ9.qPwyN_FJ06KBq0fF0e8ocsCy7vHEF9LhS1kpwHnObgw"
}
```
