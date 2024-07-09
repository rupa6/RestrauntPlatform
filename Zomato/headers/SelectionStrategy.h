//
// Created by Anushi on 05/07/24.
//

#ifndef SELECTIONSTRATEGY_H
#define SELECTIONSTRATEGY_H
#include "../services/Restraunt.h"

class SelectionStrategy {
public:
    // virtual ~SelectionStrategy() = 0;
    virtual std::optional<Restraunt*> selectRestraunt(std::vector<Restraunt>& restraunts, const Order& order) = 0;
};

#endif //SELECTIONSTRATEGY_H
