//
//  main.cpp
//  LinkedListProblems
//
//  Created by Davan Basran on 2018-07-11.
//  Copyright © 2018 Davan Basran. All rights reserved.
//

#include <iostream>
#include <list>
#include <unordered_set>
#include <stack>

using namespace std;

struct Node {
    int data;
    Node* next;
};

// 2.1
void removeDuplicates(Node head) {
    unordered_set<int> set;
    set.insert(head.data);
    Node n = head;
    Node prev = head;
    
    n = *n.next;
    while (n != NULL) {
        if (set.find(n.data) != set.end()) {
            prev.next = n.next;
        }
        else {
            set.insert(n.data);
            prev = n;
        }
        n = *n.next;
    }
}

// 2.2
Node returnKthToLast(Node head, int k) {
    Node n = head;
    Node nSlow = head;
    
    for (int i = 0; i < k; ++i) {
        if (n == NULL) return NULL; // list not long enoough
        n = *n.next;
    }
    // n is k nodes ahead of positon of n - nSlow is k
    // iterate both pointers until n is at length and thus nSlow is at length - k
    while (n.next != NULL) {
        n = *n.next;
        nSlow = *nSlow.next;
    }
    return nSlow;
}

// 2.3
void deleteMiddleNode(Node middle) {
    Node n = middle;
    n.data = n.next->data;
    n.next = n.next->next;
}

// 2.4
Node partitionList(Node node, int part) {
    Node head = node;
    Node tail = node;
    
    while (node != NULL) {
        Node next = *node.next;
        if (node.data < part) {
            node.next = head;
            head = node;
        }
        else {
            tail.next = node;
            tail = node;
        }
        node = next;
    }
    tail.next = nullptr;
    
    return head;
}

// 2.5
Node addReverse(Node n1, Node n2) {
    int carry = 0;
    
    while (n1 != NULL && n2 != NULL) {
        int val = n1.data + n2.data + carry;
        carry = 0;
        if (val > 10) {
            carry = 1;
            val = val % 10;
        }
        n1.data = val;
        n1 = n1.next;
        n2 = n2.next;
    }
    if (n1 == NULL) {
        n1.next = n2;
    }
    return n1;
}

// 2.8
Node loop(Node n) {
    Node head = n;
    unordered_set<Node*> set;
    while (n != NULL) {
        if (set.find(&n) != set.end()) {
            return n;
        }
        else {
            set.insert(&n);
            n = n.next;
        }
    }
    return head;
}

Node addForward(Node n1, Node n2) {
    
}

// 2.6
bool palindrome(Node n1) {
    stack<int> stack;
    
    Node fast = n1;
    Node slow = n1;
    
    while (fast != NULL && fast.next != NULL) {
        stack.push(slow.data);
        slow = slow.next;
        fast = fast.next.next;
    }
    
    // skip middle element if list is odd sized
    if (fast != NULL) {
        slow = slow.next;
    }
    
    while (slow != NULL) {
        if (slow.data != stack.top()) {
            return false;
        }
        else {
            slow = slow.next;
            stack.pop();
        }
    }
}

int main(int argc, const char * argv[]) {
    list<int> list {0, 1, 3, 4, 4, 4, 5};
    
    return 0;
}
