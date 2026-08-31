cmake_minimum_required(VERSION 3.15)
project(atelier_minifb C CXX) # indique les langages utilisés : C et C++

set(CMAKE_C_STANDARD 11)

# Inclusion de minifb comme sous-projet
add_subdirectory(deps/minifb)

# Exécutable (démo)
add_executable(demo
	src/main.c
	src/utils/primitives.c
	src/utils/fonts.c
	src/demos/gravity.c
)
target_link_libraries(demo minifb)
