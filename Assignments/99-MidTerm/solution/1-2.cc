#include <iostream>

class SemanticSurprise {
public:
  SemanticSurprise(int value) : _value(value) {}

  SemanticSurprise(const SemanticSurprise &other) = default;

  bool operator==(const SemanticSurprise &other) const {
    return _value == other._value;
  } 

  int value() { return _value; }

private:
  int _value;
};

int main() {
  int val = 4;
  auto s1 = SemanticSurprise(val);
  auto s2 = SemanticSurprise(s1);
  if (s1 == s2) {
    std::cout << "operator== works (1/2)" << '\n';
  }
  s1 = SemanticSurprise(5);
  if (!(s1 == s2)) {
    std::cout << "operator== works (2/2)" << '\n';
  }
  std::cout << s2.value() << " " << s1.value() << '\n';


  SemanticSurprise sop2(4);       // <-- Op?
  std::cout <<  sop2.value() << '\n';                   // <-- value?

  SemanticSurprise sop3 = sop2;     // <-- Op?
  std::cout <<  sop3.value() << '\n';                   // <-- value?

  SemanticSurprise sop4(sop3);      // <-- Op?
  auto op = (sop4 == sop3);
  std::cout << op  << '\n';                     // <-- value?
  return 1;
}
