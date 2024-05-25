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

// Recursively building the sentences.
Sentences find_sentences(const WordDict &wordDict, const std::string &s,
                         const Sentence &sentence) {
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

std::string format_sentence (const Sentence &sentence, const WordDict &wordDict) {
  // Get back a string from a sentence in efficient representation.
  std::string phrase{};
  for (const auto &wi : sentence) {
    phrase.append(wordDict.at(wi));
    phrase.append(" ");
  }
  phrase.pop_back(); // Remove superfluous space at the end.
  return phrase;
}

int main () {
  std::cout << "140. Word break II" << std::endl;

  std::string ex1_s = "catsanddog";
  WordDict ex1_wd = {"cat", "cats", "and", "sand", "dog"};

  std::string ex2_s = "pineapplepenapple";
  WordDict ex2_wd = {"apple","pen","applepen","pine","pineapple"};

  std::string ex3_s = "catsandog";
  WordDict ex3_wd = {"cats","dog","sand","and","cat"};

  auto ex1_sentences = find_sentences(ex1_wd, ex1_s, Sentence {});
  for (auto sen : ex1_sentences) {
    auto phrase = format_sentence(sen, ex1_wd);
    std::cout << phrase << std::endl;
  }

  auto ex2_sentences = find_sentences(ex2_wd, ex2_s, Sentence{});
  for (auto sen : ex2_sentences) {
    auto phrase = format_sentence(sen, ex2_wd);
    std::cout << phrase << std::endl;
  }

  auto ex3_sentences = find_sentences(ex3_wd, ex3_s, Sentence{});
  for (auto sen : ex3_sentences) {
    auto phrase = format_sentence(sen, ex3_wd);
    std::cout << phrase << std::endl;
  }
}
