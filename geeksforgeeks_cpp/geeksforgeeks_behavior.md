# Behavioral Design Patterns

## 1. Chain Of Responsibility Method Design Pattern

### [chain_resp.cpp]

```cpp
#if 1
// https://www.geeksforgeeks.org/chain-responsibility-design-pattern/
#include <iostream>
#include <vector>
using namespace std;


enum Priority { BASIC=0, INTERMEDIATE, CRITICAL };

class Request {
private:
    Priority priority;
public:
    Request(Priority priority) { this->priority = priority; }
    Priority getPriority() { return priority; }
};


// Handler Interface
class SupportHandler {
public:
    virtual ~SupportHandler() {}
    virtual SupportHandler* setNextHandler(SupportHandler* nextHandler) = 0;
    virtual void handdlerRequest(Request* request) = 0;
};

// Concrete handlers
class Level1SupprotHandler : public SupportHandler {
private:
    SupportHandler* nextHandeler;
public:
    SupportHandler* setNextHandler(SupportHandler* nextHandler) override {
        this->nextHandeler = nextHandler;
        return nextHandeler;
    }
    void handdlerRequest(Request* request) override {
        if (request->getPriority() == Priority::BASIC)
            cout << "Level 1 Support handled the request.\n";
        else if (nextHandeler != nullptr)
            nextHandeler->handdlerRequest(request);
    }
};

class Level2SupprotHandler : public SupportHandler {
private:
    SupportHandler* nextHandeler;
public:
    SupportHandler* setNextHandler(SupportHandler* nextHandler) override {
        this->nextHandeler = nextHandler;
        return nextHandeler;
    }
    void handdlerRequest(Request* request) override {
        if (request->getPriority() == Priority::INTERMEDIATE)
            cout << "Level 2 Support handled the request.\n";
        else if (nextHandeler != nullptr)
            nextHandeler->handdlerRequest(request);
    }
};

class Level3SupprotHandler : public SupportHandler {
private:
    SupportHandler* nextHandeler;
public:
    SupportHandler* setNextHandler(SupportHandler* nextHandler) override {
        this->nextHandeler = nextHandler;
        return nextHandeler;
    }
    void handdlerRequest(Request* request) override {
        if (request->getPriority() == Priority::CRITICAL)
            cout << "Level 3 Support handled the request.\n";
        else
            cout << "Request cannot be handled.\n";
    }
};


// Client


int main()
{
    if (0) {
        SupportHandler* level1Handler = new Level1SupprotHandler();
        SupportHandler* level2Handler = new Level2SupprotHandler();
        SupportHandler* level3Handler = new Level3SupprotHandler();

        level1Handler->setNextHandler(level2Handler)->setNextHandler(level3Handler);

        //level1Handler->setNextHandler(level2Handler);
        //level2Handler->setNextHandler(level3Handler);

        Request* request1 = new Request(Priority::BASIC);
        Request* request2 = new Request(Priority::INTERMEDIATE);
        Request* request3 = new Request(Priority::CRITICAL);

        level1Handler->handdlerRequest(request1);
        level1Handler->handdlerRequest(request2);
        level1Handler->handdlerRequest(request3);

        delete level1Handler;
        delete level2Handler;
        delete level3Handler;

        delete request1;
        delete request2;
        delete request3;
    }

    cout << endl;
    if (1) {
        Level1SupprotHandler handler1;
        Level2SupprotHandler handler2;
        Level3SupprotHandler handler3;

        handler1.setNextHandler(&handler2)->setNextHandler(&handler3);

        //handler1.setNextHandler(&handler2);
        //handler2.setNextHandler(&handler3);

        Request req1{ BASIC };
        Request req2{ INTERMEDIATE };
        Request req3{ CRITICAL };

        handler1.handdlerRequest(&req1);
        handler1.handdlerRequest(&req2);
        handler1.handdlerRequest(&req3);
    }

    return 0;
}
#endif
```

## 2. Command Method Design Pattern

### [command_device.cpp]

```cpp
#if 1
#include <iostream>
#include <vector>
using namespace std;

// Receiver
class Device {
public:
    virtual ~Device() {}
    virtual void turnOn() const = 0;
    virtual void turnOff() const = 0;
};

class TV : public Device {
public:
    void turnOn() const override { cout << "TV is now on.\n"; }
    void turnOff() const override { cout << "TV is now off.\n"; }
    void changeChannel() const { cout << "Channel changed.\n"; }
};

class Stereo : public Device {
public:
    void turnOn() const override { cout << "Stereo is now on.\n"; }
    void turnOff() const override { cout << "Stereo is now off.\n"; }
    void adjustVolume() const { cout << "Volume adjusted.\n"; }
};


// Command Interface (Absract class)
class Command {
public:
    virtual ~Command() {}
    virtual void execute() const = 0;
};

// Concrete Commands
class TurnOnCommand : public Command {
private:
    Device* device;
public:
    TurnOnCommand(Device* device) : device(device) {}
    void execute() const override { device->turnOn(); }
};

class TurnOffCommand : public Command {
private:
    Device* device;
public:
    TurnOffCommand(Device* device) : device(device) {}
    void execute() const override { device->turnOff(); }
};

class AdjustVolumeCommand : public Command {
private:
    Stereo* stereo;
public:
    AdjustVolumeCommand(Stereo* stereo) : stereo(stereo) {}
    void execute() const override { stereo->adjustVolume(); }
};

class ChangeChannelCommand : public Command {
private:
    TV* tv;
public:
    ChangeChannelCommand(TV* tv) : tv(tv) {}
    void execute() const override { tv->changeChannel(); }
};

// Invoker
class RemoteControl {
private:
    Command* command;
public:
    void setCommand(Command* command) { this->command = command; }
    void pressButton() { command->execute(); }
};


int main()
{
    if (0) {
        // create devices
        TV* tv = new TV();
        Stereo* stereo = new Stereo();

        // create commands
        Command* turnOnTV = new TurnOnCommand(tv);
        Command* turnOffTV = new TurnOffCommand(tv);
        Command* adjustVolumeStereo = new AdjustVolumeCommand(stereo);
        Command* changeChannelTV = new ChangeChannelCommand(tv);

        RemoteControl* remote = new RemoteControl();

        remote->setCommand(turnOnTV);
        remote->pressButton();

        remote->setCommand(turnOffTV);
        remote->pressButton();

        remote->setCommand(adjustVolumeStereo);
        remote->pressButton();

        remote->setCommand(changeChannelTV);
        remote->pressButton();

        delete tv;
        delete stereo;
        delete remote;
        delete turnOnTV;
        delete turnOffTV;
        delete adjustVolumeStereo;
        delete changeChannelTV;
    }
    if (1) {
        // create devices
        TV tv;
        Stereo stereo;

        // create commands
        TurnOnCommand turnOnTV(&tv);
        TurnOffCommand turnOffTV(&tv);
        AdjustVolumeCommand adjustVolumeStereo(&stereo);
        ChangeChannelCommand changeChannelTV(&tv);

        RemoteControl remote;

        remote.setCommand(&turnOnTV);
        remote.pressButton();

        remote.setCommand(&turnOffTV);
        remote.pressButton();

        remote.setCommand(&adjustVolumeStereo);
        remote.pressButton();

        remote.setCommand(&changeChannelTV);
        remote.pressButton();
    }

    return 0;
}
#endif
```

## 3. Interpreter Method Design Pattern

### [none]

```cpp

```

## 4. Mediator Method Design Pattern

### [mediator_airport.cpp]

```cpp
#if 1
// https://www.geeksforgeeks.org/mediator-design-pattern/

#include <iostream>
#include <string>
using namespace std;


// Colleague
class AirPlane {
public:
    virtual ~AirPlane() {}
    virtual void requestTakeOff() = 0;
    virtual void requestLanding() = 0;
    virtual void notifyAirTrafficControl(const string& message) = 0;
};

// Mediator (Abstract)
class AirTrafficControlTower {
public:
    virtual void requestTakeOff(AirPlane* airplane) = 0;
    virtual void requestLanding(AirPlane* airplane) = 0;
};

// Concrete Colleague
class CommercialAirPlane : public AirPlane {
private:
    AirTrafficControlTower* mediator;
public:
    CommercialAirPlane(AirTrafficControlTower* mediator): mediator(mediator) {}
    void requestTakeOff() override {
        mediator->requestTakeOff(this);
    }
    void requestLanding() override {
        mediator->requestLanding(this);
    }
    void notifyAirTrafficControl(const string& message) override {
        cout << "Commercial Airplane: " << message << endl;
    }

};

// Concrete Mediator
class AirPortControlTower : public AirTrafficControlTower {
public:
    void requestTakeOff(AirPlane* airplane) override {
        cout << "Requesting takeoff clearance.\n";
    }
    void requestLanding(AirPlane* airplane) override {
        cout << "Requesting landing clearance.\n";
    }
};



int main()
{
    if (0) {
        AirTrafficControlTower* controlTower = new AirPortControlTower();

        AirPlane* airplane1 = new CommercialAirPlane(controlTower);
        AirPlane* airplane2 = new CommercialAirPlane(controlTower);

        airplane1->requestTakeOff();
        airplane2->requestLanding();

        delete controlTower;
        delete airplane1;
        delete airplane2;
    }
    if (1) {
        AirPortControlTower controlTower;
        CommercialAirPlane airplane1(&controlTower);
        CommercialAirPlane airplane2(&controlTower);

        airplane1.requestTakeOff();
        airplane2.requestLanding();
    }
    return 0;
}
#endif
```

## 5. Memento Method Design Patterns

### [memento.cpp]

```cpp
#if 1
// https://www.geeksforgeeks.org/memento-design-pattern/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Memento
class DocumentMemento {
private:
    string content;
public:
    DocumentMemento(const string& content) : content(content) {}
    string getSavedContent() { return content; }
};


// Originator
class Document {
private:
    string content;
public:
    Document(const string& content): content(content) {}
    void write(const string& text) { content += text; }
    string getContent() const { return content; }
    DocumentMemento* createMemento() { return new DocumentMemento(content); }
    void restoreFromMemento(DocumentMemento* memento) {
        content = memento->getSavedContent();
    }
};

// Caretaker
class History {
private:
    vector<DocumentMemento*> mementos;
public:
    //History() {}
    void addMemento(DocumentMemento* memento) { mementos.push_back(memento); }
    DocumentMemento* getMemento(int index) { return mementos[index]; }
};

// Client


int main()
{
    if (1) {
        Document* document = new Document("Initial content\n");
        History* history = new History();

        // Write some content
        document->write("Additional content\n");
        history->addMemento(document->createMemento());     // index = 0
        cout << document->getContent();
        cout << "======================\n\n";

        // Write some Content
        document->write("More content\n");
        history->addMemento(document->createMemento());     // index = 1
        cout << document->getContent();
        cout << "======================\n\n";

        // Restore to previous state
        document->restoreFromMemento(history->getMemento(0));
        cout << document->getContent();

        document->restoreFromMemento(history->getMemento(1));
        cout << document->getContent();

        delete document;
        delete history;
    }
    return 0;
}
#endif
```

## 6. Observer Method Design Pattern

### [observer.cpp]

```cpp
#if 1
// https://www.geeksforgeeks.org/observer-pattern-c-design-patterns/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Observer (Interface)
class Observer {
public:
    virtual ~Observer() {};
    virtual void update(int temperature, int humidity, int pressure) = 0;
};

// Subject
class WeatherStation {
private:
    int temperature, humidity, pressure;
    vector<Observer*> observers;
public:
    void registerObserver(Observer* observer) { observers.push_back(observer); }
    void removeObserver(Observer* observer) {}
    void notifyObservers() const {
        for (const auto obs : observers)
            obs->update(temperature, humidity, pressure);
    }
    void setMeasurements(int temperature, int humidity, int pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        notifyObservers();
    }
};

// Concrete Observer
class Display : public Observer {
public:
    void update(int temperature, int humidity, int pressure) {
        cout << "Display: Temperature = " << temperature
            << "°C, Humidity = " << humidity
            << "%, Pressure = " << pressure << " hPa"
            << endl;
    }
};


int main()
{
    WeatherStation station;

    Display display1, display2;
    station.registerObserver(&display1);
    station.registerObserver(&display2);

    station.setMeasurements(25, 60, 1013);
    //station.setMeasurements(20, 50, 1000);

    return 0;
}
#endif
```

## 7. State Method Design Pattern

### [state_vending-machine.cpp]

```cpp
#if 1
// https://www.geeksforgeeks.org/state-design-pattern/
#include <iostream>
#include <string>
using namespace std;


// State Interface
class VendingMachineState {
public:
    virtual ~VendingMachineState() {}
    virtual void handleRequest() const = 0;
};

// Context
class VendingMachineContext {
private:
    VendingMachineState* state;
public:
    void setState(VendingMachineState* state) { this->state = state; }
    void request() { state->handleRequest(); }
};


// Concrete States
class ReadyState : public VendingMachineState {
public:
    void handleRequest() const override {
        cout << "Ready state: Please select a product.\n";
    }
};

class ProductSelectedState: public VendingMachineState {
public:
    void handleRequest() const override {
        cout << "Product selected state: Processing payment.\n";
    }
};

class PaymentPendingState: public VendingMachineState {
public:
    void handleRequest() const override {
        cout << "Payment pending state: Dispensing product.\n";
    }
};

class OutOfStockState: public VendingMachineState {
public:
    void handleRequest() const override {
        cout << "Out of stock state: Product unavailable. Please select another product.\n";
    }
};

int main()
{
    if (0) {
        VendingMachineContext* machine = new VendingMachineContext();

        machine->setState(new ReadyState());
        machine->request();

        machine->setState(new ProductSelectedState());
        machine->request();

        machine->setState(new PaymentPendingState());
        machine->request();

        machine->setState(new OutOfStockState());
        machine->request();

        delete machine;
    }
    if (1) {
        VendingMachineContext machine;

        machine.setState(new ReadyState());
        machine.request();

        machine.setState(new ProductSelectedState());
        machine.request();

        machine.setState(new PaymentPendingState());
        machine.request();

        machine.setState(new OutOfStockState());
        machine.request();
    }

    return 0;
}
#endif
```

## 8. Strategy Method Design Pattern

### [strategy_sorting.cpp]

```cpp
#if 1
#include <iostream>
#include <string>
using namespace std;

// Strategy Interface
class SortingStrategy {
public:
    virtual ~SortingStrategy() {};
    virtual void sort(int arr[]) const = 0;
};

// Context
class SortingContext {
private:
    SortingStrategy* sortingStrategy;
public:
    SortingContext(SortingStrategy* sortingStrategy) {
        this->sortingStrategy = sortingStrategy;
    }
    void setSortingStrategy(SortingStrategy* sortingStrategy) {
        this->sortingStrategy = sortingStrategy;
    }
    void performSort(int arr[]) {
        sortingStrategy->sort(arr);
    }
};

// Concrete Stretegies
class BubbleSortStrategy : public SortingStrategy {
public:
    void sort(int arr[]) const override {
        cout << "Sorting using Bubble Sort\n";
    }
};

class MergeSortStrategy : public SortingStrategy {
public:
    void sort(int arr[]) const override {
        cout << "Sorting using Merge Sort\n";
    }
};

class QuickSortStrategy : public SortingStrategy {
public:
    void sort(int arr[]) const override {
        cout << "Sorting using Quick Sort\n";
    }
};

// Client


int main()
{
    if (0) {
        SortingContext* context = new SortingContext(new BubbleSortStrategy());
        int arr[] = { 5, 2, 9, 1, 5 };
        context->performSort(arr);

        context->setSortingStrategy(new MergeSortStrategy());
        context->performSort(arr);

        context->setSortingStrategy(new QuickSortStrategy());
        context->performSort(arr);

        delete context;
    }

    if (1) {
        BubbleSortStrategy bubbleSort;
        MergeSortStrategy mergeSort;
        QuickSortStrategy quickSort;

        SortingContext context(&bubbleSort);
        int arr[] = { 5, 2, 9, 1, 5 };
        context.performSort(arr);

        context.setSortingStrategy(&mergeSort);
        context.performSort(arr);

        context.setSortingStrategy(&quickSort);
        context.performSort(arr);
    }

    return 0;
}
#endif
```

## 9. Template Method Design Pattern

### [template_beverage.cpp]

```cpp
#if 1
#include <iostream>
#include <string>
using namespace std;

// Abstract Class
class BeverageMaker {
public:
    virtual ~BeverageMaker() {};

    void makeBeverage() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }
    virtual void brew() const = 0;
    virtual void addCondiments() const = 0;
    void boilWater() { cout << "Boiling water\n"; }
    void pourInCup() { cout << "Pouring into cup\n"; }
};

// Concrete Subclasses
class TeaMaker : public BeverageMaker {
public:
    void brew() const override { cout << "Steeping the tea\n"; }
    void addCondiments() const override { cout << "Adding lemon\n"; }
};

class CoffeeMaker : public BeverageMaker {
public:
    void brew() const override { cout << "Dripping coffee through filter\n"; }
    void addCondiments() const override { cout << "Adding sugar and milk\n"; }
};


int main()
{
    if (0) {
        BeverageMaker* teaMaker = new TeaMaker();
        teaMaker->makeBeverage();

        BeverageMaker* coffeeMaker = new CoffeeMaker();
        coffeeMaker->makeBeverage();

        delete teaMaker;
        delete coffeeMaker;
    }

    if (1) {
        TeaMaker teaMaker;
        teaMaker.makeBeverage();

        CoffeeMaker coffeeMaker;
        coffeeMaker.makeBeverage();
    }
    return 0;
}
#endif
```

## 10. Visitor Method Design Pattern

### [visitor_shopping.cpp]

```cpp
#if 1
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Book;
class Fruit;

// Visitor
class ShoppingCartVisitor {
public:
    virtual ~ShoppingCartVisitor() {};
    virtual int visit(Book* book) const = 0;
    virtual int visit(Fruit* fruit) const = 0;
};


// Visitable (Interface)
class ItemElement {
public:
    virtual ~ItemElement() {};
    virtual int accept(ShoppingCartVisitor* visitor) = 0;
};

// Concrete Visitalbes
class Book : public ItemElement {
private:
    int price;
    string isbnNumber;
public:
    Book(int price, const string& isbnNumber) {
        this->price = price;
        this->isbnNumber = isbnNumber;
    }
    int getPrice() const { return price; }
    string getIsbnNumber() const { return isbnNumber; }
    int accept(ShoppingCartVisitor* visitor) override { return visitor->visit(this); }
};

class Fruit : public ItemElement {
private:
    int price, weight;
    string name;
public:
    Fruit(int price, int weight, const string& name) {
        this->price = price;
        this->weight = weight;
        this->name = name;
    }
    int getPrice() const { return price; }
    int getWeight() const { return weight; }
    string getName() const { return name; }
    int accept(ShoppingCartVisitor* visitor) override { return visitor->visit(this); }
};

// Concrete Visitors
class ShoppingCartVisitorImpl : public ShoppingCartVisitor {
public:
    int visit(Book* book) const override {
        int cost = 0;
        if (book->getPrice() > 50)
            cost = book->getPrice() - 5;
        else
            cost = book->getPrice();
        cout << "Book ISBN: " << book->getIsbnNumber()
            << " cost = " << book->getPrice() << endl;
        return cost;
    }
    int visit(Fruit* fruit) const override {
        int cost = fruit->getPrice() * fruit->getWeight();
        cout << fruit->getName() << " cost = " << cost << endl;
        return cost;
    }
};

int calculatePrice(const vector<ItemElement*>& items) {
    ShoppingCartVisitor* visitor = new ShoppingCartVisitorImpl();
    int sum = 0;
    for (auto item : items)
        sum += item->accept(visitor);
    return sum;
}

int main()
{
    if (1) {
        vector<ItemElement*> items = { 
            new Book(20, "1234"),
            new Book(100, "5678"), 
            new Fruit(10, 2, "Banana"),
            new Fruit(5, 5, "Apple")
        };
        
        int total = calculatePrice(items);
        cout << "Total cost = " << total << endl;
    }

    //if (0) {
    //    vector<const ItemElement&> items = {
    //        Book(100, "5678"),
    //        Fruit(10, 2, "Banana"),
    //        Fruit(5, 5, "Apple")
    //    };

    //    int total = calculatePrice(items);
    //    cout << "Total cost = " << total << endl;
    //}

    return 0;
}
#endif
```
