#include "functions.hpp"

int main() {
    string file_name;
    multiset< pair<string, int> > words;
    while (!words.size()) {
        std::cout << "Iveskite failo pavadinima\n";
        std::cin >> file_name; 
        words = read_text(file_name);
    } 

    string selection;
    std::cout << "Ka norite daryti?:\n1 - Isvesti rezultata i faila\n2 - Sugeneruoti lentele\n3 - Isvesti rezultata i faila ir sugeneruoti lentele\n";
    while(true) {
        std::cin >> selection;
        if (check_select(selection)) {
            break;
        } else {
            std::cout << "Iveskite 1, 2 arba 3\n";
        }
    }
    
    int s = std::stoi(selection);
    string f_name;

    switch (s)
    {
    case 1:
        write_output(words, "output.txt");
        break;
    
    case 2:
        generate_md_table(words, "table.txt");
        break;

    case 3:
        write_output(words, "output.txt");
        generate_md_table(words, "table.txt");
        break;
    }
    
}