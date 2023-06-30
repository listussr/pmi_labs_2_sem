#include<fstream>
#include<vector>
/*
	написать по-другому ввод из файла; по-другому перевыделять память под слов; 
*/
using std::ifstream;
using std::ofstream;
using std::vector;

bool is_digit(char ch) { // функция проверки на соответствие символа числу
	return (ch >= '0' && ch <= '9') ? 1 : 0;
}

bool is_alpha(char ch) { // функция проверки на соответствие символа латинской букве
	return (ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z') ? 1 : 0;
}

bool is_border(char ch) { // функция проверки на соответствие символа барьерному знаку
	return (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\0') ? 1 : 0;
}

vector<char*> spisok(char* const text) { // функция, находящая слова, нужные для задания
	vector<char*> list;
	char* word = new char[100];
	bool flag = true;
	for (size_t i = 1, j = 0; i < 100; i++) {

		if (!is_digit(text[i]) && !is_alpha(text[i]) && !is_border(text[i])) { // проверка на соответствие алфавиту
			j = 0;
			flag = false;
			continue;
		}

		if (is_border(text[i])) // сбрасываем флаг ошибки
			flag = true;

		if (!flag && !is_border(text[i])) { // пропускаем слово, если хоть что-то не соответствует определению слова
			j = 0;
			continue;
		}

		if ((is_digit(text[i]) && is_digit(text[i - 1]) || (is_alpha(text[i - 1])) && is_alpha(text[i]))) { // если что-то не соответствует слову ставим флаг ошибки
			j = 0;
			flag = false;
		}

		if ((is_digit(text[i]) && is_alpha(text[i - 1])) || (is_digit(text[i - 1]) && is_alpha(text[i]))) { // если предыдущий символ и текущий соответствуют заданию
			if (j == 0) {
				word[j] = text[i - 1];
				j++;
			}
			word[j] = text[i];
			j++;
		}
		else if (i != 1 && j > 1 && is_border(text[i])) { // если в слове > 1 символа, символ - барьер и счётчик > 0
			word[j] = '\0';
			list.push_back(word);
			/// ///////////////////////////////////////////////// вопрос ?????????????????????????????????
			word = new char[100]; // перевыделение памяти........
			/// /////////////////////////////////////////////////
			j = 0;
		}
		else // если последовательность нарушается
			j = 0;
	}
	return list;
}

void output(ofstream& out, vector<char*> text) { // вывод вектора получившихся слов
	for (size_t i = 0; i < text.size(); i++)
		out << text[i] << ' ';
}

void deleting(vector<char*>& vec) { // освобождение памяти
	for (size_t i = 0; i < vec.size(); i++) {
		delete[] vec[i];
		vec[i] = nullptr;
	}
}

int main()
{
	ifstream in("input.txt"); // открываем файлы
	ofstream out("output.txt");
	if (in.is_open()) {
		char text[100];
		in.getline(text, 100, '\0'); // читаем и закрываем исходный файл
		in.close();

		vector<char*> list = spisok(text); // делаем вектор с ответами

		output(out, list); // вывод ответов и завершение программы
		out.close();
		deleting(list);
	}
	return 0;
}