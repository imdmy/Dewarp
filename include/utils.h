//
// Created by Admin on 24-11-18.
//

#ifndef UTILS_H
#define UTILS_H


#include <format>
#include <string>
#include <vector>
#include <cstdio>

template<typename... Args>
void print(const std::string_view fmt_str, Args&&... args) {
    std::string outstr{ std::vformat(fmt_str, std::make_format_args(args...)) }; // // 构建对象，包含所有传入的格式化参数 然后字符串格式化
    fputs(outstr.c_str(), stdout);
}

int run_cmd(const char* cmd, const char* output_file);
std::string extract_data_from_file(const std::string& file_name, const std::string& target_prefix);
std::vector<std::string> parse_matrix_data(const std::string& data);

int dewarp(const char* picPath, std::vector<std::string>& matrixData);


#endif //UTILS_H
