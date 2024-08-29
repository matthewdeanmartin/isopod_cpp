#include <algorithm> // For std::find
#include <iostream>
#include <map>
#include <string>
#include <vector>

// ANSI escape codes for colored and styled output
const std::string RESET = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string ITALIC = "\033[3m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";

class Game {
public:
  Game() {
    initialize_map();
    current_location = "Entrance";
    found_hideout = false;
    found_cookie = false;
    found_friend = false;
  }

  void play() {
    std::string command;
    print_welcome_message();
    describe_current_location();

    while (!is_game_won()) {
      std::cout << BOLD << GREEN << "\nWhat will you do? " << RESET;
      std::getline(std::cin, command);
      process_command(command);
    }

    print_victory_message();
  }

private:
  std::map<std::string, std::vector<std::string>> map;
  std::string current_location;
  std::vector<std::string> inventory;
  bool found_hideout;
  bool found_cookie;
  bool found_friend;

  void initialize_map() {
    map["Entrance"] = {"Garden", "Shed"};
    map["Garden"] = {"Entrance", "Rock", "Flowerbed"};
    map["Shed"] = {"Entrance", "CookieCrumb"};
    map["Rock"] = {"Garden", "Hideout"};
    map["Flowerbed"] = {"Garden"};
    map["CookieCrumb"] = {"Shed"};
    map["Hideout"] = {"Rock"};
  }

  void print_welcome_message() {
    std::cout << BLUE << ITALIC << "Welcome, little isopod!" << RESET << "\n";
    std::cout << "You are on a mission to find:"
              << "\n";
    std::cout << YELLOW << "1. A place to hide 🏠" << RESET << "\n";
    std::cout << YELLOW << "2. A cookie crumb 🍪" << RESET << "\n";
    std::cout << YELLOW << "3. Another isopod friend 🐞" << RESET << "\n";
    std::cout << "Use commands like 'go', 'inventory', 'search', and 'help' to "
                 "play.\n";
  }

  void describe_current_location() {
    std::cout << BOLD << "You are now at: " << YELLOW << current_location
              << RESET << "\n";
    std::cout << BOLD << "You can go to: " << RESET;

    if (map[current_location].empty()) {
      std::cout << ITALIC << "Nowhere" << RESET << "\n";
    } else {
      for (size_t i = 0; i < map[current_location].size(); ++i) {
        std::cout << YELLOW << map[current_location][i] << RESET;
        if (i < map[current_location].size() - 1) {
          std::cout << ", ";
        }
      }
      std::cout << "\n";
    }
  }

  void print_victory_message() {
    std::cout << BOLD << GREEN
              << "\nCongratulations! 🎉 You've completed your mission!" << RESET
              << "\n";
  }

  void process_command(const std::string &command) {
    if (command == "help") {
      print_help();
    } else if (command == "inventory") {
      print_inventory();
    } else if (command.find("go") == 0) {
      std::string direction = command.length() > 3 ? command.substr(3) : "";
      if (direction.empty()) {
        std::cout << RED << "You need to specify a location to go." << RESET
                  << "\n";
      } else {
        move_to_location(direction);
      }
    } else if (command == "search") {
      search_current_location();
    } else {
      std::cout << RED << "Unknown command. Type 'help' for a list of commands."
                << RESET << "\n";
    }
  }

  void print_help() {
    std::cout << BOLD << "\nAvailable commands:" << RESET << "\n";
    std::cout << ITALIC << "go [location]" << RESET
              << " - Move to a different location.\n";
    std::cout << ITALIC << "search" << RESET
              << " - Search the current location.\n";
    std::cout << ITALIC << "inventory" << RESET << " - Check your inventory.\n";
    std::cout << ITALIC << "help" << RESET << " - Show this help message.\n";
  }

  void print_inventory() {
    std::cout << BOLD << "\nYour inventory contains:" << RESET << "\n";
    if (inventory.empty()) {
      std::cout << ITALIC << "Nothing yet..." << RESET << "\n";
    } else {
      for (const auto &item : inventory) {
        std::cout << YELLOW << item << RESET << "\n";
      }
    }
  }

  void move_to_location(const std::string &location) {
    if (map[current_location].empty()) {
      std::cout << RED << "You can't go anywhere from here." << RESET << "\n";
      describe_current_location();
      return;
    }

    for (const auto &loc : map[current_location]) {
      if (loc == location) {
        current_location = location;
        std::cout << BLUE << "You move to " << location << "." << RESET << "\n";
        describe_current_location();
        return;
      }
    }
    std::cout << RED << "You can't go there from here." << RESET << "\n";
    describe_current_location();
  }

  void search_current_location() {
    if (current_location == "Hideout" && !found_hideout) {
      std::cout << GREEN << "You found a cozy hideout! 🏠" << RESET << "\n";
      found_hideout = true;
    } else if (current_location == "CookieCrumb" && !found_cookie) {
      std::cout << GREEN << "You found a delicious cookie crumb! 🍪" << RESET
                << "\n";
      found_cookie = true;
    } else if (current_location == "Garden" && !found_friend) {
      std::cout << GREEN << "You found another isopod friend! 🐞" << RESET
                << "\n";
      found_friend = true;
    } else {
      std::cout << YELLOW << "There's nothing special here..." << RESET << "\n";
    }

    update_inventory();
  }

  void update_inventory() {
    if (found_hideout && std::find(inventory.begin(), inventory.end(),
                                   "Hideout") == inventory.end()) {
      inventory.push_back("Hideout");
    }
    if (found_cookie && std::find(inventory.begin(), inventory.end(),
                                  "Cookie Crumb") == inventory.end()) {
      inventory.push_back("Cookie Crumb");
    }
    if (found_friend && std::find(inventory.begin(), inventory.end(),
                                  "Isopod Friend") == inventory.end()) {
      inventory.push_back("Isopod Friend");
    }
  }

  bool is_game_won() const {
    return found_hideout && found_cookie && found_friend;
  }
};

int main() {
  Game game;
  game.play();
  return 0;
}
