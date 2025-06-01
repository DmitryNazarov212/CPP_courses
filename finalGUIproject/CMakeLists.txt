cmake_minimum_required(VERSION 3.5)

project(ChatServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Network Core)
find_package(ODBC REQUIRED)

# Автоматическое подключение MOC, UIC и RCC
set(CMAKE_AUTUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)
# Исходные файлы
set(SOURCES_SERVER
    src/main.cpp
    src/ServerGUI.cpp
    src/ServerTCP.cpp
    src/DataBase.cpp
)
set(SOURCES_CLIENT
    src/main_client.cpp
    src/ClientTCP.cpp
    src/DataBase.cpp
)

# Заголовочные файлы
set(HEADERS_SERVER
    include/ServerGUI.h
    include/ServerTCP.h
    include/Logger.h
    include/DataBase.h
)
set(HEADERS_CLIENT
    include/ClientTCP.h
    include/Logger.h
    include/DataBase.h
)

# Формы Qt
set(FORMS
    ui/ServerGUI.ui
)


# Создаем исполняемый файл
add_executable(ChatServer
    ${FORMS}
    ${SOURCES_SERVER}
    ${HEADERS_SERVER}

)

add_executable(ChatClient
    ${FORMS}
    ${SOURCES_CLIENT}
    ${HEADERS_CLIENT}

)

# Подключаем зависимости
target_link_libraries(ChatServer
    Qt5::Widgets
    Qt5::Network
    Qt5::Core
    ${ODBC_LIBRARIES}
    pthread
)
target_link_libraries(ChatClient
    ${ODBC_LIBRARIES}
    pthread
)

# Для Windows добавляем определение
if(WIN32)
    add_definitions(-DQT_DEPRECATED_WARNINGS)
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()
