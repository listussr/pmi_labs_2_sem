#include<fstream> // подключаем библиотеки
#include<string>

#define ld long double // добавл€ем макрос, чтобы проще удобнее писать

using std::string; // чтобы не писать std::string

ld find_max(ld* arrray_of_elements, int& size_of_array) { // функци€ нахождени€ максимального элемента

	// присваиваем max_el значение 0 элемента, и проход€ по массиву, будем сравнивать max_el 
	// с каждым элементом, и если элемент > max_el, то max_el присваиваетс€ значение этого элемента

	ld max_el = arrray_of_elements[0];
	for (ld* n = arrray_of_elements; arrray_of_elements != n + size_of_array; arrray_of_elements++) {
		if (max_el < *arrray_of_elements)
			max_el = *arrray_of_elements;
	}
	return max_el;
}

int find_repetitions(ld* arrray_of_elements, int& size_of_array, ld& val) { // функци€ поиска повтор€ющихс€ элементов

	// если при проходе по массиву встречаетс€ такой же элемент, r инкрементируетс€
	int r = 0;
	for (ld* n = arrray_of_elements; arrray_of_elements != size_of_array + n; arrray_of_elements++) {
		if (val == *arrray_of_elements)
			r++;
	}
	return r;
}

void output(ld& max_element_in_array, int& repetitions_amount){ // функци€ вывода значений в выходной файл
	std::ofstream out("output.txt");
	out << max_element_in_array << ' ' << repetitions_amount;
	out.close();
}

void push(ld*& arrray_of_elements, int& size_of_array, ld& element) { // push_back() дл€ динамического массива

	// создаЄм новый массив, в котором будем хранить данные из прошлого массива
	ld* new_arrray_of_elements = new ld[size_of_array];
	for (int i = 0; i < size_of_array; i++)
		new_arrray_of_elements[i] = arrray_of_elements[i];
	// очищаем пам€ть от исходного массива и увеличиваем его будущий размер
	delete[] arrray_of_elements;
	++size_of_array;
	// перевыдел€ем пам€ть на исходный массив и заполн€ем его данными
	arrray_of_elements = new ld[size_of_array];
	for (int i = 0; i < size_of_array - 1; i++)
		arrray_of_elements[i] = new_arrray_of_elements[i];
	// удал€ем пам€ть, выделенную на массив дл€ промежуточного хранени€ данных
	delete[] new_arrray_of_elements;
	arrray_of_elements[size_of_array - 1] = element;
}

ld* getting_data(std::ifstream& in, int& size_of_array) { // функци€, осуществл€юща€ ввод из исходного файла
	ld* arrray_of_elements = new ld[size_of_array];
	string element;
	// пока в файле есть элементы дл€ ввода, вводим их
	while (in >> element) {
		try{
			// если в файле оказалось не число, то выбрасываетс€ исключение
			ld ld_element = std::stold(element);
			// если в файле оказалось число, то оно добавл€етс€ в массив
			push(arrray_of_elements, size_of_array, ld_element);
		}
		catch (std::invalid_argument& e) {}
	}
	return arrray_of_elements;
}

int main() // точка входа в программу
{
	int size_of_array = 0;
	std::ifstream in("input.txt");
	ld* arrray_of_elements = getting_data(in, size_of_array);
	in.close();
	ld max_element_in_array = find_max(arrray_of_elements, size_of_array);
	int amount_of_repetitions = find_repetitions(arrray_of_elements, size_of_array, max_element_in_array);
	output(max_element_in_array, amount_of_repetitions);
	delete[] arrray_of_elements;
	return 0;
}