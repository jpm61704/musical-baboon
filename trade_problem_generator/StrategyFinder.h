//
// Created by Jack on 04/29/2016.
//

#ifndef MUSICAL_BABOON_STRATEGYFINDER_H
#define MUSICAL_BABOON_STRATEGYFINDER_H

#include <vector>
using namespace std;

//for main trade and gap storeage
//should I add pointers for the before and after pair?
struct trade_pair{
    bool isTrade, active;
    int transaction1, transaction2, value;
    trade_pair* before;
    trade_pair* after;
};

struct trade_pair_compare{
    bool operator()(trade_pair* t1, trade_pair* t2) const{
        return t1->value > t2->value;
    }
};

/*
 * used to rank trades and gaps for removal and merging
 */

class StrategyFinder {
public:
    StrategyFinder(vector<int> data);
    StrategyFinder();
    void decrementNumberOfTrades();
    int getNumberOfTrades();
    bool isActive();
    void printGaps();
    void printTrades();


private:
    int r;
    bool activated;

    vector<struct trade_pair*> trades;
    vector<struct trade_pair*> gaps;
    vector<int> raw_data;

    trade_pair* getLowestTrade();
    trade_pair* getLowestGap();
    trade_pair* popLowestTrade();
    trade_pair* popLowestGap();
    void mergeTrades(trade_pair* gap);
    void destroyTrade(trade_pair* trade);

    trade_pair* createPair(int max, int min, trade_pair* previous, trade_pair* next, bool isTrade);




};



#endif //MUSICAL_BABOON_STRATEGYFINDER_H
