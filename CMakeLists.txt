cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME dominion)

set(CMAKE_TOOLCHAIN_FILE /usr/local/lib/vcpkg/scripts/buildsystems/vcpkg.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED yes)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

project(${PROJECT_NAME})

find_package(fmt CONFIG REQUIRED)

add_executable(
	${PROJECT_NAME}
	main.cpp
	Karten.h
	Karten.cpp
	Spiel.h
	Spiel.cpp
	Spieler.h
	Spieler.cpp
	Zufall.h
	Zufall.cpp
)
	
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt fmt::fmt-header-only)
