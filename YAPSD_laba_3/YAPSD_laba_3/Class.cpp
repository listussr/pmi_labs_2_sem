//#include<fstream>
//
//struct Node {
//	Node* next;
//	int val;
//
//	Node() {
//		next = nullptr;
//		val = 0;
//	}
//
//	Node(int v) {
//		next = nullptr;
//		val = v;
//	}
//
//	Node(int v, Node* n) {
//		next = n;
//		val = v;
//	}
//
//	~Node() {
//		next = nullptr;
//		delete next;
//	}
//};
//
//class forward_list {
//	Node* head;
//	int s;
//
//public:
//
//	forward_list();
//
//	forward_list(int);
//
//	forward_list(forward_list&);
//
//	~forward_list();
//
//	void push_back(int);
//};
//
//forward_list::forward_list() {
//	head = nullptr;
//	s = 0;
//}
//
//forward_list::forward_list(int size) {
//	s = size;
//	Node* h = new Node;
//	head = h;
//	Node* n_n = new Node;
//	h->next = n_n;
//	//h = h->next;
//	for (int i = 1; i < s; i++) {
//		n_n = new Node;
//		//h = h->next;
//		//h->next = n_n;
//		n_n->next = head;
//	}
//}
//
//forward_list::forward_list(forward_list& list) {}
//
//forward_list::~forward_list(){}
//
//int main() {
//	forward_list(4);
//	return 0;
//}