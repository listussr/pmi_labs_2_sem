#include<fstream> // ���������� ����������
#include<math.h> // ����� �� ������ ���� ������� �������
#include<queue> // ��� ���������� ������ �����
#include<string>

using std::ofstream; // ����� ������ ����
using std::ifstream;

typedef int size_m; // ��� ������� � ��������
typedef long double ld;

/*
	������� ������� �� ������� �� �������

	*	����� 1 - �������� �����:
		-> ���������� ����� ����� check_root(), ������������ ������ ��������

	*	����� 2 - ���������� ����������:
		-> �� ������� ����� ������� ���������, �� ��� �������, ��� ������� ����� ���� ���������,
		���������� ����� ����� add_koef(), ��������� ��������������� � ������ ������

	*	����� 3 - �������� �����������:
		-> ���������� ����� ������������� �������� +, ������������ ������ ���� polinomial	

	*	����� 4 - ��������� �� ���������:
		-> ���������� ����� ������������� �������� *=, ����������� ��������������� � ������ ������

	*	����� 5 - ������������ �����������:
		-> ���������� ����� ������������� �������� *, ������������ ������ ���� polinomial
*/

class polinomial { // ����� ����������
	ld* koef; // ������ �����������
	size_m max_pow; // ����. �������, ��� ����� ������ �������

public:
	polinomial(); // ������������ � ����������
	polinomial(ld*, size_m);
	polinomial(const polinomial&);
	~polinomial();

	polinomial operator=(const polinomial&); // �������� ������������

	bool operator==(polinomial&); // �������� ���������
	bool operator!=(polinomial&);
	bool operator<(polinomial&);
	bool operator<=(polinomial&);
	bool operator>(polinomial&);
	bool operator>=(polinomial&);

	polinomial operator+(polinomial&); // ������������� ��������� ��� ������� 3 - 5
	void operator*=(ld);
	polinomial operator*(polinomial&);

	bool check_root(ld); // ����� 1
	void add_koef(ld, size_m); // ����� 2

	void* operator new(size_t size); // ���������� ���������� new � delete
	void* operator new[](size_t size);
	void operator delete(void* ptr);
	void operator delete[](void* ptr);

	friend ofstream& operator<<(ofstream&, polinomial&); // ���������� ���������� ����� � ������
	friend ifstream& operator>>(ifstream&, polinomial&);
};

polinomial::polinomial() { // ����������� �� ���������
	koef = NULL;
	max_pow = 0;
}

polinomial::polinomial(ld* mass, size_m sz) { // ����������� �������������
	max_pow = sz - 1; 
	koef = new ld[sz];
	for (size_m i = 0, j = sz - 1; i < sz; ++i, --j) 
		koef[i] = mass[j];
}

polinomial::polinomial(const polinomial& cpy) { // ����������� �����������
	max_pow = cpy.max_pow;
	koef = new ld[cpy.max_pow + 1]; // �������� ������
	for (size_m i = 0; i <= cpy.max_pow; ++i) // �������� ������
		koef[i] = cpy.koef[i];
}

polinomial::~polinomial() { // ����������
	delete[] koef; // ������ ������
	koef = nullptr;
	max_pow = 0;
}

polinomial polinomial::operator=(const polinomial& ref) { // ���������� ��������� ������������
	if (ref.koef == (*this).koef)
		return *this;
	koef = new ld[ref.max_pow + 1]; // ��������� ������
	max_pow = ref.max_pow; // ����������� ����. �������
	for (size_m i = 0; i <= ref.max_pow; ++i)
		koef[i] = ref.koef[i];
	return *this;
}

bool polinomial::operator==(polinomial& pol) { // ���������� ��������� ==
	if (max_pow - pol.max_pow) // ���� ������������ ������� �� ���������
		return false;
	for (size_m i = 0; i <= max_pow; ++i) // ���� ���������� ��� �������� �� ���������
		if (koef[i] - pol.koef[i])
			return false;
	return true;
}

bool polinomial::operator!=(polinomial& pol) { // ���������� ��������� !=
	return !operator==(pol); // ����������� �������� �� ������������ ����. �������� � ����������� ��� ��������
}

bool polinomial::operator<(polinomial& pol) { // ���������� ��������� <
	if (max_pow != pol.max_pow) // ���������� ������������ �������
		return max_pow < pol.max_pow;
	else
		return koef[max_pow - 1] < pol.koef[max_pow - 1];
}

bool polinomial::operator<=(polinomial& pol) { // ���������� ��������� <= 
	return operator<(pol) || operator==(pol); // ���������� ����� ������
}

bool polinomial::operator>(polinomial& pol) { // ���������� ��������� >
	return !operator<=(pol); // ����� �������� ����� ������
}

bool polinomial::operator>=(polinomial& pol) { // ���������� ��������� >=
	return !operator<(pol); // ���������� ����� ������
}

polinomial polinomial::operator+(polinomial& ref) { // �������� �����������
	polinomial res;
	res.koef = new ld[(ref.max_pow > max_pow ? ref.max_pow: max_pow) + 1]; // ��������� ������
	res.max_pow = ref.max_pow > max_pow ? ref.max_pow : max_pow; // ���� ����. �������
	if (ref.max_pow == max_pow) { // ���� ����. ������� �����
		for (size_m i = 0; i <= res.max_pow; ++i)
			res.koef[i] = ref.koef[i] + koef[i];
	}
	else { // ���� ����. ������� �� ���������
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

void polinomial::operator*=(ld kf) { // ��������� ���������� �� ���������
	for (size_m i = 0; i <= max_pow; ++i)
		koef[i] *= kf;
}

polinomial polinomial::operator*(polinomial& second) { // ������������ 2 �����������
	polinomial res;
	res.max_pow = max_pow + second.max_pow; // ����. ������� = ����� ��������
	res.koef = new ld[res.max_pow + 1];
	for (size_m i = 0; i <= res.max_pow; ++i)
		res.koef[i] = 0;
	for (size_m i = 0; i <= max_pow; ++i) { // ���� ���������� ��� �������� ��������������� ��������
		for (size_m j = 0; j <= second.max_pow; ++j) {
			res.koef[i + j] += koef[i] * second.koef[j];
		}
	}
	res.koef[res.max_pow] = koef[max_pow] * second.koef[second.max_pow]; // ����� �������� ��������� ���������
	return res;
}

bool polinomial::check_root(ld root) { // �������� ����� ����������
	ld res{ 0.0 };
	for (size_m i = 0; i <= max_pow; ++i) { // ����������� ����� � ��������� � ������� �����
		res += koef[i] * powl(root, i);
	}
	return !(float)res; // ����� ������������ � �����-�� ��������� �� �������
}

void polinomial::add_koef(ld k, size_m place) { // ��������� ��������� � �������
	if (place < max_pow) { // ���� �������, ��� ������� ����� ��������� ��� ����, �� ������ ���������� ���������
		koef[place] += k;
	}
	else {
		ld* buf = new ld[place + 1]; // ������ ����� ������ ���������� � ������������ ��������, = ������� ��� ����� ����. 
		for (size_m i = 0; i <= max_pow; ++i) // ��������� ����� ������������, ������� ��� ����
			buf[i] = koef[i];
		delete[] koef; // ������ ��������� ���������
		koef = new ld[place + 1]; // ������������ ������

		if (place == max_pow + 1) // ��������� ����� � ������������
			buf[place] = k;
		else {
			for (size_m i = max_pow; i <= place; ++i) // ��������� 0, ���������� ��� ��������,
				// ������� �� ���� � ��������� ���������� � ������� ������ ����� ����. �������
				buf[i] = (i != place ? 0 : k);
		}

		for (size_m i = 0; i <= place; ++i) // ��������� ������ ����������� ������
			koef[i] = buf[i];
		max_pow = place; // ������ ������������ �������
		delete[] buf; // ������ �����
	}
}

void* polinomial::operator new(size_t size) { // ���������� ��������� ��������� ������������ ������ ��� ���� ������
	return ::operator new(size);
}

void* polinomial::operator new[](size_t size) { // ���������� ��������� ��������� ������������ ������ ��� ������ ��������
	return ::operator new[](size);
}

void polinomial::operator delete(void* ptr) { // ���������� ��������� ������������ ������������ ������ �� ���������� ������
	return ::operator delete(ptr);
}

void polinomial::operator delete[](void* ptr) { // ���������� ��������� ������������ ������ ��-��� ������������ ������
	return ::operator delete[](ptr);
}

ofstream& operator<<(ofstream& outp, polinomial& ref) { // ����� ��������
	if (ref.koef) {
		for (size_m i = ref.max_pow; i != -1; --i) {
			outp << ref.koef[i];
			if (i > 1)
				outp << "*x^" << i << " + ";
			else if (i == 1)
				outp << "*x" << " + "; 
		}
	}
	else // ����� � ������� ��� �����������
		outp << "There is nothing!";
	return outp;
}

ifstream& operator>>(ifstream& inp, polinomial& ref) { // ����� � ����
	std::string str;
	std::queue<std::string> mass; // ������� �� �����
	while (inp >> str && str != "|") // ��������� �� ����� ����� ��� �� �����������, ���� 2 ����������
		mass.push(str); // ���������� �� � �������
	ref.max_pow = mass.size() - 1;
	ref.koef = new ld[mass.size()]; // �������� ������
	size_m sz1{ ref.max_pow }; // ������� ��� ������ � ������
	while (!mass.empty()){ // ���������� � ������ �����������
		try {
			ref.koef[sz1--] = std::stold(mass.front()); // ��������� ������ ���������� �������
		}
		catch (std::invalid_argument& err){};
		mass.pop(); // ������� ������� �� �������
	}
	return inp;
}

void operation(ifstream& inp, ofstream& outp, unsigned short int flag) { // ����� �������� � ���� ��������
	if (flag == 1) { // ����������� �� ���������
		polinomial pol;
		outp << pol;
	}
	else if (flag == 2) { // ����������� �������������
		size_m sz, counter{ 0 };
		inp >> sz;
		ld* el = new ld[sz];
		while (inp >> el[counter++] && counter < sz);
		polinomial pol(el, sz);
		outp << pol;
		delete[] el;
	}
	else if (flag == 3) { // ����������� �����������
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
	else if (flag == 6) { // �������� �����
		ld root;
		polinomial pol;
		inp >> root;
		inp >> pol;
		outp << root << '\t' << (pol.check_root(root) ? "true" : "false");
	}
	else if (flag == 7) { // ���������� ����������
		ld kf;
		size_m place;
		polinomial pol;
		inp >> kf;
		inp >> place;
		inp >> pol;
		pol.add_koef(kf, place);
		outp << pol;
	}
	else if (flag == 8) { // �������� �����������
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
	else if (flag == 9) { // ��������� �� ���������
		polinomial pol;
		ld cnst;
		inp >> cnst;
		inp >> pol;
		pol *= cnst;
		outp << pol;
	}
	else if (flag == 10) { // ��������� �����������
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
	ifstream in("input.txt"); // ��������� ����� ��� ������ � ������
	ofstream out("output.txt");
	unsigned short int flag; // ��� ������, ���������� ������ 2 �����
	in >> flag; // ��������� ���� ������
	polinomial pol1, pol2;
	operation(in, out, flag); // �������� �� ������� �� ��������� �����
	in.close(); // ��������� �����
	out.close();
	return 0;
}