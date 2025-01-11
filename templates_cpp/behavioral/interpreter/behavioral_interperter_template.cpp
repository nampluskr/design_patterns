#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
using namespace std;


// 전방 선언
struct Context;

// Expression 인터페이스
struct Expression {
    virtual ~Expression() = default;
    virtual int interpret(Context& context) = 0;
    virtual void print(ostream& os) const = 0;
};

// NumberExpression (숫자 표현식)
struct NumberExpression : Expression {
    NumberExpression(int number) : _number(number) {}
    int interpret(Context& context) override { return _number; }
    void print(ostream& os) const override { os << _number; }
private:
    int _number;
};

// PlusExpression (덧셈 표현식)
struct PlusExpression : Expression {
    PlusExpression(Expression* left, Expression* right) : _left(left), _right(right) {}
    ~PlusExpression(){
        delete _left;
        delete _right;
    }
    int interpret(Context& context) override {
        return _left->interpret(context) + _right->interpret(context);
    }
    void print(ostream& os) const override {
        os << "(";
        _left->print(os);
        os << " + ";
        _right->print(os);
        os << ")";
    }
private:
    Expression* _left;
    Expression* _right;
};

// MinusExpression (뺄셈 표현식)
struct MinusExpression : Expression {
    MinusExpression(Expression* left, Expression* right) : _left(left), _right(right) {}
    ~MinusExpression(){
        delete _left;
        delete _right;
    }
    int interpret(Context& context) override {
        return _left->interpret(context) - _right->interpret(context);
    }
    void print(ostream& os) const override {
        os << "(";
        _left->print(os);
        os << " - ";
        _right->print(os);
        os << ")";
    }
private:
    Expression* _left;
    Expression* _right;
};

// Context (문맥) - 현재 환경 정보를 저장
struct Context {
    Context(const string& input): _input(input), _currentPosition(0){}
    string getInput() const { return _input; }
    int getCurrentPosition() const { return _currentPosition; }
    void setCurrentPosition(int position){ _currentPosition = position; }
    int getCurrentToken() {
        if(_currentPosition < _input.length()){
            return _input[_currentPosition] - '0';
        }
        return -1;
    }
private:
    string _input;
    int _currentPosition;
};

Expression* parse(Context& context) {
    int currentToken = context.getCurrentToken();
    context.setCurrentPosition(context.getCurrentPosition() + 1);
    Expression* left = new NumberExpression(currentToken);

    if (context.getCurrentPosition() < context.getInput().length()){
        char op = context.getInput()[context.getCurrentPosition()];
        context.setCurrentPosition(context.getCurrentPosition() + 1);
        Expression* right = parse(context);
        if (op == '+') {
            return new PlusExpression(left, right);
        } else if (op == '-') {
            return new MinusExpression(left, right);
        } else {
            throw invalid_argument("Invalid operator");
        }
    }
    return left;
}

int main()
{
    string expressionStr;
    cout << "수식을 입력하세요 (예: 1+2-3): ";
    // cin >> expressionStr;
    expressionStr = "1+2-3+4";

    Context context(expressionStr);
    try{
        Expression* expression = parse(context);

        cout << "입력된 수식: ";
        expression->print(cout);
        cout << endl;

        int result = expression->interpret(context);
        cout << "결과: " << result << endl;
        delete expression;
    } catch(const invalid_argument& e){
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}