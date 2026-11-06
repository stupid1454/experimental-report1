#include <iostream>
#include <iomanip> // 用于控制输出格式 (setprecision)

using namespace std;

// 1. 定义内联函数：计算平方
inline double square(double x) {
    return x * x;
}

// 2. 定义带默认参数值的函数：计算乘幂
// 如果未给出指数，默认 exponent = 2，即计算平方
double power(double base, int exponent = 2) {
    double result = 1.0;
    if (exponent == 0) return 1.0; // 任何非零数的0次方为1
    
    int abs_exponent = exponent > 0 ? exponent : -exponent;
    for (int i = 0; i < abs_exponent; ++i) {
        result *= base;
    }
    
    // 处理负指数的情况
    return (exponent > 0) ? result : (1.0 / result);
}

// 3. 定义两个重载函数：实现基本运算
// 版本一：处理 double 类型的操作数
double calc(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0.0) {
                cout << "Error: divide by zero" << endl;
                return 0.0; // 发生错误时返回 0.0
            }
            return a / b;
        default:
            cout << "Error: invalid operator" << endl;
            return 0.0;
    }
}

// 版本二：处理 int 类型的操作数
double calc(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                cout << "Error: divide by zero" << endl;
                return 0.0;
            }
            return (double)a / b; // 强制类型转换，避免整数除法丢失精度
        default:
            cout << "Error: invalid operator" << endl;
            return 0.0;
    }
}

int main() {
    double num1, num2;
    char op;

    // 从标准输入读取两个操作数和一个运算符
    cout << "请输入两个操作数和一个运算符 (例如: 3.5 2.0 +): ";
    if (!(cin >> num1 >> num2 >> op)) {
        return 1; // 输入格式错误
    }

    // 设置输出格式为保留两位小数
    cout << fixed << setprecision(2);

    cout << "--- 计算结果 ---" << endl;

    // 依次调用 square()、power() 和 calc() 函数
    // 这里我们使用读取到的第一个操作数进行单目运算演示
    
    // 调用内联函数
    cout << "1. square(" << num1 << ") = " << square(num1) << endl;

    // 调用带默认参数的函数 (不传第二个参数，触发默认值 2)
    cout << "2. power(" << num1 << ") [默认指数为2] = " << power(num1) << endl;

    // 调用重载函数
    cout << "3. calc(" << num1 << ", " << num2 << ", '" << op << "') = ";
    
    // 针对除数为 0 的情况做特殊处理，避免多打印一个 0.00
    if (op == '/' && num2 == 0.0) {
        calc(num1, num2, op); // 该函数内部会打印错误提示
    } else {
        // 正常情况：因为读取的是 double 类型，这里会自动匹配到 double 版本的重载函数
        cout << calc(num1, num2, op) << endl;
    }

    return 0;
}

