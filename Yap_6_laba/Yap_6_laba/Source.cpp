//#define nul nullptr
//#include<fstream> // подключаем библиотеки
//#include<math.h> // чтобы не писать свою функцию степени
//#include<queue> // для перегрузки потока ввода
//#include<string>
//#include<iostream>
//
//using std::ofstream; // чтобы удобно было
//using std::ifstream;
//using std::ostream;
//
//typedef int size_m; // для красоты и удобства
//typedef long double ld;
//
//class list;
//
///*
//	Краткая справка по методам из задания
//
//	*	метод 1 - проверка корня:
//		-> реализован через метод check_root(), возвращающий булево значение
//
//	*	метод 2 - добавление коэфицента:
//		-> во входном файле записан коэфицент, за ним степень, при которой стоит этот коэфицент,
//		реализация через метод add_koef(), оперирует непосредственно с полями класса
//
//	*	метод 3 - сложение многочленов:
//		-> реализован через перегруженный оператор +, возвращающий объект типа polinomial
//
//	*	метод 4 - умножение на константу:
//		-> реализован через перегруженный оператор *=, оперирующий непосредственно с полями класса
//
//	*	метод 5 - перемножение многочленов:
//		-> реализован через перегруженный оператор *, возвращающий объект типа polinomial
//*/
//
//class polinomial { // класс многочлена
//	ld* koef; // массив коэфицентов
//	size_m max_pow; // макс. степень, или иначе размер массива
//
//public:
//	polinomial(); // конструкторы и деструктор
//	polinomial(ld*, size_m);
//	polinomial(const polinomial&);
//	~polinomial();
//
//	polinomial operator=(const polinomial&); // оператор присваивания
//
//	bool operator==(polinomial&); // операции сравнения
//	bool operator!=(polinomial&);
//	bool operator<(polinomial&);
//	bool operator<=(polinomial&);
//	bool operator>(polinomial&);
//	bool operator>=(polinomial&);
//
//	polinomial operator+(polinomial&); // перегруженные операторы для методов 3 - 5
//	void operator*=(ld);
//	polinomial operator*(polinomial&);
//
//	bool check_root(ld); // метод 1
//	void add_koef(ld, size_m); // метод 2
//
//	size_m get_max_pow();
//
//	void* operator new(size_t size); // перегрузка операторов new и delete
//	void* operator new[](size_t size);
//	void operator delete(void* ptr);
//	void operator delete[](void* ptr);
//
//	friend ofstream& operator<<(ofstream&, polinomial&); // перегрузка операторов ввода и вывода
//	friend ifstream& operator>>(ifstream&, polinomial&);
//
//	friend ostream& operator<<(ostream&, polinomial&);
//
//	friend list;
//};
//
//polinomial::polinomial() { // конструктор по умолчанию
//	koef = NULL;
//	max_pow = 0;
//}
//
//polinomial::polinomial(ld* mass, size_m sz) { // конструктор инициализации
//	max_pow = sz - 1;
//	koef = new ld[sz];
//	for (size_m i = 0, j = sz - 1; i < sz; ++i, --j)
//		koef[i] = mass[j];
//}
//
//polinomial::polinomial(const polinomial& cpy) { // конструктор копирования
//	max_pow = cpy.max_pow;
//	koef = new ld[cpy.max_pow + 1]; // выделяем память
//	for (size_m i = 0; i <= cpy.max_pow; ++i) // копируем массив
//		koef[i] = cpy.koef[i];
//}
//
//polinomial::~polinomial() { // деструктор
//	delete[] koef; // чистим память
//	koef = nullptr;
//	max_pow = 0;
//}
//
//polinomial polinomial::operator=(const polinomial& ref) { // перегрузка оператора присваивания
//	if (ref.koef == (*this).koef)
//		return *this;
//	koef = new ld[ref.max_pow + 1]; // выделение памяти
//	max_pow = ref.max_pow; // присваиваем макс. степень
//	for (size_m i = 0; i <= ref.max_pow; ++i)
//		koef[i] = ref.koef[i];
//	return *this;
//}
//
//bool polinomial::operator==(polinomial& pol) { // перегрузка оператора ==
//	if (max_pow - pol.max_pow) // если максимальные степени не совпадают
//		return false;
//	for (size_m i = 0; i <= max_pow; ++i) // если коэфиценты при степенях не совпадают
//		if (koef[i] - pol.koef[i])
//			return false;
//	return true;
//}
//
//bool polinomial::operator!=(polinomial& pol) { // перегрузка оператора !=
//	return !operator==(pol); // уменьшенная проверка на соответствие макс. степеней и коэфицентов при степенях
//}
//
//bool polinomial::operator<(polinomial& pol) { // перегрузка оператора <
//	if (max_pow != pol.max_pow) // сравниваем максимальные степени
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
//bool polinomial::operator<=(polinomial& pol) { // перегрузка оператора <= 
//	return operator<(pol) || operator==(pol); // выражается через другие
//}
//
//bool polinomial::operator>(polinomial& pol) { // перегрузка оператора >
//	return !operator<=(pol); // можно выразить через другие
//}
//
//bool polinomial::operator>=(polinomial& pol) { // перегрузка оператора >=
//	return !operator<(pol); // выражается через другое
//}
//
//polinomial polinomial::operator+(polinomial& ref) { // сложение многочленов
//	polinomial res;
//	res.koef = new ld[(ref.max_pow > max_pow ? ref.max_pow : max_pow) + 1]; // выделение памяти
//	res.max_pow = ref.max_pow > max_pow ? ref.max_pow : max_pow; // ищем макс. степень
//	if (ref.max_pow == max_pow) { // если макс. степени равны
//		for (size_m i = 0; i <= res.max_pow; ++i)
//			res.koef[i] = ref.koef[i] + koef[i];
//	}
//	else { // если макс. степени не совпадают
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
//void polinomial::operator*=(ld kf) { // умножение многочлена на константу
//	for (size_m i = 0; i <= max_pow; ++i)
//		koef[i] *= kf;
//}
//
//polinomial polinomial::operator*(polinomial& second) { // перемножение 2 многочленов
//	polinomial res;
//	res.max_pow = max_pow + second.max_pow; // макс. степень = сумме степеней
//	res.koef = new ld[res.max_pow + 1];
//	for (size_m i = 0; i <= res.max_pow; ++i)
//		res.koef[i] = 0;
//	for (size_m i = 0; i <= max_pow; ++i) { // ищем коэфиценты при степенях результирующего полинома
//		for (size_m j = 0; j <= second.max_pow; ++j) {
//			res.koef[i + j] += koef[i] * second.koef[j];
//		}
//	}
//	res.koef[res.max_pow] = koef[max_pow] * second.koef[second.max_pow]; // чтобы считался наивысший коэфицент
//	return res;
//}
//
//bool polinomial::check_root(ld root) { // проверка корня многочлена
//	ld res{ 0.0 };
//	for (size_m i = 0; i <= max_pow; ++i) { // подставляем число в многочлен и считаем сумму
//		res += koef[i] * powl(root, i);
//	}
//	return !(float)res; // чтобы возвращалось с какой-то точностью до десятых
//}
//
//void polinomial::add_koef(ld k, size_m place) { // добавляем коэфицент в полином
//	if (place < max_pow) { // если степень, при которой стоит коэфицент уже есть, то просто прибавляем коэфицент
//		koef[place] += k;
//	}
//	else {
//		ld* buf = new ld[place + 1]; // делаем буфер нового многочлена с максимальной степенью, = степени при новом коэф. 
//		for (size_m i = 0; i <= max_pow; ++i) // заполняем буфер коэфицентами, которые уже есть
//			buf[i] = koef[i];
//		delete[] koef; // чистим начальный многочлен
//		koef = new ld[place + 1]; // перевыделяем память
//
//		if (place == max_pow + 1) // заполняем буфер с коэфицентами
//			buf[place] = k;
//		else {
//			for (size_m i = max_pow; i <= place; ++i) // заполняем 0, коэфиценты при степенях,
//				// которых не было в начальном многочлене и которые меньше новой макс. степени
//				buf[i] = (i != place ? 0 : k);
//		}
//
//		for (size_m i = 0; i <= place; ++i) // заполняем массив коэфицентов заново
//			koef[i] = buf[i];
//		max_pow = place; // ставим максимальную степень
//		delete[] buf; // чистим буфер
//	}
//}
//
//size_m polinomial::get_max_pow() {
//	return max_pow;
//}
//
//void* polinomial::operator new(size_t size) { // перегрузка оператора выделения динамической памяти под один объект
//	return ::operator new(size);
//}
//
//void* polinomial::operator new[](size_t size) { // перегрузка оператора выделения динамической памяти под массив объектов
//	return ::operator new[](size);
//}
//
//void polinomial::operator delete(void* ptr) { // перегрузка оператора освобождения динамической памяти по опредённому адресу
//	return ::operator delete(ptr);
//}
//
//void polinomial::operator delete[](void* ptr) { // перегрузка оператора освобождения памяти из-под динамической памяти
//	return ::operator delete[](ptr);
//}
//
//ofstream& operator<<(ofstream& outp, polinomial& ref) { // вывод полинома
//	if (ref.koef) {
//		for (size_m i = ref.max_pow; i != -1; --i) {
//			outp << ref.koef[i];
//			if (i > 1)
//				outp << "*x^" << i << " + ";
//			else if (i == 1)
//				outp << "*x" << " + ";
//		}
//	}
//	else // когда в массиве нет коэфицентов
//		outp << "There is nothing!";
//	return outp;
//}
//
//ifstream& operator>>(ifstream& inp, polinomial& ref) { // вывод в файл
//	std::string str;
//	std::queue<std::string> mass; // очередь из строк
//	while (inp >> str && str != "|") // считываем до конца файла или до разделителя, если 2 многочлена
//		mass.push(str); // записываем всё в очередь
//	ref.max_pow = mass.size() - 1;
//	ref.koef = new ld[mass.size()]; // выделяем память
//	size_m sz1{ ref.max_pow }; // счётчик для записи в массив
//	while (!mass.empty()) { // записываем в массив коэфицентов
//		try {
//			ref.koef[sz1--] = std::stold(mass.front()); // заполняем массив считанными числами
//		}
//		catch (std::invalid_argument& err) {};
//		mass.pop(); // удаляем элемент из очереди
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
//	else // когда в массиве нет коэфицентов
//		outp << "There is nothing!";
//	return outp;
//}
//
//struct Node { // структура узла
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
//class list { // класс списка
//	Node* first;
//	Node* last;
//	int s; // размер списка
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
//	polinomial front();
//
//	polinomial back();
//
//	Node* begin();
//
//	Node* end();
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
//// конструктор по умолчанию
//list::list() { 
//	first = last = nul;
//	s = 0;
//}
//
//// бесполезный конструктор
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
//// конструктор копирования
//list::list(const list& ref) { 
//	first = ref.first;
//	last = ref.last;
//	s = ref.s;
//}
//
//list::~list() { // деструктор
//	clear();
////	if (s) {
////		if (s - 1) {
////			Node* del{ begin() }, * next_ptr{ begin() };
////			while (s-- - 1) {
////				next_ptr = del->next;
////				delete del;
////				del = next_ptr;
////			}
////		}
////		else {
////			delete first;
////			first = last = nullptr;
////		} 
////	}
////}
//	//while (s)
//	//	pop_front();
//}
//
//void list::pop_front() {
//	if (first) {
//		if (first != last) {
//			Node* n = first, *second = n->next;
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
//// методы класса
//
//// проверка на пустоту
//bool list::is_empty() {
//	return !first;
//}
//
//// возвращаем размер списка
//int list::size() {
//	return s;
//}
//
//// возвращаем значение головы
//polinomial list::front() {
//	return first->val;
//}
//
//// возвращаем значение хвоста
//polinomial list::back() {
//	return last->val;
//}
//
//// возвращаем указатель на голову
//Node* list::begin() {
//	return first;
//}
//
//// возвращаем указатель на хвост
//Node* list::end() {
//	return last;
//}
//
//// добавление в конец
//void list::push_back(polinomial n) { 
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
//// вставка в начало
//void list::push_front(polinomial n) { 
//	Node* new_node = new Node(n);
//	if (is_empty()) {
//		first = new_node;
//		last = new_node;
//	}
//	else {
//		new_node->next = first;
//		last->next = new_node;
//		first = new_node;
//	}
//	++s;
//}
//
//// чистим список
//void list::clear() {
//	pop_front_n(size());
//}
//
//// ненужные swap-ы
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
//			// ptr_mid <---> ptr_c
//			ptr_a->next = ptr_c;
//			ptr_mid->next = ptr_c->next;
//			ptr_c->next = ptr_mid;
//		}
//	}
//}
//void list::swap(Node* ptr_1, Node* ptr_2) {
//	// меняем местами голову списка и n-ый элемент, который не является конечным
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
//	// меняем местами голову и хвост списка
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
//	// меняем местами n-ый элемент списка, не являющийся начальным, и хвост списка
//	else if (ptr_1 != first && ptr_2 == last) {
//		Node* ref_ptr_1{ first }, *ref_ptr_2{ first };
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
//	// меняем местами k-ый и n-ый элементы, которые не являются ни головой, ни хвостом списка
//	else {
//		Node* ref_ptr_1{ first }, *ref_ptr_2{ first }, *ref_ptr_3{ first };
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
//void list::pop_in_border(int ind1, int ind2, bool& flag_out_of) {
//
//	if (ind1 && ind2 != size() - 1) { // удаление с конца списка
//		Node* ptr_a = first, * ptr_b = first;
//		for (int i = 0; i < ind1 - 1; ++i)
//			ptr_a = ptr_a->next;
//		for (int i = 0; i <= ind2; ++i)
//			ptr_b = ptr_b->next;
//		ptr_a->next = ptr_b;
//		flag_out_of = 1; // для inserta
//		s -= (ind2 - ind1 + 1);
//	}
//
//	else if (ind1 && !(ind2 - size() + 1)) { // если первый индекс != 0 и второй индекс не конечный (удаление из середины)
//		Node* ptr_a = first;
//		for (int i = 0; i < ind1 - 1; ++i)
//			ptr_a = ptr_a->next;
//		last = ptr_a;
//		last->next = first;
//		flag_out_of = 0; // для inserta
//		s -= (ind2 - ind1 + 1);
//	}
//
//	else if (!ind1 && ind2 != size() - 1) { // если первый индекс нулевой
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
//// уже бесполезная перегрузка функции
//void list::insert(int ind1, int ind2, list& ref, bool flag_out_of) {
//	if (is_empty()) { // если список пуст
//		first = ref.first;
//		last = ref.last;
//		s += ref.size();
//	}
//	else if (!ind1) { // вставка в начало
//		ref.last->next = first;
//		last->next = ref.first;
//		first = ref.first;
//		s += ref.size();
//	}
//	else {
//		if (flag_out_of) { // вставка в середину списка
//			Node* ptr_a = first;
//			for (int i = 0; i < ind1 - 1; ++i)
//				ptr_a = ptr_a->next;
//			ref.last->next = ptr_a->next;
//			ptr_a->next = ref.first;
//		}
//		else { // вставка в конец списка
//			last->next = ref.first;
//			ref.last = first;
//			last = ref.last;
//		}
//		s += ref.size();
//	}
//}
//
//// вставка узла на определённое место в списке
//void list::insert(Node* place, Node* ptr) {
//	// вставка не в начало
//	if (place != first) {
//		Node* ref{ first };
//		while (ref->next != place)
//			ref = ref->next;
//		ref->next = ptr;
//		ptr->next = place;
//		++s;
//	}
//	// вставка в начало
//	else if (place == first)
//		push_front(ptr->val);
//}
//
//// удаляем узел, чтобы потом вставить в нужное место
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
//		//while (s-- - 1) {
//		//	Node* ptr = first, *del = first->next;
//		//	delete ptr;
//		//	last->next = del;
//		//	ptr = del;
//		//	del = ptr->next;
//		//	first = ptr;
//		//}
//		//delete last;
//		first = last = nul;
//		s = 0;
//	}
//}
//
//polinomial list::operator[](int ind) { // перегрузка оператора индексации
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
//// оператор присваивания
//list list::operator=(list& ref) {
//	list cpy(ref);
//	cpy.s = ref.s;
//	return cpy;
//}
//
//// операторы вывода в консоль и в файл
//std::ofstream& operator<<(ofstream& out, list& ref) { // перегрузка оператора вывода
//	out << ref.first;
//	return out;
//}
//ostream& operator<<(ostream& out, list& ref) {
//	out << ref.first;
//	return out;
//}
//
//////////////////////////////////////
//// просто функции
//////////////////////////////////////
//
//// сортировка вставками
//void Insertion_Sort(list& vec, int amount) {
//
//	Node *ptr;
//	while (amount--) {
//		ptr = vec.begin();
//		int sz = vec.size() - amount;
//		while (sz--)
//			ptr = ptr->next;
//		Node* ref{ vec.begin() };
//		bool flag{ true };
//		while (ref != ptr && flag){
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
////void Merge(list& vec, int left, int middle, int right) {
////	if (left == right - 1) { // если всего 2 ноды, то можно воспользоваться swap-ом
////		if (vec[left] > vec[right])
////			swap_elements(vec, right, left);
////		return;
////	}
////
////	Node* iter = vec.begin(); // промежуточные состояния
////	list a, b, res;
////	for (int i = 0; i < left; ++i)
////		iter = iter->next;
////	for (int i = left; i <= middle; ++i) {
////		a.push_back(iter->val);
////		iter = iter->next;
////	}
////	for (int i = middle + 1; i <= right; ++i) {
////		b.push_back(iter->val);
////		iter = iter->next;
////	}
////
////	int i = 0, j = 0, a_n = a.size(), b_n = b.size();
////	while (i < a_n && j < b_n) { // слияние двух отсортированных списков
////		if (a[i] <= b[j]) {
////			res.push_back(a[i++]);
////		}
////		else {
////			res.push_back(b[j++]);
////		}
////	}
////
////	while (i < a_n)
////		res.push_back(a[i++]);
////	while (j < b_n)
////		res.push_back(b[j++]);
////
////	// перегруппировка узлов в списке
////	//		|
////	//		\/
////
////	bool inserting_flag = 1;
////	vec.pop_in_border(left, right, inserting_flag);
////	vec.insert(left, right, res, inserting_flag);
////}
////
////void Merge_Sort(list& vec, int left, int right) { // разбиение списка на части для последующего слияния
////	/*
////		как оказалось, это не merge sort, а какая-то разновидность heap sort/\
////	*/
////	if (right <= left)
////		return;
////	int middle = left + (right - left) / 2;
////	Merge_Sort(vec, left, middle); // разбиение на ноды и их сортировка
////	Merge_Sort(vec, middle + 1, right);
////	Merge(vec, left, middle, right); // слияние списков
////}
////
////void sort(list& vec, bool sorting_flag) {
////	sorting_flag ? Merge_Sort(vec, 0, vec.size() - 1) : Insertion_Sort(vec);
////}
//
//// создаём рандомные полиномы
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
//	return pol;
//}
//
//// создаём список из рандомных полиномов
//list create_list(int amount) {
//	list l;
//	while (amount--) {
//		l.push_back(create_random_polinomial());
//	}
//	return l;
//}
//
//// функция проверки отсортированности списка
//bool is_sorted(list vec) {
//	Node* prev{ vec.begin() }, *cur{ vec.begin()->next };
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
//	srand(time(NULL)); // псевдо рандомизация
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