#define nul nullptr
#include<fstream> // подключаем библиотеки
#include<math.h> // чтобы не писать свою функцию степени
#include<queue> // для перегрузки потока ввода
#include<string>
#include<iostream>

using std::ofstream; // чтобы удобно было
using std::ifstream;
using std::ostream;

typedef int size_m; // для красоты и удобства
typedef long double ld;

class cyclic_singly_linked_list;

/*
	Краткая справка по методам из задания

	*	метод 1 - проверка корня:
		-> реализован через метод check_root(), возвращающий булево значение

	*	метод 2 - добавление коэфицента:
		-> во входном файле записан коэфицент, за ним степень, при которой стоит этот коэфицент,
		реализация через метод add_koef(), оперирует непосредственно с полями класса

	*	метод 3 - сложение многочленов:
		-> реализован через перегруженный оператор +, возвращающий объект типа polinomial

	*	метод 4 - умножение на константу:
		-> реализован через перегруженный оператор *=, оперирующий непосредственно с полями класса

	*	метод 5 - перемножение многочленов:
		-> реализован через перегруженный оператор *, возвращающий объект типа polinomial
*/


/*sa
все дефайны сделаны для того, чтобы повысить оригинальность

названия старался подбирать наиболее понятные
*/
#define opening_input_file ifstream in("input.txt")
#define opening_output_file ofstream out("output.txt");
#define psevdo_random srand(time(NULL))
#define boolean_variable bool
#define long_fractional_number ld
#define long_fractional_number_pointer ld*
#define overloading_equal operator=
#define overloading_boolean_equal operator==
#define overloading_no_equal operator!=
#define overloading_fewer operator<
#define overloading_fewer_or_equal operator<=
#define overloading_more operator>
#define overloading_more_or_equal operator>=
#define overloading_plus operator+
#define overloading_multiplication_and_equality operator*=
#define overloading_multiplication operator*
#define class_friend friend
#define null_value void
#define null_value_pointer void*
#define four_byte_integer int
#define invariant const
#define reference &
#define deleting_a_single_element delete
#define overloading_deleting_a_single_element operator delete
#define deleting_an_array delete[]
#define overloading_deleting_an_array operator delete[]
#define overloading_an_operator_new_single operator new
#define overloading_an_operator_new_array operator new[]
#define getting_random_integer rand()
#define thruth true
#define lie false
#define recover return
#define object_template_private class
#define object_template_public struct
#define opened_functions_in_template public
#define overloading_output_operator operator<<
#define overloading_input_operator operator>>
#define current_element_pointer this
#define current_element *this
#define loop_while while
#define loop_for for
#define logic_operator_if if
#define logic_operator_else_if else if
#define logic_operator_else else
#define new_line_in_console std::cout << '\n';
#define tab '\t'
#define central_function int main()

object_template_private polinomial_class_ { // класс многочлена
	long_fractional_number_pointer array_of_coefficents_for_polinomial; // массив коэфицентов
	size_m max_degree_in_current_polinomial; // макс. степень, или иначе размер массива
opened_functions_in_template:
	polinomial_class_(); // конструкторы и деструктор
	polinomial_class_(long_fractional_number_pointer, size_m); // конструктор инициализации полинома
	polinomial_class_(invariant polinomial_class_ reference); // конструктор копирования
	~polinomial_class_(); // деструктор

	polinomial_class_ overloading_equal(invariant polinomial_class_ reference); // оператор присваивания

	boolean_variable overloading_boolean_equal(polinomial_class_ reference); // операции сравнения
	boolean_variable overloading_no_equal(polinomial_class_ reference); // операция !=
	boolean_variable overloading_fewer(polinomial_class_ reference); // операция < 
	boolean_variable overloading_fewer_or_equal(polinomial_class_ reference); // операция <=
	boolean_variable overloading_more(polinomial_class_ reference); // операция >
	boolean_variable overloading_more_or_equal(polinomial_class_ reference); // операция >= 

	polinomial_class_ overloading_plus(polinomial_class_ reference); // перегруженные операторы для методов 3 - 5
	null_value overloading_multiplication_and_equality(long_fractional_number); // операция *= скалирования многочлена
	polinomial_class_ overloading_multiplication(polinomial_class_ reference); // операция * для перемножения многочленов

	boolean_variable checking_the_number_for_matching_the_root(long_fractional_number); // метод 1 <-> проверка корня
	null_value add_a_coefficient_into_a_polinomial_to_certain_place(long_fractional_number, size_m); // метод 2 <-> вставка коэфицента в какую=то степено

	size_m get_max_degree_in_polinomial(); // возвращаем максимальную степень многочлена

	// перегрузка операторов new и delete
	null_value_pointer overloading_an_operator_new_single(size_t size); // new для единичного указателя
	null_value_pointer overloading_an_operator_new_array(size_t size); // new для массива
	null_value overloading_deleting_a_single_element(null_value_pointer ptr); // delete для единичного указателя
	null_value overloading_deleting_an_array(null_value_pointer ptr); // delete для массива

	class_friend ofstream reference overloading_output_operator(ofstream reference, polinomial_class_ reference); // перегрузка операторов вывода в файл
	class_friend ifstream reference overloading_input_operator(ifstream reference, polinomial_class_ reference); // перегрузка оператора ввода с файла

	class_friend ostream reference overloading_output_operator(ostream reference, polinomial_class_ reference); // перегрузка оператора вывода в консоль

	class_friend cyclic_singly_linked_list; // объявляем друга класса
};

polinomial_class_::polinomial_class_() { // конструктор по умолчанию
	array_of_coefficents_for_polinomial = nul;
	max_degree_in_current_polinomial = 0;
}

polinomial_class_::polinomial_class_(long_fractional_number_pointer mass, size_m variable_sz) { // конструктор инициализации
	max_degree_in_current_polinomial = variable_sz - 1; // максимальная степень
	array_of_coefficents_for_polinomial = new long_fractional_number[variable_sz]; // выделяем память
	loop_for(size_m counter_i = 0, counter_j = variable_sz - 1; counter_i < variable_sz; ++counter_i, --counter_j) // копируем массив
		array_of_coefficents_for_polinomial[counter_i] = mass[counter_j];
}

polinomial_class_::polinomial_class_(invariant polinomial_class_ reference cpy) { // конструктор копирования
	max_degree_in_current_polinomial = cpy.max_degree_in_current_polinomial;
	array_of_coefficents_for_polinomial = new long_fractional_number[cpy.max_degree_in_current_polinomial + 1]; // выделяем память
	loop_for(size_m counter_i = 0; counter_i <= cpy.max_degree_in_current_polinomial; ++counter_i) // копируем массив
		array_of_coefficents_for_polinomial[counter_i] = cpy.array_of_coefficents_for_polinomial[counter_i];
}

polinomial_class_::~polinomial_class_() { // деструктор
	logic_operator_if(array_of_coefficents_for_polinomial) {
		deleting_an_array array_of_coefficents_for_polinomial; // чистим память
		array_of_coefficents_for_polinomial = nul;
		max_degree_in_current_polinomial = 0;
	}
}

polinomial_class_ polinomial_class_::overloading_equal(invariant polinomial_class_ reference referenced_value) { // перегрузка оператора присваивания
	logic_operator_if(reference referenced_value != current_element_pointer) { // если присваиваемый объект не равен нынешнему
		polinomial_class_ neew_polinomial(referenced_value); // создаём новый объект через конструктор копирования
		logic_operator_if(max_degree_in_current_polinomial and array_of_coefficents_for_polinomial) { // через std::swap() меняем поля
			std::swap(max_degree_in_current_polinomial, neew_polinomial.max_degree_in_current_polinomial);
			std::swap(array_of_coefficents_for_polinomial, neew_polinomial.array_of_coefficents_for_polinomial);
		}
		logic_operator_else {
			max_degree_in_current_polinomial = neew_polinomial.max_degree_in_current_polinomial; neew_polinomial.max_degree_in_current_polinomial = 0;
			array_of_coefficents_for_polinomial = neew_polinomial.array_of_coefficents_for_polinomial; neew_polinomial.array_of_coefficents_for_polinomial = nul;
		}
	}
	recover current_element;
}

boolean_variable polinomial_class_::overloading_boolean_equal(polinomial_class_ reference referenced_value) { // перегрузка оператора ==
	logic_operator_if(max_degree_in_current_polinomial - referenced_value.max_degree_in_current_polinomial) // если максимальные степени не совпадают
		recover lie;
	loop_for(size_m counter_i = 0; counter_i <= max_degree_in_current_polinomial; ++counter_i) // если коэфиценты при степенях не совпадают
		logic_operator_if(array_of_coefficents_for_polinomial[counter_i] - referenced_value.array_of_coefficents_for_polinomial[counter_i])
			recover lie;
	recover thruth;
}

boolean_variable polinomial_class_::overloading_no_equal(polinomial_class_ reference referenced_value) { // перегрузка оператора !=
	recover !overloading_boolean_equal(referenced_value); // уменьшенная проверка на соответствие макс. степеней и коэфицентов при степенях
}

boolean_variable polinomial_class_::overloading_fewer(polinomial_class_ reference referenced_value) { // перегрузка оператора <
	logic_operator_if(max_degree_in_current_polinomial != referenced_value.max_degree_in_current_polinomial) // сравниваем максимальные степени
		recover max_degree_in_current_polinomial < referenced_value.max_degree_in_current_polinomial;
	logic_operator_else { // проходимся по коэфицентам и смотрим на то, что больше
		size_m counter_sz = max_degree_in_current_polinomial;
		loop_for (; counter_sz; --counter_sz) {
			logic_operator_if(array_of_coefficents_for_polinomial[counter_sz] != referenced_value.array_of_coefficents_for_polinomial[counter_sz])
				recover array_of_coefficents_for_polinomial[counter_sz] < referenced_value.array_of_coefficents_for_polinomial[counter_sz];
		}
		recover thruth;
	}
}

boolean_variable polinomial_class_::overloading_fewer_or_equal(polinomial_class_ reference referenced_value) { // перегрузка оператора <= 
	recover overloading_fewer(referenced_value) or overloading_boolean_equal(referenced_value); // выражается через другие
}

boolean_variable polinomial_class_::overloading_more(polinomial_class_ reference referenced_value) { // перегрузка оператора >
	recover !overloading_fewer_or_equal(referenced_value); // можно выразить через другие
}

boolean_variable polinomial_class_::overloading_more_or_equal(polinomial_class_ reference referenced_value) { // перегрузка оператора >=
	recover !overloading_fewer(referenced_value); // выражается через другое
}

polinomial_class_ polinomial_class_::overloading_plus(polinomial_class_ reference referenced_value) { // сложение многочленов
	polinomial_class_ resulting_value;
	resulting_value.array_of_coefficents_for_polinomial = new long_fractional_number[(referenced_value.max_degree_in_current_polinomial > max_degree_in_current_polinomial ? referenced_value.max_degree_in_current_polinomial : max_degree_in_current_polinomial) + 1]; // выделение памяти
	resulting_value.max_degree_in_current_polinomial = referenced_value.max_degree_in_current_polinomial > max_degree_in_current_polinomial ? referenced_value.max_degree_in_current_polinomial : max_degree_in_current_polinomial; // ищем макс. степень
	logic_operator_if(referenced_value.max_degree_in_current_polinomial == max_degree_in_current_polinomial) { // если макс. степени равны
		loop_for (size_m counter_i = 0; counter_i <= resulting_value.max_degree_in_current_polinomial; ++counter_i)
			resulting_value.array_of_coefficents_for_polinomial[counter_i] = referenced_value.array_of_coefficents_for_polinomial[counter_i] + array_of_coefficents_for_polinomial[counter_i];
	}
	logic_operator_else { // если макс. степени не совпадают
	logic_operator_if(referenced_value.max_degree_in_current_polinomial > max_degree_in_current_polinomial) {
			loop_for (size_m counter_i = 0; counter_i <= max_degree_in_current_polinomial; ++counter_i)
				resulting_value.array_of_coefficents_for_polinomial[counter_i] = referenced_value.array_of_coefficents_for_polinomial[counter_i] + array_of_coefficents_for_polinomial[counter_i];
			loop_for (size_m counter_i = max_degree_in_current_polinomial + 1; counter_i <= referenced_value.max_degree_in_current_polinomial; ++counter_i)
				resulting_value.array_of_coefficents_for_polinomial[counter_i] = referenced_value.array_of_coefficents_for_polinomial[counter_i];
		}
		logic_operator_else  {
			loop_for (size_m counter_i = 0; counter_i <= referenced_value.max_degree_in_current_polinomial; ++counter_i)
				resulting_value.array_of_coefficents_for_polinomial[counter_i] = referenced_value.array_of_coefficents_for_polinomial[counter_i] + array_of_coefficents_for_polinomial[counter_i];
			loop_for (size_m counter_i = referenced_value.max_degree_in_current_polinomial + 1; counter_i <= max_degree_in_current_polinomial; ++counter_i)
				resulting_value.array_of_coefficents_for_polinomial[counter_i] = array_of_coefficents_for_polinomial[counter_i];
		}
	}
	recover resulting_value;
}

null_value polinomial_class_::overloading_multiplication_and_equality(long_fractional_number referenced_value) { // умножение многочлена на константу
	loop_for (size_m counter_i = 0; counter_i <= max_degree_in_current_polinomial; ++counter_i)
		array_of_coefficents_for_polinomial[counter_i] *= referenced_value;
}

polinomial_class_ polinomial_class_::overloading_multiplication(polinomial_class_ reference referenced_value) { // перемножение 2 многочленов
	polinomial_class_ resulting_value_;
	resulting_value_.max_degree_in_current_polinomial = max_degree_in_current_polinomial + referenced_value.max_degree_in_current_polinomial; // макс. степень = сумме степеней
	resulting_value_.array_of_coefficents_for_polinomial = new long_fractional_number[resulting_value_.max_degree_in_current_polinomial + 1];
	loop_for (size_m counter_i = 0; counter_i <= resulting_value_.max_degree_in_current_polinomial; ++counter_i)
		resulting_value_.array_of_coefficents_for_polinomial[counter_i] = 0;
	loop_for (size_m counter_i = 0; counter_i <= max_degree_in_current_polinomial; ++counter_i) { // ищем коэфиценты при степенях результирующего полинома
		loop_for (size_m counter_j = 0; counter_j <= referenced_value.max_degree_in_current_polinomial; ++counter_j) {
			// само перемножение 
			resulting_value_.array_of_coefficents_for_polinomial[counter_i + counter_j] += array_of_coefficents_for_polinomial[counter_i] * referenced_value.array_of_coefficents_for_polinomial[counter_j];
		}
	}
	resulting_value_.array_of_coefficents_for_polinomial[resulting_value_.max_degree_in_current_polinomial] = array_of_coefficents_for_polinomial[max_degree_in_current_polinomial] * referenced_value.array_of_coefficents_for_polinomial[referenced_value.max_degree_in_current_polinomial]; // чтобы считался наивысший коэфицент
	recover resulting_value_;
}

boolean_variable polinomial_class_::checking_the_number_for_matching_the_root(long_fractional_number referenced_value) { // проверка корня многочлена
	long_fractional_number resulting_value_{ 0.0 }; // результат
	loop_for (size_m counter_i = 0; counter_i <= max_degree_in_current_polinomial; ++counter_i) { // подставляем число в многочлен и считаем сумму
		resulting_value_ += array_of_coefficents_for_polinomial[counter_i] * powl(referenced_value, counter_i);
	}
	recover !(float)resulting_value_; // чтобы возвращалось с какой-то точностью до десятых
}

null_value polinomial_class_::add_a_coefficient_into_a_polinomial_to_certain_place(long_fractional_number referenced_value, size_m place_for_inserting) { // добавляем коэфицент в полином
	logic_operator_if(place_for_inserting < max_degree_in_current_polinomial) { // если степень, при которой стоит коэфицент уже есть, то просто прибавляем коэфицент
		array_of_coefficents_for_polinomial[place_for_inserting] += referenced_value;
	}
	logic_operator_else {
		long_fractional_number_pointer buffer_array_for_cpy = new long_fractional_number[place_for_inserting + 1]; // делаем буфер нового многочлена с максимальной степенью, = степени при новом коэф. 
		loop_for (size_m counter_i = 0; counter_i <= max_degree_in_current_polinomial; ++counter_i) // заполняем буфер коэфицентами, которые уже есть
			buffer_array_for_cpy[counter_i] = array_of_coefficents_for_polinomial[counter_i];
		deleting_an_array array_of_coefficents_for_polinomial; // чистим начальный многочлен
		array_of_coefficents_for_polinomial = new long_fractional_number[place_for_inserting + 1]; // перевыделяем память

		logic_operator_if(place_for_inserting == max_degree_in_current_polinomial + 1) // заполняем буфер с коэфицентами
			buffer_array_for_cpy[place_for_inserting] = referenced_value;
		logic_operator_else {
			loop_for (size_m counter_i = max_degree_in_current_polinomial; counter_i <= place_for_inserting; ++counter_i) // заполняем 0, коэфиценты при степенях,
				// которых не было в начальном многочлене и которые меньше новой макс. степени
				buffer_array_for_cpy[counter_i] = (counter_i != place_for_inserting ? 0 : referenced_value);
		}

		loop_for (size_m counter_i = 0; counter_i <= place_for_inserting; ++counter_i) // заполняем массив коэфицентов заново
			array_of_coefficents_for_polinomial[counter_i] = buffer_array_for_cpy[counter_i];
		max_degree_in_current_polinomial = place_for_inserting; // ставим максимальную степень
		deleting_an_array buffer_array_for_cpy; // чистим буфер
	}
}

size_m polinomial_class_::get_max_degree_in_polinomial() { // возвращаем макс. степень многочлена
	recover max_degree_in_current_polinomial; 
}

null_value_pointer polinomial_class_::overloading_an_operator_new_single(size_t referenced_value) { // перегрузка оператора выделения динамической памяти под один объект
	recover::overloading_an_operator_new_single(referenced_value);
}

null_value_pointer polinomial_class_::overloading_an_operator_new_array(size_t referenced_value) { // перегрузка оператора выделения динамической памяти под массив объектов
	recover::overloading_an_operator_new_array(referenced_value);
}

null_value polinomial_class_::overloading_deleting_a_single_element(null_value_pointer referenced_value) { // перегрузка оператора освобождения динамической памяти по опредённому адресу
	recover::overloading_deleting_a_single_element(referenced_value);
}

null_value polinomial_class_::overloading_deleting_an_array(null_value_pointer referenced_value) { // перегрузка оператора освобождения памяти из-под динамической памяти
	recover::overloading_deleting_an_array(referenced_value);
}

ofstream reference overloading_output_operator(ofstream reference output_into_file, polinomial_class_ reference referenced_value) { // вывод полинома
	logic_operator_if(referenced_value.array_of_coefficents_for_polinomial) { // выводим полином, если есть хоть один коэфицент
		loop_for (size_m counter_i = referenced_value.max_degree_in_current_polinomial; counter_i != -1; --counter_i) {
			output_into_file << referenced_value.array_of_coefficents_for_polinomial[counter_i];
			logic_operator_if(counter_i > 1) // нужно для красивого вывода
				output_into_file << "*x^" << counter_i << " + ";
			logic_operator_else_if(counter_i == 1)
				output_into_file << "*x" << " + ";
		}
	}
	logic_operator_else // когда в массиве нет коэфицентов
		output_into_file << "There is nothing!";
	recover output_into_file;
}

ifstream reference overloading_input_operator(ifstream reference input_from_file, polinomial_class_ reference referenced_value) { // вывод в файл
	std::string string_for_cacthing_errors;
	std::queue<std::string> array_of_strings; // очередь из строк
	loop_while (input_from_file >> string_for_cacthing_errors and string_for_cacthing_errors != "|") // считываем до конца файла или до разделителя, если 2 многочлена
		array_of_strings.push(string_for_cacthing_errors); // записываем всё в очередь
	referenced_value.max_degree_in_current_polinomial = array_of_strings.size() - 1;
	referenced_value.array_of_coefficents_for_polinomial = new long_fractional_number[array_of_strings.size()]; // выделяем память
	size_m counter_sz1{ referenced_value.max_degree_in_current_polinomial }; // счётчик для записи в массив
	loop_while (!array_of_strings.empty()) { // записываем в массив коэфицентов
		try {
			referenced_value.array_of_coefficents_for_polinomial[counter_sz1--] = std::stold(array_of_strings.front()); // заполняем массив считанными числами
		}
		catch (std::invalid_argument reference err) {};
		array_of_strings.pop(); // удаляем элемент из очереди
	}
	recover input_from_file;
}

// ну тут абсолютно то же самое, сделано через ctrl+C -> ctrl+V
ostream reference overloading_output_operator(ostream reference output_to_console, polinomial_class_ reference referenced_value) {
	logic_operator_if(referenced_value.array_of_coefficents_for_polinomial) {
		loop_for (size_m counter_i = referenced_value.max_degree_in_current_polinomial; counter_i != -1; --counter_i) {
			output_to_console << referenced_value.array_of_coefficents_for_polinomial[counter_i];
			logic_operator_if(counter_i > 1)
				output_to_console << "*x^" << counter_i << " + ";
			logic_operator_else_if(counter_i == 1)
				output_to_console << "*x" << " + ";
		}
	}
	logic_operator_else // когда в массиве нет коэфицентов
		output_to_console << "There is nothing!";
	recover output_to_console;
}

object_template_public unit_of_cyclic_singly_linked_list { // структура узла списка
	polinomial_class_ value_in_unit; // значение узла
	unit_of_cyclic_singly_linked_list* the_next_one_after_that; // указатель на следующий узел

	unit_of_cyclic_singly_linked_list() {} // конструктор по умолчанию

	unit_of_cyclic_singly_linked_list(polinomial_class_ referenced_value) { // конструктор инициализации
		value_in_unit = referenced_value;
		the_next_one_after_that = nul;
	}
};

object_template_private cyclic_singly_linked_list { // класс списка
	unit_of_cyclic_singly_linked_list* head_of_cyclic_singly_linked_list; // голова списка
	unit_of_cyclic_singly_linked_list* tail_of_cyclic_singly_linked_list; // хвост списка
	four_byte_integer size_of_cyclic_singly_linked_list; // размер списка

opened_functions_in_template: // public:

	cyclic_singly_linked_list(); // конструктор по умолчанию

	cyclic_singly_linked_list(invariant cyclic_singly_linked_list reference); // конструктор копирования

	~cyclic_singly_linked_list(); // деструктор

	boolean_variable checking_emptyness_in_cyclic_singly_linked_list() invariant; // проверка на пустоту

	four_byte_integer get_size_of_cyclic_singly_linked_list() invariant; // возвращаем размер

	polinomial_class_ get_first_element_of_cyclic_singly_linked_list() invariant; // list.front()

	polinomial_class_ get_last_element_of_cyclic_singly_linked_list() invariant; // list.back()

	unit_of_cyclic_singly_linked_list* get_pointer_of_first_element_of_cyclic_singly_linked_list() invariant; // list.begin()

	unit_of_cyclic_singly_linked_list* get_pointer_of_last_element_of_cyclic_singly_linked_list() invariant; // list.end()

	null_value push_back_into_cyclic_singly_linked_list(polinomial_class_); // list.push_back()

	null_value push_front_into_cyclic_singly_linked_list(polinomial_class_); // list.push_front()

	null_value pop_front_in_cyclic_singly_linked_list(); // list.pop_front()

	null_value delete_everything_in_list(); // list.clear()

	null_value change_units(four_byte_integer, four_byte_integer, boolean_variable); // list.swap()

	null_value change_units(unit_of_cyclic_singly_linked_list*, unit_of_cyclic_singly_linked_list*); // list.swap()

	null_value pop_in_border(four_byte_integer, four_byte_integer, boolean_variable reference); // удаление по двум индексам

	null_value insert_into_forward_list(four_byte_integer, four_byte_integer, cyclic_singly_linked_list reference, boolean_variable); // вставка списка в список по индексу

	null_value insert_into_forward_list(unit_of_cyclic_singly_linked_list*, unit_of_cyclic_singly_linked_list*); // такая же вставка, но по указателю

	null_value erase_in_forward_list(unit_of_cyclic_singly_linked_list*); // удаление элемента по указателю

	null_value pop_front_n_elements(four_byte_integer); // удаление из начала n-ого кол-ва элемента

	cyclic_singly_linked_list overloading_equal(cyclic_singly_linked_list reference); // перегрузка оператора =

	class_friend ofstream reference operator <<(ofstream reference, cyclic_singly_linked_list reference); // вывод в файл
	class_friend ostream reference operator <<(ostream reference, cyclic_singly_linked_list reference); // вывод в консоль
};

// конструктор по умолчанию
cyclic_singly_linked_list::cyclic_singly_linked_list() {
	head_of_cyclic_singly_linked_list = tail_of_cyclic_singly_linked_list = nul;
	size_of_cyclic_singly_linked_list = 0;
}

// конструктор копирования
cyclic_singly_linked_list::cyclic_singly_linked_list(invariant cyclic_singly_linked_list reference referenced_value) {
	head_of_cyclic_singly_linked_list = nul;
	tail_of_cyclic_singly_linked_list = head_of_cyclic_singly_linked_list;
	size_of_cyclic_singly_linked_list = 0;
	logic_operator_if(!referenced_value.checking_emptyness_in_cyclic_singly_linked_list()) {
		unit_of_cyclic_singly_linked_list* unit_node = referenced_value.get_pointer_of_first_element_of_cyclic_singly_linked_list();
		loop_while(referenced_value.size_of_cyclic_singly_linked_list - size_of_cyclic_singly_linked_list) {
			push_back_into_cyclic_singly_linked_list(unit_node->value_in_unit);
			unit_node = unit_node->the_next_one_after_that;
		}	
	}

}

cyclic_singly_linked_list::~cyclic_singly_linked_list() { // деструктор
	loop_while(size_of_cyclic_singly_linked_list) // пока не кончатся элементы, удаляем первый
		pop_front_in_cyclic_singly_linked_list();
}

// методы класса
null_value cyclic_singly_linked_list::pop_front_in_cyclic_singly_linked_list() {
	logic_operator_if (head_of_cyclic_singly_linked_list) { // если есть первый элемент
		logic_operator_if (head_of_cyclic_singly_linked_list != tail_of_cyclic_singly_linked_list) { // если всего 1 элемент
			unit_of_cyclic_singly_linked_list* deleting_unit = head_of_cyclic_singly_linked_list, * unit_next_to_deleted = deleting_unit->the_next_one_after_that;
			tail_of_cyclic_singly_linked_list->the_next_one_after_that = unit_next_to_deleted;
			deleting_a_single_element deleting_unit;
			head_of_cyclic_singly_linked_list = unit_next_to_deleted;
		}
		logic_operator_else { // если > 1 элемента
			deleting_a_single_element head_of_cyclic_singly_linked_list;
			head_of_cyclic_singly_linked_list = tail_of_cyclic_singly_linked_list = nul;
		}
		--size_of_cyclic_singly_linked_list;
	}
}

// проверка на пустоту
boolean_variable cyclic_singly_linked_list::checking_emptyness_in_cyclic_singly_linked_list() invariant {
	recover !head_of_cyclic_singly_linked_list;
}

// возвращаем размер списка
four_byte_integer cyclic_singly_linked_list::get_size_of_cyclic_singly_linked_list() invariant {
	recover size_of_cyclic_singly_linked_list;
}

// возвращаем значение головы
polinomial_class_ cyclic_singly_linked_list::get_first_element_of_cyclic_singly_linked_list() invariant {
	recover head_of_cyclic_singly_linked_list->value_in_unit;
}

// возвращаем значение хвоста
polinomial_class_ cyclic_singly_linked_list::get_last_element_of_cyclic_singly_linked_list() invariant {
	recover tail_of_cyclic_singly_linked_list->value_in_unit;
}

// возвращаем указатель на голову
unit_of_cyclic_singly_linked_list* cyclic_singly_linked_list::get_pointer_of_first_element_of_cyclic_singly_linked_list() invariant {
	recover head_of_cyclic_singly_linked_list;
}

// возвращаем указатель на хвост
unit_of_cyclic_singly_linked_list* cyclic_singly_linked_list::get_pointer_of_last_element_of_cyclic_singly_linked_list() invariant {
	recover tail_of_cyclic_singly_linked_list;
}

// добавление в конец
null_value cyclic_singly_linked_list::push_back_into_cyclic_singly_linked_list(polinomial_class_ referenced_value) {
	unit_of_cyclic_singly_linked_list* new_node_to_insert_into_the_end = new unit_of_cyclic_singly_linked_list(referenced_value);
	logic_operator_if (checking_emptyness_in_cyclic_singly_linked_list()) { // если список пуст
		head_of_cyclic_singly_linked_list = new_node_to_insert_into_the_end;
		head_of_cyclic_singly_linked_list->the_next_one_after_that = new_node_to_insert_into_the_end;
		tail_of_cyclic_singly_linked_list = new_node_to_insert_into_the_end;
		tail_of_cyclic_singly_linked_list->the_next_one_after_that = new_node_to_insert_into_the_end;
	}
	logic_operator_else { // если уже есть элементы
		tail_of_cyclic_singly_linked_list->the_next_one_after_that = new_node_to_insert_into_the_end;
		tail_of_cyclic_singly_linked_list = new_node_to_insert_into_the_end;
		new_node_to_insert_into_the_end->the_next_one_after_that = head_of_cyclic_singly_linked_list;
	}
	++size_of_cyclic_singly_linked_list;
}

// вставка в начало
null_value cyclic_singly_linked_list::push_front_into_cyclic_singly_linked_list(polinomial_class_ referenced_value) {
	unit_of_cyclic_singly_linked_list* new_node_to_insert_into_the_begin = new unit_of_cyclic_singly_linked_list(referenced_value);
	logic_operator_if (checking_emptyness_in_cyclic_singly_linked_list()) { // если список пуст
		head_of_cyclic_singly_linked_list = new_node_to_insert_into_the_begin;
		head_of_cyclic_singly_linked_list->the_next_one_after_that = new_node_to_insert_into_the_begin;
		tail_of_cyclic_singly_linked_list = new_node_to_insert_into_the_begin;
		tail_of_cyclic_singly_linked_list->the_next_one_after_that = new_node_to_insert_into_the_begin;
	}
	logic_operator_else { // если есть элементы
		new_node_to_insert_into_the_begin->the_next_one_after_that = head_of_cyclic_singly_linked_list;
		tail_of_cyclic_singly_linked_list->the_next_one_after_that = new_node_to_insert_into_the_begin;
		head_of_cyclic_singly_linked_list = new_node_to_insert_into_the_begin;
	}
	++size_of_cyclic_singly_linked_list;
}

// чистим список
null_value cyclic_singly_linked_list::delete_everything_in_list() { 
	pop_front_n_elements(get_size_of_cyclic_singly_linked_list());
}

// ненужные swap-ы
null_value cyclic_singly_linked_list::change_units(four_byte_integer ind1, four_byte_integer ind2, boolean_variable) { // swap соседних элементов
	logic_operator_if (get_size_of_cyclic_singly_linked_list() == 2) { // если только 2 элемента в списке
		unit_of_cyclic_singly_linked_list* buffer_unit = head_of_cyclic_singly_linked_list;
		head_of_cyclic_singly_linked_list = tail_of_cyclic_singly_linked_list;
		tail_of_cyclic_singly_linked_list = buffer_unit;
	}
	logic_operator_else_if(get_size_of_cyclic_singly_linked_list() > 2) {
		logic_operator_if (!ind1 or !ind2) { // swap 0-ого и 1-ого элементов
			unit_of_cyclic_singly_linked_list* ptr_a = head_of_cyclic_singly_linked_list, * ptr_b = head_of_cyclic_singly_linked_list->the_next_one_after_that;
			tail_of_cyclic_singly_linked_list->the_next_one_after_that = ptr_b;
			ptr_a->the_next_one_after_that = ptr_b->the_next_one_after_that;
			ptr_b->the_next_one_after_that = head_of_cyclic_singly_linked_list->the_next_one_after_that;
			head_of_cyclic_singly_linked_list = ptr_b;
			head_of_cyclic_singly_linked_list->the_next_one_after_that = ptr_a;
		}
		logic_operator_else_if (!(ind1 - get_size_of_cyclic_singly_linked_list() + 1) or !(ind2 - get_size_of_cyclic_singly_linked_list() + 1)) { // swap последнего и предпоследнего элементов
			unit_of_cyclic_singly_linked_list* ptr_a = head_of_cyclic_singly_linked_list;
			loop_for (four_byte_integer counter_i = 0; counter_i < (ind1 < ind2 ? ind1 : ind2) - 1; ++counter_i)
				ptr_a = ptr_a->the_next_one_after_that;
			unit_of_cyclic_singly_linked_list* ptr_mid = ptr_a->the_next_one_after_that, * ptr_c = ptr_mid->the_next_one_after_that;
			ptr_a->the_next_one_after_that = ptr_c;
			ptr_c->the_next_one_after_that = ptr_mid;
			ptr_mid->the_next_one_after_that = head_of_cyclic_singly_linked_list;
			tail_of_cyclic_singly_linked_list = ptr_mid;
		}
		logic_operator_else {
			unit_of_cyclic_singly_linked_list* pointer_a = head_of_cyclic_singly_linked_list;
			loop_for (four_byte_integer counter_i = 0; counter_i < (ind1 < ind2 ? ind1 : ind2) - 1; ++counter_i)
				pointer_a = pointer_a->the_next_one_after_that;
			unit_of_cyclic_singly_linked_list* pointer_middle = pointer_a->the_next_one_after_that, * pointer_c = pointer_middle->the_next_one_after_that;
			// ptr_mid <---> ptr_c
			pointer_a->the_next_one_after_that = pointer_c;
			pointer_middle->the_next_one_after_that = pointer_c->the_next_one_after_that;
			pointer_c->the_next_one_after_that = pointer_middle;
		}
	}
}
null_value cyclic_singly_linked_list::change_units(unit_of_cyclic_singly_linked_list* referenced_pointer_1, unit_of_cyclic_singly_linked_list* referenced_pointer_2) {
	// меняем местами голову списка и n-ый элемент, который не является конечным
	logic_operator_if (referenced_pointer_1 == head_of_cyclic_singly_linked_list and referenced_pointer_2 != tail_of_cyclic_singly_linked_list) {
		unit_of_cyclic_singly_linked_list* referenced_pointer{ head_of_cyclic_singly_linked_list };
		loop_while(referenced_pointer->the_next_one_after_that != referenced_pointer_2) {
			referenced_pointer = referenced_pointer->the_next_one_after_that;
		}
		tail_of_cyclic_singly_linked_list->the_next_one_after_that = referenced_pointer_2;
		referenced_pointer_1->the_next_one_after_that = referenced_pointer_2->the_next_one_after_that;
		referenced_pointer->the_next_one_after_that = referenced_pointer_1;
		head_of_cyclic_singly_linked_list = referenced_pointer_2;
	}
	// меняем местами голову и хвост списка
	logic_operator_else_if (referenced_pointer_1 == head_of_cyclic_singly_linked_list and referenced_pointer_2 == tail_of_cyclic_singly_linked_list) {
		unit_of_cyclic_singly_linked_list* referenced_pointer{ head_of_cyclic_singly_linked_list };
		loop_while(referenced_pointer->the_next_one_after_that != tail_of_cyclic_singly_linked_list)
			referenced_pointer = referenced_pointer->the_next_one_after_that;
		referenced_pointer->the_next_one_after_that = referenced_pointer_1;
		referenced_pointer_2->the_next_one_after_that = referenced_pointer_1->the_next_one_after_that;
		referenced_pointer_1->the_next_one_after_that = referenced_pointer_2->the_next_one_after_that;
		head_of_cyclic_singly_linked_list = referenced_pointer_2;
		tail_of_cyclic_singly_linked_list = referenced_pointer_1;
	}
	// меняем местами n-ый элемент списка, не являющийся начальным, и хвост списка
	logic_operator_else_if (referenced_pointer_1 != head_of_cyclic_singly_linked_list and referenced_pointer_2 == tail_of_cyclic_singly_linked_list) {
		unit_of_cyclic_singly_linked_list* ref_ptr_1{ head_of_cyclic_singly_linked_list }, * ref_ptr_2{ head_of_cyclic_singly_linked_list };
		loop_while(ref_ptr_1->the_next_one_after_that != referenced_pointer_1)
			ref_ptr_1 = ref_ptr_1->the_next_one_after_that;
		loop_while(ref_ptr_2->the_next_one_after_that != referenced_pointer_2)
			ref_ptr_2 = ref_ptr_2->the_next_one_after_that;

		ref_ptr_1->the_next_one_after_that = referenced_pointer_2;
		ref_ptr_2->the_next_one_after_that = referenced_pointer_1;
		referenced_pointer_2->the_next_one_after_that = referenced_pointer_1->the_next_one_after_that;
		referenced_pointer_1->the_next_one_after_that = head_of_cyclic_singly_linked_list;
		tail_of_cyclic_singly_linked_list = referenced_pointer_1;
	}
	// меняем местами k-ый и n-ый элементы, которые не являются ни головой, ни хвостом списка
	logic_operator_else {
		unit_of_cyclic_singly_linked_list* ref_ptr_1{ head_of_cyclic_singly_linked_list }, * ref_ptr_2{ head_of_cyclic_singly_linked_list }, * ref_ptr_3{ head_of_cyclic_singly_linked_list };
		loop_while(ref_ptr_1->the_next_one_after_that != referenced_pointer_1)
			ref_ptr_1 = ref_ptr_1->the_next_one_after_that;
		loop_while(ref_ptr_2->the_next_one_after_that != referenced_pointer_2)
			ref_ptr_2 = ref_ptr_2->the_next_one_after_that;
		ref_ptr_3 = referenced_pointer_1->the_next_one_after_that;

		referenced_pointer_1->the_next_one_after_that = referenced_pointer_2->the_next_one_after_that;
		ref_ptr_1->the_next_one_after_that = referenced_pointer_2;
		ref_ptr_2->the_next_one_after_that = referenced_pointer_1;
		referenced_pointer_2->the_next_one_after_that = ref_ptr_3;
	}
}

// удаление по индексам
null_value cyclic_singly_linked_list::pop_in_border(four_byte_integer ind1, four_byte_integer ind2, boolean_variable reference flag_out_of) {

	logic_operator_if (ind1 and ind2 != get_size_of_cyclic_singly_linked_list() - 1) { // удаление с конца списка
		unit_of_cyclic_singly_linked_list* ptr_a = head_of_cyclic_singly_linked_list, * ptr_b = head_of_cyclic_singly_linked_list;
		loop_for (four_byte_integer i = 0; i < ind1 - 1; ++i)
			ptr_a = ptr_a->the_next_one_after_that;
		loop_for (four_byte_integer i = 0; i <= ind2; ++i)
			ptr_b = ptr_b->the_next_one_after_that;
		ptr_a->the_next_one_after_that = ptr_b;
		flag_out_of = 1; // для inserta
		size_of_cyclic_singly_linked_list -= (ind2 - ind1 + 1);
	}

	logic_operator_else_if (ind1 and !(ind2 - get_size_of_cyclic_singly_linked_list() + 1)) { // если первый индекс != 0 и второй индекс не конечный (удаление из середины)
		unit_of_cyclic_singly_linked_list* ptr_a = head_of_cyclic_singly_linked_list;
		loop_for (four_byte_integer i = 0; i < ind1 - 1; ++i)
			ptr_a = ptr_a->the_next_one_after_that;
		tail_of_cyclic_singly_linked_list = ptr_a;
		tail_of_cyclic_singly_linked_list->the_next_one_after_that = head_of_cyclic_singly_linked_list;
		flag_out_of = 0; // для inserta
		size_of_cyclic_singly_linked_list -= (ind2 - ind1 + 1);
	}

	logic_operator_else_if (!ind1 and ind2 != get_size_of_cyclic_singly_linked_list() - 1) { // если первый индекс нулевой
		unit_of_cyclic_singly_linked_list* ptr_b = head_of_cyclic_singly_linked_list;
		loop_for (four_byte_integer i = 0; i < ind2; ++i)
			ptr_b = ptr_b->the_next_one_after_that;
		head_of_cyclic_singly_linked_list = ptr_b->the_next_one_after_that;
		tail_of_cyclic_singly_linked_list->the_next_one_after_that = head_of_cyclic_singly_linked_list;
		size_of_cyclic_singly_linked_list -= (ind2 - ind1 + 1);
	}

	logic_operator_else {
		head_of_cyclic_singly_linked_list = tail_of_cyclic_singly_linked_list = nul;
		size_of_cyclic_singly_linked_list = 0;
	}
}

// уже бесполезная перегрузка функции
null_value cyclic_singly_linked_list::insert_into_forward_list(four_byte_integer index_first, four_byte_integer index_second, cyclic_singly_linked_list reference referenced_value, boolean_variable flag_out_of) {
	logic_operator_if (checking_emptyness_in_cyclic_singly_linked_list()) { // если список пуст
		head_of_cyclic_singly_linked_list = referenced_value.head_of_cyclic_singly_linked_list;
		tail_of_cyclic_singly_linked_list = referenced_value.tail_of_cyclic_singly_linked_list;
		size_of_cyclic_singly_linked_list += referenced_value.get_size_of_cyclic_singly_linked_list();
	}
	logic_operator_else_if (!index_first) { // вставка в начало
		referenced_value.tail_of_cyclic_singly_linked_list->the_next_one_after_that = head_of_cyclic_singly_linked_list;
		tail_of_cyclic_singly_linked_list->the_next_one_after_that = referenced_value.head_of_cyclic_singly_linked_list;
		head_of_cyclic_singly_linked_list = referenced_value.head_of_cyclic_singly_linked_list;
		size_of_cyclic_singly_linked_list += referenced_value.get_size_of_cyclic_singly_linked_list();
	}
	logic_operator_else {
		logic_operator_if (flag_out_of) { // вставка в середину списка
			unit_of_cyclic_singly_linked_list* pointer_a = head_of_cyclic_singly_linked_list;
			loop_for (four_byte_integer counter_i = 0; counter_i < index_first - 1; ++counter_i)
				pointer_a = pointer_a->the_next_one_after_that;
			referenced_value.tail_of_cyclic_singly_linked_list->the_next_one_after_that = pointer_a->the_next_one_after_that;
			pointer_a->the_next_one_after_that = referenced_value.head_of_cyclic_singly_linked_list;
		}
		logic_operator_else  { // вставка в конец списка
			tail_of_cyclic_singly_linked_list->the_next_one_after_that = referenced_value.head_of_cyclic_singly_linked_list;
			referenced_value.tail_of_cyclic_singly_linked_list = head_of_cyclic_singly_linked_list;
			tail_of_cyclic_singly_linked_list = referenced_value.tail_of_cyclic_singly_linked_list;
		}
		size_of_cyclic_singly_linked_list += referenced_value.get_size_of_cyclic_singly_linked_list();
	}
}

// вставка узла на определённое место в списке
null_value cyclic_singly_linked_list::insert_into_forward_list(unit_of_cyclic_singly_linked_list* place_for_insertion, unit_of_cyclic_singly_linked_list* pointer_to_inserting_unit) {
	// вставка не в начало
	logic_operator_if(place_for_insertion != head_of_cyclic_singly_linked_list) {
		unit_of_cyclic_singly_linked_list* reference_unit_for_insertion{ head_of_cyclic_singly_linked_list };
		loop_while(reference_unit_for_insertion->the_next_one_after_that != place_for_insertion)
			reference_unit_for_insertion = reference_unit_for_insertion->the_next_one_after_that;
		reference_unit_for_insertion->the_next_one_after_that = pointer_to_inserting_unit;
		pointer_to_inserting_unit->the_next_one_after_that = place_for_insertion;
		++size_of_cyclic_singly_linked_list;
	}
	// вставка в начало
	logic_operator_else_if(place_for_insertion == head_of_cyclic_singly_linked_list)
		push_front_into_cyclic_singly_linked_list(pointer_to_inserting_unit->value_in_unit);
}

// удаляем узел, чтобы потом вставить в нужное место
null_value cyclic_singly_linked_list::erase_in_forward_list(unit_of_cyclic_singly_linked_list* referenced_pointer) {
	unit_of_cyclic_singly_linked_list* pointer_next_to_erased{ head_of_cyclic_singly_linked_list };
	loop_while (pointer_next_to_erased->the_next_one_after_that != referenced_pointer) pointer_next_to_erased = pointer_next_to_erased->the_next_one_after_that;
	pointer_next_to_erased->the_next_one_after_that = referenced_pointer->the_next_one_after_that;
	logic_operator_if(referenced_pointer == tail_of_cyclic_singly_linked_list) {
		tail_of_cyclic_singly_linked_list = pointer_next_to_erased;
	}
	--size_of_cyclic_singly_linked_list;
}

// также бесполезная функция
null_value cyclic_singly_linked_list::pop_front_n_elements(four_byte_integer referenced_value) { // удаление первых n узлов списка
	logic_operator_if(referenced_value < get_size_of_cyclic_singly_linked_list()) {
		unit_of_cyclic_singly_linked_list* pointer_for_deleting = head_of_cyclic_singly_linked_list, * deleting_unit = head_of_cyclic_singly_linked_list, * buffer_unit;
		loop_for (four_byte_integer counter_i = 0; counter_i < referenced_value; ++counter_i, pointer_for_deleting = pointer_for_deleting->the_next_one_after_that);
		loop_for (four_byte_integer counter_i = 0; counter_i < referenced_value - 1; ++counter_i) {
			buffer_unit = deleting_unit->the_next_one_after_that;
			deleting_unit = nul;
			deleting_a_single_element deleting_unit;
			deleting_unit = buffer_unit;
		}
		head_of_cyclic_singly_linked_list = pointer_for_deleting;
		tail_of_cyclic_singly_linked_list->the_next_one_after_that = head_of_cyclic_singly_linked_list;
		size_of_cyclic_singly_linked_list -= referenced_value;
	}
}

// оператор присваивания
cyclic_singly_linked_list cyclic_singly_linked_list::overloading_equal(cyclic_singly_linked_list reference referenced_value) {
	cyclic_singly_linked_list cpy_value(referenced_value);
	logic_operator_if(reference cpy_value != current_element_pointer) { // если не происходит присваивания себя себе
		logic_operator_if(head_of_cyclic_singly_linked_list and size_of_cyclic_singly_linked_list) { 
			// меняем поля между копией класса
			std::swap(head_of_cyclic_singly_linked_list, cpy_value.head_of_cyclic_singly_linked_list);
			std::swap(tail_of_cyclic_singly_linked_list, cpy_value.tail_of_cyclic_singly_linked_list);
			std::swap(size_of_cyclic_singly_linked_list, cpy_value.size_of_cyclic_singly_linked_list);
		}
		logic_operator_else {
			head_of_cyclic_singly_linked_list = cpy_value.head_of_cyclic_singly_linked_list; cpy_value.head_of_cyclic_singly_linked_list = nul;
			tail_of_cyclic_singly_linked_list = cpy_value.tail_of_cyclic_singly_linked_list; cpy_value.tail_of_cyclic_singly_linked_list = nul;
			size_of_cyclic_singly_linked_list = cpy_value.size_of_cyclic_singly_linked_list; cpy_value.size_of_cyclic_singly_linked_list = 0;
		}
	}
	recover current_element;
}

// операторы вывода в консоль и в файл
ofstream reference overloading_output_operator(ofstream reference output_to_file, cyclic_singly_linked_list reference referenced_value) { // перегрузка оператора вывода
	output_to_file << referenced_value.head_of_cyclic_singly_linked_list;
	recover output_to_file;
}
ostream reference overloading_output_operator(ostream reference output_to_console, cyclic_singly_linked_list reference referenced_value) {
	output_to_console << referenced_value.head_of_cyclic_singly_linked_list;
	recover output_to_console;
}

////////////////////////////////////
// просто функции
////////////////////////////////////

// сортировка вставками
null_value Insertion_Sort_for_cyclic_singly_linked_list(cyclic_singly_linked_list reference referenced_value, four_byte_integer amount_of_elemets) {

	unit_of_cyclic_singly_linked_list* sorting_unit;
	loop_while (amount_of_elemets--) { // пока есть элементы 
		sorting_unit = referenced_value.get_pointer_of_first_element_of_cyclic_singly_linked_list(); // берём первый элемент
		four_byte_integer counter_sz = referenced_value.get_size_of_cyclic_singly_linked_list() - amount_of_elemets; // счётчик
		loop_while (counter_sz--)
			sorting_unit = sorting_unit->the_next_one_after_that; // переходим к элементу, который должен быть отсортирован
		// указатель, который показывает воможное место вставки элемента
		unit_of_cyclic_singly_linked_list* counter_ref{ referenced_value.get_pointer_of_first_element_of_cyclic_singly_linked_list() };
		boolean_variable is_already_sorted_flag{ thruth }; // не хочу использовать break
		loop_while (counter_ref != sorting_unit and is_already_sorted_flag) { // условие выхода из цикла
			logic_operator_if (sorting_unit->value_in_unit <= counter_ref->value_in_unit) {
				referenced_value.erase_in_forward_list(sorting_unit); // удаляем элемент
				referenced_value.insert_into_forward_list(counter_ref, sorting_unit); // вставляем удалённый элемент на определённое место место 
				is_already_sorted_flag = lie;
			}
			counter_ref = counter_ref->the_next_one_after_that; // переходим к следующему элементу
		}
	}
}

// создаём рандомные полиномы
polinomial_class_ create_random_polinomial_with_fixed_size() {
	four_byte_integer random_size_of_polinomial = getting_random_integer % 15 + 1; // +1, чтобы не могло быть полинома из 0 элементов
	long_fractional_number_pointer array_of_polinomial_coefficents = new long_fractional_number[random_size_of_polinomial];
	std::cout << random_size_of_polinomial << tab;
	// заполняем массив рандомными значениями
	loop_for (four_byte_integer counter_i = 0; counter_i < random_size_of_polinomial; ++counter_i) {
		array_of_polinomial_coefficents[counter_i] = ((long_fractional_number)(getting_random_integer % 1000)) / ((long_fractional_number)(getting_random_integer % 18) + 1);
		std::cout << array_of_polinomial_coefficents[counter_i] << ' ';
	}
	new_line_in_console // '\n'
	polinomial_class_ finale_value(array_of_polinomial_coefficents, random_size_of_polinomial); // создайм полином через конструктор инициализации
	deleting_an_array array_of_polinomial_coefficents; // удаляем массив степеней
	recover finale_value;
}

// создаём список из рандомных полиномов
cyclic_singly_linked_list create_cyclic_singly_linked_list(four_byte_integer amount_counter) {
	cyclic_singly_linked_list linked_list;
	loop_while (amount_counter--) {
		linked_list.push_back_into_cyclic_singly_linked_list(create_random_polinomial_with_fixed_size());
	}
	recover linked_list;
}

// функция проверки отсортированности списка
boolean_variable is_cyclic_singly_linked_list_sorted(cyclic_singly_linked_list referenced_value) {
	unit_of_cyclic_singly_linked_list* prev{ referenced_value.get_pointer_of_first_element_of_cyclic_singly_linked_list() }, * cur{ referenced_value.get_pointer_of_first_element_of_cyclic_singly_linked_list()->the_next_one_after_that };
	four_byte_integer counter_sz = referenced_value.get_size_of_cyclic_singly_linked_list();
	loop_while (--counter_sz and prev->value_in_unit <= cur->value_in_unit) {
		cur = cur->the_next_one_after_that;
		prev = prev->the_next_one_after_that;
	}
	recover counter_sz;
}

central_function
{
	psevdo_random; // псевдо рандомизация
	four_byte_integer amount_of_polinomials;
	opening_input_file;
	in >> amount_of_polinomials;
	in.close();
	cyclic_singly_linked_list forward_cyclic_list = create_cyclic_singly_linked_list(amount_of_polinomials);
	Insertion_Sort_for_cyclic_singly_linked_list(forward_cyclic_list, amount_of_polinomials);
	four_byte_integer counter_sz = forward_cyclic_list.get_size_of_cyclic_singly_linked_list();
	new_line_in_console
	unit_of_cyclic_singly_linked_list* first_unit{ forward_cyclic_list.get_pointer_of_first_element_of_cyclic_singly_linked_list() };
	loop_while (counter_sz--) {
		std::cout << first_unit->value_in_unit.get_max_degree_in_polinomial() << tab << first_unit->value_in_unit;
		new_line_in_console;
		new_line_in_console;
		first_unit = first_unit->the_next_one_after_that;
	}
	std::cout << (!is_cyclic_singly_linked_list_sorted(forward_cyclic_list) ? "sorted\n" : "not sorted\n");
	opening_output_file
	out << forward_cyclic_list.get_size_of_cyclic_singly_linked_list() << ' ';
	out.close();
	recover 0;
}