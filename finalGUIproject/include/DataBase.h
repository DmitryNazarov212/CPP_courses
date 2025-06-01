#ifndef DATABASE_H
#define DATABASE_H

#include <sql.h>
#include <sqlext.h>
#include <string>

class DataBase {
public:
    DataBase();
    ~DataBase();
    bool connect();
    bool registerUser(const std::string& username, const std::string& password);
    bool authenticateUser(const std::string& username, const std::string& password);

private:
    SQLHENV sqlEnvHandle;
    SQLHDBC sqlConnHandle;
    SQLHSTMT sqlStmtHandle;
};

#endif // DATABASE_H
