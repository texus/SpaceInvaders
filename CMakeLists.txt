cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -pedantic")

set(SPACE_INVADERS_SRC
    src/main.cpp
    src/Client.cpp
    src/Observable.cpp
    src/Controller/Controller.cpp
    src/Controller/EnemyController.cpp
    src/Controller/PlayerController.cpp
    src/Controller/PowerupController.cpp
    src/Controller/Powerups.cpp
    src/Controller/WallController.cpp
    src/Factory/DebugEntityFactory.cpp
    src/Model/Entities.cpp
    src/Model/Gun.cpp
    src/View/AbstractView.cpp
    src/View/SFMLEntityRepresentation.cpp
    src/View/SFMLView.cpp
)

include_directories("${PROJECT_SOURCE_DIR}/include")

find_package(SFML 2 COMPONENTS graphics window system)

add_executable(SpaceInvaders ${SPACE_INVADERS_SRC})
target_link_libraries(SpaceInvaders ${SFML_LIBRARIES})

install(TARGETS SpaceInvaders DESTINATION ${PROJECT_SOURCE_DIR})
