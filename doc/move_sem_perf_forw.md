# Move Semantics and Perfect Forwarding

## Overview

*Rvalue* references are the glue that ties these two features together\

Rvalue references are in broad terms temporary values that are used to initialize variables.\
They are not accessible to us via their own address, although they are an object in memory just like lvalues.\
You can think of them (not always) as temporary objects returned from functions, while lvalue object correspond to objects we can refer to (by name or by following a pointer or lvalue reference)\

#### Move Semantics**

Make it possible for compilers to replace expensive copying operations with less expensive moves.\
In same way that copy constructors and copy assignment operators give you control over what it means to copy objects, move constructors and move assignment operators offer control over the semantics of moving.\
Also enable the creation of _move-only_ types (*unique_ptr*, *future*, *thread*)

They make the **rule of three** be the **rule of five**


#### Perfect Forwarding**

Makes it possible to write function templates that take arbitrary arguments and forward them to other functions, such that the target functions recieve exactly the same arguments as were passed to the forwarding functions


For now, important thing to remember is **that the parameter is always an lvalue, even if its type is an rvalue reference**. 
```cpp
void f(Widget&& w);
```
parameter w is an lvalue (its type is rvalue-reference to Widget)

Useful heuristic to determine whether an expression is an lvalue is to ask if you can take its address. If you can, typically we have lvalue. If we can't its usually an rvalue

## Move semantics 

Move semantics allows an object, under certain conditions, to take ownership of some other object's external resources:
- If an object doesn't manage at least one external resource (directly or indirectly), moving and copying object means the same thing

In following code, we want to do the same thing every time: initialize our string object with a string value
```cpp
string x = "init";
string y = "string";

string a(x);                                    // Line 1
string b(x + y);                                // Line 2
string c(some_function_returning_a_string());   // Line 3
```
However, only at one point, we need to save both the passing argument and the initialized object (when initializing with object x).\
Object x (and y) is an `lvalue`, that means, that it's an **exact same object every time**.\
Arguments x+y, and function call are not lvalues, but rvalues, because underlying string objects have no names -> we cannot inspect them at a later point in time.

From c++11, we have an already talked about `rvalue reference`, which allows us to detect rvalue arguments via function overloading. We just need to write a constructor with rvalue reference parameter
```cpp
string(string&& that) {  // string&& is an rvalue reference to a string
  data = that.data;
  that.data = nullptr;
}
```
Inside the constructor, we can do _anything_ we want with the source, as long as we leave it in some valid state

Instead of deeply copying the heap data, we have just copied the pointer, and then set the original pointer to null (**to prevent delete[] from source object's destructor from releasing our stolen data**)

We can do the same with assignment operator (Reference **copy-and-swap idiom**)

```cpp
string& operator=(string that){
  std::swap(data, that.data);
  return *this;
}
```

Here, we don't need an rvalue reference, as the parameter `that` needs to be initialized, as it's passed *by value*.\
That means that it needs to be constructed, and you can see where im going with this (if you can't, we will use move constructor to create the parameter)\
After swap, destructor of that deletes previous reference

### Understanding `std::move`

Neither *does* what it says (move doesn't move anything, forward doesn't forward anything)\
They don't do anything at runtime and they don't generate executable code

They are *function templates* that perform casts\
`move` unconditionally casts its argument to an rvalue\
`forward` performs this cas only if a particular condition is fulfilled

**Move function**

Here is sample implementation of `move`
```cpp
template<typename T> 
typename remove_reference<T>::type&& move(T&& param){
  using ReturnType = typename remove_reference<T>::type&&; 
  return static_cast<ReturnType>(param);
}
```
It takes *universal* reference to an object and return a reference to the `same` object

The `&&` part of return type implies that the reference being returned is rvalue reference (If the T is to be an lvalue reference, T&& would become lvalue reference)\
> To prevent this, we use remove_reference to T, thus ensring that && is applied to a type that isn't reference

**Rvalue references returned from functions(even move) are rvalues**

In C++14, we can do following
```cpp
template<typename T> 
decltype(auto) move(T&& param) {
  using ReturnType = remove_reference_t<T>&&;
  return static_cast<ReturnType>(param);
}
```

Rvalues are candidates for moving, so applying move to an object tells the compiler that the object is eligible to be moved from

When you execute said code, you will get 4 prints of copy constructor: `p1 -> m, p2 -> f, m -> male, move(f) -> female`

If we delete `const` from `const Person f`, we can observe move constructor being called

```cpp
#include <iostream>

using namespace std;

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

  // Destructor
  ~Person() {
    cout << "Destructor Called for " << name << "\n";
  }
}

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
  Pair(const Person m, const Person f) : male(male), female(move(f)) {
    cout << "male(m), female(move(f))" << endl;
  }

  Pair(const Pair& p) : male(p.male), female(p.female) {}
};

void main(){
  Person p1("Mike", 30);
  Person p2("Lucy", 25);

  cout << p1 << endl << p2 << endl;

  Pair pair(p1, p2);
  
}
```

This behavior is essential to maintaining const-correctness.\
Moving a value out of an object generally modifies the object, so the langage should not permit *const* objects to be passed to functions(move constructors) that could modify them

> Don't declare objects const if you want to be able to move from them (silently to copy operations)

> Move doesn't move, nor does it guarantee that the object it's casting will be eligible to be moved (only thing we know is that it's an rvalue)

## Perfect Forwarding

It's the act of passing a function's parameters to another function while preserving its reference category.\
Commonly used by wrapper methods that want to pass their parameters through to another function

```cpp
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
```

Function takes its parameters and forwards them to T constructor(`perfectly`), meaning that if original value is an rvalue reference, the constructor recieves rvalue reference (lvalue -> lvalue).

> Catch is, it can forward only objects. It can't forward _braced things that are trying to become objects_

```cpp
struct Point
{
  int x, y;
};

struct Segment
{
  Segment(Point p1, Point p2);
};

void test()
{
  // This works
  Segment s({ 1, 1 }, { 2, 2 });

  // This doesn't
  auto p = std::make_unique<Segment>({ 1, 1 }, { 2, 2 });
}
```

We can observe that in the make_unique ({},{}), braces would become Points at some time.\
But the compiler sees the parameters as stuff in curly braces, which is not an object\
Point is lightweight, and we don't need it, but we can do something like this:

```cpp
struct Segment
{
  Segment(Point p1, Point p2);

  template<typename Arg1 = Point,typename Arg2 = Point>
  static std::unique_ptr<Segment> make_unique(Arg1&& p1, Arg2&& p2){
    return std::make_unique<Segment>(std::forward<Arg1>(p1), std::forward<Arg2>(p2));
  }
};
```


### Understanding `std::forward`

**Forward function**

`Forward` casts only under certain conditions, as it's a *conditional* cast.\

Typical usage of forward is a function template taking a universal reference parameter that is to be passed to another function
```cpp
void process(const Widget& lvalArg); // process lvalues
void process(Widget&& rvalArg); // process rvalues

template<typename T> // template that passes
void logAndProcess(T&& param) { // param to process
  auto now = std::chrono::system_clock::now(); // get current time
  makeLogEntry("Calling 'process'", now);
  process(std::forward<T>(param));
}
```

Consider two calls

```cpp
Widget w;
logAndProcess(w); // call with lvalue
logAndProcess(std::move(w)); // call with rvalue
```

As we said, `param` is an lvalue inside logAndProcess.\
To prevent always invoking lvalue overload for process, we need a mechanism for param to be cas to an rvalue `if and only if the argument with which param was initialized (one passed to logAndProcess) was an rvalue`.\
This is precisely what `forward` does.
