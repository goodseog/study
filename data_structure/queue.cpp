#include <iostream>

using namespace std;

// MAX_SIZE는 메모리 관리용.
// 아래 하드코딩해도 상관 없음
template <class T, int MAX_SIZE = 10000>
struct Queue {
  T queue[MAX_SIZE];
  int fcur, rcur;

  Queue() { init(); }

  void init() {
    fcur = 0;
    rcur = 0;
  }

  void push(T value) { queue[rcur++] = value; }

  T front() {
    if (isEmpty())
      return (T)NULL;
    else
      return queue[fcur];
  }

  T pop() {
    if (isEmpty())
      return (T)NULL;
    else
      return queue[fcur++];
  }

  bool isEmpty() { return fcur == rcur; }

  int size() { return rcur - fcur; }
};

int main(int argc, char** argv) {
  Queue<int, 10> queue;
  cout << "Push 100 " << endl; queue.push(100);
  cout << "Push 200 " << endl; queue.push(200);
  cout << "Push 300 " << endl; queue.push(300);

  cout << "pop  :" << queue.pop() << endl;
  cout << "front  :" << queue.front() << endl;
  cout << "pop  :" << queue.pop() << endl;  
  cout << "pop  :" << queue.pop() << endl;
  cout << "pop  :" << queue.pop() << endl;

  cout << "====================" << endl;

  Queue<double> queued;
  queued.push(1.23);
  queued.push(2.45);
  queued.push(3.6);

  cout << queued.pop() << endl;
  cout << queued.pop() << endl;
  cout << queued.pop() << endl;

  return 0;
}