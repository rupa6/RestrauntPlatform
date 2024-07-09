//
// Created by Anushi on 04/07/24.
//

#ifndef ORDER_H
#define ORDER_H
#include <string>
#include <unordered_map>

#include "Amount.h"

class Item;
typedef int Quantity;

enum OrderStatus {
    UNASSIGNED,
    ACCEPETED,
    CANCELED,
    COMPLETED
};

class Order {
public:
    Order(const std::unordered_map<Item, Quantity>& ordered_items)
        : orderId(rand() % 100000),
          orderedItems(ordered_items), orderStatus(UNASSIGNED) {
        // std::cout<<"Order create "<<orderId<<std::endl;
    }

    Order(const Order& other): orderId(other.orderId), orderedItems(other.orderedItems), orderStatus(other.orderStatus) {
        // std::cout<<"Order copy "<<orderId<<std::endl;
    }

    ~Order() {
        // std::cout<<"Order destruct "<<orderId<<std::endl;
    }

    [[nodiscard]] int getOrderId() const {
        return orderId;
    }

    // [[nodiscard]] Amount getTotalAmount() const {
    //     return totalAmount;
    // }

    [[nodiscard]] std::unordered_map<Item, Quantity> getOrderedItems() const {
        return orderedItems;
    }

    void updateOrderStatus(const OrderStatus order_status) {
        orderStatus = order_status;
    }

    bool operator==(const Order &other) const {
        return  orderId == other.orderId;
    }

    void print() const {
        std::cout << "============== Order#"<<orderId<<"=============="<<std::endl;
        for(const auto [item, quanity]: orderedItems) {
            item.print();
            std::cout<<" Quantity = "<<quanity<<std::endl;
        }
        std::cout<<"OrderStatus: "<<orderStatus<<std::endl;
    }


private:
    int orderId;
    std::unordered_map<Item, Quantity> orderedItems;
    OrderStatus orderStatus;
};

template <>
struct std::hash<Order>
{
    std::size_t operator()(const Order& order) const {
        return hash<int>()(order.getOrderId());
    }
};


#endif //ORDER_H
