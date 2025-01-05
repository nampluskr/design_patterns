// Originator (원조자): 내부 상태를 가지고 있으며, 상태를 저장하고 복원하는 메서드를 제공합니다.
// Memento (메멘토): Originator의 상태를 저장하는 객체입니다. 외부에서는 Memento의 내부 상태에 직접 접근할 수 없습니다.
// Caretaker (관리자): Memento 객체를 저장하고 관리합니다. Originator의 상태 복원을 요청할 때 Memento를 Originator에게 전달합니다.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Memento (메멘토)
struct Memento {
    Memento(const string& state) { _state = state; } // const 참조로 받음
    string getState() const { return _state; }
private:
    string _state;
};

// Originator (원조자)
struct Originator {
    void setState(const string& state) { // const 참조로 받음
        cout << "Originator: Setting state to " << state << endl;
        _state = state;
    }
    Memento* createMemento() const { // 포인터 반환
        cout << "Originator: Creating Memento of current State.\n";
        return new Memento(_state); // 동적 할당
    }
    void restoreFromMemento(const Memento* memento) { // const 포인터로 받음
        if (memento) { // null 체크 추가
            _state = memento->getState();
            cout << "Originator: State after restoring from Memento: " << _state << endl;
        } else {
            cerr << "Error: Null Memento pointer.\n";
        }
    }
    void showState() const {
        cout << "Current State: " << _state << endl;
    }
private:
    string _state;
};

// Caretaker (관리자)
struct Caretaker {
    ~Caretaker(){ for(Memento* memento : _mementos) delete memento; }   // 소멸자에서 메모리 해제
    void addMemento(Memento* memento) {       // 포인터 받음
        _mementos.push_back(memento);
        current_index++; // 추가할 때마다 인덱스 증가
    }
    Memento* getMemento(int index) const {      // 포인터 반환
        if (index >= 0 && index < _mementos.size()) {
            return _mementos[index];
        } else {
            cerr << "Invalid Memento index.\n";
            return nullptr; // null 반환
        }
    }
    void undo(Originator* originator) { // undo 메서드 추가
        if (current_index > 0) {
            current_index--; // 이전 인덱스로 이동
            Memento* memento = _mementos[current_index];
            originator->restoreFromMemento(memento);
        } else {
            cout << "No more states to undo." << endl;
        }
    }
    void redo(Originator* originator){
        if(current_index < _mementos.size() -1){
            current_index++;
            Memento* memento = _mementos[current_index];
            originator->restoreFromMemento(memento);
        } else {
            cout << "No more states to redo." << endl;
        }
    }
    void showCurrentIndex(){
        cout << "Current index: " << current_index << endl;
    }
private:
    vector<Memento*> _mementos; // Memento 포인터 저장
    int current_index = -1;     // 현재 Memento 인덱스 추가
};


int main()
{
    Originator originator;
    Caretaker caretaker;

    originator.setState("State #1");
    caretaker.addMemento(originator.createMemento());
    caretaker.showCurrentIndex();

    originator.setState("State #2");
    caretaker.addMemento(originator.createMemento());
    caretaker.showCurrentIndex();

    originator.setState("State #3");
    caretaker.addMemento(originator.createMemento());
    caretaker.showCurrentIndex();

    cout << endl << "Now lets restore the state:" << endl;

    caretaker.undo(&originator); // undo 실행 (State #2로 복원)
    originator.showState();
    caretaker.showCurrentIndex();

    caretaker.undo(&originator); // undo 실행 (State #1로 복원)
    originator.showState();
    caretaker.showCurrentIndex();

    caretaker.undo(&originator); // undo 실행 (더 이상 undo할 상태 없음)
    originator.showState();
    caretaker.showCurrentIndex();

    cout << endl << "Now lets redo the state:" << endl;
    caretaker.redo(&originator);
    originator.showState();
    caretaker.showCurrentIndex();
    caretaker.redo(&originator);
    originator.showState();
    caretaker.showCurrentIndex();
    caretaker.redo(&originator);
    originator.showState();
    caretaker.showCurrentIndex();
    caretaker.redo(&originator);
    originator.showState();
    caretaker.showCurrentIndex();

    return 0;
}