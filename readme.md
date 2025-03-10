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

