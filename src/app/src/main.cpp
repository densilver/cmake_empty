#include <stdio.h>

struct Node;
struct Node {
	int val;
	Node* next;
};

struct List {
public:
	Node* new_node(int val) {
		Node* p = new Node;
		p->val = val;
		p->next = nullptr;
		return p;
	}
	
	Node* add_front(Node* p) {
		p->next = head;
		head = p;
		return p;
	}

	Node* add_end(Node* newp) {
		if (!head) {
			head = newp;
			return head;
		}
		Node* p = head;
		while (p->next) {
			p = p->next;
		}
		p->next = newp;
		return head;
	}

	Node* lookup(int val) {
		for (Node* p = head; p; p = p->next) {
			if (p->val == val) {
				return p;
			}
		}
		return nullptr;
	}

	Node* del_node(int val) {
		Node* prev = nullptr;
		for (Node* p = head; p; p = p->next) {
			if (p->val == val) {
				if (prev == nullptr) {
					head = p->next;
				} else {
					prev->next = p->next;
				}
				delete p;
				return head;
			}
			prev = p;
		}
		return head;
	}
	
	~List() {
		for (Node* next; head; head = next) {
			next = head->next;
			delete head;
		}
	}

private:
	Node* head = nullptr;
};

int main() {
	List nodes;

	nodes.add_front(nodes.new_node(0));
	nodes.add_front(nodes.new_node(1));
	nodes.add_front(nodes.new_node(2));

	nodes.del_node(1);
}
