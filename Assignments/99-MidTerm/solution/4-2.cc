#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
using namespace std;

int main() {
  int c = 0;
  bool done = false;
  queue<int> goods;

  mutex mu;
  condition_variable cond;
  int _size = 50;

  thread producer([&]() {
    for (int i = 0; i < 500; ++i) {
      std::unique_lock<std::mutex> locker(mu);
      cond.wait(locker, [&]() { return c < _size; });
      goods.push(i);
      c++;
      // cout << "p(" << c << ") "; Just for fun
      locker.unlock();
      cond.notify_all();
    }
    // cout << "producer: finished " << c << '\n';

    done = true;
  });

  thread consumer([&]() {
    while (!done) {
      // cout << "consumer: start " << c << '\n';
      while (!goods.empty()) {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [&]() { return c > 0; });
        goods.pop();
        c--;
        // cout << "c(" << c << ") "; Just for fun
        locker.unlock();
        cond.notify_all();
      }
    }
  });

  producer.join();
  consumer.join();
  cout << "Net: " << c << endl;
}
