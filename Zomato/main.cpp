#include <iostream>

#include "headers/Application.h"
#include "services/LowestCostSelectionStrategy.h"
#include "services/Zomato.h"

std::vector<Item> items;
std::vector<Item> excludedItems;

int getRandNumber(int low, int high) {
    int x = rand() % (high-low);
    return x+low;
}

Menu generateRandomMenu() {
    std::vector<MenuSection> sections;
    sections.push_back(MenuSection{"Section 1"});
    sections.push_back(MenuSection{"Section 2"});
    for(const auto& item: items) {
        int included = getRandNumber(1,8);
        if(included) {
            bool whichSection = getRandNumber(0,2);
            const auto price = Amount(getRandNumber(10,100), getRandNumber(0, 50));
            sections[whichSection].addItem(item, price);
        }
    }
    // if(sections[0].getItems().empty()) {
    //     sections.erase(0);
    // }
    return Menu{sections};
}

Order generateRandomOrder() {
    std::unordered_map<Item, Quantity> orderItems;
    for(const auto& item: items) {
        int included = getRandNumber(0,2);
        if(included) {
            const auto price = getRandNumber(1, 10);
            orderItems[item] = price;
        }
    }
    return Order(orderItems);
}


int main() {
    std::cout << "Hello, Zomato!" << std::endl;

    SelectionStrategy* lowestCostStrategy = new LowestCostSelectionStrategy();
    Application* app = new Zomato(lowestCostStrategy);

    int totalItems = 10;
    for(int i=0;i<totalItems;i++) {
        auto price = Amount(getRandNumber(2, 100), getRandNumber(0, 80));
        Item item{"Item" + std::to_string(i)};
        items.push_back(item);
    }

    int excludedItemsCount = 5;
    for(int i=0;i<excludedItemsCount;i++) {
        auto price = Amount(getRandNumber(2, 100), getRandNumber(0, 80));
        Item item{"Excluded Item" + std::to_string(i)};
        excludedItems.push_back(item);
    }

    int totalRestraunts = 5;
    std::vector<Restraunt> restraunts;
    for(int i=0;i<totalRestraunts;i++) {
        auto name = "Restraunt" + std::to_string(i);
        auto restraunt = Restraunt{name, generateRandomMenu(), getRandNumber(2, 5), Rating(4)};
        restraunts.push_back(restraunt);
        restraunt.print();
        app->onboardRestraunt(restraunt);
    }

    int totalOrders = 10;
    std::vector<std::future<std::optional<Restraunt>>> orderFutures;
    for(int i=0;i<totalOrders;i++) {
        orderFutures.push_back(std::move( app->placeOrder(generateRandomOrder())));
    }

    std::vector<std::optional<Restraunt>> results;
    for(auto& fut: orderFutures) {
        fut.wait();
        results.push_back(fut.get());
    }

    const auto& orders = app->getAllOrders();
    for(int i=0;i<results.size();i++) {
        orders[i].print();
        const auto& result = results[i];
        if(!result.has_value()) std::cout<<"No restraunt assigned"<<std::endl;
        else {
            std::cout<<result->getName()<<std::endl;
        }
    }
    return 0;
}
