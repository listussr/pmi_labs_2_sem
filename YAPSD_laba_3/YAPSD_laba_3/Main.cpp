#include<fstream>
#define nul nullptr

using std::ifstream;
using std::ofstream;

struct Node { // ��������� ����
	int val;
	Node* next;

	Node(){}

	Node(int value) {
		val = value;
		next = nul;
	}
};

class list { // ����� ������
	Node* first;
	Node* last;
	int s;

public:

	list();

	list(Node*, Node*);

	list(const list&);

	~list();

	bool is_empty();

	int size();

	int front();

	int back();

	Node* begin();
	
	Node* end();

	void push_back(int);

	void push_front(int);

	void clear();

	void swap(int, int, bool);

	void pop_in_border(int, int, bool&);

	void insert(int, int, list&, bool);

	void pop_front_n(int);

	int operator[](int);

	friend std::ofstream& operator <<(std::ofstream&, list&);
};

list::list(){ // ����������� �� ���������
	first = last = nul;
	s = 0;
}

list::list(Node* f, Node* l) { 
	first = f;
	last = l;
}

list::list(const list& ref) { // ����������� �����������
	first = ref.first;
	last = ref.last;
}

list::~list() { // ����������
	clear();
}

// ������ ������

bool list::is_empty() {
	return first == nul;
}

int list::size() {
	return s;
}

int list::front() {
	return first->val;
}

int list::back() {
	return last->val;
}

Node* list::begin() {
	return first;
}

Node* list::end() {
	return last;
}

void list::push_back(int n) { // ��������� � �����
	Node* new_node = new Node(n);
	if (is_empty()) {
		first = new_node;
		last = new_node;
	}
	else {
		last->next = new_node;
		last = new_node;
		new_node->next = first;
	}
	++s;
	return;
}

void list::push_front(int n) { // ���������� � ������
	Node* new_node = new Node(n);
	if (is_empty()) {
		first = new_node;
		last = new_node;
	}
	else {
		new_node->next = first;
		last->next = new_node;
	}
	++s;
	return;
}

void list::clear() {
	pop_front_n(size());
}

void list::swap(int ind1, int ind2, bool) { // swap �������� ���������
	if (size() == 2) { // ���� ������ 2 �������� � ������
		Node* buffer = first;
		first = last;
		last = buffer;
	}
	else if(size() > 2) {
		if (!ind1 || !ind2) { // swap 0-��� � 1-��� ���������
			Node* ptr_a = first, *ptr_b = first->next;
			last->next = ptr_b;
			ptr_a->next = ptr_b->next;
			ptr_b->next = first->next;
			first = ptr_b;
			first->next = ptr_a;
		}
		else if (!(ind1 - size() + 1) || !(ind2 - size() + 1)) { // swap ���������� � �������������� ���������
			Node* ptr_a = first;
			for (int i = 0; i < (ind1 < ind2 ? ind1 : ind2) - 1; ++i)
				ptr_a = ptr_a->next;
			Node* ptr_mid = ptr_a->next, * ptr_c = ptr_mid->next;
			ptr_a->next = ptr_c;
			ptr_c->next = ptr_mid;
			ptr_mid->next = first;
			last = ptr_mid;
		}
		else {
			Node* ptr_a = first;
			for (int i = 0; i < (ind1 < ind2 ? ind1 : ind2) - 1; ++i)
				ptr_a = ptr_a->next;
			Node* ptr_mid = ptr_a->next, * ptr_c = ptr_mid->next;
			// ptr_mid <---> ptr_c
			ptr_a->next = ptr_c;
			ptr_mid->next = ptr_c->next;
			ptr_c->next = ptr_mid;
		}
	}
}

void list::pop_in_border(int ind1, int ind2, bool& flag_out_of) {

	if (ind1 && ind2 != size() - 1) { // �������� � ����� ������
		Node* ptr_a = first, * ptr_b = first;
		for (int i = 0; i < ind1 - 1; ++i)
			ptr_a = ptr_a->next;
		for (int i = 0; i <= ind2; ++i)
			ptr_b = ptr_b->next;
		ptr_a->next = ptr_b;
		flag_out_of = 1; // ��� inserta
		s -= (ind2 - ind1 + 1);
	}

	else if (ind1 && !(ind2 - size() + 1)) { // ���� ������ ������ != 0 � ������ ������ �� �������� (�������� �� ��������)
		Node* ptr_a = first;
		for (int i = 0; i < ind1 - 1; ++i)
			ptr_a = ptr_a->next;
		last = ptr_a;
		last->next = first;
		flag_out_of = 0; // ��� inserta
		s -= (ind2 - ind1 + 1);
	}

	else if(!ind1 && ind2 != size() - 1) { // ���� ������ ������ �������
		Node* ptr_b = first;
		for (int i = 0; i < ind2; ++i)
			ptr_b = ptr_b->next;
		first = ptr_b->next;
		last->next = first;
		s -= (ind2 - ind1 + 1);
	}

	else {
		first = last = nul;
		s = 0;
	}
}

void list::insert(int ind1, int ind2, list& ref, bool flag_out_of) {
	if (is_empty()) { // ���� ������ ����
		first = ref.first;
		last = ref.last;
		s += ref.size();
	}
	else if (!ind1) { // ������� � ������
		ref.last->next = first;
		last->next = ref.first;
		first = ref.first;
		s += ref.size();
	}
	else {
		if (flag_out_of) { // ������� � �������� ������
			Node* ptr_a = first;
			for (int i = 0; i < ind1 - 1; ++i)
				ptr_a = ptr_a->next;
			ref.last->next = ptr_a->next;
			ptr_a->next = ref.first;
		}
		else { // ������� � ����� ������
			last->next = ref.first;
			ref.last = first;
			last = ref.last;
		}
		s += ref.size();
	}
}

void list::pop_front_n(int am) { // �������� ������ n ����� ������
	if (am < size()) {
		Node* pointer = first, * del = first, * buf;
		for (int i = 0; i < am; ++i, pointer = pointer->next);
		for (int i = 0; i < am - 1; ++i) {
			buf = del->next;
			del = nul;
			delete del;
			del = buf;
		}
		first = pointer;
		last->next = first;
		s -= am;
	}
	else {
		first = last = nul;
	}
}

int list::operator[](int ind) { // ���������� ��������� ����������
	if (ind < size()) {
		Node* pointer = first;
		for (int i = 0; i < ind; ++i)
			pointer = pointer->next;
		return pointer->val;
	}
	else
		return 0;
}

std::ofstream& operator<<(ofstream& out, list& ref) { // ���������� ��������� ������
	out << ref.first;
	return out;
}

////////////////////////////////////
// ������ �������
////////////////////////////////////

void swap_elements(list& ref, int left, int right) { // ������� swap() (��� ���� ����� ������ �������� Node)
	ref.swap(left, right, 1);
}

void get_data(ifstream& in, list& l, int& amount) { // ������ ������
	int el;
	while (in >> el) {
		l.push_back(el);
		++amount;
	}
}

void out_data(ofstream& out, list& l) { // ������� ������ ������
	for(Node* ptr = l.begin(); ptr->next != l.begin(); ptr = ptr->next)
		out << ptr->val << ' ';
	out << l.back();
}

void Insertion_Sort(list& vec) { // ����������� �� O(n^3)
	int i = 1;
	for (; i < vec.size(); ++i) { // ���������� ���������
		int j = i;
		bool flag = true;
		while (j >= 1 && flag) {
			if (vec[j] >= vec[j - 1]) // ���� �� �������������� - �������
				flag = false;
			if (flag) { // ������ �������, ���� �� ��������������
				swap_elements(vec, j, j - 1);
				--j;
			}
		}
	}
}

void Merge(list& vec, int left, int middle, int right) {
	if (left == right - 1) { // ���� ����� 2 ����, �� ����� ��������������� swap-��
		if (vec[left] > vec[right]) 
			swap_elements(vec, right, left);
		return;
	}

	Node* iter = vec.begin(); // ������������� ���������
	list a, b, res;
	for (int i = 0; i < left; ++i)
		iter = iter->next;
	for (int i = left; i <= middle; ++i) {
		a.push_back(iter->val);
		iter = iter->next;
	}
	for (int i = middle + 1; i <= right; ++i) {
		b.push_back(iter->val);
		iter = iter->next;
	}

	int i = 0, j = 0, a_n = a.size(), b_n = b.size();
	while (i < a_n && j < b_n) { // ������� ���� ��������������� �������
		if (a[i] <= b[j]) {
			res.push_back(a[i++]);
		}
		else {
			res.push_back(b[j++]);
		}
	}
	
	while (i < a_n) 
		res.push_back(a[i++]);
	while (j < b_n)
		res.push_back(b[j++]);

	// ��������������� ����� � ������
	//		|
	//		\/

	bool inserting_flag = 1;
	vec.pop_in_border(left, right, inserting_flag);
	vec.insert(left, right, res, inserting_flag);
}

void Merge_Sort(list& vec, int left, int right) { // ��������� ������ �� ����� ��� ������������ �������
	/*
		��� ���������, ��� �� merge sort, � �����-�� ������������� heap sort/\
	*/
	if (right <= left)
		return;
	int middle = left + (right - left) / 2;
	Merge_Sort(vec, left, middle); // ��������� �� ���� � �� ����������
	Merge_Sort(vec, middle + 1, right);
	Merge(vec, left, middle, right); // ������� �������
}

void sort(list& vec, bool sorting_flag) {
	sorting_flag? Merge_Sort(vec, 0, vec.size() - 1) : Insertion_Sort(vec);
}

int main()
{

	/*
	 ���������� ��������� ����� ����������� O(n^3) (��� ���������� ��-�� �������������� ��������� ����������, ������� ��� �� �������� �� O(n),
	 ������������ �� O(n^2) ����� ����������), ������� ��� �� �������� �� ������� �� 5000 ���������

	 � ������ ����� ������� �������� ����� ����� ��� ������� ��������, ��� ����������� ����� log(n), �� � ������ ������
	 ����� ����������� �� ����� ����� ������ �� �� O(n^3).

	 � ��� �������������� ��������� ���������� ������ �� ������ ����� (���������� ���������) ���-�� ����� ����������� �� O(n)
	*/

	list l;
	bool flag;
	int amount{ 0 };
	ifstream in("input.txt");
	in >> flag;
	get_data(in, l, amount);
	in.close();
	sort(l, flag);
	ofstream out("output.txt");
	out << amount << ' ';
	out_data(out, l);
	out.close();
	return 0;
}