#include <string>

class DatabaseHandler
{
private:
    const std::string _cafcin = "Caffe-and-cinema.csv";
    const std::string _costs = "Costs.csv";
    const std::string _inst = "Institute.csv";
    const std::string _tr = "Transport.csv"; // пути чтобы был класс
    std::string _directoryPath;
public:
    DatabaseHandler();
    DatabaseHandler(const std::string& directoryPath);
    void SetPath(const std::string& path);
    unsigned int getTransportCost(const std::string& city, const std::string& homeAddress,
                      const std::string& institute) const;
    unsigned int getInstituteDinnerCost(const std::string& city, const std::string& institute) const;
    unsigned int getCoffeeCost(const std::string& city, const std::string& coffee) const;
    unsigned int getCinemaCost(const std::string& city, const std::string& cinema) const;
    unsigned int getHomeFoodCost(const std::string& city, unsigned int age, unsigned int month) const;
    unsigned int getOtherMontlyCosts(unsigned int month, const std::string& city, unsigned int age) const;
    unsigned int getDaysCount(unsigned int month) const;
    unsigned int getWorkdays(unsigned int month) const;
    std::string getCafcin() const;
    std::string getCosts() const;
    std::string getInst() const;
    std::string getTr() const;
};