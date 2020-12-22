# documentation for configuring SFML with CMake : https://en.sfml-dev.org/forums/index.php?topic=24070.0

cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 14)

project(AlgorithmSimulator)

#location of project's files
include_directories(${CMAKE_SOURCE_DIR})

# directory for excutables
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# object files
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)


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
	set(SFML_STATIC_LIBRARIES TRUE)
	set(CMAKE_FIND_FRAMEWORK LAST)
	set(SFML_LIBRARY_DIR "./SFML_macOS/lib")
# Linux
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(STATUS "Linux detected")
	set(LINUX TRUE)
	#set(SFML_STATIC_LIBRARIES TRUE)
	set(SFML_DIR "./SFML_Linux/lib/cmake/SFML")
else()
	message(FATAL_ERROR "Your Operating System is not supported")
endif()


# after configuring the paths of sfml for windows, macOS and linux cmake needs only to find the below packages 
find_package(SFML 2.5 COMPONENTS network audio graphics window system REQUIRED)


# define & list the header an source files in the solution explorer
file(GLOB HEADERS "include/*.h")
file(GLOB SOURCES "SortingAlgorithmsSrc/*.cpp" "src/*.cpp")

# compiling the files
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

#if(SFML_FOUND)
	link_directories(${SFML_LIBRARY_DIR})
	# sfml .dll files and the .dll files for tgui
	target_link_libraries(${PROJECT_NAME} sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
#endif()


# this will allow us to install an .exe file of the project
install(TARGETS ${PROJECT_NAME} DESTINATION bin) #${CMAKE_INSTALL_PREFIX}/bin
install(FILES Main.cpp DESTINATION src)          #${CMAKE_INSTALL_PREFIX}/src