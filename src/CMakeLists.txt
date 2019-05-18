include_directories(../include)

add_executable(src
        ../main.cpp
        Body.cpp
        Jet_Body.cpp
        System_Bodies.cpp
        Animation.cpp
        )

target_link_libraries(src sfml-graphics sfml-window sfml-system GL)