//
// Created by Anushi on 07/07/24.
//

#ifndef LOWESTCOSTSELECTIONSTRATEGY_H
#define LOWESTCOSTSELECTIONSTRATEGY_H

class LowestCostSelectionStrategy final : public SelectionStrategy {
public:
    ~LowestCostSelectionStrategy() = default;

    std::optional<Restraunt*> selectRestraunt(std::vector<Restraunt>& restraunts, const Order& order) override;
};

#endif //LOWESTCOSTSELECTIONSTRATEGY_H
