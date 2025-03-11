#include "my_lib.h"

int main() {

  #ifdef __FLAG_LAMBDA__
  lambda_sort();
  cout << '\n';
  first_divisible();
  cout << '\n';
  lambda_transform();
  cout << '\n';
  filter_with_predicates(2);
  cout << '\n';
  custom_sort();
  cout << '\n';
  recursive_lambda();
  cout << '\n';
  func_param_lambda();
  cout << '\n';
  immediate_invocation_lambda();
  cout << '\n';
  generic_print_lambda();
  cout << '\n';
  #endif

  #ifdef __FLAG_RANGE_FOR__
  examples_range_based_for();
  cout << '\n';
  #endif

  #ifdef __FLAG_AUTO_DECLTYPE__
  examples_auto_decltype();
  cout << '\n';
  #endif

  #ifdef __FLAG_AUTO__
  examples_auto();
  cout << '\n';
  #endif

  return 0;
}
