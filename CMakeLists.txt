cmake_minimum_required(VERSION 3.10)
project(mon_mmo_serveur)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Boost
find_package(Boost 1.70 REQUIRED COMPONENTS system)

# PostgreSQL
find_package(PostgreSQL REQUIRED)

# Dossiers
set(SOURCE_DIR	${CMAKE_CURRENT_SOURCE_DIR}/Server)
set(INCLUDE_DIR	${CMAKE_CURRENT_SOURCE_DIR}/Include)

# Sources
set(SOURCES
	${SOURCE_DIR}/main_server.cpp
	${SOURCE_DIR}/server.cpp
	${SOURCE_DIR}/packet_handler.cpp
	${SOURCE_DIR}/db.cpp
)

# Headers
set(HEADERS
	${INCLUDE_DIR}/server.hpp
	${INCLUDE_DIR}/packet.hpp
	${INCLUDE_DIR}/packet_handler.hpp
	${INCLUDE_DIR}/player.hpp
	${INCLUDE_DIR}/struct_loot.hpp
	${INCLUDE_DIR}/db.hpp
)

add_executable(mon_mmo_serveur ${SOURCES} ${HEADERS})

target_include_directories(mon_mmo_serveur PRIVATE
	${INCLUDE_DIR}
	${SOURCE_DIR}
	${PostgreSQL_INCLUDE_DIRS}
)

target_link_libraries(mon_mmo_serveur PRIVATE
	Boost::system
	${PostgreSQL_LIBRARIES}
)