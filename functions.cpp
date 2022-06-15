/** @file */

#include "functions.h"
#include"structures.h"

void show_usage(std::string name) {
    std::cerr << "Usage: " << name << "<option(s)> SOURCES"
              << "Options:\n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t-o,--output FILE_PATH\tSpecify the output path\n"
              << "\t-i,--input FILE_PATH\tSpecify the input path\n"
              << std::endl;
}

void printArgs(int argc, char **argv) {
    std::cout << "You have entered " << argc
              << " arguments:" << "\n";

    for (int i = 0; i < argc; ++i)
        std::cout << argv[i] << "\n";

    std::cout << "\n\n\n";
}

treenode *new_node(char cha, int freq, treenode *left, treenode *right) {
    treenode *treenodee = new treenode();
    treenodee->charac = cha;
    treenodee->frequency = freq;
    treenodee->point0 = left;
    treenodee->point1 = right;

    return treenodee;
}

std::string text_from_input(std::string input) {
    std::string string_to_work_with, result;
    std::fstream inputt;
    inputt.open(input, std::ios::in | std::ios::out);
    while (!inputt.eof()) {
        std::getline(inputt, string_to_work_with);
        result += string_to_work_with + "\n";
    }
    return result;
}

treenode *build_tree(std::string text) {
    std::map<char, int> frequency;

    for (char chara: text) {
        if (frequency.count(chara) == 0) {
            frequency[chara] = 1;
        } else
            frequency[chara]++;
    }

    std::priority_queue<treenode *, std::vector<treenode *>, compare> priqueue;
    for (auto pair: frequency) {
        priqueue.push(new_node(pair.first, pair.second, NULL, NULL));
    }

    while (priqueue.size() != 1) {
        treenode *right = priqueue.top();
        priqueue.pop();
        treenode *left = priqueue.top();
        priqueue.pop();
        int newFrequency = right->frequency + left->frequency;
        priqueue.push(new_node((char) 0, newFrequency, left, right));
    }
    treenode *root = priqueue.top();

    return root;
}

std::vector<bool> compress(std::map<int, std::string> dict, std::string text) {
    std::string result = "";
    for (char c : text) {
        std::string code = dict[int(c)];
        result += code;
    }
    std::vector<bool> to_compress;
    for (int i = 0; i < result.size(); i++) {
        if (result[i] == '0') {
            to_compress.push_back(false);
        } else {
            to_compress.push_back(true);
        }
    }

    return to_compress;
}

void add_to_map(treenode *root, std::map<int, std::string> &huff_codes, std::string path) {
    if (root == NULL) return;

    if (root->point0 == NULL && root->point1 == NULL) {
        huff_codes[root->charac] = path;
    }

    add_to_map(root->point0, huff_codes, path + "0");
    add_to_map(root->point1, huff_codes, path + "1");
}

std::map<int, std::string> dictionary(treenode *root) {
    std::map<int, std::string> huff_codes;

    add_to_map(root, huff_codes, "");

    return huff_codes;
}

void write_dictionary(std::map<int, std::string> dict, std::string path) {
    std::fstream dictionary_file;
    dictionary_file.open(path, std::ios::in | std::ios::out | std::ios::trunc);
    for (auto pair : dict) {
        dictionary_file << int(pair.first) << " " << pair.second << "\n";
    }
    dictionary_file.close();
}

void compressed_file(std::vector<bool> text_after_compression, std::string path) {
    FILE *file = fopen(path.c_str(), "wb");
    if (file == NULL) {
        std::cerr << "Can't open file";
    }

    unsigned char zeroBits = text_after_compression.size() % 8;
    if (zeroBits != 0) {
        zeroBits = 8 - zeroBits;
    }
    fputc(zeroBits, file);

    for (int i = 0; i < text_after_compression.size(); i += 8) {
        int j = i;
        unsigned char result = 0;
        while (j < i + 8 and j < text_after_compression.size()) {
            if (text_after_compression[j] == 1) {
                int pow = i + 7 - j;
                result += (pow == 0) ? 1 : (2 << pow - 1);
            }
            j++;
        }
        fputc(result, file);
    }

    fclose(file);
}

std::map<std::string, int> read_dictionary(std::string path) {
    std::map<std::string, int> dictio_two;
    std::ifstream dictionary_file;
    dictionary_file.open(path, std::ios::in | std::ios::app);
    while (!dictionary_file.eof()) {
        char tempChar;
        int temp;
        std::string tempString;
        dictionary_file >> temp;
        dictionary_file >> tempString;
        tempChar = char(temp);
        dictio_two.emplace(std::make_pair(tempString, tempChar));
    }
    dictionary_file.close();
    return dictio_two;
}

std::string decompress(std::map<std::string, int> code_to_char, std::vector<bool> text) {
    std::string result = "";
    std::string prefix = "";

    for (int i = 0; i < text.size(); i++) {
        prefix += (text[i] == 1) ? "1" : "0";
        if (code_to_char.find(prefix) != code_to_char.end()) {
            result += code_to_char[prefix];
            prefix = "";
        }
    }
    return result;
}

std::vector<bool> decompressed_file(std::string path) {

    std::vector<bool> output_text;
    FILE* file = fopen(path.c_str(), "rb");
    unsigned char c = fgetc(file);
    unsigned char zeroBits = c;
    c = fgetc(file);
    unsigned char eof = 255;
    while (c != eof) {
        std::bitset<8> bitset(c);

        c = fgetc(file);
        int readUntil = (c == eof) ? zeroBits : 0;
        for (int i = 7; i >= readUntil; i--) {
            output_text.push_back(bitset[i]);
        }
    }
    fclose(file);
    return output_text;
}