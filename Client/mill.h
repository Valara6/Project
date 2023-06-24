#ifndef MILL_H
#define MILL_H
#include <QString>

using namespace std;
enum State_mili { State1_mili, State2_mili, State3_mili };

// Определение функции выхода
char mooreOutput(State_mili state) ;
State_mili nextState_mili(State_mili currentState, QChar input);
QString processInput_mili(QString input);
QString maint_mili(const QString& string);
#endif // MILL_H
