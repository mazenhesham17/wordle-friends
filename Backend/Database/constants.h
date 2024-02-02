#ifndef BACKEND_CONSTANTS_H
#define BACKEND_CONSTANTS_H

# include <sqlite3.h>

extern const int QUERY_SIZE, ERROR_SIZE;
extern const char *DATABASE_FILE_NAME;
extern sqlite3 *db;

#endif //BACKEND_CONSTANTS_H
