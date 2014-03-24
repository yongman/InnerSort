/*************************************************************************
	> File Name: innersort.h
	> Author: MingYan
	> Mail: yming0221@gmail.com 
	> Created Time: Sun 16 Mar 2014 03:18:36 PM CST
 ************************************************************************/
#ifndef INNERSORT_H
#define INNERSORT_H

#include<iostream>
#include<vector>
using namespace std;
const int size = 8;

class InnerSort
{
public:
    vector<int> array;//数据从1开始存储，0留作他用
    InnerSort();
    void insert_sort();
    void bubble_sort();
    void select_sort();
    void shell_sort(int seq[],int n);
    void quicksort(int low,int high);
    void heap_sort();
    void merge_sort();
    void radix_sort();
};


#endif
