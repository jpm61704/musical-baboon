
//
// Created by Jack on 04/24/2016.
//

#include "TradeProblemGenerator.h"

TradeProblemGenerator::TradeProblemGenerator(int n) {
    srand(time(NULL));
    days = n;
}

int *TradeProblemGenerator::generateProblem() {
    return generateProblem(days);
}

int *TradeProblemGenerator::generateProblem(int n) {

    int* problem = new int[n];

    for(int i = 0; i < n; i++){
        problem[i] = rand() % n;
    }

    return problem;
}

void TradeProblemGenerator::writeProblemToFile(string file) {

}