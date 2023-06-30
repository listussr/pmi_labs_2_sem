//#define _CRT_SECURE_NO_WARNINGS
//#include<fstream>
//#include<vector>
//#include<cstring>
//
///*
//типы терминальных символов
//
//1 - if - if
//2 - then - th
//3 - else - el
//4 - end - en
//5 - < | > | <= | >= | <> - co
//6 - = - eq
//7 - id - id
//8 - const - vl
//9 - + | * | / - ao
//10 - wrong lex - wl
//11 - # - sharp // для обозначения конца вектора лексем
//12 - - - minus - для знака минуса
//*/
//
//enum State // состояния автомата
//{
//	Start_lex, Id_1, Id_2, Id_3, Id_4, Id_5, Minus, Plus,
//	More, Fewer, More_or_Equal, Fewer_or_Equal, Equal, UnEqual,
//	Digit_1, Digit_2, Digit_3, Digit_4, Four_digit_number_1,
//	Four_digit_number_2, Four_digit_number_3, Four_digit_number_4,
//	ERROR_lex, Final, Last_digit
//};
//
//// входные данные
//enum signals { alpha, min, more, fewer, plus, equal, border, one_two, three, four_six, seven, eight, nine, zero, other };
//
//// тип лексемы
//enum lex_type { _if, th, el, en, id, vl, co, ao, minus, eq, wl, sharp };
//
///*
//	kw - ключевое слово
//	id - идентификатор
//	vl - константа
//	wl - неверная лексема
//	ao - спецсимволы (+ -)
//	co - сравнение (compare)
//	{
//		<;
//		<=;
//		<>; ( != )
//	}
//	eq - равно
//*/
//using std::ofstream;
//using std::ifstream;
//using std::vector;
//
//struct Lex // структура лексемы
//{
//	char* mass;
//	lex_type type;
//};
//
//enum aaaaaa {
//	if_, el_, en_, th_, ar_oper, sharp_, cond
//};
//
//enum syntax_state {
//	S_, S1, S2, S3, S4, S5, S6, F_, ERROR_
//};
//
///*
//операнд - идентификатор | значение
//арифметическая операция - + | - 
//логическое выражение - операнд | операнд + операция + операнд
//арифметическое выражение - операнд | операнд + арифметическая операция + операнд
//*/
//
//
//void Syntax_analys() {
//
//}
//
//void collapsing_lexem(vector<Lex>& first, vector<aaaaaa>& second) {
//	for (int i = 0; i < first.size(); ++i) {
//		aaaaaa type;
//
//	}
//}
//
//signals get_signal(const char ch) { // обработка входных данных
//	if (ch == '0') return zero;
//	else if ((ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90)) return alpha;
//	else if (ch == '>') return more;
//	else if (ch == '<') return fewer;
//	else if (ch == '=') return equal;
//	else if (ch == '-') return min;
//	else if (ch == '+') return plus;
//	else if (ch == '\t' || ch == ' ' || ch == '\n' || ch == '\0') return border;
//	else if (ch == '1' || ch == '2') return one_two;
//	else if (ch == '3') return three;
//	else if (ch >= 52 && ch <= 54) return four_six;
//	else if (ch == '7') return seven;
//	else if (ch == '8') return eight;
//	else if (ch == '9') return nine;
//	return other;
//}
//
//void filling_automat_table(State(&table)[15][25]) { // заполнение автомата
//	// для Start
//	table[signals::alpha][Start_lex] = State::Id_1;
//	table[signals::equal][Start_lex] = State::Equal;
//	table[signals::min][Start_lex] = State::Minus;
//	table[signals::plus][Start_lex] = State::Plus;
//	table[signals::more][Start_lex] = State::More;
//	table[signals::fewer][Start_lex] = State::Fewer;
//	table[signals::one_two][Start_lex] = State::Digit_1;
//	table[signals::three][Start_lex] = State::Digit_1;
//	table[signals::four_six][Start_lex] = State::Four_digit_number_1;
//	table[signals::seven][Start_lex] = State::Four_digit_number_1;
//	table[signals::eight][Start_lex] = State::Four_digit_number_1;
//	table[signals::nine][Start_lex] = State::Four_digit_number_1;
//	table[signals::border][Start_lex] = State::Start_lex;
//	table[signals::other][Start_lex] = State::ERROR_lex;
//
//	// для Id_1
//	table[signals::alpha][Id_1] = State::Id_2;
//	table[signals::equal][Id_1] = State::Final;
//	table[signals::min][Id_1] = State::Final;
//	table[signals::plus][Id_1] = State::Final;
//	table[signals::more][Id_1] = State::Final;
//	table[signals::fewer][Id_1] = State::Final;
//	table[signals::one_two][Id_1] = State::Id_2;
//	table[signals::three][Id_1] = State::Id_2;
//	table[signals::four_six][Id_1] = State::Id_2;
//	table[signals::seven][Id_1] = State::Id_2;
//	table[signals::eight][Id_1] = State::Id_2;
//	table[signals::nine][Id_1] = State::Id_2;
//	table[signals::border][Id_1] = State::Final;
//	table[signals::other][Id_1] = State::ERROR_lex;
//
//	// для Id_2
//	table[signals::alpha][Id_2] = State::Id_3;
//	table[signals::equal][Id_2] = State::Final;
//	table[signals::min][Id_2] = State::Final;
//	table[signals::plus][Id_2] = State::Final;
//	table[signals::more][Id_2] = State::Final;
//	table[signals::fewer][Id_2] = State::Final;
//	table[signals::one_two][Id_2] = State::Id_3;
//	table[signals::three][Id_2] = State::Id_3;
//	table[signals::four_six][Id_2] = State::Id_3;
//	table[signals::seven][Id_2] = State::Id_3;
//	table[signals::eight][Id_2] = State::Id_3;
//	table[signals::nine][Id_2] = State::Id_3;
//	table[signals::border][Id_2] = State::Final;
//	table[signals::other][Id_2] = State::ERROR_lex;
//
//	// для Id_3
//	table[signals::alpha][Id_3] = State::Id_4;
//	table[signals::equal][Id_3] = State::Final;
//	table[signals::min][Id_3] = State::Final;
//	table[signals::plus][Id_3] = State::Final;
//	table[signals::more][Id_3] = State::Final;
//	table[signals::fewer][Id_3] = State::Final;
//	table[signals::one_two][Id_3] = State::Id_4;
//	table[signals::three][Id_3] = State::Id_4;
//	table[signals::four_six][Id_3] = State::Id_4;
//	table[signals::seven][Id_3] = State::Id_4;
//	table[signals::eight][Id_3] = State::Id_4;
//	table[signals::nine][Id_3] = State::Id_4;
//	table[signals::border][Id_3] = State::Final;
//	table[signals::other][Id_3] = State::ERROR_lex;
//
//	// для Id_4
//	table[signals::alpha][Id_4] = State::Id_5;
//	table[signals::equal][Id_4] = State::Final;
//	table[signals::min][Id_4] = State::Final;
//	table[signals::plus][Id_4] = State::Final;
//	table[signals::more][Id_4] = State::Final;
//	table[signals::fewer][Id_4] = State::Final;
//	table[signals::one_two][Id_4] = State::Id_5;
//	table[signals::three][Id_4] = State::Id_5;
//	table[signals::four_six][Id_4] = State::Id_5;
//	table[signals::seven][Id_4] = State::Id_5;
//	table[signals::eight][Id_4] = State::Id_5;
//	table[signals::nine][Id_4] = State::Id_5;
//	table[signals::border][Id_4] = State::Final;
//	table[signals::other][Id_4] = State::ERROR_lex;
//
//	// для Id_5
//	table[signals::alpha][Id_5] = State::ERROR_lex;
//	table[signals::equal][Id_5] = State::Final;
//	table[signals::min][Id_5] = State::Final;
//	table[signals::plus][Id_5] = State::Final;
//	table[signals::more][Id_5] = State::Final;
//	table[signals::fewer][Id_5] = State::Final;
//	table[signals::one_two][Id_5] = State::ERROR_lex;
//	table[signals::three][Id_5] = State::ERROR_lex;
//	table[signals::four_six][Id_5] = State::ERROR_lex;
//	table[signals::seven][Id_5] = State::ERROR_lex;
//	table[signals::eight][Id_5] = State::ERROR_lex;
//	table[signals::nine][Id_5] = State::ERROR_lex;
//	table[signals::border][Id_5] = Final;
//	table[signals::other][Id_5] = State::ERROR_lex;
//
//	// для Minus
//	table[signals::alpha][Minus] = State::Final;
//	table[signals::equal][Minus] = State::Final;
//	table[signals::min][Minus] = State::Final;
//	table[signals::plus][Minus] = State::Final;
//	table[signals::more][Minus] = State::Final;
//	table[signals::fewer][Minus] = State::Final;
//	table[signals::one_two][Minus] = State::Final;
//	table[signals::three][Minus] = State::Final;
//	table[signals::four_six][Minus] = State::Final;
//	table[signals::seven][Minus] = State::Final;
//	table[signals::eight][Minus] = State::Final;
//	table[signals::nine][Minus] = State::Final;
//	table[signals::border][Minus] = State::Final;
//	table[signals::other][Minus] = State::ERROR_lex;
//
//	// для Plus
//	table[signals::alpha][Plus] = State::Final;
//	table[signals::equal][Plus] = State::Final;
//	table[signals::min][Plus] = State::Final;
//	table[signals::plus][Plus] = State::Final;
//	table[signals::more][Plus] = State::Final;
//	table[signals::fewer][Plus] = State::Final;
//	table[signals::one_two][Plus] = State::Final;
//	table[signals::three][Plus] = State::Final;
//	table[signals::four_six][Plus] = State::Final;
//	table[signals::seven][Plus] = State::Final;
//	table[signals::eight][Plus] = State::Final;
//	table[signals::nine][Plus] = State::Final;
//	table[signals::border][Plus] = State::Final;
//	table[signals::other][Plus] = State::ERROR_lex;
//
//	// для More
//	table[signals::alpha][More] = State::Final;
//	table[signals::equal][More] = State::More_or_Equal;
//	table[signals::min][More] = State::Final;
//	table[signals::plus][More] = State::Final;
//	table[signals::more][More] = State::Final;
//	table[signals::fewer][More] = State::Final;
//	table[signals::one_two][More] = State::Final;
//	table[signals::three][More] = State::Final;
//	table[signals::four_six][More] = State::Final;
//	table[signals::seven][More] = State::Final;
//	table[signals::eight][More] = State::Final;
//	table[signals::nine][More] = State::Final;
//	table[signals::border][More] = State::Final;
//	table[signals::other][More] = State::ERROR_lex;
//
//	// для More_or_Equal
//	table[signals::alpha][More_or_Equal] = State::Final;
//	table[signals::equal][More_or_Equal] = State::Final;
//	table[signals::min][More_or_Equal] = State::Final;
//	table[signals::plus][More_or_Equal] = State::Final;
//	table[signals::more][More_or_Equal] = State::Final;
//	table[signals::fewer][More_or_Equal] = State::Final;
//	table[signals::one_two][More_or_Equal] = State::Final;
//	table[signals::three][More_or_Equal] = State::Final;
//	table[signals::four_six][More_or_Equal] = State::Final;
//	table[signals::seven][More_or_Equal] = State::Final;
//	table[signals::eight][More_or_Equal] = State::Final;
//	table[signals::nine][More_or_Equal] = State::Final;
//	table[signals::border][More_or_Equal] = State::Final;
//	table[signals::other][More_or_Equal] = State::ERROR_lex;
//
//	// для Fewer
//	table[signals::alpha][Fewer] = State::Final;
//	table[signals::equal][Fewer] = State::Fewer_or_Equal;
//	table[signals::min][Fewer] = State::Final;
//	table[signals::plus][Fewer] = State::Final;
//	table[signals::more][Fewer] = State::UnEqual;
//	table[signals::fewer][Fewer] = State::Final;
//	table[signals::one_two][Fewer] = State::Final;
//	table[signals::three][Fewer] = State::Final;
//	table[signals::four_six][Fewer] = State::Final;
//	table[signals::seven][Fewer] = State::Final;
//	table[signals::eight][Fewer] = State::Final;
//	table[signals::nine][Fewer] = State::Final;
//	table[signals::border][Fewer] = State::Final;
//	table[signals::other][Fewer] = State::ERROR_lex;
//
//	// для Fewer_or_Equal
//	table[signals::alpha][Fewer_or_Equal] = State::Final;
//	table[signals::equal][Fewer_or_Equal] = State::Final;
//	table[signals::min][Fewer_or_Equal] = State::Final;
//	table[signals::plus][Fewer_or_Equal] = State::Final;
//	table[signals::more][Fewer_or_Equal] = State::Final;
//	table[signals::fewer][Fewer_or_Equal] = State::Final;
//	table[signals::one_two][Fewer_or_Equal] = State::Final;
//	table[signals::three][Fewer_or_Equal] = State::Final;
//	table[signals::four_six][Fewer_or_Equal] = State::Final;
//	table[signals::seven][Fewer_or_Equal] = State::Final;
//	table[signals::eight][Fewer_or_Equal] = State::Final;
//	table[signals::nine][Fewer_or_Equal] = State::Final;
//	table[signals::border][Fewer_or_Equal] = State::Final;
//	table[signals::other][Fewer_or_Equal] = State::ERROR_lex;
//
//	// для Equal
//	table[signals::alpha][Equal] = State::Final;
//	table[signals::equal][Equal] = State::Final;
//	table[signals::min][Equal] = State::Final;
//	table[signals::plus][Equal] = State::Final;
//	table[signals::more][Equal] = State::Final;
//	table[signals::fewer][Equal] = State::Final;
//	table[signals::one_two][Equal] = State::Final;
//	table[signals::three][Equal] = State::Final;
//	table[signals::four_six][Equal] = State::Final;
//	table[signals::seven][Equal] = State::Final;
//	table[signals::eight][Equal] = State::Final;
//	table[signals::nine][Equal] = State::Final;
//	table[signals::border][Equal] = State::Final;
//	table[signals::other][Equal] = State::ERROR_lex;
//
//	// для UnEqual
//	table[signals::alpha][UnEqual] = State::Final;
//	table[signals::equal][UnEqual] = State::Final;
//	table[signals::min][UnEqual] = State::Final;
//	table[signals::plus][UnEqual] = State::Final;
//	table[signals::more][UnEqual] = State::Final;
//	table[signals::fewer][UnEqual] = State::Final;
//	table[signals::one_two][UnEqual] = State::Final;
//	table[signals::three][UnEqual] = State::Final;
//	table[signals::four_six][UnEqual] = State::Final;
//	table[signals::seven][UnEqual] = State::Final;
//	table[signals::eight][UnEqual] = State::Final;
//	table[signals::nine][UnEqual] = State::Final;
//	table[signals::border][UnEqual] = State::Final;
//	table[signals::other][UnEqual] = State::ERROR_lex;
//
//	// для A
//	table[signals::alpha][Digit_1] = State::Id_2;
//	table[signals::equal][Digit_1] = State::Final;
//	table[signals::min][Digit_1] = State::Final;
//	table[signals::plus][Digit_1] = State::Final;
//	table[signals::more][Digit_1] = State::Final;
//	table[signals::fewer][Digit_1] = State::Final;
//	table[signals::zero][Digit_1] = State::Digit_2;
//	table[signals::one_two][Digit_1] = State::Digit_2;
//	table[signals::three][Digit_1] = State::Four_digit_number_2;
//	table[signals::four_six][Digit_1] = State::Four_digit_number_2;
//	table[signals::seven][Digit_1] = State::Four_digit_number_2;
//	table[signals::eight][Digit_1] = State::Four_digit_number_2;
//	table[signals::nine][Digit_1] = State::Four_digit_number_2;
//	table[signals::border][Digit_1] = State::Final;
//	table[signals::other][Digit_1] = State::ERROR_lex;
//
//	// для B
//	table[signals::alpha][Digit_2] = State::Id_3;
//	table[signals::equal][Digit_2] = State::Final;
//	table[signals::min][Digit_2] = State::Final;
//	table[signals::plus][Digit_2] = State::Final;
//	table[signals::more][Digit_2] = State::Final;
//	table[signals::fewer][Digit_2] = State::Final;
//	table[signals::zero][Digit_2] = State::Digit_3;
//	table[signals::one_two][Digit_2] = State::Digit_3;
//	table[signals::three][Digit_2] = State::Digit_3;
//	table[signals::four_six][Digit_2] = State::Digit_3;
//	table[signals::seven][Digit_2] = State::Digit_3;
//	table[signals::eight][Digit_2] = State::Four_digit_number_3;
//	table[signals::nine][Digit_2] = State::Four_digit_number_3;
//	table[signals::border][Digit_2] = State::Final;
//	table[signals::other][Digit_2] = State::ERROR_lex;
//
//	// для C
//	table[signals::alpha][Digit_3] = State::Id_4;
//	table[signals::equal][Digit_3] = State::Final;
//	table[signals::min][Digit_3] = State::Final;
//	table[signals::plus][Digit_3] = State::Final;
//	table[signals::more][Digit_3] = State::Final;
//	table[signals::fewer][Digit_3] = State::Final;
//	table[signals::zero][Digit_3] = State::Digit_4;
//	table[signals::one_two][Digit_3] = State::Digit_4;
//	table[signals::three][Digit_3] = State::Digit_4;
//	table[signals::four_six][Digit_3] = State::Digit_4;
//	table[signals::seven][Digit_3] = State::Four_digit_number_4;
//	table[signals::eight][Digit_3] = State::Four_digit_number_4;
//	table[signals::nine][Digit_3] = State::Four_digit_number_4;
//	table[signals::border][Digit_3] = State::Final;
//	table[signals::other][Digit_3] = State::ERROR_lex;
//
//	// для D
//	table[signals::alpha][Digit_4] = State::Id_5;
//	table[signals::equal][Digit_4] = State::Final;
//	table[signals::min][Digit_4] = State::Final;
//	table[signals::plus][Digit_4] = State::Final;
//	table[signals::more][Digit_4] = State::Final;
//	table[signals::fewer][Digit_4] = State::Final;
//	table[signals::zero][Digit_4] = State::Last_digit;
//	table[signals::one_two][Digit_4] = State::Last_digit;
//	table[signals::three][Digit_4] = State::Last_digit;
//	table[signals::four_six][Digit_4] = State::Last_digit;
//	table[signals::seven][Digit_4] = State::Last_digit;
//	table[signals::eight][Digit_4] = State::ERROR_lex;
//	table[signals::nine][Digit_4] = State::ERROR_lex;
//	table[signals::border][Digit_4] = State::Final;
//	table[signals::other][Digit_4] = State::ERROR_lex;
//
//	// для Last_digit
//	table[signals::alpha][Last_digit] = State::ERROR_lex;
//	table[signals::equal][Last_digit] = State::Final;
//	table[signals::min][Last_digit] = State::Final;
//	table[signals::plus][Last_digit] = State::Final;
//	table[signals::more][Last_digit] = State::Final;
//	table[signals::fewer][Last_digit] = State::Final;
//	table[signals::zero][Last_digit] = State::ERROR_lex;
//	table[signals::one_two][Last_digit] = State::ERROR_lex;
//	table[signals::three][Last_digit] = State::ERROR_lex;
//	table[signals::four_six][Last_digit] = State::ERROR_lex;
//	table[signals::seven][Last_digit] = State::ERROR_lex;
//	table[signals::eight][Last_digit] = State::ERROR_lex;
//	table[signals::nine][Last_digit] = State::ERROR_lex;
//	table[signals::border][Last_digit] = Final;
//	table[signals::other][Last_digit] = State::ERROR_lex;
//
//	// для More_1
//	table[signals::alpha][Four_digit_number_1] = State::Id_2;
//	table[signals::equal][Four_digit_number_1] = State::Final;
//	table[signals::min][Four_digit_number_1] = State::Final;
//	table[signals::plus][Four_digit_number_1] = State::Final;
//	table[signals::more][Four_digit_number_1] = State::Final;
//	table[signals::fewer][Four_digit_number_1] = State::Final;
//	table[signals::zero][Four_digit_number_1] = State::Four_digit_number_2;
//	table[signals::one_two][Four_digit_number_1] = State::Four_digit_number_2;
//	table[signals::three][Four_digit_number_1] = State::Four_digit_number_2;
//	table[signals::four_six][Four_digit_number_1] = State::Four_digit_number_2;
//	table[signals::seven][Four_digit_number_1] = State::Four_digit_number_2;
//	table[signals::eight][Four_digit_number_1] = State::Four_digit_number_2;
//	table[signals::nine][Four_digit_number_1] = State::Four_digit_number_2;
//	table[signals::border][Four_digit_number_1] = State::Final;
//	table[signals::other][Four_digit_number_1] = State::ERROR_lex;
//
//	// для More_2
//	table[signals::alpha][Four_digit_number_2] = State::Id_3;
//	table[signals::equal][Four_digit_number_2] = State::Final;
//	table[signals::min][Four_digit_number_2] = State::Final;
//	table[signals::plus][Four_digit_number_2] = State::Final;
//	table[signals::more][Four_digit_number_2] = State::Final;
//	table[signals::fewer][Four_digit_number_2] = State::Final;
//	table[signals::zero][Four_digit_number_2] = State::Four_digit_number_3;
//	table[signals::one_two][Four_digit_number_2] = State::Four_digit_number_3;
//	table[signals::three][Four_digit_number_2] = State::Four_digit_number_3;
//	table[signals::four_six][Four_digit_number_2] = State::Four_digit_number_3;
//	table[signals::seven][Four_digit_number_2] = State::Four_digit_number_3;
//	table[signals::eight][Four_digit_number_2] = State::Four_digit_number_3;
//	table[signals::nine][Four_digit_number_2] = State::Four_digit_number_3;
//	table[signals::border][Four_digit_number_2] = State::Final;
//	table[signals::other][Four_digit_number_2] = State::ERROR_lex;
//
//	// для More_3
//	table[signals::alpha][Four_digit_number_3] = State::Id_4;
//	table[signals::equal][Four_digit_number_3] = State::Final;
//	table[signals::min][Four_digit_number_3] = State::Final;
//	table[signals::plus][Four_digit_number_3] = State::Final;
//	table[signals::more][Four_digit_number_3] = State::Final;
//	table[signals::fewer][Four_digit_number_3] = State::Final;
//	table[signals::zero][Four_digit_number_3] = State::Four_digit_number_4;
//	table[signals::one_two][Four_digit_number_3] = State::Four_digit_number_4;
//	table[signals::three][Four_digit_number_3] = State::Four_digit_number_4;
//	table[signals::four_six][Four_digit_number_3] = State::Four_digit_number_4;
//	table[signals::seven][Four_digit_number_3] = State::Four_digit_number_4;
//	table[signals::eight][Four_digit_number_3] = State::Four_digit_number_4;
//	table[signals::nine][Four_digit_number_3] = State::Four_digit_number_4;
//	table[signals::border][Four_digit_number_3] = State::Final;
//	table[signals::other][Four_digit_number_3] = State::ERROR_lex;
//
//	// для More_4
//	table[signals::alpha][Four_digit_number_4] = State::Id_5;
//	table[signals::equal][Four_digit_number_4] = State::Final;
//	table[signals::min][Four_digit_number_4] = State::Final;
//	table[signals::plus][Four_digit_number_4] = State::Final;
//	table[signals::more][Four_digit_number_4] = State::Final;
//	table[signals::fewer][Four_digit_number_4] = State::Final;
//	table[signals::zero][Four_digit_number_4] = State::ERROR_lex;
//	table[signals::one_two][Four_digit_number_4] = State::ERROR_lex;
//	table[signals::three][Four_digit_number_4] = State::ERROR_lex;
//	table[signals::four_six][Four_digit_number_4] = State::ERROR_lex;
//	table[signals::seven][Four_digit_number_4] = State::ERROR_lex;
//	table[signals::eight][Four_digit_number_4] = State::ERROR_lex;
//	table[signals::nine][Four_digit_number_4] = State::ERROR_lex;
//	table[signals::border][Four_digit_number_4] = State::Final;
//	table[signals::other][Four_digit_number_4] = State::ERROR_lex;
//
//	// для ERROR
//	table[signals::alpha][State::ERROR_lex] = State::ERROR_lex;
//	table[signals::equal][State::ERROR_lex] = State::Final;
//	table[signals::min][State::ERROR_lex] = State::Final;
//	table[signals::plus][State::ERROR_lex] = State::Final;
//	table[signals::more][State::ERROR_lex] = State::Final;
//	table[signals::fewer][State::ERROR_lex] = State::Final;
//	table[signals::zero][State::ERROR_lex] = State::ERROR_lex;
//	table[signals::one_two][State::ERROR_lex] = State::ERROR_lex;
//	table[signals::three][State::ERROR_lex] = State::ERROR_lex;
//	table[signals::four_six][State::ERROR_lex] = State::ERROR_lex;
//	table[signals::seven][State::ERROR_lex] = State::ERROR_lex;
//	table[signals::eight][State::ERROR_lex] = State::ERROR_lex;
//	table[signals::nine][State::ERROR_lex] = State::ERROR_lex;
//	table[signals::border][State::ERROR_lex] = State::Final;
//	table[signals::other][State::ERROR_lex] = State::ERROR_lex;
//
//	// для Final
//	table[signals::alpha][Final] = State::Id_1;
//	table[signals::equal][Final] = State::Equal;
//	table[signals::min][Final] = State::Minus;
//	table[signals::plus][Final] = State::Plus;
//	table[signals::more][Final] = State::More;
//	table[signals::fewer][Final] = State::Fewer;
//	table[signals::one_two][Final] = State::Digit_1;
//	table[signals::three][Final] = State::Digit_1;
//	table[signals::four_six][Final] = State::Four_digit_number_1;
//	table[signals::seven][Final] = State::Four_digit_number_1;
//	table[signals::eight][Final] = State::Four_digit_number_1;
//	table[signals::nine][Final] = State::Four_digit_number_1;
//	table[signals::border][Final] = State::Final;
//	table[signals::other][Final] = State::ERROR_lex;
//}
//
//int Get_File_size(ifstream& in) { // узнаём размер файла
//	in.seekg(1, std::ios::end);
//	return in.tellg();
//}
//
//int read_file(ifstream& in, char*& mass) { // считываем файл
//	int sz = Get_File_size(in);
//	in.seekg(0, std::ios::beg);
//	mass = new char[sz];
//	in.getline(mass, sz, '\0');
//	return sz;
//}
//
//lex_type Get_lex_type(State st, const char* txt) { // выбираем лексему
//	if (st == Four_digit_number_1 || st == Four_digit_number_2 || st == Four_digit_number_3 || st == Four_digit_number_4 || st == Digit_1 || st == Digit_2 || st == Digit_3 || st == Digit_4 || st == Last_digit)
//		return vl;
//	else if (st == State::ERROR_lex)
//		return wl;
//	else if (st == Minus)
//		return minus;
//	else if (st == Plus)
//		return ao;
//	else if (st == Equal)
//		return eq;
//	else if (st == Fewer || st == Fewer_or_Equal || st == More || st == More_or_Equal || st == UnEqual)
//		return co;
//	else if (st == Id_1 || st == Id_5)
//		return id;
//	else if (st == Id_2) // праверяем на соответствие ключевым словам
//		return (!strcmp(txt, "if")) ? _if : id;
//	else if (st == Id_3)
//		return (!strcmp(txt, "end")) ? en : id;
//	else if (st == Id_4)
//		return ((!strcmp(txt, "then")) ? th : (!strcmp(txt, "else") ? el : id));
//}
//
//void lex_analys(vector<Lex>& res, char* text, State table[15][25], int mass_sz) {
//	Lex lex{};
//	State cur{ Start_lex }, prev;
//	char ptr;
//	int counter{ 0 }, counter_prev{ 0 };
//	while (counter < mass_sz) {
//		prev = cur;
//		ptr = text[counter];
//
//		cur = table[get_signal(ptr)][cur];
//
//		if (!cur) // если несколько разделителей ' ', '\t', '\n'
//			++counter_prev;
//
//		if (cur == State::Final) {
//			int size = counter - counter_prev;
//			lex.mass = new char[size + 1];
//			strncpy(lex.mass, &text[0] + counter_prev, size);
//			lex.mass[size] = '\0';
//			lex.type = Get_lex_type(prev, lex.mass);
//			res.push_back(lex);
//			counter_prev = (ptr == ' ' || ptr == '\t' || ptr == '\n' ? counter + 1 : counter); // для недопуска разделителей в лексемму
//			cur = table[get_signal(ptr)][cur = Start_lex];
//		}
//		++counter;
//	}
//	lex.type = sharp;
//	lex.mass = new char[2];
//	lex.mass[0] = '#';
//	lex.mass[1] = '\0';
//	res.push_back(lex);
//}
//
//void printl(vector<Lex>& vec, ofstream& out) {
//	vector<Lex>::iterator iter = vec.begin();
//	const char* list_of_types[] = { "if", "th", "el", "en", "id", "vl", "co", "ao", "eq", "wl", "sharp" };
//	while (iter != vec.end() - 1) {
//		out << iter->mass << '[' << ((iter->type > 7) ? list_of_types[iter->type - 1] : list_of_types[iter->type]) << ']' << ' ';
//		++iter;
//	}
//	out << '\n';
//}
//
//void delete_res(vector<Lex>& res) { // удаление
//	for (std::vector<Lex>::size_type j = 0; j < res.size(); ++j)
//		delete[] res[j].mass;
//}
//
//int main() {
//	ifstream in("input.txt"); // читаем из файла
//	char* mass;
//	int mass_sz = read_file(in, mass);
//	in.close();
//	vector<Lex> res;
//	State table[15][25];
//	filling_automat_table(table);
//	lex_analys(res, mass, table, mass_sz);
//	ofstream out("output.txt");
//	printl(res, out);
//	out.close();
//	delete_res(res);
//	delete[] mass;
//	return 0;
//}