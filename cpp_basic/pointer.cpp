#include <iostream>

using namespace std;

/********************** Call by value, pointer, reference excample **************************/

void sum_value(int a, int b, int c) {
  c = a + b;
}

void sum_pointer(int a, int b, int* c) {
  (*c) = a + b;
}

void sum_reference(int a, int b, int& c) {
  c = a + b;
}

void value_change_scenario() {
  int a = 3;
  int b = 5;
  int answer;
  
  // Call by value
  answer = -1;
  sum_value(a, b, answer);
  cout << "Sum by value     : a + b = 3 + 5 = "  << answer << "????" << endl;

  // Call by pointer (address)
  answer = -1;
  sum_pointer(a, b, &answer);
  cout << "Sum by pointer   : a + b = 3 + 5 = "  << answer << "!!!!" << endl;

  // Call by Reference
  answer = -1;
  sum_reference(a, b, answer);
  cout << "Sum by reference : a + b = 3 + 5 = "  << answer << "!!!!" << endl;
}

/*******************************************************************************************/

// void set(int arr[1000]) {
void set_array(int arr[], int idx, int value) {
  arr[0] = 10000; 
}

int main() {
  value_change_scenario()

  return 0;
}