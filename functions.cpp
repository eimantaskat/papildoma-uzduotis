#include "functions.hpp"

multiset< pair<string, int> > read_text(const string &file_name) {
    stringstream buffer;

    std::fstream file (file_name);
    if (!file) {
        std::cout << "Failas neegzistuoja\n";
        multiset< pair<string, int> > t;
        return t;
    }
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
    // string t = "uv";

    stringstream w_output, url_output;

    std::vector<int> lines;
    string prev = (*((words.begin()))).first;

    url_output << "URL's:\n";
    w_output << left << setw(43) << "Žodis" << left << setw(10) << "Kartojasi\n"; // << " Eilutės, kuriose yra žodis\n";
    int count = 0;
    for (auto iter = words.begin(); iter != words.end(); iter++) {
        // if ((*iter).first.find(t) < (*iter).first.size())
        //     count++;

        
        if (prev == (*iter).first)
            lines.push_back((*iter).second);
        else {
            if (!is_url(prev)) {
                if (lines.size() > 1) {
                    w_output << left << setw(44 + count_ltu_letters(prev)) << prev << right << setw(3) << lines.size() << "  ";
                    // for (int l:lines)
                    //     w_output << l << " ";
                    w_output << "\n";
                }
            } else {
                url_output << "\t" << prev << "\n";
            }

            prev = (*iter).first;
            lines.clear();
            lines.push_back((*iter).second);
        }
    }
    url_output << "\n";

    std::ofstream file (file_name);
    if (!file) {
        std::cout << "Nepavyko sukurti failo\n";
        return;
    }

    if (url_output.str().length() > 9)
        file << url_output.rdbuf();
    file << w_output.rdbuf();
    file.close();
    std::cout << "Rezultatas isvestas i faila " << file_name << "\n";
    // std::cout << t << " kartojasi " << count << " kartus\n"; 
}

void generate_md_table(const multiset< pair<string, int> >& words, const string &file_name) {
    stringstream table;
    int ln = 0;

    for (auto word:words) {
        if (word.second > ln)
            ln = word.second;
    }

    table << "|Žodis\\eitutė|";
    for (int i = 1; i <= ln; i++)
        table << i << "|";
    table << "\n";

    table << "|";
    for (int i = 0; i <= ln; i++)
        table << "---|";
    table << "\n";

    string prev = (*((words.begin()))).first;

    std::vector<int> lines;
    for (auto iter = words.begin(); iter != words.end(); iter++) {
        if (prev == (*iter).first)
            lines.push_back((*iter).second);
        else {
            if (!is_url(prev)) {
                if (lines.size() > 1) {
                    std::sort(lines.rbegin(), lines.rend());
                    table << "|" << prev << "|";
                    for (int i = 1; i <= ln; i++) {
                        if (i == lines.back()) {
                            table << "X|";
                            lines.pop_back();
                        } else {
                            table << "  |";
                        }
                    }
                    table << "\n";
                }
            }

            prev = (*iter).first;
            lines.clear();
            lines.push_back((*iter).second);
        }
    }
    
    std::ofstream file (file_name);
    if (!file) {
        std::cout << "Nepavyko sukurti failo\n";
        return;
    }

    file << table.rdbuf();
    file.close();

    std::cout << "Lentele sugeneruota i faila " << file_name << "\n";
}