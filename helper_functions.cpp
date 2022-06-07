#include "functions.hpp"

char to_lower(const char &c) {
    string lt_upper = "ĄČĘĖĮŠŲŪŽ";
    string lt_lower = "ąčęėįšųūž";

    for (int i = 0; i < lt_upper.size(); i++) {
        if (c == lt_upper[i])
            return lt_lower[i];
    }

    return std::tolower(c);
}

int count_ltu_letters(const string &word) {
    int count = 0;
    for (char letter:word) {
        if ((int)letter > 255 || (int)letter < 0)
            count++;
    }
    return count/2;
}

bool is_letter(const char &c) {
    string letters = "aąbcčdeęėfghiįyjklmnoprsštuųūvzž";
    for (char l:letters) {
        if (c == l)
            return true;
    }
    return false;
}

bool check_select(const string &s) {
    std::regex reg("[1-3]");
    return std::regex_match(s, reg);
}

void process_word(string &word) {
    string symbols = "(),.[]-„“\"\':;%!?/<>|\\{}+=-*&^%$#@~`”•€–0123456789°½¢£";
    
    for (char c: symbols) {
        if (*(word.begin()) == c)
            word.erase(word.begin());

        if (*(word.end() - 1) == c)
            word.erase(word.end() - 1);
    }

    std::transform(word.begin(), word.end(), word.begin(), to_lower);
}

bool is_url(const string &str) {
    return std::regex_match(str, std::regex (".*http.*\\..*")) || std::regex_match(str, std::regex (".*www.*\\..*")) || std::regex_match(str, std::regex (".*lt\\..*\\..*"));
}

bool is_word(const string &str) {
    int alpha = 0;
    for (char c:str) {
        if (is_letter(c))
            alpha++;
    }
    return (alpha > str.size()/1.5);
}