
// #ifdef __FLAG_LAMBDA__

#include "my_lib.h"
#include "helper_struct.h"

void lambda_sort() {

  vector<int> v = {5, 1, 8, 3, 9, 2};

  // Sort in descending order
  sort(v.begin(), v.end(), [] (const int& a, const int&b) {
    return a > b;
  });

  for (int x : v)
    cout << x << " ";
}

void first_divisible() {
  vector<int> v = {5, 1, 8, 3, 9, 2};

  auto it = find_if(v.begin(), v.end(), [] (const int& a) {
      return a % 3 == 0;
  });

  if (it != v.end()) cout << *it;
  else cout << "No such element";
}

void lambda_transform(){
  std::vector<int> numbers = {1, 2, 3, 4, 5};

  cout << "Pre transform: ";
  printv(numbers);
  cout << endl;
    
  // TODO: Create a lambda that doubles a number
  // Use it with std::transform to double all elements in the vector

  transform(numbers.begin(), numbers.end(), numbers.begin(), 
    [](auto& num) mutable {
      return num *= 2;
    });

  cout << "Post transform: ";
  printv(numbers);
  cout << endl;

}

void filter_with_predicates(int val){
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> filtered;
    
  cout << "Pre filter: ";
  printv(numbers);
  cout << endl;
  // TODO: Create a lambda to check if a number is divisible with parameter
  // Use it with std::copy_if to copy even numbers into the 'filtered' vector
    
  copy_if(numbers.begin(), numbers.end(), back_inserter(filtered), 
    [divisor=val](const auto& num) {
      return num % divisor == 0;
    });

  cout << "Filtered: ";
  printv(filtered);
  cout << endl;
}


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

  // TODO: Create a lambda to sort people by name alphabetically (ascending)
  // Use it with std::sort

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


void recursive_lambda(){

  // TODO: Create a recursive lambda to calculate factorial
  // Hint: You'll need to use std::function and a reference capture

  std::function<int(int)> f1 = [&f1](int x)->int {  
    if(x == 0 || x == 1) 
      return 1; 
    else return f1(x-1) + f1(x-2);  
  };
  
  auto f2 = [](int x){
    auto lambda = [](int x, const auto& ff)->int {  
      if(x == 0 || x == 1) 
        return 1;
      else return ff(x-1,ff) + ff(x-2,ff); 
    };
    return lambda(x,lambda);
  };

  auto fib = [](int x, const auto& lambda)->int {  
    if(x == 0 || x == 1) 
      return 1; 
    else return lambda(x-1,lambda) + lambda(x-2, lambda);  
  };

  cout << "Fib: " << fib(5,fib) << endl;
  cout << "Fib: " << f2(5) << endl;
  cout << "Fib: " << f1(5) << endl;
}

// This function takes a vector and a function to process each element
void process_vector(const std::vector<int>& vec /* TODO: Add function parameter type */) {
  for (const auto& element : vec) {
    // TODO: Call the function on each element
  }
}

void func_param_lambda(){
  vector<int> numbers = {1, 2, 3, 4, 5};
    
  // TODO: Call process_vector with a lambda that prints each number multiplied by itself
    
}

void immediate_invocation_lambda(){
  // TODO: Create and immediately invoke a lambda to initialize a vector 
  // with 10 random numbers between 1 and 100
    
}


void generic_print_lambda(){
  vector<int> integers = {1, 2, 3};
  vector<double> doubles = {1.1, 2.2, 3.3};
  vector<string> strings = {"one", "two", "three"};
  
  // TODO: Create a generic lambda that can print elements of any vector type
  // Use it to print all three vectors
}
// #endif