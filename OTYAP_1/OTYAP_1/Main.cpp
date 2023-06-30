#include<fstream>
#include<vector>
/*
	�������� ��-������� ���� �� �����; ��-������� ������������ ������ ��� ����; 
*/
using std::ifstream;
using std::ofstream;
using std::vector;

bool is_digit(char ch) { // ������� �������� �� ������������ ������� �����
	return (ch >= '0' && ch <= '9') ? 1 : 0;
}

bool is_alpha(char ch) { // ������� �������� �� ������������ ������� ��������� �����
	return (ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z') ? 1 : 0;
}

bool is_border(char ch) { // ������� �������� �� ������������ ������� ���������� �����
	return (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\0') ? 1 : 0;
}

vector<char*> spisok(char* const text) { // �������, ��������� �����, ������ ��� �������
	vector<char*> list;
	char* word = new char[100];
	bool flag = true;
	for (size_t i = 1, j = 0; i < 100; i++) {

		if (!is_digit(text[i]) && !is_alpha(text[i]) && !is_border(text[i])) { // �������� �� ������������ ��������
			j = 0;
			flag = false;
			continue;
		}

		if (is_border(text[i])) // ���������� ���� ������
			flag = true;

		if (!flag && !is_border(text[i])) { // ���������� �����, ���� ���� ���-�� �� ������������� ����������� �����
			j = 0;
			continue;
		}

		if ((is_digit(text[i]) && is_digit(text[i - 1]) || (is_alpha(text[i - 1])) && is_alpha(text[i]))) { // ���� ���-�� �� ������������� ����� ������ ���� ������
			j = 0;
			flag = false;
		}

		if ((is_digit(text[i]) && is_alpha(text[i - 1])) || (is_digit(text[i - 1]) && is_alpha(text[i]))) { // ���� ���������� ������ � ������� ������������� �������
			if (j == 0) {
				word[j] = text[i - 1];
				j++;
			}
			word[j] = text[i];
			j++;
		}
		else if (i != 1 && j > 1 && is_border(text[i])) { // ���� � ����� > 1 �������, ������ - ������ � ������� > 0
			word[j] = '\0';
			list.push_back(word);
			/// ///////////////////////////////////////////////// ������ ?????????????????????????????????
			word = new char[100]; // ������������� ������........
			/// /////////////////////////////////////////////////
			j = 0;
		}
		else // ���� ������������������ ����������
			j = 0;
	}
	return list;
}

void output(ofstream& out, vector<char*> text) { // ����� ������� ������������ ����
	for (size_t i = 0; i < text.size(); i++)
		out << text[i] << ' ';
}

void deleting(vector<char*>& vec) { // ������������ ������
	for (size_t i = 0; i < vec.size(); i++) {
		delete[] vec[i];
		vec[i] = nullptr;
	}
}

int main()
{
	ifstream in("input.txt"); // ��������� �����
	ofstream out("output.txt");
	if (in.is_open()) {
		char text[100];
		in.getline(text, 100, '\0'); // ������ � ��������� �������� ����
		in.close();

		vector<char*> list = spisok(text); // ������ ������ � ��������

		output(out, list); // ����� ������� � ���������� ���������
		out.close();
		deleting(list);
	}
	return 0;
}