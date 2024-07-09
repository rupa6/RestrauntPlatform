//
// Created by Anushi on 06/07/24.
//

#ifndef ZOMATO_H
#define ZOMATO_H
#include "../headers/Application.h"

class Zomato final : public Application {
public:
    Zomato() = delete;

    explicit Zomato(SelectionStrategy* selection_strategy);

    ~Zomato() = default;

    void onboardRestraunt(Restraunt& newRestraunt) override;

    std::vector<Restraunt> getAllRestraunts() override;

    std::future<std::optional<Restraunt>> placeOrder(Order order) override;

    std::vector<Order> getAllOrders() override {
        return orders;
    }

    void udpateSelectionStrategy(SelectionStrategy* selectionStrategy) override;

private:
    std::vector<Restraunt> restraunts{};
    std::vector<Order> orders{};
    SelectionStrategy* currentSelectionStrategy{};
    std::mutex orderQueueMutex;
};

#endif //ZOMATO_H
