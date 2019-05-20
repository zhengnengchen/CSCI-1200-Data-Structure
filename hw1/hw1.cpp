#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

// Repeated work when print out a line in flush_left mode
void flush_left_line(std::ofstream &out_str,
                     std::string &one_line,
                     const std::string empty_line,
                     int &occupied_length) {
    out_str << one_line << std::endl;
    one_line = empty_line;
    occupied_length = 0;
}

// Repeated work when print out a line in flush_right mode
void flush_right_line(int &start_pos,
                      const int width,
                      int &occupied_length,
                      int &full,
                      std::vector<std::string> &line_words,
                      std::ofstream &out_str,
                      std::string &one_line,
                      const std::string empty_line) {
    start_pos += width - occupied_length;
    if (occupied_length <= width && full == 0) start_pos++;
    else full = 0;
    for (int j = 0; j < line_words.size(); ++j) {
        one_line.replace(start_pos, line_words[j].size(), line_words[j]);
        start_pos += line_words[j].size();
        if (j < line_words.size() - 1) start_pos++;
    }
    line_words.clear();
    flush_left_line(out_str, one_line, empty_line, occupied_length);
    start_pos = 2;
}

// Repeated work when print out a line in full_justify mode
void full_justify_line(int &full,
                       int &occupied_length,
                       std::vector<std::string> &line_words,
                       const int width,
                       std::string &one_line,
                       int &start_pos,
                       std::ofstream &out_str,
                       const std::string empty_line) {
    if (full == 0) occupied_length -= 1;
    else full = 0;
    int space1, space2;
    if (line_words.size() == 1 || line_words.size() == 2) {
        space1 = width - occupied_length - 1;
        space2 = 1;
    } else {
        space1 = (width - occupied_length) / (line_words.size() - 1);
        space2 = (width - occupied_length) % (line_words.size() - 1);
    }
    for (int j = 0; j < line_words.size(); ++j) {
        one_line.replace(start_pos, line_words[j].size(), line_words[j]);
        start_pos += line_words[j].size();
        if (j < space2) start_pos += space1 + 2;
        else if (j < line_words.size() - 1) start_pos += space1 + 1;
    }
    line_words.clear();
    flush_left_line(out_str, one_line, empty_line, occupied_length);
    start_pos = 2;
}

void process_str(const std::string mode,
                 std::ofstream &out_str,
                 const std::vector<std::string> input,
                 const int width,
                 std::string &one_line,
                 const std::string empty_line) {
    int start_pos = 2, occupied_length = 0, i = 0, full = 0;
    std::vector<std::string> line_words;
    while (i < input.size()) {
        if (input[i].size() > width) {
            // flush current line
            if (occupied_length != 0) {
                if (mode == std::string("flush_left")) flush_left_line(out_str, one_line, empty_line, occupied_length);
                else if (mode == std::string("flush_right")) flush_right_line(start_pos, width, occupied_length, full, line_words, out_str, one_line, empty_line);
                else full_justify_line(full, occupied_length, line_words, width, one_line, start_pos, out_str, empty_line);
            }
            // and write long word in a new line
            int count = input[i].size() / (width - 1);
            int res = input[i].size() % (width - 1);
            for (int j = 0; j < count - 1; ++j) {
                one_line.replace(start_pos, width, input[i].substr(j * (width - 1), width - 1) + "-");
                flush_left_line(out_str, one_line, empty_line, occupied_length);
            }
            if (res == 1) {
                one_line.replace(start_pos, width, input[i].substr((count - 1) * (width - 1), width));
                flush_left_line(out_str, one_line, empty_line, occupied_length);
            } else {
                one_line.replace(start_pos, width, input[i].substr((count - 1) * (width - 1), width - 1) + "-");
                flush_left_line(out_str, one_line, empty_line, occupied_length);
                if (mode == std::string("flush_left")) one_line.replace(start_pos, res, input[i].substr(count * (width - 1), res));
                else line_words.push_back(input[i].substr(count * (width - 1), res));
                occupied_length = res;
                if (occupied_length < width) occupied_length++;
            }
        } else if (occupied_length + input[i].size() > width) { // One line ends and to be flushed
            if (mode == std::string("flush_left")) flush_left_line(out_str, one_line, empty_line, occupied_length);
            else if (mode == std::string("flush_right")) flush_right_line(start_pos, width, occupied_length, full, line_words, out_str, one_line, empty_line);
            else full_justify_line(full, occupied_length, line_words, width, one_line, start_pos, out_str, empty_line);
            continue;
        } else { // Still have space to put in a new word
            if (mode == std::string("flush_left")) one_line.replace(start_pos + occupied_length, input[i].size(), input[i]);
            else line_words.push_back(input[i]);
            occupied_length += input[i].size();
            if (occupied_length < width) occupied_length += 1;
            else full = 1;
        }
        ++i;
    }
    // If there is something left at one_line to be write to file after all words are added to it
    if (occupied_length != 0) {
        if (mode == std::string("flush_left")) flush_left_line(out_str, one_line, empty_line, occupied_length);
        else if (mode == std::string("flush_right")) flush_right_line(start_pos, width, occupied_length, full, line_words, out_str, one_line, empty_line);
        else { // flush_left for the last line of full_justify
            for (int j = 0; j < line_words.size(); ++j) {
                one_line.replace(start_pos, line_words[j].size(), line_words[j]);
                start_pos += line_words[j].size();
                if (j < line_words.size() - 1) start_pos++;
            }
            flush_left_line(out_str, one_line, empty_line, occupied_length);
        }
    }
}

int main(int argc, char* argv[]) {
    // Check argument number, create I/O file descriptor and read in file into a vector of word strings
    if (argc != 5) {
        std::cerr << "Need 4 arguments" << std::endl;
        return 1;
    }
    std::ifstream in_str(argv[1]);
    if (!in_str.good()) {
        std::cerr << "Cannot open file " << std::string(argv[1]) << " to read" << std::endl;
        return 1;
    }
    std::ofstream out_str(argv[2]);
    if (!out_str.good()) {
        std::cerr << "Cannot open file " << std::string(argv[2]) << " to write" << std::endl;
        return 1;
    }
    std::string word;
    std::vector<std::string> input;
    while (in_str >> word) input.push_back(word);
    
    // Create a couple of strings to help output.
    char* command_line_width = argv[3];
    const int width = atoi(command_line_width);
    const std::string mode(argv[4]);
	const std::string dash_line(width + 4, '-');
    const std::string blanks(width + 2, ' ');
	const std::string empty_line = "|" + blanks + "|";
    std::string one_line = empty_line;
    
    out_str << dash_line << std::endl;
    // Main work to process file in 3 different mode using if-else condition
    if (mode == std::string("flush_left") ||
        mode == std::string("flush_right") ||
        mode == std::string("full_justify"))
        process_str(mode, out_str, input, width, one_line, empty_line);
    else {
        std::cerr << "Wrong mode in command line" << std::endl;
        return 1;
    }
    out_str << dash_line << std::endl;
    
    return 0;
}
