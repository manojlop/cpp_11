#include "my_lib.h"

#ifdef __FLAG_AUTO__

#include <bits/stdc++.h>
#include <vector>
void examples_auto() {
  // /home/manojlo/Desktop/org/cpp/learn/cpp_11/src/my_lib.cpp:5:3: error: declaration of ‘auto a’ has no initializer
  #ifdef __AUTO_DECL_ERROR__ 
  auto a; 
  #endif

  #ifdef __AUTO_PRINT__
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

  // Create a set of strings
  set<string> st;
  st.insert({ "geeks", "for", "geeks", "org" });

  // 'it' evaluates to iterator to set of string
  // type automatically
  for (auto it = st.begin(); it != st.end(); it++)
    cout << *it << " ";

  cout << endl;

  #else

  auto x = 1;      //x : int

  float* p;
  auto x = p;      //x : float*
  auto* y = p;     //y : float*

  double f();
  auto x = f();             //x : double
  const auto& y = f();      //y : const double&

  class R;
  R* h();
  auto* x = h();    //x : R*
  auto y = h();     //y : R*

  int& g();
  auto x = g();           //x : int
  const auto& y = g();    //y : const int&
  auto* z = g();          //error, g() does not return a pointer type 

  vector<int> vec;
  for (vector<int>::iterator i = vec.begin(); i < vec.end(); i++)  
  {
    int* a = new int(1);
    //...
  }

  for (auto i = vec.begin(); i < vec.end(); i++)  
  {
    auto a = new auto(1);
    //...
  }

  #endif

}
#endif