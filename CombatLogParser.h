#pragma once
#include <string>
#include <vector>

struct LogEntry {
    std::string timestamp;
    std::string attacker;
    std::string target;
    std::string weapon;
    double damage;
    std::string area;
};

class CombatLogParser {
private:
    std::string logFilePath;
    std::vector<LogEntry> parsedEntries;

public:
    CombatLogParser(const std::string& path);
    ~CombatLogParser();

    bool readLatestLogs();
    void clearCache();
    
    std::vector<LogEntry> getEntriesByAttacker(const std::string& attackerName) const;
    void printLatestHits() const;
};