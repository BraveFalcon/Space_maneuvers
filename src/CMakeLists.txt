include_directories(../include)

add_executable(src
        ../main.cpp
        Body.cpp
        Jet_Body.cpp
        System_Bodies.cpp
        DrawObject.cpp
        Animation.cpp
        )

target_link_libraries(src GL GLU glut SOIL)