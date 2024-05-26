// This is probably solved by a maths formula, probably combinatorics.

// We can count:
// 1. How many possible records there are in total. -> easy
// 2. Subtract those that have more than one A in them.
// 3. Of the remaining records, how many have strictly less than 3 consecutive
// L? -> consider the case without As, and the case with one A.

// 1. Total number of records: R
// We have 3 choices for each of n letters.
// The total number of possible records is then 3x3x3...x3 n times.
// R = 3^n

// 2.
// * The number of records with zero A is obtained by considering that,
// out of all the records, A is not drawn for n turns. So the amount of
// such records is (2/3)^n of the whole set of records.
// A_0 = R * (2/3)^n = 2^n
// * The amount of records which contain A one time is obtained by considering
// that A is present with rate (1/3) at any of the n positions, and not
// present in the remaining n-1 positions.
// A_1 = 1/3 * (2/3)^(n-1) * n * R = 2^(n-1) * n
// Thus the number of records with A present 0 or 1 time is A_0 + A_1.

// It might be shorter to do R - cases with more than one A
// - cases with more than 2 consecutive L
// + cases with both more than one A and more than 2 consecutive L

// Cases with two or more A: A2*
// This is R - A0 - A1
// A2* = 3^n - 2^n - 2^(n-1) * n

// Cases with three or more consecutive L (L3*)
// L has been chosen three times in a row, and is positioned at any of the (n-2)
// positions which can fit them.
// L3* = R * (1/3)^3 * (n-2) = 3^(n-3) * (n-2)

// Cases with both more than one A and more than 2 consecutive L (D)
// ** L has been chosen three times in a row, at (n-2) possible positions, this
// is L3*
// ** We have to fill the remaining (n-3) positions with a least two A.
// We exclude the cases where A was never chosen, or chosen only once.
// D = L3* (1 - (2/3)^(n-3) - (1/3) * (n-3) * (2/3)^(n-4))
//   = 3^(n-3) * (n-2) * (1 - (2/3)^(n-3) - (n-3) * 2^(n-4) * (1/3)^(n-3))
//   = (n-2) * (3^(n-3) - 2^(n-3) - (n-3) * 2^(n-4))

// Sol = R - A2* - L3* + D

// If n = 1, Sol = 1
// If n = 2, Sol = 2^n + 2^(n-1)*n = 8
// If n = 3, Sol = 2^n + 2^(n-1)*n - 3^(n-3) * (n-2) = 19
// If n >= 4, the above equation works.

// Example: n=3
// All possible records are:
// "AAA", "AAL", "AAP", "ALA", "ALL*", "ALP*", "APA", "APL*", "APP*", -> 4
// "LAA", "LAL*", "LAP*", "LLA*", "LLL", "LLP*", "LPA*", "LPL*", "LPP*", -> 7
// "PAA", "PAL*", "PAP*", "PLA*", "PLL*", "PLP*", "PPA*", "PPL*", "PPP*" -> 8

// Solution is 19 for n=3.


// Now we just have to implement the +, -, * and power operators with modulo
// TODO: is there a problem with the signs?
//       What happens when we do minus for unsigned types?

#include <iostream>

typedef long long Num; // Long enough for mod_fact * mod_fact
const Num mod_fact {1000000007};

Num plu(Num x, Num y) { return (x + y) % mod_fact; }

Num minu(Num x, Num y) { return (x - y) % mod_fact; }

Num mul(Num x, Num y) { return (x * y) % mod_fact; }

Num pow(Num x, long y) {
  if (y < 0) {return 0;}
  Num res{1};
  for (long i = 0; i < y; ++i) {
    res = mul(res, x);
  }
  return res;
}

Num R (Num n) {
  // Total number of possible records of length n.
  return pow(3,n);
}

Num A0 (Num n) {
  // Number of records with zero A.
  return pow(2,n);
}

Num A1 (Num n) {
  // Number of records with one A exactly.
  // A1 = 2^(n-1) * n
  return mul(n, pow(2,n-1));
}

Num A2star (Num n) {
  // Number of records with two or more A.
  // This is R - A0 - A1
  return minu(minu(R(n), A0(n)), A1(n));
}

Num L3star (Num n) {
  // Number of records with three consecutive L in it.
  // L3* = 3^(n-3) * (n-2)
  return mul(n-2, pow(3,n-3));
}

Num D (Num n) {
  // Number of records which both have two or more A,
  // and three consecutive L.
  // D = (n-2) * (3^(n-3) - 2^(n-3) - (n-3) * 2^(n-4))
  return mul(n-2,
             minu(minu(pow(3,n-3), pow(2,n-3)),
                  mul(n-3, pow(2,n-4))));
}

Num awards (Num n) {
  // Number of records winning the award.
  // Sol = R - A2* - L3* + D
  return plu(minu(minu(R(n), A2star(n)),
                  L3star(n)),
             D(n));
}

int main() {
  int n{10101};
  std::cout << "R: " << R(n) << " A2*: " << A2star(n)
            << " L3*: " << L3star(n) << " D: " << D(n)
            << " awards: " << awards(n)
            << std::endl;

}
