#if 1
#include <iostream>
using namespace std;


struct ChocolateBoiler {
    static ChocolateBoiler* getInstance() {
        if (instance == nullptr) {
            instance = new ChocolateBoiler();
        }
        return instance;
    }
    void fill() {
        if (isEmpty()) {
            empty = false;
            boiled = false;
            // fill the boiler with a milk/chocolate mixture
            cout << "filled" << endl;
        }
    }
    void drain() {
        if (!isEmpty() && isBoiled()) {
            empty = true;
            // drain the boiled milk and chocolate
            cout << "drained" << endl;
        }
    }
    void boil() {
        if (!isEmpty() && !isBoiled()) {
            boiled = true;
            // bring the contents to a boil
            cout << "boiled" << endl;
        }
    }
    bool isEmpty() { return empty; }
    bool isBoiled() { return boiled; }
private:
    static ChocolateBoiler* instance;
    bool empty, boiled;
    
    ChocolateBoiler() { empty = true; boiled = false; }
    ~ChocolateBoiler() = default;
    ChocolateBoiler(const ChocolateBoiler&) = delete;
    ChocolateBoiler& operator=(const ChocolateBoiler&) = delete;
};

// Initialize the static member
ChocolateBoiler* ChocolateBoiler::instance = nullptr;

int main()
{
    ChocolateBoiler* boiler1 = ChocolateBoiler::getInstance();
    boiler1->fill();
    boiler1->boil();
    boiler1->drain();

    ChocolateBoiler* boiler2 = ChocolateBoiler::getInstance();
    boiler2->fill();
    boiler2->boil();
    boiler2->drain();

    if (boiler1 == boiler2) { cout << "same" << endl; }
    else { cout << "different" << endl; }

    return 0;
}
#endif