//
// Created by YuzukiTsuru on 2021/3/21.
//
#include <fstream>
#include <string>

#include "FileIO.h"
#include "exception.h"

std::string Yisp::FileIO::read_from_file(const std::string &file_name) {
    std::ifstream File(file_name);
    std::string file_content = {};
    std::string buffer_content = {};
    if (File.is_open()) {
        while (std::getline(File, buffer_content)) {
            file_content += buffer_content;
        }
    } else {
        throw file_not_found("file name: " + file_name);
    }
    File.close();
    return file_content;
}
