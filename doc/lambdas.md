# Lambda Expressions

Lambda expressions are one of the most powerful features introduced in C++11. They provide a way to define anonymous inline functions that can capture variables from their surrounding scope, making them particularly useful for short code snippets that won't be reused elsewhere.

## Overview

A lambda expression creates a function object (closure) that can be called later, similar to function pointers but with more capabilities and convenience. The primary use cases include passing custom behavior to algorithms and creating short callback functions.

## Basic Syntax

```
[capture-clause] (parameters) -> return-type { function-body }
```

Where:
- **capture-clause**: Specifies which variables from the enclosing scope are available inside the lambda
- **parameters**: Function parameters (optional)
- **return-type**: The return type (optional, usually deduced automatically)
- **function-body**: The function code

## Simple Example

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    
    // Defining a lambda that doubles its input
    auto res = [](int x) {
        return x + x;
    };
    cout << res(5);  // Outputs: 10
    
    return 0;
}
```

## Key Concepts

### Lambda vs Closure vs Closure Class

Understanding the distinction between these terms is important:

- A **lambda expression** is the code you write (everything from `[` to `}` in your source code)
- A **closure** is the runtime object created when the lambda is evaluated
- A **closure class** is the compiler-generated class from which the closure is instantiated

For example, in this code:

```cpp
std::find_if(container.begin(), container.end(), 
             [](int val) { return 0 < val && val < 10; });
```

The lambda expression is `[](int val) { return 0 < val && val < 10; }`, and the closure is the function object that's passed to `std::find_if`.

## Variable Capture

The capture clause allows lambdas to access variables from the surrounding scope:

### Capture Modes

- **[&]**: Capture all external variables by reference
- **[=]**: Capture all external variables by value
- **[a, &b]**: Capture 'a' by value and 'b' by reference
- **[]**: No captures (can only access variables declared within the lambda)

### Example with Different Capture Modes

```cpp
#include <bits/stdc++.h>
using namespace std;

void print(vector<int> v) {
    for (auto x : v) cout << x << " ";
    cout << endl;
}

int main() {
    vector<int> v1, v2;

    // Capture v1 and v2 by reference
    auto byRef = [&] (int m) {
        v1.push_back(m);
        v2.push_back(m);
    };
    
    // Capture v1 and v2 by value
    auto byVal = [=] (int m) mutable {
        v1.push_back(m);
        v2.push_back(m);
    };
    
    // Capture v1 by reference and v2 by value
    auto mixed = [=, &v1] (int m) mutable {
        v1.push_back(m);
        v2.push_back(m);
    };

    // Push 20 in both v1 and v2
    // byRef captures all by reference. So pushing 20 will push it into original v1 and v2
    byRef(20);
    
    // Push 234 in both v1 and v2
    // byVal captures all by value. So pushing 234 will not do anything to original vectors.
    byVal(234);
    
    // Push 10 in both v1 and v2
    // mixed captures v1 by reference and v2 by value. So pushing 10 will only push it into v1.
    mixed(10);
    
    print(v1); // 20 10
    print(v2); // 20
    
    return 0;
}
```

### The `mutable` Keyword

By default, variables captured by value are **const** within the lambda. The `mutable` keyword allows modification of captured-by-value variables within the lambda:

```cpp
int x = 5;
auto lambda = [x]() mutable { 
    x += 5;  // Without 'mutable', this would be a compile error
    cout << x << endl; 
};
lambda();  // Outputs: 10
cout << x; // Still 5, because x was captured by value
```

## Common Applications

Lambda expressions excel in several scenarios:

1. **Inline, Anonymous Functions**
   ```cpp
   std::vector<int> nums = {1, 2, 3, 4, 5};
   std::for_each(nums.begin(), nums.end(), [](int& n){ n *= 2; });
   ```

2. **STL Algorithms**
   ```cpp
   // Sort in descending order
   std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
   ```

3. **Callbacks and Event Handling**
   ```cpp
   button.setOnClickListener([](ClickEvent e) { 
       std::cout << "Button clicked at: " << e.x << ", " << e.y << std::endl; 
   });
   ```

4. **Threading and Concurrency**
   ```cpp
   std::thread t([](){ 
       std::cout << "I'm running in a separate thread!" << std::endl; 
   });
   ```

5. **Custom Comparators in Containers**
   ```cpp
   auto compare = [](const Person& a, const Person& b) { 
       return a.lastName < b.lastName; 
   };
   std::set<Person, decltype(compare)> people(compare);
   ```

## Potential Issues with Captures

### Default Capture by Reference [&]

Capturing by reference can lead to dangling references if the lambda outlives the captured variables:

```cpp
void addDivisorFilter()
{
  auto calc1 = computeSomeValue1();
  auto calc2 = computeSomeValue2();
  
  auto divisor = computeDivisor(calc1, calc2); 

  filters.emplace_back([&](int value) {return value % divisor == 0;});
  // DANGER: Reference to divisor will dangle after function returns!
}
```

**Solution:** Capture specific variables by value when they need to outlive the current scope:

```cpp
filters.emplace_back([divisor](int value) {return value % divisor == 0;});
```

### Default Capture by Value [=]

Capturing by value seems safer but can be problematic with pointers:

```cpp
void processWidget(std::shared_ptr<Widget> pw)
{
  auto func = [=]() { 
      // pw was captured by value, but it's still just a copy of the pointer
      pw->process();  // What if the original shared_ptr is reset?
  };
  // ...
}
```

### Capturing Class Members

Class members cannot be directly captured because they're not local variables:

```cpp
class Widget {
public:
  void addFilter() const;
private:
  int divisor;
};

// This doesn't work
void Widget::addFilter() const
{
  filters.emplace_back([divisor](int value){ return value % divisor == 0; });
  // Error: 'divisor' is not a local variable
}
```

When using `[=]` in a member function, it implicitly captures `this`:

```cpp
// This works, but captures this pointer
void Widget::addFilter() const
{
  filters.emplace_back([=](int value) { return value % divisor == 0; });
  // Actually uses this->divisor internally
}
```

**Better solutions:**

1. Copy the member variable to a local:
   ```cpp
   void Widget::addFilter() const
   {
     auto divisorCopy = divisor; // copy data member
     filters.emplace_back([divisorCopy](int value)  
       { return value % divisorCopy == 0; });
   }
   ```

2. Use a C++14 initialization capture (generalized lambda capture):
   ```cpp
   void Widget::addFilter() const
   {
     filters.emplace_back(
       [divisor = divisor](int value) 
       { return value % divisor == 0; }
     );
   }
   ```

## C++14 Enhancements

C++14 added several improvements to lambda expressions:

1. **Generic lambdas** with `auto` parameters:
   ```cpp
   auto gen = [](auto x, auto y) { return x + y; };
   ```

2. **Initialization captures** (generalized lambda captures):
   ```cpp
   auto timer = [start = std::chrono::steady_clock::now()]() {
     return std::chrono::steady_clock::now() - start;
   };
   ```

## Best Practices

1. Prefer capturing specific variables over default captures
2. Be wary of capturing references to local variables
3. For member function lambdas, copy member variables to locals if possible
4. Use `mutable` only when necessary
5. Keep lambdas short and focused; if they grow large, consider making them named functions
6. Use generic lambdas (`auto` parameters) when appropriate to create more flexible code