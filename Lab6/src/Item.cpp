#include "Item.h"

// ============================================================================
// Base Item class implementation
// ============================================================================

// TODO: Implement Item constructor
// HINTS:
// - Use initializer list to initialize all member variables
// - Parameters map directly to member variables
//
Item::Item(const std::string& name, const std::string& description,
           const std::string& type, int value)
    : name(name), description(description), type(type), value(value) {
}


// TODO: Implement Item destructor
// HINTS:
// - Can add debug output if helpful
//
Item::~Item() {
    //std::cout << "DEBUGGING Destorying Item: " << name << std::endl;
}


// TODO: Implement displayInfo (base version)
// HINTS:
// - Print item name, description, and value
// - Format: 
//   [ITEM] ItemName
//     Description text
//     Value: X
//
void Item::displayInfo() const {
    // TODO: Display item information
    std::cout << "[ITEM] " << name << "\n" 
        << "  " << description << "\n" 
        << "  Value: " << value << std::endl;
}


// TODO: Implement displayBrief
// HINTS:
// - One line format: "Name (Type)"
// - Example: "Iron Sword (Weapon)"
//
void Item::displayBrief() const {
    // TODO: Display brief item info
    std::cout << name << " (" << type << ")" << std::endl;
}


// ============================================================================
// Weapon class implementation
// ============================================================================

// TODO: Implement Weapon constructor
// HINTS:
// - MUST call base Item constructor using initializer list
// - Type should be "Weapon"
// - Value is the damage bonus
// - Also initialize damage_bonus member
// - Format: Weapon::Weapon(...) : Item(name, desc, "Weapon", damage), damage_bonus(damage) { }
//
Weapon::Weapon(const std::string& name, const std::string& description, int damage)
    : Item(name, description, "Weapon", damage), damage_bonus(damage) {
}


// TODO: Override displayInfo for Weapon
// HINTS:
// - Print weapon-specific format
// - Use getName(), getDescription(), getDamageBonus()
// - Format:
//   [WEAPON] WeaponName
//     Description
//     Damage Bonus: +X
//
void Weapon::displayInfo() const {
    // TODO: Display weapon-specific information
    std::cout << "[WEAPON] " << getName() << "\n" 
        << "  " << getDescription() << "\n" 
        << "  Damage Bonus: +" << getDamageBonus() << std::endl;
}


// ============================================================================
// Armor class implementation
// ============================================================================

// TODO: Implement Armor constructor
// HINTS:
// - MUST call base Item constructor using initializer list
// - Type should be "Armor"
// - Value is the defense bonus
// - Also initialize defense_bonus member
//
Armor::Armor(const std::string& name, const std::string& description, int defense)
    : Item(name, description, "Armor", defense), defense_bonus(defense) {
}


// TODO: Override displayInfo for Armor
// HINTS:
// - Print armor-specific format
// - Format:
//   [ARMOR] ArmorName
//     Description
//     Defense Bonus: +X
//
void Armor::displayInfo() const {
    // TODO: Display armor-specific information
    std::cout << "[ARMOR] " << getName() << "\n"
        << "  " << getDescription() << "\n"
        << "  Defense Bonus: +" << getDefenseBonus() << std::endl;
}


// ============================================================================
// Consumable class implementation
// ============================================================================

// TODO: Implement Consumable constructor
// HINTS:
// - MUST call base Item constructor using initializer list
// - Type should be "Consumable"
// - Value is the healing amount
// - Initialize healing_amount and set used to false
//
Consumable::Consumable(const std::string& name, const std::string& description, 
                       int healing)
    : Item(name, description, "Consumable", healing), 
      healing_amount(healing), used(false) {
}


// TODO: Override displayInfo for Consumable
// HINTS:
// - Print consumable-specific format
// - Format:
//   [CONSUMABLE] ConsumableName
//     Description
//     Restores: X HP
//
void Consumable::displayInfo() const {
    // TODO: Display consumable-specific information
    std::cout << "[CONSUMABLE] " << getName() << "\n"
        << "  " << getDescription() << "\n"
        << "  Restores: " << healing_amount << " HP" << std::endl;

}


// TODO: Implement use() function
// HINTS:
// - Check if already used
// - If not used: print message and set used to true
// - If already used: print error message
// - Format: "Used ItemName! Restored X HP."
//
void Consumable::use() {
    // TODO: Implement use logic
    if(used){
        std::cout << "Error: " << getName() << " has already been used."
        << std::endl;
        return;
    }
        std::cout << "Used " <<getName() << "! Restored " 
        << healing_amount << " HP." << std::endl;
        used = true;
}

// Key implementaion 
Key::Key(const std::string& name, const std::string& description)
    : Item(name, description, "Key", 0) { 
    }

void Key::displayInfo() const {
    std::cout << "[KEY] " << getName() << "\n"
              << "  Unlocks: " << getDescription() << std::endl;
}

void Key::use() {
    std::cout << "You try using " << getName() << ". It might unlock something!\n";
}


// Scroll implementation
Scroll::Scroll(const std::string& name, const std::string& description, int bonus)
    : Item(name, description, "Scroll", bonus), bonus(bonus), used(false){ 
    }

void Scroll::displayInfo() const {
    std::cout << "[SCROLL] " << getName() << "\n"
              << "  " << getDescription() << std::endl;
    std::cout << "  Bonus: +" << getBonusAmount() << " HP" << std::endl;
}

void Scroll::use() {
    if(!used){
        used = true;
        std::cout << "Using " << getName() << "! " << getBonusAmount() << " HP icreased.\n";
    }else{
        std::cout << "ERROR: " << getName() << " has already been activated.\n";
    }
}

// Gold implementation
Gold::Gold(const std::string& name, const std::string& description, int amt)
    : Item(name, description, "Gold", amt), amount(amt) { }

void Gold::displayInfo() const {
    std::cout << "[GOLD] " << getName() << "\n";
    std::cout << "  " << getDescription() << std::endl;
    std::cout << "  Gold: " <<getAmount() << std::endl;
}

void Gold::use() {
    std::cout << "Collected " << amount << " gold coins.\n";
}
