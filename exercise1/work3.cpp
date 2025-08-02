//
// Created by lyx on 2025/7/31.
//
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

int main(){
    system("chcp 65001");
    std::string text;
    std::cout << "请输入一段文本 : \n";

    // 读取整段文本
    std::ostringstream oss;
    std::string line;
    while(std::getline(std::cin, line)){
        oss << line << " ";
    }
    text = oss.str();

    // 创建一个字符串流
    std::stringstream ss(text);
    // 创建一个单词映射
    std::string word;
    // map统计单词出现的次数
    std::map<std::string, int> wordCount;
    // 统计单词数
    size_t totalWords = 0;
    // 最长的单词
    std::string longestWord;

    //从字符串流中读取单词
    while(ss >> word){
        // 删除标点符号
        word.erase(std::remove_if(word.begin(), word.end(), [](char c){
            return ispunct(c);
        }), word.end());

        // 转为小写
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        // 若不为空
        if(!word.empty()){
            // 该单词单词数加一
            wordCount[word]++;
            // 总单词数加一
            totalWords++;
            // 判断最长单词
            if(word.length() > longestWord.length()){
                longestWord = word;
            }
        }
    }

    std::cout << "\n 统计结果 \n";
    std::cout << "总单词数：" << totalWords << "\n";
    std::cout << "每个单词出现的次数：\n";
    for(const auto &pair : wordCount){
        std::cout << pair.first << ": " << pair.second << "\n";
    }
    std::cout << "最长单词：" << longestWord << "\n";

    // 查找指定单词出现次数
    std::string searchWord;
    std::cout << "\n请输入要查找的单词：";
    std::cin >> searchWord;
    std::transform(searchWord.begin(), searchWord.end(), searchWord.begin(), ::tolower);
    auto it = wordCount.find(searchWord);
    if(it != wordCount.end()){
        std::cout << "单词" << searchWord << "出现的次数为：" << it->second << "\n";
    } else {
        std::cout << "单词" << searchWord << "未找到\n";
    }
    return 0;
}