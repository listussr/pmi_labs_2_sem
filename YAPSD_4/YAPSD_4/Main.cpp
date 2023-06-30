#include<fstream>
#include<map>

#define nnnull nullptr // �������� �������� ��������� ����
#define void_ void
using std::ifstream;
using std::ofstream;

typedef std::pair<int, bool> pair_; 
/*
	������ �������� � ���� �������� �� ���-�� ��������� ����������� �������� � ������,
	������ �������� �������� ������, ������� ��������������� ��� ������ ����������� � ������ ����������� ��������
	=> ��� ����� == 1 � ���-��� �������� > 1, ��������� ������� � ���� ��������� ����� ��������� ���������
*/
typedef std::map<int, pair_> dictoinary_;
/*
	� ������� �������� ��� �����, �������� � ������ � ���-��� ����� ���������� � ������ ����������
*/

struct derevo { // ��������� ��������� ������ ������
	derevo* left, * right;
	int val;

	derevo(); // ������������
	derevo(derevo&);
	derevo(int);

	~derevo();

	void_ push_node(derevo*, int); // ���������� ������� � ������

	void_ set_root(int); // ��������� �����

	void_ deleting_repetitions(derevo*, dictoinary_); // ��������� �� �������

	friend ofstream& operator<<(std::ofstream&, derevo*); // ���������� ��������� ������

	derevo* get_root_ptr(); // �������, ������������ ������ ������
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
	if (!root) // ����� �� ��������
		return;
	if (root->left) {
		dictoinary_::iterator iter = map.find(root->left->val); // ���� � ������� �������� ������� � ���-�� � ��������

		if (iter->second.second && iter->second.first > 1) { // ������� �� �� ������� ��� ����������� ����� � ���� �� ��� ��� ��������� � ������

			if (root->left->left && !root->left->right) { // ���� ����� ���, �� ��� �������
				derevo* buf = root->left->left;
				root->left = nnnull;
				delete root->left;
				root->left = buf;
			}
			else if (!root->left->left && root->left->right) { // ���� ������ ���, �� ��� ������
				derevo* buf = root->left->right;
				root->left = nnnull;
				delete root->left;
				root->left = buf;
			}
			else if (!root->left->left && !root->left->right) { // ��� �� ������ ����
				delete root->left;
				root->left = nnnull;
			}
			--iter->second.first;
			deleting_repetitions(root, map); // ������� �� ��� ������, ���� �� ����� ���������� ������ � ������
		}
		else
			iter->second.second = 1; // ������ ���� ����, ��� ��� ����� ��� ������� � ������
	}
	if (root->right) { // ������ �� �� �����, �� ��� � ������ ��������
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
	deleting_repetitions(root->left, map); // ����������� ����� ������
	deleting_repetitions(root->right, map);
}

void_ derevo::push_node(derevo* versh, int pushing_val) { // ����������� ������� �������� � ������
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

derevo* derevo::get_root_ptr() { // ������� ��������� �� ������ ������ ��� ���������
	return this;
}

ofstream& operator<<(ofstream& operator_out, derevo* tree) { // ���������� ��������� ������
	operator_out << tree->val;
	return operator_out;
}

void print_tree(ofstream& out, derevo* tree) { // ������������ ����� ������
	if (!tree)
		return;
	print_tree(out, tree->left);
	out << tree << ' ';
	print_tree(out, tree->right);
}

void_ filling_binary_tree(ifstream& in, derevo* tree, dictoinary_& map) { // ���������� ������
	int el;
	in >> el;
	pair_ counters(1, 1); 
	std::pair<int, pair_> pair(el, counters); // ��������� �������� ������� � ������� 
	map.insert(pair);
	counters.second = 0;
	dictoinary_::iterator iter;
	(*tree).set_root(el); // ������������� �������� �������
	while (in >> el) {
		(*tree).push_node(tree, el); // ��������� � ������ ��������

		iter = map.find(el); // ������� ��� �� ��� �������� ������� � ���� �� ���������
		if (iter != map.end()) // ���� ��, �� �������������� �������� ���-�� ��������� � �������
			++iter->second.first;
		else { // ����� ��������� ������� � �������
			pair.first = el;
			pair.second = counters;
			map.insert(pair);
		}
	}
}

void_ delete_tree(derevo*& root) { // ������� ������ ��-��� ������
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