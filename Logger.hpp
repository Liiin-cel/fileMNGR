#pragma once


#include <fstream>
#include <string>

using namespace std;

class Logger {
private:
    ofstream logFile;
    bool alsoPrintToConsole;

public:
    // Конструктор
    explicit Logger(const string& filename, bool printToConsole = true);

    // Деструктор
    ~Logger();

    // Запрет копирования
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;


    void log(const string& level, const string& message);

    // Частые методы
    void info(const string& message);
    void warn(const string& message);
    void error(const string& message);
};