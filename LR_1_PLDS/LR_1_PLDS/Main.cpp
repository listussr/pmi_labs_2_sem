//#include<fstream>
//#define ld long double
//
//ld find_max(ld* arrray_of_elements, int& size_of_array){
//	ld max_el = arrray_of_elements[0];
//	for (ld* n = arrray_of_elements; arrray_of_elements != n + size_of_array; *arrray_of_elements++) {
//		if (max_el < *arrray_of_elements)
//			max_el = *arrray_of_elements;
//	}
//	return max_el;
//}
//
//int find_repetitions(ld* arrray_of_elements, int& size_of_array, ld& val) {
//	int r = 0;
//	for (ld* n = arrray_of_elements; arrray_of_elements != size_of_array + n; *arrray_of_elements++) {
//		if (val == *arrray_of_elements)
//			r++;
//	}
//	return r;
//}
//
//void output(ld& max_element_in_array, int& repetitions_amount)
//{
//	std::ofstream out("output.txt");
//	out << max_element_in_array << ' ' << repetitions_amount;
//	out.close();
//}
//
//void push(ld*& arrray_of_elements, int& size_of_array, ld& element) {
//	ld* new_arrray_of_elements = new ld[size_of_array];
//	for (int i = 0; i < size_of_array; i++)
//		new_arrray_of_elements[i] = arrray_of_elements[i];
//	delete[] arrray_of_elements;
//	++size_of_array;
//	arrray_of_elements = new ld[size_of_array];
//	for (int i = 0; i < size_of_array - 1; i++)
//		arrray_of_elements[i] = new_arrray_of_elements[i];
//	delete[] new_arrray_of_elements;
//	arrray_of_elements[size_of_array - 1] = element;
//}
//
//ld* getting_data(std::ifstream& in, int& size_of_array) {
//	ld* arrray_of_elements = new ld[size_of_array];
//	//while(!in.eof()) {
//	//	ld element;
//	//	in >> element;
//	//	push(arrray_of_elements, size_of_array, element);
//	//}
//	ld element;
//	while (in >> element) {
//		push(arrray_of_elements, size_of_array, element);
//	}
//	return arrray_of_elements;
//}
//
//int main()
//{
//	int size_of_array = 0;
//	std::ifstream in("input.txt");
//	ld* arrray_of_elements = getting_data(in, size_of_array);
//	in.close();
//	ld max_element_in_array = find_max(arrray_of_elements, size_of_array);
//	int amount_of_repetitions = find_repetitions(arrray_of_elements, size_of_array, max_element_in_array);
//	output(max_element_in_array, amount_of_repetitions);
//	delete[] arrray_of_elements;
//	return 0;
//}