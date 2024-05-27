// We program examples to check our solution for small cases.

#include <array>
#include <iostream>

enum class Char { A, L, P };

std::ostream& operator << (std::ostream& os, const Char& ch)
{
  char x {'X'};
  switch (ch) {
  case Char::A:
    x = 'A';
    break;
  case Char::L:
    x = 'L';
    break;
  case Char::P:
    x = 'P';
    break;
  }
   os << x;
   return os;
}

void operator++ (Char &ch) {
  // Prefix increment operator for Char with wrap-around.
  switch (ch) {
  case Char::A:
    ch = Char::L;
    break;
  case Char::L:
    ch = Char::P;
    break;
  case Char::P:
    ch = Char::A;
    break;
  }
}

template <std::size_t n>
class Record {
public:
  std::array<Char, n> rec;

  Record () {
    for (auto &ch : rec) {
      ch = Char::A;
    }
  }

  bool operator++ () {
    // Prefix increment operator.
    // Set to false when we reach the last Record: "PPPPP..."
    // We increment the first Char in the record and then carry the increment.
    std::size_t pos {0};
    ++(rec.at(pos));
    while (rec.at(pos) == Char::A) {
      ++pos;
      if (pos == n)
        return false;
      ++(rec.at(pos));
    }
    return true;
  }
};

template <std::size_t n>
std::ostream &operator<<(std::ostream &os, const Record<n> &rec) {
  for (const auto &ch : rec.rec) {
    os << ch;
  }
  return os;
}

int main() {
  Record<3> rec;
  do {
    std::cout << rec << std::endl;
  }
  while (++rec);
}
