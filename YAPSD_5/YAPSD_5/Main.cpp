//#include<fstream>
//#include<iostream>
//#include<math.h>
//#include<deque>
//using std::ofstream;
//using std::ifstream;
//
//typedef int size_m;
//typedef long double ld;
//typedef std::deque<ld> mass;
//
////template<class T> class polinomial{
////	T* koef;
////	size_m max_pow;
////
////public:
////	polinomial();
////	polinomial(T*, size_m);
////	polinomial(polinomial&);
////	~polinomial();
////
////	friend ofstream& operator<<(ofstream&, polinomial);
////	//friend ifstream& operator<<(ifstream&, polinomial);
////};
////
////template<class T> polinomial<T>::polinomial() {
////	koef = new T;
////	koef[0] = 0;
////	max_pow = 0;
////}
////
////template<class T> polinomial<T>::polinomial(T* mass, size_m m_pow) {
////	koef = new T[m_pow + 1];
////	max_pow = mass[m_pow];
////	for (size_m i = 0; i <= m_pow; ++i)
////		koef[i] = mass[i];
////}
////
////template<class T> polinomial<T>::polinomial(polinomial<T>& cpy) {
////	koef = new T[cpy.max_pow + 1];
////	max_pow = cpy.max_pow;
////	for (size_m i = 0; i <= cpy.max_pow; ++i)
////		koef[i] = cpy.koef[i];
////}
////
////template<class T> polinomial<T>::~polinomial() {
////	delete[] koef;
////	koef = nullptr;
////	max_pow = 0;
////}
////
////template<class T> ofstream& operator<<(ofstream& outp, polinomial<T> ref) {
////	for (size_m i = ref.max_pow; i != 0; ++i)
////		outp << ref[i] << '*' << i << (i > 1 ? " + " : "");
////	return outp;
////}
//
//class polinomial {
//	mass koef;
//	size_m max_pow;
//
//public:
//	polinomial();
//	polinomial(ld*, size_m);
//	polinomial(const polinomial&);
//	//~polinomial();
//
//	polinomial operator=(const polinomial&);
//
//	bool operator==(polinomial&);
//	bool operator!=(polinomial&);
//
//	bool operator<(polinomial&);
//	bool operator<=(polinomial&);
//	bool operator>(polinomial&);
//	bool operator>=(polinomial&);
//
//	polinomial operator+(polinomial&);
//
//	bool check_root(ld);
//	void add_coef(ld, size_m);
//
//	friend ofstream& operator<<(ofstream&, polinomial&);
//	friend ifstream& operator>>(ifstream&, polinomial&);
//};
//
//polinomial::polinomial() {
//	koef.push_back(0);
//	max_pow = 0;
//}
//
//polinomial::polinomial(ld* mass, size_m sz) {
//	for (size_m i = 0; i < sz; ++i) {
//		koef.push_back(mass[i]);
//		++max_pow;
//	}
//}
//
//polinomial::polinomial(const polinomial& cpy) {
//	max_pow = cpy.max_pow;
//	for (size_m i = 0; i < cpy.max_pow; ++i)
//		koef.push_back(cpy.koef[i]);
//}
////
////polinomial::~polinomial() {
////	koef.clear();
////	max_pow = 0;
////}
//
//polinomial polinomial::operator=(const polinomial& ref) {
//	polinomial pol;
//	pol.max_pow = ref.max_pow;
//	pol.koef.clear();
//	for (size_m i = 0; i < ref.koef.size(); ++i)
//		pol.koef.push_back(ref.koef[i]);
//	return pol;
//}
//
//bool polinomial::operator==(polinomial& pol) {
//	if (max_pow - pol.max_pow)
//		return false;
//	for (size_m i = 0; i < max_pow; ++i)
//		if (koef[i] - pol.koef[i])
//			return false;
//	return true;
//}
//
//bool polinomial::operator!=(polinomial& pol) {
//	return !operator==(pol);
//}
//
//bool polinomial::operator<(polinomial& pol) {
//	if (max_pow < pol.max_pow)
//		return true;
//	else if (max_pow == pol.max_pow)
//		return koef[max_pow - 1] < pol.koef[max_pow - 1];
//	else
//		return false;
//}
//
//bool polinomial::operator<=(polinomial& pol) {
//	return operator<(pol) || operator==(pol);
//}
//
//bool polinomial::operator>(polinomial& pol) {
//	return !operator<=(pol);
//}
//
//bool polinomial::operator>=(polinomial& pol) {
//	return !operator<(pol);
//}
//
//polinomial polinomial::operator+(polinomial& ref) {
//	polinomial res;
//	if (ref.max_pow == max_pow) {
//		for (size_m i = 0; i < ref.koef.size(); ++i)
//			res.koef.push_back(ref.koef[i] + koef[i]);
//	}
//	else {
//		if (ref.max_pow > max_pow) {
//			for (size_m i = 0; i < koef.size(); ++i)
//				res.koef.push_back(ref.koef[i] + koef[i]);
//			for (size_m i = koef.size(); i < ref.koef.size(); ++i)
//				res.koef.push_back(ref.koef[i]);
//		}
//		else {
//			for (size_m i = 0; i < ref.koef.size(); ++i)
//				res.koef.push_back(ref.koef[i] + koef[i]);
//			for (size_m i = ref.koef.size(); i < koef.size(); ++i)
//				res.koef.push_back(koef[i]);
//		}
//	}
//	res.max_pow = ref.max_pow > max_pow ? ref.max_pow : max_pow;
//	return res;
//}
//
//bool polinomial::check_root(ld root) {
//	ld res{ 0.0 };
//	for (size_m i = 0; i < max_pow; ++i) {
//		res += koef[i] * powl(root, i);
//	}
//	std::cout << res;
//	return !res;
//}
//
//void polinomial::add_coef(ld k, size_m place) {
//	if (place <= max_pow) {
//		koef[place] += k;
//	}	
//	else {
//		if (place == max_pow + 1) {
//			koef.push_back(k);
//			++max_pow;
//		}
//		else {
//			for (size_m i = max_pow; i <= place; ++i) {
//				koef.push_back(i != place ? 0 : k);
//				++max_pow;
//			}
//		}
//	}
//}
//
//ofstream& operator<<(ofstream& outp, polinomial& ref) {
//	for (size_m i = ref.max_pow - 1; i != -1; --i)
//		outp << ref.koef[i] << "*x^" << i << (i > 0 ? " + " : "");
//	return outp;
//}
//
//ifstream& operator>>(ifstream& inp, polinomial& ref) {
//	ld element;
//	while (inp >> element) {
//		++ref.max_pow;
//		ref.koef.push_back(element);
//	}
//	return inp;
//}
//
//int main() {
//	ld* mass = new ld[3];
//	for (int i = 0; i < 3; ++i)
//		mass[i] = i + 1;
//	mass[2] -= 2;
//	polinomial pol, ref(mass, 3);
//	ifstream in("input.txt", std::ios::binary);
//	in >> pol;
//	in.close();
//	ofstream out("output.txt");
//	//out << pol;
//	polinomial res(pol + ref);
//	ref.check_root(1);
//	ref.add_coef(10, 10);
//	out << ref;
//	out << '\n';
//	out << pol;
//	out << '\n';
//	out << res;
//	out << '\n';
//
//	//std::cout << "== " << (ref == pol) << '\t' << "!= " << (ref != pol) << '\t' << "< " << (ref < pol)
//	//	<< '\t' << "<= " << (ref <= pol) << '\t' << "> " << (ref > pol) << '\t' << ">= " << (ref >= pol);
//	out.close();
//	return 0;
//}