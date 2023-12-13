#include "inventory.h"
#include <iostream>
#include <iomanip>
#include <utility>
#include <vector>
#include <fstream>

[[maybe_unused]] void displayAllProducts(const Inventory inventory[], int size) {
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

void Inventory::setUnits(std::string units){
    itemUnits = units;
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

std::string Inventory::toString() const {
    return this->itemName + ";"
           + std::to_string(this->itemPrice) + ";"
           + std::to_string(this->quantity) + ";";
}

std::string Inventory::getUnits() const {
    return this->itemUnits;
}

void addProduct(std::vector<Inventory> &inventory) {
    Inventory product;
    std::string input;

    std::cout << "Введіть дані для нового товару:" << std::endl;
    std::cout << "Назва товару: ";

    std::getline(std::cin, input);
    const std::string name = input;
    product.setItemName(name);

    std::cout << "Ціна товару: ";

    std::getline(std::cin, input);
    const float price = std::stof(input);
    product.setItemPrice(price);

    std::cout << "Кількість: ";

    std::getline(std::cin, input);
    const int qty = std::stoi(input);
    product.setQuantity(qty);

    std::cout << "Одиниці вимірювання: ";

    std::getline(std::cin, input);
    const std::string units = input;
    product.setUnits(units);

    inventory.push_back(product);
    std::cout << "Товар додано!" << std::endl;
}

// Функция проведения инвентаризации и вывода выводов
void performInventory(const std::vector<Inventory> &inventory) {
    float totalInventoryValue = 0;
    std::vector<std::string> conclusions;

    std::cout << "Інвентаризація:" << std::endl;
    for (int i = 0; i < inventory.size(); ++i) {
        if (inventory[i].isFilled()) {
            inventory[i].displayInfo();
            totalInventoryValue += inventory[i].calculateTotalCost(inventory[i].getQuantity());

            // Добавление выводов в вектор
            conclusions.push_back("Товар: " + inventory[i].getItemName() +
                                  ", Кількість: " + std::to_string(inventory[i].getQuantity()) +
                                  (inventory[i].getUnits()) +
                                  ", Загальна вартість: $" +
                                  std::to_string(inventory[i].calculateTotalCost(inventory[i].getQuantity())));
        }
    }

    std::cout << "Сумарна вартість інвентарю: $" << std::fixed << std::setprecision(2) << totalInventoryValue
              << std::endl;

    // Вывод выводов
    std::cout << "Висновки:" << std::endl;
    for (const auto &conclusion: conclusions) {
        std::cout << conclusion << std::endl;
    }
}

std::vector<Inventory> loadInventory() {
    std::ifstream fin(filename);
    std::vector<Inventory> inventory;
    if (!fin.is_open()) {
        saveInventory(inventory);
        return inventory;
    }
    std::string input;
    std::getline(fin, input, ' ');
    std::getline(fin, input);
    int size = std::stoi(input);
    for (int i = 0; i < size; i++) {
        Inventory product;

        std::getline(fin, input, ';');
        std::string name = input;
        product.setItemName(name);

        std::getline(fin, input, ';');
        float itemPrice = std::stof(input);
        product.setItemPrice(itemPrice);

        std::getline(fin, input, ';');
        int quantity = std::stoi(input);
        product.setQuantity(quantity);

        inventory.push_back(product);
        std::getline(fin, input);
    }
    return inventory;
}

void saveInventory(const std::vector<Inventory> &inventory) {
    std::ofstream fout(filename);
    std::string line;
    fout << "inventory: " << inventory.size() << std::endl;
    for (const auto &i: inventory) {
        fout << i.toString() << std::endl;
    }
    fout.close();
}
