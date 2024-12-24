# Aggregation vs. Composition

- 객체지향 프로그래밍(OOP)에서 Aggregation과 Composition은 둘 다 클래스 간의 관계를 나타내지만, 중요한 차이가 있습니다. 이 차이는 객체의 생명 주기와 관계 깊습니다.
- Aggregation과 Composition의 차이를 이해하고, 올바르게 사용하는 것은 객체지향 설계에서 중요한 부분입니다.

## Aggregation (집합 관계)

- Aggregation은 "has-a" 관계를 나타내며, 부분과 전체 간의 관계를 표현합니다.
- Aggregation에서는 부분 객체는 독립적인 생명 주기를 갖습니다. 즉, 전체 객체가 삭제되더라도 부분 객체는 존재할 수 있습니다.

### 예제

- 설명: `Engine` 객체는 `Car` 객체에 포함될 수 있지만, `Car` 객체가 삭제되어도 `Engine` 객체는 독립적으로 존재합니다.

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Engine {
public:
    Engine(string type) : type(type) {}
    string getType() { return type; }
private:
    string type;
};

class Car {
public:
    Car(string model) : model(model) {}
    void addEngine(Engine* engine) {
        engines.push_back(engine);
    }
    void showEngines() {
        cout << "Engines in " << model << ":\n";
        for (auto engine : engines)
            cout << " - " << engine->getType() << endl;
    }
private:
    string model;
    vector<Engine*> engines;
};

int main() {
    Engine* engine1 = new Engine("V8");
    Engine* engine2 = new Engine("V6");

    Car car("Ford Mustang");
    car.addEngine(engine1);
    car.addEngine(engine2);

    car.showEngines();

    delete engine1;
    delete engine2;

    return 0;
}
```

## Composition (합성 관계)

- Composition은 "is-part-of" 관계를 나타내며, 강한 소유 관계를 표현합니다.
- Composition에서는 부분 객체는 전체 객체의 생명 주기에 의존합니다. 즉, 전체 객체가 삭제되면 부분 객체도 함께 삭제됩니다.

### 예제

- 설명: `Engine` 객체는 `Car` 객체의 생명 주기에 완전히 의존합니다. `Car` 객체가 삭제되면, `Engine` 객체도 함께 삭제됩니다.

```cpp
#include <iostream>
#include <string>
using namespace std;

class Engine {
public:
    Engine(string type) : type(type) {}
    string getType() { return type; }
private:
    string type;
};

class Car {
public:
    Car(string model, string engineType) : model(model) {
        engine = new Engine(engineType);
    }
    ~Car() { delete engine; }
    void showEngine() {
        cout << "Engine in " << model << ":\n";
        cout << " - " << engine->getType() << endl;
    }
private:
    string model;
    Engine* engine;
};

int main() {
    Car car("Ford Mustang", "V8");
    car.showEngine();

    // No need to delete the engine explicitly
    return 0;
}
```