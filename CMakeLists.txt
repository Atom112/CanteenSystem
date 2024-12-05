cmake_minimum_required(VERSION 3.29)
project(CanteenSystem C)

set(CMAKE_C_STANDARD 11)

add_executable(
        Functions.h
        ReadMenu.c
        Order.c
        TableFeedback.c
        TakeOutFeedback.c
        AddToSum.c
        CanteenSystem.c
        CustomerMode.c
        ManagerMode.c
        AddDish.c
        DeleteDish.c
        SearchDish.c
        EditDishInfo.c
)
