//
// Created by Anushi on 04/07/24.
//

#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "Amount.h"

class Item {
public:
    Item(std::string name2)
        : name(name2) {
        id = std::to_string(rand() % 10000000);
        // std::cout<<"Item create "<<id<<std::endl;
    }

    Item(const Item& other) : name(other.name), id(other.id) {
        // std::cout<<"Item copy "<<id<<std::endl;
    }

    ~Item() {
        // std::cout<<"Item destruct "<<id<<std::endl;
    }

    [[nodiscard]] std::string getId() const {
        return id;
    }

    [[nodiscard]] std::string getName() const {
        return name;
    }

    bool operator==(const Item &other) const {
        return id == other.id;
    }

    void print() const {
        std::cout<<id<<"::"<<name;
    }

private:
    std::string id;
    std::string name;
};

template <>
struct std::hash<Item>
{
    std::size_t operator()(const Item& item) const {
      return hash<std::string>()(item.getId());
    }
};


class MenuSection {
public:
    MenuSection(std::string section_name) : sectionName(std::move(section_name)) {
    }

    [[nodiscard]] std::unordered_map<Item, Amount> getItems() const {
        return items;
    }

    [[nodiscard]] std::string getName() const {
        return sectionName;
    }

    void addItem(Item item, Amount price) {
        items.insert({item, price});
    }

    void print() const {
        for(const auto& [item, price]: items) {
            item.print();
            std::cout<<" Amount:";
            price.print();
            std::cout<<std::endl;
        }
    }

private:
    std::unordered_map<Item, Amount> items;
    std::string sectionName;
};

class Menu {
public:
    [[nodiscard]] std::vector<MenuSection> getSections() const {
        return sections;
    }

    explicit Menu(const std::vector<MenuSection> &sections)
        : sections(sections) {
    }

    void print() const {
        for(const auto& section: sections) {
            std::cout<<"-----------------"<<section.getName()<<"------------"<<std::endl;
            section.print();
            std::cout<<std::endl;
        }
    }

private:
    std::vector<MenuSection> sections;
};

#endif //MENU_H
