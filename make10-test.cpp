#include <math.h>

#include <iostream>
#include <map>
#include <vector>
using namespace std;

// 2つの数の演算を指定された演算子によって行う
double cal(double first, double second, int op) {
    switch (op) {
        case 0:
            return first + second;
            break;
        case 1:
            return first - second;
            break;
        case 2:
            return first * second;
            break;
        case 3:
            return first / second;
            break;
        default:
            break;
    }
    return 0;
}

// 数字で管理している演算子を文字に直す関数
string change(int op) {
    switch (op) {
        case 0:
            return "+";
            break;
        case 1:
            return "-";
            break;
        case 2:
            return "×";
            break;
        case 3:
            return "÷";
            break;
        default:
            break;
    }
    return 0;
}

int main() {
    // 割り算を扱うため doubleで宣言
    vector<double> input(4);

    while (1) {
        // 入力を受け取る
        cin >> input[0] >> input[1] >> input[2] >> input[3];
        if(input[0] == -1) break;

        // 配列をsortする
        sort(input.begin(), input.end());

        // next_permutationを用いて順列の全探索
        bool check = false;
        while (1) {
            // 4つの数の間に入る演算子を全探索
            for (int op1 = 0; op1 < 4; op1++) {
                for (int op2 = 0; op2 < 4; op2++) {
                    for (int op3 = 0; op3 < 4; op3++) {
                        double ans = 0;

                        // patern1[n1 op1 n2) op2 n3) op3 n4]
                        ans += cal(input[0], input[1], op1);
                        ans = cal(ans, input[2], op2);
                        ans = cal(ans, input[3], op3);
                        // 正解があれば出力
                        if (ans == 10) {
                            cout << "((" << input[0] << change(op1) << input[1]
                                 << ")";
                            cout << change(op2) << input[2] << ")";
                            cout << change(op3) << input[3] << endl;
                            check = true;
                            break;
                        }

                        // patern2[(n1 op1 n2) op2 (n3 op3 n4)]
                        double temp1 = 0, temp2 = 0;
                        temp1 += cal(input[0], input[1], op1);
                        temp2 += cal(input[2], input[3], op3);
                        ans = cal(temp1, temp2, op2);
                        // 正解があれば出力
                        if (ans == 10) {
                            cout << "(" << input[0] << change(op1) << input[1]
                                 << ")";
                            cout << change(op2);
                            cout << "(" << input[2] << change(op3) << input[3]
                                 << ")" << endl;
                            check = true;
                            break;
                        }

                        // pattern3[割り算の例外処理]
                        // double temp1 = 0, temp2 = 0;
                        if (op1 == 3 || op2 == 3 || op3 == 3) {
                            // n4 op3 (n3 op2 (n1 op1 n2))
                            ans += cal(input[0], input[1], op1);
                            ans = cal(input[2], ans, op2);
                            ans = cal(input[3], ans, op3);

                            // 正解があれば出力
                            if (ans == 10) {
                                cout << input[3] << change(op3);
                                cout << "(" << input[2] << change(op2);
                                cout << "(" << input[0] << change(op1)
                                     << input[1] << "))" << endl;
                                check = true;
                                break;
                            }
                        } else if (op1 == 3 || op2 == 3) {
                            // (n3 op2 (n1 op1 n2)) op3 n4
                            ans += cal(input[0], input[1], op1);
                            ans = cal(input[2], ans, op2);
                            ans = cal(ans, input[3], op3);

                            // 正解があれば出力
                            if (ans == 10) {
                                cout << "(" << input[2] << change(op2);
                                cout << "(" << input[0] << change(op1)
                                     << input[1] << "))";
                                cout << change(op3) << input[3] << endl;
                                check = true;
                                break;
                            }
                        } else if (op1 == 3 || op3 == 3) {
                            // n4 op3 ((n1 op1 n2) op2 n3)
                            ans += cal(input[0], input[1], op1);
                            ans = cal(ans, input[2], op2);
                            ans = cal(input[3], ans, op3);

                            // 正解があれば出力
                            if (ans == 10) {
                                cout << input[3] << change(op3) << endl;
                                cout << "((" << input[0] << change(op1)
                                     << input[1] << ")";
                                cout << change(op2) << input[2] << ")" << endl;
                                check = true;
                                break;
                            }
                        } else {
                            continue;
                        }
                    }
                    if(check) break;
                }
                if(check)break;
            }
            if(check) break;

            // falseを返した時に探索を終了
            if (!next_permutation(input.begin(), input.end())) break;
        }

        // 該当なし
        if(!check)cout << "Not found" << endl;
    }
    return 0;
}
