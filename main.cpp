#pragma optimize("", on)
#include "inventory.h"




int main() {
    SetConsoleOutputCP(CP_UTF8);
    const int inventorySize = 5;
    Inventory inventory[inventorySize];
    std::string choice;

    do {
        std::cout << "=== Меню ===" << std::endl;
        std::cout << "1. Реєстрація прибуття товару" << std::endl;
        std::cout << "2. Обробка покупки" << std::endl;
        std::cout << "3. Амортизація" << std::endl;
        std::cout << "4. Інвентаризація" << std::endl;
        std::cout << "5. Вихід" << std::endl;
        std::cout << "Оберіть опцію: ";
        std::getline(std::cin, choice);


        switch (atoi(choice.c_str())) {
            case 1:
                for (int i = 0; i < inventorySize; ++i) {
                    if (!inventory[i].getQuantity() && inventory[i].getItemName().empty() &&
                        inventory[i].getItemPrice() == 0.0 && inventory[i].getQuantity() == 0) {
                        addProduct(&inventory[i]);
                        break;
                    }
                }
                break;
            case 2: {
                int itemToPurchase;
                int quantityToPurchase;
                std::cout << "Введіть номер товару для покупки: ";
                std::cin >> itemToPurchase;

                if (itemToPurchase >= 1 && itemToPurchase <= inventorySize) {
                    std::cout << "Введіть кількість для покупки: ";
                    std::cin >> quantityToPurchase;

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
                std::cin >> itemToDepreciate;

                if (itemToDepreciate >= 1 && itemToDepreciate <= inventorySize) {
                    std::cout << "Введіть відсоток амортизації: ";
                    std::cin >> depreciationPercentage;

                    inventory[itemToDepreciate - 1].depreciate(depreciationPercentage);
                    std::cout << "Амортизація успішна!" << std::endl;
                } else {
                    std::cout << "Неправильний номер товару. Будь ласка, введіть правильний номер товару." << std::endl;
                }
                break;
            }
            case 4:
                performInventory(inventory, inventorySize);
                char backToMenu;
                std::cout << "Натисніть 'q' для повернення в меню: ";
                std::cin >> backToMenu;
                if (backToMenu == 'q' || backToMenu == 'Q') {
                    continue;
                }
                break;
            case 5:
                std::cout << "Дякую за використання програми. До побачення!" << std::endl;
                break;
            default:
                std::cout << "Неправильний вибір. Будь ласка, спробуйте ще раз." << std::endl;
        }
    } while (choice != "5");

    return 0;
}
