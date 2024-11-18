//
// Created by Admin on 24-11-18.
//
// utils.cpp

#include "include/utils.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>


// 运行命令并将输出写入文件
int run_cmd(const char* cmd, const char* output_file) {
    char MsgBuff[1024];
    int MsgLen = 1020;
    FILE* fp;
    FILE* out_fp = fopen(output_file, "w");

    if (out_fp == nullptr) {
        std::cerr << "无法打开输出文件: " << output_file << std::endl;
        return -1;
    }

    if (cmd == nullptr) {
        fclose(out_fp);
        return -1;
    }

    if ((fp = _popen(cmd, "r")) == nullptr) {
        fclose(out_fp);
        return -2;
    }

    memset(MsgBuff, 0, MsgLen);
    while (fgets(MsgBuff, MsgLen, fp) != nullptr) {
        fprintf(out_fp, "%s", MsgBuff);
    }

    if (_pclose(fp) == -1) {
        fclose(out_fp);
        return -3;
    }

    fclose(out_fp);
    return 0;
}

// 从文件中提取包含特定前缀的数据行
std::string extract_data_from_file(const std::string& file_name, const std::string& target_prefix) {
    std::ifstream file(file_name);
    if (!file) {
        std::cerr << "can't open file: " << file_name << std::endl;
        return "";
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find(target_prefix) == 0) {
            if (line.length() > target_prefix.length()) {
                return line.substr(target_prefix.length() + 1); // 跳过冒号
            }
        }
    }

    print("can't find string behind: {}\n", target_prefix);
    return "";
}

// 将数据字符串按逗号分隔并存储到向量中
std::vector<std::string> parse_matrix_data(const std::string& data) {
    std::vector<std::string> results;
    size_t pos = 0, commaPos;

    while ((commaPos = data.find(",", pos)) != std::string::npos) {
        results.push_back(data.substr(pos, commaPos - pos));
        pos = commaPos + 1;
    }

    if (pos < data.length()) {
        results.push_back(data.substr(pos)); // 最后一个部分
    }

    return results;
}

