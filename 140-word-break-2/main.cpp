// We can use a tree for this problem.
// Each node holds the next possible word in the string and the rest of the
// string.
// We build the tree from the root by going over the string in order.
// At each stage, we list all the next possible words given the current position
// in the string, and store them as children nodes along with the rest of the
// string.
// All possible word sequences are obtained by going over all tree leaves, and
// collecting words from the leaf to the root of the tree.

// Note there is a slight twist: the string must be used in its entierety.

// Solving the problem with an explicit tree is too cumbersome, so we do it
// through implicitely building and collecting from the tree with recursion.

// For space efficiency, the words are represented as indices into a collection
// of words, and the rest of the string is represented as an index into the
// string.

#include <iostream>
#include <vector>
#include <string>

class Solution {
private:
  // Index for words inside dictionary, dictionary is less than 1000 in size.
  typedef int WordIndex;
  typedef std::vector<std::string> WordDict;
  typedef std::vector<WordIndex> Sentence;
  typedef std::vector<Sentence> Sentences;

  std::vector<WordIndex> find_next_words(const WordDict &wordDict,
                                         const std::string &s) {
    // Find all the possible next words from the wordDict at the beginning of s.
    std::vector<WordIndex> possible_words;
    for (std::size_t i = 0; i < wordDict.size(); ++i) {
      auto w = wordDict.at(i);
      if (s.starts_with(w)) {
        possible_words.push_back(i);
      }
    }
    return possible_words;
  }

Sentences find_sentences(const WordDict &wordDict, const std::string &s,
                         const Sentence &sentence) {
  // Recursively building the sentences.
  // Stop if there is no more string s.
  Sentences finished_sentences {};
  if (s.empty()) {
    finished_sentences.push_back(sentence);
    return finished_sentences;
  }

  auto next_words = find_next_words(wordDict, s);
  // If there is no more matches, it means no full sentence can be built,
  // we return an empty result.
  if (next_words.empty()) {
    return finished_sentences;
  }

  // Add all possible newly constructed sentences to the set.
  // Remove the current sentence from the set of results.
  // Call the function on every new result.
  for (auto wi : next_words) {
    Sentence cur_sentence{sentence};
    cur_sentence.push_back(wi);
    auto word_size = wordDict.at(wi).size();
    auto next_string = s.substr(word_size);
    auto next_sentences = find_sentences(wordDict, next_string, cur_sentence);
    for (const auto &seq : next_sentences) {
      finished_sentences.push_back(seq);
    }
  }
  return finished_sentences;
}

std::string format_sentence(const Sentence &sentence,
                            const WordDict &wordDict) {
  // Get back a string from a sentence in efficient representation.
  std::string phrase{};
  for (const auto &wi : sentence) {
    phrase.append(wordDict.at(wi));
    phrase.append(" ");
  }
  phrase.pop_back(); // Remove superfluous space at the end.
  return phrase;
}

public:
  std::vector<std::string> wordBreak (std::string s,
                                      std::vector<std::string> &wordDict) {
    std::vector<std::string> phrases {};
    auto sentences = find_sentences(wordDict, s, Sentence {});
    for (auto sen : sentences) {
      auto phrase = format_sentence(sen, wordDict);
      phrases.push_back(phrase);
    }
    return phrases;
  }
};

int main () {
  std::cout << "140. Word break II" << std::endl;

  std::string ex1_s = "catsanddog";
  std::vector<std::string> ex1_wd = {"cat", "cats", "and", "sand", "dog"};

  std::string ex2_s = "pineapplepenapple";
  std::vector<std::string> ex2_wd = {"apple", "pen", "applepen", "pine",
                                     "pineapple"};

  std::string ex3_s = "catsandog";
  std::vector<std::string> ex3_wd = {"cats", "dog", "sand", "and", "cat"};

  Solution solver;
  auto ex1_phrases = solver.wordBreak(ex2_s, ex2_wd);
  for (auto phrase : ex1_phrases) {
    std::cout << phrase << std::endl;
  }
}
