cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(DSR)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

add_executable(dsr dsr.cc ${sources} ${headers})
target_link_libraries(dsr ${Geant4_LIBRARIES})

add_custom_target(Simulation DEPENDS dsr)


