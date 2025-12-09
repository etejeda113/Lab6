#include "Shop.h"
#include <iostream>
#include <algorithm>

Shop::Shop() {}

Shop::~Shop() {
    for(size_t i = 0; i < stock.size(); i++) {
        delete stock[i].item; 
    }
    stock.clear();
}

void Shop::addToStock(Item* item, int price) {
    stock.push_back(ShopEntry(item, price)); 
}

std::string Shop::toLower(const std::string& name) {
    std::string out = name;
    std::transform(out.begin(), out.end(), out.begin(), ::tolower);
    return out; 
}

void Shop::shop_display(Player* player) const {
    std::cout << "\n------------------ Charlie's Shop --------------\n";
    std::cout << "Options:\n";
    std::cout << "  buy <item>  - Purchase an item\n";
    std::cout << "  sell <item> - Sell an item from your inventory\n";
    std::cout << "  leave       - Exit the shop\n\n";
    std::cout << "------------ Items for Sale -----------\n"; 
    for(size_t i = 0; i < stock.size(); i++) {
        std::cout << "  " << stock[i].item->getName() 
                  << " - " << stock[i].price << " gold\n"; 
    }
    std::cout << "--------------------------------------\n"; 
    std::cout << "You have: " << player->getGold() << " gold.\n"; 
}

void Shop::buyItem(Player* player, const std::string& name) {
    std::string item_name = toLower(name);
    for(size_t i = 0; i < stock.size(); i++) {
        if(toLower(stock[i].item->getName()) == item_name) {
            if(player->getGold() < stock[i].price) {
                std::cout << "You don't have enough gold.\n"; 
                return; 
            }
            player->spendGold(stock[i].price);
            std::cout << "You bought " << stock[i].item->getName() << "!\n";
            player->addItem(stock[i].item);
            stock.erase(stock.begin() + i);
            return;
        }
    }
    std::cout << "Item '" << name << "' is not sold here.\n";
}

void Shop::sellItem(Player* player, const std::string& name) {
    Item* item = player->getItem(name);
    if(!item) {
        std::cout << "You do not have '" << name << "' in your inventory.\n";
        return; 
    }
    if(item->getType() == "Key") {
        std::cout << "You cannot sell a Key.\n";
        return; 
    }
    int sell_price = item->getGoldPrice();
    std::cout << "Sold " << name << " for " << sell_price << " gold.\n"; 
    player->addGold(sell_price);
    player->removeItemShop(name);
    int shop_price = sell_price * 2;
    addToStock(item, shop_price);
}