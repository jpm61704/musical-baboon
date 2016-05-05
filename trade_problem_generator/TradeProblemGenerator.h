//
// Created by Jack on 04/24/2016.
//

#ifndef MUSICAL_BABOON_TRADEPROBLEMGENERATOR_H
#define MUSICAL_BABOON_TRADEPROBLEMGENERATOR_H

#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

class TradeProblemGenerator {
public:
    TradeProblemGenerator(int n);

    int* generateProblem();
    int* generateProblem(int n);
    void writeProblemToFile(string file);
private:
    int days;
};


#endif //MUSICAL_BABOON_TRADEPROBLEMGENERATOR_H
