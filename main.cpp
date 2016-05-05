#include <iostream>
#include <vector>
#include "trade_problem_generator/TradeProblemGenerator.h"
#include "trade_problem_generator/StrategyFinder.h"

using namespace std;

int main() {
    int days = 10;


    TradeProblemGenerator gen = TradeProblemGenerator(days);
    int* prob = gen.generateProblem();

    vector<int> problem;
    problem.assign(prob, prob+days);

    for(int i = 0; i < problem.size(); i++)
        cout << i << "\t" << problem[i] << endl;

    StrategyFinder finder = StrategyFinder(problem);

    finder.printTrades();
    finder.printGaps();
    cout << "++++++++++++++++++++++++++++" << endl;
    finder.decrementNumberOfTrades();
    finder.printTrades();
    finder.printGaps();
    cout << "++++++++++++++++++++++++++++" << endl;
    finder.decrementNumberOfTrades();
    finder.printTrades();
    finder.printGaps();
    cout << "++++++++++++++++++++++++++++" << endl;
    finder.decrementNumberOfTrades();
    finder.printTrades();
    finder.printGaps();
    delete prob;

    return 0;
}