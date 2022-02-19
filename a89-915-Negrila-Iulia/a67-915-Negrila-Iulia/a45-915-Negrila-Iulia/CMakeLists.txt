cmake_minimum_required(VERSION 3.17)
project(a45-915-Negrila-Iulia)

set(CMAKE_C_STANDARD 99)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\mingw81_64")
#set (CMAKE_PREFIX_PATH "D:\\Qt\\Tools\\CMake_64")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        domain/movie.cpp
        domain/movie.h
        tests/tests.cpp
        tests/tests.h
        repository/repository.cpp
        repository/repository.h
        repository/repository_exceptions.cpp
        repository/repository_exceptions.h
        service/service.cpp
        service/service.h
        domain/validator.cpp
        domain/validator.h
        ui/ui.cpp
        ui/ui.h
        user_data/watch_list.cpp
        user_data/watch_list.h
        user_data/file_watch_list.cpp
        user_data/file_watch_list.h
        user_data/csv_watch_list.cpp
        user_data/csv_watch_list.h
        user_data/html_watch_list.cpp
        user_data/html_watch_list.h
        gui/gui.cpp
        gui/gui.h
        gui/gui.ui
        gui/movies_table_model.cpp
        gui/movies_table_model.h
        main.cpp
        )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(a45-915-Negrila-Iulia
            ${PROJECT_SOURCES}
            )
else()
    if(ANDROID)
        add_library(a45-915-Negrila-Iulia SHARED
                ${PROJECT_SOURCES}
                )
    else()
        add_executable(a45-915-Negrila-Iulia
                ${PROJECT_SOURCES}
                )
    endif()
endif()

target_link_libraries(a45-915-Negrila-Iulia PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
