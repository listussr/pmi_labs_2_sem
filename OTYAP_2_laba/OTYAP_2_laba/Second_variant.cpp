//#define _CRT_SECURE_NO_WARNINGS 
//#include<fstream>
//#include<vector>
//#include<cstring>
//
//using std::ifstream;
//using std::ofstream;
//using std::vector;
//
//typedef size_t ll;
//
//enum State { S, A, B, C, D, E, F };
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
//	return (ch == ' ' || ch == '\n' || ch == '\0' || ch == '\t');
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
//			  | S | A  | B  | C  | D  | E  | F  |
//	---------------------------------------------
//	a..z, A..Z| B | D  | E  | D  | E  | E  |    |
//	---------------------------------------------
//	0..9	  |	A |	E  | C  | E  | C  | E  |	|
//	---------------------------------------------
//		' '	  | E | E  | E  | F  | F  | E  |	|
//	---------------------------------------------
//			  |	  |    |    |    |    |    | 1  |
//*/
//
//
//
//void changing_automat_state(State& st, bool digit, bool alpha, bool border) {
//	// digit - цифра, alpha - буква, border - граничное состояние
//	if (st == S) { // идём по матрице состояний
//		if (digit)
//			st = A;
//		else if (alpha)
//			st = B;
//		else
//			st = E;
//	}
//	else if (st == A) {
//		if (alpha)
//			st = D;
//		else
//			st = E;
//	}
//	else if (st == B) {
//		if (digit)
//			st = C;
//		else
//			st = E;
//	}
//	else if (st == C) {
//		if (alpha)
//			st = D;
//		else if (digit)
//			st = E;
//		else
//			st = F;
//	}
//	else if (st == D) {
//		if (alpha)
//			st = E;
//		else if (digit)
//			st = C;
//		else
//			st = F;
//	}
//	else if (st == E) {
//		st = E;
//	}
//}
//
//void lexanalisis(vector<lexema>& res, char* mass, ll Size_Of_Mass) {
//	ll pos{ 0 }, first_pos{ 0 };
//	State st = S;
//	lexema lex{};
//	lex.error_flag = false;
//	char* buf = mass;
//
//	while (Size_Of_Mass - pos) {
//
//		if ((lex.error_flag) && is_border(*mass)) { // сбрасываем флаг ошибки при нахождении граничного символа
//			lex.error_flag = false;
//			first_pos = pos;
//		}
//		if (lex.error_flag) { // если стоит флаг ошибки
//			++pos;
//			++mass;
//			continue;
//		}
//
//		bool digit = is_digit(*mass), alpha = is_alpha(*mass), border = is_border(*mass); // флаги символов алфавита
//
//		if (!(digit || border || alpha)) {
//			lex.error_flag = true; // ставим флаг ошибки - причина: символ не принадлежит алфавиту
//			++pos;
//			++mass;
//			continue;
//		}
//		changing_automat_state(st, digit, alpha, border);
//
//		if (border && st == F) {
//			
//			// сохранение лексемы в вектор, если встретился экранирующий символ
//			// и мы находимся в состояниях детерминированного автомата откуда возможен выход
//		
//			ll sz = pos - first_pos;
//			lex.str = new char[sz + 1];
//			strncpy(&lex.str[0], &buf[0] + first_pos, sz);
//			lex.str[sz] = '\0';
//			res.push_back(lex);
//			st = S;
//			first_pos = pos + 1;
//		}
//		else if (border && st != F) {
//			first_pos = pos + 1;
//			st = S;
//		}
//		++pos;
//		++mass;
//	}
//}
//
//void outp(ofstream& out, vector<lexema> res) {
//	if (!res.empty()) {
//		for (ll i = 0; i < res.size() - 1; ++i)
//			out << res[i].str << ' ';
//		out << res[res.size() - 1].str;
//	}
//}
//
//void deleting(vector<lexema>& vec) {
//	for (ll i = 0; i < vec.size(); ++i) {
//		vec[i].str = nullptr;
//		delete[] vec[i].str;
//	}
//}
//
//int main() {
//	ifstream in("input.txt");
//	if (in.is_open()) {
//		ll SIZE_OF_STR = Get_File_Size(in);
//		char* inp_str = new char[SIZE_OF_STR];
//		in.getline(inp_str, SIZE_OF_STR, '\0');
//		in.close();
//		vector<lexema> res;
//		lexanalisis(res, inp_str, SIZE_OF_STR);
//		ofstream out("output.txt");
//		outp(out, res);
//		out.close();
//	}
//	return 0;
//}