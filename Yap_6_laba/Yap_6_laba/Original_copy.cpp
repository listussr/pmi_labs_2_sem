//#define nul nullptr
//#include<fstream> // ���������� ����������
//#include<math.h> // ����� �� ������ ���� ������� �������
//#include<queue> // ��� ���������� ������ �����
//#include<string>
//#include<iostream>
//
//using std::ofstream; // ����� ������ ����
//using std::ifstream;
//using std::ostream;
//
//typedef int size_m; // ��� ������� � ��������
//typedef long double ld;
//
//class list;
//
///*
//	������� ������� �� ������� �� �������
//
//	*	����� 1 - �������� �����:
//		-> ���������� ����� ����� check_root(), ������������ ������ ��������
//
//	*	����� 2 - ���������� ����������:
//		-> �� ������� ����� ������� ���������, �� ��� �������, ��� ������� ����� ���� ���������,
//		���������� ����� ����� add_koef(), ��������� ��������������� � ������ ������
//
//	*	����� 3 - �������� �����������:
//		-> ���������� ����� ������������� �������� +, ������������ ������ ���� polinomial
//
//	*	����� 4 - ��������� �� ���������:
//		-> ���������� ����� ������������� �������� *=, ����������� ��������������� � ������ ������
//
//	*	����� 5 - ������������ �����������:
//		-> ���������� ����� ������������� �������� *, ������������ ������ ���� polinomial
//*/
//
//
//class polinomial { // ����� ����������
//	ld* koef; // ������ �����������
//	size_m max_pow; // ����. �������, ��� ����� ������ �������
//
//public:
//	polinomial(); // ������������ � ����������
//	polinomial(ld*, size_m);
//	polinomial(const polinomial&);
//	~polinomial();
//
//	polinomial operator=(const polinomial&); // �������� ������������
//
//	bool operator==(polinomial&); // �������� ���������
//	bool operator!=(polinomial&);
//	bool operator<(polinomial&);
//	bool operator<=(polinomial&);
//	bool operator>(polinomial&);
//	bool operator>=(polinomial&);
//
//	polinomial operator+(polinomial&); // ������������� ��������� ��� ������� 3 - 5
//	void operator*=(ld);
//	polinomial operator*(polinomial&);
//
//	bool check_root(ld); // ����� 1
//	void add_koef(ld, size_m); // ����� 2
//
//	size_m get_max_pow();
//
//	void* operator new(size_t size); // ���������� ���������� new � delete
//	void* operator new[](size_t size);
//	void operator delete(void* ptr);
//	void operator delete[](void* ptr);
//
//	friend ofstream& operator<<(ofstream&, polinomial&); // ���������� ���������� ����� � ������
//	friend ifstream& operator>>(ifstream&, polinomial&);
//
//	friend ostream& operator<<(ostream&, polinomial&);
//
//	friend list;
//};
//
//polinomial::polinomial() { // ����������� �� ���������
//	koef = nul;
//	max_pow = 0;
//}
//
//polinomial::polinomial(ld* mass, size_m sz) { // ����������� �������������
//	max_pow = sz - 1;
//	koef = new ld[sz];
//	for (size_m i = 0, j = sz - 1; i < sz; ++i, --j)
//		koef[i] = mass[j];
//}
//
//polinomial::polinomial(const polinomial& cpy) { // ����������� �����������
//	max_pow = cpy.max_pow;
//	koef = new ld[cpy.max_pow + 1]; // �������� ������
//	for (size_m i = 0; i <= cpy.max_pow; ++i) // �������� ������
//		koef[i] = cpy.koef[i];
//}
//
//polinomial::~polinomial() { // ����������
//	if (koef) {
//		delete[] koef; // ������ ������
//		koef = nullptr;
//		max_pow = 0;
//	}
//}
//
//polinomial polinomial::operator=(const polinomial& ref) { // ���������� ��������� ������������
//	if (&ref != this) {
//		polinomial pol(ref);
//		if (max_pow && koef) {
//			std::swap(max_pow, pol.max_pow);
//			std::swap(koef, pol.koef);
//		}
//		else {
//			max_pow = pol.max_pow; pol.max_pow = 0;
//			koef = pol.koef; pol.koef = nul;
//		}
//	}
//	return *this;
//}
//
//bool polinomial::operator==(polinomial& pol) { // ���������� ��������� ==
//	if (max_pow - pol.max_pow) // ���� ������������ ������� �� ���������
//		return false;
//	for (size_m i = 0; i <= max_pow; ++i) // ���� ���������� ��� �������� �� ���������
//		if (koef[i] - pol.koef[i])
//			return false;
//	return true;
//}
//
//bool polinomial::operator!=(polinomial& pol) { // ���������� ��������� !=
//	return !operator==(pol); // ����������� �������� �� ������������ ����. �������� � ����������� ��� ��������
//}
//
//bool polinomial::operator<(polinomial& pol) { // ���������� ��������� <
//	if (max_pow != pol.max_pow) // ���������� ������������ �������
//		return max_pow < pol.max_pow;
//	else {
//		size_m sz = max_pow;
//		for (; sz; --sz) {
//			if (koef[sz] != pol.koef[sz])
//				return koef[sz] < pol.koef[sz];
//		}
//		return true;
//	}
//}
//
//bool polinomial::operator<=(polinomial& pol) { // ���������� ��������� <= 
//	return operator<(pol) || operator==(pol); // ���������� ����� ������
//}
//
//bool polinomial::operator>(polinomial& pol) { // ���������� ��������� >
//	return !operator<=(pol); // ����� �������� ����� ������
//}
//
//bool polinomial::operator>=(polinomial& pol) { // ���������� ��������� >=
//	return !operator<(pol); // ���������� ����� ������
//}
//
//polinomial polinomial::operator+(polinomial& ref) { // �������� �����������
//	polinomial res;
//	res.koef = new ld[(ref.max_pow > max_pow ? ref.max_pow : max_pow) + 1]; // ��������� ������
//	res.max_pow = ref.max_pow > max_pow ? ref.max_pow : max_pow; // ���� ����. �������
//	if (ref.max_pow == max_pow) { // ���� ����. ������� �����
//		for (size_m i = 0; i <= res.max_pow; ++i)
//			res.koef[i] = ref.koef[i] + koef[i];
//	}
//	else { // ���� ����. ������� �� ���������
//		if (ref.max_pow > max_pow) {
//			for (size_m i = 0; i <= max_pow; ++i)
//				res.koef[i] = ref.koef[i] + koef[i];
//			for (size_m i = max_pow + 1; i <= ref.max_pow; ++i)
//				res.koef[i] = ref.koef[i];
//		}
//		else {
//			for (size_m i = 0; i <= ref.max_pow; ++i)
//				res.koef[i] = ref.koef[i] + koef[i];
//			for (size_m i = ref.max_pow + 1; i <= max_pow; ++i)
//				res.koef[i] = koef[i];
//		}
//	}
//	return res;
//}
//
//void polinomial::operator*=(ld kf) { // ��������� ���������� �� ���������
//	for (size_m i = 0; i <= max_pow; ++i)
//		koef[i] *= kf;
//}
//
//polinomial polinomial::operator*(polinomial& second) { // ������������ 2 �����������
//	polinomial res;
//	res.max_pow = max_pow + second.max_pow; // ����. ������� = ����� ��������
//	res.koef = new ld[res.max_pow + 1];
//	for (size_m i = 0; i <= res.max_pow; ++i)
//		res.koef[i] = 0;
//	for (size_m i = 0; i <= max_pow; ++i) { // ���� ���������� ��� �������� ��������������� ��������
//		for (size_m j = 0; j <= second.max_pow; ++j) {
//			res.koef[i + j] += koef[i] * second.koef[j];
//		}
//	}
//	res.koef[res.max_pow] = koef[max_pow] * second.koef[second.max_pow]; // ����� �������� ��������� ���������
//	return res;
//}
//
//bool polinomial::check_root(ld root) { // �������� ����� ����������
//	ld res{ 0.0 };
//	for (size_m i = 0; i <= max_pow; ++i) { // ����������� ����� � ��������� � ������� �����
//		res += koef[i] * powl(root, i);
//	}
//	return !(float)res; // ����� ������������ � �����-�� ��������� �� �������
//}
//
//void polinomial::add_koef(ld k, size_m place) { // ��������� ��������� � �������
//	if (place < max_pow) { // ���� �������, ��� ������� ����� ��������� ��� ����, �� ������ ���������� ���������
//		koef[place] += k;
//	}
//	else {
//		ld* buf = new ld[place + 1]; // ������ ����� ������ ���������� � ������������ ��������, = ������� ��� ����� ����. 
//		for (size_m i = 0; i <= max_pow; ++i) // ��������� ����� ������������, ������� ��� ����
//			buf[i] = koef[i];
//		delete[] koef; // ������ ��������� ���������
//		koef = new ld[place + 1]; // ������������ ������
//
//		if (place == max_pow + 1) // ��������� ����� � ������������
//			buf[place] = k;
//		else {
//			for (size_m i = max_pow; i <= place; ++i) // ��������� 0, ���������� ��� ��������,
//				// ������� �� ���� � ��������� ���������� � ������� ������ ����� ����. �������
//				buf[i] = (i != place ? 0 : k);
//		}
//
//		for (size_m i = 0; i <= place; ++i) // ��������� ������ ����������� ������
//			koef[i] = buf[i];
//		max_pow = place; // ������ ������������ �������
//		delete[] buf; // ������ �����
//	}
//}
//
//size_m polinomial::get_max_pow() {
//	return max_pow;
//}
//
//void* polinomial::operator new(size_t size) { // ���������� ��������� ��������� ������������ ������ ��� ���� ������
//	return ::operator new(size);
//}
//
//void* polinomial::operator new[](size_t size) { // ���������� ��������� ��������� ������������ ������ ��� ������ ��������
//	return ::operator new[](size);
//}
//
//void polinomial::operator delete(void* ptr) { // ���������� ��������� ������������ ������������ ������ �� ���������� ������
//	return ::operator delete(ptr);
//}
//
//void polinomial::operator delete[](void* ptr) { // ���������� ��������� ������������ ������ ��-��� ������������ ������
//	return ::operator delete[](ptr);
//}
//
//ofstream& operator<<(ofstream& outp, polinomial& ref) { // ����� ��������
//	if (ref.koef) {
//		for (size_m i = ref.max_pow; i != -1; --i) {
//			outp << ref.koef[i];
//			if (i > 1)
//				outp << "*x^" << i << " + ";
//			else if (i == 1)
//				outp << "*x" << " + ";
//		}
//	}
//	else // ����� � ������� ��� �����������
//		outp << "There is nothing!";
//	return outp;
//}
//
//ifstream& operator>>(ifstream& inp, polinomial& ref) { // ����� � ����
//	std::string str;
//	std::queue<std::string> mass; // ������� �� �����
//	while (inp >> str && str != "|") // ��������� �� ����� ����� ��� �� �����������, ���� 2 ����������
//		mass.push(str); // ���������� �� � �������
//	ref.max_pow = mass.size() - 1;
//	ref.koef = new ld[mass.size()]; // �������� ������
//	size_m sz1{ ref.max_pow }; // ������� ��� ������ � ������
//	while (!mass.empty()) { // ���������� � ������ �����������
//		try {
//			ref.koef[sz1--] = std::stold(mass.front()); // ��������� ������ ���������� �������
//		}
//		catch (std::invalid_argument& err) {};
//		mass.pop(); // ������� ������� �� �������
//	}
//	return inp;
//}
//
//ostream& operator<<(ostream& outp, polinomial& ref) {
//	if (ref.koef) {
//		for (size_m i = ref.max_pow; i != -1; --i) {
//			outp << ref.koef[i];
//			if (i > 1)
//				outp << "*x^" << i << " + ";
//			else if (i == 1)
//				outp << "*x" << " + ";
//		}
//	}
//	else // ����� � ������� ��� �����������
//		outp << "There is nothing!";
//	return outp;
//}
//
//struct Node { // ��������� ����
//	polinomial val;
//	Node* next;
//
//	Node() {}
//
//	Node(polinomial value) {
//		val = value;
//		next = nul;
//	}
//};
//
//class list { // ����� ������
//	Node* first;
//	Node* last;
//	int s; // ������ ������
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
//	bool is_empty() const;
//
//	int size() const;
//
//	polinomial front() const;
//
//	polinomial back() const;
//
//	Node* begin() const;
//
//	Node* end() const;
//
//	void push_back(polinomial);
//
//	void push_front(polinomial);
//
//	void pop_front();
//
//	void clear();
//
//	void swap(int, int, bool);
//
//	void swap(Node*, Node*);
//
//	void pop_in_border(int, int, bool&);
//
//	void insert(int, int, list&, bool);
//
//	void insert(Node*, Node*);
//
//	void erase(Node*);
//
//	void pop_front_n(int);
//
//	polinomial operator[](int);
//
//	list operator=(list&);
//
//	friend ofstream& operator <<(ofstream&, list&);
//	friend ostream& operator <<(ostream&, list&);
//};
//
//// ����������� �� ���������
//list::list() {
//	first = last = nul;
//	s = 0;
//}
//
//// ����������� �����������
//list::list(Node* f, Node* l) {
//	first = f;
//	last = l;
//	s = { 0 };
//	while (f->next != l->next) {
//		++s;
//		f = f->next;
//	}
//}
//
//// ����������� �����������
//list::list(const list& ref) {
//	first = nul;
//	last = first;
//	s = 0;
//	if (!ref.is_empty()) {
//		Node* node = ref.begin();
//		while (ref.s - s) {
//			push_back(node->val);
//			node = node->next;
//		}
//	}
//
//}
//
//list::~list() { // ����������
//	while (s)
//		pop_front();
//}
//
//void list::pop_front() {
//	if (first) {
//		if (first != last) {
//			Node* n = first, * second = n->next;
//			last->next = second;
//			delete n;
//			first = second;
//		}
//		else {
//			delete first;
//			first = last = nul;
//		}
//		--s;
//	}
//}
//// ������ ������
//
//// �������� �� �������
//bool list::is_empty() const {
//	return !first;
//}
//
//// ���������� ������ ������
//int list::size() const {
//	return s;
//}
//
//// ���������� �������� ������
//polinomial list::front() const {
//	return first->val;
//}
//
//// ���������� �������� ������
//polinomial list::back() const {
//	return last->val;
//}
//
//// ���������� ��������� �� ������
//Node* list::begin() const {
//	return first;
//}
//
//// ���������� ��������� �� �����
//Node* list::end() const {
//	return last;
//}
//
//// ���������� � �����
//void list::push_back(polinomial n) {
//	Node* new_node = new Node(n);
//	if (is_empty()) {
//		first = new_node;
//		first->next = new_node;
//		last = new_node;
//		last->next = new_node;
//	}
//	else {
//		last->next = new_node;
//		last = new_node;
//		new_node->next = first;
//	}
//	++s;
//}
//
//// ������� � ������
//void list::push_front(polinomial n) {
//	Node* new_node = new Node(n);
//	if (is_empty()) {
//		first = new_node;
//		first->next = new_node;
//		last = new_node;
//		last->next = new_node;
//	}
//	else {
//		new_node->next = first;
//		last->next = new_node;
//		first = new_node;
//	}
//	++s;
//}
//
//// ������ ������
//void list::clear() {
//	pop_front_n(size());
//}
//
//// �������� swap-�
//void list::swap(int ind1, int ind2, bool) { // swap �������� ���������
//	if (size() == 2) { // ���� ������ 2 �������� � ������
//		Node* buffer = first;
//		first = last;
//		last = buffer;
//	}
//	else if (size() > 2) {
//		if (!ind1 || !ind2) { // swap 0-��� � 1-��� ���������
//			Node* ptr_a = first, * ptr_b = first->next;
//			last->next = ptr_b;
//			ptr_a->next = ptr_b->next;
//			ptr_b->next = first->next;
//			first = ptr_b;
//			first->next = ptr_a;
//		}
//		else if (!(ind1 - size() + 1) || !(ind2 - size() + 1)) { // swap ���������� � �������������� ���������
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
//			// ptr_mid <---> ptr_c
//			ptr_a->next = ptr_c;
//			ptr_mid->next = ptr_c->next;
//			ptr_c->next = ptr_mid;
//		}
//	}
//}
//void list::swap(Node* ptr_1, Node* ptr_2) {
//	// ������ ������� ������ ������ � n-�� �������, ������� �� �������� ��������
//	if (ptr_1 == first && ptr_2 != last) {
//		Node* ref_ptr{ first };
//		while (ref_ptr->next != ptr_2) {
//			ref_ptr = ref_ptr->next;
//		}
//		last->next = ptr_2;
//		ptr_1->next = ptr_2->next;
//		ref_ptr->next = ptr_1;
//		first = ptr_2;
//	}
//	// ������ ������� ������ � ����� ������
//	else if (ptr_1 == first && ptr_2 == last) {
//		Node* ref_ptr{ first };
//		while (ref_ptr->next != last)
//			ref_ptr = ref_ptr->next;
//		ref_ptr->next = ptr_1;
//		ptr_2->next = ptr_1->next;
//		ptr_1->next = ptr_2->next;
//		first = ptr_2;
//		last = ptr_1;
//	}
//	// ������ ������� n-�� ������� ������, �� ���������� ���������, � ����� ������
//	else if (ptr_1 != first && ptr_2 == last) {
//		Node* ref_ptr_1{ first }, * ref_ptr_2{ first };
//		while (ref_ptr_1->next != ptr_1)
//			ref_ptr_1 = ref_ptr_1->next;
//		while (ref_ptr_2->next != ptr_2)
//			ref_ptr_2 = ref_ptr_2->next;
//
//		ref_ptr_1->next = ptr_2;
//		ref_ptr_2->next = ptr_1;
//		ptr_2->next = ptr_1->next;
//		ptr_1->next = first;
//		last = ptr_1;
//	}
//	// ������ ������� k-�� � n-�� ��������, ������� �� �������� �� �������, �� ������� ������
//	else {
//		Node* ref_ptr_1{ first }, * ref_ptr_2{ first }, * ref_ptr_3{ first };
//		while (ref_ptr_1->next != ptr_1)
//			ref_ptr_1 = ref_ptr_1->next;
//		while (ref_ptr_2->next != ptr_2)
//			ref_ptr_2 = ref_ptr_2->next;
//		ref_ptr_3 = ptr_1->next;
//
//		ptr_1->next = ptr_2->next;
//		ref_ptr_1->next = ptr_2;
//		ref_ptr_2->next = ptr_1;
//		ptr_2->next = ref_ptr_3;
//	}
//}
//
//// �������� �� ��������
//void list::pop_in_border(int ind1, int ind2, bool& flag_out_of) {
//
//	if (ind1 && ind2 != size() - 1) { // �������� � ����� ������
//		Node* ptr_a = first, * ptr_b = first;
//		for (int i = 0; i < ind1 - 1; ++i)
//			ptr_a = ptr_a->next;
//		for (int i = 0; i <= ind2; ++i)
//			ptr_b = ptr_b->next;
//		ptr_a->next = ptr_b;
//		flag_out_of = 1; // ��� inserta
//		s -= (ind2 - ind1 + 1);
//	}
//
//	else if (ind1 && !(ind2 - size() + 1)) { // ���� ������ ������ != 0 � ������ ������ �� �������� (�������� �� ��������)
//		Node* ptr_a = first;
//		for (int i = 0; i < ind1 - 1; ++i)
//			ptr_a = ptr_a->next;
//		last = ptr_a;
//		last->next = first;
//		flag_out_of = 0; // ��� inserta
//		s -= (ind2 - ind1 + 1);
//	}
//
//	else if (!ind1 && ind2 != size() - 1) { // ���� ������ ������ �������
//		Node* ptr_b = first;
//		for (int i = 0; i < ind2; ++i)
//			ptr_b = ptr_b->next;
//		first = ptr_b->next;
//		last->next = first;
//		s -= (ind2 - ind1 + 1);
//	}
//
//	else {
//		first = last = nul;
//		s = 0;
//	}
//}
//
//// ��� ����������� ���������� �������
//void list::insert(int ind1, int ind2, list& ref, bool flag_out_of) {
//	if (is_empty()) { // ���� ������ ����
//		first = ref.first;
//		last = ref.last;
//		s += ref.size();
//	}
//	else if (!ind1) { // ������� � ������
//		ref.last->next = first;
//		last->next = ref.first;
//		first = ref.first;
//		s += ref.size();
//	}
//	else {
//		if (flag_out_of) { // ������� � �������� ������
//			Node* ptr_a = first;
//			for (int i = 0; i < ind1 - 1; ++i)
//				ptr_a = ptr_a->next;
//			ref.last->next = ptr_a->next;
//			ptr_a->next = ref.first;
//		}
//		else { // ������� � ����� ������
//			last->next = ref.first;
//			ref.last = first;
//			last = ref.last;
//		}
//		s += ref.size();
//	}
//}
//
//// ������� ���� �� ����������� ����� � ������
//void list::insert(Node* place, Node* ptr) {
//	// ������� �� � ������
//	if (place != first) {
//		Node* ref{ first };
//		while (ref->next != place)
//			ref = ref->next;
//		ref->next = ptr;
//		ptr->next = place;
//		++s;
//	}
//	// ������� � ������
//	else if (place == first)
//		push_front(ptr->val);
//}
//
//// ������� ����, ����� ����� �������� � ������ �����
//void list::erase(Node* ptr_1) {
//	Node* ptr{ first };
//	while (ptr->next != ptr_1) ptr = ptr->next;
//	ptr->next = ptr_1->next;
//	if (ptr_1 == last) {
//		last = ptr;
//	}
//	--s;
//}
//
//void list::pop_front_n(int am) { // �������� ������ n ����� ������
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
//}
//
//polinomial list::operator[](int ind) { // ���������� ��������� ����������
//	if (ind < size()) {
//		Node* pointer = first;
//		for (int i = 0; i < ind; ++i)
//			pointer = pointer->next;
//		return pointer->val;
//	}
//	else {
//		polinomial n;
//		return n;
//	}
//}
//
//// �������� ������������
//list list::operator=(list& ref) {
//	list cpy(ref);
//	if (&cpy != this) {
//		if (first && s) {
//			std::swap(first, cpy.first);
//			std::swap(last, cpy.last);
//			std::swap(s, cpy.s);
//		}
//		else {
//			first = cpy.first; cpy.first = nul;
//			last = cpy.last; cpy.last = nul;
//			s = cpy.s; cpy.s = 0;
//		}
//	}
//	return *this;
//}
//
//// ��������� ������ � ������� � � ����
//std::ofstream& operator<<(ofstream& out, list& ref) { // ���������� ��������� ������
//	out << ref.first;
//	return out;
//}
//ostream& operator<<(ostream& out, list& ref) {
//	out << ref.first;
//	return out;
//}
//
//////////////////////////////////////
//// ������ �������
//////////////////////////////////////
//
//// ���������� ���������
//void Insertion_Sort(list& vec, int amount) {
//
//	Node* ptr;
//	while (amount--) {
//		ptr = vec.begin();
//		int sz = vec.size() - amount;
//		while (sz--)
//			ptr = ptr->next;
//		Node* ref{ vec.begin() };
//		bool flag{ true };
//		while (ref != ptr && flag) {
//			if (ptr->val <= ref->val) {
//				vec.erase(ptr);
//				vec.insert(ref, ptr);
//				flag = false;
//			}
//			ref = ref->next;
//		}
//	}
//}
//
//// ������ ��������� ��������
//polinomial create_random_polinomial() {
//	int amount = rand() % 15 + 1;
//	ld* mass = new ld[amount];
//	std::cout << amount << '\t';
//	for (int i = 0; i < amount; ++i) {
//		mass[i] = ((ld)(rand() % 1000)) / ((ld)(rand() % 18) + 1);
//		std::cout << mass[i] << ' ';
//	}
//	std::cout << '\n';
//	polinomial pol(mass, amount);
//	delete[] mass;
//	return pol;
//}
//
//// ������ ������ �� ��������� ���������
//list create_list(int amount) {
//	list l;
//	while (amount--) {
//		l.push_back(create_random_polinomial());
//	}
//	return l;
//}
//
//// ������� �������� ����������������� ������
//bool is_sorted(list vec) {
//	Node* prev{ vec.begin() }, * cur{ vec.begin()->next };
//	int sz = vec.size();
//	while (--sz && prev->val <= cur->val) {
//		cur = cur->next;
//		prev = prev->next;
//	}
//	return sz;
//}
//
//int main()
//{
//	srand(time(NULL)); // ������ ������������
//	int amount;
//	ifstream in("input.txt");
//	in >> amount;
//	in.close();
//	list vec = create_list(amount);
//	Insertion_Sort(vec, amount);
//	int sz = vec.size();
//	std::cout << '\n';
//	Node* beg{ vec.begin() };
//	while (sz--) {
//		std::cout << beg->val.get_max_pow() << '\t' << beg->val << '\n' << '\n';
//		beg = beg->next;
//	}
//	std::cout << (!is_sorted(vec) ? "true\n" : "false\n");
//	ofstream out("output.txt");
//	out << vec.size() << ' ';
//	out.close();
//	return 0;
//}