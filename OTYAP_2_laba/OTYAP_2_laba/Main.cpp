//#define _CRT_SECURE_NO_WARNINGS 
//#include<fstream>
//#include<vector>
//
//using std::ifstream;
//using std::ofstream;
//using std::vector;
//
//typedef size_t ll;
//
//enum State { S, A, B, AF, BF, E };
//
//bool is_digit(char ch) {
//	return (ch >= '0' && ch <= '9');
//}
//
//bool is_alpha(char ch) {
//	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
//}
//
//bool is_border(char ch) {
//	return (ch == ' ' || ch == '\0');
//}
//
//bool is_alphabet(char ch) {
//	return (is_alpha(ch) || is_digit(ch) || is_border(ch));
//}
//
//struct lexema {
//	bool error_flag;
//	char* str;
//};
//
//ll Get_File_Size(ifstream& in) {
//	in.seekg(1, std::ios_base::end);
//	ll SIZE = in.tellg();
//	in.seekg(0, std::ios_base::beg);
//	return SIZE;
//}
//
//
///*
//			  | S | A  | B  | AF | BF |
//	-----------------------------------
//	a..z, A..Z| B | BF |  E | BF |	E |
//	-----------------------------------
//	0..9	  |	A |	 E | AF |  E | AF |
//	-----------------------------------
//			  |   |    |	|  1 |  1 |
//*/
//
//
//void changing_automat_state(char ch, State& st, lexema& lex, bool digit, bool alpha) {
//	if (st == S) { // идём по матрице состояний
//		if (digit)
//			st = A;
//		else
//			st = B;
//	}
//	else if (st == A || st == AF) {
//		if (alpha)
//			st = BF; // переходим в возможное конечное состояние детерминированного автомата
//		else
//			st = E; // выставляем флаг несоответствия слову
//	}
//	else if (st == B || st == BF) {
//		if (digit)
//			st = AF;
//		else
//			st = E;
//	}
//}
//
//void lexanalisis(vector<lexema>& res, char* mass, ll Size_Of_Mass) {
//	ll pos{ 0 };
//	State st = S;
//	lexema lex{};
//	ll first_pos{ 0 };
//	lex.error_flag = false;
//	char* buf = mass;
//
//	while (Size_Of_Mass - pos) {
//
//		if ((lex.error_flag || st == E) && is_border(*mass)) { // сбрасываем флаг ошибки при нахождении граничного символа
//			lex.error_flag = false;
//			first_pos = pos;
//		}
//		if (lex.error_flag || st == E) { // если стоит флаг ошибки
//			++pos;
//			++mass;
//			continue;
//		}
//
//		bool digit = is_digit(*mass), alpha = is_alpha(*mass); // соответствие 
//		if (!is_alphabet(*mass)) {
//			lex.error_flag = true; // ставим флаг ошибки - причина: символ не принадлежит алфавиту
//			++pos;
//			++mass;
//			continue;
//		}
//		if (is_border(*mass) && (st == AF || st == BF)) { // сохранение лексемы в вектор, если встретился экранирующий символ
//														  // и мы находимся в состояниях детерминированного автомата откуда возможен выход
//			ll sz = pos - first_pos;
//			lex.str = new char[sz + 1];
//			std::strncpy(&lex.str[0], &buf[0] + first_pos, sz);
//			lex.str[sz] = '\0';
//			res.push_back(lex);
//			st = S;
//			first_pos = pos;
//		}
//		else
//			changing_automat_state(*mass, st, lex, digit, alpha);
//		
//		++pos;
//		++mass;
//	}
//}
//
//void outp(ofstream& out, vector<lexema> res) {
//	if (!res.empty()) {
//		for (ll i = 0; i < res.size(); ++i)
//			out << res[i].str;
//	}
//}
//
//void deleting(vector<lexema>& vec) {
//	for (int i = 0; i < vec.size(); ++i) {
//		vec[i].str = nullptr;
//		delete[] vec[i].str;
//	}
//}
//
//int main() {
//	ifstream in("input.txt");
//	ll SIZE_OF_STR = Get_File_Size(in);
//	char* inp_str = new char[SIZE_OF_STR];
//	in.getline(inp_str, SIZE_OF_STR, '\0');
//	in.close();
//	vector<lexema> res;
//	lexanalisis(res, inp_str, SIZE_OF_STR);
//	ofstream out("output.txt");
//	outp(out, res);
//	out.close();
//	return 0;
//}