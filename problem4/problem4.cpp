#include <iostream>
using namespace std;

const int SIZE = 50;

struct node {
    string name;
    int severity;
    int timestamp;

    node() {}
    node(string n, int s, int t) {
        name = n;
        severity = s;
        timestamp = t;
    }
};

class priority_queue {
    node heap[SIZE];
    int count;

    void swap(node &a, node &b) {
        node temp = a;
        a = b;
        b = temp;
    }

    bool hasHigherPriority(node a, node b) {
        return (a.severity > b.severity) ||
               (a.severity == b.severity && a.timestamp < b.timestamp);
    }

public:
    priority_queue() {
        count = 0;
    }

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void insert(node x) {
        if (count >= SIZE) {
            cout << "Heap is full (Overflow)." << endl;
            return;
        }

        int current = count;
        heap[current] = x;
        count++;

        while (current > 0 && hasHigherPriority(heap[current], heap[parent(current)])) {
            swap(heap[current], heap[parent(current)]);
            current = parent(current);
        }
    }

    void print_heap() {
        priority_queue tempPQ;
        for (int i = 0; i < count; i++) {
            tempPQ.insert(heap[i]);
        }

        // Extract and print nodes in sorted order
        cout << "Sorted Queue (by severity and timestamp):\n";
        while (tempPQ.count > 0) {
            node maxPatient = tempPQ.extract_max();
            cout << maxPatient.name << " (S:" << maxPatient.severity << ", T:" << maxPatient.timestamp << ")\n";
        }
    }


    node peek() {
        if (count == 0) {
            cout << "Queue is empty.\n";
            return node(); 
        }
        return heap[0];
    }

    node extract_max() {
    if (count == 0) {
        cout << "Queue is empty.\n";
        return node(); 
    }

    node maxPatient = heap[0];
    heap[0] = heap[count - 1]; 
    count--;

    int current = 0;
    while (true) {
        int l = left(current);
        int r = right(current);
        int largest = current;

        if (l < count && hasHigherPriority(heap[l], heap[largest]))
            largest = l;
        if (r < count && hasHigherPriority(heap[r], heap[largest]))
            largest = r;

        if (largest != current) {
            swap(heap[current], heap[largest]);
            current = largest;
        } else {
            break;
        }
    }

    return maxPatient;
}


};


int main() {
    priority_queue pq;

    pq.insert(node("Ali", 3, 2));
    pq.insert(node("Sara", 5, 1));
    pq.insert(node("Ziad", 5, 0));
    pq.insert(node("Omar", 1, 3));

    cout << "Initial Queue:\n";
    pq.print_heap();

    cout << "\nTop Priority Patient (peek):\n";
    node top = pq.peek();
    cout << top.name << " (S:" << top.severity << ", T:" << top.timestamp << ")\n";

    cout << "\nAfter Extracting Max:\n";
    node treated = pq.extract_max();
    cout << "Treated: " << treated.name << endl;
    pq.print_heap();

    return 0;
}

