#include <iostream>
#include <string>
using namespace std;

// Interface
struct Command {
    virtual ~Command() = default;
    virtual void excute() = 0;
};

// Devices
struct Light {
    void on () { cout << "Light is On\n"; }
    void off () { cout << "Light is Off\n"; }
};

struct GarageDoor {
    void up() { cout << "Garage Door is Up\n"; }
    void down() { cout << "Garage Door is Down\n"; }
    void stop() { cout << "Garage Door is Stopped\n"; }
    void lightOn() { cout << "Garage Door Light is On\n"; }
    void lightOff() { cout << "Garage Door Light is Off\n"; }
};

// Concrete Light Command
struct LightOnCommand : Command {
    LightOnCommand(Light* light) { this->light = light; }
    // ~LightOnCommand() { delete light; }
    void excute() override { light->on(); }
private:
    Light* light;
};

struct LightOffCommand : Command {
    LightOffCommand(Light* light) { this->light = light; }
    // ~LightOffCommand() { delete light; }
    void excute() override { light->off(); }
private:
    Light* light;
};

// Concrete GarageDoor Command
struct GarageDoorOpenCommand : Command {
    GarageDoorOpenCommand(GarageDoor* garageDoor) { this->garageDoor = garageDoor; }
    void excute() { garageDoor->up(); }
private:
    GarageDoor* garageDoor;
};

struct GarageDoorCloseCommand : Command {
    GarageDoorCloseCommand(GarageDoor* garageDoor) { this->garageDoor = garageDoor; }
    void excute() { garageDoor->down(); }
private:
    GarageDoor* garageDoor;
};

struct SimpleRemoteControl {
    void setCommand(Command* command) { slot = command; }
    void buttonWasPressed() { slot->excute(); }
private:
    Command* slot;
};

int main()
{
    if (1) {
        SimpleRemoteControl* remote = new SimpleRemoteControl();

        Light* light = new Light();
        LightOnCommand* lightOn = new LightOnCommand(light);
        remote->setCommand(lightOn);
        remote->buttonWasPressed();

        LightOffCommand* lightOff = new LightOffCommand(light);
        remote->setCommand(lightOff);
        remote->buttonWasPressed();

        GarageDoor* garageDoor = new GarageDoor();
        GarageDoorOpenCommand* garageOpen = new GarageDoorOpenCommand(garageDoor);
        remote->setCommand(garageOpen);
        remote->buttonWasPressed();

        GarageDoorCloseCommand* garageClose = new GarageDoorCloseCommand(garageDoor);
        remote->setCommand(garageClose);
        remote->buttonWasPressed();

        delete remote;
        delete light, lightOn, lightOff;
        delete garageDoor, garageOpen, garageClose;
    }
    if (1) {
        auto& remote = SimpleRemoteControl();

        auto& light = Light();
        auto& lightOn = LightOnCommand(&light);
        remote.setCommand(&lightOn);
        remote.buttonWasPressed();

        auto& lightOff = LightOffCommand(&light);
        remote.setCommand(&lightOff);
        remote.buttonWasPressed();

        auto& garageDoor = GarageDoor();
        auto& garageOpen = GarageDoorOpenCommand(&garageDoor);
        remote.setCommand(&garageOpen);
        remote.buttonWasPressed();

        auto& garageClose = GarageDoorCloseCommand(&garageDoor);
        remote.setCommand(&garageClose);
        remote.buttonWasPressed();
    }
    return 0;
}