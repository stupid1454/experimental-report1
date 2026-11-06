#include <iostream>
#include <iomanip> // 引入输入输出格式化控制库
#include <string>

using namespace std;

int main() {
    int n;
    // 1. 读取学生人数
    if (!(cin >> n)) return 0;

    // 循环处理每个学生的信息
    for (int i = 0; i < n; ++i) {
        string name;
        double chinese, math, english;
        
        // 2. 读取每位学生的姓名和三门成绩
        cin >> name >> chinese >> math >> english;
        
        // 计算平均分
        double average = (chinese + math + english) / 3.0;
        
        // 3. 格式化输出
        // left: 左对齐
        // setw(10): 设置姓名输出宽度为10个字符，保证列对齐
        // fixed 和 setprecision(2): 强制保留两位小数
        cout << left << setw(10) << name 
             << fixed << setprecision(2) 
             << setw(7) << chinese 
             << setw(7) << math 
             << setw(7) << english 
             << setw(7) << average;
             
        // 判断平均分是否大于等于90，是则输出 Excellent
        if (average >= 90.0) {
            cout << "Excellent";
        }
        
        // 换行
        cout << endl;
    }

    return 0;
}

