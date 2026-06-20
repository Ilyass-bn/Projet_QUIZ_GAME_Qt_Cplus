cmake_minimum_required(VERSION 3.16)

project(Projet_quiz_game VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia LinguistTools Sql Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia LinguistTools Sql Widgets Network)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Projet_quiz_game
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        first_game.h first_game.cpp first_game.ui


        food_game.h food_game.cpp food_game.ui
        world_cup.h world_cup.cpp world_cup.ui
        picture_world.h picture_world.cpp picture_world.ui
        picture_m.h picture_m.cpp picture_m.ui
        aichat.h aichat.cpp aichat.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Projet_quiz_game APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Projet_quiz_game SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Projet_quiz_game
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Projet_quiz_game PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia  Qt${QT_VERSION_MAJOR}::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Projet_quiz_game)
endif()
set_target_properties(Projet_quiz_game PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Projet_quiz_game
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
# On définit explicitement les fichiers de traduction
set(TS_FILES
    app_en.ts
    app_ar.ts
)

# Cette fonction gère la compilation des .ts en .qm
qt_add_translations(Projet_quiz_game
    TS_FILES ${TS_FILES}
)

# --- LA LIGNE MAGIQUE ---
# Cela crée une cible "update_translations" que tu pourras lancer manuellement
qt_add_lupdate(Projet_quiz_game TS_FILES ${TS_FILES})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Projet_quiz_game)
endif()

