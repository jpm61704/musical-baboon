cmake_minimum_required(VERSION 3.3)
project(musical_baboon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp trade_problem_generator/TradeProblemGenerator.cpp trade_problem_generator/TradeProblemGenerator.h StrategyFinder.cpp StrategyFinder.h)s

add_executable(musical_baboon ${SOURCE_FILES})