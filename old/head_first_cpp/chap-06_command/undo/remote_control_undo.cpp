#include <iostream>
#include <sstream>
#include <string>
using namespace std;


// Interface
struct Command {
    virtual ~Command() = default;
    virtual void excute() = 0;
    virtual void undo() = 0;
};

struct NoCommand : Command {
    void excute() override { cout << "NoCommand::execute\n"; }
    void undo() override { cout << "NoCommand::undo\n"; }
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
    void undo() override { light->off(); }
private:
    Light* light;
};

struct LightOffCommand : Command {
    LightOffCommand(Light* light) { this->light = light; }
    // ~LightOffCommand() { delete light; }
    void excute() override { light->off(); }
    void undo() override { light->on(); }
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
        undoCommand = noCommand;
    }

    void setCommand(int slot, Command* onCommand, Command* offCommand) {
        onCommands[slot] = onCommand;
        offCommands[slot] = offCommand;
    }
    void onButtonWasPushed(int slot) {
        onCommands[slot]->excute();
        undoCommand = onCommands[slot];
    }
    void offButtonWasPushed(int slot) {
        offCommands[slot]->excute();
        undoCommand = offCommands[slot];
    }
    void undoButtonWasPushed() {
        undoCommand->undo();
    }
    string toString() {
        stringstream value;
        value << "\n------ Remote Control -------\n" << endl;
        for (int i = 0; i < NUM_SLOTS; i++) {
            value << "[slot " << i << "] ";
            value << typeid(*onCommands[i]).name() << "    ";
            value << typeid(*offCommands[i]).name() << endl;
        }
        value << typeid(*undoCommand).name() << endl;
        return value.str();
    }
private:
    static const int NUM_SLOTS = 7;
    Command* onCommands[NUM_SLOTS];
    Command* offCommands[NUM_SLOTS];
    Command* undoCommand;
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

        remoteControl->onButtonWasPushed(0);
        remoteControl->offButtonWasPushed(0);

        cout << remoteControl->toString() << endl;
        remoteControl->undoButtonWasPushed();

        remoteControl->onButtonWasPushed(1);
        remoteControl->offButtonWasPushed(1);
        remoteControl->undoButtonWasPushed();

        remoteControl->onButtonWasPushed(2);
        remoteControl->offButtonWasPushed(2);
        remoteControl->undoButtonWasPushed();

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

        remoteControl.onButtonWasPushed(0);
        remoteControl.offButtonWasPushed(0);

        cout << remoteControl.toString() << endl;
        remoteControl.undoButtonWasPushed();

        remoteControl.onButtonWasPushed(1);
        remoteControl.offButtonWasPushed(1);

        remoteControl.onButtonWasPushed(2);
        remoteControl.offButtonWasPushed(2);
    }
    return 0;
}