// 11_04zoo_classes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include<vector>
#include <memory>
using namespace std;



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

    }
};











int main()
{

}

