cmake_minimum_required(VERSION 3.10)
project(mon_mmo_serveur)

# Trouver Boost (nécessaire pour ASIO)
find_package(Boost 1.70 REQUIRED COMPONENTS system)

# Dossiers sources et include
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Server)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Include)
set(PLAYER_SYSTEM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Player_System)
set(PVE_SYSTEM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/PVE_System)

# Fichiers sources (liste explicite pour éviter les erreurs de GLOB)
set(SOURCES
	${SOURCE_DIR}/main_server.cpp
	${SOURCE_DIR}/server.cpp
	${SOURCE_DIR}/NetworkManager/packet_handler.cpp
)

set(HEADERS
	${INCLUDE_DIR}/server.hpp
	${INCLUDE_DIR}/packet.hpp
	${INCLUDE_DIR}/packet_handler.hpp
	${INCLUDE_DIR}/player.hpp
	${INCLUDE_DIR}/struct_loot.hpp
)

# Exécutable
add_executable(mon_mmo_serveur ${SOURCES} ${HEADERS})

# Inclure les dossiers
target_include_directories(mon_mmo_serveur PRIVATE
    ${INCLUDE_DIR}
    ${SOURCE_DIR}
    ${PLAYER_SYSTEM_DIR}
    ${PVE_SYSTEM_DIR}
)

# Lier Boost
target_link_libraries(mon_mmo_serveur PRIVATE Boost::system)

# Options de compilation
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_executable(mon_mmo_serveur ${SOURCES} ${HEADERS})
