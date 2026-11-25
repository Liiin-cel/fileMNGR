
#include "Logger.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;
using timepoint=   std::chrono::time_point<std::chrono::high_resolution_clock>
using namespace std.chrono;

    // Вспомогательная функция для формирования текущей метки времени: ГГГГ-ММ-ДД ЧЧ:ММ:СС
    string currentTimestamp() {
        timepoint now = system_clock::now();
        time_t nowTime = system_clock::to_time_t(now);

        tm localTm{};
#if defined(_WIN32)
        localtime_s(&localTm, &nowTime);
#else
        localtime_r(&nowTime, &localTm);
#endif

        ostringstream oss;
        oss << put_time(&localTm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }


Logger::Logger(const string& filename, bool printToConsole)
    : alsoPrintToConsole(printToConsole) {
    // Открываем файл в режиме дозаписи (app), чтобы сохранять историю запусков
    logFile.open(filename, ios::app);
    if (!logFile.is_open()) {
        cerr << "[ERROR] Не удалось открыть файл лога: " << filename << "\n";
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const string& level, const string& message) {
    string line = "[" + currentTimestamp() + "] [" + level + "] " + message;

    if (logFile.is_open()) {
        logFile << line << "\n";
        logFile.flush();
    }

    if (alsoPrintToConsole) {
        if (level == "ERROR") {
            cerr << line << "\n";
        }
        else {
            cout << line << "\n";
        }
    }
}

void Logger::info(const string& message) {
    log("INFO", message);
}

void Logger::warn(const string& message) {
    log("WARN", message);
}

void Logger::error(const string& message) {
    log("ERROR", message);
}