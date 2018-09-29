cmake_minimum_required(VERSION 3.2)
PROJECT(babilas)

set (babilas_VERSION_MAJOR 0)
set (babilas_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 5.11 REQUIRED COMPONENTS DBus Gui Qml Quick Widgets Xml)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QXmpp 0.9.4 REQUIRED) # TODO: Version
find_package(KF5Kirigami2 REQUIRED) # TODO: Version

add_subdirectory(translations)

set(babilas_SOURCES
    # C++ implementations
    src/account.hh
    src/account.cc
    src/accountmanager.cc
    src/accountmanager.hh
    src/client.cc
    src/client.hh
    src/contact.cc
    src/contact.hh
    src/constants.cc
    src/constants.hh
    src/conversation.cc
    src/conversation.hh
    src/photoprovider.cc
    src/photoprovider.hh
    # main source
    src/main.cc
    # QRC files
    src/qml/qml.qrc
    img/img.qrc
)

configure_file(src/babilas-config.hh.in babilas-config.hh)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(babilas
    ${babilas_SOURCES}
)

target_link_libraries(babilas
    Qt5::DBus
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    Qt5::Widgets
    KF5::Kirigami2
    QXmpp::QXmpp
)

install(TARGETS babilas RUNTIME DESTINATION bin)

