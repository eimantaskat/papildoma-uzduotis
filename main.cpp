#include "functions.hpp"

int main() {
    auto words = read_text("text.txt");

    write_output(words, "output.txt");
    generate_md_table(words, "table.txt");
}