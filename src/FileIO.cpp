//
// Created by YuzukiTsuru on 2021/3/21.
//
#include <fstream>

#include "FileIO.h"
#include "exception.h"

std::string Yisp::FileIO::read_from_file(const std::string& file_name) {
    std::ifstream File(file_name);
    std::string file_content = {};
    if (File.is_open()) {
        File >> file_content;
    } else {
        throw file_not_found("file name: " + file_name);
    }
    return file_content;
}
