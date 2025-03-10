# C++11 Features Guide

This document provides an overview of key features introduced in C++11, with examples and explanations to help you understand and use these modern C++ capabilities in your code.

## Table of Contents
- [Auto Type Deduction and Decltype](#auto-type-deduction-and-decltype)
- [Range-Based For Loops](#range-based-for-loops)
- [Lambda Expressions](#lambda-expressions)
- [Advanced Lambdas](#advanced-lambdas)
- [Move Semantics](#move-semantics)
- [Perfect Forwarding](#perfect-forwarding)
- [Smart Pointers](#smart-pointers)
- [Variadic Templates](#variadic-templates)
- [Constexpr](#constexpr)
- [Threading Library](#threading-library)

## Type inference

Automatic deduction of the data type of an expression\
Before C++1, each data type needed to be explicitly declared at compile-time, limiting values of an expression at runtime\
Keywords like `auto` and `decltype` leave deduction of type to compiler itself

As all the types are deduced in the compiler phase only, the time for compilation increases slightly but it does not affect the run time of the program.

### Auto

Keyword `auto` in C++ speficies that the type of the variable that is being declared will be automatically deducted from its initializer.

In case of functions, if return type is auto, that will be evaluated by return type expression at compile time

> The variable declared with auto keyword should be initialized at the time of its declaration only or else there will be a compile-time error.

> We can use `typeid()` to get type of the variables (when we want to know dynamic type of object)

```cpp
void examples_auto() {
  // /*/cpp_11/src/my_lib.cpp:5:3: error: declaration of ‘auto a’ has no initializer
  #ifdef __AUTO_DECL_ERROR__ 
  auto a; 
  #endif

  auto x = 4;
  auto y = 3.37;
  auto z = 3.37f;
  auto c = 'a';
  auto ptr = &x;
  auto pptr = &ptr; //pointer to a pointer
  cout << typeid(x).name() << endl
        << typeid(y).name() << endl
        << typeid(z).name() << endl
        << typeid(c).name() << endl
        << typeid(ptr).name() << endl
          << typeid(pptr).name() << endl;

}
```

typeid(x).name() returns the data type of x, for example, it returns:
  - ‘i’ for integers, ‘d’ for doubles,
  -  ‘f’ for float, ‘c’ for char, 
  -  Pi’ for the pointer to the integer,
  -  ‘Pd’ for the pointer to double,’
  -  Pf’ for the pointer to float, 
  -  ‘Pc’ for the pointer to char,
  -  ‘PPi’ for the pointer to pointer to integer.
  -  Single Pointer results in  prefix ‘P’,
  -  double-pointer results in ‘PP’ as a prefix and so on.


__Use case__: To avoid long initialization when creating iterators for containers

```cpp
int main(){
// Create a set of strings
  set<string> st;
  st.insert({ "geeks", "for", "geeks", "org" });

  // 'it' evaluates to iterator to set of string
  // type automatically
  for (auto it = st.begin(); it != st.end(); it++)
    cout << *it << " ";

  return 0;
}
```

### Decltype


## Range-Based For Loops


## Lambda Expressions


## Advanced Lambdas



## Move Semantics



## Perfect Forwarding



## Smart Pointers

### unique_ptr


### shared_ptr



## Variadic Templates



## Constexpr



## Threading Library

