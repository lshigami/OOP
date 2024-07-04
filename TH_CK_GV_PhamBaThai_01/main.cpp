#include <bits/stdc++.h>

using namespace std;

class Pet {
protected:
    string name;
    int age;
    double price;
public:
    Pet(string name, int age, double price);

    virtual void makeSound() = 0;

    virtual void displayInfo() = 0;
};

class Dog : public Pet {
private:
    string breed;
public:
    Dog(string name, int age, double price, string breed);

    void makeSound();

    void displayInfo();
};

class Cat : public Pet {
private:
    string color;
public:
    Cat(string name, int age, double price, string color);

    void makeSound();

    void displayInfo();
};

class Bird : public Pet {
private:
    double wingSpan;
public:
    Bird(string name, int age, double price, double wingSpan);

    void makeSound();

    void displayInfo();
};

Pet::Pet(std::string name, int age, double price) {
    this->name = name;
    this->age = age;
    this->price = price;
}

Dog::Dog(std::string name, int age, double price, std::string breed) : Pet(name, age, price) {
    this->breed = breed;
}

void Dog::makeSound() {
    cout << "Woof!" << endl;
}

void Dog::displayInfo() {
    cout <<fixed<<setprecision(1)<< std::left << std::setw(10) << "Dog" << " | "
         << std::setw(16) << name << " | "
         << std::setw(6) << age << " | "
         << std::setw(12) << price << " | "
         << std::setw(16) << breed << endl;

}

Cat::Cat(std::string name, int age, double price, std::string color) : Pet(name, age, price) {
    this->color = color;
}

void Cat::makeSound() {
    cout << "Meow!" << endl;
}

void Cat::displayInfo() {
    cout <<fixed<<setprecision(1)<< std::left << std::setw(10) << "Cat" << " | "
         << std::setw(16) << name << " | "
         << std::setw(6) << age << " | "
         << std::setw(12) << price << " | "
         << std::setw(16) << color << endl;

}

Bird::Bird(std::string name, int age, double price, double wingSpan) : Pet(name, age, price) {
    this->wingSpan = wingSpan;
}

void Bird::makeSound() {
    cout << "Chirp!" << endl;
}

void Bird::displayInfo() {
    cout <<fixed<<setprecision(1)<< std::left << std::setw(10) << "Bird" << " | "
         << std::setw(16) << name << " | "
         << std::setw(6) << age << " | "
         << std::setw(12) << price << " | "
         << std::setw(16) << wingSpan << endl;

}

class PetStore{
private:
    vector<Pet*> pets;
public:
    void addPet(Pet* pet);
    void display();
};
void PetStore::addPet(Pet *pet) {
    pets.push_back(pet);
}
void PetStore::display() {
    std::cout << std::left << std::setw(10) << "Type" << " | "
              << std::setw(16) << "Name" << " | "
              << std::setw(6) << "Age" << " | "
              << std::setw(12) << "Price" << " | "
              << std::setw(16) << "Special" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    for (Pet* pet : pets) {
        pet->displayInfo();
    }
}



class IParsable{
public:
    virtual Pet* parse(string input)=0;
};
class DogParser: public IParsable{
public:
    Pet* parse(string input) override {
        string type, name, breed;
        int age;
        double price;
        stringstream ss(input);
        ss>>type>>name>>age>>price>>breed;
        return new Dog(name, age, price, breed);
    }
};
class CatParser: public IParsable{
public:
    Pet* parse(string input) override {
        string type,name, color;
        int age;
        double price;
        stringstream ss(input);
        ss>>type>>name>>age>>price>>color;
        return new Cat(name, age, price, color);
    }

};
class BirdParser: public IParsable{
public:
    Pet* parse(string input) override {
        string type, name;
        int age;
        double price, wingSpan;
        stringstream ss(input);
        ss>>type>>name>>age>>price>>wingSpan;
        return new Bird(name, age, price, wingSpan);
    }
};


class Parser{
private:
    map<string, IParsable*> _parsers;
public:
    Parser(){
        _parsers["Dog"]=new DogParser();
        _parsers["Cat"]=new CatParser();
        _parsers["Bird"]=new BirdParser();
    }
    IParsable* getParser(string type){
        return _parsers[type];
    }
    static Pet* parsePet(string input){
        Parser parser;
        stringstream ss(input);
        string type;
        ss>>type;
        IParsable* p=parser.getParser(type);
        return p->parse(input);
    }
};



int main() {
    int testID;
    std::cin >> testID;
    std::cout << "Test " << testID << ":" << std::endl;

    PetStore store;
    store.addPet(new Bird("Rio", 1, 150.0, 12.5));
    store.addPet(new Dog("Lucky", 2, 120.0, "Vietnam"));
    store.addPet(new Cat("Milu", 1, 100.0, "Gray"));

    std::vector<std::string> inputs = {
            "Dog Buddy 3 150.0 Golden_Retriever",
            "Cat Whiskers 2 100.0 Black",
            "Bird Tweety 1 50.0 25.0"
    };

    for (const auto& input : inputs) {
        Pet* pet = Parser::parsePet(input);
        store.addPet(pet);
    }

    store.display();

    return 0;
}

/*
input :1
output :
Test 1:
Type | Name | Age | Price | Special
----------------------------------------------------------------------
Dog | Buddy | 3 | 150.0 | Golden_Retriever
Cat | Whiskers | 2 | 100.0 | Black
Bird | Tweety | 1 | 50.0 | 25.0
 */