#include<fstream>
#include<string>
#define ld long double

using std::ofstream;
using std::ifstream;

void getting_data(ifstream& in, ld**& matrix, int& col, int& bar) {
	std::string el;
	int str = 0, stl = 0;
	while (!in.eof() && str != bar){ // считывание из файла
		in >> el;
		try {
			ld el_ld = std::stold(el);
			matrix[str][stl] = el_ld;
			stl++;
			if (stl == col) { // если строка заполнена - переходим на следующую
				stl = 0;
				str++;
			}
		}
		catch(std::invalid_argument& e){}
	}
}

void changing_matrix(ifstream& in, ld**& matrix, int& bar, int& col) {
	int x1, y1, x2, y2;
	in >> x1 >> y1 >> x2 >> y2; // считываем границы, в рамках которых нужно помен€ть элементы

	x1 >= bar ? x1 = bar - 1 : 1; // проверка на выход за границы массива
	x2 >= bar ? x1 = bar - 1 : 1;
	y1 >= col ? y1 = col - 1 : 1;
	y2 >= col ? y2 = col - 1 : 1;
	x1 < bar ? x1 = 0 : 1;
	x2 < bar ? x1 = 0 : 1;
	y1 < col ? y1 = 0 : 1;
	y2 < col ? y2 = 0 : 1;


	for (int i = x1; i <= x2; i++) { // замена на 0
		for (int j = y1; j <= y2; j++) {
			matrix[i][j] = 0;
		}
	}
}

void counting_middle(ld*& res, ld**& matrix, int& col, int& bar) {

	for (int j = 0; j < col; j++) {
		ld middle = 0;

		for (int i = 0; i < bar; i++) // вычисл€ем сумму элементов столбца матрицы
			middle += matrix[i][j];
		middle /= bar; // считаем среднее значение и сохран€ем в результирующий массив
		res[j] = middle;
	}
}

void output(ofstream& out, ld* res, int& a) {
	for (ld* n = res; res != n + a; res++) // вывод в файл результат операций
		out << *res << ' ';
}

void deleting(ld**& matrix, int& col, int& bar) { // функци€ удалени€ матрицы
	for (int i = 0; i < bar; i++)
		delete[]matrix[i];
	delete[] matrix;
}

int main(){
	ifstream in("input.txt"); // открытие файлов
	ofstream out("output.txt");
	
	int collumns, bar;

	in >> bar >> collumns; // ввод кол-ва строк и столбцов

	ld** matrix = new ld*[bar]; // объ€вление двумерного динамического массива
	for (int i = 0; i < bar; i++)
		matrix[i] = new ld[collumns];
	
	getting_data(in, matrix, collumns, bar); // считывание данных из файла
	changing_matrix(in, matrix, bar, collumns); // мен€ем матрицу
	in.close();

	ld* res = new ld[collumns]; // находим результат
	counting_middle(res, matrix, collumns, bar);

	output(out, res, collumns); // выводим в файл
	out.close();

	deleting(matrix, collumns, bar); // удаление матрицы

	delete[] res;
	return 0;
}