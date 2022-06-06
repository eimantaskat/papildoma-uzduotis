#pragma once

#include "main.hpp"

char to_lower(const char&);
int count_ltu_letters(const string&);
void process_word(string&);
bool is_url(const string&);
bool is_word(const string&);
bool is_letter(const char&);

multiset< pair<string, int> > read_text(const string &);
void write_output(const multiset< pair<string, int> >&, const string&);