# Association vs. Aggregation

### 요약

- Association: 두 객체 간의 연결 관계로, 객체들은 독립적인 생명 주기를 가집니다.
  - 예: `Car`와 `Engine`의 참조 관계.
- Aggregation: 부분 객체가 전체 객체에 포함되지만, 독립적인 생명 주기를 유지합니다.
  - 예: `Car`가 여러 개의 `Engine` 객체를 소유하는 관계.

## Association (연관 관계)

- 의미: 두 클래스 간의 연결 관계를 나타내며, `Car` 클래스가 `Engine` 클래스의 객체를 참조하는 형태입니다. 이 관계는 독립적이며, 두 객체는 별도의 생명 주기를 가집니다.
- 강도: 약한 관계로, 객체 간의 독립성이 유지됩니다.

### 예제

- 설명: `Car`는 `Engine` 객체를 참조할 수 있지만, `Car` 객체가 삭제되더라도 `Engine` 객체는 독립적으로 존재할 수 있습니다.

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
    void setEngine(Engine* engine) { this->engine = engine; }
    void showEngine() {
        if (engine)
            cout << "This car has an engine: " << engine->getType() << endl;
        else
            cout << "This car has no engine." << endl;
    }
private:
    Engine* engine = nullptr;
};

int main() {
    Engine engine("V8");
    Car car;
    car.setEngine(&engine);
    car.showEngine();

    return 0;
}
```

## Aggregation (집합 관계)

- 의미: 전체와 부분의 관계를 나타내며, `Car` 클래스가 `Engine` 클래스의 객체를 소유하지만, 부분 객체는 독립적인 생명 주기를 가집니다. 즉, `Car` 객체가 삭제되더라도 `Engine` 객체는 다른 곳에서 사용할 수 있습니다.
- 강도: 약한 소유 관계로, 부분 객체는 독립적인 생명 주기를 유지합니다.

### 예제

- 설명: `Car`는 여러 개의 `Engine` 객체를 소유할 수 있지만, `Car` 객체가 삭제되더라도 `Engine` 객체는 독립적으로 존재할 수 있습니다.

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
    Engine engine1("V8");
    Engine engine2("V6");

    Car car("Ford Mustang");
    car.addEngine(&engine1);
    car.addEngine(&engine2);

    car.showEngines();

    return 0;
}
```