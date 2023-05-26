#include <string>
#include <vector>
#include <stdexcept>

class DatabaseHandler
{
private:
    const std::string _cafcin = "Caffe-and-cinema.csv";
    const std::string _costs = "Costs.csv";
    const std::string _inst = "Institute.csv";
    const std::string _tr = "Transport.csv";
    std::string _directoryPath;
    std::vector<std::vector<std::string>> _cafcinData;
    std::vector<std::vector<std::string>> _costsData;
    std::vector<std::vector<std::string>> _instData;
    std::vector<std::vector<std::string>> _trData;
public:
    class FileOpenException : public std::runtime_error {
    public:
        FileOpenException(const std::string& filename)
            : std::runtime_error("Failed to open file: " + filename), filename_(filename) {}

        std::string getFilename() const {
            return filename_;
        }

    private:
        std::string filename_;
    };
    DatabaseHandler();
    DatabaseHandler(const std::string& directoryPath);
    void setPath(const std::string& path);
    void initDatabase();
    void readCSV(std::ifstream& file, std::vector<std::vector<std::string>>& vectorData, char delimiter = ',');
    std::vector<std::vector<std::string>>& getcafcinData();
    std::vector<std::vector<std::string>>& getcostsData();
    std::vector<std::vector<std::string>>& getinstData();
    std::vector<std::vector<std::string>>& gettrData();

    std::vector<std::string> getCities() const;
    std::vector<std::string> getAddresses() const;
    std::vector<std::string> getInstitutes() const;
    std::vector<std::string> getCafes() const;
    std::vector<std::string> getCinemas() const;
    std::vector<unsigned int> getAges() const;
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
    std::string getPath() const;
};
