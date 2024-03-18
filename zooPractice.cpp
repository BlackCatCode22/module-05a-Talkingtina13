#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <chrono> // For timestamps

// Animal class
class Animal {
protected:
    std::string name;
    int age;
    std::string species;
    std::chrono::system_clock::time_point arrivalTime; // Timestamp for arrival time
public:
    Animal(std::string name, int age, std::string species, std::chrono::system_clock::time_point arrivalTime)
        : name(name), age(age), species(species), arrivalTime(arrivalTime) {}
    // Getters
    std::string getName() const { return name; }
    int getAge() const { return age; }
    std::string getSpecies() const { return species; }
    std::chrono::system_clock::time_point getArrivalTime() const { return arrivalTime; } // Getter for arrival time
};

// Subclasses
class Hyena : public Animal {
public:
    Hyena(std::string name, int age, std::chrono::system_clock::time_point arrivalTime) 
        : Animal(name, age, "Hyena", arrivalTime) {}
};

class Lion : public Animal {
public:
    Lion(std::string name, int age, std::chrono::system_clock::time_point arrivalTime) 
        : Animal(name, age, "Lion", arrivalTime) {}
};

class Tiger : public Animal {
public:
    Tiger(std::string name, int age, std::chrono::system_clock::time_point arrivalTime) 
        : Animal(name, age, "Tiger", arrivalTime) {}
};

class Bear : public Animal {
public:
    Bear(std::string name, int age, std::chrono::system_clock::time_point arrivalTime) 
        : Animal(name, age, "Bear", arrivalTime) {}
};

int main() {
    std::vector<Animal*> animals;
    std::map<std::string, int> speciesCount;

    // Read animal names from animalNames.txt
    std::ifstream animalNamesFile("animalNames.txt");
    std::vector<std::string> animalNames;
    std::string name;
    while (animalNamesFile >> name) {
        animalNames.push_back(name);
    }
    animalNamesFile.close();

    // Generate random ages for animals
    srand(time(NULL)); // Seed for random number generator
    int maxAge = 15; // Maximum age for animals
    int minAge = 1;  // Minimum age for animals

    // Read animal details from arrivingAnimals.txt
    std::ifstream arrivingAnimalsFile("arrivingAnimals.txt");
    std::string animalType;
    while (arrivingAnimalsFile >> animalType) {
        // Generate random age
        int age = rand() % (maxAge - minAge + 1) + minAge;

        // Create timestamp for arrival time
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

        // Create animal object based on type
        if (animalType == "Hyena") {
            animals.push_back(new Hyena(animalNames[rand() % animalNames.size()], age, now));
        } else if (animalType == "Lion") {
            animals.push_back(new Lion(animalNames[rand() % animalNames.size()], age, now));
        } else if (animalType == "Tiger") {
            animals.push_back(new Tiger(animalNames[rand() % animalNames.size()], age, now));
        } else if (animalType == "Bear") {
            animals.push_back(new Bear(animalNames[rand() % animalNames.size()], age, now));
        }

        // Count species
        speciesCount[animalType]++;
    }
    arrivingAnimalsFile.close();

    // Write report to newAnimals.txt
    std::ofstream reportFile("newAnimals.txt");
    for (auto& animal : animals) {
        std::time_t arrivalTime = std::chrono::system_clock::to_time_t(animal->getArrivalTime());
        reportFile << "Name: " << animal->getName() << ", Age: " << animal->getAge() << ", Species: " << animal->getSpecies()
                   << ", Arrival Time: " << std::ctime(&arrivalTime);
        delete animal; // Free memory
    }
    reportFile << "Species Count:\n";
    for (const auto& pair : speciesCount) {
        reportFile << pair.first << ": " << pair.second << std::endl;
    }
    reportFile.close();

    return 0;
}
