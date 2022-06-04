#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iomanip>

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
    std::multiset< std::pair<std::string, int>> words;

    std::fstream f ("text1.txt");
    std::stringstream buffer;
    buffer << f.rdbuf();
    f.close();

    std::string word, ln;
    int line_number = 0;
    while(!buffer.eof()) {
        line_number++;
        std::getline(buffer, ln);
        std::stringstream line;
        line << ln;
        while (!line.eof()) {
            line >> word;
            word = remove_punctuation(word);
            if (word.size() > 0) 
                words.insert({word, line_number});
            word = "";
        }
    }

    std::ofstream of ("result.txt");
    std::multiset<std::pair<std::string, int>>::iterator iter;
    std::string prev = (*((words.begin()))).first;
    std::vector<int> lines;
    for (iter = words.begin();iter!=words.end();++iter) {
        if (prev == (*iter).first)
            lines.push_back((*iter).second);
        else {
            of << std::left << std::setw(44) << prev << "\t" << std::setw(5) << lines.size();
            for (int l:lines)
                of << l << " ";
            of << "\n";

            prev = (*iter).first;
            lines.clear();
            lines.push_back((*iter).second);
        }
    }
    of.close();
}