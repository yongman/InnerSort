/*************************************************************************
	> File Name: innnersort.cpp
	> Author: MingYan
	> Mail: yming0221@gmail.com 
	> Created Time: Sun 16 Mar 2014 03:26:27 PM CST
 ************************************************************************/

#include<iostream>
#include "innersort.h"
#include<vector>
#include<algorithm>

using namespace std;

static void exchange(int &a,int &b)
{
    int tmp;
    tmp = a;a = b;b = tmp;
}
//构造函数
InnerSort::InnerSort()
{
    for(int i=0;i<size;i++)
        array.push_back(i);
    //随机洗牌
    random_shuffle(array.begin()+1,array.end());
    for(int i=1;i<size;++i)
        cout<<array[i]<<" ";
    cout<<endl;
}

//插入排序
void InnerSort::insert_sort()
{
    for(int i = 2;i < size;++i)
    {
        if(array[i] < array[i - 1])
        {
           //设置哨兵
            array[0] = array[i];
            int j;
            for(j = i - 1;array[j] > array[0];--j)
            {
                array[j + 1] = array[j];
            }
            array[j + 1] = array[0];    
        }
    }
}


static void shell_Insert(vector<int> &array,int delta)
{
    for(int i = 1 + delta;i < size;++i)
    {
        if(array[i] < array[i - delta])
        {
            array[0] = array[i];//暂存数据
            int j;
            for(j = i - delta;j>0 && array[0] < array[j];j-=delta)
            {
                array[j + delta] = array[j];
            }
            array[j + delta] = array[0];
        }
    }
}
//希尔排序(多次进行插入排序)
void InnerSort::shell_sort(int seq[],int n)
{
    for(int i=0;i<n;i++)
        shell_Insert(array,seq[i]);//以序列seq进行一趟希尔插入排序
}


//快速排序
static int Partition(vector<int> &array,int low,int high)
{
    array[0] = array[low];//暂存
    while(low < high)
    {
        while(low < high && array[0] <= array[high]) --high;
        exchange(array[low],array[high]);//可以优化
        while(low < high && array[0] >= array[low]) ++low;
        exchange(array[low],array[high]);//可以优化
    }
    return low;//low == high
}
void InnerSort::quicksort(int low,int high)
{
    if(low < high)
    {
        int pivot = Partition(array,low,high);
        quicksort(low,pivot - 1);
        quicksort(pivot + 1,high);
    }
}

//选择排序
static int select_the_min_index(const vector<int> &array,int start)
{
    int min = 999999;//代表最小
    int pos = -1;

    for(int i = start;i < size;++i)
    {
        if(min > array[i])
        {
            min = array[i];
            pos = i;
        }
    }
    return pos;
}

void InnerSort::select_sort()
{
    for(int i = 1;i<size;i++)
    {
        int theminindex = select_the_min_index(array,i);
        if(theminindex != i)
            exchange(array[i],array[theminindex]);
    }
}

//堆排序
//i:以i为跟节点的树进行堆调整
//len:当前的堆的大小[1...len-1]
static void HeapAjust(vector<int> &array,int i,int len)
{
    //本函数用于进行调整以i为根节点的树，并且除了i节点以外，左右子树都已经满足了
    //堆的性质，所以只需要沿着根节点的较小的子节点进行向下筛选即可。
    
    int rc = array[i];
    int k;
    for(k = i*2;k < len-1;k *= 2)
    {
        //选择子节点中较大的节点
        if(k < len - 1 && array[k] < array[k + 1])
            k++;
        //找到合适的插入位置
        if(rc > array[k] && rc > array[k + 1])
            break;

        array[k/2] = array[k]; 
    }
    array[k/2] = rc;

}
void InnerSort::heap_sort()
{
    //首先从叶子到根进行堆调整
    for(int i = size/2;i > 0;--i)
    {
        HeapAjust(array,i,size);//调整以i为根的子树
    }

    //将[i]与[1]交换，得到最大的元素，将新的树进行堆调整
    for(int i = size - 1;i > 1;--i)
    {
        //交换堆顶和最后一个叶子节点
        swap(array[1],array[i]);
        //交换节点后的树可能不再满足大根堆的性质，需要进行以1为根节点的堆调整，堆的大小也相应减1
        HeapAjust(array,1,i);
    }
}

int main()
{
    InnerSort is;
    
    int seq[] = {5,4,3,1};
    //is.insert_sort();
    //is.shell_sort(seq,4);
    //is.quicksort(1,size - 1);
    //is.select_sort();
    is.heap_sort();
    for(int i=1;i<size;++i)
    {
        cout<<is.array[i]<<" ";
    }
    cout<<endl;
}
