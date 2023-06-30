//#define _CRT_SECURE_NO_WARNINGS
//#include<fstream>
//#include<vector>
//#include<cstring>
//
//enum State 
//{ 
//	Start, t, TH, THE, THEN, e, EL, ELS, ELSE, EN, END, i, IF, Id_1,Id_2, Id_3, Id_4,
//	Id_5, Minus, Plus, More, Fewer, More_or_Equal, Fewer_or_Equal, Equal, A, A_m, B, B_M,
//	C, C_M, d, D_M, More_1, More_2, More_3, More_4, ERROR, Final, Last_digit
//};
//
//enum signals { I, F, T, H, E, N, D, L, S, alpha, min, more, fewer, plus, equal, border, one_two, three, four_six, seven, eight, nine, zero, other }; 
//
//enum lex_type { kw, id, vl, co, ao, eq, wl };
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
//struct Lex
//{
//	char* mass;
//	lex_type type;
//};
//
//signals get_signal(const char ch) {
//	if (ch == '0') return zero;
//	else if (ch == 'i') return I;
//	else if (ch == 'f') return F;
//	else if (ch == 'e') return E;
//	else if (ch == 'h') return H;
//	else if (ch == 'l') return L;
//	else if (ch == 's') return S;
//	else if (ch == 'n') return N;
//	else if (ch == 'd') return D;
//	else if (ch == 't') return T;
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
///*
//void filling_automat_table(State (&table)[24][40]) {
//	// для S
//	table[signals::I][Start] = State::i;
//	table[signals::T][Start] = State::t;
//	table[signals::E][Start] = State::e;
//	table[signals::alpha][Start] = State::Id_1;
//	table[signals::equal][Start] = State::Equal;
//	table[signals::min][Start] = State::Minus;
//	table[signals::plus][Start] = State::Plus;
//	table[signals::more][Start] = State::More;
//	table[signals::fewer][Start] = State::Fewer;
//	table[signals::one_two][Start] = A;
//	table[signals::three][Start] = A;
//	table[signals::four_six][Start] = More_1;
//	table[signals::seven][Start] = More_1;
//	table[signals::eight][Start] = More_1; 
//	table[signals::nine][Start] = More_1;
//	table[signals::F][Start] = Id_1;
//	table[signals::F][Start] = Id_1;
//	table[signals::H][Start] = Id_1;
//	table[signals::L][Start] = Id_1;
//	table[signals::S][Start] = Id_1;
//	table[signals::N][Start] = Id_1;
//	table[signals::D][Start] = Id_1;
//	table[signals::border][Start] = Start;
//	table[signals::other][Start] = ERROR;
//
//	// для T
//	table[signals::H][t] = State::TH;
//	table[signals::alpha][t] = State::Id_2;
//	table[signals::equal][t] = ERROR;
//	table[signals::more][t] = ERROR;
//	table[signals::min][t] = ERROR;
//	table[signals::plus][t] = ERROR;
//	table[signals::fewer][t] = ERROR;
//	table[signals::zero][t] = Id_2;
//	table[signals::one_two][t] = Id_2;
//	table[signals::three][t] = Id_2; 
//	table[signals::four_six][t] = Id_2;
//	table[signals::seven][t] = Id_2;
//	table[signals::eight][t] = Id_2;
//	table[signals::nine][t] = Id_2;
//	table[signals::T][t] = Id_2;
//	table[signals::E][t] = Id_2;
//	table[signals::F][t] = Id_2;
//	table[signals::I][t] = Id_2;
//	table[signals::L][t] = Id_2;
//	table[signals::S][t] = Id_2;
//	table[signals::N][t] = Id_2;
//	table[signals::D][t] = Id_2;
//	table[signals::border][t] = State::Final;
//	table[signals::other][t] = ERROR;
//
//	// для TH
//	table[signals::H][TH] = State::TH;
//	table[signals::alpha][TH] = State::Id_3;
//	table[signals::equal][TH] = ERROR;
//	table[signals::more][TH] = ERROR;
//	table[signals::min][TH] = ERROR;
//	table[signals::plus][TH] = ERROR;
//	table[signals::fewer][TH] = ERROR;
//	table[signals::zero][THE] = Id_3;
//	table[signals::one_two][TH] = Id_3;
//	table[signals::three][TH] = Id_3;
//	table[signals::four_six][TH] = Id_3;
//	table[signals::seven][TH] = Id_3;
//	table[signals::eight][TH] = Id_3;
//	table[signals::nine][TH] = Id_3;
//	table[signals::T][TH] = Id_3;
//	table[signals::E][TH] = THE;
//	table[signals::F][TH] = Id_3;
//	table[signals::I][TH] = Id_3;
//	table[signals::L][TH] = Id_3;
//	table[signals::S][TH] = Id_3;
//	table[signals::N][TH] = Id_3;
//	table[signals::D][TH] = Id_3;
//	table[signals::border][TH] = State::Final;
//	table[signals::other][TH] = ERROR;
//
//	// для THE
//	table[signals::N][THE] = State::THEN;
//	table[signals::alpha][THE] = State::Id_4;
//	table[signals::equal][THE] = State::ERROR;
//	table[signals::min][THE] = State::ERROR;
//	table[signals::plus][THE] = State::ERROR;
//	table[signals::more][THE] = State::ERROR;
//	table[signals::fewer][THE] = State::ERROR;
//	table[signals::one_two][THE] = Id_4;
//	table[signals::three][THE] = State::Id_4;
//	table[signals::four_six][THE] = Id_4;
//	table[signals::seven][THE] = Id_4;
//	table[signals::eight][THE] = Id_4;
//	table[signals::nine][THE] = Id_4;
//	table[signals::zero][THE] = Id_4;
//	table[signals::H][THE] = State::Id_4;
//	table[signals::T][THE] = State::Id_4;
//	table[signals::F][THE] = State::Id_4;
//	table[signals::I][THE] = State::Id_4;
//	table[signals::L][THE] = State::Id_4;
//	table[signals::S][THE] = State::Id_4;
//	table[signals::E][THE] = State::Id_4;
//	table[signals::D][THE] = State::Id_4;
//	table[signals::border][THE] = State::Final;
//	table[signals::other][THE] = ERROR;
//
//	// для THEN
//	table[signals::N][THEN] = State::Id_5;
//	table[signals::alpha][THEN] = State::Id_5;
//	table[signals::equal][THEN] = State::ERROR;
//	table[signals::min][THEN] = State::ERROR;
//	table[signals::plus][THEN] = State::ERROR;
//	table[signals::more][THEN] = State::ERROR;
//	table[signals::fewer][THEN] = State::ERROR;
//	table[signals::one_two][THEN] = Id_5;
//	table[signals::three][THEN] = State::Id_5;
//	table[signals::four_six][THEN] = Id_5;
//	table[signals::seven][THEN] = Id_5;
//	table[signals::eight][THEN] = Id_5;
//	table[signals::nine][THEN] = Id_5;
//	table[signals::zero][THEN] = Id_5;
//	table[signals::H][THEN] = State::Id_5;
//	table[signals::T][THEN] = State::Id_5;
//	table[signals::F][THEN] = State::Id_5;
//	table[signals::I][THEN] = State::Id_5;
//	table[signals::L][THEN] = State::Id_5;
//	table[signals::S][THEN] = State::Id_5;
//	table[signals::E][THEN] = State::Id_5;
//	table[signals::D][THEN] = State::Id_5;
//	table[signals::border][THEN] = State::Final;
//	table[signals::other][THEN] = ERROR;
//
//	// для I
//	table[signals::N][i] = State::Id_2;
//	table[signals::alpha][i] = State::Id_2;
//	table[signals::equal][i] = State::ERROR;
//	table[signals::min][i] = State::ERROR;
//	table[signals::plus][i] = State::ERROR;
//	table[signals::more][i] = State::ERROR;
//	table[signals::fewer][i] = State::ERROR;
//	table[signals::one_two][i] = Id_2;
//	table[signals::three][i] = Id_2;
//	table[signals::four_six][i] = Id_2;
//	table[signals::seven][i] = Id_2;
//	table[signals::eight][i] = Id_2;
//	table[signals::nine][i] = Id_2;
//	table[signals::zero][i] = Id_2;
//	table[signals::H][i] = State::Id_2;
//	table[signals::T][i] = State::Id_2;
//	table[signals::F][i] = State::IF;
//	table[signals::I][i] = State::Id_2;
//	table[signals::L][i] = State::Id_2;
//	table[signals::S][i] = State::Id_2;
//	table[signals::E][i] = State::Id_2;
//	table[signals::D][i] = State::Id_2;
//	table[signals::border][i] = State::Final;
//	table[signals::other][i] = ERROR;
//
//	// для IF
//	table[signals::N][IF] = State::Id_3;
//	table[signals::alpha][IF] = State::Id_3;
//	table[signals::equal][IF] = State::ERROR;
//	table[signals::min][IF] = State::ERROR;
//	table[signals::plus][IF] = State::ERROR;
//	table[signals::more][IF] = State::ERROR;
//	table[signals::fewer][IF] = State::ERROR;
//	table[signals::one_two][IF] = Id_3;
//	table[signals::three][IF] = Id_3;
//	table[signals::four_six][IF] = Id_3;
//	table[signals::seven][IF] = Id_3;
//	table[signals::eight][IF] = Id_3;
//	table[signals::nine][IF] = Id_3;
//	table[signals::zero][IF] = Id_3;
//	table[signals::H][IF] = State::Id_3;
//	table[signals::T][IF] = State::Id_3;
//	table[signals::F][IF] = State::Id_3;
//	table[signals::I][IF] = State::Id_3;
//	table[signals::L][IF] = State::Id_3;
//	table[signals::S][IF] = State::Id_3;
//	table[signals::E][IF] = State::Id_3;
//	table[signals::D][IF] = State::Id_3;
//	table[signals::border][IF] = State::Final;
//	table[signals::other][IF] = ERROR;
//
//	// для E
//	table[signals::N][e] = State::EN;
//	table[signals::alpha][e] = State::Id_2;
//	table[signals::equal][e] = State::ERROR;
//	table[signals::min][e] = State::ERROR;
//	table[signals::plus][e] = State::ERROR;
//	table[signals::more][e] = State::ERROR;
//	table[signals::fewer][e] = State::ERROR;
//	table[signals::one_two][e] = Id_2;
//	table[signals::three][e] = Id_2;
//	table[signals::four_six][e] = Id_2;
//	table[signals::seven][e] = Id_2;
//	table[signals::eight][e] = Id_2;
//	table[signals::nine][e] = Id_2;
//	table[signals::zero][e] = Id_2;
//	table[signals::H][e] = State::Id_2;
//	table[signals::T][e] = State::Id_2;
//	table[signals::F][e] = State::Id_2;
//	table[signals::I][e] = State::Id_2;
//	table[signals::L][e] = State::EL;
//	table[signals::S][e] = State::Id_2;
//	table[signals::E][e] = State::Id_2;
//	table[signals::D][e] = State::Id_2;
//	table[signals::border][e] = State::Final;
//	table[signals::other][e] = ERROR;
//
//	// для EN
//	table[signals::N][EN] = State::Id_3;
//	table[signals::alpha][EN] = State::Id_3;
//	table[signals::equal][EN] = State::ERROR;
//	table[signals::min][EN] = State::ERROR;
//	table[signals::plus][EN] = State::ERROR;
//	table[signals::more][EN] = State::ERROR;
//	table[signals::fewer][EN] = State::ERROR;
//	table[signals::one_two][EN] = Id_3;
//	table[signals::three][EN] = Id_3;
//	table[signals::four_six][EN] = Id_3;
//	table[signals::seven][EN] = Id_3;
//	table[signals::eight][EN] = Id_3;
//	table[signals::nine][EN] = Id_3;
//	table[signals::zero][EN] = Id_3;
//	table[signals::H][EN] = State::Id_3;
//	table[signals::T][EN] = State::Id_3;
//	table[signals::F][EN] = State::Id_3;
//	table[signals::I][EN] = State::Id_3;
//	table[signals::L][EN] = State::Id_3;
//	table[signals::S][EN] = State::Id_3;
//	table[signals::E][EN] = State::Id_3;
//	table[signals::D][EN] = State::END;
//	table[signals::border][EN] = State::Final;
//	table[signals::other][EN] = ERROR;
//
//	// для END
//	table[signals::N][END] = State::Id_4;
//	table[signals::alpha][END] = State::Id_4;
//	table[signals::equal][END] = State::ERROR;
//	table[signals::min][END] = State::ERROR;
//	table[signals::plus][END] = State::ERROR;
//	table[signals::more][END] = State::ERROR;
//	table[signals::fewer][END] = State::ERROR;
//	table[signals::one_two][END] = Id_4;
//	table[signals::three][END] = Id_4;
//	table[signals::four_six][END] = Id_4;
//	table[signals::seven][END] = Id_4;
//	table[signals::eight][END] = Id_4;
//	table[signals::nine][END] = Id_4;
//	table[signals::zero][END] = Id_4;
//	table[signals::H][END] = State::Id_4;
//	table[signals::T][END] = State::Id_4;
//	table[signals::F][END] = State::Id_4;
//	table[signals::I][END] = State::Id_4;
//	table[signals::L][END] = State::Id_4;
//	table[signals::S][END] = State::Id_4;
//	table[signals::E][END] = State::Id_4;
//	table[signals::D][END] = State::END;
//	table[signals::border][END] = State::Final;
//	table[signals::other][END] = ERROR;
//
//	// для EL
//	table[signals::N][EL] = State::Id_3;
//	table[signals::alpha][EL] = State::Id_3;
//	table[signals::equal][EL] = State::ERROR;
//	table[signals::min][EL] = State::ERROR;
//	table[signals::plus][EL] = State::ERROR;
//	table[signals::more][EL] = State::ERROR;
//	table[signals::fewer][EL] = State::ERROR;
//	table[signals::one_two][EL] = Id_3;
//	table[signals::three][EL] = Id_3;
//	table[signals::four_six][EL] = Id_3;
//	table[signals::seven][EL] = Id_3;
//	table[signals::eight][EL] = Id_3;
//	table[signals::nine][EL] = Id_3;
//	table[signals::zero][EL] = Id_3;
//	table[signals::H][EL] = State::Id_3;
//	table[signals::T][EL] = State::Id_3;
//	table[signals::F][EL] = State::Id_3;
//	table[signals::I][EL] = State::Id_3;
//	table[signals::L][EL] = State::Id_3;
//	table[signals::S][EL] = State::ELS;
//	table[signals::E][EL] = State::Id_3;
//	table[signals::D][EL] = State::Id_3;
//	table[signals::border][EL] = State::Final;
//	table[signals::other][EL] = ERROR;
//
//	// для ELS
//	table[signals::N][ELS] = State::Id_4;
//	table[signals::alpha][ELS] = State::Id_4;
//	table[signals::equal][ELS] = State::ERROR;
//	table[signals::min][ELS] = State::ERROR;
//	table[signals::plus][ELS] = State::ERROR;
//	table[signals::more][ELS] = State::ERROR;
//	table[signals::fewer][ELS] = State::ERROR;
//	table[signals::one_two][ELS] = Id_4;
//	table[signals::three][ELS] = Id_4;
//	table[signals::four_six][ELS] = Id_4;
//	table[signals::seven][ELS] = Id_4;
//	table[signals::eight][ELS] = Id_4;
//	table[signals::nine][ELS] = Id_4;
//	table[signals::zero][ELS] = Id_4;
//	table[signals::H][ELS] = State::Id_4;
//	table[signals::T][ELS] = State::Id_4;
//	table[signals::F][ELS] = State::Id_4;
//	table[signals::I][ELS] = State::Id_4;
//	table[signals::L][ELS] = State::Id_4;
//	table[signals::S][ELS] = State::Id_4;
//	table[signals::E][ELS] = State::ELSE;
//	table[signals::D][ELS] = State::Id_4;
//	table[signals::border][ELS] = State::Final;
//	table[signals::other][ELS] = ERROR;
//
//	// для ELSE
//	table[signals::N][ELSE] = State::Id_5;
//	table[signals::alpha][ELSE] = State::Id_5;
//	table[signals::equal][ELSE] = State::ERROR;
//	table[signals::min][ELSE] = State::ERROR;
//	table[signals::plus][ELSE] = State::ERROR;
//	table[signals::more][ELSE] = State::ERROR;
//	table[signals::fewer][ELSE] = State::ERROR;
//	table[signals::one_two][ELSE] = Id_5;
//	table[signals::three][ELSE] = Id_5;
//	table[signals::four_six][ELSE] = Id_5;
//	table[signals::seven][ELSE] = Id_5;
//	table[signals::eight][ELSE] = Id_5;
//	table[signals::nine][ELSE] = Id_5;
//	table[signals::zero][ELSE] = Id_5;
//	table[signals::H][ELSE] = State::Id_5;
//	table[signals::T][ELSE] = State::Id_5;
//	table[signals::F][ELSE] = State::Id_5;
//	table[signals::I][ELSE] = State::Id_5;
//	table[signals::L][ELSE] = State::Id_5;
//	table[signals::S][ELSE] = State::Id_5;
//	table[signals::E][ELSE] = State::Id_5;
//	table[signals::D][ELSE] = State::Id_5;
//	table[signals::border][ELSE] = State::Final;
//	table[signals::other][ELSE] = ERROR;
//
//	// Id_1
//	table[signals::N][Id_1] = State::Id_2;
//	table[signals::alpha][Id_1] = State::Id_2;
//	table[signals::equal][Id_1] = State::ERROR;
//	table[signals::min][Id_1] = State::ERROR;
//	table[signals::plus][Id_1] = State::ERROR;
//	table[signals::more][Id_1] = State::ERROR;
//	table[signals::fewer][Id_1] = State::ERROR;
//	table[signals::one_two][Id_1] = Id_2;
//	table[signals::three][Id_1] = Id_2;
//	table[signals::four_six][Id_1] = Id_2;
//	table[signals::seven][Id_1] = Id_2;
//	table[signals::eight][Id_1] = Id_2;
//	table[signals::nine][Id_1] = Id_2;
//	table[signals::zero][Id_1] = Id_2;
//	table[signals::H][Id_1] = State::Id_2;
//	table[signals::T][Id_1] = State::Id_2;
//	table[signals::F][Id_1] = State::Id_2;
//	table[signals::I][Id_1] = State::Id_2;
//	table[signals::L][Id_1] = State::Id_2;
//	table[signals::S][Id_1] = State::Id_2;
//	table[signals::E][Id_1] = State::Id_2;
//	table[signals::D][Id_1] = State::Id_2;
//	table[signals::border][Id_1] = State::Final;
//	table[signals::other][Id_1] = ERROR;
//
//	// для Id_2
//	table[signals::N][Id_2] = State::Id_3;
//	table[signals::alpha][Id_2] = State::Id_3;
//	table[signals::equal][Id_2] = State::ERROR;
//	table[signals::min][Id_2] = State::ERROR;
//	table[signals::plus][Id_2] = State::ERROR;
//	table[signals::more][Id_2] = State::ERROR;
//	table[signals::fewer][Id_2] = State::ERROR;
//	table[signals::one_two][Id_2] = Id_3;
//	table[signals::three][Id_2] = Id_3;
//	table[signals::four_six][Id_2] = Id_3;
//	table[signals::seven][Id_2] = Id_3;
//	table[signals::eight][Id_2] = Id_3;
//	table[signals::nine][Id_2] = Id_3;
//	table[signals::zero][Id_2] = Id_3;
//	table[signals::H][Id_2] = State::Id_3;
//	table[signals::T][Id_2] = State::Id_3;
//	table[signals::F][Id_2] = State::Id_3;
//	table[signals::I][Id_2] = State::Id_3;
//	table[signals::L][Id_2] = State::Id_3;
//	table[signals::S][Id_2] = State::Id_3;
//	table[signals::E][Id_2] = State::Id_3;
//	table[signals::D][Id_2] = State::Id_3;
//	table[signals::border][Id_2] = State::Final;
//	table[signals::other][Id_2] = ERROR;
//
//	// для Id_3
//	table[signals::N][Id_3] = State::Id_4;
//	table[signals::alpha][Id_3] = State::Id_4;
//	table[signals::equal][Id_3] = State::ERROR;
//	table[signals::min][Id_3] = State::ERROR;
//	table[signals::plus][Id_3] = State::ERROR;
//	table[signals::more][Id_3] = State::ERROR;
//	table[signals::fewer][Id_3] = State::ERROR;
//	table[signals::one_two][Id_3] = Id_4;
//	table[signals::three][Id_3] = Id_4;
//	table[signals::four_six][Id_3] = Id_4;
//	table[signals::seven][Id_3] = Id_4;
//	table[signals::eight][Id_3] = Id_4;
//	table[signals::nine][Id_3] = Id_4;
//	table[signals::zero][Id_3] = Id_4;
//	table[signals::H][Id_3] = State::Id_4;
//	table[signals::T][Id_3] = State::Id_4;
//	table[signals::F][Id_3] = State::Id_4;
//	table[signals::I][Id_3] = State::Id_4;
//	table[signals::L][Id_3] = State::Id_4;
//	table[signals::S][Id_3] = State::Id_4;
//	table[signals::E][Id_3] = State::Id_4;
//	table[signals::D][Id_3] = State::Id_4;
//	table[signals::border][Id_3] = State::Final;
//	table[signals::other][Id_3] = ERROR;
//	
//	// для Id_4
//	table[signals::N][Id_4] = State::Id_5;
//	table[signals::alpha][Id_4] = State::Id_5;
//	table[signals::equal][Id_4] = State::ERROR;
//	table[signals::min][Id_4] = State::ERROR;
//	table[signals::plus][Id_4] = State::ERROR;
//	table[signals::more][Id_4] = State::ERROR;
//	table[signals::fewer][Id_4] = State::ERROR;
//	table[signals::one_two][Id_4] = Id_5;
//	table[signals::three][Id_4] = Id_5;
//	table[signals::four_six][Id_4] = Id_5;
//	table[signals::seven][Id_4] = Id_5;
//	table[signals::eight][Id_4] = Id_5;
//	table[signals::nine][Id_4] = Id_5;
//	table[signals::zero][Id_4] = Id_5;
//	table[signals::H][Id_4] = State::Id_5;
//	table[signals::T][Id_4] = State::Id_5;
//	table[signals::F][Id_4] = State::Id_5;
//	table[signals::I][Id_4] = State::Id_5;
//	table[signals::L][Id_4] = State::Id_5;
//	table[signals::S][Id_4] = State::Id_5;
//	table[signals::E][Id_4] = State::Id_5;
//	table[signals::D][Id_4] = State::Id_5;
//	table[signals::border][Id_4] = State::Final;
//	table[signals::other][Id_4] = ERROR;
//
//	// для Id_5
//	table[signals::N][Id_5] = State::ERROR;
//	table[signals::alpha][Id_5] = State::ERROR;
//	table[signals::equal][Id_5] = State::ERROR;
//	table[signals::min][Id_5] = State::ERROR;
//	table[signals::plus][Id_5] = State::ERROR;
//	table[signals::more][Id_5] = State::ERROR;
//	table[signals::fewer][Id_5] = State::ERROR;
//	table[signals::one_two][Id_5] = ERROR;
//	table[signals::three][Id_5] = ERROR;
//	table[signals::four_six][Id_5] = ERROR;
//	table[signals::seven][Id_5] = ERROR;
//	table[signals::eight][Id_5] = ERROR;
//	table[signals::nine][Id_5] = ERROR;
//	table[signals::zero][Id_5] = ERROR;
//	table[signals::H][Id_5] = State::ERROR;
//	table[signals::T][Id_5] = State::ERROR;
//	table[signals::F][Id_5] = State::ERROR;
//	table[signals::I][Id_5] = State::ERROR;
//	table[signals::L][Id_5] = State::ERROR;
//	table[signals::S][Id_5] = State::ERROR;
//	table[signals::E][Id_5] = State::ERROR;
//	table[signals::D][Id_5] = State::ERROR;
//	table[signals::border][Id_5] = State::Final;
//	table[signals::other][Id_5] = ERROR;
//
//	// для Plus
//	table[signals::N][Plus] = State::ERROR;
//	table[signals::alpha][Plus] = State::ERROR;
//	table[signals::equal][Plus] = State::ERROR;
//	table[signals::min][Plus] = State::ERROR;
//	table[signals::plus][Plus] = State::ERROR;
//	table[signals::more][Plus] = State::ERROR;
//	table[signals::fewer][Plus] = State::ERROR;
//	table[signals::one_two][Plus] = ERROR;
//	table[signals::three][Plus] = ERROR;
//	table[signals::four_six][Plus] = ERROR;
//	table[signals::seven][Plus] = ERROR;
//	table[signals::eight][Plus] = ERROR;
//	table[signals::nine][Plus] = ERROR;
//	table[signals::zero][Plus] = ERROR;
//	table[signals::H][Plus] = State::ERROR;
//	table[signals::T][Plus] = State::ERROR;
//	table[signals::F][Plus] = State::ERROR;
//	table[signals::I][Plus] = State::ERROR;
//	table[signals::L][Plus] = State::ERROR;
//	table[signals::S][Plus] = State::ERROR;
//	table[signals::E][Plus] = State::ERROR;
//	table[signals::D][Plus] = State::ERROR;
//	table[signals::border][Plus] = State::Final;
//	table[signals::other][Plus] = ERROR;
//
//	// для Equal
//	table[signals::N][Equal] = State::ERROR;
//	table[signals::alpha][Equal] = State::ERROR;
//	table[signals::equal][Equal] = State::ERROR;
//	table[signals::min][Equal] = State::ERROR;
//	table[signals::plus][Equal] = State::ERROR;
//	table[signals::more][Equal] = State::ERROR;
//	table[signals::fewer][Equal] = State::ERROR;
//	table[signals::one_two][Equal] = ERROR;
//	table[signals::three][Equal] = ERROR;
//	table[signals::four_six][Equal] = ERROR;
//	table[signals::seven][Equal] = ERROR;
//	table[signals::eight][Equal] = ERROR;
//	table[signals::nine][Equal] = ERROR;
//	table[signals::zero][Equal] = ERROR;
//	table[signals::H][Equal] = State::ERROR;
//	table[signals::T][Equal] = State::ERROR;
//	table[signals::F][Equal] = State::ERROR;
//	table[signals::I][Equal] = State::ERROR;
//	table[signals::L][Equal] = State::ERROR;
//	table[signals::S][Equal] = State::ERROR;
//	table[signals::E][Equal] = State::ERROR;
//	table[signals::D][Equal] = State::ERROR;
//	table[signals::border][Equal] = State::Final;
//	table[signals::other][Equal] = ERROR;
//
//	// для Fewer
//	table[signals::N][Fewer] = State::ERROR;
//	table[signals::alpha][Fewer] = State::ERROR;
//	table[signals::equal][Fewer] = State::Fewer_or_Equal;
//	table[signals::min][Fewer] = State::ERROR;
//	table[signals::plus][Fewer] = State::ERROR;
//	table[signals::more][Fewer] = State::ERROR;
//	table[signals::fewer][Fewer] = State::ERROR;
//	table[signals::one_two][Fewer] = ERROR;
//	table[signals::three][Fewer] = ERROR;
//	table[signals::four_six][Fewer] = ERROR;
//	table[signals::seven][Fewer] = ERROR;
//	table[signals::eight][Fewer] = ERROR;
//	table[signals::nine][Fewer] = ERROR;
//	table[signals::zero][Fewer] = ERROR;
//	table[signals::H][Fewer] = State::ERROR;
//	table[signals::T][Fewer] = State::ERROR;
//	table[signals::F][Fewer] = State::ERROR;
//	table[signals::I][Fewer] = State::ERROR;
//	table[signals::L][Fewer] = State::ERROR;
//	table[signals::S][Fewer] = State::ERROR;
//	table[signals::E][Fewer] = State::ERROR;
//	table[signals::D][Fewer] = State::ERROR;
//	table[signals::border][Fewer] = State::Final;
//	table[signals::other][Fewer] = ERROR;
//
//	// для Fewer_or_Equal
//	table[signals::N][Fewer_or_Equal] = State::ERROR;
//	table[signals::alpha][Fewer_or_Equal] = State::ERROR;
//	table[signals::equal][Fewer_or_Equal] = State::ERROR;
//	table[signals::min][Fewer_or_Equal] = State::ERROR;
//	table[signals::plus][Fewer_or_Equal] = State::ERROR;
//	table[signals::more][Fewer_or_Equal] = State::ERROR;
//	table[signals::fewer][Fewer_or_Equal] = State::ERROR;
//	table[signals::one_two][Fewer_or_Equal] = ERROR;
//	table[signals::three][Fewer_or_Equal] = ERROR;
//	table[signals::four_six][Fewer_or_Equal] = ERROR;
//	table[signals::seven][Fewer_or_Equal] = ERROR;
//	table[signals::eight][Fewer_or_Equal] = ERROR;
//	table[signals::nine][Fewer_or_Equal] = ERROR;
//	table[signals::zero][Fewer_or_Equal] = ERROR;
//	table[signals::H][Fewer_or_Equal] = State::ERROR;
//	table[signals::T][Fewer_or_Equal] = State::ERROR;
//	table[signals::F][Fewer_or_Equal] = State::ERROR;
//	table[signals::I][Fewer_or_Equal] = State::ERROR;
//	table[signals::L][Fewer_or_Equal] = State::ERROR;
//	table[signals::S][Fewer_or_Equal] = State::ERROR;
//	table[signals::E][Fewer_or_Equal] = State::ERROR;
//	table[signals::D][Fewer_or_Equal] = State::ERROR;
//	table[signals::border][Fewer_or_Equal] = State::Final;
//	table[signals::other][Fewer_or_Equal] = ERROR;
//
//	// для More
//	table[signals::N][More] = State::ERROR;
//	table[signals::alpha][More] = State::ERROR;
//	table[signals::equal][More] = State::More_or_Equal;
//	table[signals::min][More] = State::ERROR;
//	table[signals::plus][More] = State::ERROR;
//	table[signals::more][More] = State::ERROR;
//	table[signals::fewer][More] = State::ERROR;
//	table[signals::one_two][More] = ERROR;
//	table[signals::three][More] = ERROR;
//	table[signals::four_six][More] = ERROR;
//	table[signals::seven][More] = ERROR;
//	table[signals::eight][More] = ERROR;
//	table[signals::nine][More] = ERROR;
//	table[signals::zero][More] = ERROR;
//	table[signals::H][More] = State::ERROR;
//	table[signals::T][More] = State::ERROR;
//	table[signals::F][More] = State::ERROR;
//	table[signals::I][More] = State::ERROR;
//	table[signals::L][More] = State::ERROR;
//	table[signals::S][More] = State::ERROR;
//	table[signals::E][More] = State::ERROR;
//	table[signals::D][More] = State::ERROR;
//	table[signals::border][More] = State::Final;
//	table[signals::other][More] = ERROR;
//
//	// для More_or_Equal
//	table[signals::N][More_or_Equal] = State::ERROR;
//	table[signals::alpha][More_or_Equal] = State::ERROR;
//	table[signals::equal][More_or_Equal] = State::ERROR;
//	table[signals::min][More_or_Equal] = State::Minus;
//	table[signals::plus][More_or_Equal] = State::ERROR;
//	table[signals::more][More_or_Equal] = State::ERROR;
//	table[signals::fewer][More_or_Equal] = State::ERROR;
//	table[signals::one_two][More_or_Equal] = A;
//	table[signals::three][More_or_Equal] = A;
//	table[signals::four_six][More_or_Equal] = More_1;
//	table[signals::seven][More_or_Equal] = More_1;
//	table[signals::eight][More_or_Equal] = More_1;
//	table[signals::nine][More_or_Equal] = More_1;
//	table[signals::zero][More_or_Equal] = A;
//	table[signals::H][More_or_Equal] = State::ERROR;
//	table[signals::T][More_or_Equal] = State::ERROR;
//	table[signals::F][More_or_Equal] = State::ERROR;
//	table[signals::I][More_or_Equal] = State::ERROR;
//	table[signals::L][More_or_Equal] = State::ERROR;
//	table[signals::S][More_or_Equal] = State::ERROR;
//	table[signals::E][More_or_Equal] = State::ERROR;
//	table[signals::D][More_or_Equal] = State::ERROR;
//	table[signals::border][More_or_Equal] = State::Final;
//	table[signals::other][More_or_Equal] = ERROR;
//
//	// для A
//	table[signals::N][A] = State::ERROR;
//	table[signals::alpha][A] = State::ERROR;
//	table[signals::equal][A] = State::Equal;
//	table[signals::min][A] = State::Minus;
//	table[signals::plus][A] = State::Plus;
//	table[signals::more][A] = State::More;
//	table[signals::fewer][A] = State::Fewer;
//	table[signals::one_two][A] = B;
//	table[signals::three][A] = More_2;
//	table[signals::four_six][A] = More_2;
//	table[signals::seven][A] = More_2;
//	table[signals::eight][A] = More_2;
//	table[signals::nine][A] = More_2;
//	table[signals::zero][A] = B;
//	table[signals::H][A] = State::ERROR;
//	table[signals::T][A] = State::ERROR;
//	table[signals::F][A] = State::ERROR;
//	table[signals::I][A] = State::ERROR;
//	table[signals::L][A] = State::ERROR;
//	table[signals::S][A] = State::ERROR;
//	table[signals::E][A] = State::ERROR;
//	table[signals::D][A] = State::ERROR;
//	table[signals::border][A] = State::Final;
//	table[signals::other][A] = ERROR;
//
//	// для B
//	table[signals::N][B] = State::ERROR;
//	table[signals::alpha][B] = State::ERROR;
//	table[signals::equal][B] = State::Equal;
//	table[signals::min][B] = State::Minus;
//	table[signals::plus][B] = State::Plus;
//	table[signals::more][B] = State::More;
//	table[signals::fewer][B] = State::Fewer;
//	table[signals::one_two][B] = C;
//	table[signals::three][B] = C;
//	table[signals::four_six][B] = C;
//	table[signals::seven][B] = C;
//	table[signals::eight][B] = More_3;
//	table[signals::nine][B] = More_3;
//	table[signals::zero][B] = C;
//	table[signals::H][B] = State::ERROR;
//	table[signals::T][B] = State::ERROR;
//	table[signals::F][B] = State::ERROR;
//	table[signals::I][B] = State::ERROR;
//	table[signals::L][B] = State::ERROR;
//	table[signals::S][B] = State::ERROR;
//	table[signals::E][B] = State::ERROR;
//	table[signals::D][B] = State::ERROR;
//	table[signals::border][B] = State::Final;
//	table[signals::other][B] = ERROR;
//
//	// для С
//	table[signals::N][C] = State::ERROR;
//	table[signals::alpha][C] = State::ERROR;
//	table[signals::equal][C] = State::Equal;
//	table[signals::min][C] = State::Minus;
//	table[signals::plus][C] = State::Plus;
//	table[signals::more][C] = State::More;
//	table[signals::fewer][C] = State::Fewer;
//	table[signals::one_two][C] = d;
//	table[signals::three][C] = d;
//	table[signals::four_six][C] = d;
//	table[signals::seven][C] = More_4;
//	table[signals::eight][C] = More_4;
//	table[signals::nine][C] = More_4;
//	table[signals::zero][C] = d;
//	table[signals::H][C] = State::ERROR;
//	table[signals::T][C] = State::ERROR;
//	table[signals::F][C] = State::ERROR;
//	table[signals::I][C] = State::ERROR;
//	table[signals::L][C] = State::ERROR;
//	table[signals::S][C] = State::ERROR;
//	table[signals::E][C] = State::ERROR;
//	table[signals::D][C] = State::ERROR;
//	table[signals::border][C] = State::Final;
//	table[signals::other][C] = ERROR;
//
//	// для D
//	table[signals::N][d] = State::ERROR;
//	table[signals::alpha][d] = State::ERROR;
//	table[signals::equal][d] = State::Equal;
//	table[signals::min][d] = State::Minus;
//	table[signals::plus][d] = State::Plus;
//	table[signals::more][d] = State::More;
//	table[signals::fewer][d] = State::Fewer;
//	table[signals::one_two][d] = Last_digit;
//	table[signals::three][d] = Last_digit;
//	table[signals::four_six][d] = Last_digit;
//	table[signals::seven][d] = Last_digit;
//	table[signals::eight][d] = ERROR;
//	table[signals::nine][d] = ERROR;
//	table[signals::zero][d] = Last_digit;
//	table[signals::H][d] = State::ERROR;
//	table[signals::T][d] = State::ERROR;
//	table[signals::F][d] = State::ERROR;
//	table[signals::I][d] = State::ERROR;
//	table[signals::L][d] = State::ERROR;
//	table[signals::S][d] = State::ERROR;
//	table[signals::E][d] = State::ERROR;
//	table[signals::D][d] = State::ERROR;
//	table[signals::border][d] = State::Final;
//	table[signals::other][d] = ERROR;
//
//	// для Minus
//	table[signals::N][Minus] = State::ERROR;
//	table[signals::alpha][Minus] = State::ERROR;
//	table[signals::equal][Minus] = State::ERROR;
//	table[signals::min][Minus] = State::ERROR;
//	table[signals::plus][Minus] = State::ERROR;
//	table[signals::more][Minus] = State::ERROR;
//	table[signals::fewer][Minus] = State::ERROR;
//	table[signals::one_two][Minus] = A_m;
//	table[signals::three][Minus] = More_1;
//	table[signals::four_six][Minus] = More_1;
//	table[signals::seven][Minus] = More_1;
//	table[signals::eight][Minus] = More_1;
//	table[signals::nine][Minus] = More_1;
//	table[signals::zero][Minus] = A_m;
//	table[signals::H][Minus] = State::ERROR;
//	table[signals::T][Minus] = State::ERROR;
//	table[signals::F][Minus] = State::ERROR;
//	table[signals::I][Minus] = State::ERROR;
//	table[signals::L][Minus] = State::ERROR;
//	table[signals::S][Minus] = State::ERROR;
//	table[signals::E][Minus] = State::ERROR;
//	table[signals::D][Minus] = State::ERROR;
//	table[signals::border][Minus] = State::Final;
//	table[signals::other][Minus] = ERROR;
//
//	// для A_minus
//	table[signals::N][A_m] = State::ERROR;
//	table[signals::alpha][A_m] = State::ERROR;
//	table[signals::equal][A_m] = State::ERROR;
//	table[signals::min][A_m] = State::ERROR;
//	table[signals::plus][A_m] = State::ERROR;
//	table[signals::more][A_m] = State::ERROR;
//	table[signals::fewer][A_m] = State::ERROR;
//	table[signals::one_two][A_m] = B_M;
//	table[signals::three][A_m] = More_2;
//	table[signals::four_six][A_m] = More_2;
//	table[signals::seven][A_m] = More_2;
//	table[signals::eight][A_m] = More_2;
//	table[signals::nine][A_m] = More_2;
//	table[signals::zero][A_m] = B_M;
//	table[signals::H][A_m] = State::ERROR;
//	table[signals::T][A_m] = State::ERROR;
//	table[signals::F][A_m] = State::ERROR;
//	table[signals::I][A_m] = State::ERROR;
//	table[signals::L][A_m] = State::ERROR;
//	table[signals::S][A_m] = State::ERROR;
//	table[signals::E][A_m] = State::ERROR;
//	table[signals::D][A_m] = State::ERROR;
//	table[signals::border][A_m] = State::Final;
//	table[signals::other][A_m] = ERROR;
//
//	// для B_minus
//	table[signals::N][B_M] = State::ERROR;
//	table[signals::alpha][B_M] = State::ERROR;
//	table[signals::equal][B_M] = State::ERROR;
//	table[signals::min][B_M] = State::ERROR;
//	table[signals::plus][B_M] = State::ERROR;
//	table[signals::more][B_M] = State::ERROR;
//	table[signals::fewer][B_M] = State::ERROR;
//	table[signals::one_two][B_M] = C_M;
//	table[signals::three][B_M] = C_M;
//	table[signals::four_six][B_M] = C_M;
//	table[signals::seven][B_M] = C_M;
//	table[signals::eight][B_M] = More_3;
//	table[signals::nine][B_M] = More_3;
//	table[signals::zero][B_M] = C_M;
//	table[signals::H][B_M] = State::ERROR;
//	table[signals::T][B_M] = State::ERROR;
//	table[signals::F][B_M] = State::ERROR;
//	table[signals::I][B_M] = State::ERROR;
//	table[signals::L][B_M] = State::ERROR;
//	table[signals::S][B_M] = State::ERROR;
//	table[signals::E][B_M] = State::ERROR;
//	table[signals::D][B_M] = State::ERROR;
//	table[signals::border][B_M] = State::Final;
//	table[signals::other][B_M] = ERROR;
//
//	// для С_minus
//	table[signals::N][C_M] = State::ERROR;
//	table[signals::alpha][C_M] = State::ERROR;
//	table[signals::equal][C_M] = State::ERROR;
//	table[signals::min][C_M] = State::ERROR;
//	table[signals::plus][C_M] = State::ERROR;
//	table[signals::more][C_M] = State::ERROR;
//	table[signals::fewer][C_M] = State::ERROR;
//	table[signals::one_two][C_M] = D_M;
//	table[signals::three][C_M] = D_M;
//	table[signals::four_six][C_M] = D_M;
//	table[signals::seven][C_M] = More_4;
//	table[signals::eight][C_M] = More_4;
//	table[signals::nine][C_M] = More_4;
//	table[signals::zero][C_M] = D_M;
//	table[signals::H][C_M] = State::ERROR;
//	table[signals::T][C_M] = State::ERROR;
//	table[signals::F][C_M] = State::ERROR;
//	table[signals::I][C_M] = State::ERROR;
//	table[signals::L][C_M] = State::ERROR;
//	table[signals::S][C_M] = State::ERROR;
//	table[signals::E][C_M] = State::ERROR;
//	table[signals::D][C_M] = State::ERROR;
//	table[signals::border][C_M] = State::Final;
//	table[signals::other][C_M] = ERROR;
//
//	// для D_minus
//	table[signals::N][D_M] = State::ERROR;
//	table[signals::alpha][D_M] = State::ERROR;
//	table[signals::equal][D_M] = State::ERROR;
//	table[signals::min][D_M] = State::ERROR;
//	table[signals::plus][D_M] = State::ERROR;
//	table[signals::more][D_M] = State::ERROR;
//	table[signals::fewer][D_M] = State::ERROR;
//	table[signals::one_two][D_M] = Last_digit;
//	table[signals::three][D_M] = Last_digit;
//	table[signals::four_six][D_M] = Last_digit;
//	table[signals::seven][D_M] = Last_digit;
//	table[signals::eight][D_M] = Last_digit;
//	table[signals::nine][D_M] = ERROR;
//	table[signals::zero][D_M] = Last_digit;
//	table[signals::H][D_M] = State::ERROR;
//	table[signals::T][D_M] = State::ERROR;
//	table[signals::F][D_M] = State::ERROR;
//	table[signals::I][D_M] = State::ERROR;
//	table[signals::L][D_M] = State::ERROR;
//	table[signals::S][D_M] = State::ERROR;
//	table[signals::E][D_M] = State::ERROR;
//	table[signals::D][D_M] = State::ERROR;
//	table[signals::border][D_M] = State::Final;
//	table[signals::other][D_M] = ERROR;
//
//	// для Last_digit
//	table[signals::N][Last_digit] = State::ERROR;
//	table[signals::alpha][Last_digit] = State::ERROR;
//	table[signals::equal][Last_digit] = State::ERROR;
//	table[signals::min][Last_digit] = State::ERROR;
//	table[signals::plus][Last_digit] = State::ERROR;
//	table[signals::more][Last_digit] = State::ERROR;
//	table[signals::fewer][Last_digit] = State::ERROR;
//	table[signals::one_two][Last_digit] = ERROR;
//	table[signals::three][Last_digit] = ERROR;
//	table[signals::four_six][Last_digit] = ERROR;
//	table[signals::seven][Last_digit] = ERROR;
//	table[signals::eight][Last_digit] = ERROR;
//	table[signals::nine][Last_digit] = ERROR;
//	table[signals::zero][Last_digit] = ERROR;
//	table[signals::H][Last_digit] = State::ERROR;
//	table[signals::T][Last_digit] = State::ERROR;
//	table[signals::F][Last_digit] = State::ERROR;
//	table[signals::I][Last_digit] = State::ERROR;
//	table[signals::L][Last_digit] = State::ERROR;
//	table[signals::S][Last_digit] = State::ERROR;
//	table[signals::E][Last_digit] = State::ERROR;
//	table[signals::D][Last_digit] = State::ERROR;
//	table[signals::border][Last_digit] = State::Final;
//	table[signals::other][Last_digit] = ERROR;
//
//	// для More_1
//	table[signals::N][More_1] = State::ERROR;
//	table[signals::alpha][More_1] = State::ERROR;
//	table[signals::equal][More_1] = State::ERROR;
//	table[signals::min][More_1] = State::ERROR;
//	table[signals::plus][More_1] = State::ERROR;
//	table[signals::more][More_1] = State::ERROR;
//	table[signals::fewer][More_1] = State::ERROR;
//	table[signals::one_two][More_1] = More_2;
//	table[signals::three][More_1] = More_2;
//	table[signals::four_six][More_1] = More_2;
//	table[signals::seven][More_1] = More_2;
//	table[signals::eight][More_1] = More_2;
//	table[signals::nine][More_1] = More_2;
//	table[signals::zero][More_1] = More_2;
//	table[signals::H][More_1] = State::ERROR;
//	table[signals::T][More_1] = State::ERROR;
//	table[signals::F][More_1] = State::ERROR;
//	table[signals::I][More_1] = State::ERROR;
//	table[signals::L][More_1] = State::ERROR;
//	table[signals::S][More_1] = State::ERROR;
//	table[signals::E][More_1] = State::ERROR;
//	table[signals::D][More_1] = State::ERROR;
//	table[signals::border][More_1] = State::Final;
//	table[signals::other][More_1] = ERROR;
//
//	// для More_2
//	table[signals::N][More_2] = State::ERROR;
//	table[signals::alpha][More_2] = State::ERROR;
//	table[signals::equal][More_2] = State::ERROR;
//	table[signals::min][More_2] = State::ERROR;
//	table[signals::plus][More_2] = State::ERROR;
//	table[signals::more][More_2] = State::ERROR;
//	table[signals::fewer][More_2] = State::ERROR;
//	table[signals::one_two][More_2] = More_3;
//	table[signals::three][More_2] = More_3;
//	table[signals::four_six][More_2] = More_3;
//	table[signals::seven][More_2] = More_3;
//	table[signals::eight][More_2] = More_3;
//	table[signals::nine][More_2] = More_3;
//	table[signals::zero][More_2] = More_3;
//	table[signals::H][More_2] = State::ERROR;
//	table[signals::T][More_2] = State::ERROR;
//	table[signals::F][More_2] = State::ERROR;
//	table[signals::I][More_2] = State::ERROR;
//	table[signals::L][More_2] = State::ERROR;
//	table[signals::S][More_2] = State::ERROR;
//	table[signals::E][More_2] = State::ERROR;
//	table[signals::D][More_2] = State::ERROR;
//	table[signals::border][More_2] = State::Final;
//	table[signals::other][More_2] = ERROR;
//
//	// для More_3
//	table[signals::N][More_3] = State::ERROR;
//	table[signals::alpha][More_3] = State::ERROR;
//	table[signals::equal][More_3] = State::ERROR;
//	table[signals::min][More_3] = State::ERROR;
//	table[signals::plus][More_3] = State::ERROR;
//	table[signals::more][More_3] = State::ERROR;
//	table[signals::fewer][More_3] = State::ERROR;
//	table[signals::one_two][More_3] = More_4;
//	table[signals::three][More_3] = More_4;
//	table[signals::four_six][More_3] = More_4;
//	table[signals::seven][More_3] = More_4;
//	table[signals::eight][More_3] = More_4;
//	table[signals::nine][More_3] = More_4;
//	table[signals::zero][More_3] = More_4;
//	table[signals::H][More_3] = State::ERROR;
//	table[signals::T][More_3] = State::ERROR;
//	table[signals::F][More_3] = State::ERROR;
//	table[signals::I][More_3] = State::ERROR;
//	table[signals::L][More_3] = State::ERROR;
//	table[signals::S][More_3] = State::ERROR;
//	table[signals::E][More_3] = State::ERROR;
//	table[signals::D][More_3] = State::ERROR;
//	table[signals::border][More_3] = State::Final;
//	table[signals::other][More_3] = ERROR;
//
//	// для More_4
//	table[signals::N][More_4] = State::ERROR;
//	table[signals::alpha][More_4] = State::ERROR;
//	table[signals::equal][More_4] = State::ERROR;
//	table[signals::min][More_4] = State::ERROR;
//	table[signals::plus][More_4] = State::ERROR;
//	table[signals::more][More_4] = State::ERROR;
//	table[signals::fewer][More_4] = State::ERROR;
//	table[signals::one_two][More_4] = ERROR;
//	table[signals::three][More_4] = ERROR;
//	table[signals::four_six][More_4] = ERROR;
//	table[signals::seven][More_4] = ERROR;
//	table[signals::eight][More_4] = ERROR;
//	table[signals::nine][More_4] = ERROR;
//	table[signals::zero][More_4] = ERROR;
//	table[signals::H][More_4] = State::ERROR;
//	table[signals::T][More_4] = State::ERROR;
//	table[signals::F][More_4] = State::ERROR;
//	table[signals::I][More_4] = State::ERROR;
//	table[signals::L][More_4] = State::ERROR;
//	table[signals::S][More_4] = State::ERROR;
//	table[signals::E][More_4] = State::ERROR;
//	table[signals::D][More_4] = State::ERROR;
//	table[signals::border][More_4] = State::Final;
//	table[signals::other][More_4] = ERROR;
//	
//	// для ERROR
//	table[signals::N][ERROR] = State::ERROR;
//	table[signals::alpha][ERROR] = State::ERROR;
//	table[signals::equal][ERROR] = State::ERROR;
//	table[signals::min][ERROR] = State::ERROR;
//	table[signals::plus][ERROR] = State::ERROR;
//	table[signals::more][ERROR] = State::ERROR;
//	table[signals::fewer][ERROR] = State::ERROR;
//	table[signals::one_two][ERROR] = ERROR;
//	table[signals::three][ERROR] = ERROR;
//	table[signals::four_six][ERROR] = ERROR;
//	table[signals::seven][ERROR] = ERROR;
//	table[signals::eight][ERROR] = ERROR;
//	table[signals::nine][ERROR] = ERROR;
//	table[signals::zero][ERROR] = ERROR;
//	table[signals::H][ERROR] = State::ERROR;
//	table[signals::T][ERROR] = State::ERROR;
//	table[signals::F][ERROR] = State::ERROR;
//	table[signals::I][ERROR] = State::ERROR;
//	table[signals::L][ERROR] = State::ERROR;
//	table[signals::S][ERROR] = State::ERROR;
//	table[signals::E][ERROR] = State::ERROR;
//	table[signals::D][ERROR] = State::ERROR;
//	table[signals::border][ERROR] = State::Final;
//	table[signals::other][ERROR] = ERROR;
//}
//*/
//
//void filling_automat_table(State(&table)[24][40]) {
//	// для S
//	table[signals::I][Start] = State::i;
//	table[signals::T][Start] = State::t;
//	table[signals::E][Start] = State::e;
//	table[signals::alpha][Start] = State::Id_1;
//	table[signals::equal][Start] = State::Equal;
//	table[signals::min][Start] = State::Minus;
//	table[signals::plus][Start] = State::Plus;
//	table[signals::more][Start] = State::More;
//	table[signals::fewer][Start] = State::Fewer;
//	table[signals::one_two][Start] = A;
//	table[signals::three][Start] = A;
//	table[signals::four_six][Start] = More_1;
//	table[signals::seven][Start] = More_1;
//	table[signals::eight][Start] = More_1;
//	table[signals::nine][Start] = More_1;
//	table[signals::F][Start] = Id_1;
//	table[signals::F][Start] = Id_1;
//	table[signals::H][Start] = Id_1;
//	table[signals::L][Start] = Id_1;
//	table[signals::S][Start] = Id_1;
//	table[signals::N][Start] = Id_1;
//	table[signals::D][Start] = Id_1;
//	table[signals::border][Start] = Start;
//	table[signals::other][Start] = ERROR;
//
//	// для T
//	table[signals::H][t] = State::TH;
//	table[signals::alpha][t] = State::Id_2;
//	table[signals::equal][t] = Equal;
//	table[signals::more][t] = More;
//	table[signals::min][t] = Minus;
//	table[signals::plus][t] = Plus;
//	table[signals::fewer][t] = Fewer;
//	table[signals::zero][t] = Id_2;
//	table[signals::one_two][t] = Id_2;
//	table[signals::three][t] = Id_2;
//	table[signals::four_six][t] = Id_2;
//	table[signals::seven][t] = Id_2;
//	table[signals::eight][t] = Id_2;
//	table[signals::nine][t] = Id_2;
//	table[signals::T][t] = Id_2;
//	table[signals::E][t] = Id_2;
//	table[signals::F][t] = Id_2;
//	table[signals::I][t] = Id_2;
//	table[signals::L][t] = Id_2;
//	table[signals::S][t] = Id_2;
//	table[signals::N][t] = Id_2;
//	table[signals::D][t] = Id_2;
//	table[signals::border][t] = State::Final;
//	table[signals::other][t] = ERROR;
//
//	// для TH
//	table[signals::H][TH] = State::TH;
//	table[signals::alpha][TH] = State::Id_3;
//	table[signals::equal][TH] = ERROR;
//	table[signals::more][TH] = ERROR;
//	table[signals::min][TH] = ERROR;
//	table[signals::plus][TH] = ERROR;
//	table[signals::fewer][TH] = ERROR;
//	table[signals::zero][THE] = Id_3;
//	table[signals::one_two][TH] = Id_3;
//	table[signals::three][TH] = Id_3;
//	table[signals::four_six][TH] = Id_3;
//	table[signals::seven][TH] = Id_3;
//	table[signals::eight][TH] = Id_3;
//	table[signals::nine][TH] = Id_3;
//	table[signals::T][TH] = Id_3;
//	table[signals::E][TH] = THE;
//	table[signals::F][TH] = Id_3;
//	table[signals::I][TH] = Id_3;
//	table[signals::L][TH] = Id_3;
//	table[signals::S][TH] = Id_3;
//	table[signals::N][TH] = Id_3;
//	table[signals::D][TH] = Id_3;
//	table[signals::border][TH] = State::Final;
//	table[signals::other][TH] = ERROR;
//
//	// для THE
//	table[signals::N][THE] = State::THEN;
//	table[signals::alpha][THE] = State::Id_4;
//	table[signals::equal][THE] = State::ERROR;
//	table[signals::min][THE] = State::ERROR;
//	table[signals::plus][THE] = State::ERROR;
//	table[signals::more][THE] = State::ERROR;
//	table[signals::fewer][THE] = State::ERROR;
//	table[signals::one_two][THE] = Id_4;
//	table[signals::three][THE] = State::Id_4;
//	table[signals::four_six][THE] = Id_4;
//	table[signals::seven][THE] = Id_4;
//	table[signals::eight][THE] = Id_4;
//	table[signals::nine][THE] = Id_4;
//	table[signals::zero][THE] = Id_4;
//	table[signals::H][THE] = State::Id_4;
//	table[signals::T][THE] = State::Id_4;
//	table[signals::F][THE] = State::Id_4;
//	table[signals::I][THE] = State::Id_4;
//	table[signals::L][THE] = State::Id_4;
//	table[signals::S][THE] = State::Id_4;
//	table[signals::E][THE] = State::Id_4;
//	table[signals::D][THE] = State::Id_4;
//	table[signals::border][THE] = State::Final;
//	table[signals::other][THE] = ERROR;
//
//	// для THEN
//	table[signals::N][THEN] = State::Id_5;
//	table[signals::alpha][THEN] = State::Id_5;
//	table[signals::equal][THEN] = State::ERROR;
//	table[signals::min][THEN] = State::ERROR;
//	table[signals::plus][THEN] = State::ERROR;
//	table[signals::more][THEN] = State::ERROR;
//	table[signals::fewer][THEN] = State::ERROR;
//	table[signals::one_two][THEN] = Id_5;
//	table[signals::three][THEN] = State::Id_5;
//	table[signals::four_six][THEN] = Id_5;
//	table[signals::seven][THEN] = Id_5;
//	table[signals::eight][THEN] = Id_5;
//	table[signals::nine][THEN] = Id_5;
//	table[signals::zero][THEN] = Id_5;
//	table[signals::H][THEN] = State::Id_5;
//	table[signals::T][THEN] = State::Id_5;
//	table[signals::F][THEN] = State::Id_5;
//	table[signals::I][THEN] = State::Id_5;
//	table[signals::L][THEN] = State::Id_5;
//	table[signals::S][THEN] = State::Id_5;
//	table[signals::E][THEN] = State::Id_5;
//	table[signals::D][THEN] = State::Id_5;
//	table[signals::border][THEN] = State::Final;
//	table[signals::other][THEN] = ERROR;
//
//	// для I
//	table[signals::N][i] = State::Id_2;
//	table[signals::alpha][i] = State::Id_2;
//	table[signals::equal][i] = State::Equal;
//	table[signals::min][i] = State::Minus;
//	table[signals::plus][i] = State::Plus;
//	table[signals::more][i] = State::More;
//	table[signals::fewer][i] = State::Fewer;
//	table[signals::one_two][i] = Id_2;
//	table[signals::three][i] = Id_2;
//	table[signals::four_six][i] = Id_2;
//	table[signals::seven][i] = Id_2;
//	table[signals::eight][i] = Id_2;
//	table[signals::nine][i] = Id_2;
//	table[signals::zero][i] = Id_2;
//	table[signals::H][i] = State::Id_2;
//	table[signals::T][i] = State::Id_2;
//	table[signals::F][i] = State::IF;
//	table[signals::I][i] = State::Id_2;
//	table[signals::L][i] = State::Id_2;
//	table[signals::S][i] = State::Id_2;
//	table[signals::E][i] = State::Id_2;
//	table[signals::D][i] = State::Id_2;
//	table[signals::border][i] = State::Final;
//	table[signals::other][i] = ERROR;
//
//	// для IF
//	table[signals::N][IF] = State::Id_3;
//	table[signals::alpha][IF] = State::Id_3;
//	table[signals::equal][IF] = State::ERROR;
//	table[signals::min][IF] = State::ERROR;
//	table[signals::plus][IF] = State::ERROR;
//	table[signals::more][IF] = State::ERROR;
//	table[signals::fewer][IF] = State::ERROR;
//	table[signals::one_two][IF] = Id_3;
//	table[signals::three][IF] = Id_3;
//	table[signals::four_six][IF] = Id_3;
//	table[signals::seven][IF] = Id_3;
//	table[signals::eight][IF] = Id_3;
//	table[signals::nine][IF] = Id_3;
//	table[signals::zero][IF] = Id_3;
//	table[signals::H][IF] = State::Id_3;
//	table[signals::T][IF] = State::Id_3;
//	table[signals::F][IF] = State::Id_3;
//	table[signals::I][IF] = State::Id_3;
//	table[signals::L][IF] = State::Id_3;
//	table[signals::S][IF] = State::Id_3;
//	table[signals::E][IF] = State::Id_3;
//	table[signals::D][IF] = State::Id_3;
//	table[signals::border][IF] = State::Final;
//	table[signals::other][IF] = ERROR;
//
//	// для E
//	table[signals::N][e] = State::EN;
//	table[signals::alpha][e] = State::Id_2;
//	table[signals::equal][e] = State::Equal;
//	table[signals::min][e] = State::Minus;
//	table[signals::plus][e] = State::Plus;
//	table[signals::more][e] = State::More;
//	table[signals::fewer][e] = State::Fewer;
//	table[signals::one_two][e] = Id_2;
//	table[signals::three][e] = Id_2;
//	table[signals::four_six][e] = Id_2;
//	table[signals::seven][e] = Id_2;
//	table[signals::eight][e] = Id_2;
//	table[signals::nine][e] = Id_2;
//	table[signals::zero][e] = Id_2;
//	table[signals::H][e] = State::Id_2;
//	table[signals::T][e] = State::Id_2;
//	table[signals::F][e] = State::Id_2;
//	table[signals::I][e] = State::Id_2;
//	table[signals::L][e] = State::EL;
//	table[signals::S][e] = State::Id_2;
//	table[signals::E][e] = State::Id_2;
//	table[signals::D][e] = State::Id_2;
//	table[signals::border][e] = State::Final;
//	table[signals::other][e] = ERROR;
//
//	// для EN
//	table[signals::N][EN] = State::Id_3;
//	table[signals::alpha][EN] = State::Id_3;
//	table[signals::equal][EN] = State::ERROR;
//	table[signals::min][EN] = State::ERROR;
//	table[signals::plus][EN] = State::ERROR;
//	table[signals::more][EN] = State::ERROR;
//	table[signals::fewer][EN] = State::ERROR;
//	table[signals::one_two][EN] = Id_3;
//	table[signals::three][EN] = Id_3;
//	table[signals::four_six][EN] = Id_3;
//	table[signals::seven][EN] = Id_3;
//	table[signals::eight][EN] = Id_3;
//	table[signals::nine][EN] = Id_3;
//	table[signals::zero][EN] = Id_3;
//	table[signals::H][EN] = State::Id_3;
//	table[signals::T][EN] = State::Id_3;
//	table[signals::F][EN] = State::Id_3;
//	table[signals::I][EN] = State::Id_3;
//	table[signals::L][EN] = State::Id_3;
//	table[signals::S][EN] = State::Id_3;
//	table[signals::E][EN] = State::Id_3;
//	table[signals::D][EN] = State::END;
//	table[signals::border][EN] = State::Final;
//	table[signals::other][EN] = ERROR;
//
//	// для END
//	table[signals::N][END] = State::Id_4;
//	table[signals::alpha][END] = State::Id_4;
//	table[signals::equal][END] = State::ERROR;
//	table[signals::min][END] = State::ERROR;
//	table[signals::plus][END] = State::ERROR;
//	table[signals::more][END] = State::ERROR;
//	table[signals::fewer][END] = State::ERROR;
//	table[signals::one_two][END] = Id_4;
//	table[signals::three][END] = Id_4;
//	table[signals::four_six][END] = Id_4;
//	table[signals::seven][END] = Id_4;
//	table[signals::eight][END] = Id_4;
//	table[signals::nine][END] = Id_4;
//	table[signals::zero][END] = Id_4;
//	table[signals::H][END] = State::Id_4;
//	table[signals::T][END] = State::Id_4;
//	table[signals::F][END] = State::Id_4;
//	table[signals::I][END] = State::Id_4;
//	table[signals::L][END] = State::Id_4;
//	table[signals::S][END] = State::Id_4;
//	table[signals::E][END] = State::Id_4;
//	table[signals::D][END] = State::END;
//	table[signals::border][END] = State::Final;
//	table[signals::other][END] = ERROR;
//
//	// для EL
//	table[signals::N][EL] = State::Id_3;
//	table[signals::alpha][EL] = State::Id_3;
//	table[signals::equal][EL] = State::ERROR;
//	table[signals::min][EL] = State::ERROR;
//	table[signals::plus][EL] = State::ERROR;
//	table[signals::more][EL] = State::ERROR;
//	table[signals::fewer][EL] = State::ERROR;
//	table[signals::one_two][EL] = Id_3;
//	table[signals::three][EL] = Id_3;
//	table[signals::four_six][EL] = Id_3;
//	table[signals::seven][EL] = Id_3;
//	table[signals::eight][EL] = Id_3;
//	table[signals::nine][EL] = Id_3;
//	table[signals::zero][EL] = Id_3;
//	table[signals::H][EL] = State::Id_3;
//	table[signals::T][EL] = State::Id_3;
//	table[signals::F][EL] = State::Id_3;
//	table[signals::I][EL] = State::Id_3;
//	table[signals::L][EL] = State::Id_3;
//	table[signals::S][EL] = State::ELS;
//	table[signals::E][EL] = State::Id_3;
//	table[signals::D][EL] = State::Id_3;
//	table[signals::border][EL] = State::Final;
//	table[signals::other][EL] = ERROR;
//
//	// для ELS
//	table[signals::N][ELS] = State::Id_4;
//	table[signals::alpha][ELS] = State::Id_4;
//	table[signals::equal][ELS] = State::ERROR;
//	table[signals::min][ELS] = State::ERROR;
//	table[signals::plus][ELS] = State::ERROR;
//	table[signals::more][ELS] = State::ERROR;
//	table[signals::fewer][ELS] = State::ERROR;
//	table[signals::one_two][ELS] = Id_4;
//	table[signals::three][ELS] = Id_4;
//	table[signals::four_six][ELS] = Id_4;
//	table[signals::seven][ELS] = Id_4;
//	table[signals::eight][ELS] = Id_4;
//	table[signals::nine][ELS] = Id_4;
//	table[signals::zero][ELS] = Id_4;
//	table[signals::H][ELS] = State::Id_4;
//	table[signals::T][ELS] = State::Id_4;
//	table[signals::F][ELS] = State::Id_4;
//	table[signals::I][ELS] = State::Id_4;
//	table[signals::L][ELS] = State::Id_4;
//	table[signals::S][ELS] = State::Id_4;
//	table[signals::E][ELS] = State::ELSE;
//	table[signals::D][ELS] = State::Id_4;
//	table[signals::border][ELS] = State::Final;
//	table[signals::other][ELS] = ERROR;
//
//	// для ELSE
//	table[signals::N][ELSE] = State::Id_5;
//	table[signals::alpha][ELSE] = State::Id_5;
//	table[signals::equal][ELSE] = State::ERROR;
//	table[signals::min][ELSE] = State::ERROR;
//	table[signals::plus][ELSE] = State::ERROR;
//	table[signals::more][ELSE] = State::ERROR;
//	table[signals::fewer][ELSE] = State::ERROR;
//	table[signals::one_two][ELSE] = Id_5;
//	table[signals::three][ELSE] = Id_5;
//	table[signals::four_six][ELSE] = Id_5;
//	table[signals::seven][ELSE] = Id_5;
//	table[signals::eight][ELSE] = Id_5;
//	table[signals::nine][ELSE] = Id_5;
//	table[signals::zero][ELSE] = Id_5;
//	table[signals::H][ELSE] = State::Id_5;
//	table[signals::T][ELSE] = State::Id_5;
//	table[signals::F][ELSE] = State::Id_5;
//	table[signals::I][ELSE] = State::Id_5;
//	table[signals::L][ELSE] = State::Id_5;
//	table[signals::S][ELSE] = State::Id_5;
//	table[signals::E][ELSE] = State::Id_5;
//	table[signals::D][ELSE] = State::Id_5;
//	table[signals::border][ELSE] = State::Final;
//	table[signals::other][ELSE] = ERROR;
//
//	// Id_1
//	table[signals::N][Id_1] = State::Id_2;
//	table[signals::alpha][Id_1] = State::Id_2;
//	table[signals::equal][Id_1] = State::Equal;
//	table[signals::min][Id_1] = State::Minus;
//	table[signals::plus][Id_1] = State::Plus;
//	table[signals::more][Id_1] = State::More;
//	table[signals::fewer][Id_1] = State::Fewer;
//	table[signals::one_two][Id_1] = Id_2;
//	table[signals::three][Id_1] = Id_2;
//	table[signals::four_six][Id_1] = Id_2;
//	table[signals::seven][Id_1] = Id_2;
//	table[signals::eight][Id_1] = Id_2;
//	table[signals::nine][Id_1] = Id_2;
//	table[signals::zero][Id_1] = Id_2;
//	table[signals::H][Id_1] = State::Id_2;
//	table[signals::T][Id_1] = State::Id_2;
//	table[signals::F][Id_1] = State::Id_2;
//	table[signals::I][Id_1] = State::Id_2;
//	table[signals::L][Id_1] = State::Id_2;
//	table[signals::S][Id_1] = State::Id_2;
//	table[signals::E][Id_1] = State::Id_2;
//	table[signals::D][Id_1] = State::Id_2;
//	table[signals::border][Id_1] = State::Final;
//	table[signals::other][Id_1] = ERROR;
//
//	// для Id_2
//	table[signals::N][Id_2] = State::Id_3;
//	table[signals::alpha][Id_2] = State::Id_3;
//	table[signals::equal][Id_2] = State::Equal;
//	table[signals::min][Id_2] = State::Minus;
//	table[signals::plus][Id_2] = State::Plus;
//	table[signals::more][Id_2] = State::More;
//	table[signals::fewer][Id_2] = State::Fewer;
//	table[signals::one_two][Id_2] = Id_3;
//	table[signals::three][Id_2] = Id_3;
//	table[signals::four_six][Id_2] = Id_3;
//	table[signals::seven][Id_2] = Id_3;
//	table[signals::eight][Id_2] = Id_3;
//	table[signals::nine][Id_2] = Id_3;
//	table[signals::zero][Id_2] = Id_3;
//	table[signals::H][Id_2] = State::Id_3;
//	table[signals::T][Id_2] = State::Id_3;
//	table[signals::F][Id_2] = State::Id_3;
//	table[signals::I][Id_2] = State::Id_3;
//	table[signals::L][Id_2] = State::Id_3;
//	table[signals::S][Id_2] = State::Id_3;
//	table[signals::E][Id_2] = State::Id_3;
//	table[signals::D][Id_2] = State::Id_3;
//	table[signals::border][Id_2] = State::Final;
//	table[signals::other][Id_2] = ERROR;
//
//	// для Id_3
//	table[signals::N][Id_3] = State::Id_4;
//	table[signals::alpha][Id_3] = State::Id_4;
//	table[signals::equal][Id_3] = State::Equal;
//	table[signals::min][Id_3] = State::Minus;
//	table[signals::plus][Id_3] = State::Plus;
//	table[signals::more][Id_3] = State::More;
//	table[signals::fewer][Id_3] = State::Fewer;
//	table[signals::one_two][Id_3] = Id_4;
//	table[signals::three][Id_3] = Id_4;
//	table[signals::four_six][Id_3] = Id_4;
//	table[signals::seven][Id_3] = Id_4;
//	table[signals::eight][Id_3] = Id_4;
//	table[signals::nine][Id_3] = Id_4;
//	table[signals::zero][Id_3] = Id_4;
//	table[signals::H][Id_3] = State::Id_4;
//	table[signals::T][Id_3] = State::Id_4;
//	table[signals::F][Id_3] = State::Id_4;
//	table[signals::I][Id_3] = State::Id_4;
//	table[signals::L][Id_3] = State::Id_4;
//	table[signals::S][Id_3] = State::Id_4;
//	table[signals::E][Id_3] = State::Id_4;
//	table[signals::D][Id_3] = State::Id_4;
//	table[signals::border][Id_3] = State::Final;
//	table[signals::other][Id_3] = ERROR;
//
//	// для Id_4
//	table[signals::N][Id_4] = State::Id_5;
//	table[signals::alpha][Id_4] = State::Id_5;
//	table[signals::equal][Id_4] = State::Equal;
//	table[signals::min][Id_4] = State::Minus;
//	table[signals::plus][Id_4] = State::Plus;
//	table[signals::more][Id_4] = State::More;
//	table[signals::fewer][Id_4] = State::Fewer;
//	table[signals::one_two][Id_4] = Id_5;
//	table[signals::three][Id_4] = Id_5;
//	table[signals::four_six][Id_4] = Id_5;
//	table[signals::seven][Id_4] = Id_5;
//	table[signals::eight][Id_4] = Id_5;
//	table[signals::nine][Id_4] = Id_5;
//	table[signals::zero][Id_4] = Id_5;
//	table[signals::H][Id_4] = State::Id_5;
//	table[signals::T][Id_4] = State::Id_5;
//	table[signals::F][Id_4] = State::Id_5;
//	table[signals::I][Id_4] = State::Id_5;
//	table[signals::L][Id_4] = State::Id_5;
//	table[signals::S][Id_4] = State::Id_5;
//	table[signals::E][Id_4] = State::Id_5;
//	table[signals::D][Id_4] = State::Id_5;
//	table[signals::border][Id_4] = State::Final;
//	table[signals::other][Id_4] = ERROR;
//
//	// для Id_5
//	table[signals::N][Id_5] = State::ERROR;
//	table[signals::alpha][Id_5] = State::ERROR;
//	table[signals::equal][Id_5] = State::Equal;
//	table[signals::min][Id_5] = State::Minus;
//	table[signals::plus][Id_5] = State::Plus;
//	table[signals::more][Id_5] = State::More;
//	table[signals::fewer][Id_5] = State::Fewer;
//	table[signals::one_two][Id_5] = ERROR;
//	table[signals::three][Id_5] = ERROR;
//	table[signals::four_six][Id_5] = ERROR;
//	table[signals::seven][Id_5] = ERROR;
//	table[signals::eight][Id_5] = ERROR;
//	table[signals::nine][Id_5] = ERROR;
//	table[signals::zero][Id_5] = ERROR;
//	table[signals::H][Id_5] = State::ERROR;
//	table[signals::T][Id_5] = State::ERROR;
//	table[signals::F][Id_5] = State::ERROR;
//	table[signals::I][Id_5] = State::ERROR;
//	table[signals::L][Id_5] = State::ERROR;
//	table[signals::S][Id_5] = State::ERROR;
//	table[signals::E][Id_5] = State::ERROR;
//	table[signals::D][Id_5] = State::ERROR;
//	table[signals::border][Id_5] = State::Final;
//	table[signals::other][Id_5] = ERROR;
//
//	// для Plus
//	table[signals::N][Plus] = State::Id_1;
//	table[signals::alpha][Plus] = State::Id_1;
//	table[signals::equal][Plus] = State::ERROR;
//	table[signals::min][Plus] = State::Minus;
//	table[signals::plus][Plus] = State::Plus;
//	table[signals::more][Plus] = State::ERROR;
//	table[signals::fewer][Plus] = State::ERROR;
//	table[signals::one_two][Plus] = A;
//	table[signals::three][Plus] = A;
//	table[signals::four_six][Plus] = More_1;
//	table[signals::seven][Plus] = More_1;
//	table[signals::eight][Plus] = More_1;
//	table[signals::nine][Plus] = More_1;
//	table[signals::zero][Plus] = A;
//	table[signals::H][Plus] = State::Id_1;
//	table[signals::T][Plus] = State::t;
//	table[signals::F][Plus] = State::Id_1;
//	table[signals::I][Plus] = State::i;
//	table[signals::L][Plus] = State::Id_1;
//	table[signals::S][Plus] = State::Id_1;
//	table[signals::E][Plus] = State::e;
//	table[signals::D][Plus] = State::Id_1;
//	table[signals::border][Plus] = State::Final;
//	table[signals::other][Plus] = ERROR;
//
//	// для Equal
//	table[signals::N][Equal] = State::Id_1;
//	table[signals::alpha][Equal] = State::Id_1;
//	table[signals::equal][Equal] = State::Equal;
//	table[signals::min][Equal] = State::Minus;
//	table[signals::plus][Equal] = State::Plus;
//	table[signals::more][Equal] = State::ERROR;
//	table[signals::fewer][Equal] = State::ERROR;
//	table[signals::one_two][Equal] = A;
//	table[signals::three][Equal] = A;
//	table[signals::four_six][Equal] = More_1;
//	table[signals::seven][Equal] = More_1;
//	table[signals::eight][Equal] = More_1;
//	table[signals::nine][Equal] = More_1;
//	table[signals::zero][Equal] = A;
//	table[signals::H][Equal] = State::Id_1;
//	table[signals::T][Equal] = State::t;
//	table[signals::F][Equal] = State::Id_1;
//	table[signals::I][Equal] = State::i;
//	table[signals::L][Equal] = State::Id_1;
//	table[signals::S][Equal] = State::Id_1;
//	table[signals::E][Equal] = State::e;
//	table[signals::D][Equal] = State::Id_1;
//	table[signals::border][Equal] = State::Final;
//	table[signals::other][Equal] = ERROR;
//
//	// для Fewer
//	table[signals::N][Fewer] = State::Id_1;
//	table[signals::alpha][Fewer] = State::Id_1;
//	table[signals::equal][Fewer] = State::Fewer_or_Equal;
//	table[signals::min][Fewer] = State::Minus;
//	table[signals::plus][Fewer] = State::ERROR;
//	table[signals::more][Fewer] = State::ERROR;
//	table[signals::fewer][Fewer] = State::ERROR;
//	table[signals::one_two][Fewer] = A;
//	table[signals::three][Fewer] = A;
//	table[signals::four_six][Fewer] = More_1;
//	table[signals::seven][Fewer] = More_1;
//	table[signals::eight][Fewer] = More_1;
//	table[signals::nine][Fewer] = More_1;
//	table[signals::zero][Fewer] = A;
//	table[signals::H][Fewer] = State::Id_1;
//	table[signals::T][Fewer] = State::t;
//	table[signals::F][Fewer] = State::Id_1;
//	table[signals::I][Fewer] = State::i;
//	table[signals::L][Fewer] = State::Id_1;
//	table[signals::S][Fewer] = State::Id_1;
//	table[signals::E][Fewer] = State::e;
//	table[signals::D][Fewer] = State::Id_1;
//	table[signals::border][Fewer] = State::Final;
//	table[signals::other][Fewer] = ERROR;
//
//	// для Fewer_or_Equal
//	table[signals::N][Fewer_or_Equal] = State::Id_1;
//	table[signals::alpha][Fewer_or_Equal] = State::Id_1;
//	table[signals::equal][Fewer_or_Equal] = State::ERROR;
//	table[signals::min][Fewer_or_Equal] = State::Minus;
//	table[signals::plus][Fewer_or_Equal] = State::Plus;
//	table[signals::more][Fewer_or_Equal] = State::ERROR;
//	table[signals::fewer][Fewer_or_Equal] = State::ERROR;
//	table[signals::one_two][Fewer_or_Equal] = A;
//	table[signals::three][Fewer_or_Equal] = A;
//	table[signals::four_six][Fewer_or_Equal] = More_1;
//	table[signals::seven][Fewer_or_Equal] = More_1;
//	table[signals::eight][Fewer_or_Equal] = More_1;
//	table[signals::nine][Fewer_or_Equal] = More_1;
//	table[signals::zero][Fewer_or_Equal] = A;
//	table[signals::H][Fewer_or_Equal] = State::Id_1;
//	table[signals::T][Fewer_or_Equal] = State::t;
//	table[signals::F][Fewer_or_Equal] = State::Id_1;
//	table[signals::I][Fewer_or_Equal] = State::i;
//	table[signals::L][Fewer_or_Equal] = State::Id_1;
//	table[signals::S][Fewer_or_Equal] = State::Id_1;
//	table[signals::E][Fewer_or_Equal] = State::e;
//	table[signals::D][Fewer_or_Equal] = State::Id_1;
//	table[signals::border][Fewer_or_Equal] = State::Final;
//	table[signals::other][Fewer_or_Equal] = ERROR;
//
//	// для More
//	table[signals::N][More] = State::Id_1;
//	table[signals::alpha][More] = State::Id_1;
//	table[signals::equal][More] = State::More_or_Equal;
//	table[signals::min][More] = State::Minus;
//	table[signals::plus][More] = State::Plus;
//	table[signals::more][More] = State::ERROR;
//	table[signals::fewer][More] = State::ERROR;
//	table[signals::one_two][More] = A;
//	table[signals::three][More] = A;
//	table[signals::four_six][More] = More_1;
//	table[signals::seven][More] = More_1;
//	table[signals::eight][More] = More_1;
//	table[signals::nine][More] = More_1;
//	table[signals::zero][More] = A;
//	table[signals::H][More] = State::Id_1;
//	table[signals::T][More] = State::t;
//	table[signals::F][More] = State::Id_1;
//	table[signals::I][More] = State::i;
//	table[signals::L][More] = State::Id_1;
//	table[signals::S][More] = State::Id_1;
//	table[signals::E][More] = State::e;
//	table[signals::D][More] = State::Id_1;
//	table[signals::border][More] = State::Final;
//	table[signals::other][More] = ERROR;
//
//	// для More_or_Equal
//	table[signals::N][More_or_Equal] = State::Id_1;
//	table[signals::alpha][More_or_Equal] = State::Id_1;
//	table[signals::equal][More_or_Equal] = State::ERROR;
//	table[signals::min][More_or_Equal] = State::Minus;
//	table[signals::plus][More_or_Equal] = State::Plus;
//	table[signals::more][More_or_Equal] = State::ERROR;
//	table[signals::fewer][More_or_Equal] = State::ERROR;
//	table[signals::one_two][More_or_Equal] = A;
//	table[signals::three][More_or_Equal] = A;
//	table[signals::four_six][More_or_Equal] = More_1;
//	table[signals::seven][More_or_Equal] = More_1;
//	table[signals::eight][More_or_Equal] = More_1;
//	table[signals::nine][More_or_Equal] = More_1;
//	table[signals::zero][More_or_Equal] = A;
//	table[signals::H][More_or_Equal] = State::Id_1;
//	table[signals::T][More_or_Equal] = State::t;
//	table[signals::F][More_or_Equal] = State::Id_1;
//	table[signals::I][More_or_Equal] = State::i;
//	table[signals::L][More_or_Equal] = State::Id_1;
//	table[signals::S][More_or_Equal] = State::Id_1;
//	table[signals::E][More_or_Equal] = State::e;
//	table[signals::D][More_or_Equal] = State::Id_1;
//	table[signals::border][More_or_Equal] = State::Final;
//	table[signals::other][More_or_Equal] = ERROR;
//
//	// для A
//	table[signals::N][A] = State::ERROR;
//	table[signals::alpha][A] = State::ERROR;
//	table[signals::equal][A] = State::Equal;
//	table[signals::min][A] = State::Minus;
//	table[signals::plus][A] = State::Plus;
//	table[signals::more][A] = State::More;
//	table[signals::fewer][A] = State::Fewer;
//	table[signals::one_two][A] = B;
//	table[signals::three][A] = More_2;
//	table[signals::four_six][A] = More_2;
//	table[signals::seven][A] = More_2;
//	table[signals::eight][A] = More_2;
//	table[signals::nine][A] = More_2;
//	table[signals::zero][A] = B;
//	table[signals::H][A] = State::ERROR;
//	table[signals::T][A] = State::ERROR;
//	table[signals::F][A] = State::ERROR;
//	table[signals::I][A] = State::ERROR;
//	table[signals::L][A] = State::ERROR;
//	table[signals::S][A] = State::ERROR;
//	table[signals::E][A] = State::ERROR;
//	table[signals::D][A] = State::ERROR;
//	table[signals::border][A] = State::Final;
//	table[signals::other][A] = ERROR;
//
//	// для B
//	table[signals::N][B] = State::ERROR;
//	table[signals::alpha][B] = State::ERROR;
//	table[signals::equal][B] = State::Equal;
//	table[signals::min][B] = State::Minus;
//	table[signals::plus][B] = State::Plus;
//	table[signals::more][B] = State::More;
//	table[signals::fewer][B] = State::Fewer;
//	table[signals::one_two][B] = C;
//	table[signals::three][B] = C;
//	table[signals::four_six][B] = C;
//	table[signals::seven][B] = C;
//	table[signals::eight][B] = More_3;
//	table[signals::nine][B] = More_3;
//	table[signals::zero][B] = C;
//	table[signals::H][B] = State::ERROR;
//	table[signals::T][B] = State::ERROR;
//	table[signals::F][B] = State::ERROR;
//	table[signals::I][B] = State::ERROR;
//	table[signals::L][B] = State::ERROR;
//	table[signals::S][B] = State::ERROR;
//	table[signals::E][B] = State::ERROR;
//	table[signals::D][B] = State::ERROR;
//	table[signals::border][B] = State::Final;
//	table[signals::other][B] = ERROR;
//
//	// для С
//	table[signals::N][C] = State::ERROR;
//	table[signals::alpha][C] = State::ERROR;
//	table[signals::equal][C] = State::Equal;
//	table[signals::min][C] = State::Minus;
//	table[signals::plus][C] = State::Plus;
//	table[signals::more][C] = State::More;
//	table[signals::fewer][C] = State::Fewer;
//	table[signals::one_two][C] = d;
//	table[signals::three][C] = d;
//	table[signals::four_six][C] = d;
//	table[signals::seven][C] = More_4;
//	table[signals::eight][C] = More_4;
//	table[signals::nine][C] = More_4;
//	table[signals::zero][C] = d;
//	table[signals::H][C] = State::ERROR;
//	table[signals::T][C] = State::ERROR;
//	table[signals::F][C] = State::ERROR;
//	table[signals::I][C] = State::ERROR;
//	table[signals::L][C] = State::ERROR;
//	table[signals::S][C] = State::ERROR;
//	table[signals::E][C] = State::ERROR;
//	table[signals::D][C] = State::ERROR;
//	table[signals::border][C] = State::Final;
//	table[signals::other][C] = ERROR;
//
//	// для D
//	table[signals::N][d] = State::ERROR;
//	table[signals::alpha][d] = State::ERROR;
//	table[signals::equal][d] = State::Equal;
//	table[signals::min][d] = State::Minus;
//	table[signals::plus][d] = State::Plus;
//	table[signals::more][d] = State::More;
//	table[signals::fewer][d] = State::Fewer;
//	table[signals::one_two][d] = Last_digit;
//	table[signals::three][d] = Last_digit;
//	table[signals::four_six][d] = Last_digit;
//	table[signals::seven][d] = Last_digit;
//	table[signals::eight][d] = ERROR;
//	table[signals::nine][d] = ERROR;
//	table[signals::zero][d] = Last_digit;
//	table[signals::H][d] = State::ERROR;
//	table[signals::T][d] = State::ERROR;
//	table[signals::F][d] = State::ERROR;
//	table[signals::I][d] = State::ERROR;
//	table[signals::L][d] = State::ERROR;
//	table[signals::S][d] = State::ERROR;
//	table[signals::E][d] = State::ERROR;
//	table[signals::D][d] = State::ERROR;
//	table[signals::border][d] = State::Final;
//	table[signals::other][d] = ERROR;
//
//	// для Minus
//	table[signals::N][Minus] = State::Id_1;
//	table[signals::alpha][Minus] = State::Id_1;
//	table[signals::equal][Minus] = State::ERROR;
//	table[signals::min][Minus] = State::Minus;
//	table[signals::plus][Minus] = State::Plus;
//	table[signals::more][Minus] = State::ERROR;
//	table[signals::fewer][Minus] = State::ERROR;
//	table[signals::one_two][Minus] = A;
//	table[signals::three][Minus] = A;
//	table[signals::four_six][Minus] = More_1;
//	table[signals::seven][Minus] = More_1;
//	table[signals::eight][Minus] = More_1;
//	table[signals::nine][Minus] = More_1;
//	table[signals::zero][Minus] = A;
//	table[signals::H][Minus] = State::Id_1;
//	table[signals::T][Minus] = State::t;
//	table[signals::F][Minus] = State::Id_1;
//	table[signals::I][Minus] = State::i;
//	table[signals::L][Minus] = State::Id_1;
//	table[signals::S][Minus] = State::Id_1;
//	table[signals::E][Minus] = State::e;
//	table[signals::D][Minus] = State::Id_1;
//	table[signals::border][Minus] = State::Final;
//	table[signals::other][Minus] = ERROR;
//
//	// для Last_digit
//	table[signals::N][Last_digit] = State::ERROR;
//	table[signals::alpha][Last_digit] = State::ERROR;
//	table[signals::equal][Last_digit] = State::Equal;
//	table[signals::min][Last_digit] = State::Minus;
//	table[signals::plus][Last_digit] = State::Plus;
//	table[signals::more][Last_digit] = State::More;
//	table[signals::fewer][Last_digit] = State::Fewer;
//	table[signals::one_two][Last_digit] = ERROR;
//	table[signals::three][Last_digit] = ERROR;
//	table[signals::four_six][Last_digit] = ERROR;
//	table[signals::seven][Last_digit] = ERROR;
//	table[signals::eight][Last_digit] = ERROR;
//	table[signals::nine][Last_digit] = ERROR;
//	table[signals::zero][Last_digit] = ERROR;
//	table[signals::H][Last_digit] = State::ERROR;
//	table[signals::T][Last_digit] = State::ERROR;
//	table[signals::F][Last_digit] = State::ERROR;
//	table[signals::I][Last_digit] = State::ERROR;
//	table[signals::L][Last_digit] = State::ERROR;
//	table[signals::S][Last_digit] = State::ERROR;
//	table[signals::E][Last_digit] = State::ERROR;
//	table[signals::D][Last_digit] = State::ERROR;
//	table[signals::border][Last_digit] = State::Final;
//	table[signals::other][Last_digit] = ERROR;
//
//	// для More_1
//	table[signals::N][More_1] = State::ERROR;
//	table[signals::alpha][More_1] = State::ERROR;
//	table[signals::equal][More_1] = State::Equal;
//	table[signals::min][More_1] = State::Minus;
//	table[signals::plus][More_1] = State::Plus;
//	table[signals::more][More_1] = State::More;
//	table[signals::fewer][More_1] = State::Fewer;
//	table[signals::one_two][More_1] = More_2;
//	table[signals::three][More_1] = More_2;
//	table[signals::four_six][More_1] = More_2;
//	table[signals::seven][More_1] = More_2;
//	table[signals::eight][More_1] = More_2;
//	table[signals::nine][More_1] = More_2;
//	table[signals::zero][More_1] = More_2;
//	table[signals::H][More_1] = State::ERROR;
//	table[signals::T][More_1] = State::ERROR;
//	table[signals::F][More_1] = State::ERROR;
//	table[signals::I][More_1] = State::ERROR;
//	table[signals::L][More_1] = State::ERROR;
//	table[signals::S][More_1] = State::ERROR;
//	table[signals::E][More_1] = State::ERROR;
//	table[signals::D][More_1] = State::ERROR;
//	table[signals::border][More_1] = State::Final;
//	table[signals::other][More_1] = ERROR;
//
//	// для More_2
//	table[signals::N][More_2] = State::ERROR;
//	table[signals::alpha][More_2] = State::ERROR;
//	table[signals::equal][More_2] = State::Equal;
//	table[signals::min][More_2] = State::Minus;
//	table[signals::plus][More_2] = State::Plus;
//	table[signals::more][More_2] = State::More;
//	table[signals::fewer][More_2] = State::Fewer;
//	table[signals::one_two][More_2] = More_3;
//	table[signals::three][More_2] = More_3;
//	table[signals::four_six][More_2] = More_3;
//	table[signals::seven][More_2] = More_3;
//	table[signals::eight][More_2] = More_3;
//	table[signals::nine][More_2] = More_3;
//	table[signals::zero][More_2] = More_3;
//	table[signals::H][More_2] = State::ERROR;
//	table[signals::T][More_2] = State::ERROR;
//	table[signals::F][More_2] = State::ERROR;
//	table[signals::I][More_2] = State::ERROR;
//	table[signals::L][More_2] = State::ERROR;
//	table[signals::S][More_2] = State::ERROR;
//	table[signals::E][More_2] = State::ERROR;
//	table[signals::D][More_2] = State::ERROR;
//	table[signals::border][More_2] = State::Final;
//	table[signals::other][More_2] = ERROR;
//
//	// для More_3
//	table[signals::N][More_3] = State::ERROR;
//	table[signals::alpha][More_3] = State::ERROR;
//	table[signals::equal][More_3] = State::Equal;
//	table[signals::min][More_3] = State::Minus;
//	table[signals::plus][More_3] = State::Plus;
//	table[signals::more][More_3] = State::More;
//	table[signals::fewer][More_3] = State::Fewer;
//	table[signals::one_two][More_3] = More_4;
//	table[signals::three][More_3] = More_4;
//	table[signals::four_six][More_3] = More_4;
//	table[signals::seven][More_3] = More_4;
//	table[signals::eight][More_3] = More_4;
//	table[signals::nine][More_3] = More_4;
//	table[signals::zero][More_3] = More_4;
//	table[signals::H][More_3] = State::ERROR;
//	table[signals::T][More_3] = State::ERROR;
//	table[signals::F][More_3] = State::ERROR;
//	table[signals::I][More_3] = State::ERROR;
//	table[signals::L][More_3] = State::ERROR;
//	table[signals::S][More_3] = State::ERROR;
//	table[signals::E][More_3] = State::ERROR;
//	table[signals::D][More_3] = State::ERROR;
//	table[signals::border][More_3] = State::Final;
//	table[signals::other][More_3] = ERROR;
//
//	// для More_4
//	table[signals::N][More_4] = State::ERROR;
//	table[signals::alpha][More_4] = State::ERROR;
//	table[signals::equal][More_4] = State::Equal;
//	table[signals::min][More_4] = State::Minus;
//	table[signals::plus][More_4] = State::Plus;
//	table[signals::more][More_4] = State::More;
//	table[signals::fewer][More_4] = State::Fewer;
//	table[signals::one_two][More_4] = ERROR;
//	table[signals::three][More_4] = ERROR;
//	table[signals::four_six][More_4] = ERROR;
//	table[signals::seven][More_4] = ERROR;
//	table[signals::eight][More_4] = ERROR;
//	table[signals::nine][More_4] = ERROR;
//	table[signals::zero][More_4] = ERROR;
//	table[signals::H][More_4] = State::ERROR;
//	table[signals::T][More_4] = State::ERROR;
//	table[signals::F][More_4] = State::ERROR;
//	table[signals::I][More_4] = State::ERROR;
//	table[signals::L][More_4] = State::ERROR;
//	table[signals::S][More_4] = State::ERROR;
//	table[signals::E][More_4] = State::ERROR;
//	table[signals::D][More_4] = State::ERROR;
//	table[signals::border][More_4] = State::Final;
//	table[signals::other][More_4] = ERROR;
//
//	// для ERROR
//	table[signals::N][ERROR] = State::ERROR;
//	table[signals::alpha][ERROR] = State::ERROR;
//	table[signals::equal][ERROR] = State::ERROR;
//	table[signals::min][ERROR] = State::ERROR;
//	table[signals::plus][ERROR] = State::ERROR;
//	table[signals::more][ERROR] = State::ERROR;
//	table[signals::fewer][ERROR] = State::ERROR;
//	table[signals::one_two][ERROR] = ERROR;
//	table[signals::three][ERROR] = ERROR;
//	table[signals::four_six][ERROR] = ERROR;
//	table[signals::seven][ERROR] = ERROR;
//	table[signals::eight][ERROR] = ERROR;
//	table[signals::nine][ERROR] = ERROR;
//	table[signals::zero][ERROR] = ERROR;
//	table[signals::H][ERROR] = State::ERROR;
//	table[signals::T][ERROR] = State::ERROR;
//	table[signals::F][ERROR] = State::ERROR;
//	table[signals::I][ERROR] = State::ERROR;
//	table[signals::L][ERROR] = State::ERROR;
//	table[signals::S][ERROR] = State::ERROR;
//	table[signals::E][ERROR] = State::ERROR;
//	table[signals::D][ERROR] = State::ERROR;
//	table[signals::border][ERROR] = State::Final;
//	table[signals::other][ERROR] = ERROR;
//}
//
//
//int Get_File_size(ifstream& in) { // узнаём размер файла
//	in.seekg(1, std::ios::end);
//	return in.tellg();
//}
//
//int read_file(ifstream& in, char*& mass) {
//	int sz = Get_File_size(in);
//	in.seekg(0, std::ios::beg);
//	mass = new char[sz];
//	in.getline(mass, sz, '\0');
//	return sz;
//}
//
//lex_type Get_Lex_Type(State st) {
//	if (st == State::t || st == State::TH || st == State::THE || st == State::e || st == State::EL
//		|| st == State::ELS || st == State::i || st == State::Id_1 || st == State::Id_2 ||
//		st == State::Id_3 || st == State::Id_4 || st == State::Id_5) return id;
//
//	else if (st == State::Minus || st == State::Plus) return ao;
//
//	else if (st == State::THEN || st == State::ELSE || st == State::END || st == State::IF) return kw;
//
//	else if (st == State::More || st == State::Fewer || st == State::More_or_Equal || st == State::Fewer_or_Equal) return co;
//
//	else if (st == State::Equal) return eq;
//
//	else if (st == State::A || st == State::B || st == State::C || st == State::d || st == State::A_m
//		|| st == State::B_M || st == State::C_M || st == State::D_M || st == State::More_1
//		|| st == State::More_2 || st == State::More_3 || st == State::More_4
//		|| st == State::Last_digit) return vl;
//
//	else if (st == State::ERROR) return wl;
//}
//
//void Lex_analys(vector<Lex>& res, char* mass, State table[24][40], int mass_sz) {
//	Lex lex{};
//	State cur = Start, prev;
//	char marker;
//	int counter = 0, counter_prev = 0;
//	while (counter != mass_sz) {
//		prev = cur;
//		marker = mass[counter];
//		if (cur == State::Start && (marker == ' ' || marker == '\n' || marker == '\t')) {
//			marker = mass[++counter];
//			++counter_prev;
//		}
//
//		cur = table[get_signal(marker)][cur];
//
//		if (cur == State::Final) {
//			int size = counter - counter_prev;
//			lex.mass = new char[size + 1];
//			strncpy(lex.mass, &mass[0] + counter_prev, size);
//			lex.mass[size] = '\0';
//			lex.type = Get_Lex_Type(prev);
//			res.push_back(lex);
//			cur = State::Start;
//			counter_prev = (marker == ' ' || marker == '\t' || marker == '\n' ? counter + 1 : counter);
//		}
//		else if ((cur == State::Equal || cur == State::More || cur == State::Fewer || cur == State::Plus || cur == State::Minus)
//			&&( prev == State::A || prev == State::B || prev == State::C
//			|| prev == State::d || prev == State::More_1 || prev == State::More_2
//			|| prev == State::More_3 || prev == State::More_4 || prev == State::Last_digit))
//		{ // 12 < || + || - || = || >
//			int size = counter - counter_prev;
//			lex.mass = new char[size + 1];
//			strncpy(lex.mass, &mass[0] + counter_prev, size);
//			lex.mass[size] = '\0';
//			lex.type = Get_Lex_Type(prev);
//			res.push_back(lex);
//			counter_prev = (marker == ' ' || marker == '\t' || marker == '\n' ? counter + 1 : counter);
//		}
//		else if ((prev == State::Equal || prev == State::More || prev == State::Fewer || prev == State::Plus 
//			|| prev == State::Minus || prev == State::More_or_Equal || prev == State::Fewer_or_Equal)
//			&&( cur == State::A || cur == State::B || cur == State::C
//			|| cur == State::d || cur == State::More_1 || cur == State::More_2
//			|| cur == State::More_3 || cur == State::More_4 || cur == State::Last_digit))
//		{ 
//			int size = counter - counter_prev;
//			lex.mass = new char[size + 1];
//			strncpy(lex.mass, &mass[0] + counter_prev, size);
//			lex.mass[size] = '\0';
//			lex.type = Get_Lex_Type(prev);
//			res.push_back(lex);
//			counter_prev = (marker == ' ' || marker == '\t' || marker == '\n' ? counter + 1 : counter);
//		}
//		else if ((cur == State::Equal || cur == State::More || cur == State::Fewer || cur == State::Plus || cur == State::Minus)
//			&& (prev == State::Id_1 || prev == State::Id_2 || prev == State::Id_3
//			|| prev == State::Id_4 || prev == State::Id_5 || prev == State::i || prev == State::IF
//			|| prev == State::e || prev == State::EL || prev == State::ELS
//			|| prev == State::ELSE || prev == State::EN || prev == State::END ||
//			prev == State::t || prev == State::TH || prev == State::THE || prev == State::THEN))
//		{ // 12 < || + || - || = || >
//			int size = counter - counter_prev;
//			lex.mass = new char[size + 1];
//			strncpy(lex.mass, &mass[0] + counter_prev, size);
//			lex.mass[size] = '\0';
//			lex.type = Get_Lex_Type(prev);
//			res.push_back(lex);
//			counter_prev = (marker == ' ' || marker == '\t' || marker == '\n' ? counter + 1 : counter);
//		}
//		else if ((prev == State::Equal || prev == State::More || prev == State::Fewer || prev == State::Plus || prev == State::Minus
//			|| prev == State::More_or_Equal || prev == State::Fewer_or_Equal)
//			&&( cur == State::Id_1 || cur == State::Id_2 || cur == State::Id_3
//			|| cur == State::Id_4 || cur == State::Id_5 || cur == State::i || cur == State::IF
//			|| cur == State::e || cur == State::EL || cur == State::ELS
//			|| cur == State::ELSE || cur == State::EN || cur == State::END
//			|| cur == State::t || cur == State::TH || cur == State::THE || cur == State::THEN))
//		{
//			int size = counter - counter_prev;
//			lex.mass = new char[size + 1];
//			strncpy(lex.mass, &mass[0] + counter_prev, size);
//			lex.mass[size] = '\0';
//			lex.type = Get_Lex_Type(prev);
//			res.push_back(lex);
//			counter_prev = (marker == ' ' || marker == '\t' || marker == '\n' ? counter + 1 : counter);
//
//		}
//		else if ((prev == State::Equal || prev == State::More || prev == State::Fewer || prev == State::Plus || prev == State::Minus
//			|| prev == State::More_or_Equal || prev == State::Fewer_or_Equal)
//			&& (cur == Plus || cur == State::Minus || cur  == State::Equal))
//		{
//			int size = counter - counter_prev;
//			lex.mass = new char[size + 1];
//			strncpy(lex.mass, &mass[0] + counter_prev, size);
//			lex.mass[size] = '\0';
//			lex.type = Get_Lex_Type(prev);
//			res.push_back(lex);
//			counter_prev = (marker == ' ' || marker == '\t' || marker == '\n' ? counter + 1 : counter);
//		}
//		++counter;
//	}
//}
//
//void writln(ofstream& out, vector<Lex>& vec) {
//	static const char* str[] = { "kw", "id", "vl", "co", "ao", "eq", "wl" };
//	for (std::vector<Lex>::size_type j = 0; j < vec.size(); ++j)
//		out << vec[j].mass << '[' << str[vec[j].type] << ']' << (j != vec.size() - 1? ' ': '\n');
//	vector<Lex> idenificator, constant;
//	for (std::vector<Lex>::size_type j = 0; j < vec.size(); ++j) {
//		if (vec[j].type == 1)
//			idenificator.push_back(vec[j]);
//		else if (vec[j].type == 2)
//			constant.push_back(vec[j]);
//	}
//	for (std::vector<Lex>::size_type j = 0; j < idenificator.size(); ++j)
//		out << idenificator[j].mass << (j != idenificator.size() - 1 ? ' ' : '\n');
//
//	for(std::vector<Lex>::size_type j = 0; j < constant.size(); ++j)
//		out << constant[j].mass << ' ';
//}
//
//int main() {
//	ifstream in("input.txt"); // читаем из файла
//	char* mass;
//	int mass_sz = read_file(in, mass);
//	in.close();
//	vector<Lex> res;
//	State table[24][40];
//	filling_automat_table(table);
//	Lex_analys(res, mass, table, mass_sz);
//	ofstream out("output.txt");
//	writln(out, res);
//	out.close();
//	return 0;
//}