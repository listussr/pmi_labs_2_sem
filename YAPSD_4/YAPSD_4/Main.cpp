#include<fstream>
#include<map>

#define nnnull nullptr // повышаем удобство написания кода
#define void_ void
using std::ifstream;
using std::ofstream;

typedef std::pair<int, bool> pair_; 
/*
	первое значение в паре отвечает за кол-во элементов конкретного значения в дереве,
	второе значение является флагом, который устанавливается при первом обнаружении в дереве конкретного элемента
	=> при флаге == 1 и кол-вом значений > 1, следующий элемент с этим значением будет считаться повторным
*/
typedef std::map<int, pair_> dictoinary_;
/*
	в словаре хранятся все числа, попавшие в дерево с кол-вом своих повторений и флагом повторения
*/

struct derevo { // структура бинарного дерева поиска
	derevo* left, * right;
	int val;

	derevo(); // конструкторы
	derevo(derevo&);
	derevo(int);

	~derevo();

	void_ push_node(derevo*, int); // добавление вершины в дерево

	void_ set_root(int); // установка корня

	void_ deleting_repetitions(derevo*, dictoinary_); // процедура из задания

	friend ofstream& operator<<(std::ofstream&, derevo*); // перегрузка оператора вывода

	derevo* get_root_ptr(); // функция, возвращающая корень дерева
};

derevo::derevo() {
	val = 0;
	left = right = nnnull;
}

derevo::derevo(int value_for_creating_our_new_node) {
	val = value_for_creating_our_new_node;
	left = right = nnnull;
}

derevo::derevo(derevo& old_binary_searching_tree) {
	left = old_binary_searching_tree.left;
	right = old_binary_searching_tree.right;
	val = old_binary_searching_tree.val;
}

derevo::~derevo() {}

void_ derevo::set_root(int r) {
	val = r;
	left = right = nnnull;
}

void_ derevo::deleting_repetitions(derevo* root, dictoinary_ map) {
	if (!root) // выход из рекурсии
		return;
	if (root->left) {
		dictoinary_::iterator iter = map.find(root->left->val); // ищем в словаре значение вершины и кол-во её повторов

		if (iter->second.second && iter->second.first > 1) { // смотрим на то сколько раз встречается число и было ли оно уже встречено в дереве

			if (root->left->left && !root->left->right) { // есть левый сын, но нет правого
				derevo* buf = root->left->left;
				root->left = nnnull;
				delete root->left;
				root->left = buf;
			}
			else if (!root->left->left && root->left->right) { // есть правый сын, но нет левого
				derevo* buf = root->left->right;
				root->left = nnnull;
				delete root->left;
				root->left = buf;
			}
			else if (!root->left->left && !root->left->right) { // нет ни одного сына
				delete root->left;
				root->left = nnnull;
			}
			--iter->second.first;
			deleting_repetitions(root, map); // смотрим на тот случай, если мы опять прикрепили повтор к дереву
		}
		else
			iter->second.second = 1; // ставим флаг того, что это число уже найдено в дереве
	}
	if (root->right) { // делаем то же самое, но уже с правым потомком
		dictoinary_::iterator iter = map.find(root->right->val);
		if (iter->second.second && iter->second.first > 1) {
			if (root->right->left && !root->right->right) {
				derevo* buf = root->right->left;
				delete root->right;
				root->right = buf;
			}
			else if (!root->right->left && root->right->right) {
				derevo* buf = root->right->right;
				delete root->right;
				root->right = buf;
			}
			else if (!root->right->left && !root->right->right) {
				delete root->right;
				root->right = nnnull;
			}
			--iter->second.first;
			deleting_repetitions(root, map);
		}
		else {
			iter->second.second = 1;
		}
	}
	deleting_repetitions(root->left, map); // рекурсивный обход дерева
	deleting_repetitions(root->right, map);
}

void_ derevo::push_node(derevo* versh, int pushing_val) { // рекурсивная вставка элемента в дерево
	if (pushing_val > versh->val && !versh->right) {
		derevo* new_node = new derevo(pushing_val);
		versh->right = new_node;
	}
	else if (pushing_val <= versh->val && !versh->left) {
		derevo* new_node = new derevo(pushing_val);
		versh->left = new_node;
	}
	else if (pushing_val > versh->val)
		push_node(versh->right, pushing_val);
	else if (pushing_val <= versh->val)
		push_node(versh->left, pushing_val);
}

derevo* derevo::get_root_ptr() { // возврат указателя на корень дерева или поддерева
	return this;
}

ofstream& operator<<(ofstream& operator_out, derevo* tree) { // перегрузка оператора вывода
	operator_out << tree->val;
	return operator_out;
}

void print_tree(ofstream& out, derevo* tree) { // симметричный обход дерева
	if (!tree)
		return;
	print_tree(out, tree->left);
	out << tree << ' ';
	print_tree(out, tree->right);
}

void_ filling_binary_tree(ifstream& in, derevo* tree, dictoinary_& map) { // заполнение дерева
	int el;
	in >> el;
	pair_ counters(1, 1); 
	std::pair<int, pair_> pair(el, counters); // добавляем значение вершины в словарь 
	map.insert(pair);
	counters.second = 0;
	dictoinary_::iterator iter;
	(*tree).set_root(el); // устанавливаем корневой элемент
	while (in >> el) {
		(*tree).push_node(tree, el); // добавляем в дерево элементы

		iter = map.find(el); // смотрим был ли уже встречен элемент с этим же значением
		if (iter != map.end()) // если да, то инкрементируем значение кол-ва элементов в словаре
			++iter->second.first;
		else { // иначе вставляем элемент в словарь
			pair.first = el;
			pair.second = counters;
			map.insert(pair);
		}
	}
}

void_ delete_tree(derevo*& root) { // очистка памяти из-под дерева
	if (!root)
		return;
	if (root) {
		delete_tree(root->left);
		delete_tree(root->right);
		delete root;
		root = nnnull;
	}
}

int main()
{
	derevo* tree = new derevo;
	dictoinary_ map;
	ifstream in("input.txt");
	filling_binary_tree(in, tree, map);
	in.close();
	(*tree).deleting_repetitions(tree, map);
	ofstream out("output.txt");
	print_tree(out, tree);
	out.close();
	delete_tree(tree);
	delete tree;
	map.clear();
	return 0;
}