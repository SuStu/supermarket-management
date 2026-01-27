include("D:/QT_code/qt_pro/new_1/build-cmake-debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/test2-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase;qtserialport")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "D:/QT_code/qt_pro/new_1/build-cmake-debug/test2.exe"
    GENERATE_QT_CONF
)
