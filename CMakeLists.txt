cmake_minimum_required(VERSION 2.6)

project(StoppingMuon)


find_package(Geant4 REQUIRED ui_all vis_all) #ui_all = user interface
                                             #vis_all = visualization interface



include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)

file(GLOB MACRO_FILES
    "*.mac"
)

file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(simulation main.cpp ${sources} ${headers})
target_link_libraries(simulation ${Geant4_LIBRARIES})

add_custom_target(StoppingMuon DEPENDS simulation)

