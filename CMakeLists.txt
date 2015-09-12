cmake_minimum_required(VERSION 2.8.9)
project(LCDDisplays)

include_directories(/usr/local/include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

# Set JAVA_HOME from environment, or default to known development locations
set(JAVA_HOME $ENV{JAVA_HOME})
if("${JAVA_HOME}" STREQUAL "")
    message(STATUS "JAVA_HOME not set in envrionment, attempting to default...")
    # Check for the oracle jvm on our debian image
    if(EXISTS /usr/lib/jvm/jdk-8-oracle-arm-vfp-hflt)
        set(JAVA_HOME /usr/lib/jvm/jdk-8-oracle-arm-vfp-hflt)
    elseif(EXISTS /usr/lib/jvm/jdk1.8.0_51)
        set(JAVA_HOME /usr/lib/jvm/jdk1.8.0_51)
        message(STATUS "Using Oracle JDK=${JAVA_HOME}")
    elseif(EXISTS /Library/Java/JavaVirtualMachines/jdk1.8.0_45.jdk/Contents/Home)
        set(JAVA_HOME /Library/Java/JavaVirtualMachines/jdk1.8.0_45.jdk/Contents/Home)
        message(STATUS "Using Mac JDK=${JAVA_HOME}")
    else()
        # Default to a download in my envrionment
        set(JAVA_HOME /root/Downloads/jdk1.8.0_45)
        message(STATUS "JAVA_HOME defaulting to ${JAVA_HOME}")
    endif()
endif()
# Validate it has the jni headers
if(EXISTS ${JAVA_HOME}/include AND EXISTS ${JAVA_HOME}/include/linux)
    include_directories(${JAVA_HOME}/include ${JAVA_HOME}/include/linux)
    message(STATUS "Using JDK=${JAVA_HOME}")
elseif(EXISTS ${JAVA_HOME}/include AND EXISTS ${JAVA_HOME}/include/darwin)
    include_directories(${JAVA_HOME}/include ${JAVA_HOME}/include/darwin)
    message(STATUS "Using Mac JDK=${JAVA_HOME}, development only mode")
else()
    message(FATAL_ERROR "${JAVA_HOME}/include and ${JAVA_HOME}/include/linux do not exist. Check that JAVA_HOME points to a JDK.")
endif()

find_library(WiringPi_Libs NAMES wiringPi)
if(WiringPi_Libs)
    MESSAGE(STATUS "Found WiringPi_Libs: ${WiringPi_Libs}")
endif()
find_library(WiringPiDev_Libs NAMES wiringPiDev)
if(WiringPiDev_Libs)
    MESSAGE(STATUS "Found WiringPi_Libs: ${WiringPiDev_Libs}")
endif()
if(WiringPi_Libs AND WiringPiDev_Libs)
    set(WiringPi_LIBRARIES ${WiringPiDev_Libs} ${WiringPi_Libs})
    set(WiringPi_FOUND true)
    ADD_DEFINITIONS(-DHAVE_LCD_DISPLAY)
    MESSAGE(STATUS "Using WiringPi: ${WiringPi_LIBRARIES}")
    MESSAGE(STATUS "Added lcd source to build")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    MESSAGE(STATUS "Skipping wiringPi check on Darwin")
    set(WIRING_PI_HOME /Users/starksm/Dev/IoT/wiringPi)
    include_directories(${WIRING_PI_HOME}/wiringPi ${WIRING_PI_HOME}/devLib)
else()
endif()

# The LCD library
add_library (lcdDisplayObjs OBJECT PCD8544.c AbstractLcdView.cpp MiniLcdPCD8544.cpp WiringPiLcdDisplay.cpp org_jboss_rhiot_beacon_lcd_MiniLcdPCD8544.cpp)
add_library (lcdDisplay SHARED $<TARGET_OBJECTS:lcdDisplayObjs>)
target_link_libraries(lcdDisplay wiringPiDev wiringPi)
install(TARGETS lcdDisplay
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)
