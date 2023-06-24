#include "mill.h"
#include <QString>



// Определение функции выхода
char mooreOutput(State_mili state) {
    switch (state) {
        case State2_mili:
            return 'B';
        case State3_mili:
            return 'C';
        case State1_mili:
            return 'A';
    }
}

// Определение функции перехода
State_mili nextState_mili(State_mili currentState, QChar input) {
    switch (currentState) {
        case State1_mili:
            return (input == '0') ? State2_mili : State3_mili;
        case State2_mili:
            return State1_mili;
        case State3_mili:
            return (input == '1') ? State1_mili : State3_mili;
    }
}

// Обработка входной цепочки
QString processInput_mili(QString input) {
    State_mili currentState = State1_mili;
    QString result="";
    for (QChar c : input) {
        char output = mooreOutput(currentState);
        result+=output;
        currentState = nextState_mili(currentState, c);
    }
    return result;
}

QString maint_mili(const QString& string) {
    QString result=processInput_mili(string);
    return result;
}

