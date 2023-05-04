#include <string>
#include "DatabaseHandler.h"

class Student
{
private:
    unsigned int age;
    std::string city;
    std::string homeAddress;
    std::string institute;
public:
    Student();
    Student(unsigned int age, const std::string& city, const std::string& homeAddress, const std::string& institute);
    void setAge(unsigned int ag);
    void setCity(const std::string& cit);
    void setHomeAdress(const std::string& homeAdres);
    void setInstitute(const std::string& institut);
    void setAge();
    void setCity();
    void setHomeAdress();
    void setInstitute();

    unsigned int getCosts(unsigned int month, const std::string& city, const std::string& homeAddress, 
              const std::string& institute, const std::string& cinema,
              const std::string& coffee, unsigned int age, const DatabaseHandler& base) const;
    unsigned int getWorkdayCost(const std::string& city, const std::string& homeAddress,
                    const std::string& institute, unsigned int age, unsigned int month, const DatabaseHandler& base) const;
    unsigned int getWeekandCost(const std::string& city, const std::string& cinema,
                    const std::string& coffee, unsigned int age, unsigned int month, const DatabaseHandler& base) const;
    

    unsigned int getAge() const; // константный метод
    std::string getCity() const;
    std::string getHomeAdress() const;
    std::string getInstitute() const;
};