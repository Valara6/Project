#ifndef MOORE_H
#define MOORE_H



#include <QString>

using namespace std;

// Определение множества состояний
enum State { State1, State2, State3 };

// Определение входного алфавита
enum Input { InputA, InputB };

// Определение функции перехода
State nextState(State currentState, Input input);

// Определение функции выхода
char mooreOutput_2(State state);

// Обработка входной цепочки
QString processInput(QString input);

QString maint(const QString& string1);
#endif // MOORE_H
