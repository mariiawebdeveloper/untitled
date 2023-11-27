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

// ����������� ������� ������ Inventory
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
    std::cout << "����� ������: " << itemNumber << std::endl;
    std::cout << "����� ������: " << itemName << std::endl;
    std::cout << "ֳ�� ������: " << std::fixed << std::setprecision(2) << itemPrice << std::endl;
    std::cout << "ʳ������: " << quantity << std::endl;
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

    std::cout << "������ ��� ��� ������ ������:" << std::endl;
    std::cout << "����� ������: ";
//    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);
    product.setItemName(name);

    std::cout << "ֳ�� ������: ";
    std::cin >> price;
    product.setItemPrice(price);

    std::cout << "ʳ������: ";
    std::cin >> qty;
    product.setQuantity(qty);

    std::cout << "����� ������!" << std::endl;
}

// ������� ���������� �������������� � ������ �������
void performInventory(const Inventory inventory[], int size) {
    float totalInventoryValue = 0;
    std::vector<std::string> conclusions;

    std::cout << "��������������:" << std::endl;
    for (int i = 0; i < size; ++i) {
        if (inventory[i].isFilled()) {
            inventory[i].displayInfo();
            totalInventoryValue += inventory[i].calculateTotalCost(inventory[i].getQuantity());

            // ���������� ������� � ������
            conclusions.push_back("�����: " + inventory[i].getItemName() +
                                  ", ʳ������: " + std::to_string(inventory[i].getQuantity()) +
                                  ", �������� �������: $" +
                                  std::to_string(inventory[i].calculateTotalCost(inventory[i].getQuantity())));
        }
    }

    std::cout << "������� ������� ���������: $" << std::fixed << std::setprecision(2) << totalInventoryValue
              << std::endl;

    // ����� �������
    std::cout << "��������:" << std::endl;
    for (const std::string &conclusion: conclusions) {
        std::cout << conclusion << std::endl;
    }

    // ������� ������ ����� ����� ����������� ������� backToMenu
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    char backToMenu;
    std::cout << "�������� 'q' ��� ���������� � ����: ";
    std::cin >> backToMenu;
    if (backToMenu == 'q' || backToMenu == 'Q') {
        return; // ���������� ��� ����������� ��������� ����� � main
    }
}