#include <iostream>
#include <string>
#include "VecInt.hpp"


static void showVec(const VecInt &v, const std::string &name) {
    std::cout << name << " -> size: " << v.size()
              << ", capacity: " << v.capacity()
              << ", contents: ";
    v.print();
}


int main() {
    std::cout << "=== VecInt test program ===\n\n";


    // 1) Default constructor
    std::cout << "--- 1) Default constructor ---\n";
    VecInt a;
    showVec(a, "a (default)");
    std::cout << "Calling pop_back() on default-constructed vector (should be safe-ish):\n";
    a.pop_back();
    showVec(a, "a (after pop_back)");


    // 2) Parameterized constructor (size + value)
    std::cout << "\n--- 2) Parameterized constructor ---\n";
    VecInt b(3, 7); // three 7s
    showVec(b, "b (3 of 7)");


    // 3) push_back until triggers reserve once and then again
    std::cout << "\n--- 3) push_back tests ---\n";
    std::cout << "Push 8\n";
    b.push_back(8);
    showVec(b, "b");
    std::cout << "Push 9\n";
    b.push_back(9);
    showVec(b, "b");


    // 4) pop_back
    std::cout << "\n--- 4) pop_back tests ---\n";
    std::cout << "pop_back()\n";
    b.pop_back();
    showVec(b, "b");


    // 5) insert at beginning, middle, end and invalid insert
    std::cout << "\n--- 5) insert tests ---\n";
    std::cout << "insert(0, 100)  (at front)\n";
    b.insert(0, 100);
    showVec(b, "b");
    std::cout << "insert(2, 200)  (middle)\n";
    b.insert(2, 200);
    showVec(b, "b");
    std::cout << "insert(size(), 300)  (at end)\n";
    b.insert(b.size(), 300);
    showVec(b, "b");
    std::cout << "insert(invalid index) -> should print 'Invalid index' message\n";
    b.insert(b.size() + 5, 999); // invalid


    // 6) erase at beginning, middle, last, invalid
    std::cout << "\n--- 6) erase tests ---\n";
    std::cout << "erase(0)  (remove first)\n";
    b.erase(0);
    showVec(b, "b");
    if (b.size() >= 3) {
        std::cout << "erase(2)  (remove middle)\n";
        b.erase(2);
        showVec(b, "b");
    } else {
        std::cout << "Skipping erase(2) because size < 3\n";
    }
    if (b.size() > 0) {
        std::cout << "erase(last)  (remove last)\n";
        b.erase(b.size() - 1);
        showVec(b, "b");
    }
    std::cout << "erase(invalid index) -> should print 'Invalid index' message\n";
    b.erase(b.size()); // invalid


    // 7) clear (should set size to 0 but keep capacity)
    std::cout << "\n--- 7) clear test ---\n";
    std::cout << "Before clear:\n";
    showVec(b, "b");
    std::cout << "b.clear()\n";
    b.clear();
    showVec(b, "b (after clear)");


    // 8) push_back after clear (capacity should remain, size grows)
    std::cout << "\n--- 8) push_back after clear ---\n";
    b.push_back(55);
    b.push_back(66);
    showVec(b, "b");


    // 9) Copy constructor: c is copy of b
    std::cout << "\n--- 9) copy constructor ---\n";
    VecInt c(b);
    showVec(b, "b (original)");
    showVec(c, "c (copy of b)");


    std::cout << "Mutate c (push_back and insert) and show that b remains unchanged if deep copy works\n";
    c.push_back(77);
    c.insert(1, 88);
    showVec(c, "c (after modifications)");
    showVec(b, "b (should be unchanged)");


    // 10) Copy assignment operator
    std::cout << "\n--- 10) copy assignment operator ---\n";
    VecInt d(1, 1);
    showVec(d, "d (before assign)");
    d = c;
    showVec(d, "d (after d = c)");
    std::cout << "Mutate d (pop_back) -> c should remain unchanged\n";
    d.pop_back();
    showVec(d, "d (after pop_back)");
    showVec(c, "c (should be unchanged)");


    // self-assignment test
    std::cout << "\n--- 11) self-assignment test ---\n";
    std::cout << "d = d (self-assignment)\n";
    d = d; // should be handled safely
    showVec(d, "d (after self-assign)");


    // 12) assignment between differently sized/capacity vectors
    std::cout << "\n--- 12) assignment capacity tests ---\n";
    VecInt e(10, 9); // large capacity
    showVec(e, "e (10 of 9)");
    std::cout << "Assign e = c (c is smaller):\n";
    e = c;
    showVec(e, "e (after e = c)");
    std::cout << "Now assign c = e (larger to smaller):\n";
    c = e;
    showVec(c, "c (after c = e)");


    // 13) growth test: start with capacity 1 and push many times to exercise reserve
    std::cout << "\n--- 13) growth/reserve behavior test ---\n";
    VecInt growth(1, 42); // start small
    showVec(growth, "growth (initial)");
    for (int i = 0; i < 10; ++i) {
        growth.push_back(100 + i);
        std::cout << "After push " << i << " -> size: " << growth.size()
                  << ", capacity: " << growth.capacity() << '\n';
    }
    std::cout << "Final growth contents: ";
    growth.print();


    // final: show all vectors one more time
    std::cout << "\n--- Final state of vectors ---\n";
    showVec(a, "a");
    showVec(b, "b");
    showVec(c, "c");
    showVec(d, "d");
    showVec(e, "e");
    showVec(growth, "growth");


        // 14) operator[] and operator== tests
    std::cout << "\n--- 14) operator[] and operator== tests ---\n";


    VecInt f(5, 1); // f = [1, 1, 1, 1, 1]
    VecInt g(5, 1); // g = [1, 1, 1, 1, 1]
    VecInt h(5, 2); // h = [2, 2, 2, 2, 2]


    showVec(f, "f");
    showVec(g, "g");
    showVec(h, "h");


    std::cout << "Check if f == g: " << (f == g ? "true" : "false") << '\n'; // should be true
    std::cout << "Check if f == h: " << (f == h ? "true" : "false") << '\n'; // should be false


    std::cout << "Modify g[2] = 9\n";
    g[2] = 9;
    showVec(g, "g (after modification)");
    std::cout << "Now check f == g: " << (f == g ? "true" : "false") << '\n'; // should be false


    std::cout << "Accessing g[2]: " << g[2] << '\n'; // should be 9
    std::cout << "Trying to access out-of-bounds index g[10]...\n";
    try {
        int val = g[10]; // should throw
        std::cout << "Unexpected: g[10] = " << val << '\n';
    } catch (const std::out_of_range&) {
        std::cout << "Caught out_of_range exception as expected\n";
    }


    std::cout << "\n=== Test program complete ===\n";
    return 0;
}
