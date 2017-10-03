My Sorts
#include<stdio.h>
#include<stdlib.h>
void InsertSort( int a[] )		//插入排序 
{
	int i, j, tmp;
	for( i = 1; i<9; i++ ) {
		if( a[i]<a[i-1] ) {
			tmp = a[i];
			for( j = i-1; j>=0 && tmp<a[j]; j-- ) 
				a[j+1] = a[j];
			a[j+1] = tmp;
		}
	}
}
void ShellSort( int a[], int len )	//希尔排序 
{
	int i, j, k;
	int s = 1;
	int deta[10];
	for( i = 0; i<10; i++ ) {
		if( s == 1 )
			deta[i] = 1;
		else deta[i] = s +1;
		s *= 2;
	}
	int cnt = 3;
	for( k = deta[cnt]; k>0; k = deta[--cnt] ) {
		for( i = k; i<len; i++ ) {
			if( a[i]<a[i-k] ) {
				int tmp = a[i];
				for( j = i-k; j>=0 && tmp<a[j]; j -= k )
					a[j+k] = a[j];
				a[j+k] = tmp;
			}
		}
	}
}
void QuickSort( int a[], int low, int high)	//快排 
{
	int l = low, h = high;
	if( l<h ) {
		int tmp = a[low];
		while( l<h ) {
			while( l<h && tmp<a[h] )
				h--;
			if( l<h ) {
				a[l] = a[h];
				l++;
			}
			while( l<h && tmp>a[l])
				l++;
			if( l<h ){
				a[h] = a[l];
				h--;
			}
		}
		a[l] = tmp;
		QuickSort( a, low, l-1);
		QuickSort( a, l+1, high );
	}
}
void MergeSort( int a[], int b[], int low, int high )	//归并排序 
{	void Merge(int*, int*, int, int, int);
	if( low<high ) {
		int mid = ( low+high )/2;
		MergeSort(a, b, low, mid);
		MergeSort( a, b, mid+1, high );
		Merge(a, b, low, mid, high);
	}
}  
void Merge( int a[], int b[], int l, int m, int h )	//归并俩数列 
{
	int k = l, i = l, j = m+1; 
	while( i<=m && j<=h ) {
		if( a[i]<a[j] )
			b[k++] = a[i++];
		else
			b[k++] = a[j++];
	}
	while( i <= m ) b[k++] = a[i++];
	while( j <= h ) b[k++] = a[j++];
	for( i = l; i<=h; i++ )		//关键步骤 
		a[i] = b[i];
}
void HeapAdjust( int a[], int i, int len)	//建立大顶堆 
{
	int j;
	int tmp = a[i];
	j = 2*i;
	while( j<=len ) {
		if( j<len && a[j]<a[j+1])
			j++;		//指向关键字大的孩子 
		if( a[j]>tmp ) {
			a[i] = a[j];
			i = j;
			j = 2*i;
		}
		else 
			break; 
	}
	a[i] = tmp;
}
void HeapSort( int a[], int len )	//堆排序 
{
	int i, j;
	for( i = len/2; i>0; i-- )
		HeapAdjust( a, i, len );	//建立大顶堆 
	for( i = len; i>1; i-- ) {
		int tmp = a[1];
		a[1] = a[i];
		a[i] = tmp;
		HeapAdjust(a, 1, i-1); 
	} 
}
int GetNum( int x, int n )		//获取指定位的数 
{
	int a;
	while( n!= 0 ) {
		a = x%10;		 
		x /= 10;
		n--;
	}
	return a;
}
void RadixSort( int a[], int len )	//基数排序 
{
	int que[10][len], rear[10], front[10];
	int ipos, jpos, i, k;			//ipos行坐标，jpos列坐标 
	for( i = 0; i<10; i++ )
		front[i] = rear[i] = 0;		//初始化队列 
		
	for( k = 1; k<=3; k++ ) {
		for( i = 0; i<len; i++ ) {
			ipos = GetNum(a[i], k);
			jpos = rear[ipos]++;
			que[ipos][jpos] = a[i];
		}
		i = 0;
		for( ipos = 0; ipos<10; ipos++ ) {
			while( front[ipos] != rear[ipos] ) {
				jpos = front[ipos]++;
				a[i++] = que[ipos][jpos];
			}
		}
		for( i = 0; i<10; i++ )
			rear[i] = front[i] = 0;		//一趟排序之后队列初始化 
	}
}
int main()
{
	int a[] = { 8, 49, 38, 65, 97, 76, 13, 27, 49 };
	int b[10] = { 278, 109, 63, 930, 589, 184, 505, 269, 8, 83 };
//	int b[9];
//	InsertSort( a ); 
//	ShellSort( a, 9 );
//	QuickSort( a, 0, 9 );
//	MergeSort( a, b, 0 ,8 ); 
//	HeapSort( a, 8 );
	RadixSort(b, 10);
	for( int i = 0; i<10; i++ )
		printf("%d ", b[i]);
	putchar(10);
	return 0;
}
