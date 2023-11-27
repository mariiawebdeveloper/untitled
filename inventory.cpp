#include "inventory.h"
#include <iostream>
#include <iomanip>
#include <vector>

void displayAllProducts(const Inventory inventory[], int size) {
    for (int i = 0; i < size; ++i) {
        inventory[i].displayInfo();
    }
}

int Inventory::nextItemNumber = 1;

// Определения методов класса Inventory
void Inventory::setItemName(std::string name) {
    itemName = std::move(name);
}

void Inventory::setItemPrice(float price) {
    itemPrice = price;
}

void Inventory::setQuantity(int qty) {
    quantity = qty;
}

bool Inventory::isFilled() const {
    return (itemNumber != 0 || !itemName.empty() || itemPrice != 0.0 || quantity != 0);
}

int Inventory::getQuantity() const {
    return quantity;
}

float Inventory::getItemPrice() const {
    return itemPrice;
}

std::string Inventory::getItemName() const {
    return itemName;
}

void Inventory::displayInfo() const {
    std::cout << "Номер товару: " << itemNumber << std::endl;
    std::cout << "Назва товару: " << itemName << std::endl;
    std::cout << "Ціна товару: " << std::fixed << std::setprecision(2) << itemPrice << std::endl;
    std::cout << "Кількість: " << quantity << std::endl;
    std::cout << "=====================" << std::endl;
}

float Inventory::calculateTotalCost(int quantity) const {
    return itemPrice * quantity;
}

void Inventory::depreciate(float depreciationPercentage) {
    itemPrice -= itemPrice * (depreciationPercentage / 100);
}

void Inventory::updateQuantity(int purchasedQuantity) {
    quantity -= purchasedQuantity;
}
void addProduct(Inventory &product) {
    std::string name;
    float price;
    int qty;

    std::cout << "Введіть дані для нового товару:" << std::endl;
    std::cout << "Назва товару: ";
//    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);
    product.setItemName(name);

    std::cout << "Ціна товару: ";
    std::cin >> price;
    product.setItemPrice(price);

    std::cout << "Кількість: ";
    std::cin >> qty;
    product.setQuantity(qty);

    std::cout << "Товар додано!" << std::endl;
}

// Функция проведения инвентаризации и вывода выводов
void performInventory(const Inventory inventory[], int size) {
    float totalInventoryValue = 0;
    std::vector<std::string> conclusions;

    std::cout << "Інвентаризація:" << std::endl;
    for (int i = 0; i < size; ++i) {
        if (inventory[i].isFilled()) {
            inventory[i].displayInfo();
            totalInventoryValue += inventory[i].calculateTotalCost(inventory[i].getQuantity());

            // Добавление выводов в вектор
            conclusions.push_back("Товар: " + inventory[i].getItemName() +
                                  ", Кількість: " + std::to_string(inventory[i].getQuantity()) +
                                  ", Загальна вартість: $" +
                                  std::to_string(inventory[i].calculateTotalCost(inventory[i].getQuantity())));
        }
    }

    std::cout << "Сумарна вартість інвентарю: $" << std::fixed << std::setprecision(2) << totalInventoryValue
              << std::endl;

    // Вывод выводов
    std::cout << "Висновки:" << std::endl;
    for (const std::string &conclusion: conclusions) {
        std::cout << conclusion << std::endl;
    }

    // Очистка буфера вводу перед зчитуванням символу backToMenu
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    char backToMenu;
    std::cout << "Натисніть 'q' для повернення в меню: ";
    std::cin >> backToMenu;
    if (backToMenu == 'q' || backToMenu == 'Q') {
        return; // Повернення без продовження виконання циклу в main
    }
}