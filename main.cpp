#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iomanip>
#include <regex>

char to_lower(char const c) {
    std::string lt_upper = "ĄČĘĖĮŠŲŪŽ";
    std::string lt_lower = "ąčęėįšųūž";
    for (int i = 0; i < lt_upper.size(); i++) {
        if (c == lt_upper[i])
            return lt_lower[i];
    }
    return std::tolower(c);
}

int count_ltu_letters(std::string const word) {
    int count = 0;
    for (char letter:word) {
        if ((int)letter > 255 || (int)letter < 0)
            count++;
    }
    return count/2;
}

std::string process_word(std::string word) {
    std::string symbols = "(),.[]-„“\"\':;%!?/<>|\\{}+=-*&^%$#@~`”•€–0123456789°½¢£";
    for (char c: symbols) {
        if (*(word.begin()) == c)
            word.erase(word.begin());

        if (*(word.end() - 1) == c)
            word.erase(word.end() - 1);
    }

    std::transform(word.begin(), word.end(), word.begin(), to_lower);
    return word;
}

bool is_url(std::string const str) {
    std::regex reg(".*www\\..*\\..*");
    return std::regex_match(str, reg);
}

bool is_word(std::string const str) {
    int alpha = 0;
    for (char c:str) {
        if (isalpha(c))
            alpha++;
    }
    return (alpha > str.size()/1.5);
}

std::multiset< std::pair<std::string, int> > read_text(std::string const file_name) {
    std::stringstream buffer;

    std::fstream file (file_name);
    buffer << file.rdbuf();
    file.close();

    std::multiset< std::pair<std::string, int>> words;
    std::string word, ln;
    int line_number = 0;

    while(!buffer.eof()) {
        line_number++;
        std::getline(buffer, ln);
        std::stringstream line;
        line << ln;
        while (!line.eof()) {
            line >> word;
            if (is_word(word) || is_url(word)) {
                word = process_word(word);
                if (word.size() > 0) {
                    if (is_url(word))
                        // std::cout << word << " ";
                        words.insert({word, -1});
                    else
                        words.insert({word, line_number});
                }
            }
            word = "";
        }
    }

    return words;
}

void write_output(std::multiset< std::pair<std::string, int> > const &words, std::string const file_name = "output.txt") {
    std::stringstream w_output, url_output;

    std::vector<int> lines;
    std::string prev = (*((words.begin()))).first;

    url_output << "URL's: ";
    w_output << std::left << std::setw(39) << "Žodis" << std::left << std::setw(10) << "Kartojasi" << " Eilutės, kuriose yra žodis\n";
    for (auto iter = words.begin(); iter != words.end(); iter++) {
        if (prev == (*iter).first)
            lines.push_back((*iter).second);
        else {
            if (!is_url(prev)) {
                if (lines.size() > 1) {
                    w_output << std::left << std::setw(44 + count_ltu_letters(prev)) << prev << std::right << std::setw(3) << lines.size() << "  ";
                    for (int l:lines)
                        w_output << l << " ";
                    w_output << "\n";
                }
            } else {
                url_output << prev << " ";
            }

            prev = (*iter).first;
            lines.clear();
            lines.push_back((*iter).second);
        }
    }

    // for (auto iter = words.begin(); iter != words.end(); iter++) {
    //     w_output << (*iter).first << "\n";
    // }
    url_output << "\n\n";

    std::ofstream file (file_name);
    if (url_output.str().length() > 9)
        file << url_output.rdbuf();
    file << w_output.rdbuf();
    file.close();
}

int main() {
    auto words = read_text("text.txt");

    write_output(words);
    // std::cout << process_word("medalis");
}