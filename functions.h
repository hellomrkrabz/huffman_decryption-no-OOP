/** @file */
#include "structures.h"

#ifndef functions_h
#define functions_h

/** Function used to show arguments that work with the project.
 * @param name is argv[0].
 * @return nothing.
 */
void show_usage(std::string name);

/** Function that prints entered arguments.
 * @param argc one of argument's parameter.
 * @param argv one of argument's parameter.
 * @return nothing.
 */
void printArgs(int argc, char** argv);

/**
 * Function that creates a new node used in tree.
 * @param cha character in treenode.
 * @param freq frequency of the character in treenode.
 * @param left pointer to another treenode.
 * @param right pointer to another treenode.
 * @return a new treenode.
 */
treenode* new_node(char cha, int freq, treenode* left, treenode* right );

/**
 * Function that builds the tree used in compression.
 * @param text input text based on which the tree is created.
 * @return built tree.
 */
treenode* build_tree(std::string text);

/**
 * Function that builds a map used to create dictionary.
 * @param root path throughout tree at the end of which there's a second parameter of map.
 * @return map used to create dictionary.
 */
std::map<int, std::string> dictionary(treenode* root);

/**
 * Function that writes dictionary file based on a map.
 * @param dict a map used to write dictionary.
 * @param path the path to a dictionary file.
 * @return nothing.
 */
void write_dictionary(std::map<int, std::string> dict, std::string path);

/**
 * Function that creates a file with compressed data.
 * @param text_after_compression compressed binary form of input.
 * @param path the path to a compressed file.
 */
void compressed_file(std::vector<bool> text_after_compression, std::string path);

/**
 * Function that compresses input text.
 * @param dict dictionary based on which the compression is performed.
 * @param text input text which is going to get compressed.
 * @return binary vector with compressed data.
 */
std::vector<bool> compress(std::map<int, std::string> dict, std::string text);

/**
 * A function that adds new data to a map.
 * @param root root from the tree.
 * @param huff_codes a map to which data is being added.
 * @param path the path throughout the tree.
 * @return nothing.
 */
void add_to_map(treenode *root, std::map<int, std::string> &huff_codes, std::string path);

/**
 * Function that creates a new map based on the dictionary file.
 * @param path the path to dictionary file.
 * @return a new map.
 */
std::map<std::string, int> read_dictionary(std::string path);

/**
 * Function that completes the decompression.
 * @param code_to_char a map based on which the decompression is performed.
 * @param text binary vector that is a compressed version of text that is being decompressed.
 * @return decompressed text.
 */
std::string decompress(std::map<std::string, int> code_to_char, std::vector<bool> text);

/**
 * Function that saves the decompressed version to a file.
 * @param path the path to file in which the text will be saved.
 * @return the output.
 */
std::vector<bool> decompressed_file(std::string path);

/**
 * Function that makes a string ready to work with from the input file.
 * @param input the file that program will be working with.
 * @return string that program will be able to work with.
 */
std::string text_from_input (std::string input);

#endif