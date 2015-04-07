#include <stdio.h>
#include <stdlib.h>


/*! 输出p中的划分 */
void outputPrefix(int p[], int n);
/*! 输出 n 个 1 */
void outputOnes(int n);
/*! 输出n的，各项都<=m的，所有划分 
 *  并在每一个划分前输出一个前缀prefix
 *  参数d为前缀的长度
 */
int divide(int prefix[], int d, int n, int m);

/*! 输出n的，各项都>=m的，所有划分 
 *  并在每一个划分前输出一个前缀prefix
 *  参数d为前缀的长度
 */
int gdiv(int prefix[], int d, int n, int m);

