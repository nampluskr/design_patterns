#if 0
#include <iostream>
using namespace std;

// Not Singleton pattern
struct ChocolateBoiler {
    ChocolateBoiler() { empty = true; boiled = false; }

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
            // drain the boiled milk and chocolate
            empty = true;
            cout << "drained" << endl;
        }
    }
    void boil() {
        if (!isEmpty() && !isBoiled()) {
            // bring the contents to a boil
            boiled = true;
            cout << "boiled" << endl;
        }
    }
    bool isEmpty() { return empty; }
    bool isBoiled() { return boiled; }
private:
    bool empty, boiled;
};

int main()
{
    ChocolateBoiler* boiler1 = new ChocolateBoiler();
    boiler1->fill();
    boiler1->boil();
    boiler1->drain();

    ChocolateBoiler* boiler2 = new ChocolateBoiler();
    boiler2->fill();
    boiler2->boil();
    boiler2->drain();

    if (boiler1 == boiler2) { cout << "same" << endl; }
    else { cout << "different" << endl; }

    delete boiler1;
    delete boiler2;
    return 0;
}
#endif