#include <iostream>
#include <vector>
#include <stdio.h>
#include "trade_problem_generator/TradeProblemGenerator.h"
#include "trade_problem_generator/StrategyFinder.h"

using namespace std;

vector<unsigned int> parse(int days,char* filename);

int main(int argc, char** argv) {
    unsigned int days = atoi(argv[1]);
    unsigned int trades = atoi(argv[2]);

    vector<unsigned int> problem = parse(days, argv[3]);

    StrategyFinder finder = StrategyFinder(problem);

    while (finder.getNumberOfTrades() > trades){
        finder.decrementNumberOfTrades();
    }

    finder.printFinalTrades();


    return 0;
}

vector<unsigned int> parse(int days,char* filename){
    unsigned int value;

    vector<unsigned int> v;

    FILE* fp = fopen(filename, "r");

    for(unsigned int i = 0; i < days; i++){
        fscanf(fp, "%d", &value);
        v.push_back(value);
    }



    fclose(fp);

    return v;

}