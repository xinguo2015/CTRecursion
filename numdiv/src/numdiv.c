#include <stdio.h>
#include <stdlib.h>
#include "numdiv.h"

/*! 输出p中的划分 */
void outputPrefix(int p[], int n)
{
	int k;
	for( k=0; k<n; k++)
		printf("%d ", p[k]);
}

/*! 输出 n 个 1 */
void outputOnes(int n)
{
	int k;
	for( k=0; k<n; k++)
		printf("%d ", 1);
}

/***************************************************
 *
 * 定义f(n,m)为n的，各项都<=m的，所有划分构成的集合。
 * 那么f(n,n)为n的所有划分构成的集合。
 * 注意函数f的值都是集合，每一个集合元素是一个划分组合。
 *
 * 根据定义，f(n,m)可以分为两个子集：f1和f2，
 * 其中f1里面的划分满足：各项<=m-1；
 *     f2里面的划分都至少有一项等于m。
 * 注意，根据定义有f1 = f(n,m-1)。而f2可以表示为：
 *     f2 = {{m}} X f(n-m,m)
 * 其中 X 表示两个集合的乘积. 例如：
 *     {{a}} X {{b},{c}} = {{a,b},{a,c}}
 *
 * (可以证明，f1和f2没有交集，而且f = f1 U f2）
 *
 * 因此，我们有如下的递推通式
 *      f(n,m) = {{m}} X f(n-m,m) U f(n,m-1)
 * 其中 U 表示集合的并操作,
 *
 * 考虑整数n,m的大小关系和特殊情况，我们有：
 * f(n,m) =	when m=1, {{11...1}} // n个1
 *			when n=1, {{1}}      // n个1
 *			when n<m, f(n,n)
 *			when n=m, {{m}} U f(n,m-1)
 *			when n>m, {{m}} X f(n-m,m) U f(n,m-1)
 */

/***************************************************
 *
 *  @brief     一个深度优先的数字分解算法
 *  @return    不同的分解的数量
 *  
 *  这是一个递归实现，利用一个前缀参数prefix[],将上层
 *  的分解传递给下层。
 */
int divide(int prefix[], int d, int n, int m)
{
	int f1, f2;
	if( m==1 || n==1)
	{
		/*! combination: {n个1} */
		outputPrefix(prefix, d);
		outputOnes(n);
		printf("\n");
		return 1;
	}
	else if( n<=m )
	{
		/*! combination {n} */
		outputPrefix(prefix,d);
		printf("%d \n", n);
		/*! combinations with m=n-1 */
		return 1 + divide(prefix,d,n,n-1);
	}
	/*! case: n>m */
	prefix[d] = m;
	f2 = divide(prefix,d+1,n-m,m);
	f1 = divide(prefix,d,n,m-1);
	return (f1+f2);
}


/***************************************************************
 *
 * 定义g(n,m)为n的，各项都>=m的，所有划分构成的集合。
 * 那么g(n,1)为n的所有划分构成的集合。
 * 注意函数f的值都是集合，每一个集合元素是一个划分组合。
 *
 * 根据定义，g(n,m)可以分为两个子集：g1和g2，
 * 其中g1里面的划分满足：各项>=m+1；
 *     g2里面的划分都至少有一项等于m。
 * 注意，根据定义有g1 = f(n,m+1)。而g2可以表示为：
 *     g2 = {{m}} X f(n-m,m)
 * 其中 X 表示两个集合的乘积. 例如：
 *     {{a}} X {{b},{c}} = {{a,b},{a,c}}
 *
 * (可以证明，g1和g2没有交集，而且g = g1 U g2）
 *
 * 因此，我们有如下的递推通式
 *      g(n,m) = {{m}} X g(n-m,m) U g(n,m+1)
 * 其中 U 表示集合的并操作,
 *
 * 考虑整数n,m的大小关系和特殊情况，我们有：
 * g(n,m) =	when m=n, {{n}}
 *			when m>n, 空
 *			when n>m, {{m}} X g(n-m,m) U g(n,m+1)
 */
int gdiv(int prefix[], int d, int n, int m)
{
	int f1, f2;
	if( m>n ) /*! case: m>n ) */
		return 0;
	else if( m==n ) /*! case: m=n ) */
	{
		outputPrefix(prefix, d);
		printf("%d \n", n);
		return 1;
	}
	/*! case: n > m */
	prefix[d] = m;
	f2 = gdiv(prefix,d+1,n-m,m);
	f1 = gdiv(prefix,d,n,m+1);
	return (f1+f2);
}

int main()
{
	int prefix[100], n, total;
	printf("Input a positive number to partition: ");
	scanf("%d", &n);
	printf("The first method gets:\n");
	total = divide(prefix,0,n,n);
	printf("total = %d\n", total);
	printf("The second solution gets:\n");
	total = gdiv(prefix,0,n,1);
	printf("total = %d\n", total);

	return 0;
}

