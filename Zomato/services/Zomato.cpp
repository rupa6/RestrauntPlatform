//
// Created by Anushi on 06/07/24.
//

#include "Zomato.h"

#include <future>

Zomato::Zomato(SelectionStrategy* current_selection_strategy)
        : currentSelectionStrategy(current_selection_strategy) {
    }

void Zomato::onboardRestraunt(Restraunt& newRestraunt) {
    restraunts.push_back(newRestraunt);
}

std::vector<Restraunt> Zomato::getAllRestraunts() {
    return restraunts;
}

std::future<std::optional<Restraunt>> Zomato::placeOrder(Order order) {
    orderQueueMutex.lock();
    orders.push_back(order);
    orderQueueMutex.unlock();
    auto whichRestrauntOptional = currentSelectionStrategy->selectRestraunt(restraunts, order);
    if (!whichRestrauntOptional.has_value()) {
        std::promise<std::optional<Restraunt>> result;
        order.updateOrderStatus(OrderStatus::CANCELED);
        result.set_value(std::optional<Restraunt>());
        return result.get_future();
    }
    Restraunt* whichRestraunt = whichRestrauntOptional.value();
    return std::async(std::launch::async, [](Restraunt* whichRestraunt, Order order) {
        whichRestraunt->processOrder(order).get();
        order.updateOrderStatus(OrderStatus::COMPLETED);
        return std::optional<Restraunt>(*whichRestraunt);
    }, whichRestraunt, order);
}

void Zomato::udpateSelectionStrategy(SelectionStrategy* selectionStrategy) {
    currentSelectionStrategy = selectionStrategy;
}

