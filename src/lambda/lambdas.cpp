
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
}


void func_param_lambda(){

}

void immediate_invocation_lambda(){

}


void generic_print_lambda(){

}
// #endif