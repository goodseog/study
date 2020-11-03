#include <iostream>

using namespace std;

// MAX_SIZE는 메모리 관리용.
// 아래 하드코딩해도 상관 없음
template <class T, int MAX_SIZE = 10000>
struct Stack {
  T stack[MAX_SIZE];
  int cur;

  Stack() { init(); }

  void init() { cur = 0; }

  void push(T value) { stack[cur++] = value; }

  T top() {
    if (isEmpty())
      return (T)NULL;
    else
      return stack[cur - 1];
  }

  T pop() {
    if (isEmpty())
      return (T)NULL;
    else
      return stack[--cur];
  }

  bool isEmpty() { return cur == 0; }

  int size() { return top; }
};

int main(int argc, char** argv) {
  Stack<int, 10> stack;
  cout << "Push 100 : " << endl; stack.push(100);
  cout << "Push 200 : " << endl; stack.push(200);
  cout << "Push 300 : " << endl; stack.push(300);

  cout << "stack.top() : " << stack.top() << endl;
  cout << "stack.pop() : " << stack.pop() << endl;
  cout << "stack.pop() : " << stack.pop() << endl;
  cout << "stack.pop() : " << stack.pop() << endl;
  cout << "stack.pop() : " << stack.pop() << endl;

  cout << "====================" << endl;

  Stack<double> stackd;
  stackd.push(1.23);
  stackd.push(2.45);
  stackd.push(3.6);

  cout << stackd.pop() << endl;
  cout << stackd.pop() << endl;
  cout << stackd.pop() << endl;

  return 0;
}