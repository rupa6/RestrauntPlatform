#ifndef RESTRAUNT_H
#define RESTRAUNT_H
#include <cassert>
#include <future>
#include <set>
#include <unordered_set>

#include "../headers/Menu.h"
#include "../headers/Order.h"

class Rating {
    int value;

public:
    explicit Rating(unsigned short value)
        : value(value) {
        assert(value < 6);
    }
};

class Restraunt {
public:
     ~Restraunt() = default;

     Restraunt(std::string name, Menu menu, int capacity, Rating current_rating);

     Restraunt(const Restraunt& restraunt);

     std::string getName() const {
        return name;
     }

     const Menu getMenu() const;

     const int getOrderProcessingCapacity() const;

     std::future<void> processOrder(Order order);

     const std::vector<Order> getAllProcessedOrders() const;

     const std::unordered_set<Order> getAllProcessingOrders() const;

     [[nodiscard]] const Rating getRating() const;

    void print() const {
        std::cout<<"============="<<name<<"============"<<std::endl;
        menu.print();
        std::cout<<"Capacity: "<<capacity<<std::endl;
    }

    std::string name;
    Menu menu;
    int capacity;
    Rating currentRating;
    std::unordered_set<Order> processingOrders;
    std::vector<Order> processedOrders;
    std::mutex orderProcessing;
};

#endif // RESTRAUNT_H
