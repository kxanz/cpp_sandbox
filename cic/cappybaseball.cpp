#include <iostream>
#include <vector>
#include <string>

int calPoints(const std::vector<std::string>& ops) 
{
    std::vector<int> res;

    for (const std::string& op : ops) {

        if (op == "C") {
            res.pop_back();
        }
        else if (op == "D") {
            res.push_back(res.back() * 2);
        }
        else if (op == "+") {
            res.push_back(res[res.size() - 1] + res[res.size() - 2]);
        }
        else {
            res.push_back(std::stoi(op));
        }
    }

    int sum = 0;
    for (int score : res) sum += score;
    return sum;
}

int main() {
    std::vector<std::string> ops1 = {"5", "2", "C", "D", "+"};
    std::cout << calPoints(ops1) << "\n";   // 30

    std::vector<std::string> ops2 = {"5", "-2", "4", "C", "D", "9", "+", "+"};
    std::cout << calPoints(ops2) << "\n";   // 27

    return 0;
}
