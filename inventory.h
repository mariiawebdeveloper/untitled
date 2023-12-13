#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <iomanip>
#include <utility>
#include <vector>
#include <windows.h>
#include <limits>
#include <string>

const std::string filename = "inventory.txt";

class Inventory {
private:
    static int nextItemNumber;
    int itemNumber;
    std::string itemName;
    float itemPrice{};
    int quantity{};
    std::string itemUnits;

public:
    Inventory() : itemNumber(nextItemNumber++), itemPrice(0.0), quantity(0) {}

    void setItemName(std::string name);

    void setItemPrice(float price);

    void setQuantity(int qty);

    [[nodiscard]] bool isFilled() const;

    [[nodiscard]] int getQuantity() const;

    [[nodiscard]] float getItemPrice() const;

    [[nodiscard]] std::string getItemName() const;

    void displayInfo() const;

    [[nodiscard]] float calculateTotalCost(int quantity) const;

    void depreciate(float depreciationPercentage);

    void updateQuantity(int purchasedQuantity);

    [[nodiscard]] std::string toString() const;

    void setUnits(std::string units);

    [[nodiscard]] std::string getUnits() const;
};

// Declare the function without providing the definition
[[maybe_unused]] void displayAllProducts(const Inventory inventory[], int size);

void addProduct(std::vector<Inventory> &inventory);

void performInventory(const std::vector<Inventory> &inventory);

std::vector<Inventory> loadInventory();

void saveInventory(const std::vector<Inventory> &inventory);

#endif // INVENTORY_H