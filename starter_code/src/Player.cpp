#include "Player.h"
#include <iostream>
#include <algorithm>

// TODO: Implement Player constructor
// HINTS:
// - MUST call Character base constructor. 
//
Player::Player(const std::string& name)
    : Character(name, 100, 10, 5),
      level(1), experience(0), gold(0),
      equipped_weapon(NULL), equipped_armor(NULL) {
}


// TODO: Implement Player destructor
// HINTS:
// - CRITICAL: Must delete all items in inventory to prevent memory leaks!
// - DON'T delete equipped_weapon or equipped_armor - they point to items
//   already in the inventory, so they're already deleted!
//
Player::~Player() {
    // TODO: Delete all inventory items
    for (Item* item : inventory){
        delete item;
    }
}


// TODO: Override displayStats
// HINTS:
// - Show player-specific information
// - Include: level, HP, attack (with weapon bonus), defense (with armor bonus), gold, experience
// - Show equipped weapon and armor names if any
// - Use decorative formatting (borders, headers)
// - Use getters to access inherited Character data
//
void Player::displayStats() const {
    // TODO: Display comprehensive player stats
    std::cout << "============================\n";
    std::cout << "     PLAYER STATS\n";
    std::cout << "============================\n";
    std::cout << "Name: " << getName() << "\n";
    std::cout << "Level: " << level << "\n";
    std::cout << "HP: " << getCurrentHP() << "/" << getMaxHP() << "\n";

    int attack = getAttack();
    int defense = getDefense();

    if(equipped_weapon){
        attack += equipped_weapon->getDamageBonus();
    }
    if(equipped_armor){
        defense += equipped_armor->getDefenseBonus();
    }

    std::cout << "Attack: " << attack;\

    if (equipped_weapon) std::cout << " (+" << equipped_weapon->getDamageBonus() << " from " << equipped_weapon->getName() << ")";
    std::cout << "\n";

    std::cout << "Defense: " << defense;
    if (equipped_armor) std::cout << " (+" << equipped_armor->getDefenseBonus() << " from " << equipped_armor->getName() << ")";
    std::cout << "\n";

    std::cout << "Gold: " << gold << "\n";
    std::cout << "EXP: " << experience << "\n";
    std::cout << "============================\n";
}


// TODO: Override calculateDamage to include weapon bonus
// HINTS:
// - If weapon is equipped, add weapon's damage bonus
// - Return total damage
//
int Player::calculateDamage() const {
    // TODO: Calculate damage with weapon bonus
    int base = getAttack();
    if(equipped_weapon){
        base += equipped_weapon->getDamageBonus();
        return base;
    }
}


// TODO: Implement addItem
// HINTS:
// - Add item to inventory vector using push_back()
// - Print pickup message with item name
//
void Player::addItem(Item* item) {
    // TODO: Add item to inventory
    inventory.push_back(item);
    std::cout <<"Picked up: " << item->getName << "\n";

}


// TODO: Implement removeItem
// HINTS:
// - Search inventory for item by name (case-insensitive comparison)
// - If found: delete the item, then erase from vector
// - If not found: print error message
// - Remember: inventory.erase(inventory.begin() + i) to remove at index i
//
void Player::removeItem(const std::string& item_name) {
    // TODO: Find and remove item from inventory
    std::string target = toLower(item_name);
    for(int i=0; i<inventory.size(); i++){
        if(toLower(inventory[i]->getName())==target){
            if (inventory[i] == equipped_weapon) equipped_weapon = NULL;
            if (inventory[i] == equipped_armor) equipped_armor = NULL;

            delete inventory[i];
            inventory.erase(inventory.begin() +i);
            std::cout << "Removed item: " << item_name << "\n";
            return
        }
    }
    std::cout << "Error: Item '" << item_name << "' not found.\n";
}


// TODO: Implement displayInventory
// HINTS:
// - Print header: "----- Inventory -----"
// - If inventory is empty, print "Empty"
// - Otherwise, loop through and print each item's name and type
// - Format: "- ItemName (ItemType)"
// - Print footer: "--------------------"
//
void Player::displayInventory() const {
    // TODO: Display all items in inventory
    std::cout << "----- Inventory -----\n";

    if(inventory.empy()){
        std::cout << "Empty\n";
    }
    else{
        for(Item* item : inventory){
            std::cout << "- " << item->getName() << " (" << item->getType() << ")\n";
        }
    }
    std::cout << "--------------------\n";
}


// TODO: Implement hasItem
// HINTS:
// - Search inventory for item by name (case-insensitive)
// - Return true if found, false otherwise
// - Use same case-insensitive comparison as removeItem
//
bool Player::hasItem(const std::string& item_name) const {
    // TODO: Check if item exists in inventory
    return false;  // REPLACE THIS
}


// TODO: Implement getItem
// HINTS:
// - Search inventory for item by name (case-insensitive)
// - Return pointer to item if found
// - Return NULL if not found
//
Item* Player::getItem(const std::string& item_name) {
    // TODO: Find and return item pointer
    return NULL;  // REPLACE THIS
}


// TODO: Implement equipWeapon
// HINTS:
// - Get item from inventory using getItem()
// - Check if item exists (not NULL)
// - Check if item type is "Weapon"
// - If current weapon equipped, print unequip message
// - Set equipped_weapon pointer to this item
// - Print equip message
//
void Player::equipWeapon(const std::string& weapon_name) {
    // TODO: Equip weapon from inventory
}


// TODO: Implement equipArmor
// HINTS:
// - Similar to equipWeapon but for armor
// - Check if item type is "Armor"
// - Set equipped_armor pointer
//
void Player::equipArmor(const std::string& armor_name) {
    // TODO: Equip armor from inventory
}


// TODO: Implement unequipWeapon
// HINTS:
// - Check if weapon is currently equipped
// - If so, print message and set equipped_weapon to NULL
// - If not, print error message
//
void Player::unequipWeapon() {
    // TODO: Unequip current weapon
}


// TODO: Implement unequipArmor
// HINTS:
// - Similar to unequipWeapon
// - Set equipped_armor to NULL
//
void Player::unequipArmor() {
    // TODO: Unequip current armor
}


// TODO: Implement useItem
// HINTS:
// - Get item from inventory using getItem()
// - Check if item exists (not NULL)
// - Check if item type is "Consumable"
// - Cast to Consumable*: Consumable* consumable = static_cast<Consumable*>(item)
// - Check if already used: consumable->isUsed()
// - Get healing amount: consumable->getHealingAmount()
// - Call heal() with that amount
// - Call consumable->use() to mark as used
// - Remove item from inventory (it's been consumed!)
//
void Player::useItem(const std::string& item_name) {
    // TODO: Use consumable item
}


// TODO: Implement gainExperience
// HINTS:
// - Add experience points
// - Print message showing exp gained
// - Check if enough exp to level up: if (experience >= level * 100)
// - If so, call levelUp()
//
void Player::gainExperience(int exp) {
    // TODO: Add experience and check for level up
}


// TODO: Implement levelUp
// HINTS:
// - Increment level
// - Reset experience to 0
// - Increase stats:
//   * Increase max_hp by 10 (use setMaxHP())
//   * Set current_hp to max (full heal on level up)
//   * Increase attack by 2
//   * Increase defense by 1
// - Print celebratory level up message
// - Display new stats
//
void Player::levelUp() {
    // TODO: Level up the player
}
