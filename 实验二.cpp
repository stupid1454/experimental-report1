#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>

using namespace std;

// ================= 模块一：常量与数据结构 =================
const double FEE_RATE = 0.02;           // 充值手续费率
const double WARNING_BALANCE = 10.0;    // 低余额警戒值

struct Card {
    int id;             // 学号
    string name;        // 姓名
    double balance;     // 当前余额
    int transactions;   // 交易次数
};

// ================= 模块二：命名空间与格式化输出 =================
namespace card {
    // 打印分隔线
    void printLine(char c = '-', int len = 60) {
        for (int i = 0; i < len; ++i) {
            cout << c;
        }
        cout << endl;
    }
    
    // 打印标题
    void title(const string& s) {
        printLine('=');
        int padding = (60 - s.length()) / 2;
        for (int i = 0; i < padding; ++i) cout << " ";
        cout << s << endl;
        printLine('=');
    }
}

// ================= 模块三：动态内存管理与录入 =================
Card* createCards(int n) {
    return new Card[n]; 
}

void destroyCards(Card* p) {
    delete[] p;
}

void inputCards(Card* arr, int n) {
    for (int i = 0; i < n; ++i) {
        cout << "请输入第 " << (i + 1) << " 个账户的学号、姓名和初始余额: ";
        cin >> arr[i].id >> arr[i].name >> arr[i].balance;
        
        // 模块九：输入异常检测
        if (arr[i].balance < 0) {
            throw invalid_argument("初始余额不能为负数！");
        }
        arr[i].transactions = 0; // 交易次数初始化为0
    }
}

// ================= 模块四：账户操作 =================
void deposit(Card& c, double amount, double feeRate = FEE_RATE) {
    if (amount <= 0) throw invalid_argument("充值金额必须大于0");
    double fee = amount * feeRate;
    c.balance += (amount - fee);
    c.transactions++;
}

bool spend(Card& c, double cost) {
    // 模块九：消费异常处理
    if (cost <= 0) throw invalid_argument("消费金额必须大于0");
    if (cost > c.balance) throw runtime_error("余额不足，无法完成消费！");

    c.balance -= cost;
    c.transactions++;
    return true;
}

// 函数重载
bool spend(Card& c, double cost, const string& item) {
    cout << "消费项目: " << item << endl;
    return spend(c, cost); 
}

void showBalance(const Card& c) {
    cout << "当前余额: " << fixed << setprecision(2) << c.balance << " 元" << endl;
}

void viewStudentID(const Card* p) {
    cout << "账户学号: " << p->id << endl;
}

// ================= 模块五：强制类型转换 =================
int toCent(double amount) {
    return static_cast<int>(amount * 100);
}

// ================= 模块六：报表输出 =================
void printReport(const Card* arr, int n) {
    card::printLine();
    cout << left 
         << setw(15) << "ID" 
         << setw(15) << "Name" 
         << setw(15) << "Balance" 
         << setw(15) << "Transactions" << endl;
    card::printLine();
    
    for (int i = 0; i < n; ++i) {
        cout << left 
             << setw(15) << arr[i].id 
             << setw(15) << arr[i].name 
             << setw(15) << fixed << setprecision(2) << arr[i].balance 
             << setw(15) << arr[i].transactions << endl;
    }
    card::printLine();
}

// ================= 模块八 & 九：主程序与异常捕获 =================
int main() {
    try {
        // 1. 输出系统标题，输入学生数量
        card::title("校园一卡通消费管理系统");

        int n;
        cout << "请输入学生数量: ";
        cin >> n;
        if (n <= 0) throw invalid_argument("学生数量必须大于0！");

        // 2. 动态创建账户数组并录入账户信息
        Card* cards = createCards(n);
        inputCards(cards, n);

        card::printLine();
        cout << ">>> 演示第一个账户的测试操作 <<<" << endl;

        // 3. 对第一个账户充值100元，消费8.5元（项目：食堂午餐）
        deposit(cards[0], 100.0);
        cout << "成功充值 100 元 (已扣除手续费)。" << endl;
        
        spend(cards[0], 8.5, "食堂午餐");
        cout << "消费完成。" << endl;

        // 4. 显示该账户余额与账户ID
        viewStudentID(&cards[0]);
        showBalance(cards[0]);

        // 低余额预警判断
        if (cards[0].balance < WARNING_BALANCE) {
            cout << "[警告] 您的余额已低于警戒值 " << WARNING_BALANCE << " 元！" << endl;
        }

        // 5. 将余额换算为分并输出
        int cents = toCent(cards[0].balance);
        cout << "账户余额(按分计): " << cents << " 分" << endl;

        // 6. 输出全部账户报表，最后释放动态内存
        cout << "\n>>> 全部账户信息报表 <<<" << endl;
        printReport(cards, n);

        destroyCards(cards);
        cout << "系统安全退出，内存已释放。" << endl;

    } 
    catch (const bad_alloc& e) {
        // 内存申请异常处理
        cerr << "【严重错误】内存分配失败: " << e.what() << endl;
    }
    catch (const exception& e) {
        // 通用异常捕获 (包括输入校验失败、消费余额不足等)
        cerr << "【操作异常】" << e.what() << endl;
    }

    return 0;
}
