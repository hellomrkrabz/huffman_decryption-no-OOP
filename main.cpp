/** @file */

#include<iostream>
#include<sstream>
#include <map>
#include<algorithm>

#include "functions.h"
#include "structures.h"

int main(int argc, char *argv[]){

    printArgs(argc, argv);

    if (argc < 5) {
        std::string s = argv[0];
        show_usage(s);
        return 1;
    }

    std::string input, output, mode, dictionary_path;
    for (int i = 1; i < argc; i++) {
        auto argument = std::string(argv[i]);
        if (argument == "-i" || argument == "--input") {
            input = argv[i + 1];
            std::cout << "Input: " << input << "\n";
        } else if (argument == "-o" || argument == "--output") {
            output = argv[i + 1];
            std::cout << "Output: " << output << "\n";
        } else if (argument == "-m" || argument == "--mode") {
            mode = argv[i + 1];
            std::cout << "Mode: " << mode << "\n";
        } else if (argument == "-d" || argument == "--dictionary-file") {
            dictionary_path = argv[i + 1];
            std::cout << "Dictionary: " << dictionary_path << "\n";
        }
    }

    if (mode == "-c") {
        std::string text = text_from_input(input);
        treenode *final_tree = build_tree(text);
        std::map<int, std::string> dictio = dictionary(final_tree);
        write_dictionary(dictio, dictionary_path);
        std::vector<bool> compressed = compress(dictio, text);
        compressed_file(compressed, output);

    } else if (mode == "-d") {
        std::vector<bool> bits = decompressed_file(input);
        std::string decompressed = decompress(read_dictionary(dictionary_path), bits);

        std::fstream file;
        file.open(output, std::ios::in | std::ios::out | std::ios::trunc);
        file << decompressed;
        file.close();
    } else {
        std::cerr << "Unknown mode";
    }

    std::cout << "Done\n";
    return 0;
}