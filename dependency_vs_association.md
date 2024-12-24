# Dependency vs. Association

### 요약

- Dependency: 클래스가 다른 클래스를 일시적으로 사용할 때 나타나는 관계입니다.
- Association: 클래스가 다른 클래스의 객체를 멤버로 가지며, 지속적인 상호작용을 나타내는 관계입니다.

## Dependency (의존 관계)

- Dependency는 "uses-a" 관계를 나타내며, 한 클래스가 다른 클래스를 일시적으로 사용하는 관계입니다.
- Dependency에서는 클래스가 메서드를 통해 다른 클래스의 객체를 사용하지만, 두 클래스 간의 강한  연관성은 없습니다.

### 예제

- 설명: `Car` 클래스는 `inspectEngine` 메서드에서 `Engine` 객체를 사용합니다. `Car와` `Engine`은 의존 관계에 있으며, `Car`는 `Engine`을 일시적으로 사용합니다.

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
    void inspectEngine(Engine* engine) {
        // Car "uses" an Engine to perform an operation
        cout << "Inspecting engine: " << engine->getType() << endl;
    }
};

int main() {
    Engine engine("V8");
    Car car;
    car.inspectEngine(&engine);

    return 0;
}
```

## Association (연관 관계)

- Association은 "has-a" 관계를 나타내며, 한 클래스가 다른 클래스의 객체를 멤버로 가지는 관계입니다.
- Association에서는 클래스 간의 상호작용이 더 강하게 나타나며, 객체 간의 관계가 지속됩니다.

### 예제

- 설명: `Car` 클래스는 `Engine` 객체를 멤버로 가지며, 이는 `Car`와 `Engine` 간의 연관 관계를 나타냅니다. `Car` 객체는 `Engine` 객체를 지속적으로 참조합니다.

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
    Car(Engine* engine) : engine(engine) {}
    void showEngine() {
        cout << "This car has an engine: " << engine->getType() << endl;
    }
private:
    Engine* engine;
};

int main() {
    Engine engine("V8");
    Car car(&engine);
    car.showEngine();

    return 0;
}
```