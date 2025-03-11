#ifndef __HELP_STRUCT__
#define __HELP_STRUCT__

#include "my_lib.h"

class Person {
private:
  string name;
  int age;

public:
  // Constructors
  Person() : name("Unknown"), age(0) {}  // Default constructor
  Person(const string& name, int age) : name(name), age(age) {}  // Parameterized constructor

  // Copy Constructor
  Person(const Person& other) : name(other.name), age(other.age) {
    cout << "Copy Constructor Called\n";
  }

  // Move Constructor
  Person(Person&& other) noexcept : name(move(other.name)), age(other.age) {
    cout << "Move Constructor Called\n";
  }

  // Copy Assignment Operator
  Person& operator=(const Person& other) {
    if (this != &other) {
      name = other.name;
      age = other.age;
    }
    cout << "Copy Assignment Operator Called\n";
    return *this;
  }

  // Move Assignment Operator
  Person& operator=(Person&& other) noexcept {
    if (this != &other) {
      name = move(other.name);
      age = other.age;
    }
    cout << "Move Assignment Operator Called\n";
    return *this;
  }

  // Destructor
  ~Person() {
    cout << "Destructor Called for " << name << "\n";
  }


  // Getters
  string getName() const { return name; }
  int getAge() const { return age; }

  // Setters
  void setName(const string& newName) { name = newName; }
  void setAge(int newAge) { age = newAge; }

  // toString method
  string toString() const {
    return "Name: " + name + ", Age: " + to_string(age);
  }

  // Friend function for output stream
  friend ostream& operator<<(ostream& os, const Person& person) {
    return os << person.toString();
  }
};

#endif