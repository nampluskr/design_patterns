#include <iostream>
#include <sstream>
#include <string>
using namespace std;


// Interface
struct Command {
    virtual ~Command() = default;
    virtual void excute() = 0;
};

struct NoCommand : Command {
    void excute() override { cout << "NoCommand::execute\n"; }
};

// Devices
struct Light {
    Light(const string& loc) { location = loc; }
    void on () { cout << location << " Light is On\n"; }
    void off () { cout << location <<" Light is Off\n"; }
private:
    string location;
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

// Invoker
struct RemoteControl {
    RemoteControl() {
        Command* noCommand = new NoCommand();
        for (int i = 0; i < NUM_SLOTS; i++) {
            onCommands[i] = noCommand;
            offCommands[i] = noCommand;
        }
    }
    void setCommand(int slot, Command* onCommand, Command* offCommand) {
        onCommands[slot] = onCommand;
        offCommands[slot] = offCommand;
    }
    void onButtonWasPushed(int slot) { onCommands[slot]->excute(); }
    void offButtonWasPushed(int slot) { offCommands[slot]->excute(); }
    string toString() {
        stringstream value;
        value << "\n------ Remote Control -------\n" << endl;
        for (int i = 0; i < NUM_SLOTS; i++) {
            value << "[slot " << i << "] ";
            value << typeid(*onCommands[i]).name() << "    ";
            value << typeid(*offCommands[i]).name() << endl;
        }
        return value.str();
    }
private:
    static const int NUM_SLOTS = 7;
    Command* onCommands[NUM_SLOTS];
    Command* offCommands[NUM_SLOTS];
};

// RemoteLoader
int main()
{
    if (0) {
        RemoteControl* remoteControl = new RemoteControl();
        
        Light* livingRoomLight = new Light("Living Room");
        LightOnCommand* livingRoomLightOn = new LightOnCommand(livingRoomLight);
        LightOffCommand* livingRoomLightOff = new LightOffCommand(livingRoomLight);

        Light* kitchenLight = new Light("Kitchen");
        LightOnCommand* kitchenLightOn = new LightOnCommand(kitchenLight);
        LightOffCommand* kitchenLightOff = new LightOffCommand(kitchenLight);

        remoteControl->setCommand(0, livingRoomLightOn, livingRoomLightOff);
        remoteControl->setCommand(1, kitchenLightOn, kitchenLightOff);

        cout << remoteControl->toString() << endl;

        remoteControl->onButtonWasPushed(0);
        remoteControl->offButtonWasPushed(0);

        remoteControl->onButtonWasPushed(1);
        remoteControl->offButtonWasPushed(1);

        remoteControl->onButtonWasPushed(2);
        remoteControl->offButtonWasPushed(2);

        delete remoteControl;
        delete livingRoomLight, livingRoomLightOn, livingRoomLightOff;
        delete kitchenLight, kitchenLightOn, kitchenLightOff;
    }
    if (1) {
        auto& remoteControl = RemoteControl();
        
        auto& livingRoomLight = Light("Living Room");
        auto& livingRoomLightOn = LightOnCommand(&livingRoomLight);
        auto& livingRoomLightOff = LightOffCommand(&livingRoomLight);

        auto& kitchenLight = Light("Kitchen");
        auto& kitchenLightOn = LightOnCommand(&kitchenLight);
        auto& kitchenLightOff = LightOffCommand(&kitchenLight);

        remoteControl.setCommand(0, &livingRoomLightOn, &livingRoomLightOff);
        remoteControl.setCommand(1, &kitchenLightOn, &kitchenLightOff);

        cout << remoteControl.toString() << endl;

        remoteControl.onButtonWasPushed(0);
        remoteControl.offButtonWasPushed(0);

        remoteControl.onButtonWasPushed(1);
        remoteControl.offButtonWasPushed(1);

        remoteControl.onButtonWasPushed(2);
        remoteControl.offButtonWasPushed(2);
    }
    return 0;
}