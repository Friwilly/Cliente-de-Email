cmake_minimum_required(VERSION 3.16)

project(Teste_GUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ativa a magica do qt (geração automatica de codigo para a interface)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Procura a biblioteca do Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Adiciona os arquivos fontes do projeto
add_executable(Teste_GUI
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

# Conecta o seu executável com o Qt6 e com a biblioteca VMime
target_link_libraries(Teste_GUI PRIVATE
    Qt6::Widgets
    vmime
)