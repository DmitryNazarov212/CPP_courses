#include "../include/DataBase.h"
#include <iostream>
#include <string>

DataBase::DataBase() : sqlEnvHandle(nullptr), sqlConnHandle(nullptr), sqlStmtHandle(nullptr) {
}

DataBase::~DataBase() {
    if (sqlStmtHandle) SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    if (sqlConnHandle) SQLDisconnect(sqlConnHandle);
    if (sqlConnHandle) SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
    if (sqlEnvHandle) SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
}


bool DataBase::connect() {
    std::cout << "Attempting connection to SQL Server...\n";


    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle)) {
        std::cerr << "Failed to allocate environment handle\n";
        return false;
    }


    if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)) {
        std::cerr << "Failed to set ODBC version\n";
        SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
        return false;
    }


    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle)) {
        std::cerr << "Failed to allocate connection handle\n";
        SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
        return false;
    }

    const char* connStr = "DRIVER={MySQL ODBC 9.2 ANSI Driver};SERVER=localhost;PORT=3306;DATABASE=chatdb;UID=root;PWD=root;";
    SQLCHAR outStr[1024];
    SQLSMALLINT outStrLen;

    SQLRETURN ret = SQLDriverConnect(
        sqlConnHandle,
        nullptr,
        (SQLCHAR*)connStr, 
        SQL_NTS,
        outStr,
        sizeof(outStr),
        &outStrLen,
        SQL_DRIVER_NOPROMPT
    );

    if (SQL_SUCCESS != ret && SQL_SUCCESS_WITH_INFO != ret) {
        std::cerr << "Failed to connect to database\n";
        SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
        SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
        return false;
    }


    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle)) {
        std::cerr << "Failed to allocate statement handle\n";
        SQLDisconnect(sqlConnHandle);
        SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
        SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
        return false;
    }

    std::cout << "Connected to database successfully\n";
    return true;
}

bool DataBase::registerUser(const std::string& username, const std::string& password) {
    if (!sqlStmtHandle) {
        std::cerr << "Statement handle not initialized\n";
        return false;
    }

    // Используем подготовленные выражения
    const char* query = "INSERT INTO users (username, password) VALUES (?, ?)";
    if (SQL_SUCCESS != SQLPrepare(sqlStmtHandle, (SQLCHAR*)query, SQL_NTS)) {
        std::cerr << "Failed to prepare statement\n";
        return false;
    }

    // Привязываем параметры
    SQLCHAR* user = (SQLCHAR*)username.c_str();
    SQLCHAR* pass = (SQLCHAR*)password.c_str();
    SQLLEN userLen = username.length();
    SQLLEN passLen = password.length();

    if (SQL_SUCCESS != SQLBindParameter(sqlStmtHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 
                                       username.length(), 0, user, 0, &userLen) ||
        SQL_SUCCESS != SQLBindParameter(sqlStmtHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 
                                       password.length(), 0, pass, 0, &passLen)) {
        std::cerr << "Failed to bind parameters\n";
        return false;
    }

    // Выполняем запрос
    if (SQL_SUCCESS != SQLExecute(sqlStmtHandle)) {
        std::cerr << "Failed to execute statement\n";
        return false;
    }

    std::cout << "User registered: " << username << "\n";
    return true;
}


bool DataBase::authenticateUser(const std::string& username, const std::string& password) {
    if (!sqlStmtHandle) {
        std::cerr << "Statement handle not initialized\n";
        return false;
    }

    // Используем подготовленные выражения
    const char* query = "SELECT * FROM users WHERE username = ? AND password = ?";
    if (SQL_SUCCESS != SQLPrepare(sqlStmtHandle, (SQLCHAR*)query, SQL_NTS)) {
        std::cerr << "Failed to prepare statement\n";
        return false;
    }

    // Привязываем параметры
    SQLCHAR* user = (SQLCHAR*)username.c_str();
    SQLCHAR* pass = (SQLCHAR*)password.c_str();
    SQLLEN userLen = username.length();
    SQLLEN passLen = password.length();

    if (SQL_SUCCESS != SQLBindParameter(sqlStmtHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 
                                       username.length(), 0, user, 0, &userLen) ||
        SQL_SUCCESS != SQLBindParameter(sqlStmtHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 
                                       password.length(), 0, pass, 0, &passLen)) {
        std::cerr << "Failed to bind parameters\n";
        return false;
    }

    // Выполняем запрос
    if (SQL_SUCCESS != SQLExecute(sqlStmtHandle)) {
        std::cerr << "Failed to execute statement\n";
        return false;
    }

    // Проверяем результат
    if (SQL_SUCCESS == SQLFetch(sqlStmtHandle)) {
        std::cout << "User authenticated: " << username << "\n";
        SQLCloseCursor(sqlStmtHandle);
        return true;
    }

    SQLCloseCursor(sqlStmtHandle);
    return false;
}


