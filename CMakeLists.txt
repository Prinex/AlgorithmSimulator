# documentation for configuring SFML with CMake : https://en.sfml-dev.org/forums/index.php?topic=24070.0

cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)

project(AlgorithmSimulator)

#location of project's files
include_directories(${CMAKE_SOURCE_DIR})

# directory for excutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# configuring SFML for windows
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message(STATUS "Windows detected")
	set(WINDOWS TRUE)
	set(SFML_STATIC_LIBRARIES TRUE)
	set(SFML_DIR "./SFML_Win/lib/cmake/SFML")
# MacOS
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    	message(STATUS "MacOS detected")
	set(MACOSX TRUE)
	set(SFML_DIR "./SFML_macOS/Frameworks/SFML.framework/Resources/CMake")
# Linux
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    	message(STATUS "Linux detected")
	set(LINUX TRUE)
	set(SFML_DIR "./SFML_Linux/lib/cmake/SFML")
else()
	message(FATAL_ERROR "Your Operating System is not supported")
endif()


# after configuring the paths of sfml for windows, macOS and linux cmake needs only to find the below packages 
find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)


# define & list the header an source files in the solution explorer
file(GLOB HEADERS "include/*.h")
file(GLOB SOURCES "SortingAlgorithmsSrc/*.cpp" "src/*.cpp")

# compiling the files
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
# linking SFML's libraries
link_directories(${SFML_LIBRARY_DIR})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window)


# this will allow us to install an .exe file of the project
install(TARGETS ${PROJECT_NAME} DESTINATION bin) #${CMAKE_INSTALL_PREFIX}/bin
install(FILES ./src/Main.cpp DESTINATION src)    #${CMAKE_INSTALL_PREFIX}/src