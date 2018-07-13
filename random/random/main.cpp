//
//  main.cpp
//  random
//
//  Created by Davan Basran on 2018-07-10.
//  Copyright © 2018 Davan Basran. All rights reserved.
//

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

// 1.1
bool isUnique1(const string& str) {
    unordered_set<char> set;
    for (auto s : str) {
        auto it = set.find(s);
        if (it != set.end()) return false;
        set.emplace(s);
    }
    return true;
}

bool isUnique2(const string& str) {
    bool bucket[256]{false};
    for (auto s : str) {
        if (bucket[s - 'a']) return false;
        bucket[s] = true;
    }
    return true;
}

// 1.2
bool isPerm(const string& str1, const string& str2) {
    if (str1.length() != str2.length()) return false;
    int bucket[256]{0};
    for (auto s : str1) {
        ++(bucket[s - 'a']);
    }
    for (auto s : str2) {
        --(bucket[s - 'a']);
    }
    for (auto i : bucket) {
        if (i) return false;
    }
    return true;
}

// 1.4
bool isPermPalindrome(const string& str) {
    int bucket[256]{0};
    for (auto s : str) {
        ++(bucket[s - 'a']);
    }
    bool foundOdd {false};
    for (auto i : bucket) {
        if (i % 2 == 1) {
            if (!foundOdd) foundOdd = true;
            else return false;
        }
    }
    return true;
}

// 1.9
bool isRotation(const string& str, const string& str2) {
    string newStr {str + str};
    auto res = newStr.find(str2);
    if (res != string::npos) return true;
    return false;
}

// medium

// 16.8
string intToEnglish(int num) {
    
    return "";
}

// 16.17
int largestContigiousSum(const vector<int>& list) {
    if (list.size() == 0) return numeric_limits<int>::min();
    if (list.size() == 1) return list[0];
    
    size_t endIndex = list.size();
    int sum {0};
    int maxSum {numeric_limits<int>::min()};
    
    for (size_t i = 0; i < endIndex; ++i) {
        sum += list[i];
        maxSum = max(maxSum, sum);
        // if including the number goes below 0, then no number after will make the sum
        // greater than just including the next number, reset the sum
        if (sum < 0) sum = 0;
    }
    
    return maxSum;
}

// 16.22
enum class Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

struct Position {
    int x;
    int y;
};

struct Ant {
    Direction direction;
    Position position;
};

struct Node {
    Node* nodes[4];
    Position position;
    bool colour; // 0 = white, 1 = black
};

Direction getNewDirection(Direction origin, bool newOrientation) {
    switch (origin) {
        case Direction::UP:
            return newOrientation ? Direction::RIGHT : Direction::LEFT;
        case Direction::RIGHT:
            return newOrientation ? Direction::DOWN : Direction::UP;
        case Direction::DOWN:
            return newOrientation ? Direction::LEFT : Direction::RIGHT;
        case Direction::LEFT:
            return newOrientation ? Direction::UP : Direction::DOWN;
    }
}

Node& nextMove(Ant& ant, Node& node) {
    bool colour {node.colour};
    Direction newDir = getNewDirection(ant.direction, colour);
    Node* newNode {new Node{{nullptr, nullptr, nullptr, nullptr}, {0, 0}, 0}};
    node.nodes[static_cast<int>(newDir)] = newNode;
    colour = !colour; // flip colour
    
    return *newNode;
}

void printKMoves(int k) {
    Ant ant {Direction::RIGHT, {0, 0}};
    Node root {{nullptr, nullptr, nullptr, nullptr}, {0, 0}, 0};
    
    Node next = nextMove(ant, root);
    --k;
    while (k > 0) {
        next = nextMove(ant, next);
        --k;
    }
}

int main(int argc, const char * argv[]) {
    string str1 {"abcdef"};
    string str2 {"afbedc"};
    string str3 {"abcdeg"};
    string str4 {"abcde"};
    
    string str5 {"tacocat"};
    string str6 {"hello"};
    string str7 {"tacoocat"};
    
    string str8 {"waterbottle"};
    string str9 {"erbottlewat"};
    string str10 {"bluewaterbottle"};
    string str11 {"erbottleredwat"};
    
    vector<int> vec {2, -8, 3, -2, 4, -10};
    vector<int> vec2 {-2, -8, -3, -2, -4, -10};
    vector<int> vec3 {2, -8, -3, -2, 4, -10};
    vector<int> vec4 {2, 3, -8, -1, 2, 4, -2, 3};
    
//    cout << isUnique2(str1) << endl;
//    cout << isUnique2(str2) << endl;
//
//    cout << isPerm(str1, str2) << endl;
//    cout << isPerm(str1, str3) << endl;
//    cout << isPerm(str1, str4) << endl;
//
//    cout << isPermPalindrome(str5) << endl;
//    cout << isPermPalindrome(str6) << endl;
//    cout << isPermPalindrome(str7) << endl;
//
//    cout << isRotation(str9, str8) << endl;
//    cout << isRotation(str11, str10) << endl;
    
    cout << largestContigiousSum(vec) << endl; // 5
    cout << largestContigiousSum(vec2) << endl; // -2
    cout << largestContigiousSum(vec3) << endl; // 4
    cout << largestContigiousSum(vec4) << endl; // 10
    
    return 0;
}
