cmake_minimum_required(VERSION 3.16)

project(dcnow-qt6 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick QuickControls2)

qt_standard_project_setup()

qt_add_executable(appdcnow-qt6
    main.cpp
)

qt_add_resources(appdcnow-qt6 "resources"
    PREFIX "/dcnow"
    FILES
        dcnow/dcnow_bg/AFO.jpg
        dcnow/dcnow_bg/CHUCHU.jpg
        dcnow/dcnow_bg/FOURXFOUR.jpg
        dcnow/dcnow_bg/MAXPOOL.jpg
        dcnow/dcnow_bg/MONACO.jpg
        dcnow/dcnow_bg/MONACOPOD.jpg
        dcnow/dcnow_bg/MSR.jpg
        dcnow/dcnow_bg/NBA2K2.jpg
        dcnow/dcnow_bg/PSO.jpg
        dcnow/dcnow_bg/Q3.jpg
        dcnow/dcnow_bg/SA1.jpg
        dcnow/dcnow_bg/SA2.jpg
        dcnow/dcnow_bg/STARLANCER.jpg
        dcnow/dcnow_bg/TETRIS.jpg
        dcnow/dcnow_bg/TOYRACER.jpg
        dcnow/dcnow_bg/UNKNOWN.jpg
        dcnow/dcnow_bg/WWP.jpg

        dcnow/dcnow_covers/AFO.jpg
        dcnow/dcnow_covers/CHUCHU.jpg
        dcnow/dcnow_covers/CTAXI2.jpg
        dcnow/dcnow_covers/FOURXFOUR.jpg
        dcnow/dcnow_covers/MAXPOOL.jpg
        dcnow/dcnow_covers/MONACO.jpg
        dcnow/dcnow_covers/MONACOPOD.jpg
        dcnow/dcnow_covers/MSR.jpg
        dcnow/dcnow_covers/NBA2K2.jpg
        dcnow/dcnow_covers/OOGABOOGA.jpg
        dcnow/dcnow_covers/PLANETRING.jpg
        dcnow/dcnow_covers/PSO.jpg
        dcnow/dcnow_covers/Q3.jpg
        dcnow/dcnow_covers/SA1.jpg
        dcnow/dcnow_covers/SA2.jpg
        dcnow/dcnow_covers/STARLANCER.jpg
        dcnow/dcnow_covers/TETRIS.jpg
        dcnow/dcnow_covers/TOYRACER.jpg
        dcnow/dcnow_covers/WWP.jpg

        dcnow/icon-loading.png
        dcnow/icon-refresh.png
)

qt_add_qml_module(appdcnow-qt6
    URI dcnow
    VERSION 1.0
    SOURCES
        dcnow/basicgameinfometa.h
        dcnow/basicgameinfometa.cpp

        dcnow/gameinfo.h
        dcnow/gameinfo.cpp
        dcnow/gameinfomodel.h
        dcnow/gameinfomodel.cpp

        dcnow/gameinfofiltermodel.h
        dcnow/gameinfofiltermodel.cpp

        dcnow/userinfo.h
        dcnow/userinfo.cpp
        dcnow/userinfomodel.h
        dcnow/userinfomodel.cpp
        dcnow/userinfofiltermodel.cpp
        dcnow/userinfofiltermodel.h
        dcnow/util.h
        dcnow/util.cpp
    QML_FILES
        dcnow/main.qml
        dcnow/dcartcollection.js
        dcnow/SettingsPage.qml
        dcnow/UsersPage.qml
        dcnow/ListHeader.qml
        dcnow/ListLoading.qml
        dcnow/GamesPage.qml
        dcnow/GameSchedule.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appdcnow-qt6 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appdcnow-qt6
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appdcnow-qt6
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2
)

include_directories(${CMAKE_SOURCE_DIR}/dcnow)

include(GNUInstallDirs)
install(TARGETS appdcnow-qt6
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
