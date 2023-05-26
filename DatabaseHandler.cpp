#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include "DatabaseHandler.h"

DatabaseHandler::DatabaseHandler(): _directoryPath("") {}

DatabaseHandler::DatabaseHandler(const std::string& directoryPath): _directoryPath(directoryPath) {}

void DatabaseHandler::setPath(const std::string& path)  {
    _directoryPath = path;
}

void DatabaseHandler::initDatabase() {
    std::vector<std::string> failedFiles;
    std::ifstream cafcinFile(_directoryPath + '/' + _cafcin);
    if (!cafcinFile.is_open()) {
        failedFiles.push_back(_cafcin);
    }
    std::ifstream costsFile(_directoryPath + '/' + _costs);
    if (!costsFile.is_open()) {
        failedFiles.push_back(_costs);
    }
    std::ifstream instFile(_directoryPath + '/' + _inst);
    if (!instFile.is_open()) {
        failedFiles.push_back(_inst);
    }
    std::ifstream trFile(_directoryPath + '/' + _tr);
    if (!trFile.is_open()) {
        failedFiles.push_back(_tr);
    }
    if (!failedFiles.empty()) {
        std::string failedFilesString;
        for (size_t i = 0; i < failedFiles.size(); ++i) {
                failedFilesString += failedFiles[i];
                if (i != failedFiles.size() - 1) {
                    failedFilesString += ", ";
                }
        }

        throw FileOpenException(failedFilesString);
    }

    readCSV(cafcinFile, _cafcinData);
    readCSV(costsFile, _costsData);
    readCSV(instFile, _instData);
    readCSV(trFile, _trData);


    cafcinFile.close();
    costsFile.close();
    instFile.close();
    trFile.close();
}

void DatabaseHandler::readCSV(std::ifstream& file, std::vector<std::vector<std::string>>& vectorData, char delimiter) {
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, delimiter)) {
            row.push_back(cell);
        }

        vectorData.push_back(row);
    }
}

std::vector<std::vector<std::string>>& DatabaseHandler::getcafcinData() {
        return _cafcinData;
}
std::vector<std::vector<std::string>>& DatabaseHandler::getcostsData() {
        return _costsData;
}
std::vector<std::vector<std::string>>& DatabaseHandler::getinstData() {
        return _instData;
}
std::vector<std::vector<std::string>>& DatabaseHandler::gettrData() {
        return _trData;
}


std::vector<std::string> DatabaseHandler::getCities() const {
    std::vector<std::string> v;
    for (size_t i = 1; i < _trData.size(); i++) {
        if (!_trData[i].empty() && (std::find(v.begin(), v.end(), _trData[i][0]) == v.end())) {
            v.push_back(_trData[i][0]);
        }
    }
    return v;
}

std::vector<std::string> DatabaseHandler::getAddresses() const {
    std::vector<std::string> v;
    for (size_t i = 1; i < _trData.size(); i++) {
        if (!_trData[i].empty() && (std::find(v.begin(), v.end(), _trData[i][1]) == v.end())) {
            v.push_back(_trData[i][1]);
        }
        }
    return v;
}

std::vector<std::string> DatabaseHandler::getInstitutes() const {
    std::vector<std::string> v;
    for (size_t i = 1; i < _instData.size(); i++) {
        if (!_instData[i].empty() && (std::find(v.begin(), v.end(), _instData[i][1]) == v.end())) {
            v.push_back(_instData[i][1]);
        }
    }
    return v;
}

std::vector<std::string> DatabaseHandler::getCafes() const {
    std::vector<std::string> v;
    for (size_t i = 1; i < _cafcinData.size(); i++) {
        if (!_cafcinData[i].empty() && (std::find(v.begin(), v.end(), _cafcinData[i][2]) == v.end())) {
            v.push_back(_cafcinData[i][2]);
        }
    }
    return v;
}

std::vector<std::string> DatabaseHandler::getCinemas() const {
    std::vector<std::string> v;
    for (size_t i = 1; i < _cafcinData.size(); i++) {
        if (!_cafcinData[i].empty() && (std::find(v.begin(), v.end(), _cafcinData[i][4]) == v.end())) {
            v.push_back(_cafcinData[i][4]);
        }
     }
    return v;
}

std::vector<unsigned int> DatabaseHandler::getAges() const {
    std::vector<unsigned int> v;
    for (size_t i = 1; i < _costsData.size(); i++) {
        if (!_costsData[i].empty() && (std::find(v.begin(), v.end(), stoi(_costsData[i][1])) == v.end())) {
            v.push_back(stoi(_costsData[i][1]));
        }
     }
    return v;
}

unsigned int DatabaseHandler::getWorkdays(unsigned int month) const {
    unsigned int wdayz[] = {17, 18, 22, 20, 20, 21, 21, 23, 21, 22, 21, 21};
    unsigned int wdays = wdayz[month - 1];
    return wdays;
}

unsigned int DatabaseHandler::getDaysCount(unsigned int month) const {
    unsigned int dayz[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    unsigned int days = dayz[month - 1];
    return days;
}

unsigned int DatabaseHandler::getHomeFoodCost(const std::string& city, unsigned int age, unsigned int month) const {
    auto foundIt = std::find_if(_costsData.begin(), _costsData.end(), [&](const std::vector<std::string>& innerVec) {
            return std::find(innerVec.begin(), innerVec.end(), city) != innerVec.end() &&
                   std::find(innerVec.begin(), innerVec.end(), std::to_string(age)) != innerVec.end();
    });
    if (foundIt == _costsData.end()) {
        std::cout << "There is no food cost for city: " << city << ", age: " << age << std::endl;
        exit(0);
    }
    const std::vector<std::string>& foundVector = *foundIt;
    return std::stoi(foundVector[2]) / getDaysCount(month);
}

unsigned int DatabaseHandler::getCinemaCost(const std::string& city, const std::string& cinema) const {
    auto foundIt = std::find_if(_cafcinData.begin(), _cafcinData.end(), [&](const std::vector<std::string>& innerVec) {
            return std::find(innerVec.begin(), innerVec.end(), city) != innerVec.end() &&
                   std::find(innerVec.begin(), innerVec.end(), cinema) != innerVec.end();
    });
    if (foundIt == _cafcinData.end()) {
        std::cout << "There is no cinema cost for city: " << city << ", cinema: " << cinema << std::endl;
        exit(0);
    }
    const std::vector<std::string>& foundVector = *foundIt;
    return std::stoi(foundVector[5]);
}

unsigned int DatabaseHandler::getCoffeeCost(const std::string& city, const std::string& coffee) const {
    auto foundIt = std::find_if(_cafcinData.begin(), _cafcinData.end(), [&](const std::vector<std::string>& innerVec) {
            return std::find(innerVec.begin(), innerVec.end(), city) != innerVec.end() &&
                   std::find(innerVec.begin(), innerVec.end(), coffee) != innerVec.end();
    });
    if (foundIt == _cafcinData.end()) {
        std::cout << "There is no coffee cost for city: " << city << ", coffee: " << coffee << std::endl;
        exit(0);
    }
    const std::vector<std::string>& foundVector = *foundIt;
    return std::stoi(foundVector[3]);
}

unsigned int DatabaseHandler::getTransportCost(const std::string& city, const std::string& homeAddress,
                      const std::string& institute) const {
    auto foundIt = std::find_if(_trData.begin(), _trData.end(), [&](const std::vector<std::string>& innerVec) {
            return std::find(innerVec.begin(), innerVec.end(), city) != innerVec.end() &&
                   std::find(innerVec.begin(), innerVec.end(), homeAddress) != innerVec.end() &&
                   std::find(innerVec.begin(), innerVec.end(), institute) != innerVec.end();
    });
    if (foundIt == _trData.end()) {
        std::cout << "There is no transport cost for city: " << city << ", home address: " << homeAddress << ", institute: " << institute << std::endl;
        exit(0);
    }
    const std::vector<std::string>& foundVector = *foundIt;
    return std::stoi(foundVector[3]);
}

unsigned int DatabaseHandler::getInstituteDinnerCost(const std::string& city, const std::string& institute) const {
    auto foundIt = std::find_if(_instData.begin(), _instData.end(), [&](const std::vector<std::string>& innerVec) {
            return std::find(innerVec.begin(), innerVec.end(), city) != innerVec.end() &&
                   std::find(innerVec.begin(), innerVec.end(), institute) != innerVec.end();
    });
    if (foundIt == _instData.end()) {
        std::cout << "There is no institute dinner cost for city: " << city << ", institute: " << institute << std::endl;
        exit(0);
    }
    const std::vector<std::string>& foundVector = *foundIt;
    return std::stoi(foundVector[2]);
}

unsigned int DatabaseHandler::getOtherMontlyCosts(unsigned int month, const std::string& city, unsigned int age) const {
    auto foundIt = std::find_if(_costsData.begin(), _costsData.end(), [&](const std::vector<std::string>& innerVec) {
            return std::find(innerVec.begin(), innerVec.end(), city) != innerVec.end() &&
                   std::find(innerVec.begin(), innerVec.end(), std::to_string(age)) != innerVec.end();
    });
    if (foundIt == _costsData.end()) {
        std::cout << "There is no other montly cost for city: " << city << ", age: " << age << std::endl;
        exit(0);
    }
    const std::vector<std::string>& foundVector = *foundIt;
    return std::stoi(foundVector[3]);
}

std::string DatabaseHandler::getCafcin() const {
    return _cafcin;
}

std::string DatabaseHandler::getCosts() const {
    return _costs;
}

std::string DatabaseHandler::getInst() const {
    return _inst;
}

std::string DatabaseHandler::getTr() const {
    return _tr;
}

std::string DatabaseHandler::getPath() const {
    return _directoryPath;
}
