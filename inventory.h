#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <iomanip>
#include <utility>
#include <vector>
#include <windows.h>
#include <limits>

class Inventory {
private:
    static int nextItemNumber;
    int itemNumber;
    std::string itemName;
    float itemPrice{};
    int quantity{};

public:
    Inventory() : itemNumber(nextItemNumber++), itemPrice(0.0), quantity(0) {}

    void setItemName(std::string name);

    void setItemPrice(float price);

    void setQuantity(int qty);

    bool isFilled() const;

    int getQuantity() const;

    float getItemPrice() const;

    std::string getItemName() const;

    void displayInfo() const;

    float calculateTotalCost(int quantity) const;

    void depreciate(float depreciationPercentage);

    void updateQuantity(int purchasedQuantity);
};

// Declare the function without providing the definition
void displayAllProducts(const Inventory inventory[], int size);

void addProduct(Inventory *product);

void performInventory(const Inventory inventory[], int size);

#endif // INVENTORY_H