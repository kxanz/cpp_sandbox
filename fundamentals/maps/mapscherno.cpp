#include <iostream>
#include <vector>

#include <map>
#include <unordered_map>
#include <string>

struct CityRecord 
{
    std::string Name;
    uint64_t Population;
    double Latitude, Longitude;

    bool operator<(const CityRecord)
};

namespace std {
    
    template<>
    struct hash<CityRecord>
    {
        size_t operator()(CityRecord& key)
        {
            return hash<std::string>()(key.Name);
        }
    };
}

int main() {

    std::unordered_map<CityRecord, uint32_t> foundedMap;

    foundedMap[CityRecord{"Melbourne, 500000, 2,4, 9.4"}] = 1850;

    std::unordered_map<std::string, CityRecord> cityMap;
    cityMap["Melbourne"] = CityRecord { "Melbourne", 5000000, 2.4, 9.4};
    cityMap["Lol-town"] = CityRecord { "Lol-town", 5000000, 2.4, 9.4}; 
    //cityMap["Berlin"] = CityRecord { "Berlin", 5000000, 2.4, 9.4}; 
    cityMap["Paris"] = CityRecord { "Paris", 5000000, 2.4, 9.4}; 
    cityMap["London"] = CityRecord { "London", 5000000, 2.4, 9.4}; 

    cityMap.erase("Paris");
    
    const auto& cities = cityMap;
    if (cities.find("Berlin") != cities.end())
    {
        const CityRecord& berlinData = cities.at("Berlin");
    }

    for (auto&[name, city] : cityMap)
    {
        std::cout << name << "\n Population: " << city.Population << std::endl;
    }

    CityRecord berlinData;
    berlinData.Name = "Berlin";
    berlinData.Population = 5;
    cityMap["Berlin"] = berlinData;
}