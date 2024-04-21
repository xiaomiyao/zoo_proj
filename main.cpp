class Animal { //base class that other classes will inherit from
protected:
    std::string name;
    int age;
public:
    Animal(string name, int age) : name(name), age(age) {}

    virtual void feed() = 0; //abstraction
    virtual void speak() = 0; //abstraction. each derived class will provide its own implementation

    string getName() { return name; }
    int getAge() { return age; }
};

class Lion : public Animal {
public:
    Lion(string name, int age) : Animal(name, age) {}
    void feed() override {
        std::cout << "Feeding the lion meat." << std::endl;
    }
    void speak() override {
        std::cout << "The lion roars." << std::endl;
    }
};

class Elephant : public Animal {
public:
    Elephant(string name, int age) : Animal(name, age) {}
    void feed() override {
        std::cout << "Feeding the elephant fruits and vegetables." << std::endl;
    }
    void speak() override {
        std::cout << "The elephant trumpets." << std::endl;
    }
};

class Bird : public Animal {
public:
    Bird(std::string name, int age) : Animal(name, age) {}

    void feed() override {
        std::cout << "Feeding the bird seeds." << std::endl;
    }

    void speak() override {
        std::cout << "The bird sings." << std::endl;
    }
};

class Zoo {
private:
    std::vector<std::shared_ptr<Animal>> animals;

public:
    void addAnimal(std::shared_ptr<Animal> animal) {
        animals.push_back(animal);
        std::cout << animal->getName() << " has been added to the zoo." << std::endl;
    }

    // Remove an animal from the zoo by name
    bool removeAnimal(const std::string& name) {
        auto it = std::remove_if(animals.begin(), animals.end(), [&name](const std::shared_ptr<Animal>& animal) {
            return animal->getName() == name;
            });
        if (it != animals.end()) {
            std::cout << (*it)->getName() << " has been removed from the zoo." << std::endl;
            animals.erase(it, animals.end());
            return true;
        }
        std::cout << "No animal named " << name << " found in the zoo." << std::endl;
        return false;
    }
};








int main()
{
    Zoo zoo;

    std::shared_ptr<Animal> lion = std::make_shared<Lion>("Leo", 5);
    std::shared_ptr<Animal> elephant = std::make_shared<Elephant>("Ella", 10);
    std::shared_ptr<Animal> bird = std::make_shared<Bird>("Bella", 2);

    zoo.addAnimal(lion);
    zoo.addAnimal(elephant);
    zoo.addAnimal(bird);

    zoo.removeAnimal("Ella");
    return 0;
}