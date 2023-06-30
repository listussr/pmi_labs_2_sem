#include<fstream>
#include<string>
#define ld long double

using std::ofstream;
using std::ifstream;

void getting_data(ifstream& in, ld**& matrix, int& col, int& bar) {
	std::string el;
	int str = 0, stl = 0;
	while (!in.eof() && str != bar){ // ���������� �� �����
		in >> el;
		try {
			ld el_ld = std::stold(el);
			matrix[str][stl] = el_ld;
			stl++;
			if (stl == col) { // ���� ������ ��������� - ��������� �� ���������
				stl = 0;
				str++;
			}
		}
		catch(std::invalid_argument& e){}
	}
}

void changing_matrix(ifstream& in, ld**& matrix, int& bar, int& col) {
	int x1, y1, x2, y2;
	in >> x1 >> y1 >> x2 >> y2; // ��������� �������, � ������ ������� ����� �������� ��������

	x1 >= bar ? x1 = bar - 1 : 1; // �������� �� ����� �� ������� �������
	x2 >= bar ? x1 = bar - 1 : 1;
	y1 >= col ? y1 = col - 1 : 1;
	y2 >= col ? y2 = col - 1 : 1;
	x1 < bar ? x1 = 0 : 1;
	x2 < bar ? x1 = 0 : 1;
	y1 < col ? y1 = 0 : 1;
	y2 < col ? y2 = 0 : 1;


	for (int i = x1; i <= x2; i++) { // ������ �� 0
		for (int j = y1; j <= y2; j++) {
			matrix[i][j] = 0;
		}
	}
}

void counting_middle(ld*& res, ld**& matrix, int& col, int& bar) {

	for (int j = 0; j < col; j++) {
		ld middle = 0;

		for (int i = 0; i < bar; i++) // ��������� ����� ��������� ������� �������
			middle += matrix[i][j];
		middle /= bar; // ������� ������� �������� � ��������� � �������������� ������
		res[j] = middle;
	}
}

void output(ofstream& out, ld* res, int& a) {
	for (ld* n = res; res != n + a; res++) // ����� � ���� ��������� ��������
		out << *res << ' ';
}

void deleting(ld**& matrix, int& col, int& bar) { // ������� �������� �������
	for (int i = 0; i < bar; i++)
		delete[]matrix[i];
	delete[] matrix;
}

int main(){
	ifstream in("input.txt"); // �������� ������
	ofstream out("output.txt");
	
	int collumns, bar;

	in >> bar >> collumns; // ���� ���-�� ����� � ��������

	ld** matrix = new ld*[bar]; // ���������� ���������� ������������� �������
	for (int i = 0; i < bar; i++)
		matrix[i] = new ld[collumns];
	
	getting_data(in, matrix, collumns, bar); // ���������� ������ �� �����
	changing_matrix(in, matrix, bar, collumns); // ������ �������
	in.close();

	ld* res = new ld[collumns]; // ������� ���������
	counting_middle(res, matrix, collumns, bar);

	output(out, res, collumns); // ������� � ����
	out.close();

	deleting(matrix, collumns, bar); // �������� �������

	delete[] res;
	return 0;
}