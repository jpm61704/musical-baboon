#include <iostream>
#include <vector>
#include "trade_problem_generator/TradeProblemGenerator.h"
#include "trade_problem_generator/StrategyFinder.h"

using namespace std;

int main() {
    int days = 10;


    TradeProblemGenerator gen = TradeProblemGenerator(days);
    int* prob = gen.generateProblem();

    vector<int> problem = {5,9,4,6,1,8,4,2,3,3};
    //problem.assign(prob, prob+days);

    for(int i = 0; i < problem.size(); i++)
        cout << i << "\t" << problem[i] << endl;

    StrategyFinder finder = StrategyFinder(problem);


    while (finder.getNumberOfTrades() > 0){
        cout << "===" << finder.getNumberOfTrades() << "===" << endl;
        finder.printTrades();
        finder.printGaps();
        finder.decrementNumberOfTrades();
    }

    return 0;
}