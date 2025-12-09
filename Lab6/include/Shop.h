#ifndef SHOP_H
#define SHOP_H

#include <string>
#include <vector>
#include "Item.h"
#include "Player.h"

struct ShopEntry {
    Item* item;
    int price;
    ShopEntry(Item* i, int p) : item(i), price(p) {}
};

class Shop {
private: 
    std::vector<ShopEntry> stock;
    std::string toLower(const std::string& name);
    
public: 
    Shop();
    ~Shop();
    void shop_display(Player* player) const;
    void addToStock(Item* item, int price);
    void buyItem(Player* player, const std::string& name);
    void sellItem(Player* player, const std::string& name);
};

#endif
