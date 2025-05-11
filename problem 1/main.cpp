#include <iostream>
#include <string>
using namespace std;


struct Node {
    string url;
    Node* next;
    Node(const string& url)  {

        this->url=url;
        this->next= nullptr;
    }
};

Node* pop(Node*& stack) {
    if (stack == nullptr) {
        return nullptr;
    }
    Node* topNode = stack;
    stack = stack->next;
    return topNode;
}


void push(Node*& stack, const string& url) {
    Node* newNode = new Node(url);
    newNode->next = stack;
    stack = newNode;
}


void clearStack(Node*& stack) {
    while (stack != nullptr) {
        Node* temp = stack;
        stack = stack->next;
        delete temp;
    }
}

void printStack(Node* stack) {
    Node* current = stack;
    while (current != nullptr) {
        std::cout << current->url << " , ";
        current = current->next;
    }

}
class BrowserHistory {
private:


    Node* backStack;
    Node* forwardStack;
    string currentUrl;



public:
    BrowserHistory() : backStack(nullptr), forwardStack(nullptr), currentUrl("") {}


    void visit(const string& url) {
//        if (!currentUrl.empty()) {
//            push(backStack, currentUrl);
//        }
        currentUrl = url;
        push(backStack, currentUrl);
        clearStack(forwardStack);


        cout<<"visit ("<<currentUrl << ")"<<endl;


        cout << "backStack: ";
        printStack(backStack);
        cout << endl;

        cout << "forwardStack: ";
        printStack(forwardStack);
        cout << endl;

        cout << "currentUrl: " << currentUrl << endl;
        cout<<endl;
        cout<<endl;

    }


    void goBack() {
        if (backStack == nullptr) {
            cout << "Cannot go back: No history" << endl;
            return;
        }
        push(forwardStack, currentUrl);

        Node* prevNode = pop(backStack);
        currentUrl = prevNode->next->url;
        delete prevNode;
        cout << "GOBackWord " << endl;

        cout << "backStack: ";
        printStack(backStack);
        cout << endl;

        cout << "forwardStack: ";
        printStack(forwardStack);
        cout << endl;

        cout << "currentUrl: " << currentUrl << endl;
        cout<<endl;
        cout<<endl;
    }


    void goForward() {
        if (forwardStack == nullptr) {
            cout << "Cannot go forward: No forward history" << endl;
            return;
        }
        push(backStack, currentUrl);
        Node* nextNode = pop(forwardStack);
        currentUrl = nextNode->url;
        delete nextNode;
        cout << "GOForward() "  << endl;

        cout << "backStack: ";
        printStack(backStack);
        cout << endl;

        cout << "forwardStack: ";
        printStack(forwardStack);
        cout << endl;

        cout << "currentUrl: " << currentUrl << endl;
        cout<<endl;
        cout<<endl;
    }


    string getCurrentUrl() const {
        return currentUrl;
    }


    ~BrowserHistory() {
        clearStack(backStack);
        clearStack(forwardStack);
    }
};

int main() {
    BrowserHistory browser;

    browser.visit("https://www.google.com");
    browser.visit("https://www.wikipedia.org");
    browser.visit("https://www.youtube.com");

    browser.goBack();  // Should go back to "wikipedia.org"
    browser.goBack();  // Should go back to "google.com"
    browser.goForward();  // Should go forward to "wikipedia.org"
    browser.visit("https://www.facebook.com");  // Clear forward history

    return 0;
}
