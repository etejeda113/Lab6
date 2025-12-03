#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

/**
 * Main entry point for Dungeon Crawler RPG
 * 
 * This program demonstrates:
 * - C++ class hierarchies and inheritance
 * - STL containers (vector, map, string)
 * - Polymorphism with virtual functions
 * - Dynamic memory management with new/delete
 * - Resource management with destructors (RAII)
 * 
 * LEARNING OBJECTIVES:
 * - Complete object-oriented design
 * - Multi-file project organization
 * - Memory management patterns
 */

int main() {
    // Seed random number generator for combat calculations
    // This ensures different random numbers each time the game runs
    srand(static_cast<unsigned int>(time(0)));
    
    try {

        /* -----------------------WEEK 1 TESTING-------------------------
        // Testing Character 

        std::cout << "-----Testing Character-----\n";
        Character hero("Hero", 100, 10, 5);
        hero.displayStats();
        hero.takeDamage(20);
        hero.displayStats();
        hero.heal(10);
        hero.displayStats();
        std::cout << "\n";

        // Testing Items

        std::cout << "----- Item Tests -----\n";
        Weapon sword("Iron Sword", "A sturdy blade", 5);
        Armor chainmail("Chain Mail", "Protective armor", 3);
        Consumable potion("Health Potion", "Restores HP", 20);

        sword.displayInfo();
        chainmail.displayInfo();
        potion.displayInfo();
        potion.use();
        potion.use();
        std::cout << "\n";

        // Testing Inventory

        std::cout << "----- Inventory Tests -----\n";

        std::vector<Item*> inventory;
        
        // Add items
        inventory.push_back(new Weapon("Sword", "Sharp blade", 5));
        inventory.push_back(new Armor("Shield", "Wooden shield", 2));
        inventory.push_back(new Consumable("Potion", "Heals", 20));
        
        // Display all
        for (int i = 0; i < inventory.size(); i++) {
            inventory[i]->displayInfo();
        }
        
        // Clean up - VERY IMPORTANT!
        for (int i = 0; i < inventory.size(); i++) {
            delete inventory[i];
        }
        inventory.clear();
        
        return 0;    


        // --------- WEEK 1 DONE and TESTED (NO MEM LEAKS!!!) -------------*/

        //---------------------- WEEK 2 TESTING ---------------------------

        
        /*
        Player hero("Alice");
        hero.displayStats();
        hero.takeDamage(20);  // Inherited method
        hero.displayStats();
        return 0;
        */
        
        /*
        Player hero("Bob");
        hero.addItem(new Weapon("Sword", "Sharp", 5));
        hero.addItem(new Consumable("Potion", "Heals", 20));
        hero.displayInventory();
        hero.removeItem("potion");  // Case insensitive
        hero.displayInventory();
        return 0;
        */

        /*
        Player hero("Charlie");
        hero.addItem(new Weapon("Sword", "Sharp", 5));
        hero.addItem(new Armor("Chainmail", "Strong", 3));
        
        hero.equipWeapon("sword");
        hero.equipArmor("chainmail");
        
        hero.displayStats();
        
        int dmg = hero.calculateDamage();
        std::cout << "Damage: " << dmg << std::endl;  // Should include weapon bonus
        
        return 0;
        */
        
        /*
        Player hero("Dana");
        hero.displayStats();
        hero.gainExperience(100);  // Should trigger level up
        hero.displayStats();
        return 0;
        */

        /*
        Monster orc("Orc", 50, 8, 3, 20, 10);
        orc.addLoot(new Consumable("Potion", "Heals", 15));
        orc.displayStats();
        orc.takeDamage(30);
        
        std::vector<Item*> loot = orc.dropLoot();
        // Clean up loot
        for (int i = 0; i < loot.size(); i++) {
            delete loot[i];
        }
        
        return 0;
        */
        
        /*
        // Test polymorphism - base class pointers to derived objects
        Monster* monsters[3];
        monsters[0] = new Goblin();
        monsters[1] = new Skeleton();
        monsters[2] = new Dragon();
        
        for (int i = 0; i < 3; i++) {
            monsters[i]->displayStats();
            std::cout << monsters[i]->getAttackMessage() << std::endl;
            int dmg = monsters[i]->calculateDamage();
            std::cout << "Damage: " << dmg << std::endl;
            std::cout << std::endl;
        }
        
        // Clean up
        for (int i = 0; i < 3; i++) {
            delete monsters[i];
        }
        
        return 0;
        */
       
        // --------- WEEK 2 DONE and TESTED (NO MEM LEAKS!!!) -------------*/


        // Create game object
        Game game;
        
        // Run main game loop
        // This doesn't return until game is over
        game.run();
        

        /* ---------------------- WEEK 3 TESTING --------------------------
        Room entrance("Entrance", "A dark corridor");
        entrance.display();
   
        Room room1("Room 1", "First room");
        Room room2("Room 2", "Second room");
        
        room1.addExit("north", &room2);
        room2.addExit("south", &room1);
        
        room1.display();
        
        Room* next = room1.getExit("north");
        if (next) {
            next->display();
        }
        
        Room room("Armory", "Weapons everywhere");
        room.addItem(new Weapon("Sword", "Sharp", 5));
        room.setMonster(new Goblin());
        
        room.display();
        
        if (room.hasMonster()) {
            std::cout << "Monster present!" << std::endl;
        }
        
        return 0;

        // --------- WEEK 3 DONE and TESTED (NO MEM LEAKS!!!) -------------*/


    }
    catch (const std::exception& e) {
        // Catch any exceptions and print error message
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    // Normal exit
    return 0;
}
