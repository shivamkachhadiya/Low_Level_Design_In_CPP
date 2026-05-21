cmake_minimum_required(VERSION 4.2)

project(Low_Level_Design_CPP)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        .
        "Desgin Google Docs/include"
        "Zomato_System_Desgin/include"
)

# =========================
# Google Docs Project
# =========================

add_executable(design_google_docs
        "Desgin Google Docs/src/desgin_google_docs.cpp"
)

# =========================
# Strategy Design Pattern
# =========================

add_executable(strategy_pattern
        Strategy_Desgin_Pattern/Strategy.cpp
)

# =========================
# Factory Design Pattern
# =========================

add_executable(factory_pattern
        Factory_Desgin_Pattern/Factory.cpp
)

# =========================
# Zomato System Design
# =========================

add_executable(zomato_system
        Zomato_System_Desgin/main.cpp
        Zomato_System_Desgin/src/models/Order.cpp
)