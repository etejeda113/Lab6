#include "Monster.h"
#include <iostream>

// ============================================================================
// Base Monster class
// ============================================================================

// TODO: Implement Monster constructor
// HINTS:
// - MUST call Character base constructor
// - Initialize experience_reward and gold_reward
// - Loot table starts empty automatically
//
Monster::Monster(const std::string& name, int hp, int attack, int defense,
                 int exp_reward, int gold_reward)
    : Character(name, hp, attack, defense),
      experience_reward(exp_reward), gold_reward(gold_reward) {
}


// TODO: Implement Monster destructor
// HINTS:
// - Deallocate any allocated memory 
// - Loop through loot_table vector and delete each Item*
// - Clear the vector after deleting items
//
Monster::~Monster() {
    for (size_t i = 0; i < loot_table.size(); i++) {
        delete loot_table[i]; 
    }
    loot_table.clear();
}


// TODO: Override displayStats
// HINTS:
// - Show monster name and HP
// - Format: "MonsterName [HP: current/max]"
// - Keep it simple - monsters don't need detailed stats display
//
void Monster::displayStats() const {
    // TODO: Display monster stats
    std::cout << getName() << " [HP: " << getCurrentHP() << "/" << getMaxHP() << "]\n";
}


// TODO: Implement addLoot
// HINTS:
// - Check if item pointer is not NULL
// - Add item to loot_table vector using push_back()
//
void Monster::addLoot(Item* item) {
    // TODO: Add item to loot table
    if(item!=NULL){
        loot_table.push_back(item);
    }
}


// TODO: Implement dropLoot
// HINTS:
// - Create a copy of the loot_table vector
// - Clear the original loot_table (transfer ownership to caller!)
// - Return the copy
// - This is important: caller now owns the items and must delete them
//
std::vector<Item*> Monster::dropLoot() {
    // TODO: Return loot and transfer ownership
    std::vector<Item*> dropped = loot_table;
    loot_table.clear();
    return dropped;
}


// TODO: Implement getAttackMessage (base version)
// HINTS:
// - Return default attack message
// - Format: "MonsterName attacks!"
// - Use getName() to get monster's name
//
std::string Monster::getAttackMessage() const {
    // TODO: Return attack message
    return getName() + " attacks!";
}


// ============================================================================
// Goblin - Weak but common enemy
// ============================================================================

// TODO: Implement Goblin constructor
// HINTS:
// - Call Monster constructor with these stats:
//   * Name: "Goblin"
//   * HP: 30
//   * Attack: 5
//   * Defense: 2
//   * Experience: 10
//   * Gold: 5
// - Add a small potion to loot table
// - Example: addLoot(new Consumable("Small Potion", "Restores 10 HP", 10));
//
Goblin::Goblin() 
    : Monster("Goblin", 30, 5, 2, 10, 5) {
    // TODO: Add loot items
    addLoot(new Consumable("Small Potion", "Restores 10 HP", 10));
}


// TODO: Override getAttackMessage for Goblin
// HINTS:
// - Return goblin-specific attack message
// - Example: "The goblin swipes at you with its rusty dagger!"
//
std::string Goblin::getAttackMessage() const {
    // TODO: Return goblin attack message
    return "The goblin swipes at you with its rusty dagger!";
}





// ============================================================================
// Skeleton - Undead warrior
// ============================================================================

// TODO: Implement Skeleton constructor
// HINTS:
// - Call Monster constructor with these stats:
//   * Name: "Skeleton"
//   * HP: 40
//   * Attack: 8
//   * Defense: 4
//   * Experience: 20
//   * Gold: 10
// - Add an old sword to loot table
//
Skeleton::Skeleton()
    : Monster("Skeleton", 40, 8, 4, 20, 10) {
    // TODO: Add loot items
    addLoot(new Weapon("Old Sword", "A rusty old sword", 3));

}

// TODO: Override getAttackMessage for Skeleton
// HINTS:
// - Return skeleton-specific attack message
// - Example: "The skeleton rattles its bones and slashes with a sword!"
//
std::string Skeleton::getAttackMessage() const {
    // TODO: Return skeleton attack message
    return "The skeleton rattles its bones and slashes with a sword!";    
}

// Troll
Troll::Troll()
    : Monster("Troll", 120, 7, 4, 15, 10) {
    // TODO: Add loot items
    addLoot(new Armor("Thick Skin Armor", "Thick wearable troll hide armor", 30));

}

std::string Troll::getAttackMessage() const {
    // Return troll attack message
    return "The hefty troll sure can take a hit but sends a shockwave when charging at you!";
}


// Ghost
Ghost::Ghost()
    : Monster("Ghost", 60, 7, 2, 10, 6) {
    // TODO: Add loot items
    addLoot(new Armor("Armor of Delusion", "For a brief period you no longer need to worry about losing life!", 30));

}

std::string Ghost::getAttackMessage() const {
    // Return ghost attack message
    return "The ghost haunts you causing frequent headaches!";
}

//Wizard
Wizard::Wizard()
    : Monster("Wizard", 140, 16, 6, 25, 25) {
    // TODO: Add loot items
    addLoot(new Weapon("Sorcery", "Spellbook for Sorcery!", 30));

}

// Wizard
std::string Wizard::getAttackMessage() const {
    // Return wizard attack message
    return "The Wizard casts a nasty spell on you!";
}

/* Charlie Kirk
CharlieKirk::CharlieKirk()
    : Monster("Charlie Kirk", 120, 7, 4, 15, 10) {
    // TODO: Add loot items
    addLoot(new Weapon("Torch", "We carry the flame! We honor his name", 30));

}

std::string CharlieKirk::getAttackMessage() const {
    // Return troll attack message
    return "WE ARE CHARLIE KIRKKK! WE CAAAAAARRY THE FLAAAAAME...";
}

*/

//LABUBU
LABUBU::LABUBU()
    : Monster("LABUBU", 67, 13, 7, 69, 420) {
    // TODO: Add loot items
    addLoot(new Armor("24K Gold Dior Bag", "24k Gold Dior bag to hold all your essentials", 21));

}

std::string LABUBU::getAttackMessage() const {
    // Return wizard attack message
    return "Labubu Labu Labu Labubu Serenade";
}


//LABUBU
LAFUFU::LAFUFU()
    : Monster("LAFUFU", 67, 14, 7, 69, 420) {
    // TODO: Add loot items
    addLoot(new Weapon("Labubu Disguise", "Labubu from Temu", 3));

}

std::string LAFUFU::getAttackMessage() const {
    // Return wizard attack message
    return "Labubu Labu Labu Labubu Serenade";
}

// ============================================================================
// Dragon - Boss enemy with special ability
// ============================================================================

// TODO: Implement Dragon constructor
// HINTS:
// - Call Monster constructor with these stats:
//   * Name: "Dragon"
//   * HP: 150
//   * Attack: 20
//   * Defense: 10
//   * Experience: 100
//   * Gold: 50
// - Add legendary loot:
//   * Dragon Slayer sword (damage +10)
//   * Dragon Scale Armor (defense +8)
//   * Greater Health Potion (heals 100 HP)
//
Dragon::Dragon()
    : Monster("Dragon", 150, 20, 10, 100, 50) {
    // TODO: Add legendary loot items
    addLoot(new Weapon("Dragon Slayer", "Legendary sword with +10 damage", 10));
    addLoot(new Armor("Dragon Scale Armor", "Legendary armor with +8 defense", 8));
    addLoot(new Consumable("Greater Health Potion", "Restores 100 HP", 100));

}


// TODO: Override getAttackMessage for Dragon
// HINTS:
// - Return dragon-specific attack message
// - Example: "The dragon breathes fire at you!"
//
std::string Dragon::getAttackMessage() const {
    // TODO: Return dragon attack message
    return "The dragon breathes fire at you!";
}


// TODO: Override calculateDamage for Dragon
// HINTS:
// - Call Monster::calculateDamage() to get base damage
// - Add bonus fire damage (+5)
// - Return total damage
// - This makes the dragon hit harder than other monsters!
//
int Dragon::calculateDamage() const {
    // TODO: Calculate damage with fire bonus
    return getAttack() + 5; // Base attack + fire damage
}
