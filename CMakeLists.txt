cmake_minimum_required(VERSION 3.19)
project(test2 LANGUAGES CXX)

# 方法1：使用 Qt6 COMPONENTS 方式
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets SerialPort Sql)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUMOC ON)
set(CMAKE_AUTOURCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_standard_project_setup()

qt_add_executable(test2
    WIN32 MACOSX_BUNDLE
    main.cpp
    login_main_form.cpp
    login_main_form.h
    login_main_form.ui
    user_form.h
    user_form.cpp
    user_form.ui
    admin_form.cpp
    admin_form.h
    admin_form.ui
)

# 使用 Qt6::Sql
target_link_libraries(test2
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::SerialPort
        Qt::Sql
)


include(GNUInstallDirs)
install(TARGETS test2
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET test2
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
