//#include<iostream>
//#include<vector>
//
//using namespace std;
//
//void inserting(vector<int> vec, int left, int right, int value) {
//	bool flag = true;
//	while (left != right - 1 && flag) {
//		int mid = (right + left) / 2;
//
//		if (vec[mid] > value)
//			right = mid;
//		else if (vec[mid] < value)
//			left = mid;
//		else
//			flag = false;
//	}
//	if (flag) {
//		std::swap(vec[], vec[]);
//	}
//}
//
//void Insertion_Sort(vector<int>& vec) {
//	int k = 1;
//	for (; k < vec.size(); ++k) {
//		inserting(vec, 0, k, vec[k]);
//	}
//}
//
//int main() {
//	vector<int> vec;
//	return 0;
//}