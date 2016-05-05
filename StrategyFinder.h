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
    unsigned int transaction1, transaction2, value;
    trade_pair* before;
    trade_pair* after;
};

struct trade_pair_compare{
    bool operator()(trade_pair* t1, trade_pair* t2) const{
        return t1->value > t2->value;
    }
};

struct trade_pair_compare_for_print{
    bool operator()(trade_pair* t1, trade_pair* t2) const{
        if(t1->active && t2->active)
            return t1->transaction1 < t2->transaction1;
        else if(t1->active)
            return true;
        else
            return false;
    }
};

/*
 * used to rank trades and gaps for removal and merging
 */

class StrategyFinder {
public:
    StrategyFinder(vector<unsigned int> data);
    ~StrategyFinder();
    void decrementNumberOfTrades();
    unsigned int getNumberOfTrades();
    void printGaps();
    void printTrades();
    void printFinalTrades();


private:
    unsigned int r;

    vector<struct trade_pair*> trades;
    vector<struct trade_pair*> gaps;
    vector<unsigned int> raw_data;

    trade_pair* getLowestTrade();
    trade_pair* getLowestGap();
    trade_pair* popLowestTrade();
    trade_pair* popLowestGap();
    void destroyPair(trade_pair* pair);

    trade_pair* createPair(unsigned int max, unsigned int min, trade_pair* previous, trade_pair* next, bool isTrade);




};



#endif //MUSICAL_BABOON_STRATEGYFINDER_H
