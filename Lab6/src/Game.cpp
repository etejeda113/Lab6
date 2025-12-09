#include "Game.h"
#include "Item.h"
#include "Player.h"
#include "Shop.h" 
#include <iostream>
#include <sstream>
#include <algorithm>

// TODO: Implement Game constructor
Game::Game() : player(NULL), current_room(NULL), shop(NULL),
               game_over(false), victory(false) {
}


// TODO: Implement Game destructor
Game::~Game() {
    // TODO: Clean up player and all rooms
    if (player != NULL) {
        delete player;
        player = NULL;
    }

    for(std::map<std::string, Room*>::iterator it = world.begin(); it!= world.end(); it++){
        delete it->second;
    }

    world.clear();

    if(shop != NULL) {
        delete shop;
        shop = NULL;
    }
}


// TODO: Implement initializeWorld
// HINTS:
// - Create all rooms with new
// - Add each room to world using addRoom()
// - Connect rooms using connectRooms()
// - Add monsters to appropriate rooms using room->setMonster()
// - Add items to rooms using room->addItem()
// - Set current_room to starting room (entrance)
//
// SUGGESTED WORLD LAYOUT:
//                [Throne Room]
//                     |
//     [Armory] - [Hallway] - [Treasury]
//                     |
//                 [Entrance]
//
// MONSTERS:
// - Hallway: Goblin
// - Armory: Skeleton
// - Treasury: Skeleton
// - Throne Room: Dragon (boss!)
//
// ITEMS:
// - Entrance: Small Potion
// - Armory: Iron Sword, Chain Mail
// - Treasury: Health Potion
//
void Game::initializeWorld() {
    // TODO: Create rooms
    Room* entrance = new Room("Dungeon Entrance", "A dark stone corridor...");
    Room* hallway = new Room("Hallway", "A long halLway with flickering lights.");
    Room* armory = new Room("Armory", "Room filled with rusty weapons and armor.");
    Room* treasury = new Room("Treasury", "A room full of gold and chests.");
    Room* throne = new Room("Throne Room", "The Boss's massive room.");
    Room* laboratory = new Room("Laboratory", "A room full of strange equipment, multimeters, breadboards, wiressss...");
    Room* secret = new Room("Secret Chamber", "A hidden room with mysterious treasures.");

    shop = new Shop();
    shop->addToStock(new Weapon("Steel Sword", "A sharp blade", 5, 100), 100);
    shop->addToStock(new Armor("Plate Mail", "Heavy armor", 8, 150), 150);
    shop->addToStock(new Consumable("Mega Potion", "Restores 50 HP", 50, 75), 75);
    shop->addToStock(new Consumable("Super Potion", "Restores 30 HP", 30, 40), 40);

    // TODO: Add rooms to world
    addRoom(entrance);
    addRoom(hallway);
    addRoom(armory);
    addRoom(treasury);
    addRoom(throne);
    addRoom(laboratory);
    addRoom(secret);

    // TODO: Connect rooms bidirectionally
    connectRooms("Dungeon Entrance", "north", "Hallway");
    connectRooms("Hallway", "west", "Armory");
    connectRooms("Hallway", "east", "Treasury");
    connectRooms("Hallway", "north", "Throne Room");
    connectRooms("Hallway", "south", "Laboratory");    
    connectRooms("Laboratory", "east", "Secret Chamber");


    
    // TODO: Add monsters
    hallway->setMonster(new Goblin());
    armory->setMonster(new Skeleton());
    treasury->setMonster(new Troll());
    throne-> setMonster(new Dragon());
    laboratory->setMonster(new Wizard());
    secret->setMonster(new LAFUFU());
    entrance->setMonster(new LABUBU());


    // TODO: Add items
    entrance->addItem(new Consumable("Small Potion", "Restores 5 HP", 5, 20));
    entrance->addItem(new Armor("24k Gold Labubu Tracksuit", "Drip or Drown", 50, 500));
    armory->addItem(new Weapon("Iron Sword", "A sturdy sword", 2, 50));
    armory->addItem(new Armor("Chain Mail", "Armor that protects you", 3, 75));
    treasury->addItem(new Consumable("Health Potion", "Restores 20 HP", 20, 50));
    secret->addItem(new Key("Key", "Opens a secret door", 0));
    laboratory->addItem(new Scroll("Magic Scroll", "Contains a powerful spell", 5, 100));
    hallway->addItem(new Gold("Gold Coins", "A pile of shiny gold", 50, 0));

    // TODO: Set starting room
    current_room = entrance;
}


// TODO: Implement createStartingInventory
// HINTS:
// - Give player starting weapon: Rusty Dagger (damage +2)
// - Give player starting food: Bread (heals 5 HP)
// - Use: player->addItem(new Weapon(...))
//
void Game::createStartingInventory() {
    // TODO: Give player starting items
    if(player!= NULL){
        player->addItem(new Weapon("Rusty Dagger", "Damages 2 HP", 2, 10));
        player->addItem(new Consumable("Bread", "Restores 5 HP", 5, 5));
    }
}


// TODO: Implement addRoom
// HINTS:
// - Check if room pointer is not NULL
// - Add to world map using room's name as key
// - Use: world[room->getName()] = room
//
void Game::addRoom(Room* room) {
    // TODO: Add room to world map
    if(room!=NULL){
        world[room->getName()] = room;
    }
}


// TODO: Implement connectRooms
// HINTS:
// - Look up both rooms in world map
// - If both exist:
//   - Add forward direction: room1->addExit(direction, room2)
//   - Determine reverse direction:
//     * north ↔ south
//     * east ↔ west
//   - Add reverse direction: room2->addExit(reverse, room1)
//
void Game::connectRooms(const std::string& room1_name, const std::string& direction,
                       const std::string& room2_name) {
    // TODO: Connect rooms bidirectionally
    Room* room1 = world[room1_name];
    Room* room2 = world[room2_name];
    if (room1 == NULL || room2 == NULL){
        return;
    }

    room1->addExit(direction, room2);

    std::string reverse;
    if(direction == "north"){
        reverse = "south";
    }
    else if(direction == "south"){
        reverse = "north";
    }
    else if(direction == "east"){
        reverse = "west";
    }
    else if(direction == "west"){
        reverse = "east";
    }

    room2->addExit(reverse, room1);
}


// TODO: Implement run - main game loop
// HINTS:
// - Print welcome message and game title
// - Get player name from input 
// - Create player: player
// - Call initializeWorld()
// - Call createStartingInventory()
// - Display starting room
// - Mark starting room as visited
// - Main loop: 
//   - Print prompt: "> "
//   - Get command (use std::getline)
//   - Convert to lowercase (use std::transform)
//   - Call processCommand()
//   - Check victory condition
//   - Check defeat condition (player dead)
//
void Game::run() {
    // TODO: Implement main game loop
    std::string player_name;
    std::cout << "Welcome to Dungeon RPG!\n";
    std::cout << "Enter your name: ";
    std::getline(std::cin, player_name);

    std::cout << "Choose your class:\n";
    std::cout << "0 = Warrior\n1 = Mage\n2 = Rogue\n";
    int class_choice;
    std::cin >> class_choice;
    std::cin.ignore(); // discard leftover newline

    PlayerClass pc = static_cast<PlayerClass>(class_choice);
    player = new Player(player_name, pc);
    initializeWorld();
    createStartingInventory();

    std::cout << "\nStarting room:\n";
    current_room->display();
    current_room->markVisited();

    while(!game_over){
        std::cout << "\n> ";
        std::string command;
        std::getline(std::cin, command);

        //make lowercase
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);

        processCommand(command);

        //defeated?
        if(!player->isAlive()) {
            std::cout << "You died! Game over.\n";
            game_over = true;
        }

            // Check victory (dragon defeated)
        if(victory) {
            std::cout << "You defeated the Dragon! You win!\n";
            game_over = true;
        }
    }

}


// TODO: Implement processCommand
// HINTS:
// - Parse command into verb and object
// - Extract first word as verb
// - Rest of line is object
// - Dispatch to appropriate method based on verb:
//   * "go" or "move" → move(object)
//   * "look" or "l" → look()
//   * "attack" or "fight" → attack()
//   * "pickup" or "get" or "take" → pickupItem(object)
//   * "inventory" or "i" → inventory()
//   * "use" → useItem(object)
//   * "equip" or "e" → equip(object)
//   * "stats" → player->displayStats()
//   * "help" or "h" or "?" → help()
//   * "quit" or "exit" → set game_over to true
//
void Game::processCommand(const std::string& command) {
    // TODO: Parse and dispatch command
    std::istringstream iss(command);
    std::string verb;
    iss >> verb;

    std::string object;
    std::getline(iss, object);
    if(!object.empty() && object[0] == ' ') object.erase(0,1);

    if(verb == "go" || verb == "move"){
        move(object);
    }
    else if(verb == "look" || verb == "l"){
        look();
    }
    else if(verb == "attack" || verb == "fight"){
        attack();
    }
    else if(verb == "pickup" || verb == "get" || verb == "take"){
        pickupItem(object);
    }
    else if(verb == "inventory" || verb == "i"){
        inventory();
    }
    else if(verb == "use") {
        useItem(object);
    }
    else if(verb == "equip" || verb == "e"){
        equip(object);
    }
    else if(verb == "stats"){
        player->displayStats();
    }
    else if(verb == "help" || verb == "h" || verb == "?") {
        help();
    }
    else if(verb == "shop") {
        enterShop();
    }
    else if(verb == "quit" || verb == "exit") {
        game_over = true;
    }
    else{
        std::cout << "Unknown command. Type 'help' for a list of commands.\n";
    }
}

void Game::enterShop() {
    if(!shop) {
        std::cout << "There is no shop here.\n";
        return;
    }
    
    std::cout << "\nYou enter Charlie's Shop...\n";
    bool in_shop = true;
    
    while(in_shop) {
        shop->shop_display(player);
        std::cout << "\nShop> ";
        std::string command;
        std::getline(std::cin, command);
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        
        std::istringstream iss(command);
        std::string verb;
        iss >> verb;
        std::string object;
        std::getline(iss, object);
        if(!object.empty() && object[0] == ' ') object.erase(0,1);
        
        if(verb == "buy") {
            if(object.empty()) {
                std::cout << "Buy what? Usage: buy <item name>\n";
            } else {
                shop->buyItem(player, object);
            }
        }
        else if(verb == "sell") {
            if(object.empty()) {
                std::cout << "Sell what? Usage: sell <item name>\n";
            } else {
                shop->sellItem(player, object);
            }
        }
        else if(verb == "leave" || verb == "exit") {
            std::cout << "You leave the shop.\n";
            in_shop = false;
        }
        else {
            std::cout << "Unknown shop command. Options: buy <item>, sell <item>, leave\n";
        }
    }
}


// TODO: Implement move
// HINTS:
// - Check if monster blocks path (current_room->hasMonster())
// - If blocked, print message and return
// - Get exit in specified direction
// - If exit exists:
//   - Update current_room
//   - Display new room
//   - Mark as visited
// - Otherwise print error: "You can't go that way!"
//
void Game::move(const std::string& direction) {
    // TODO: Move to adjacent room
    if(current_room->getMonster() != NULL) {
        std::cout << "A " << current_room->getMonster()->getName() << " is blocking your path!\n";
        return;
    }
    Room* next = current_room->getExit(direction);
    if(next != NULL) {
        current_room = next;
        current_room->display();
        current_room->markVisited();
    } else {
        std::cout << "You can't go that way!\n";
    }

}


// TODO: Implement look
// HINTS:
// - Simply display current room
//
void Game::look() {
    // TODO: Display current room
    current_room->display();
}


// TODO: Implement attack
// HINTS:
// - Check if monster in room
// - If no monster, print message and return
// - If monster present, call combat()
//
void Game::attack() {
    // TODO: Attack monster in room
    Monster* m = current_room->getMonster();
    if(!m) {
        std::cout << "There is no monster here.\n";
        return;
    }
    combat(m);

}


// TODO: Implement combat
// HINTS:
// - Print "=== COMBAT BEGINS ==="
// - Combat loop: while both player and monster are alive
//   - Prompt for player action: attack/use <item>/flee
//   - If attack:
//     * Calculate player damage
//     * Monster takes damage
//     * If monster dead:
//       - Print victory
//       - Player gains exp and gold
//       - Get loot from monster
//       - Add loot to current room
//       - Check if Dragon 
//       - Clear monster from room
//       - Break from loop
//   - If use:
//     * Extract item name from command
//     * Call player->useItem()
//   - If flee:
//     * Print message and break
//   - Monster turn (if alive):
//     * Print attack message
//     * Calculate monster damage
//     * Player takes damage
// - Print "=== COMBAT ENDS ==="
//
void Game::combat(Monster* monster) {
    // TODO: Implement turn-based combat
    
    std::cout << "=== COMBAT BEGINS ===\n";

    while(player->isAlive() && monster->isAlive()) {
        std::cout << "Your action (attack/use <item>/flee): ";
        std::string action;
        std::getline(std::cin, action);
        std::transform(action.begin(), action.end(), action.begin(), ::tolower);

        std::istringstream iss(action);
        std::string verb;
        iss >> verb;
        std::string object;
        std::getline(iss, object);
        if(!object.empty() && object[0]==' ') object.erase(0,1);

        if(verb == "attack") {
            int dmg = player->calculateDamage();
            std::cout << "You attack " << monster->getName() << " for " << dmg << " damage.\n";
            monster->takeDamage(dmg);

            if(!monster->isAlive()) {
                std::cout << "You defeated " << monster->getName() << "!\n";
                player->gainExperience(monster->getExperienceReward());
                player->addGold(monster->getGoldReward());

                // Drop loot
                std::vector<Item*> loot = monster->dropLoot();
                for (size_t i = 0; i < loot.size(); i++) {
                        current_room->addItem(loot[i]);
                    }


                if(monster->getName() == "Dragon") victory = true;

                current_room->clearMonster();
                break;

        }
                
        } else if(verb == "use") {
            useItem(object);
        } else if(verb == "flee") {
            std::cout << "You flee from combat!\n";
            break;
        } else {
            std::cout << "Invalid combat action.\n";
            continue;
        }

        // Monster attacks if alive
        if(monster->isAlive()) {
            int mdmg = monster->calculateDamage();
            std::cout << monster->getName() << " attacks you for " << mdmg << " damage.\n";
            player->takeDamage(mdmg);
        }
    }

    std::cout << "=== COMBAT ENDS ===\n";
}


// TODO: Implement pickupItem
// HINTS:
// - Get item from current room
// - If exists:
//   - Add to player inventory
//   - Remove from room (ownership transfer!)
// - Otherwise print error
//
void Game::pickupItem(const std::string& item_name) {
    // TODO: Pick up item from room
    Item* item = current_room->getItem(item_name);
    if(item){
        player->addItem(item);
        current_room->removeItem(item_name);
        //std::cout << "Picked up " << item->getName() << ".\n";
    } else {
        std::cout << "No such item here.\n";
    }
}


// TODO: Implement inventory
//
void Game::inventory() {
    // TODO: Display player inventory
    player->displayInventory();
}


// TODO: Implement useItem
// HINTS:
// - Call player->useItem(item_name)
//
void Game::useItem(const std::string& item_name) {
    // TODO: Use item from inventory
    player->useItem(item_name);
}


// TODO: Implement equip
// HINTS:
// - Get item from player inventory
// - Check if item exists
// - Check item type:
//   - If "Weapon": call player->equipWeapon()
//   - If "Armor": call player->equipArmor()
//   - Otherwise: print error (can't equip consumables)
//
void Game::equip(const std::string& item_name) {
    // TODO: Equip weapon or armor
    Item* item = player->getItem(item_name);
    if(!item) {
        std::cout << "No such item in inventory.\n";
        return;
    }

    if(item->getType() == "Weapon") player->equipWeapon(item->getName());
    else if(item->getType() == "Armor") player->equipArmor(item->getName());
    else std::cout << "Unable to equip consumable.\n";

}


// TODO: Implement help
// HINTS:
// - Print all available commands with descriptions
// - Format nicely with headers
// - Commands:
//   * go <direction> - Move
//   * look - Look around
//   * attack - Attack monster
//   * pickup <item> - Pick up item
//   * inventory - Show inventory
//   * use <item> - Use consumable
//   * equip <item> - Equip weapon/armor
//   * stats - Show character stats
//   * help - Show this help
//   * quit - Exit game
//
void Game::help() {
    // TODO: Display help message
    std::cout << "Available commands:\n";
    std::cout << "  go <direction> - Move\n";
    std::cout << "  look - Look around\n";
    std::cout << "  attack - Attack monster\n";
    std::cout << "  pickup <item> - Pick up item\n";
    std::cout << "  inventory - Show inventory\n";
    std::cout << "  use <item> - Use consumable\n";
    std::cout << "  equip <item> - Equip weapon/armor\n";
    std::cout << "  stats - Show character stats\n";
    std::cout << "  shop - Enter the shop\n"; 
    std::cout << "  help - Show this help\n";
    std::cout << "  quit - Exit game\n";
}
