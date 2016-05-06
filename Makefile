# makefile for cs3050 final project

Target = CS3050FinalProject
FILES = main.cpp trade_problem_generator/TradeProblemGenerator.cpp trade_problem_generator/TradeProblemGenerator.h StrategyFinder.cpp StrategyFinder.h

all: main.cpp
	g++ -o $(Target).exe -std=c++0x $(FILES)

clean:
	$(RM) $(Target).exe
