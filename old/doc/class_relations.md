# Class Relations

다섯 가지 관계(의존, 연관, 집합, 합성, 상속)를 C++ 코드로 구현할 때의 구체적이고 명확한 차이점을 자세히 설명드리겠습니다.
각 관계를 나타내는 코드 패턴과 주의해야 할 점을 중점적으로 살펴보겠습니다.

## 1. 의존 (Dependency)

- 코드 패턴: 함수나 메서드의 매개변수, 지역 변수, 또는 반환 타입으로 다른 클래스를 사용하는 형태. 클래스 멤버 변수로 포함하지 않음.
구현 방법:
  - 함수 매개변수: `void myFunc(OtherClass& obj);` 또는 `void myFunc(OtherClass* obj);`
  - 지역 변수: `OtherClass obj;` 또는 `OtherClass* obj = new OtherClass();` (동적 할당 시에는 해제 필요)
- 핵심: 사용하는 클래스의 변경이 의존하는 클래스에 영향을 줄 수 있지만, 소유 관계는 아님.
- 예시 (이전 예제 재활용):

```cpp
class Car; // 전방 선언

class Road {
public:
    void drive(Car& car) { // Car 객체를 참조로 받음 (의존)
        // ...
    }
};
```

## 2. 연관 (Association)

- 코드 패턴: 한 클래스가 다른 클래스의 포인터 또는 참조를 멤버 변수로 가짐. 두 클래스의 생명주기는 독립적.
- 구현 방법:
  - 포인터 멤버: `OtherClass* obj_;` (동적 할당 시에는 생성/소멸 관리 필요)
  - 참조 멤버: `OtherClass& obj_;` (객체 생성 시 초기화 필수)
- 핵심: 객체 간의 연결은 존재하지만, 소유 관계는 아님. 객체의 생성과 소멸을 분리하여 관리해야 함.
- 예시 (이전 예제 재활용):

```cpp
class Mechanic; // 전방 선언

class Car {
private:
    Mechanic* mechanic_; // 연관
};
```


## 3. 집합 (Aggregation)

- 코드 패턴: 한 클래스가 다른 클래스의 포인터 또는 참조를 멤버 변수로 가지며, 부분 객체의 생명주기가 전체 객체와 독립적.
- 구현 방법: 연관과 유사하게 포인터 또는 참조 멤버를 사용. 주로 포인터를 사용하여 부분 객체의 소멸을 전체 객체가 책임지지 않도록 구현.
  - 핵심: 부분 객체를 외부에서 생성하여 전체 객체에 전달하는 방식이 일반적. 전체 객체가 소멸되더라도 부분 객체는 남아 있을 수 있음.
- 예시 (이전 예제 재활용):

```cpp
class Engine { /* ... */ };

class Car {
private:
    Engine* engine_; // 집합
};

int main() {
  Engine* engine = new Engine(200);
  Car myCar("모델", engine); // 외부에서 생성된 엔진을 전달
  delete engine; // 자동차가 사라져도 엔진은 남아있을 수 있음(의도적으로 메모리 누수 발생시킨 예제)
}
```

## 4. 합성 (Composition)

- 코드 패턴: 한 클래스가 다른 클래스의 객체를 멤버 변수로 직접 소유. 부분 객체의 생명주기는 전체 객체에 완전히 종속.
- 구현 방법: 객체를 값으로 멤버 변수로 선언: `OtherClass obj_;`
- 핵심: 전체 객체가 생성될 때 부분 객체도 함께 생성되고, 전체 객체가 소멸될 때 부분 객체도 함께 소멸. 복사 생성자와 복사 대입 연산자를 주의해서 구현해야 함 (깊은 복사 또는 복사 금지).
- 예시 (이전 예제 재활용):

```cpp
class Chassis { /* ... */ };

class Car {
private:
    Chassis chassis_; // 합성
};
```
## 5. 상속 (Inheritance)

- 코드 패턴: : 기호를 사용하여 상속을 명시: class DerivedClass : public BaseClass { ... };
- 구현 방법:
  - public 상속: 부모 클래스의 모든 public 및 protected 멤버를 상속.
  - protected 상속: 부모 클래스의 public 및 protected 멤버를 protected 멤버로 상속.
  - private 상속: 부모 클래스의 모든 멤버를 private 멤버로 상속. (일반적으로 잘 사용되지 않음)
- 핵심: "is-a" 관계. 자식 클래스는 부모 클래스의 모든 기능을 가지며, 추가적인 기능을 확장하거나 기존 기능을 재정의(override)할 수 있음.
- 예시 (이전 예제 재활용):

```cpp
class Car {
public:
    virtual void printInfo() const { /* ... */ } // 가상 함수
};

class Sedan : public Car {
public:
    void printInfo() const override { /* ... */ } // 재정의
};
```

## 연관(Association) vs. 집합(Aggregation)

연관(Association)과 집합(Aggregation)은 코드 구현 관점에서 매우 유사하게 나타나는 경우가 많습니다. 특히 C++에서는 포인터 또는 참조를 사용하여 두 관계를 모두 표현할 수 있기 때문에 더욱 그렇습니다. 하지만, 코드 의도 와 객체의 생명주기 관리 에서 명확한 차이가 있습니다. 이 차이점을 중심으로 코드 관점에서 어떻게 구분할 수 있는지 자세히 설명드리겠습니다.

### 핵심 차이: 소유권과 생명주기

- 연관: 두 객체는 서로 연결되어 있지만, 어느 한쪽이 다른 쪽을 소유하지 않습니다. 즉, 각 객체의 생명주기는 완전히 독립적입니다.
- 집합: "부분-전체" 관계를 나타내지만, 부분 객체는 전체 객체와 독립적인 생명주기를 가집니다. 전체 객체가 소멸되더라도 부분 객체는 여전히 존재할 수 있습니다. 즉, 전체 객체가 부분 객체를 소유 하지는 않지만, 사용 합니다.

### 코드 관점에서의 구분

#### 1. 객체 생성 및 소멸 책임:

- 연관: 연결된 객체들의 생성과 소멸은 서로 독립적으로 이루어집니다. 어느 한쪽에서 다른 쪽의 생성이나 소멸을 책임지지 않습니다.
- 집합: 전체 객체는 부분 객체를 사용 하지만, 부분 객체의 생성 과 소멸 을 책임지지 않습니다. 부분 객체는 외부에서 생성되어 전체 객체에 전달되는 경우가 많습니다.

#### 2. 포인터 vs. 참조:

두 관계 모두 포인터와 참조를 사용할 수 있습니다. 하지만, 집합의 경우 부분 객체의 소멸을 전체 객체가 책임지지 않아야 하기 때문에, 포인터를 사용하는 것이 더 일반적입니다. 참조를 사용하는 경우, 참조되는 객체의 생명주기가 참조하는 객체보다 길어야 한다는 제약이 있기 때문에 집합 관계를 표현하기에 부적절한 경우가 생길 수 있습니다.

#### 3. 코드의 의도:

가장 중요한 것은 코드의 의도 입니다. 코드만 보고는 연관인지 집합인지 명확히 구분하기 어려운 경우가 많습니다. 따라서, 코드 작성 시 주석이나 명명 규칙 등을 통해 관계의 의도를 명확히 표현하는 것이 중요합니다. 예를 들어, 집합 관계를 나타내는 멤버 변수 이름에 has_ 또는 owns_ 와 같은 접두사를 사용하지 않는 것이 좋습니다. (합성은 owns_ 를 사용하는 것이 일반적입니다.)

### 예제를 통한 비교 (C++):

```cpp
#include <iostream>

class Engine {
public:
    Engine(int power) : power_(power) {}
    ~Engine() { std::cout << "Engine 소멸" << std::endl; }
private:
    int power_;
};

// 연관
class CarWithMechanic {
public:
    CarWithMechanic(Engine* engine) : engine_(engine) {}
    ~CarWithMechanic(){ std::cout << "CarWithMechanic 소멸" << std::endl; }
private:
    Engine* engine_; // 연관: 엔진의 소멸을 책임지지 않음
};

// 집합
class CarWithEngine {
public:
    CarWithEngine(Engine* engine) : engine_(engine) {}
    ~CarWithEngine(){ std::cout << "CarWithEngine 소멸" << std::endl; }
private:
    Engine* engine_; // 집합: 엔진의 소멸을 책임지지 않음
};

int main() {
    // 연관 예제
    Engine* engineForMechanicCar = new Engine(100);
    {
        CarWithMechanic myCar1(engineForMechanicCar);
    }
    std::cout << "CarWithMechanic 스코프 종료" << std::endl;
    delete engineForMechanicCar; // 엔진은 Car와 독립적으로 소멸
    std::cout << "engineForMechanicCar 소멸" << std::endl;
    std::cout << std::endl;

    // 집합 예제
    Engine* engineForEngineCar = new Engine(200);
    {
        CarWithEngine myCar2(engineForEngineCar);
    }
    std::cout << "CarWithEngine 스코프 종료" << std::endl;
    //delete engineForEngineCar; // 집합에서는 Car가 소멸된 후 엔진을 삭제하는 것이 일반적
    std::cout << "engineForEngineCar는 Car 외부에서 관리됨" << std::endl; // 만약 delete를 안하면 메모리 누수 발생
    std::cout << std::endl;

    return 0;
}
```

위 예제에서 CarWithMechanic 과 CarWithEngine 은 코드 형태가 거의 동일합니다. 하지만, main 함수에서 엔진 객체의 소멸을 어떻게 처리하는지 주목해야 합니다. CarWithMechanic 의 경우, Car 객체가 소멸된 후 엔진 객체를 명시적으로 delete 해 주어야 합니다. 반면, CarWithEngine 의 경우, Car 객체가 엔진 객체의 소멸을 책임지지 않으므로, Car 객체 외부에서 엔진 객체를 관리해야 합니다. 만약 CarWithEngine 이 소멸된 후 엔진을 delete 하지 않으면 메모리 누수가 발생합니다.

### 결론:

연관과 집합은 코드 형태가 유사할 수 있지만, 객체의 생명주기 관리 방식에서 차이가 있습니다. 집합은 부분 객체의 독립적인 생명주기를 보장해야 하므로, 부분 객체의 생성과 소멸을 전체 객체가 책임지지 않도록 구현해야 합니다. 코드만 보고 두 관계를 구분하기 어려운 경우, 코드의 의도 와 객체 생명주기 관리 방식 을 명확히 파악하고, 주석이나 명명 규칙을 통해 코드의 의미를 명확히 전달하는 것이 중요합니다.