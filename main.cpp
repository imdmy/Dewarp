// main.cpp
#include <iostream>
#include <filesystem>
#include <string_view>
#include <vector>
#include "include/utils.h"
// #include <opencv2/opencv.hpp>


int main() {
    // 获取当前工作目录
    std::filesystem::path currentDir = std::filesystem::current_path();
    std::filesystem::current_path("G:\\pointcloudrendering\\CLionProj\\Dewarp");
    std::cout << currentDir << "\n";
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    // 执行命令并将输出保存到文件
    const char* picture_path{ "G:\\pointcloudrendering\\CLionProj\\Dewarp\\DJI_20241015160149_0003_D.JPG" }; //  图片路径
    // std::string cmd{ "cd .. && cd 3rdParty/exiftool-13.00_64 && exiftool.exe " + std::string(picture_path) }; //  执行的命令
    std::string cmd{ "cd 3rdParty/exiftool-13.00_64 && exiftool.exe " + std::string(picture_path) }; //  执行的命令
    const char* output_file{ "output.log" }; //  输出的文件路径


    int ret = run_cmd(cmd.c_str(), output_file);
    if (ret != 0) {
        print("failed to run {}", cmd);
        return ret;
    }

    print("done\npress any key to start read Dewarp Matrix\n");
    std::cin.get();

    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    // 从文件中提取去畸变矩阵数据
    const std::string targetPrefix = "Dewarp Data                     :";
    std::string extractedData = extract_data_from_file(output_file, targetPrefix);

    if (extractedData.empty()) {
        print("can't find dewarp matrix data in output.log\n");
        return 1;
    }

    // 查找分号并提取之后的数据
    size_t startPos = extractedData.find(";");
    if (startPos == std::string::npos) {
        std::cerr << "can't find ;" << std::endl;
        return 1;
    }
    std::string subData = extractedData.substr(startPos + 1);

    // 分析去畸变数据并存储
    std::vector<std::string> matrixData = parse_matrix_data(subData);

    if (matrixData.empty()) {

    }
    std::cout << "got data :" << std::endl;
    for (const auto& part : matrixData) {
        std::cout << part << std::endl;
    }

    // 参数序列 -（fx, fy, cx, cy, k1, k2, p1, p2, k3）
    // fx, fy - 标定的焦距(单位为像素)
    // cx, cy - 标定的光心位置（单位为像素，以相片中心为原点）
    // k1, k2, p1, p2, k3 - 径向畸变与切向畸变参数

    return dewarp(picture_path, matrixData);
}

int dewarp(const char* picPath, std::vector<std::string>& matrixData){
    using std::cout;
    cout << "picPath is " << picPath << std::endl;
    return 0;
}



//
//const int* const p = new int(10);
//int* p1 = p;
//int* const p2 = p;
//const int* p3 = p;


