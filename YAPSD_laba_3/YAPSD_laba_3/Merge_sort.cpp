//#include<iostream>
//#include<vector>
//
//using std::vector;
//
//void Merge(vector<int>& vec, int left, int middle, int right) {
//	if (right == left + 1) {
//		if(vec[left] > vec[right])
//			std::swap(vec[left], vec[right]);
//		for (int i = left; i <= right; i++)
//			std::cout << vec[i] << ' ';
//		std::cout << '\n';
//		return;
//	}
//	
//	vector<int> a, b;
//	for (int i = 0; i <= middle; ++i)
//		a.push_back(vec[i]);
//	for (int i = middle + 1; i <= right; ++i)
//		b.push_back(vec[i]);
//
//	int ptr_a = 0, ptr_b = 0, ptr_c = 0;
//
//	while (ptr_a < a.size() && ptr_b < b.size())
//	{
//		if (a[ptr_a] <= b[ptr_b]) {
//			vec[ptr_c] = a[ptr_a];
//			++ptr_a;
//		}
//		else {
//			vec[ptr_c] = b[ptr_b];
//			++ptr_b;
//		}
//		++ptr_c;
//	}
//	while (ptr_a < a.size()) {
//		vec[ptr_c++] = a[ptr_a++];
//	}
//	while (ptr_b < b.size())
//		vec[ptr_c++] = b[ptr_b++];
//	for (int i = left; i < right; ++i)
//		std::cout << vec[i] << ' ';
//	std::cout << '\n';
//}
//
//void Merge_Sort(vector<int>& vec, int left, int right) {
//	if (right <= left)
//		return;
//	int middle = left + (right - left) / 2;
//	Merge_Sort(vec, left, middle);
//	Merge_Sort(vec, middle + 1, right);
//	Merge(vec, left, middle, right);
//}
//
//int main() {
//	vector<int> vec{ 10, 15, 1, 3, 14, 2 };
//	Merge_Sort(vec, 0, vec.size() - 1);
//	for (int i = 0; i < vec.size(); i++)
//		std::cout << vec[i] << ' ';
//	return 0;
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//#define N 6
//
//// ���������� ��� ��������������� ���������� `arr[low�mid]` � `arr[mid+1�high]`
//void Merge(int arr[], int aux[], int low, int mid, int high)
//{
//    int k = low, i = low, j = mid + 1;
//
//    // ���� ���� �������� � ����� � ������ ��������
//    while (i <= mid && j <= high)
//    {
//        if (arr[i] <= arr[j]) {
//            aux[k++] = arr[i++];
//        }
//        else {
//            aux[k++] = arr[j++];
//        }
//    }
//
//    // �������� ���������� ��������
//    while (i <= mid) {
//        aux[k++] = arr[i++];
//    }
//
//    // ������ �������� ���������� �� ����� (��������� ��������� ��������
//    // ��� ��������� �� ����� ���������� ����� �� ��������������� �������)
//
//    // �������� ������� � �������� ������, ����� �������� ������� ����������
//    for (int i = low; i <= high; i++) {
//        arr[i] = aux[i];
//    }
//}
//
//// ��������� ������ `arr[low�high]`, ��������� ��������������� ������ `aux`
//void mergesort(int arr[], int aux[], int low, int high)
//{
//    // ������� �������
//    if (high == low) {        // ���� ������ ������� == 1
//        return;
//    }
//
//    // ����� ��������
//    int mid = (low + ((high - low) >> 1));
//
//    // ����������� ���������� ����������� �� ��� �������� �� ��� ���, ���� ������ ���������� �� ������ == 1,
//    // ����� ���������� �� � ������������ ����� �� ������� �������
//
//    mergesort(arr, aux, low, mid);          // ���������/���������� ����� ��������
//    mergesort(arr, aux, mid + 1, high);     // ���������/���������� ������ ��������
//
//    Merge(arr, aux, low, mid, high);        // ���������� ��� �����������.
//}
//
//// ������� ��� ��������, ������������ �� arr � ������� ����������� ��� ���
//int isSorted(int arr[])
//{
//    int prev = arr[0];
//    for (int i = 1; i < N; i++)
//    {
//        if (prev > arr[i])
//        {
//            printf("MergeSort Fails!!");
//            return 0;
//        }
//        prev = arr[i];
//    }
//
//    return 1;
//}
//
//// ���������� ��������� ���������� �������� �� C
//int main(void)
//{
//    int arr[] = {10, 15, 1, 3, 14, 2}, aux[] = {10, 15, 1, 3, 14, 2};
//    srand(time(NULL));
//
//    // ���������� ��������� ���� ����� �����
//    //for (int i = 0; i < N; i++) {
//    //    aux[i] = arr[i] = (rand() % 100) - 50;
//    //}
//
//    // ��������� ������ `arr`, ��������� ��������������� ������ `aux`
//    mergesort(arr, aux, 0, N - 1);
//
//    if (isSorted(arr))
//    {
//        for (int i = 0; i < N; i++) {
//            printf("%d ", arr[i]);
//        }
//    }
//
//    return 0;
//}