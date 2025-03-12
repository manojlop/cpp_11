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


class str {
private:

public:
  char* data;

  str(const char* d){
    size_t size = strlen(d) + 1;
    data = new char[size];
    memcpy(data, d, size);
  }

  ~str(){
    delete[] data;
  }

  str(const str& rhs){
    size_t size = strlen(rhs.data) + 1;
    data = new char[size];
    memcpy(data, rhs.data, size);

    cout << "Copy constructor" << endl;
  }

  str(str&& rhs) {
    data = rhs.data;
    rhs.data = nullptr;

    cout << "Move constructor" << endl;
  }

  str& operator=(str rhs){
    swap(data, rhs.data);
    cout << "Move operator" << endl;
    return *this;
  }

  str operator+(const str& rhs) const {
    size_t size1 = strlen(data);
    size_t size2 = strlen(rhs.data);
    
    char* newData = new char[size1 + size2 + 1];  // Allocate memory
    memcpy(newData, data, size1);
    memcpy(newData + size1, rhs.data, size2 + 1);  // Copy with null terminator

    str result(newData);

    delete[] newData;

    return result;  // Return a new str object (RVO will optimize)
  }
};

#endif