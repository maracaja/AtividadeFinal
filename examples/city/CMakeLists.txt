project(city)
add_executable(${PROJECT_NAME} main.cpp 
                                window.cpp 
                                body.cpp 
                                ball.cpp)
enable_abcg(${PROJECT_NAME})
