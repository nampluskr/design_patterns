#include <iostream>
#include <vector>
using namespace std;


// Command 인터페이스
struct Command {
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0; // undo 기능 추가
};

// Receiver 클래스 (실제 작업을 수행)
struct Receiver {
    void action1() { cout << "Receiver: Action 1 수행\n"; }
    void action2() { cout << "Receiver: Action 2 수행\n"; }
};

// CommandA 클래스
struct CommandA : Command {
    CommandA(Receiver* receiver) { _receiver = receiver; } 
    void execute() override { _receiver->action1(); }
    void undo() override { cout << "CommandA: undo 수행 (Action 1 취소)\n"; }
private:
    Receiver* _receiver;
};

// CommandB 클래스
struct CommandB : Command {
    CommandB(Receiver* receiver) { _receiver = receiver; }
    void execute() override { _receiver->action2(); }
    void undo() override { cout << "CommandB: undo 수행 (Action 2 취소)\n"; }
private:
    Receiver* _receiver;
};

// Invoker 클래스 (명령을 실행)
struct Invoker {
    ~Invoker(){ for(Command * command : _commands) delete command; }

    void setCommand(Command* command) { _commands.push_back(command); }
    void executeCommands() { for (Command* command : _commands) command->execute(); }
    void undoCommands(){
        for (int i = _commands.size() - 1; i >= 0; i--) 
            _commands[i]->undo();
    }
private:
    vector<Command*> _commands; // 명령들을 저장하는 벡터
};

int main()
{
    Receiver receiver;
    Invoker invoker;

    Command* command1 = new CommandA(&receiver);
    Command* command2 = new CommandB(&receiver);

    invoker.setCommand(command1);
    invoker.setCommand(command2);

    invoker.executeCommands();
    cout << endl;
    invoker.undoCommands();

    delete command1;
    delete command2;

    return 0;
}