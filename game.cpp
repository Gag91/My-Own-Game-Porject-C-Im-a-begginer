#include <iostream>
#include <string>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <vector>

void print_character(const std::string &name, const std::string &classType, int level, const std::string &sep);
void guess_game(const std::string &sep, int &playerXp);
void show_stats(const std::string &name, const std::string &classType, int level, int playerXp, int xpnextlevel, const std::string &sep);
void main_menu();
void play_game(const std::string &sep, int level);
void dice_game(int &playerXp, const std::string &sep);

std::vector<std::string> items = {"Bow"};
int money = 100;
bool is_valid_class(const std::string &choice)
{
    return (choice == "Warrior" || choice == "Mage" || choice == "Rogue" || choice == "warrior" || choice == "mage" || choice == "rogue");
}

void check_level_up(int &xp, int &lvl, int &nextLvl)
{
    while (xp >= nextLvl)
    {
        xp -= nextLvl;
        lvl++;
        nextLvl = lvl * 100; // ← FIXED

        std::cout << "\n================================" << std::endl;
        std::cout << " LEVEL UP! You are now Level " << lvl << "! 🎉" << std::endl;
        std::cout << "Next level requires: " << nextLvl << " XP." << std::endl;
        std::cout << "================================\n"
                  << std::endl;
    }
}

void welcome(const std::string &sep)
{
    std::cout << sep << std::endl;
    std::cout << "Welcome To Character Creation !" << std::endl;
    std::cout << sep << std::endl;
    std::cout << "1. Set Character" << std::endl;
    std::cout << "2. Play Game" << std::endl;
    std::cout << "3. Show Stats" << std::endl;
    std::cout << "4. Reset Stats " << std::endl;
    std::cout << "5. Player Game " << std::endl;
    std::cout << "6. Show Inventory" << std::endl;
    std::cout << "7. Buy Items" << std::endl;
    std::cout << "8. Calculator" << std::endl;
    std::cout << "9. Exit" << std::endl;
}

std::string get_character_name();
std::string get_character_class();

std::string sep = std::string(40, '=');
int level = 1;
int playerXp = 0;
int xpnextlevel = level * 100; // ← FIXED
std::string classType = "";
std::string name = "";

std::string get_character_name()
{
    std::string inputName;
    std::cout << "Enter character name: ";
    std::cin >> inputName;
    return inputName;
}

std::string get_character_class()
{
    std::string inputClass;
    bool valid = false;

    while (!valid)
    {
        std::cout << "Enter class (Warrior/Mage/Rogue): ";
        std::cin >> inputClass;

        if (is_valid_class(inputClass))
        {
            valid = true;
        }
        else
        {
            std::cout << "Invalid class!" << std::endl;
        }
    }

    return inputClass;
}

void print_character(const std::string &name, const std::string &classType, int level, const std::string &sep)
{
    std::cout << sep << std::endl;
    std::cout << "Player Set" << std::endl;
    std::cout << sep << std::endl;
    std::cout << "Name:  " << name << std::endl;
    std::cout << "Class: " << classType << std::endl;
    std::cout << "Level: " << level << std::endl;
}

void bye(const std::string &sep)
{
    std::cout << sep << std::endl;
    std::cout << "Byee !" << std::endl;
    std::cout << sep << std::endl;
}

void guess_game(const std::string &sep, int &xp)
{
    srand(time(0));
    int reward = 30;
    bool guessed = false;
    std::cout << sep << std::endl;
    std::cout << "Welcome To The Guess Game" << std::endl;
    std::cout << sep << std::endl;
    int secret = rand() % 10 + 1;
    int attempts = 0;
    while (attempts < 3)
    {
        int guess;
        std::cout << "Guess The Number (1-10): ";
        std::cin >> guess;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        attempts++;
        if (secret < guess)
        {
            std::cout << "Too High" << std::endl;
        }
        else if (secret > guess)
        {
            std::cout << "Too low" << std::endl;
        }
        else
        {
            guessed = true;
            std::cout << "Ggs You Won ! here is 30 XP" << std::endl;
            check_level_up(xp, level, xpnextlevel);
            break;
        }
    }
    if (guessed)
    {
        xp += reward;
    }
    else
    {
        std::cout << "You used ur 3 attempts u lost xD. The number was " << secret << std::endl;
    }
}

void play_game(const std::string &sep, int level)
{
    std::string choice;
    std::cout << sep << std::endl;
    std::cout << "Welcome To The Game !" << std::endl;
    std::cout << sep << std::endl;
    std::cout << "1. Guess Game" << std::endl;
    std::cout << "2. Dice Game" << std::endl;
    std::cout << "Choose : ";
    std::cin >> choice;

    if (choice == "1")
    {
        guess_game(sep, playerXp);
    }
    else if (choice == "2")
    {
        dice_game(playerXp, sep);
    }
}

void dice_game(int &playerXp, const std::string &sep)
{
    srand(time(0));
    bool won = false;
    int guess;
    std::cout << sep << std::endl;
    std::cout << "Welcome to The Dice Game !" << std::endl;
    std::cout << sep << std::endl;
    while (!won)
    {
        int secret = rand() % 6 + 1;
        std::cout << "Guess The Dice Number (1-6): ";
        std::cin >> guess;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        if (guess == secret)
        {
            std::cout << "Ggs You Won ! here is 50 XP" << std::endl;
            playerXp += 50;
            check_level_up(playerXp, level, xpnextlevel);
            won = true;
        }
        else
        {
            std::cout << "Wrong try again" << std::endl;
        }
    }
}

void show_stats(const std::string &name, const std::string &classType, int level, int playerXp, int xpnextlevel, const std::string &sep)
{
    bool isback = false;
    std::string choice;
    std::cout << sep << std::endl;
    std::cout << "Player Statistics : " << std::endl;
    std::cout << sep << std::endl;
    std::cout << "Name : " << name << std::endl;
    std::cout << "Class : " << classType << std::endl;
    std::cout << "Level : " << level << std::endl;
    std::cout << "XP : " << playerXp << " / " << xpnextlevel << std::endl;

    while (!isback)
    {
        std::cout << "\n1. Back.\n";
        std::cout << "Choice : ";
        std::cin >> choice;
        if (choice == "1")
        {
            isback = true;
        }
        else
        {
            std::cout << "Invalid Choice" << std::endl;
        }
    }
}
class give_xp
{
public:
    void addxp(int &playerXp, int amount)
    {
        playerXp += amount;
        std::cout << "You gained " << amount << " XP!" << std::endl;
        check_level_up(playerXp, level, xpnextlevel);
    }
};
void play_game_4_players(const std::string &sep, int level)
{
    std::cout << sep << std::endl;
    std::cout << "🎮 4-PLAYER MULTIPLAYER MODE 🎮" << std::endl;
    std::cout << sep << std::endl;

    std::string playerNames[4];
    std::string playerClasses[4];
    int playerLevels[4] = {1, 1, 1, 1};
    int playerXps[4] = {0, 0, 0, 0};
    int nextLevels[4] = {100, 100, 100, 100};

    for (int i = 0; i < 4; i++)
    {
        std::cout << "\n--- Setting up Player " << (i + 1) << " ---" << std::endl;
        std::cout << "Enter character name for Player " << (i + 1) << ": ";
        std::cin >> playerNames[i];

        std::string classChoice;
        bool validClass = false;
        while (!validClass)
        {
            std::cout << "Enter class (Warrior/Mage/Rogue): ";
            std::cin >> classChoice;
            if (is_valid_class(classChoice))
            {
                playerClasses[i] = classChoice;
                validClass = true;
            }
            else
            {
                std::cout << "Invalid class! Try again." << std::endl;
            }
        }
    }

    std::cout << "\n"
              << sep << std::endl;
    std::cout << " ALL PLAYERS SET UP! " << std::endl;
    std::cout << sep << std::endl;
    for (int i = 0; i < 4; i++)
    {
        std::cout << "Player " << (i + 1) << ": " << playerNames[i]
                  << " (" << playerClasses[i] << ") Level " << playerLevels[i] << std::endl;
    }

    bool gameRunning = true;
    while (gameRunning)
    {
        std::cout << "\n"
                  << sep << std::endl;
        std::cout << " 4-PLAYER GAME MENU " << std::endl;
        std::cout << sep << std::endl;
        std::cout << "1. Play Guess Game (All Players)" << std::endl;
        std::cout << "2. Play Dice Game (All Players)" << std::endl;
        std::cout << "3. Show All Stats" << std::endl;
        std::cout << "4. Return to Main Menu" << std::endl;
        std::cout << "Choose: ";

        std::string choice;
        std::cin >> choice;

        if (choice == "1")
        {
            // 4-player Guess Game
            srand(time(0));
            std::cout << "\n"
                      << sep << std::endl;
            std::cout << " 4-PLAYER GUESS GAME " << std::endl;
            std::cout << sep << std::endl;
            std::cout << "Each player gets 1 guess! The number is between 1-10." << std::endl;

            int secretNumber = rand() % 10 + 1;
            bool someoneWon = false;
            int winner = -1;

            for (int i = 0; i < 4; i++)
            {
                int guess;
                std::cout << "\nPlayer " << (i + 1) << " (" << playerNames[i] << "): Guess the number (1-10): ";
                std::cin >> guess;

                if (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input! Skip turn." << std::endl;
                    continue;
                }

                if (guess == secretNumber)
                {
                    someoneWon = true;
                    winner = i;
                    break;
                }
                else if (guess < secretNumber)
                {
                    std::cout << "Too low!" << std::endl;
                }
                else
                {
                    std::cout << "Too high!" << std::endl;
                }
            }

            if (someoneWon)
            {
                std::cout << "\n🎉 Player " << (winner + 1) << " (" << playerNames[winner]
                          << ") WINS! 🎉" << std::endl;
                playerXps[winner] += 50;
                std::cout << playerNames[winner] << " gains 50 XP!" << std::endl;

                // Check level up for winner
                while (playerXps[winner] >= nextLevels[winner])
                {
                    playerXps[winner] -= nextLevels[winner];
                    playerLevels[winner]++;
                    nextLevels[winner] = playerLevels[winner] * 100;
                    std::cout << "⬆️ " << playerNames[winner] << " LEVELED UP to Level "
                              << playerLevels[winner] << "! ⬆️" << std::endl;
                }
            }
            else
            {
                std::cout << "\n No one guessed correctly! The number was "
                          << secretNumber << std::endl;
            }
        }
        else if (choice == "2")
        {
            // 4-player Dice Game
            srand(time(0));
            std::cout << "\n"
                      << sep << std::endl;
            std::cout << " 4-PLAYER DICE GAME " << std::endl;
            std::cout << sep << std::endl;
            std::cout << "Each player tries to guess the dice roll (1-6)!" << std::endl;

            int secretDice = rand() % 6 + 1;
            bool someoneWon = false;
            int winner = -1;

            for (int i = 0; i < 4; i++)
            {
                int guess;
                std::cout << "\nPlayer " << (i + 1) << " (" << playerNames[i]
                          << "): Guess the dice (1-6): ";
                std::cin >> guess;

                if (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input! Skip turn." << std::endl;
                    continue;
                }

                if (guess == secretDice)
                {
                    someoneWon = true;
                    winner = i;
                    break;
                }
                else
                {
                    std::cout << "Wrong guess! The dice was " << secretDice << std::endl;
                }
            }

            if (someoneWon)
            {
                std::cout << "\n🎉 Player " << (winner + 1) << " (" << playerNames[winner]
                          << ") WINS THE DICE GAME! 🎉" << std::endl;
                playerXps[winner] += 75;
                std::cout << playerNames[winner] << " gains 75 XP!" << std::endl;

                while (playerXps[winner] >= nextLevels[winner])
                {
                    playerXps[winner] -= nextLevels[winner];
                    playerLevels[winner]++;
                    nextLevels[winner] = playerLevels[winner] * 100;
                    std::cout << "⬆️ " << playerNames[winner] << " LEVELED UP to Level "
                              << playerLevels[winner] << "! ⬆️" << std::endl;
                }
            }
            else
            {
                std::cout << "\n No one guessed correctly! The dice was "
                          << secretDice << std::endl;
            }
        }
        else if (choice == "3")
        {

            std::cout << "\n"
                      << sep << std::endl;
            std::cout << " ALL PLAYER STATISTICS " << std::endl;
            std::cout << sep << std::endl;
            for (int i = 0; i < 4; i++)
            {
                std::cout << "\n--- Player " << (i + 1) << " ---" << std::endl;
                std::cout << "Name: " << playerNames[i] << std::endl;
                std::cout << "Class: " << playerClasses[i] << std::endl;
                std::cout << "Level: " << playerLevels[i] << std::endl;
                std::cout << "XP: " << playerXps[i] << " / " << nextLevels[i] << std::endl;
            }
        }
        else if (choice == "4")
        {
            gameRunning = false;
            std::cout << "\nReturning to Main Menu..." << std::endl;
        }
        else
        {
            std::cout << "\nInvalid choice! Try again." << std::endl;
        }
    }
}
void inventory(const std::string &sep, const std::vector<std::string> &items)
{
    std::cout << sep << std::endl;
    std::cout << " Player Inventory " << std::endl;
    std::cout << sep << std::endl;

    int itemCount = items.size();

    for (int i = 0; i < itemCount; i++)
    {
        std::cout << (i + 1) << ". " << items[i] << std::endl;
    }

    bool isback = false;
    std::string choice;

    while (!isback)
    {
        std::cout << "\n1. Back to Main Menu\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == "1")
        {
            isback = true;
        }
        else
        {
            std::cout << "Invalid Choice" << std::endl;
        }
    }
}
void buy(const std::string &sep)
{
    std::cout << sep << std::endl;
    std::cout << " Buy Items " << std::endl;
    std::cout << sep << std::endl;

    std::vector<std::string> itemsForSale = {"Sword", "Shield", "Potion"};
    std::vector<int> itemPrices = {50, 30, 10};
    int itemCount = itemsForSale.size();

    for (int i = 0; i < itemCount; i++)
    {
        std::cout << (i + 1) << ". " << itemsForSale[i] << " - $" << itemPrices[i] << std::endl;
    }
    std::string choice;
    std::cout << "\nYour Money: $" << money << std::endl;
    std::cout << "Enter the number of the item you want to buy (or 1 to go back): ";
    std::cin >> choice;

    bool isback = false;
    while (!isback)
    {
        if (choice == "0")
        {
            isback = true;
        }
        else if (choice == "1" || choice == "2" || choice == "3")
        {
            int itemIndex = std::stoi(choice) - 1;
            if (itemIndex >= 0 && itemIndex < itemCount)
            {
                for (const auto &item : items)
                {
                    if (item == itemsForSale[itemIndex])
                    {
                        std::cout << "You already own a " << itemsForSale[itemIndex] << "." << std::endl;
                        return;
                    }
                }
                if (money >= itemPrices[itemIndex])
                {
                    money -= itemPrices[itemIndex];
                    std::cout << "You bought a " << itemsForSale[itemIndex] << "! Remaining Money: $" << money << std::endl;
                    items.push_back(itemsForSale[itemIndex]);
                }
                else
                {
                    std::cout << "Not enough money to buy " << itemsForSale[itemIndex] << "." << std::endl;
                }
            }
            else
            {
                std::cout << "Invalid item selection." << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid choice." << std::endl;
        }
        std::cout << "\nYour Money: $" << money << std::endl;
        std::cout << "Enter the number of the item you want to buy (or 0 to go back): ";
        std::cin >> choice;
    }
}
void calculator(const std::string &sep)
{
    std::cout << sep << std::endl;
    std::cout << " Calculator " << std::endl;
    std::cout << sep << std::endl;

    double num1, num2;
    char operation;

    std::cout << "Enter first number: ";
    std::cin >> num1;
    std::cout << "Enter operation (+, -, *, /): ";
    std::cin >> operation;
    std::cout << "Enter second number: ";
    std::cin >> num2;

    double result;
    switch (operation)
    {
    case '+':
        result = num1 + num2;
        break;
    case '-':
        result = num1 - num2;
        break;
    case '*':
        result = num1 * num2;
        break;
    case '/':
        if (num2 != 0)
            result = num1 / num2;
        else
        {
            std::cout << "Error: Division by zero!" << std::endl;
            return;
        }
        break;
    default:
        std::cout << "Invalid operation!" << std::endl;
        return;
    }

    std::cout << "Result: " << result << std::endl;

    bool isback = false;
    std::string choice;

    while (!isback)
    {
        std::cout << "\n0. Back to Main Menu";
        std::cout << "\n1. Use Calculator Again\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == "0")
        {
            isback = true;
        }
        else if (choice == "1")
        {
            calculator(sep);
        }
        else
        {
            std::cout << "Invalid Choice" << std::endl;
        }
        {
            std::cout << "Invalid Choice" << std::endl;
        }
    }
}
void main_menu()
{
    std::string choice;
    bool ischoiceValid = false;
    bool playerset = false;

    while (!ischoiceValid)
    {
        welcome(sep);
        std::cout << "Choose : ";
        std::cin >> choice;

        if (choice == "1")
        {
            if (!playerset)
            {
                name = get_character_name();
                classType = get_character_class();
                print_character(name, classType, level, sep);
                playerset = true;
            }
            else
            {
                std::cout << "\nCharacter already created!\n"
                          << std::endl;
            }
        }
        else if (choice == "2")
        {
            play_game(sep, level);
        }
        else if (choice == "3")
        {
            show_stats(name, classType, level, playerXp, xpnextlevel, sep);
        }
        else if (choice == "cheat_code")
        {

            for (int i = 0; i < 10000; ++i)
            {
                give_xp xp_giver;
                xp_giver.addxp(playerXp, 1000);
            }
        }
        else if (choice == "4")
        {
            level = 1;
            playerXp = 0;
            xpnextlevel = level * 100;
            classType = "";
            name = "";
            playerset = false;
            std::cout << "\nStats have been reset!\n"
                      << std::endl;
        }
        else if (choice == "5")
        {
            play_game_4_players(sep, level);
        }
        else if (choice == "6")
        {
            inventory(sep, items);
        }
        else if (choice == "7")
        {
            buy(sep);
        }
        else if (choice == "8")
        {
            calculator(sep);
        }
        else if (choice == "9")
        {
            bye(sep);
            ischoiceValid = true;
        }
        else
        {
            std::cout << "\nInvalid choice! Try again.\n"
                      << std::endl;
        }
    }
}

int main()
{
    main_menu();
    return 0;
}
