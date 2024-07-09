//
// Created by Anushi on 05/07/24.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include <vector>

#include "../services/Restraunt.h"
#include "SelectionStrategy.h"

class Application {
public:
    // Application() = delete;

    // explicit Application(SelectionStrategy* selection_strategy);

    // virtual ~Application() = 0;

    virtual void onboardRestraunt(Restraunt& newRestraunt) = 0;

    virtual std::vector<Restraunt> getAllRestraunts() = 0;

    virtual std::future<std::optional<Restraunt>> placeOrder(Order order) = 0;

    virtual std::vector<Order> getAllOrders() = 0;

    virtual void udpateSelectionStrategy(SelectionStrategy* selectionStrategy) = 0;
};

#endif //APPLICATION_H
