#include "CombatLogParser.h"
#include <iostream>
#include <fstream>
#include <sstream>

CombatLogParser::CombatLogParser(const std::string& path) : logFilePath(path) {}

CombatLogParser::~CombatLogParser() {}

bool CombatLogParser::readLatestLogs() {
    std::ifstream file(logFilePath);
    if (!file.is_open()) {
        std::cerr << "[Error] Failed to open Rust combat log file." << std::endl;
        return false;
    }

    std::string line;

    parsedEntries.clear(); 

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        LogEntry entry;
        std::string damageStr;

        if (ss >> entry.timestamp >> entry.attacker >> entry.target >> entry.weapon >> damageStr >> entry.area) {
            try {
                entry.damage = std::stod(damageStr);
            } catch (...) {
                entry.damage = 0.0;
            }
            parsedEntries.push_back(entry);
        }
    }

    file.close();
    return true;
}

void CombatLogParser::clearCache() {
    parsedEntries.clear();
}

std::vector<LogEntry> CombatLogParser::getEntriesByAttacker(const std::string& attackerName) const {
    std::vector<LogEntry> result;
    for (const auto& entry : parsedEntries) {
        if (entry.attacker == attackerName) {
            result.push_back(entry);
        }
    }
    return result;
}

void CombatLogParser::printLatestHits() const {
    if (parsedEntries.empty()) {
        std::cout << "[Info] No new hits recorded." << std::endl;
        return;
    }

    std::cout << "--- Latest Combat Events ---" << std::endl;
    for (const auto& entry : parsedEntries) {
        std::cout << "[" << entry.timestamp << "] " 
                  << entry.attacker << " -> " << entry.target 
                  << " | Damage: " << entry.damage << " (" << entry.area << ")" << std::endl;
    }
}