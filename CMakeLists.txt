cmake_minimum_required(VERSION 3.22)

# Project configuration
project(CameraSensorDashboard
    VERSION 1.0.0
    DESCRIPTION "Camera and Sensor Data Acquisition Dashboard"
    LANGUAGES CXX
)

# Build configuration
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler-specific options
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
endif()

# Find required packages
find_package(Qt6 REQUIRED COMPONENTS 
    Core 
    Quick 
    QuickControls2 
    Charts 
    Multimedia
)

find_package(OpenCV REQUIRED
    COMPONENTS
        core
        imgproc
        imgcodecs
        videoio
        highgui
)

# Qt configuration
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Source files
set(SOURCES
    src/main.cpp
    src/CameraCapture.cpp
    src/SensorDataGenerator.cpp
    src/DataLogger.cpp
    src/PlaybackController.cpp
    src/ImageProvider.cpp
    src/ImageProviderWrapper.cpp
)

# Header files
set(HEADERS
    include/CameraCapture.h
    include/SensorDataGenerator.h
    include/DataLogger.h
    include/PlaybackController.h
    include/ImageProvider.h
    include/ImageProviderWrapper.h
)

# QML resources
set(QML_FILES
    qml/main.qml
    qml/CameraView.qml
    qml/ControlPanel.qml
    qml/PlaybackControls.qml
    qml/SensorChart.qml
    qml/SettingsPanel.qml
    qml/ErrorDialog.qml
)

qt6_add_resources(QML_RESOURCES qml/qml.qrc)

# Create executable
qt6_add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${QML_RESOURCES}
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    include
    ${OpenCV_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Charts
    Qt6::Multimedia
    ${OpenCV_LIBRARIES}
)

# Target properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
    OUTPUT_NAME "camera-sensor-dashboard"
)

# Platform-specific configurations
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
elseif(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in
    )
endif()

# Create data directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/data)

# Installation configuration
include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    BUNDLE DESTINATION .
)

if(UNIX AND NOT APPLE)
    install(FILES launch_dashboard.sh
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
                   GROUP_EXECUTE GROUP_READ
                   WORLD_EXECUTE WORLD_READ
    )
endif()

# Testing configuration
enable_testing()


# Package configuration
set(CPACK_PACKAGE_NAME "CameraSensorDashboard")
set(CPACK_PACKAGE_VENDOR "Camera Sensor Dashboard")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Camera and Sensor Data Acquisition Dashboard")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "CameraSensorDashboard")

if(WIN32)
    set(CPACK_GENERATOR "NSIS")
elseif(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
else()
    set(CPACK_GENERATOR "DEB;RPM")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "qt6-base-dev, libopencv-dev")
    set(CPACK_RPM_PACKAGE_REQUIRES "qt6-qtbase-devel, opencv-devel")
endif()

include(CPack)

# Print configuration summary
message(STATUS "")
message(STATUS "Camera Sensor Dashboard Configuration Summary:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Qt6 version: ${Qt6_VERSION}")
message(STATUS "  OpenCV version: ${OpenCV_VERSION}")
message(STATUS "  Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "")
