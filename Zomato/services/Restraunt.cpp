//
// Created by Anushi on 06/07/24.
//

#include <future>
#include <set>
#include <thread>

#include "Restraunt.h"

Restraunt::Restraunt(std::string name, Menu menu, int capacity, Rating current_rating)
    : name(name),
      menu(menu),
      capacity(capacity),
      currentRating(current_rating) {
}

Restraunt::Restraunt(const Restraunt &restraunt)
    : name(restraunt.name), menu(restraunt.menu), capacity(restraunt.capacity), currentRating(restraunt.currentRating) {
}

const Menu Restraunt::getMenu() const {
    return menu;
}

const int Restraunt::getOrderProcessingCapacity() const {
    return capacity;
}

std::future<void> Restraunt::processOrder(const Order order) {
    return std::async(std::launch::async, [&]() {
        {
            orderProcessing.lock();
            processingOrders.insert(order);
            orderProcessing.unlock();
        }
        int preparationTime = (rand() % 1000) + 10;
        std::this_thread::sleep_for(std::chrono::milliseconds(preparationTime));
        {
            std::lock_guard<std::mutex> guard(orderProcessing);
            processingOrders.erase(order);
            processedOrders.push_back(order);
        }
    });
}

const std::vector<Order> Restraunt::getAllProcessedOrders() const {
    return processedOrders;
}

const std::unordered_set<Order> Restraunt::getAllProcessingOrders() const {
    return processingOrders;
}

const Rating Restraunt::getRating() const {
    return currentRating;
}
