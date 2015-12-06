#ifdef __LIST_H_
#define __LIST_H_


// inspired from http://trestle.icarnegie.com/content/SSD/SSD5/2.2/normal/pg-linear/pg-linked-lists/pg-list-implementation/pg-list-implementation.html#list

template <typename T>
class LinkedList {

public:

	LinkedList(const LinkedList<T>& src);  // Copy constructor
	~LinkedList(void);  // Destructor
	LinkedList(void) : head(NULL), tail(NULL), count(0) {}

	// Returns a reference to first element
	T& front(void) {
		assert(head != NULL);
		return head->data;
	}

	// Returns a reference to last element
	T& back(void) {
		assert(tail != NULL);
		return tail->data;
	}

	// Returns count of elements of list
	int size(void) {
		return count;
	}

	// Returns whether or not list contains any elements
	bool empty(void) {
		return count == 0;
	}

	void push_front(T);  // Insert element at beginning
	void push_back(T);   // Insert element at end
	void pop_front(void);  // Remove element from beginning
	void pop_back(void);  // Remove element from end
};

// Copy constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& src) :
	head(NULL), tail(NULL), count(0) {

	Node* current = src.head;
	while (current != NULL) {
		this->push_back(current->data);
		current = current->next;
	}

}
// Destructor
template <typename T>
LinkedList<T>::~LinkedList(void) {

	while (!this->empty()) {
		this->pop_front();
	}
}

// Insert an element at the beginning
template <typename T>
void LinkedList<T>::push_front(T d) {

	Node* new_head = new Node(d, head);

	if (this->empty()) {
		head = new_head;
		tail = new_head;
	}
	else {
		head = new_head;
	}
	count++;
}

// Insert an element at the end
template <typename T>
void LinkedList<T>::push_back(T d) {

	Node* new_tail = new Node(d, NULL);

	if (this->empty()) {
		head = new_tail;
	}
	else {
		tail->next = new_tail;
	}

	tail = new_tail;
	count++;
}

// Remove an element from the beginning
template <typename T>
void LinkedList<T>::pop_front(void) {

	assert(head != NULL);

	Node* old_head = head;

	if (this->size() == 1) {
		head = NULL;
		tail = NULL;
	}
	else {
		head = head->next;
	}

	delete old_head;
	count--;
}

// Remove an element from the end
template <typename T>
void LinkedList<T>::pop_back(void) {

	assert(tail != NULL);

	Node* old_tail = tail;

	if (this->size() == 1) {
		head = NULL;
		tail = NULL;
	}
	else {

		// Traverse the list to node just before tail
		Node* current = head;
		while (current->next != tail) {
			current = current->next;
		}

		// Unlink and reposition
		current->next = NULL;
		tail = current;
	}

	delete old_tail;
	count--;
}

private:
	class Node {
		friend class LinkedList<T>;

	private:
		T data;
		Node* next;

	public:
		Node(T d, Node* n = NULL) : data(d), next(n) {}
	};

	Node* head;  // Beginning of list
	Node* tail;  // End of list
	int count;    // Number of nodes in list
};

#endif