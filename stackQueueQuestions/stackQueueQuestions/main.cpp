//
//  main.cpp
//  stackQueueQuestions
//
//  Created by Davan Basran on 2018-07-12.
//  Copyright © 2018 Davan Basran. All rights reserved.
//

#include <iostream>
#include <stack>
#include <deque>

using namespace std;

template <typename T>
class MultiStack {
public:
    explicit MultiStack(size_t stackSize, size_t numberOfStacks) : mStackSize(stackSize), mNumberOfStacks(numberOfStacks) {
        mArray = new T[stackSize * numberOfStacks];
        memset(mArray, 0, sizeof(T) * stackSize * numberOfStacks);
        mSize = new T[numberOfStacks];
        memset(mSize, 0, sizeof(T) * numberOfStacks);
    }
    
    virtual ~MultiStack() {
        delete[] mArray;
        delete[] mSize;
    }
    
    virtual void push(T item, size_t stackNum) {
        if (isFull(stackNum)) {
            throw;
        }
        
        ++mSize[stackNum - 1];
        auto index {getTopIndex(stackNum)};
        mArray[index] = item;
    }
    
    virtual T pop(size_t stackNum) {
        if (isEmpty(stackNum)) {
            throw;
        }
        
        T value {peek(stackNum)};
        mArray[getTopIndex(stackNum)] = 0;
        --mSize[stackNum - 1];
        return value;
    }
    
    size_t getCapacity() const {
        return mStackSize;
    }
    
    size_t getSize(size_t stackNum) const {
        return mSize[stackNum - 1];
    }
    
    T peek(size_t stackNum) const {
        T value {mArray[getTopIndex(stackNum)]};
        return value;
    }
    
    bool isFull (size_t stackNum) const {
        return (mSize[stackNum - 1] == mStackSize);
    }
    
    bool isEmpty(size_t stackNum) const {
        return (mSize[stackNum - 1] == 0);
    }

private:
    size_t getTopIndex(size_t stackNumebr) const {
        size_t offset {mStackSize * (stackNumebr - 1)};
        size_t topIndex {offset + mSize[stackNumebr - 1] - 1};
        return topIndex;
    }
    
    size_t mStackSize;
    size_t mNumberOfStacks;
    T* mArray;
    T* mSize;
};

template <typename T>
class MultiStackWithMin : public MultiStack<T> {
public:
    explicit MultiStackWithMin(size_t stackSize, size_t numberOfStacks) : MultiStack<T>(stackSize, numberOfStacks) {
        minStack = new MultiStack<T>(stackSize, numberOfStacks);
        mFirstPush = new bool[numberOfStacks];
        memset(mFirstPush, true, sizeof(bool) * numberOfStacks);
    }
    
    ~MultiStackWithMin() {
        delete minStack;
        delete[] mFirstPush;
    }
    
    void push(T item, size_t stackNum) override {
        if (item < minStack->peek(stackNum) && !isFirstPush(stackNum)) {
            minStack->push(item, stackNum);
        }
        if (isFirstPush(stackNum)) {
            minStack->push(item, stackNum);
            mFirstPush[stackNum - 1] = false;
        }
        MultiStack<T>::push(item, stackNum);
    }
    
    T pop(size_t stackNum) override {
        auto item = MultiStack<T>::pop(stackNum);
        if (item == minStack->peek(stackNum)) {
            minStack->pop(stackNum);
        }
        return item;
    }
    
    T min(size_t stackNum) const {
        return minStack->peek(stackNum);
    }
    
private:
    bool isFirstPush(size_t stackNum) {
        return mFirstPush[stackNum - 1];
    }
    
    MultiStack<T>* minStack;
    bool* mFirstPush;
};

template <typename T>
class QueueFromStacks {
public:
    QueueFromStacks(size_t capacity) : mCapacity(capacity), mSize(0) {
        popStack = new MultiStack<T>(mCapacity, 1);
        pushStack = new MultiStack<T>(mCapacity, 1);
    }
    
    ~QueueFromStacks() {
        delete popStack;
        delete pushStack;
    }
    
    void enqueue(T item) {
        pushStack->push(item, 1);
        ++mSize;
    }
    
    T dequeue() {
        if (isEmpty()) {
            throw;
        }
        --mSize;
        if (popStackEmpty()) {
            switchStacks(pushStack, popStack);
        }
        auto item {popStack->pop(1)};
        if (popStackEmpty()) {
            switchStacks(pushStack, popStack);
        }
        return item;
    }
    
    T peek() const {
        if (popStackEmpty()) {
            switchStacks(pushStack, popStack);
        }
        return popStack->peek(1);
    }
    
    bool isFull() const {
        return (mSize == mCapacity);
    }
    
    bool isEmpty() const {
        return (mSize == 0);
    }

private:
    void switchStacks(MultiStack<T>* source, MultiStack<T>* destination) {
        while (!source->isEmpty(1)) {
            destination->push(source->pop(1), 1);
        }
    }
    
    bool popStackEmpty() const {
        return popStack->isEmpty(1);
    }
    
    bool pushStackEmpty() const {
        return pushStack->isEmpty(1);
    }
    
    size_t mCapacity;
    size_t mSize;
    MultiStack<T>* popStack;
    MultiStack<T>* pushStack;
};

template <typename T>
void stackSort(MultiStack<T>& stack) {
    MultiStack<T> temp(stack.getCapacity(), 1);
    while (!stack.isEmpty(1)) {
        // insert elements in stack into sorted order into temp
        T tempBox = stack.pop(1);
        while (tempBox < temp.peek(1) && !temp.isEmpty(1)) {
            stack.push(temp.pop(1), 1);
        }
        temp.push(tempBox, 1);
    }
    // copy back elements from temp into stack
    while (!temp.isEmpty(1)) {
        stack.push(temp.pop(1), 1);
    }
}

class Animal {
public:
    Animal(const string& name) : mName(name) {}
    virtual ~Animal() {};
    
    size_t getOrder() const {
        return mOrder;
    }
    
    void setOrder(size_t order) {
        mOrder = order;
    }
    
    string getName() const {
        return mName;
    }
    
    static bool compareAnimal (const Animal& lhs, const Animal& rhs) {
        return (lhs.getOrder() < rhs.getOrder());
    }
    
private:
    string mName;
    size_t mOrder;
};

class Dog : public Animal {
public:
    Dog(const string& name) : Animal(name) {};
};
    
class Cat : public Animal {
public:
    Cat(const string& name) : Animal(name) {};
};

class AnimalShelter {
public:
    AnimalShelter() : mOrder(0) {}
    
    void enqueue(Animal pet) {
        pet.setOrder(mOrder++);
        try {
            Dog* dog {dynamic_cast<Dog*>(&pet)};
            dogs.push_back(*dog);
        } catch (bad_cast) {}
        try {
            Cat* cat {dynamic_cast<Cat*>(&pet)};
            cats.push_back(*cat);
        } catch (bad_cast) {
            throw;
        }
    }
    
    Animal dequeueAny() {
        Dog dog {dogs.front()};
        Cat cat {cats.front()};
        bool returnDog {compareOrder(dog, cat)};
        if (returnDog) {
            dogs.pop_front();
            return dog;
        }
        else {
            cats.pop_front();
            return cat;
        }
    }
    
    Animal dequeueDog() {
        Dog dog {dogs.front()};
        dogs.pop_front();
        return dog;
    }
    
    Animal dequeueCat() {
        Cat cat {cats.front()};
        cats.pop_front();
        return cat;
    }
    
private:
    bool compareOrder(const Animal& dog, const Animal& cat) {
        return Animal::compareAnimal(dog,cat);
    }
    
    deque<Dog> dogs;
    deque<Cat> cats;
    size_t mOrder;
};

class Calculator {
public:
    static double calculate(const string& equation) {
        
    }

private:

};

int main(int argc, const char * argv[]) {
    MultiStack<int> stacks(3, 2);
    stacks.push(3, 1);
    stacks.push(2, 1);
    stacks.push(1, 1);
    
    stacks.push(3, 2);
    stacks.push(2, 2);
    stacks.push(1, 2);
    
    for(int i = 0; i < 3; ++i) {
        cout << stacks.pop(1) << " ";
    }
    cout << endl;
    for(int i = 0; i < 3; ++i) {
        cout << stacks.pop(2) << " ";
    }
    cout << endl;
    
    MultiStackWithMin<int> minStacks(3, 2);
    minStacks.push(3, 1);
    minStacks.push(1, 1);
    minStacks.push(2, 1);
    
    minStacks.push(3, 2);
    minStacks.push(1, 2);
    minStacks.push(2, 2);
    for(int i = 0; i < 3; ++i) {
        cout << "min " << minStacks.min(1) << " popping " << minStacks.pop(1) << endl;
    }
    cout << endl;
    for(int i = 0; i < 3; ++i) {
        cout << "min " << minStacks.min(2) << " popping " << minStacks.pop(2) << endl;
    }
    cout << endl;
    
    QueueFromStacks<int> queue(4);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    
    for(int i = 0; i < 2; ++i) {
        cout << queue.dequeue() << endl;
    }
    
    queue.enqueue(5);
    queue.enqueue(6);
    
    for(int i = 0; i < 4; ++i) {
        cout << queue.dequeue() << endl;
    }
    cout << endl;
    
    MultiStack<int> stack(8, 1);
    stack.push(5, 1);
    stack.push(10, 1);
    stack.push(7, 1);
    stack.push(12, 1);
    stack.push(8, 1);
    stack.push(3, 1);
    stack.push(1, 1);
    
    stackSort(stack);
    for(int i = 0; i < 7; ++i) {
        cout << stack.pop(1) << " ";
    }
    cout << endl;
    
    AnimalShelter as;
    Dog d {"Joe"};
    Cat c {"Joe2"};
    as.enqueue(d);
    as.enqueue(c);
    for (int i = 0; i < 2; ++i) {
        auto pet = as.dequeueAny();
        if (pet.getName() == "Joe") {
            cout << "DOG" << " ";
        }
        else {
            cout << "CAT" << " ";
        }
    }
    cout << endl;
    
    as.enqueue(c);
    as.enqueue(d);
    for (int i = 0; i < 2; ++i) {
        auto pet = as.dequeueAny();
        if (pet.getName() == "Joe") {
            cout << "DOG" << " ";
        }
        else {
            cout << "CAT" << " ";
        }
    }
    cout << endl;
}
