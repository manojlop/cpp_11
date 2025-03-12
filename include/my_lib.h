#ifndef MY_LIB_H
#define MY_LIB_H

#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

// Templated functions should be implemented in header
template <typename T>
void printv(const vector<T>& vect){
  for (const auto& v : vect)
    cout  << v << " ";
}

class str;


// Auto type deduction and decltype

#ifdef __FLAG_AUTO__
void examples_auto();
#endif

#ifdef __FLAG_AUTO_DECLTYPE__
void examples_auto_decltype();
#endif

// Range based for loops

#ifdef __FLAG_RANGE_FOR__
void examples_range_based_for();
#endif

// Lambda expressions

#ifdef __FLAG_LAMBDA__
void lambda_sort();
void first_divisible();
void lambda_transform();
void filter_with_predicates(int val);
// Advanced lambdas
void custom_sort();
void recursive_lambda();
void func_param_lambda();
void immediate_invocation_lambda();
void generic_print_lambda();
#endif


// Move semantics

#ifdef __FLAG_MOVE_SEM__
void move_sem_first_example();
str createStr();
void move_sem_constructor();
#endif

// Perfect forwarding

// Smart pointers

// Variadic templates

// Constexpr

// Threading library

#endif // MY_LIB_H