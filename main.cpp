#include <iostream>
#include <fstream>
#include <stdexcept> 
using namespace std;
template<typename T>
class SinglyLinkedList {
private:
	struct Node {
		T data;
		Node* next;
		Node(const T& value) : data(value), next(nullptr) {}
	};
	int count;
	Node* head;
	Node* tail;
public:
	SinglyLinkedList() : head(nullptr), tail(nullptr), count(0) {} // Default constructor
	~SinglyLinkedList() { clear(); } // Destructor
	// Methods
	void push_front(const T& value) {
		Node* newNode = new Node(value);
		newNode->next = head;
		head = newNode;
		if (tail == nullptr) tail = newNode;
		count++;
	}
	void push_back(const T& value) {
		Node* newNode = new Node(value);
		if (head == nullptr) head = tail = newNode;
		else {
			tail->next = newNode;
			tail = newNode;
		} count++;
	}
	void pop_front() {
		if (head == nullptr) throw underflow_error("List is empty");
		Node* temp = head;
		head = head->next;
		delete temp;
		count--;
		if (head == nullptr) tail = nullptr;
	}

	void print_plus_one() { // Output the elements one after another.
		const Node* current = head;
		cout << "[";
		bool isFirst = true;
		while (current != nullptr) {
			if (!isFirst) { cout << ", "; }
			else { isFirst = false; }
			cout << current->data;
			current = current->next;
			if (current == nullptr) { break; }
			else { current = current->next; }
		} cout << "]" << endl;
	}

	void print() {
		const Node* current = head;
		cout << "[";
		while (current != nullptr) {
			cout << current->data;
			if (current->next != nullptr) cout << ", ";
			current = current->next;
		}
		cout << "]" << endl;
	}

	void clear() { // In the destructor and in loading from the file
		while (head != nullptr) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
		count = 0;
	}

	void saveToFile(const string& file) {
		ofstream f(file);
		int count = 0;
		const Node* temp = head;
		while (temp) { count++; temp = temp->next; }
		f << count << "\n";
		const Node* curr = head;
		while (curr) {
			f << curr->data << " ";
			curr = curr->next;
		} f.close();
	}

	void loadFromFile(const string& file) {
		ifstream f(file);
		clear();
		int count = 0;
		if (f >> count) {
			for (int i = 0; i < count; i++) {
				T value;
				if (f >> value) push_back(value);
			}
		} f.close();
	}
};

template<typename T>
class DoublyLinkedList {
private:
	struct DNode {
		T data;
		DNode* prev;
		DNode* next;
		DNode(const T&value) : data(value), prev(nullptr), next(nullptr) {}
	};
	DNode* head;
	DNode* tail;
	int count;
public:
	DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {} // Default constructor
	~DoublyLinkedList() { clear(); } // Destructor
	// Methods
	void push_front(const T& value) {
		DNode* newNode = new DNode(value);
		newNode->next = head;
		if (head != nullptr) head->prev = newNode;
		else tail = newNode;
		head = newNode;
		count++;
	}
	void push_back(const T& value) {
		DNode* newNode = new DNode(value);
		if (tail == nullptr) head = tail = newNode;
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		} count++;
	}
	void pop_front() {
		if (head == nullptr) throw underflow_error("List is empty");
		DNode* temp = head;
		head = head->next;
		if (head != nullptr) head->prev = nullptr;
		delete temp;
		count--;
		if (head == nullptr) tail = nullptr;
	}

	void print() {
		const DNode* current = head;
		cout << "[";
		while (current != nullptr) {
			cout << current->data;
			if (current->next != nullptr) cout << ", ";
			current = current->next;
		}
		cout << "]" << endl;
	}


	void rotateLeft(int k) { // Left circular shift by k positions
		if (head == nullptr || head->next == nullptr) return;
		int size = 0;
		DNode* current = head;
		while (current != nullptr) {
			size++;
			current = current->next;
		}
		k = k % size;
		if (k < 0) k = k + size;
		if (k == 0) return;
		DNode* newTail = head;
		for (int i = 0; i < k - 1; i++) newTail = newTail->next;
		DNode* newHead = newTail->next;
		newTail->next = nullptr;
		newHead->prev = nullptr;
		DNode* oldTail = newHead;
		while (oldTail->next != nullptr) {
			oldTail = oldTail->next;
		}
		oldTail->next = head;
		head->prev = oldTail;
		head = newHead;
		tail = newTail;
	}

	void clear() { // In the destructor and in loading from the file.
		while (head != nullptr) {
			DNode* temp = head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
		count = 0;
	}

	void saveToFile(const string& file) {
		ofstream f(file);
		int count = 0;
		const DNode* temp = head;
		while (temp) { count++; temp = temp->next; }
		f << count << "\n";
		const DNode* curr = head;
		while (curr) {
			f << curr->data << " ";
			curr = curr->next;
		} f.close();
	}

	void loadFromFile(const string& file) {
		ifstream f(file);
		clear();
		int count = 0;
		if (f >> count) {
			for (int i = 0; i < count; i++) {
				T value;
				if (f >> value) push_back(value);
			}
		} f.close();
	}
};

int main() {
	cout << "SinglyLinkedList:\n";
	SinglyLinkedList<int> list;
	list.push_back(10);
	list.push_back(20);
	list.push_back(30);
	list.push_front(5);
	cout << "List: ";
	list.print();
	
	list.pop_front();
	cout << "After pop_front: ";
	list.print();

	cout << "Output elements one by one: ";
	list.print_plus_one();

	cout << "\nSerialization test SinglyLinkedList\n";
	list.saveToFile("singly_data.txt");
	cout << "List is save in singly_data.txt" << endl;

	list.clear();
	cout << "List after clear: ";
	list.print();

	list.loadFromFile("singly_data.txt");
	cout << "List after load: ";
	list.print();

	cout << "\nDoublyLinkedList:\n";
	DoublyLinkedList<int> dlist;
	dlist.push_back(15);
	dlist.push_back(25);
	dlist.push_back(35);
	dlist.push_front(6);
	dlist.push_front(5);
	dlist.push_front(3);
	dlist.push_front(1);
	dlist.push_front(7);
	cout << "List: ";
	dlist.print();

	dlist.pop_front();
	cout << "After pop_front: ";
	dlist.print();

	dlist.rotateLeft(6);
	cout << "Rotate left: ";
	dlist.print();

	cout << "\nSerialization test DoublyLinkedList\n";
	dlist.saveToFile("doubly_data.txt");
	cout << "List save in doubly_data.txt" << endl;

	dlist.clear();
	cout << "List after clear: ";
	dlist.print();

	dlist.loadFromFile("doubly_data.txt");
	cout << "list after load: ";
	dlist.print();
	return 0;
}