# Advanced Lambdas

Building on the basic lambda functionality, C++11 and later versions offer advanced lambda features for more sophisticated use cases. This section demonstrates practical examples of using lambdas with standard algorithms and showcases more complex patterns.

## Using Lambdas with Standard Algorithms

### Example 1: Transforming Values with `std::transform`

The `std::transform` algorithm applies a function to a range of elements and stores the result. Lambdas make it easy to define custom transformations:

```cpp
template <typename T>
void printv(const vector<T>& vect) {
  for (const auto& v : vect)
    cout << v << " ";
}

void lambda_transform(){
  std::vector<int> numbers = {1, 2, 3, 4, 5};

  cout << "Pre transform: ";
  printv(numbers);
  cout << endl;

  transform(numbers.begin(), numbers.end(), numbers.begin(), 
    [](auto& num) {
      return num *= 2;
    });

  cout << "Post transform: ";
  printv(numbers);
  cout << endl;
}
```

This example shows how to use a lambda with `std::transform` to double each value in a vector.

### Example 2: Filtering with Predicates

Lambdas are excellent for defining custom filtering conditions with algorithms like `std::copy_if`:

```cpp
void filter_with_predicates(int val){
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> filtered;
    
  cout << "Pre filter: ";
  printv(numbers);
  cout << endl;
  
  copy_if(numbers.begin(), numbers.end(), back_inserter(filtered), 
    [divisor=val](const auto& num) {
      return num % divisor == 0;
    });

  cout << "Filtered: ";
  printv(filtered);
  cout << endl;
}
```

This example demonstrates:
1. Using initialization capture (`[divisor=val]`) to store a parameter value
2. Using `const auto&` to avoid unnecessary copying
3. Using `std::back_inserter` to add elements to a destination container

### Example 3: Custom Sorting

Lambdas simplify the creation of custom sorting predicates for `std::sort` and similar algorithms:

```cpp
void custom_sort(){
  std::vector<Person> people = {
    {"Charlie", 20},
    {"Alice", 25},
    {"Bob", 30},
    {"Alice", 37}
  };
  
  cout << "Pre sorted: ";
  printv(people);
  cout << endl;

  sort(people.begin(), people.end(),
    [](const auto& a, const auto& b) {
      if(a.getName() < b.getName())
        return true;
      else if (a.getName() > b.getName())
        return false;
      else 
        return a.getAge() < b.getAge();
    });

  cout << "Sorted: ";
  printv(people);
  cout << endl;
}
```

This example sorts a vector of `Person` objects first by name alphabetically, then by age when names are equal.

## Advanced Lambda Techniques


## Best Practices for Advanced Lambdas

1. Use initialization captures (C++14) for more complex capture scenarios
2. Leverage auto parameters (C++14) for more generic lambdas
3. Capture specific variables by value or reference rather than using default captures
4. Consider performance implications of capturing large objects
5. Use lambdas with standard algorithms to create more expressive code
6. For complex or reusable logic, consider extracting to named functions
7. Be cautious with recursive lambdas and ensure proper termination conditions
8. Use lambda expressions instead of small functor classes
9. Remember that every lambda creates a unique type,