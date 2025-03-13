#include "my_lib.h"
#include "helper_struct.h"

#include <cstring>
#include <algorithm>

#ifdef __FLAG_MOVE_SEM__

class Pair {
private:
  Person male;
  Person female;

public:
  Pair() : male(), female() {
    cout << "Pair empty constructor";
  }

  // move(f) is an rvalue of type const std::string
  // rvalue can't be passed to Person's move constructor, because the move constructor takes an rvalue reference to a non-const Person
  // It can, however be passed to the copy constructor, because an lvalue-reference-to-const is permittted to bind to a const rvalue -> both invoke copy constructor
  // /* Try with this and observe*/ Pair(const Person m, Person f) : male(m), female(move(f)) 
  Pair(const Person m, const Person f) : male(m), female(move(f)) {
    cout << "male(m), female(move(f))" << endl;
  }

  Pair(const Pair& p) : male(p.male), female(p.female) {}
};

void move_sem_first_example(){
  Person p1("Mike", 30);
  Person p2("Lucy", 25);

  cout << p1 << endl << p2 << endl;

  Pair pair(p1, p2);
  
}

str createStr() {
  str temp("temp");
  return temp; // Force a move here by returning a named variable
}

void move_sem_constructor(){
  str x("123");
  str y("453");

  str a(x);                                   
  str b(x + y);                           
  str c = x.data;
  str d = move(x);
  str e = createStr();  
}

#endif

#ifdef __FLAG_PERF_FORW__
void process(const Person& lvalArg){
  cout << "Proces lvalues for: " << lvalArg << endl;
}
void process(Person&& rvalArg){
  cout << "Proces rvalues for: " << rvalArg << endl;
}

void perfect_forward_example(){
  Person p("Mike", 30);
  logAndProcess(p); // call with lvalue
  logAndProcess(std::move(p)); // call with rvalue
  
  logAndProcessForward(p); // call with lvalue
  logAndProcessForward(std::move(p)); // call with rvalue

  /*
  Proces lvalues for: Name: Mike, Age: 30
  Proces rvalues for: Name: Mike, Age: 30
  Proces lvalues for: Name: Mike, Age: 30
  Proces lvalues for: Name: Mike, Age: 30
  */
}
#endif


