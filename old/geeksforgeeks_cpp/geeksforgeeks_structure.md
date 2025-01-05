# Structural Design Patterns

## 1. Adapter Method Design Pattern

### [adapter_1.cpp]

```cpp
#if 1
// https://www.geeksforgeeks.org/adapter-pattern-c-design-patterns/
#include <iostream>
#include <string>
using namespace std;

// Legacy Printer vs. Modern Printer


// Target Interface (Printer)
//class Computer {
//public:
//    virtual ~Computer() {};
//    virtual void sendCommand(const string& command) = 0;
//};

class ModernComputer {
public:
    virtual void sendCommand(const string& command) {
        cout << "Sending command: " << command << "\n";
    }
};


// Adaptee (LegacyPrinter)
class LegacyPrinter {
public:
    void printInUpperCase(const string& text) {
        cout << "Printing: " << text << ".\n";
    }
};

// Adapter (PrinterAdpater)
class PrinterAdapter: public ModernComputer {
//class PrinterAdapter {
private:
    LegacyPrinter legacyPrinter;
public:
    void sendCommand(const string& command) {
        string uppercaseCommand = command;
        for (char& c : uppercaseCommand)
            c = toupper(c);
        legacyPrinter.printInUpperCase(uppercaseCommand);
    }
};

// Client
class Client {
private:
    ModernComputer* _computer;
public:
    Client(ModernComputer* computer) { setPrinter(computer); }
    void setPrinter(ModernComputer* computer) { _computer = computer; }
    void sendCommand(const string& command) {
        _computer->sendCommand(command);
    }
};


int main()
{
    if (0) {
        ModernComputer computer;
        PrinterAdapter legacyadapter;

        computer.sendCommand("Print this in lowercase");
        legacyadapter.sendCommand("Print this in lowercase (adapted)");
    };

    if (1) {
        ModernComputer computer;
        PrinterAdapter legacyAdapter;

        Client* client = new Client(&computer);
        client->sendCommand("Print this in lowercase");

        client->setPrinter(&legacyAdapter);
        client->sendCommand("Print this in lowercase (adapted)");

        delete client;
    }

    return 0;
}
#endif
```

### [adapter_2.cpp]

```cpp
#if 0
// https://www.geeksforgeeks.org/adapter-pattern/

#include <iostream>
#include <string>
using namespace std;


// Target interface (Printer)
class Printer {
public:
    virtual ~Printer() {};
    virtual void print() = 0;
};

class MordernPrinter : public Printer {
public:
    void print() override {
        cout << "Modern Printer is printing a document.\n";
    }
};

// Adaptee (LegacyPrinter)
class LegacyPrinter {
public:
    void printDocument() {
        cout << "Legacy Printer is printing a document.\n";
    }
};

// Adapter (PrinterAdapter)
class PrinterAdpater : public Printer {
private:
    LegacyPrinter _legacyPrinter;
public:
    void print() override { _legacyPrinter.printDocument(); }
};

// Client
class Client {
private:
    Printer* _printer;
public:
    Client(Printer* printer) { setPrinter(printer); }
    void setPrinter(Printer* printer) { _printer = printer; }
    void print() { _printer->print(); }
};

int main()
{
    if (0) {
        MordernPrinter printer;
        PrinterAdpater adapter;

        printer.print();
        adapter.print();
    }

    if (1) {
        MordernPrinter printer;
        PrinterAdpater adapter;

        Client* client = new Client(&printer);
        client->print();

        client->setPrinter(&adapter);
        client->print();

        delete client;
    }


    return 0;
}
#endif
```

## 2. Bridge Method Design Pattern

### [bridge_guru.cpp]

```cpp
#if 0
#include <iostream>
#include <string>
using namespace std;

// Abstract Implemetation
class Implementation {
public:
    virtual ~Implementation() {}
    virtual string OperationImplementation() const = 0;
};

class ConcreteImplementationA : public Implementation {
public:
    string OperationImplementation() const override {
        return "ConcreteImplementationA: Here's the result on the platform A.\n";
    }
};
class ConcreteImplementationB : public Implementation {
public:
    string OperationImplementation() const override {
        return "ConcreteImplementationB: Here's the result on the platform B.\n";
    }
};


class Abstraction {
protected:
    Implementation* implementation_;

public:
    Abstraction(Implementation* implementation)
        : implementation_(implementation) {}

    virtual ~Abstraction() {}
    virtual string Operation() const {
        return "Abstraction: Base operation with:\n" +
            this->implementation_->OperationImplementation();
    }
};

class ExtendedAbstraction : public Abstraction {
public:
    ExtendedAbstraction(Implementation* implementation)
        : Abstraction(implementation) {}
    string Operation() const override {
        return "ExtendedAbstraction: Extended operation with:\n" +
            this->implementation_->OperationImplementation();
    }
};

void ClientCode(const Abstraction& abstraction) {
    cout << abstraction.Operation();
}


int main() {
    Implementation* implementation = new ConcreteImplementationA;
    Abstraction* abstraction = new Abstraction(implementation);
    ClientCode(*abstraction);
    cout << endl;

    delete implementation;
    delete abstraction;

    implementation = new ConcreteImplementationB;
    abstraction = new ExtendedAbstraction(implementation);
    ClientCode(*abstraction);

    delete implementation;
    delete abstraction;

    return 0;
}
#endif
```

### [bridge_workshop_ptr.cpp]

```cpp
#if 0
// https://www.geeksforgeeks.org/bridge-design-pattern/
#include <iostream>
using namespace std;

// Implementation
class Workshop {
public:
    virtual ~Workshop() {};
    virtual void work() const = 0;
};

class Produce : public Workshop {
public:
    void work() const override { cout << "Producded"; }
};

class Assemble : public Workshop {
public:
    void work() const override { cout << " And Assembled.\n"; }
};


// Abstractrion
class Vehicle {
protected:
    Workshop* workshop1;
    Workshop* workshop2;
public:
    Vehicle(Workshop* workshop1, Workshop* workshop2)
        : workshop1(workshop1), workshop2(workshop2) {}
    virtual ~Vehicle() {};
    virtual void manufacture() const = 0;

};


class Car: public Vehicle {
public:
    Car(Workshop* workshop1, Workshop* workshop2)
        : Vehicle(workshop1, workshop2) {}
    void manufacture() const override {
        cout << "Car ";
        this->workshop1->work();
        this->workshop2->work();
    }
};

class Bike: public Vehicle {
public:
    Bike(Workshop* workshop1, Workshop* workshop2)
        : Vehicle(workshop1, workshop2) {}
    void manufacture() const override {
        cout << "Bike ";
        this->workshop1->work();
        this->workshop2->work();
    }
};


int main()
{
    Vehicle* vehicle1 = new Car(new Produce(), new Assemble());
    vehicle1->manufacture();

    Vehicle* vehicle2 = new Bike(new Produce(), new Assemble());
    vehicle2->manufacture();

    delete vehicle1;
    delete vehicle2;

    return 0;
}
#endif
```

### [bridge_workshop_ref.cpp]

```cpp
#if 1
// https://www.geeksforgeeks.org/bridge-design-pattern/
#include <iostream>
using namespace std;

// Implementation
class Workshop {
public:
    virtual ~Workshop() {};
    virtual void work() const = 0;
};

class Produce : public Workshop {
public:
    void work() const override { cout << "Producded"; }
};

class Assemble : public Workshop {
public:
    void work() const override { cout << " And Assembled.\n"; }
};


// Abstractrion
class Vehicle {
protected:
    Workshop& workshop1;
    Workshop& workshop2;
public:
    Vehicle(Workshop& workshop1, Workshop& workshop2)
        : workshop1(workshop1), workshop2(workshop2) {}
    virtual ~Vehicle() {};
    virtual void manufacture() const = 0;

};


class Car : public Vehicle {
public:
    Car(Workshop& workshop1, Workshop& workshop2)
        : Vehicle(workshop1, workshop2) {}
    void manufacture() const override {
        cout << "Car ";
        workshop1.work();
        workshop2.work();
    }
};

class Bike : public Vehicle {
public:
    Bike(Workshop& workshop1, Workshop& workshop2)
        : Vehicle(workshop1, workshop2) {}
    void manufacture() const override {
        cout << "Bike ";
        workshop1.work();
        workshop2.work();
    }
};


int main()
{
    // ref: concrete classes
    Produce produce;
    Assemble assemble;

    Car car{ produce, assemble };
    car.manufacture();

    Bike bike{ produce, assemble };
    bike.manufacture();

    return 0;
}
#endif
```

## 3. Composite Method Design Pattern

### [composite.cpp]

```cpp
#if 1
#include <iostream>
#include <string>
#include <list>
using namespace std;

// Component (Interface)
class Task {
public:
    virtual ~Task() {};
    virtual string getTitle() const = 0;
    virtual void setTitle(const string& title) = 0;
    virtual void display() const = 0;
};

// Leaf
class SimpleTask: public Task {
private:
    string title;
public:
    SimpleTask(const string title) { this->title = title; }
    string getTitle() const override { return title; }
    void setTitle(const string& title) { this->title = title; }
    void display() const override { cout << "Simple Task: " << title << "\n"; }
};

// Composite
class TaskList : public Task {
private:
    string title;
    list<Task*> tasks;
public:
    TaskList(const string& title) { this->title = title; }
    string getTitle() const override { return title; }
    void setTitle(const string& title) { this->title = title; }
    void display() const override {
        cout << "Task List: " << title << "\n";
        for (auto task : tasks)
            task->display();
    }

    void addTask(Task* task) { tasks.push_back(task); }
    void removeTask(Task* task) { tasks.remove(task); }
};


// Client

int main()
{
    Task* simpleTask1 = new SimpleTask("Complete Coding");
    Task* simpleTask2 = new SimpleTask("Write Documentation");

    TaskList* phase1Tasks = new TaskList("Phase 1 Tasks");
    phase1Tasks->addTask(new SimpleTask("Design"));
    phase1Tasks->addTask(new SimpleTask("Implementation"));

    TaskList* projectTasks = new TaskList("Project Tasks");
    projectTasks->addTask(simpleTask1);
    projectTasks->addTask(simpleTask2);
    projectTasks->addTask(phase1Tasks);

    projectTasks->display();

    delete simpleTask1;
    delete simpleTask2;
    delete phase1Tasks;
    delete projectTasks;

    return 0;
}
#endif
```

## 4. Decorator Method Design Pattern

### [decorator_icecream.cpp]

```cpp
#if 1
#include <iostream>
#include <string>
#include <map>
using namespace std;


// Component Interface
class IceCream {
public:
    virtual ~IceCream() {};
    virtual string getDescription() const = 0;
    virtual int getCost() const = 0;
};

// Concrete Components
class VanillaIceCream : public IceCream {
public:
    string getDescription() const override { return "Vanilla Ice Cream"; }
    int getCost() const override { return 160; }
};


// Decorator
class IceCreamDecorator : public IceCream {
protected:
    IceCream* iceCream; // interface
public:
    IceCreamDecorator(IceCream* iceCream) : iceCream(iceCream) {}
    string getDescription() const override { return iceCream->getDescription(); }
    int getCost() const override { return iceCream->getCost(); }
};


// Concrete Decorators
class ChocolateDecorator : public IceCreamDecorator {
public:
    ChocolateDecorator(IceCream* iceCream) : IceCreamDecorator(iceCream) {}
    string getDescription() const override {
        return iceCream->getDescription() + " with Chocolate";
    }
    int getCost() const override { return iceCream->getCost() + 100; }
};

class CaramelDecorator : public IceCreamDecorator {
public:
    CaramelDecorator(IceCream* iceCream) : IceCreamDecorator(iceCream) {}
    string getDescription() const override {
        return iceCream->getDescription() + " with Caremel";
    }
    int getCost() const override { return iceCream->getCost() + 150; }
};


// Client
//class Client {
//private:
//    IceCream* iceCream;
//    map<string, IceCream*> decorators;
//public:
//    Client(IceCream* iceCream) {
//        this->iceCream = iceCream;
//        decorators["chocolate"] = new ChocolateDecorator(iceCream);
//        decorators["caramel"] = new CaramelDecorator(iceCream);
//    }
//    ~Client() {
//        delete decorators["chocolate"];
//        delete decorators["caramel"];
//        decorators.clear();
//    }
//    void decorate(const string& deco) {
//        this->iceCream = decorators[deco]()
//    }
//    void printOrder() {
//        cout << "Order: " << iceCream->getDescription()
//            << ", Cost: Rs." << iceCream->getCost() << "\n";
//    }
//};

int main()
{
    if (0) {
        IceCream* vanillaIceCream = new VanillaIceCream();
        cout << "Order: " << vanillaIceCream->getDescription()
            << ", Cost: Rs." << vanillaIceCream->getCost() << "\n";

        IceCream* chocolateIceCream = new ChocolateDecorator(vanillaIceCream);
        cout << "Order: " << chocolateIceCream->getDescription()
            << ", Cost: Rs." << chocolateIceCream->getCost() << "\n";

        IceCream* caramelIceCream = new CaramelDecorator(chocolateIceCream);
        cout << "Order: " << caramelIceCream->getDescription()
            << ", Cost: Rs." << caramelIceCream->getCost() << "\n";

        delete vanillaIceCream;
        delete chocolateIceCream;
        delete caramelIceCream;
    }
    //if (1) {
    //    Client client{ new VanillaIceCream() };
    //    IceCream* iceCream = client.decorate("chocolate");
    //    client.printOrder();
    //}

    return 0;
}
#endif
```

## 5. Facade Method Design Pattern

### [facade_car.cpp]

```cpp
#if 0
// https://www.geeksforgeeks.org/facade-method-c-design-patterns/
#include <iostream>
using namespace std;


// Subsystem classes
class Engine {
public:
    void start() { cout << "Engine started.\n"; }
    void stop() { cout << "Engine stopped.\n"; }
};


class Light {
public:
    void turnOn() { cout << "Lights on.\n"; }
    void turnOff() { cout << "Lights off.\n"; }
};

// Facade
class Car {
private:
    Engine engine;
    Light light;
public:
    void startCar() {
        engine.start();
        light.turnOn();
        engine.stop();
        cout << "Car is ready to drive.\n";
    }
    void stopCar() {
        light.turnOff();
        engine.stop();
        cout << "Car has stopped.\n";
    }
};


int main()
{
    Car car;
    car.startCar();
    car.stopCar();

    return 0;
}
#endif
```

### [facade_hotel.cpp]

```cpp
#if 0


class Menu;

// subsystems
class Hotel {
public:
    virtual ~Hotel() {}
    virtual Menu* getMenu() const = 0;
};

class NonVegRestaurent : public Hotel {
public:
    Menu* getMenu() const override;
};

class VegRestaurent : public Hotel {
public:
    Menu* getMenu() const override;
};

class BothVegNonRestaurent : public Hotel {
public:
    Menu* getMenu() const override;
};


// Facede

int main()
{
    return 0;
}
#endif
```

### [facade_multimedia.cpp]

```cpp
#if 1
#include <iostream>
#include <string>
using namespace std;

// Subsystem classes
class AudioPlayer {
public:
    void playAudio(const string& filename) {
        cout << "Playing audio file: " << filename << endl;
    }
};
class VideoPlayer {
public:
    void playVideo(const string& filename) {
        cout << "Playing video file: " << filename << endl;
    }
};
class ImageLoader {
public:
    void loadImage(const string& filename) {
        cout << "Loading image file: " << filename << endl;
    }
};

// Facade (pointer)
class MultimediaFacade1 {
private:
    AudioPlayer* audioPlayer;
    VideoPlayer* videoPlayer;
    ImageLoader* imageLoader;
public:
    MultimediaFacade1() {
        audioPlayer = new AudioPlayer();
        videoPlayer = new VideoPlayer();
        imageLoader = new ImageLoader();
    }
    ~MultimediaFacade1() {
        delete audioPlayer;
        delete videoPlayer;
        delete imageLoader;
    }
    void playMedia(const string& filename, const string& mediaType) {
        if (mediaType == "audio")
            audioPlayer->playAudio(filename);
        else if (mediaType == "video")
            videoPlayer->playVideo(filename);
        else if (mediaType == "image")
            imageLoader->loadImage(filename);
        else
            cout << "Unsupported media type: " << mediaType << endl;
    }
};

// Facede (object)
class MultimediaFacade2 {
private:
    AudioPlayer audioPlayer;
    VideoPlayer videoPlayer;
    ImageLoader imageLoader;
public:
    void playMedia(const string& filename, const string& mediaType) {
        if (mediaType == "audio")
            audioPlayer.playAudio(filename);
        else if (mediaType == "video")
            videoPlayer.playVideo(filename);
        else if (mediaType == "image")
            imageLoader.loadImage(filename);
        else
            cout << "Unsupported media type: " << mediaType << endl;
    }
};


int main()
{
    if (1) {
        MultimediaFacade1* facade1 = new MultimediaFacade1();

        facade1->playMedia("song.mp3", "audio");
        facade1->playMedia("movie.mp4", "video");
        facade1->playMedia("picture.jpg", "image");
        facade1->playMedia("unknown.file", "unknown");

        delete facade1;
    }
    cout << endl;
    if (1) {
        MultimediaFacade2 facade2;

        facade2.playMedia("song.mp3", "audio");
        facade2.playMedia("movie.mp4", "video");
        facade2.playMedia("picture.jpg", "image");
        facade2.playMedia("unknown.file", "unknown");
    }

    return 0;
}
#endif
```

## 6. Flyweight Method Design Pattern

### [flyweight.cpp]

```cpp
// https://www.geeksforgeeks.org/flyweight-pattern-c-design-patterns/
#include <iostream>
#include <unordered_map>
using namespace std;

// Flyweight class
class Character {
private:
    const char* intrinsicState;
public:
    Character(const char* intrinsicState) : intrinsicState(intrinsicState) {}

    void draw(int extrinsicState) {
        cout << "Character '" << intrinsicState << "' at position " << extrinsicState << std::endl;
    }
};

// Flyweight factory
class CharacterFactory {
private:
    unordered_map<const char*, Character*> pool;
public:
    Character* getCharacter(const char* key) {
        auto iter = pool.find(key);
        if (iter == pool.end()) {
            auto character = new Character(key);
            pool.emplace(key, character);
            return character;
        }
        return iter->second;
    }
};

int main()
{
    if (1) {
        CharacterFactory characterFactory;

        // Extrinsic state
        int position = 0;

        // Drawing characters 'A', 'B', 'C' at different positions
        characterFactory.getCharacter("AAA")->draw(position++);
        characterFactory.getCharacter("BBB")->draw(position++);
        characterFactory.getCharacter("CCC")->draw(position++);
    }

    if (0) {
        CharacterFactory factory;
        cout << factory.getCharacter("AAA") << endl;
        cout << factory.getCharacter("BBB") << endl;
        cout << factory.getCharacter("CCC") << endl;

        cout << factory.getCharacter("AAA") << endl;
    }

    return 0;
}
```

## 7. Proxy Method Design Pattern

### [proxy_image.cpp]

```cpp
#if 1
// https://www.geeksforgeeks.org/proxy-design-pattern/
// https://www.geeksforgeeks.org/proxy-pattern-c-design-patterns/
#include <iostream>
#include <string>
using namespace std;


// Subject (Interface)
class Image {
public:
    virtual void display() = 0;
};

// Real Subject
class RealImage : public Image {
private:
    string filename;
public:
    RealImage(const string& filename) : filename(filename) {
        cout << "Loading image: " << filename << endl;
    }
    void display() override {
        cout << "Displaying image: " << filename << endl;
    }
};

// Proxy
class ImageProxy : public Image {
private:
    RealImage* realImage;   // pointer to the Real Object
    string filename;
public:
    ImageProxy(const string& filename)
        : filename(filename), realImage(nullptr) {}
    void display() override {
        if (realImage == nullptr)
            realImage = new RealImage(filename);
        realImage->display();
    }
};

// Client


int main()
{
    if (1) {
        Image* image = new ImageProxy("example.jpg");
        image->display();
        image->display();

        delete image;
    }

    return 0;
}
#endif
```
