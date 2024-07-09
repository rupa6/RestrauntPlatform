//
// Created by Anushi on 06/07/24.
//

#include "../headers/SelectionStrategy.h"
#include "LowestCostSelectionStrategy.h"
#include <unordered_set>

const Amount* _canProcessOrder(const Restraunt& restraunt, const Order& order) {
    if(restraunt.getOrderProcessingCapacity() <= restraunt.getAllProcessingOrders().size()) {
        return nullptr;
    }

    const auto menu = restraunt.getMenu();

    std::unordered_map<Item, Amount> allMenuItems;
    for(const auto& section: menu.getSections()) {
        for(const auto& [item, price]: section.getItems()) {
            allMenuItems.insert({item, price});
        }
    }

    auto* totalAmount = new Amount(0,0);
    for(const auto& [item, quantity]: order.getOrderedItems()) {
        if(!allMenuItems.contains(item)) return nullptr;
        totalAmount->operator+=(allMenuItems[item] * quantity);
    }

    return totalAmount;
}

std::optional<Restraunt*> LowestCostSelectionStrategy::selectRestraunt(std::vector<Restraunt>& restraunts, const Order& order) {
    std::vector<Restraunt>::iterator restrauntIt = std::min_element(
        restraunts.begin(),
        restraunts.end(),
        [&](const Restraunt& r1, const Restraunt& r2) {
            const auto amount1 = _canProcessOrder(r1, order);
            const auto amount2 = _canProcessOrder(r2, order);
            if(amount2 == nullptr) return true;
            if(amount1 == nullptr) return false;
            return (*amount1) < (*amount2);
        });

    if(restrauntIt == restraunts.end()) return std::optional<Restraunt*>();
    const auto bestAmount = _canProcessOrder(*restrauntIt, order);
    if(bestAmount == nullptr) return std::optional<Restraunt*>();
    return std::optional<Restraunt*>(restrauntIt.base());
}

