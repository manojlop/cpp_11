# Type Inference in C++11

C++11 introduced powerful type inference capabilities that reduce verbosity and make code more maintainable through the `auto` and `decltype` keywords.

## Overview

Before C++11, each data type needed to be explicitly declared at compile-time, limiting the flexibility of expressions at runtime. Type inference allows the compiler to automatically deduce types, making code more concise and often more readable.

While type deduction happens during compilation and may slightly increase compile time, it has no impact on runtime performance.

## Auto Keyword

The `auto` keyword tells the compiler to automatically deduce the type of a variable from its initializer expression.

### Key Rules for `auto`

- Variables declared with `auto` **must be initialized** at declaration time
- For functions with `auto` return type, the return type is deduced from the return expressions
- Trailing return types can be specified with syntax: `auto f() -> int;`

### Examples

```cpp
void examples_auto() {
  // /*/cpp_11/src/my_lib.cpp:5:3: error: declaration of 'auto a' has no initializer
  #ifdef __AUTO_DECL_ERROR__ 
  auto a; 
  #endif

  auto x = 4;               // int
  auto y = 3.37;            // double
  auto z = 3.37f;           // float
  auto c = 'a';             // char
  auto ptr = &x;            // int*
  auto pptr = &ptr;         // int**
  cout << typeid(x).name() << endl
        << typeid(y).name() << endl
        << typeid(z).name() << endl
        << typeid(c).name() << endl
        << typeid(ptr).name() << endl
          << typeid(pptr).name() << endl;
}
```

### Type Name Output

The `typeid(x).name()` function returns platform-specific type identifiers:
- 'i' for integers, 'd' for doubles
- 'f' for float, 'c' for char
- 'Pi' for pointer to integer
- 'Pd' for pointer to double
- 'Pf' for pointer to float
- 'Pc' for pointer to char
- 'PPi' for pointer to pointer to integer
- Single pointer results in prefix 'P'
- Double-pointer results in 'PP' prefix, and so on

### Use Case: Container Iterators

One of the most common use cases for `auto` is when working with iterators for containers:

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

### Important Notes on References

- `auto` becomes an int type if an integer reference is assigned to it
- To preserve reference type, use `auto&`

Example:
```cpp
int& fun() { return someInt; };
auto m = fun();    // m is int, not int&
auto& n = fun();   // n is int&
```

### Trailing Return Types

The use of `auto` before a function name enables trailing return type syntax:

```cpp
template<typename Container, typename Index> 
auto authAndAccess(Container& c, Index i) -> decltype(c[i]){
  authenticateUser();
  return c[i];
}
```

Benefits:
- Parameters can be used in the return type specification
- Useful when the return type depends on parameter types

In C++14, you can simplify further by omitting `-> decltype(c[i])` as the return type would be deduced from the `return` statement.

### Caveats with Auto Return Type Deduction

When `auto` is used for return type deduction, references are stripped:

```cpp
std::deque<int> d;
// ...
// authenticate user, return d[5],
// then assign 10 to it;
authAndAccess(d, 5) = 10;  // won't compile!
```

This fails because `d[5]` returns an `int&`, but auto return type deduction strips the reference, yielding a return type of `int` (an rvalue), which cannot be assigned to.

## Decltype Keyword

`decltype` examines the declared type of an entity or the type of an expression. Unlike `auto`, `decltype` preserves references, const-qualifiers, and value categories.

### Primary Use

The primary use for `decltype` is in declaring function templates where the return type depends on parameter types.

### Examples

```cpp
#include <bits/stdc++.h>
using namespace std;

int fun1() { return 10; }
char fun2() { return 'g'; }

int main()
{
    // Data type of x is same as return type of fun1()
    // and type of y is same as return type of fun2()
    decltype(fun1()) x; // int
    decltype(fun2()) y; // char

    cout << typeid(x).name() << endl; // i
    cout << typeid(y).name() << endl; // c

    return 0;
}
```

### Compile-time vs. Runtime Type Information

- `decltype` provides type information at compile time
- `typeid` provides type information at runtime

### Generic Function with decltype

```cpp
#include <bits/stdc++.h>
using namespace std;

// A generic function which finds minimum of two values
// return type is type of variable which is minimum
template <class A, class B>
auto findMin(A a, B b) -> decltype(a < b ? a : b)
{
    return (a < b) ? a : b;
}

// driver function to test various inference
void main()
{
    // This call returns 3.44 of double type
    cout << findMin(4, 3.44) << endl;

    // This call returns 3 of double type
    cout << findMin(5.4, 3) << endl;
}
```

### Working with Nested Types

If an element has a nested type, such as `vector<int> v`, we can use `decltype` to get that nested type:

```cpp
typedef decltype(v)::value_type elem_t; // alias for int
```

## decltype(auto) (C++14)

To solve the reference-stripping issue with `auto` return types, C++14 introduced `decltype(auto)`:

```cpp
template<typename Container, typename Index> 
decltype(auto) authAndAccess(Container& c, Index i) { 
  authenticateUser();
  return c[i];  // return type is exactly what c[i] returns (preserves references)
}
```

This ensures the function returns exactly the same type that expression `c[i]` returns, including references.

## Best Practices

1. Use `auto` for:
   - Complex iterator types
   - Lambda capture variables
   - Temporary variables with obvious types

2. Use `decltype` for:
   - Template functions where return type depends on parameters
   - Preserving exact type information including references

3. Use `decltype(auto)` for:
   - Function return types that should preserve references and other qualifiers

4. Be mindful of:
   - Type deduction rules differ between `auto` and `decltype`
   - Reference and const-qualifier stripping with `auto`
   - Potential readability issues when overused