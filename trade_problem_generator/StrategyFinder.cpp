//
// Created by Jack on 04/29/2016.
//

#include <iostream>
#include <algorithm>
#include "StrategyFinder.h"

StrategyFinder::StrategyFinder(vector<int> data) {
    raw_data = data;

    int min = -1;
    int max = -1;
    trade_pair* previous = nullptr;

    for(int i = 0; i < data.size(); i++){
        if(i == 0 && data[1] > data[0]){ //check if 0 is a local min
            min = 0;
        }else if(i == 0 && data[1] <= data[0]){
            max = 0;
        }else if(i == data.size()-1 && data[i] > data[i-1]){
            max = i;
            previous = createPair(min, max, previous, nullptr, true);
            min = -1;
        }else if(i == data.size()-1 && data[i] >= min){

        }else if(data[i + 1] > data[i] && data[i - 1] >= data[i] && min == -1){ //check for local min
            min = i;
            if(max != 0) //makes sure 0 is not the start of a gap
                previous = createPair(max, min, previous,nullptr, false);
            max = -1;
        }else if(data[i + 1] <= data[i] && data[i - 1] < data[i] && max == -1){ //check for local max
            max = i;
            previous = createPair(min, max, previous,nullptr, true);
            min = -1;
        }
    }
    r = trades.size();
}

/**
 * allocates trade_pair
 */
trade_pair* StrategyFinder::createPair(int transaction1, int transaction2, trade_pair* previous, trade_pair* next, bool isTrade) {

    trade_pair* pair = new trade_pair;

    pair->isTrade = isTrade;
    pair->active = true;
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

    if(isTrade){
        pair->value = raw_data[transaction2] - raw_data[transaction1];
        trades.push_back(pair);
        push_heap(trades.begin(), trades.end(), trade_pair_compare());
    }else {
        pair->value = raw_data[transaction1] - raw_data[transaction2];
        gaps.push_back(pair);
        push_heap(gaps.begin(), gaps.end(), trade_pair_compare());
    }
    return pair;
}


void StrategyFinder::printTrades(){
    cout << "buy\tsell\tvalue\tactive" << endl;
    for(int i = 0; i < trades.size(); i++){
        trade_pair* t = trades[i];
        cout << t->transaction1 << "\t" << t->transaction2 << "\t" << t->value << "\t" << t->active <<endl;
    }
}

void StrategyFinder::printGaps(){
    cout << "Gaps" << endl;
    cout << "sell\tbuy\tvalue\tactive" << endl;
    for(int i = 0; i < gaps.size(); i++){
        trade_pair* g = gaps[i];
        cout << g->transaction1 << "\t" << g->transaction2 << "\t" << g->value << "\t" << g->active << endl;
    }
}

void StrategyFinder::decrementNumberOfTrades() {
    while(gaps.size() != 0 && !getLowestGap()->active){
        popLowestGap();
    }
    while(trades.size() != 0 && !getLowestTrade()->active){
        popLowestTrade();
    }

    if(trades.size() == 0){
        return;
    }

    if(getLowestGap()->value <= getLowestTrade()->value){
        trade_pair* lowest_gap = popLowestGap();
        mergeTrades(lowest_gap);
        r--;
    }else if(r != 0) {
        destroyTrade(popLowestTrade());
        r--;
    }

    while(gaps.size() != 0 && !getLowestGap()->active){
        popLowestGap();
    }
    while(trades.size() != 0 && !getLowestTrade()->active){
        popLowestTrade();
    }
}

trade_pair* StrategyFinder::getLowestGap() {
    if(gaps.size() != 0)
        return gaps[0];
    else
        return nullptr;
}

trade_pair* StrategyFinder::getLowestTrade() {
    if(trades.size() != 0)
        return trades[0];
    else
        return nullptr;
}

trade_pair *StrategyFinder::popLowestGap() {
    trade_pair* gap = getLowestGap();
    if(gap != nullptr){
        pop_heap(gaps.begin(), gaps.end());
        gaps.pop_back();
        return gap;
    }
    return nullptr;
}

trade_pair *StrategyFinder::popLowestTrade() {
    trade_pair* trade = getLowestGap();
    if(trade != nullptr){
        pop_heap(trades.begin(), trades.end());
        trades.pop_back();
        return trade;
    }
    return nullptr;
}

void StrategyFinder::mergeTrades(trade_pair *gap) {
    trade_pair* trade1 = gap->before;
    trade_pair* trade2 = gap->after;

    createPair(trade1->transaction1,trade2->transaction2,trade1->before,trade2->after,true);
    trade1->active = false;
    trade2->active = false;

}

void StrategyFinder::destroyTrade(trade_pair *trade) {
    trade_pair* gap1 = trade->before;
    trade_pair* gap2 = trade->after;


    if(gap1 != nullptr && gap2 != nullptr){
        if(gap1->before != nullptr && gap2->after != nullptr)
            createPair(gap1->transaction1, gap2->transaction2, gap1->before, gap2->after, false);
    }


    gap2->active = false;
    gap1->active = false;


}
