#include <string>
#include "inventory.h"


int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    std::vector<Inventory> inventory = loadInventory();
    std::string choice;

    do {
        std::cout << "=== Меню ===" << std::endl;
        std::cout << "1. Реєстрація прибуття товару" << std::endl;
        std::cout << "2. Обробка покупки" << std::endl;
        std::cout << "3. Амортизація" << std::endl;
        std::cout << "4. Інвентаризація" << std::endl;
        std::cout << "5. Списання" << std::endl;
        std::cout << "6. Вихід" << std::endl;
        std::cout << "Оберіть опцію: ";
        std::getline(std::cin, choice);
        std::string input;

        switch (std::stoi(choice)) {
            case 1:
                addProduct(inventory);
                break;
            case 2: {
                int itemToPurchase;
                int quantityToPurchase;

                std::cout << "Введіть номер товару для покупки: ";
                std::getline(std::cin, input);
                itemToPurchase = std::stoi(input);

                if (itemToPurchase >= 1 && itemToPurchase <= inventory.size()) {
                    std::cout << "Введіть кількість для покупки: ";
                    std::getline(std::cin, input);
                    quantityToPurchase = std::stoi(input);

                    if (quantityToPurchase > 0 && quantityToPurchase <= inventory[itemToPurchase - 1].getQuantity()) {
                        float totalCost = inventory[itemToPurchase - 1].calculateTotalCost(quantityToPurchase);
                        std::cout << "Загальна вартість: $" << std::fixed << std::setprecision(2) << totalCost
                                  << std::endl;

                        inventory[itemToPurchase - 1].updateQuantity(quantityToPurchase);
                        std::cout << "Покупка успішна!" << std::endl;
                    } else {
                        std::cout << "Неправильна кількість. Будь ласка, введіть правильну кількість." << std::endl;
                    }
                } else {
                    std::cout << "Неправильний номер товару. Будь ласка, введіть правильний номер товару." << std::endl;
                }
                break;
            }
            case 3: {
                int itemToDepreciate;
                float depreciationPercentage;
                std::cout << "Введіть номер товару для амортизації: ";
                std::getline(std::cin, input);
                itemToDepreciate = std::stoi(input);

                if (itemToDepreciate >= 1 && itemToDepreciate <= inventory.size()) {
                    std::cout << "Введіть відсоток амортизації: ";
                    std::getline(std::cin, input);
                    depreciationPercentage = std::stof(input);

                    inventory[itemToDepreciate - 1].depreciate(depreciationPercentage);
                    std::cout << "Амортизація успішна!" << std::endl;
                } else {
                    std::cout << "Неправильний номер товару. Будь ласка, введіть правильний номер товару." << std::endl;
                }
                break;
            }
            case 4: {
                performInventory(inventory);
                std::string backToMenu;
                std::cout << "Натисніть 'q' для повернення в меню: ";
                std::getline(std::cin, backToMenu);
                if (backToMenu[0] == 'q' || backToMenu[0] == 'Q') {
                    continue;
                }
                break;
            }
            case 5:
                removeProduct(inventory);


            case 6:
                saveInventory(inventory);
                std::cout << "Дякую за використання програми. До побачення!" << std::endl;
                break;
            default:
                std::cout << "Неправильний вибір. Будь ласка, спробуйте ще раз." << std::endl;
        }
    } while (choice != "6");

    getchar();
    return 0;
}
