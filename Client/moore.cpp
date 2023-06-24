#include "moore.h"



#include <QString>

using namespace std;

// Определение множества состояний


// Определение функции перехода
State nextState(State currentState, Input input) {
    switch (currentState) {
    case State1:
        return (input == InputA) ? State2 : State1;
    case State2:
        return (input == InputB) ? State3 : State2;
    case State3:
        return (input == InputA) ? State1 : State3;
    }
}

// Определение функции выхода
char mooreOutput_2(State state) {
    switch (state) {
    case State1: return 'A';
    case State2: return 'B';
    case State3: return 'C';
    }
}

// Обработка входной цепочки
QString processInput(QString input) {
    State currentState = State1;
    QString res="";
    for (QChar c : input) {
        Input currentInput = (c == 'A') ? InputA : InputB;
        char output = mooreOutput_2(currentState);
        res+=output;
        currentState = nextState(currentState, currentInput);
    }
    return res;
}

QString maint(const QString& string1) {
    QString input = string1;
    QString result=processInput(input);
    return result;
}
