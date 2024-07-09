cmake_minimum_required(VERSION 3.28)
project(Zomato)

set(CMAKE_CXX_STANDARD 20)

add_executable(Zomato main.cpp
        services/Restraunt.h
        headers/Menu.h
        headers/Amount.h
        headers/Order.h
        headers/SelectionStrategy.h
        headers/Application.h
        services/Restraunt.cpp
        services/LowestCostSelectionStrategy.cpp
        services/Zomato.cpp
        services/Zomato.h
        services/LowestCostSelectionStrategy.h
)
