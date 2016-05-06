//
// Created by Jack on 04/29/2016.
//

#include <iostream>
#include <algorithm>
#include "StrategyFinder.h"
/**
 * O(n)= cycles through
 * Creates the object and finds the r=infinity solution(the globally optimal solution)
 */
StrategyFinder::StrategyFinder(vector<unsigned int> data) {
    raw_data = data;

    unsigned int min = 0;
    unsigned int max = 0;
    bool lookingForMin = true;
    trade_pair* previous = nullptr;

    for(unsigned int i = 0; i < data.size(); i++){
        if(i == 0 && data[1] > data[0]){ //check if 1st valueis a local min,look for a max
            min = 0;
            lookingForMin = false;
        }else if(i == 0 && data[1] <= data[0]){//check if 1st value is a local max,look for min
            max = 0;
            lookingForMin = true;
        }else if(i == data.size()-1 && data[i] > data[i-1]){//found a max, create a trade
            max = i;
            previous = createPair(min, max, previous, nullptr, true);
            lookingForMin = true; //min = -1;
        }else if(i == data.size()-1 && data[i] >= min){//dont create a gap on the trail end

        }else if(data[i + 1] > data[i] && data[i - 1] >= data[i] && lookingForMin){ //check for local min and create new trade
            min = i;
            if(max != 0) //makes sure 0 is not the start of a gap
                previous = createPair(max, min, previous,nullptr, false);
            lookingForMin = false; //max = -1;
        }else if(data[i + 1] <= data[i] && data[i - 1] < data[i] && !lookingForMin){ //check for local max, used for edge case on end
            max = i;
            previous = createPair(min, max, previous,nullptr, true);
            lookingForMin = true; //min = -1;
        }
    }
    r = trades.size();
}

/**
 * allocates trade_pair and puts it into the proper heap
 * O(C), C = constant
 */
trade_pair* StrategyFinder::createPair(unsigned int transaction1, unsigned int transaction2, trade_pair* previous, trade_pair* next, bool isTrade) {

    trade_pair* pair = new trade_pair;

    pair->isTrade = isTrade;
    pair->active = true;

    //fixes gap reversal, makes sure the 1st transaction is always before the second linearly
    if(transaction1 > transaction2){
        unsigned int temp = transaction1;
        transaction1 = transaction2;
        transaction2 = temp;
    }

    //assign proper edges and transactions
    pair->transaction1 = transaction1;
    pair->transaction2 = transaction2;

    if(transaction1 == 0){
        pair->before = nullptr;
    }

    pair->before = previous;
    if(previous != nullptr)
        previous->after = pair;

    pair->after = next;
    if(next != nullptr)
        next->before = pair;

    //either assign it into the trade heap or gap heap
    if(isTrade){
        pair->value = raw_data[transaction2] - raw_data[transaction1];
        trades.push_back(pair);
        push_heap(trades.begin(), trades.end(), trade_pair_compare());
    }else { // it is a gap
        pair->value = raw_data[transaction1] - raw_data[transaction2];
        gaps.push_back(pair);
        push_heap(gaps.begin(), gaps.end(), trade_pair_compare());
    }
    return pair;
}

/**
 * prints trades to stdout
 * O(n)
 */
 void StrategyFinder::printTrades(){
    cout << "buy\tsell\tvalue\tactive" << endl;
    for(unsigned int i = 0; i < trades.size(); i++){
        trade_pair* t = trades[i];
        cout << t->transaction1 << "\t" << t->transaction2 << "\t" << t->value << "\t" << t->active <<endl;
    }
}

/**
 * prints gaps to stdout
 * O(n)
 */
void StrategyFinder::printGaps(){
    cout << "Gaps" << endl;
    cout << "sell\tbuy\tvalue\tactive" << endl;
    for(unsigned int i = 0; i < gaps.size(); i++){
        trade_pair* g = gaps[i];
        cout << g->transaction1 << "\t" << g->transaction2 << "\t" << g->value << "\t" << g->active << endl;
    }
}

/*
 * decrements the number of trades so a new solution is found for r-1, remove top of heap
 * O(n)
 */
void StrategyFinder::decrementNumberOfTrades() {
    //O(n)
    //remove inactive nodes
    while(gaps.size() != 0 && !getLowestGap()->active){
        popLowestGap();
    }
    while(trades.size() != 0 && !getLowestTrade()->active){
        popLowestTrade();
    }

    if(trades.size() == 0){
        return;
    }

//O(1) removes the lowest gap or trade, whichever is lower to maximize revenue
    if(getLowestGap()->value <= getLowestTrade()->value){
        destroyPair(popLowestGap());
        r--;
    }else if(r != 0) {
        destroyPair(popLowestTrade());
        r--;
    }
//O(n)
    //remove inactive tags
    while(gaps.size() != 0 && !getLowestGap()->active){
        popLowestGap();
    }
    while(trades.size() != 0 && !getLowestTrade()->active){
        popLowestTrade();
    }
}

/**
 * returns the lowest gap
 *
 * O(C)
 */
trade_pair* StrategyFinder::getLowestGap() {
    if(gaps.size() != 0)
        return gaps[0];
    else
        return nullptr;
}

/**
 * returns the lowest gap
 *
 * O(C)
 */
trade_pair* StrategyFinder::getLowestTrade() {
    if(trades.size() != 0)
        return trades[0];
    else
        return nullptr;
}
/**
 * pops and returns the lowest gap
 *
 * O(logn)
 */
trade_pair *StrategyFinder::popLowestGap() {
    trade_pair* gap = getLowestGap();
    if(gap != nullptr){
        pop_heap(gaps.begin(), gaps.end(), trade_pair_compare());
        gaps.pop_back();
        return gap;
    }
    return nullptr;
}
/**
 * pops and returns the lowest trade
 *
 * O(logn)
 */
trade_pair *StrategyFinder::popLowestTrade() {
    trade_pair* trade = getLowestTrade();
    if(trade != nullptr){
        //pop_heap?
        pop_heap(trades.begin(), trades.end(), trade_pair_compare());
        trades.pop_back();
        return trade;
    }
    return nullptr;
}

/**
 * destroys a trade_pair and merges the pair on either side of it
 * O(C)
*/
void StrategyFinder::destroyPair(trade_pair *pair) {
    bool left_exists = (pair->before != nullptr);
    bool right_exists = (pair->after != nullptr);


    if(left_exists || right_exists){//trade isnt the only option left
        if(!left_exists){//first trade in sequence, remove the trade and gap,update 2nd trades pointer accordingly
            pair->after->before = nullptr;
            pair->active = false;
            pair->after->active = false;
            pair->after->after->before = nullptr;
        }else if(!right_exists){//last trade in sequence, remove trade and gap, update 2nd to last trades pointer
            pair->before->after = nullptr;
            pair->active = false;
            pair->before->before->after = nullptr;
            pair->before->active = false;
        }else{//in middle of trades, remove the trade merge the 2 on both sides into a new trade and reconnect the pointers to the new trade
            unsigned int left_extrema = pair->before->transaction1;
            unsigned int right_extrema = pair->after->transaction2;

            if(!pair->isTrade){//flip extrema for the gaps
                unsigned int temp = left_extrema;
                left_extrema = right_extrema;
                right_extrema = temp;
            }

            trade_pair* before = pair->before->before;
            trade_pair* after = pair->after->after;

            trade_pair* new_pair = createPair(right_extrema, left_extrema,before,after,!pair->isTrade);

            if(before != nullptr)
                before->after = new_pair;
            if(after != nullptr)
                after->before = new_pair;

            pair->active = false;
            pair->before->active = false;
            pair->after->active = false;

        }

    }
}

//O(C)
unsigned int StrategyFinder::getNumberOfTrades() {
    return r;
}

//O(size)
void StrategyFinder::printFinalTrades() {
    sort(trades.begin(), trades.end(),trade_pair_compare_for_print());
    for(unsigned int i = 0; i < trades.size(); i++){
        if(trades[i]->active){
            cout << trades[i]->transaction1+1 << endl << trades[i]->transaction2+1 << endl;
        }
    }
}

StrategyFinder::~StrategyFinder() {
    for(int i = 0; i < trades.size(); i++){
        delete trades[i];
    }
    for(int i = 0; i < gaps.size(); i++){
        delete gaps[i];
    }
}
