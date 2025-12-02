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





        
        // --------- WEEK 1 DONE and TESTED (NO MEM LEAKS!!!) -------------*/


        // Create game object
        /*Game game;
        
        // Run main game loop
        // This doesn't return until game is over
        game.run();
        */
    }
    catch (const std::exception& e) {
        // Catch any exceptions and print error message
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    // Normal exit
    return 0;
}
