//#include<fstream>
//#define nul nullptr
//
//using std::ifstream;
//using std::ofstream;
//
//struct Node { // структура узла
//	int val;
//	Node* next;
//
//	Node() {}
//
//	Node(int value) {
//		val = value;
//		next = nul;
//	}
//};
//
//class list { // класс списка
//	Node* first;
//	Node* last;
//	int s;
//
//public:
//
//	list();
//
//	list(Node*, Node*);
//
//	list(const list&);
//
//	~list();
//
//	bool is_empty();
//
//	int size();
//
//	int front();
//
//	int back();
//
//	Node* begin();
//
//	Node* end();
//
//	void push_back(int);
//
//	void clear();
//
//	void swap(int, int, bool);
//
//	void pop_front_n(int);
//
//	int operator[](int);
//
//	friend std::ofstream& operator <<(std::ofstream&, list&);
//};
//
//list::list() { // конструктор по умолчанию
//	first = last = nul;
//	s = 0;
//}
//
//list::list(Node* f, Node* l) {
//	first = f;
//	last = l;
//}
//
//list::list(const list& ref) { // конструктор копирования
//	first = ref.first;
//	last = ref.last;
//}
//
//list::~list() { // деструктор
//	clear();
//}
//
// методы класса
//
//bool list::is_empty() {
//	return first == nul;
//}
//
//int list::size() {
//	return s;
//}
//
//int list::front() {
//	return first->val;
//}
//
//int list::back() {
//	return last->val;
//}
//
//Node* list::begin() {
//	return first;
//}
//
//Node* list::end() {
//	return last;
//}
//
//void list::push_back(int n) {
//	Node* new_node = new Node(n);
//	if (is_empty()) {
//		first = new_node;
//		last = new_node;
//	}
//	else {
//		last->next = new_node;
//		last = new_node;
//		new_node->next = first;
//	}
//	++s;
//	return;
//}
//
//void list::clear() {
//	pop_front_n(size());
//}
//
//void list::swap(int ind1, int ind2, bool) { // swap соседних элементов
//	if (size() == 2) { // если только 2 элемента в списке
//		Node* buffer = first;
//		first = last;
//		last = buffer;
//	}
//	else if (size() > 2) {
//		if (!ind1 || !ind2) { // swap 0-ого и 1-ого элементов
//			Node* ptr_a = first, * ptr_b = first->next;
//			last->next = ptr_b;
//			ptr_a->next = ptr_b->next;
//			ptr_b->next = first->next;
//			first = ptr_b;
//			first->next = ptr_a;
//		}
//		else if (!(ind1 - size() + 1) || !(ind2 - size() + 1)) { // swap последнего и предпоследнего элементов
//			Node* ptr_a = first;
//			for (int i = 0; i < (ind1 < ind2 ? ind1 : ind2) - 1; ++i)
//				ptr_a = ptr_a->next;
//			Node* ptr_mid = ptr_a->next, * ptr_c = ptr_mid->next;
//			ptr_a->next = ptr_c;
//			ptr_c->next = ptr_mid;
//			ptr_mid->next = first;
//			last = ptr_mid;
//		}
//		else {
//			Node* ptr_a = first;
//			for (int i = 0; i < (ind1 < ind2 ? ind1 : ind2) - 1; ++i)
//				ptr_a = ptr_a->next;
//			Node* ptr_mid = ptr_a->next, * ptr_c = ptr_mid->next;
//			 ptr_mid <---> ptr_c
//			ptr_a->next = ptr_c;
//			ptr_mid->next = ptr_c->next;
//			ptr_c->next = ptr_mid;
//		}
//	}
//}
//
//void list::pop_front_n(int am) { // удаление первых n узлов списка
//	if (am < size()) {
//		Node* pointer = first, * del = first, * buf;
//		for (int i = 0; i < am; ++i, pointer = pointer->next);
//		for (int i = 0; i < am - 1; ++i) {
//			buf = del->next;
//			del = nul;
//			delete del;
//			del = buf;
//		}
//		first = pointer;
//		last->next = first;
//		s -= am;
//	}
//	else {
//		first = last = nul;
//	}
//}
//
//int list::operator[](int ind) { // перегрузка оператора индексации
//	if (ind < size()) {
//		Node* pointer = first;
//		for (int i = 0; i < ind; ++i)
//			pointer = pointer->next;
//		return pointer->val;
//	}
//	else
//		return 0;
//}
//
//std::ofstream& operator<<(ofstream& out, list& ref) { // перегрузка оператора вывода
//	out << ref.first;
//	return out;
//}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//void swap_elements(list& ref, int left, int right) { // функция swap() (для того чтобы менять соседние Node)
//	ref.swap(left, right, 1);
//}
//
//void get_data(ifstream& in, list& l, int& amount) { // чтение списка
//	int el;
//	while (in >> el) {
//		++amount;
//		l.push_back(el);
//	}
//}
//
//void out_data(ofstream& out, list& l) { // функция вывода списка
//	for (Node* ptr = l.begin(); ptr->next != l.begin(); ptr = ptr->next)
//		out << ptr->val << ' ';
//	out << l.back();
//}
//
//void Insertion_Sort(list& vec) {
//	int i = 1;
//	for (; i < vec.size(); ++i) { // сортировка вставками
//		int j = i;
//		bool flag = true;
//		while (j >= 1 && flag) {
//			if (vec[j] >= vec[j - 1]) // если всё отсортированно - выходим
//				flag = false;
//			if (flag) { // меняем местами, если не отсортированно
//				swap_elements(vec, j, j - 1);
//				--j;
//			}
//		}
//	}
//}
//
//void sort(list& l, char ch) {
//	Insertion_Sort(l);
//}
//
//int main()
//{
//	list l;
//	ifstream in("input.txt");
//	int amount = 0;
//	char ch;
//	in >> ch;
//	get_data(in, l, amount);
//	in.close();
//	sort(l, ch);
//	ofstream out("output.txt");
//	out << amount << ' ';
//	out_data(out, l);
//	out.close();
//	return 0;
//}