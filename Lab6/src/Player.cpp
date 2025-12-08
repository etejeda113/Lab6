#include "Player.h"
#include <iostream>
#include <algorithm>

// TODO: Implement Player constructor
// HINTS:
// - MUST call Character base constructor. 
//

static std::string toLower(const std::string& s) {
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(), ::tolower);
    return out;
}


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
    for(size_t i = 0; i < inventory.size(); i++){
        delete inventory[i];
    }
    inventory.clear();
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

    if(equipped_weapon != NULL){
        Weapon* w = dynamic_cast<Weapon*>(equipped_weapon);
        if(w){ 
            attack += w->getDamageBonus();
            std::cout << "Attack: " << attack << " (+" << w->getDamageBonus()
                    << " from " << w->getName() << ")\n";
        } else {
        std::cout << "Attack: " << attack << "\n";
    }
    }

    else {
        std::cout << "Attack: " << attack << "\n";
    }

    if(equipped_armor!=NULL){
        Armor* a = dynamic_cast<Armor*>(equipped_armor);
        if(a){
        defense += a->getDefenseBonus();
        std::cout << "Defense: " << defense << " (+" << a->getDefenseBonus()<< " from " << a->getName() << ")\n";
    } else {
        std::cout << "Defense: " << defense << "\n";}
    }
    else {
        std::cout << "Defense: " << defense << "\n";
    }

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
    int base = Character::calculateDamage();
    Weapon* w = dynamic_cast<Weapon*>(equipped_weapon);
    if(w){
        base+= w->getDamageBonus();
    }

    // Add randomness: +/- 2 damage
    int variation = rand() % 5 - 2; // random number between -2 and +2
    return std::max(1, base + variation); // ensure at least 1 damage
}


// TODO: Implement addItem
// HINTS:
// - Add item to inventory vector using push_back()
// - Print pickup message with item name
//
void Player::addItem(Item* item) {
    // TODO: Add item to inventory
    inventory.push_back(item);
    std::cout <<"Picked up: " << item->getName() << " - " << item->getDescription() << "\n";

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
    for(size_t i=0; i<inventory.size(); i++){
        if(toLower(inventory[i]->getName())==target){
            if (inventory[i] == equipped_weapon) equipped_weapon = NULL;
            if (inventory[i] == equipped_armor) equipped_armor = NULL;

            delete inventory[i];
            inventory.erase(inventory.begin() +i);
            std::cout << "Removed item: " << item_name << "\n";
            return;
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

    if(inventory.empty()){
        std::cout << "Empty\n";
    }
    else{
        for(size_t i = 0; i < inventory.size(); i++){
            Item* item = inventory[i];
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
    std::string target = toLower(item_name);
    for(size_t i = 0; i < inventory.size(); i++){
        Item* item = inventory[i];
        if(toLower(item->getName()) == target){
            return true;
        }
    }
    return false;
}


// TODO: Implement getItem
// HINTS:
// - Search inventory for item by name (case-insensitive)
// - Return pointer to item if found
// - Return NULL if not found
//
Item* Player::getItem(const std::string& item_name) {
    // TODO: Find and return item pointer
   std::string target = toLower(item_name);
    for(size_t i = 0; i < inventory.size(); i++){
        Item* item = inventory[i];
        if(toLower(item->getName()) == target){
            return item;
        }
    }
    return NULL;
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
    Item* item = getItem(weapon_name);

    if(item==NULL){
        std::cout << "Error: Weapon not found.\n";
        return;
    }
    if(item->getType() != "Weapon"){
        std::cout << "Error: " << item->getName() << " is not a weapon.\n";
        return;
    }


    if(equipped_weapon){
        std::cout << "Unequipped: " << equipped_weapon->getName() << "\n";
    }
    
    equipped_weapon = static_cast<Weapon*>(item);
    std::cout << "Equipped Weapon: " << equipped_weapon->getName() << "\n";  

}


// TODO: Implement equipArmor
// HINTS:
// - Similar to equipWeapon but for armor
// - Check if item type is "Armor"
// - Set equipped_armor pointer
//
void Player::equipArmor(const std::string& armor_name) {
    // TODO: Equip armor from inventory
    Item* item = getItem(armor_name);

    if(item==NULL){
        std::cout << "Error: Armor not found.\n";
        return;
    }
    if(item->getType() != "Armor"){
        std::cout << "Error: " << item->getName() << " is not armor.\n";
        return;
    }


    if(equipped_armor){
        std::cout << "Unequipped: " << equipped_armor->getName() << "\n";
    }
    
    equipped_armor = static_cast<Armor*>(item);
    std::cout << "Equipped Armor: " << equipped_armor->getName() << "\n";  

}


// TODO: Implement unequipWeapon
// HINTS:
// - Check if weapon is currently equipped
// - If so, print message and set equipped_weapon to NULL
// - If not, print error message
//
void Player::unequipWeapon() {
    // TODO: Unequip current weapon
    if(equipped_weapon==NULL){
        std::cout << "No weapon is equipped.\n";
        return;
    }
    std::cout << "Unequipped weapon: " << equipped_weapon->getName() << "\n";
    equipped_weapon = NULL;    
}


// TODO: Implement unequipArmor
// HINTS:
// - Similar to unequipWeapon
// - Set equipped_armor to NULL
//
void Player::unequipArmor() {
    // TODO: Unequip current armor
    if(equipped_armor==NULL){
        std::cout << "No armor is equipped.\n";
        return;
    }
    std::cout << "Unequipped armor: " << equipped_armor->getName() << "\n";
    equipped_armor = NULL;   
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
    Item* item = getItem(item_name);

    if(item == NULL){
    std::cout << "Error: Item could not be found.\n";
    return;
    }

    if(item->getType() != "Consumable"){
        std::cout << "Error: " << item->getName() << " is not a consumable.\n";
        return;
    }

    Consumable* c = static_cast< Consumable*>(item);

    if(c->isUsed()){
        std::cout << "Error: " << c->getName() << " has already been used.\n";
        return;
    }

    heal(c->getHealingAmount());
    c->use();

    removeItem(c-> getName());
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
    experience += exp;
    std::cout << "Gained " << exp << " EXP!\n";

    if(experience >= level *100){
        levelUp();
    }
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
    level++;
    experience = 0;

    setMaxHP(getMaxHP() +10);
    setCurrentHP(getMaxHP());

    setAttack(getAttack()+2);
    setDefense(getDefense()+1);

    std::cout << "LEVEL UP! Congrats! You are now level " << level << "!\n";
    displayStats();
}
