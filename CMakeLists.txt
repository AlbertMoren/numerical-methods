cmake_minimum_required(VERSION 3.10)
project(Trabalho1_MN1)
set(CMAKE_CXX_STANDARD 17)

include_directories(metodos)

# Cria o executável juntando o main com os arquivos da pasta 'metodos'
add_executable(sistema_jatos
    main.cpp
    metodos/math_jato.cpp
    metodos/bisseccao.cpp
    metodos/posicao_falsa.cpp
    metodos/newton_raphson.cpp
)