#include "functions.hpp"

multiset< pair<string, int> > read_text(const string &file_name) {
    stringstream buffer;

    std::fstream file (file_name);
    buffer << file.rdbuf();
    file.close();

    multiset< pair<string, int>> words;
    string word, ln;
    int line_number = 0;

    while(!buffer.eof()) {
        line_number++;
        std::getline(buffer, ln);
        stringstream line;
        line << ln;
        while (!line.eof()) {
            line >> word;
            if (is_word(word) || is_url(word)) {
                process_word(word);
                if (word.size() > 0) {
                    if (is_url(word))
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

void write_output(const multiset< pair<string, int> > &words, const string &file_name) {
    stringstream w_output, url_output;

    std::vector<int> lines;
    string prev = (*((words.begin()))).first;

    url_output << "URL's: ";
    w_output << left << setw(39) << "Žodis" << left << setw(10) << "Kartojasi" << " Eilutės, kuriose yra žodis\n";
    for (auto iter = words.begin(); iter != words.end(); iter++) {
        if (prev == (*iter).first)
            lines.push_back((*iter).second);
        else {
            if (!is_url(prev)) {
                if (lines.size() > 1) {
                    w_output << left << setw(44 + count_ltu_letters(prev)) << prev << right << setw(3) << lines.size() << "  ";
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
    url_output << "\n\n";

    std::ofstream file (file_name);
    if (url_output.str().length() > 9)
        file << url_output.rdbuf();
    file << w_output.rdbuf();
    file.close();
}