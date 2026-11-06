#include <iostream>
#include <string>
#include <cctype> // 用于 tolower() 函数

using namespace std;

// 1. 编写 countVowels 函数，参数为指向常量的指针 const char*
int countVowels(const char* p) {
    int count = 0;
    
    // 使用指针遍历字符串，直到遇到字符串结束符 '\0'
    while (*p != '\0') {
        // 将当前字符统一转换为小写，方便比较
        char ch = tolower(*p);
        
        // 判断是否为元音字母
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            count++;
        }
        
        // 指针后移，指向下一个字符
        p++; 
    }
    
    return count;
}

int main() {
    string input;
    
    // 2. 在主函数中输入一行字符串
    // 注意：不能只用 cin >> input，因为它遇到空格就会停止读取。
    // 需要使用 getline 才能读取包含空格的整行字符串（如 "Hello World"）
    getline(cin, input);
    // 调用函数，将 string 转换为 const char* 传入
    int result = countVowels(input.c_str());
    // 按照示例格式输出结果
    cout << "Number of vowels: " << result << endl;
    return 0;
}

