#include <iostream>
#include <vector>
#include <stdio.h>
#include "trade_problem_generator/TradeProblemGenerator.h"
#include "StrategyFinder.h"

using namespace std;

vector<unsigned int> parse(int days,char* filename);

/**
 * main program logic, contains cmd line parsing and some other errors
 */
int main(int argc, char** argv) {

    if(argc != 4){
        printf("Invalid number of command line arguments\nsee README.md");
        exit(6);
    }


    unsigned int days = strtoul(argv[1], nullptr, 0);
    unsigned int trades = strtoul(argv[2], nullptr, 0);

    vector<unsigned int> problem = parse(days, argv[3]);

    if(trades < 1){
        printf("must have at least 1 trade");
        exit(2);
    }


    StrategyFinder finder = StrategyFinder(problem);

    //remove atrade until desired trades reached
    while (finder.getNumberOfTrades() > trades){
        finder.decrementNumberOfTrades();
    }

    finder.printFinalTrades();


    return 0;
}

/**
 * parser for the program
 */
vector<unsigned int> parse(int days,char* filename){
    double value;

    vector<unsigned int> v;

    FILE* fp = fopen(filename, "r");

    if(fp == nullptr) {
        printf("File could not be opened");
        fclose(fp);
        exit(1);
    }

    for(unsigned int i = 0; i < days; i++){
        int matched = fscanf(fp, "%lf", &value);
        if(matched != 1){//invalid characters
            printf("Parsing Error: Invalid Format");
            fclose(fp);
            exit(3);
        }
        if(value < 0){//negative value
            printf("Parsing Error: Negative Number");
            fclose(fp);
            exit(4);
        }
        unsigned int submit = (unsigned int)value;
        if((value - (double)submit) != 0){//decimal is included
            printf("Parsing Error: Decimal Value");
            fclose(fp);
            exit(5);
        }

        v.push_back(submit);
    }



    fclose(fp);

    return v;

}
