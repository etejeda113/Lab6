#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

/**
 * Item class - Base class for all items in the game
 * 
 * This hierarchy demonstrates inheritance with three derived types:
 * - Weapon (increases attack damage)
 * - Armor (increases defense)
 * - Consumable (single-use healing items)
 * 
 * LEARNING OBJECTIVES:
 * - Practice inheritance
 * - Override virtual functions
 * - Understand polymorphism through items
 */
class Item {
private:
    std::string name;
    std::string description;
    std::string type;  // "Weapon", "Armor", or "Consumable"
    int value;  // Damage bonus, defense bonus, or healing amount
    int gold_price;
    
public:
    // Constructor
    // TODO: Implement in Item.cpp
    Item(const std::string& name, const std::string& description, 
         const std::string& type, int value, int gold_price=0);
    
    // Destructor
    // TODO: Implement in Item.cpp
    virtual ~Item();
    
    // Getters (inline)
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    std::string getType() const { return type; }
    int getValue() const { return value; }
    int getGoldPrice() const {return gold_price; }
    
    // Virtual function with default implementation
    // Derived classes should override this
    // TODO: Implement in Item.cpp
    virtual void displayInfo() const;
    
    // Virtual function for using items
    // Default does nothing - Consumable overrides
    virtual void use() { }
    
    // Display brief item info
    // TODO: Implement in Item.cpp
    void displayBrief() const;
};

/**
 * Weapon class - Items that increase attack damage
 */
class Weapon : public Item {
private:
    int damage_bonus;
    
public:
    // Constructor
    // TODO: Implement in Item.cpp
    // HINT: Must call base Item constructor in initializer list
    Weapon(const std::string& name, const std::string& description, int damage, int gold_price=0);
    
    // Override displayInfo to show weapon-specific format
    // TODO: Implement in Item.cpp
    void displayInfo() const;
    
    // Getter
    int getDamageBonus() const { return damage_bonus; }
};

/**
 * Armor class - Items that increase defense
 */
class Armor : public Item {
private:
    int defense_bonus;
    
public:
    // Constructor
    // TODO: Implement in Item.cpp
    // HINT: Must call base Item constructor in initializer list
    Armor(const std::string& name, const std::string& description, int defense, int gold_price=0);
    
    // Override displayInfo to show armor-specific format
    // TODO: Implement in Item.cpp
    void displayInfo() const;
    
    // Getter
    int getDefenseBonus() const { return defense_bonus; }
};

/**
 * Consumable class - Single-use items (potions, food)
 */
class Consumable : public Item {
private:
    int healing_amount;
    bool used;
    
public:
    // Constructor
    // TODO: Implement in Item.cpp
    // HINT: Must call base Item constructor in initializer list
    Consumable(const std::string& name, const std::string& description, int healing, int gold_price=0);
    
    // Override displayInfo to show consumable-specific format
    // TODO: Implement in Item.cpp
    void displayInfo() const;
    
    // Override use function
    // TODO: Implement in Item.cpp
    void use();
    
    // Getters
    int getHealingAmount() const { return healing_amount; }
    bool isUsed() const { return used; }
};

/**
 * Key class - Unlock doors
 */
class Key : public Item {
public:
    Key(const std::string& name, const std::string& description, int gold_price=0);
    void displayInfo() const;
    void use();
};

/**
 * Scroll class
 */
class Scroll : public Item {
private:
    int bonus;
    bool used;
public:
    Scroll(const std::string& name, const std::string& description, int bonus, int gold_price=0);
    void displayInfo() const;
    void use();
    int getBonusAmount() const {return bonus;}
    bool isUsed() const{return used;} 
};

/**
 * Gold class - Can be collected or sold
 */
class Gold : public Item {
private:
    int amount;
public:
    Gold(const std::string& name, const std::string& description, int amount, int gold_price=0);
    void displayInfo() const;
    void use();
    int getAmount() const { return amount;}

};
#endif // ITEM_H
