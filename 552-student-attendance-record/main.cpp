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

// 3.
// * Of the records that have zero A, we have only two choices for letters.
// We can have zero, one or two consecutive L.
// ** The total number of records with zero A and zero L is:
//    (the fraction of all possible records where P is always chosen out of the
//    three letters.)
//    A0L0 = R * (1/3)^n = 1
// ** The number of records with zero A and one L is:
//    (Only P is chosen, except one time for L, L can be in any position in the
//    string)
//    A0L1 = R * (1/3)^(n-1) * (1/3) * n = n * R * (1/3)^n = n
// ** The number of records with zero A and two consecutive L is,
//    the rate at which two L are chosen consecutively, with a P before and
//    after, at any of the n-3 position which can fit them,
//    Plus the rate at which two L are chosen consecutively at one of two ends
//    of the record, with a P before/after and if the record can hold it (n>=3).
//    If n=2, we just have to draw two L consecutively.
//    A0L2 = A_0 * [(1/2)^4 * max(n-3,0) + 2 * (1/2)^3 * (if n>=3) + (1/2)^2 *
//    (if n=2)]
//    *** if n=2:
//    A0L2 = 2^n * (1/2)^2 = 1
//    *** if n>=3:
//    A0L2 = 2^n * [(1/2)^4 * (n-3) + 2*(1/2)^3]
//         = (n-3) * 2^(n-4) + 2^(n-2)

//
// * Of the records that have one A, we can have zero, one or two consecutive L.
// ** The number of records with one A and zero L is:
//    A1L0 = A_1 * (1/2)^(n-1) = 2^(n-1)*n * (1/2)^(n-1) = n
// ** The number of records with one A and one L is:
//    (L is drawn once, at any of the n-1 available positions,
//     P is drawn for all other positions).
//    A1L1 = A_1 * (1/2) * (n-1) * (1/2)^(n-2) = 2^(n-1)*n * (n-1) * (1/2)^(n-1) = n * (n-1)
// ** The number of records with one A and two consecutive L is:
//    the number of records with zero A and two consecutive L, which when an A
//    is added, does not break the two consecutive L.
//    We can put the A in n-2 positions.
//    A1L2 = A0L2 * (n-2)

// The answer is then the sum of all of the relevant number of records.
// Sol = A0L0 + A0L1 + A0L2 + A1L0 + A1L1 + A1L2
//     = 1 + n + A0L2 + n + n * (n-1) + A0L2 * (n-2)
//     = 1 + n + n + n^2 - n + A0L2 * (n-1)
//     = n^2 + n + 1 + A0L2 * (n-1)

// TODO: We forgot the cases where there are many Ls but not consecutive.
// It might be shorter to do R - cases with more than one A
// - cases with more than 2 consecutive L
// + cases with both more than one A and more than 2 consecutive L

// Example: n=3
// All possible records are:
// "AAA", "AAL", "AAP", "ALA", "ALL*", "ALP*", "APA", "APL*", "APP*", -> 4
// "LAA", "LAL*", "LAP*", "LLA*", "LLL", "LLP*", "LPA*", "LPL*", "LPP*", -> 7
// "PAA", "PAL*", "PAP*", "PLA*", "PLL*", "PLP*", "PPA*", "PPL*", "PPP*" -> 8

// Solution is 19

