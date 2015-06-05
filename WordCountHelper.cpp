#include "WordCountHelper.h"
#include <algorithm>  //stable_sort
#include <vector>
#include <sstream> //ostringstream


WordCountHelper::WordCountHelper() { }

int WordCountHelper::getNumWords() const { // returns number of words in vocabulary
   return vocabulary.size(); 
}

int WordCountHelper::incrWordCount(std::string word) { // if word not in vocabulary, add it then increment occurence count for that word and return the count
    auto wordcount = vocabulary.find(word);
    if(wordcount == vocabulary.end()) {
      vocabulary[word] = 1;
      return 1;
    }
    else  {
        (wordcount->second)++;
        return wordcount->second;
    }
}

int WordCountHelper::getWordCount(std::string word) const { // if word does not exist in vocabulary, return 0, otherwise return count.
    auto wordcount = vocabulary.find(word);
    return (wordcount == vocabulary.end()) ? 0 : wordcount->second;
}

void WordCountHelper::dumpWordsSortedByWord(std::ostream &out) const { // dump each word,count pair as CSV to std::ostream, sorted by word
    for(auto word:vocabulary) {
        out << word.first << "," << word.second << std::endl;
    }
}

void WordCountHelper::dumpWordsSortedByOccurence(std::ostream &out) const { // dump each word,count as CSV to std::ostream, sorted decreasing by occurence
    std::vector<strIntPair> sortedByOccurence(vocabulary.begin(), vocabulary.end());
    std::stable_sort(sortedByOccurence.begin(), sortedByOccurence.end(),
        [](const strIntPair &a, const strIntPair &b){ return (a.second > b.second);});
    for(auto word:sortedByOccurence) {
        out << word.first << "," << word.second << std::endl;
    }
}

void WordCountHelper::addAllWords(std::string text) { // parse out text into individual words, and add each word
    std::string word;
    std::istringstream iss(text);
    while(iss >> word) {
        incrWordCount(stripWord(word));
    }
}

std::string WordCountHelper::stripWord(std::string word) { 
    while(!isWordChar(word[0])) {
        word.erase(0, 1);
    }
    int i = word.length();
    while(!isWordChar(word[i-1])) {
        word.erase(i-1, i);
        i--;
    }
    return word;
}

bool WordCountHelper::isWordChar(char c) {
  return
    (c >=65 && c <= 90) ||   // upper case
    (c >=97 && c <= 122) ||  // lower case
    (c >=48 && c <= 57 );    // digits
}

