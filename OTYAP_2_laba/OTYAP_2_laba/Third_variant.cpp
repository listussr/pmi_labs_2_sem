#define _CRT_SECURE_NO_WARNINGS 
#include<fstream>
#include<vector>
#include<cstring>

using std::ifstream;
using std::ofstream;
using std::vector;

typedef size_t ll;

enum State { S, A, B, C, D, E, F };

enum Signal { digit, alpha, border };

/*
			  | S | A  | B  | C  | D  | E  | F  |
	---------------------------------------------
	a..z, A..Z| B | D  | E  | D  | E  | E  |    |
	---------------------------------------------
	0..9	  |	A |	E  | C  | E  | C  | E  |	|
	---------------------------------------------
		' '	  | E | E  | E  | F  | F  | E  |	|
	---------------------------------------------
			  |	  |    |    |    |    |    | 1  |
*/

bool is_digit(char ch) { // проверки
	return (ch >= '0' && ch <= '9');
}

bool is_alpha(char ch) {
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool is_border(char ch) {
	return (ch == ' ' || ch == '\n' || ch == '\0' || ch == '\t');
}

void filling_table(State(*table)[7]) { // заполняем таблицу состояний автомата
	table[digit][S] = A;
	table[alpha][S] = B;
	table[border][S] = E;

	table[digit][A] = E;
	table[alpha][A] = D;
	table[border][A] = E;

	table[digit][B] = C;
	table[alpha][B] = E;
	table[border][B] = E;

	table[digit][C] = E;
	table[alpha][C] = D;
	table[border][C] = F;

	table[digit][D] = C;
	table[alpha][D] = E;
	table[border][D] = F;

	table[digit][E] = E;
	table[alpha][E] = E;
	table[border][E] = E;
}


struct lexema {
	bool error_flag;
	char* str;
};

ll Get_File_Size(ifstream& in) { // узнаём размер файла
	in.seekg(1, std::ios_base::end);
	ll SIZE = in.tellg();
	in.seekg(0, std::ios_base::beg);
	return SIZE;
}

Signal check_signal(bool a, bool d, bool b) { // проверка вида символа для передвижения по таблице автомата
	if (a) 
		return alpha;
	else if (d)
		return digit;
	else 
		return border;
}

void lexanalisis(vector<lexema>& res, char* mass, State(*table)[7], ll size) { // функция обработки строки
	State cur = S;
	ll pos{ 0 }, null_pos{ 0 };
	lexema lex;
	lex.error_flag = false;
	char* buf = mass;
	while (size - pos > 0) {

		bool digit_flag = is_digit(*mass), alpha_flag = is_alpha(*mass), border_flag = is_border(*mass);

		if (!(digit_flag || alpha_flag || border_flag)) // если символ не принадлежит алфавиту ставим флаг ошибки
			lex.error_flag = true;

		if (lex.error_flag && border_flag) { // отталкиваемся от стоящего флага ошибки и текущего символа
			cur = S;
			++mass;
			null_pos = ++pos;
			lex.error_flag = false;
		}
		if (lex.error_flag) {
			++pos;
			++mass;
			continue;
		}

		if(size - pos)
			cur = table[check_signal(is_alpha(*mass), is_digit(*mass), is_border(*mass))][cur]; // идём по таблице автомата

		if (cur == F) { // формируем лексемы
			ll sz = pos - null_pos;
			lex.str = new char[sz + 1];
			strncpy(lex.str, &buf[0] + null_pos, sz);
			lex.str[sz] = '\0';
			res.push_back(lex);
			null_pos = pos + 1;
			cur = S;
		}
		else if (border_flag && cur == E) {
			null_pos = pos + 1;
			cur = S;
		}
		++pos;
		++mass;
	}
}

void outp(ofstream& out, vector<lexema> res) { // вывод в файл
	if (!res.empty()) {
		for (ll i = 0; i < res.size() - 1; ++i)
			out << res[i].str << ' ';
		out << res[res.size() - 1].str;
	}
}

void deleting(vector<lexema>& vec) {
	for (ll i = 0; i < vec.size(); ++i) {
		vec[i].str = nullptr;
		delete vec[i].str;
	}
}

int main() {
	ifstream in("input.txt", std::ios::binary);
	if (in.is_open()) {
		ll SIZE_OF_STR = Get_File_Size(in);
		char* inp_str = new char[SIZE_OF_STR];
		in.getline(inp_str, SIZE_OF_STR, '\0');
		in.close();

		State current_t[3][7];
		filling_table(current_t);
		vector<lexema> res;
		lexanalisis(res, inp_str, current_t, SIZE_OF_STR);
		ofstream out("output.txt");
		outp(out, res);
		out.close();
		deleting(res);
	}
	return 0;
}