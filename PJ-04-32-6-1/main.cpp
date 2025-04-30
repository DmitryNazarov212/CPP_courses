#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

class DBConnection {
public:
    virtual ~DBConnection() = default;
    virtual bool open() = 0;
    virtual bool execQuery(const std::string& query) = 0;
    virtual void close() = 0;
};


class ClassThatUsesDB {
private:
    DBConnection* dbConnection;

public:
    ClassThatUsesDB(DBConnection* connection) : dbConnection(connection) {}

    bool openConnection() {
        return dbConnection->open();
    }

    bool useConnection(const std::string& query) {
        return dbConnection->execQuery(query);
    }

    void closeConnection() {
        dbConnection->close();
    }
};

class MockDBConnection : public DBConnection {
public:
    MOCK_METHOD(bool, open, (), (override));
    MOCK_METHOD(bool, execQuery, (const std::string& query), (override));
    MOCK_METHOD(void, close, (), (override));
};

using ::testing::_;
using ::testing::Return;

TEST(ClassThatUsesDBTest, OpenConnection) {
    MockDBConnection mockConnection;
    ClassThatUsesDB obj(&mockConnection);

    EXPECT_CALL(mockConnection, open())
        .WillOnce(Return(true));

    EXPECT_TRUE(obj.openConnection());
}

TEST(ClassThatUsesDBTest, UseConnection) {
    MockDBConnection mockConnection;
    ClassThatUsesDB obj(&mockConnection);

    EXPECT_CALL(mockConnection, execQuery("SELECT * FROM table"))
        .WillOnce(Return(true));

    EXPECT_TRUE(obj.useConnection("SELECT * FROM table"));
}

TEST(ClassThatUsesDBTest, CloseConnection) {
    MockDBConnection mockConnection;
    ClassThatUsesDB obj(&mockConnection);

    EXPECT_CALL(mockConnection, close())
        .Times(1);

    obj.closeConnection();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}