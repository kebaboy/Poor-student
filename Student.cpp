#include <string>
#include <iostream>
#include "Student.h"


Student::Student() {
//    setAge();
//    setCity();
//    setHomeAdress();
//    setInstitute();
}

Student::Student(unsigned int age, const std::string& city, const std::string& homeAddress, const std::string& institute) :
                 age(age), city(city), homeAddress(homeAddress), institute(institute) {}

void Student::setAge(unsigned int ag) {
    age = ag;
}

void Student::setCity(const std::string& cit) {
    city = cit;
}

void Student::setHomeAdress(const std::string& homeAdres) {
    homeAddress = homeAdres;
}

void Student::setInstitute(const std::string& institut) {
    institute = institut;
}

void Student::setAge() {
    unsigned int ag;
    std::cout << "What age is it?" << std::endl;
    std::cin >> ag;
    age = ag;
}

void Student::setCity() {
    std::string cit;
    std::cout << "What city is it?" << std::endl;
    std::cin >> cit;
    city = cit;
}

void Student::setHomeAdress() {
    std::string homeAddres;
    std::cout << "What address is it?" << std::endl;
    std::cin >> homeAddres;
    homeAddress = homeAddres;
}

void Student::setInstitute() {
    std::string institut;
    std::cout << "What institute is it?" << std::endl;
    std::cin >> institut;
    institute = institut;
}

unsigned int Student::getCosts(unsigned int month, const std::string& city, const std::string& homeAddress, 
              const std::string& institute, const std::string& cinema,
              const std::string& coffee, unsigned int age, const DatabaseHandler& base) const {

    const unsigned int daysCount = base.getDaysCount(month);
    const unsigned int workDays = base.getWorkdays(month);
    const unsigned int weekends = daysCount - workDays;

    return workDays * getWorkdayCost(city, homeAddress, institute, age, month, base) +
           weekends * getWeekandCost(city, cinema, coffee, age, month, base) + 
           base.getOtherMontlyCosts(month, city, age);
}

unsigned int Student::getWeekandCost(const std::string& city, const std::string& cinema,
                    const std::string& coffee, unsigned int age, unsigned int month, const DatabaseHandler& base) const {
    std::cout << "getWeekendCost: 0.66 * " << base.getHomeFoodCost(city, age, month) << " + " << base.getCinemaCost(city, cinema) << " + " << base.getCoffeeCost(city, coffee) << " + 0.5\n";
    return static_cast<unsigned int>(0.66 * base.getHomeFoodCost(city, age, month) + 
        base.getCinemaCost(city, cinema) + base.getCoffeeCost(city, coffee) + 0.5);
}

unsigned int Student::getWorkdayCost(const std::string& city, const std::string& homeAddress,
                    const std::string& institute, unsigned int age, unsigned int month, const DatabaseHandler& base) const {
    std::cout << "getWorkdayCost: 2 * " << base.getTransportCost(city, homeAddress, institute) << " + " << base.getInstituteDinnerCost(city, institute) << " + 0.66 * " << base.getHomeFoodCost(city, age, month) << " + 0.5\n";
    return static_cast<unsigned int>(2 * base.getTransportCost(city, homeAddress, institute) +
        base.getInstituteDinnerCost(city, institute) + 0.66 * base.getHomeFoodCost(city, age, month) + 0.5);
}

unsigned int Student::getAge() const {
    return age;
}

std::string Student::getCity() const {
    return city;
}

std::string Student::getHomeAdress() const {
    return homeAddress;
}

std::string Student::getInstitute() const {
    return institute;
}
