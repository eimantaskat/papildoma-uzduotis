#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <algorithm>

char to_lower(char const c) {
    std::string lt_upper = "ĄČĘĖĮŠŲŪŽ";
    std::string lt_lower = "ąčęėįšųūž";
    for (int i = 0; i < lt_upper.size(); i++) {
        if (c == lt_upper[i])
            return lt_lower[i];
    }
    return std::tolower(c);
}

std::string remove_punctuation(std::string word) {
    std::string symbols = "(),.[]-„“\"\':;%!?/<>|\\{}+=-*&^%$#@~`”•€–0123456789°½¢£";
    for (char c: symbols)
        word.erase(std::remove(word.begin(), word.end(), c), word.end());

    std::transform(word.begin(), word.end(), word.begin(), to_lower);
    return word;
}


int main() {
    // std::multiset< std::pair<std::string, int>, std::less<std::string> > words;
    std::multiset< std::string, std::less<std::string> > words;
    std::fstream f ("text.txt");
    std::string word;
    int ln = 0;
    while(!f.eof()) {
        f >> word;
        // words.insert(remove_punctuation(word));
        word = remove_punctuation(word);
        if (word.size() > 0)
            words.insert(word);
    }
    f.close();

    words.erase("");
    words.erase("\n");
    std::ofstream of ("result.txt");
    std::multiset<std::string>::iterator iter;
    std::string prev = *(words.begin());
    int count = -1;
    for (iter = words.begin();iter!=words.end();++iter) {
        if (prev == *iter)
            count++;
        else {
            of << prev << " " << count + 1 << "\n";
            prev = *iter;
            count = 0;
        }
    }
    // for (iter = words.begin();iter!=words.end();++iter) {
    //     of << *iter << "\n";
    // }
    of.close();
}