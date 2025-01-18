#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct MenuItem {
    MenuItem(const string& name, const string& description,
            bool vegetarian, double price) {
        this->name = name;
        this->description = description;
        this->vegetarian = vegetarian;
        this->price = price;
    }
    string getName() { return name; }
    string getDescription() { return description; }
    bool isVegetarian() { return vegetarian; }
    double getPrice() { return price; }
private:
    string name;
    string description;
    bool vegetarian;
    double price;
};

struct PancakeHouseMenu {
    PancakeHouseMenu() {
        addItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs and toast", true, 2.99);
        addItem("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99);
        addItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
        addItem("Waffles", "Waffles with your choice of blueberries or strawberries", true, 3.59);
    }
    void addItem(const string& name, const string& description, bool vegetarian, double price) {
        MenuItem menuItem{name, description, vegetarian, price};
        menuItems.push_back(menuItem);
    }
    vector<MenuItem> getMenuItems() { return menuItems; }
    // other menu methods here
private:
    vector<MenuItem> menuItems;
};

struct DinerMenu {
    // DinerMenu() = default;
    DinerMenu() {
        addItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
        // addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
        // addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
        // addItem("Hotdog", "A hot dog, with sauerkraut, relish, onions, topped with cheese", false, 3.05);
        // a couple of other Diner Menu items added here
    }
    void addItem(const string& name, const string& description, bool vegetarian, double price) {
        MenuItem menuItem{name, description, vegetarian, price};
        if (numberOfItems >= MAX_ITEMS) {
            cout << "Sorry, menu is full! Can't add item to menu\n";
        } else {
            menuItems[numberOfItems++] = menuItem;
        }
    }
//     MenuItem* getMenuItems() { return menuItems; }
//     // other menu methods here
private:
    static const int MAX_ITEMS = 6;
    MenuItem menuItems[MAX_ITEMS];
    int numberOfItems = 0;
};


int main() {


    return 0;
}