#include<fstream> // подключаем библиотеки
#include<math.h> // чтобы не писать свою функцию степени
#include<queue> // для перегрузки потока ввода
#include<string>

using std::ofstream; // чтобы удобно было
using std::ifstream;

typedef int size_m; // для красоты и удобства
typedef long double ld;

/*
	Краткая справка по методам из задания

	*	метод 1 - проверка корня:
		-> реализован через метод check_root(), возвращающий булево значение

	*	метод 2 - добавление коэфицента:
		-> во входном файле записан коэфицент, за ним степень, при которой стоит этот коэфицент,
		реализация через метод add_koef(), оперирует непосредственно с полями класса

	*	метод 3 - сложение многочленов:
		-> реализован через перегруженный оператор +, возвращающий объект типа polinomial	

	*	метод 4 - умножение на константу:
		-> реализован через перегруженный оператор *=, оперирующий непосредственно с полями класса

	*	метод 5 - перемножение многочленов:
		-> реализован через перегруженный оператор *, возвращающий объект типа polinomial
*/

class polinomial { // класс многочлена
	ld* koef; // массив коэфицентов
	size_m max_pow; // макс. степень, или иначе размер массива

public:
	polinomial(); // конструкторы и деструктор
	polinomial(ld*, size_m);
	polinomial(const polinomial&);
	~polinomial();

	polinomial operator=(const polinomial&); // оператор присваивания

	bool operator==(polinomial&); // операции сравнения
	bool operator!=(polinomial&);
	bool operator<(polinomial&);
	bool operator<=(polinomial&);
	bool operator>(polinomial&);
	bool operator>=(polinomial&);

	polinomial operator+(polinomial&); // перегруженные операторы для методов 3 - 5
	void operator*=(ld);
	polinomial operator*(polinomial&);

	bool check_root(ld); // метод 1
	void add_koef(ld, size_m); // метод 2

	void* operator new(size_t size); // перегрузка операторов new и delete
	void* operator new[](size_t size);
	void operator delete(void* ptr);
	void operator delete[](void* ptr);

	friend ofstream& operator<<(ofstream&, polinomial&); // перегрузка операторов ввода и вывода
	friend ifstream& operator>>(ifstream&, polinomial&);
};

polinomial::polinomial() { // конструктор по умолчанию
	koef = NULL;
	max_pow = 0;
}

polinomial::polinomial(ld* mass, size_m sz) { // конструктор инициализации
	max_pow = sz - 1; 
	koef = new ld[sz];
	for (size_m i = 0, j = sz - 1; i < sz; ++i, --j) 
		koef[i] = mass[j];
}

polinomial::polinomial(const polinomial& cpy) { // конструктор копирования
	max_pow = cpy.max_pow;
	koef = new ld[cpy.max_pow + 1]; // выделяем память
	for (size_m i = 0; i <= cpy.max_pow; ++i) // копируем массив
		koef[i] = cpy.koef[i];
}

polinomial::~polinomial() { // деструктор
	delete[] koef; // чистим память
	koef = nullptr;
	max_pow = 0;
}

polinomial polinomial::operator=(const polinomial& ref) { // перегрузка оператора присваивания
	if (ref.koef == (*this).koef)
		return *this;
	koef = new ld[ref.max_pow + 1]; // выделение памяти
	max_pow = ref.max_pow; // присваиваем макс. степень
	for (size_m i = 0; i <= ref.max_pow; ++i)
		koef[i] = ref.koef[i];
	return *this;
}

bool polinomial::operator==(polinomial& pol) { // перегрузка оператора ==
	if (max_pow - pol.max_pow) // если максимальные степени не совпадают
		return false;
	for (size_m i = 0; i <= max_pow; ++i) // если коэфиценты при степенях не совпадают
		if (koef[i] - pol.koef[i])
			return false;
	return true;
}

bool polinomial::operator!=(polinomial& pol) { // перегрузка оператора !=
	return !operator==(pol); // уменьшенная проверка на соответствие макс. степеней и коэфицентов при степенях
}

bool polinomial::operator<(polinomial& pol) { // перегрузка оператора <
	if (max_pow != pol.max_pow) // сравниваем максимальные степени
		return max_pow < pol.max_pow;
	else
		return koef[max_pow - 1] < pol.koef[max_pow - 1];
}

bool polinomial::operator<=(polinomial& pol) { // перегрузка оператора <= 
	return operator<(pol) || operator==(pol); // выражается через другие
}

bool polinomial::operator>(polinomial& pol) { // перегрузка оператора >
	return !operator<=(pol); // можно выразить через другие
}

bool polinomial::operator>=(polinomial& pol) { // перегрузка оператора >=
	return !operator<(pol); // выражается через другое
}

polinomial polinomial::operator+(polinomial& ref) { // сложение многочленов
	polinomial res;
	res.koef = new ld[(ref.max_pow > max_pow ? ref.max_pow: max_pow) + 1]; // выделение памяти
	res.max_pow = ref.max_pow > max_pow ? ref.max_pow : max_pow; // ищем макс. степень
	if (ref.max_pow == max_pow) { // если макс. степени равны
		for (size_m i = 0; i <= res.max_pow; ++i)
			res.koef[i] = ref.koef[i] + koef[i];
	}
	else { // если макс. степени не совпадают
		if (ref.max_pow > max_pow) {
			for (size_m i = 0; i <= max_pow; ++i)
				res.koef[i] = ref.koef[i] + koef[i];
			for (size_m i = max_pow + 1; i <= ref.max_pow; ++i)
				res.koef[i] = ref.koef[i];
		}
		else {
			for (size_m i = 0; i <= ref.max_pow; ++i)
				res.koef[i] = ref.koef[i] + koef[i];
			for (size_m i = ref.max_pow + 1; i <= max_pow; ++i)
				res.koef[i] = koef[i];
		}
	}
	return res;
}

void polinomial::operator*=(ld kf) { // умножение многочлена на константу
	for (size_m i = 0; i <= max_pow; ++i)
		koef[i] *= kf;
}

polinomial polinomial::operator*(polinomial& second) { // перемножение 2 многочленов
	polinomial res;
	res.max_pow = max_pow + second.max_pow; // макс. степень = сумме степеней
	res.koef = new ld[res.max_pow + 1];
	for (size_m i = 0; i <= res.max_pow; ++i)
		res.koef[i] = 0;
	for (size_m i = 0; i <= max_pow; ++i) { // ищем коэфиценты при степенях результирующего полинома
		for (size_m j = 0; j <= second.max_pow; ++j) {
			res.koef[i + j] += koef[i] * second.koef[j];
		}
	}
	res.koef[res.max_pow] = koef[max_pow] * second.koef[second.max_pow]; // чтобы считался наивысший коэфицент
	return res;
}

bool polinomial::check_root(ld root) { // проверка корня многочлена
	ld res{ 0.0 };
	for (size_m i = 0; i <= max_pow; ++i) { // подставляем число в многочлен и считаем сумму
		res += koef[i] * powl(root, i);
	}
	return !(float)res; // чтобы возвращалось с какой-то точностью до десятых
}

void polinomial::add_koef(ld k, size_m place) { // добавляем коэфицент в полином
	if (place < max_pow) { // если степень, при которой стоит коэфицент уже есть, то просто прибавляем коэфицент
		koef[place] += k;
	}
	else {
		ld* buf = new ld[place + 1]; // делаем буфер нового многочлена с максимальной степенью, = степени при новом коэф. 
		for (size_m i = 0; i <= max_pow; ++i) // заполняем буфер коэфицентами, которые уже есть
			buf[i] = koef[i];
		delete[] koef; // чистим начальный многочлен
		koef = new ld[place + 1]; // перевыделяем память

		if (place == max_pow + 1) // заполняем буфер с коэфицентами
			buf[place] = k;
		else {
			for (size_m i = max_pow; i <= place; ++i) // заполняем 0, коэфиценты при степенях,
				// которых не было в начальном многочлене и которые меньше новой макс. степени
				buf[i] = (i != place ? 0 : k);
		}

		for (size_m i = 0; i <= place; ++i) // заполняем массив коэфицентов заново
			koef[i] = buf[i];
		max_pow = place; // ставим максимальную степень
		delete[] buf; // чистим буфер
	}
}

void* polinomial::operator new(size_t size) { // перегрузка оператора выделения динамической памяти под один объект
	return ::operator new(size);
}

void* polinomial::operator new[](size_t size) { // перегрузка оператора выделения динамической памяти под массив объектов
	return ::operator new[](size);
}

void polinomial::operator delete(void* ptr) { // перегрузка оператора освобождения динамической памяти по опредённому адресу
	return ::operator delete(ptr);
}

void polinomial::operator delete[](void* ptr) { // перегрузка оператора освобождения памяти из-под динамической памяти
	return ::operator delete[](ptr);
}

ofstream& operator<<(ofstream& outp, polinomial& ref) { // вывод полинома
	if (ref.koef) {
		for (size_m i = ref.max_pow; i != -1; --i) {
			outp << ref.koef[i];
			if (i > 1)
				outp << "*x^" << i << " + ";
			else if (i == 1)
				outp << "*x" << " + "; 
		}
	}
	else // когда в массиве нет коэфицентов
		outp << "There is nothing!";
	return outp;
}

ifstream& operator>>(ifstream& inp, polinomial& ref) { // вывод в файл
	std::string str;
	std::queue<std::string> mass; // очередь из строк
	while (inp >> str && str != "|") // считываем до конца файла или до разделителя, если 2 многочлена
		mass.push(str); // записываем всё в очередь
	ref.max_pow = mass.size() - 1;
	ref.koef = new ld[mass.size()]; // выделяем память
	size_m sz1{ ref.max_pow }; // счётчик для записи в массив
	while (!mass.empty()){ // записываем в массив коэфицентов
		try {
			ref.koef[sz1--] = std::stold(mass.front()); // заполняем массив считанными числами
		}
		catch (std::invalid_argument& err){};
		mass.pop(); // удаляем элемент из очереди
	}
	return inp;
}

void operation(ifstream& inp, ofstream& outp, unsigned short int flag) { // выбор операции и сами операции
	if (flag == 1) { // конструктор по умолчанию
		polinomial pol;
		outp << pol;
	}
	else if (flag == 2) { // конструктор инициализации
		size_m sz, counter{ 0 };
		inp >> sz;
		ld* el = new ld[sz];
		while (inp >> el[counter++] && counter < sz);
		polinomial pol(el, sz);
		outp << pol;
		delete[] el;
	}
	else if (flag == 3) { // конструктор копирования
		polinomial pol;
		inp >> pol;
		polinomial ref(pol);
		outp << ref;
	}
	else if (flag == 4) { // =
		polinomial pol;
		polinomial ref;
		inp >> pol;
		ref = pol;
		outp << ref;
	}
	else if (flag == 5) { // ==
		polinomial pol;
		ld* mass = new ld[3];
		mass[0] = 1;
		mass[1] = 2;
		mass[2] = 1;
		polinomial ref(mass, 3);
		inp >> pol;
		outp << (pol == ref ? "true" : "false");
		delete[] mass;
	}
	else if (flag == 6) { // проверка корня
		ld root;
		polinomial pol;
		inp >> root;
		inp >> pol;
		outp << root << '\t' << (pol.check_root(root) ? "true" : "false");
	}
	else if (flag == 7) { // добавление коэфицента
		ld kf;
		size_m place;
		polinomial pol;
		inp >> kf;
		inp >> place;
		inp >> pol;
		pol.add_koef(kf, place);
		outp << pol;
	}
	else if (flag == 8) { // сложение многочленов
		polinomial pol;
		ld* mass = new ld[3];
		mass[0] = 1;
		mass[1] = 2;
		mass[2] = 1;
		polinomial ref(mass, 3);
		inp >> pol;
		polinomial res = pol + ref;
		outp << res;
		delete[] mass;
	}
	else if (flag == 9) { // умножение на константу
		polinomial pol;
		ld cnst;
		inp >> cnst;
		inp >> pol;
		pol *= cnst;
		outp << pol;
	}
	else if (flag == 10) { // умножение многочленов
		polinomial pol;
		ld* mass = new ld[3];
		mass[0] = 1;
		mass[1] = 2;
		mass[2] = 1;
		polinomial ref(mass, 3);
		inp >> pol;
		polinomial res = pol * ref;
		outp << res;
		delete[] mass;
	}
}

int main() {
	ifstream in("input.txt"); // открываем файлы для чтения и записи
	ofstream out("output.txt");
	unsigned short int flag; // тип данных, занимающих только 2 байта
	in >> flag; // считываем флаг метода
	polinomial pol1, pol2;
	operation(in, out, flag); // операция из задания по заданному флагу
	in.close(); // закрываем файлы
	out.close();
	return 0;
}