/** File Name : maze.c
 *  Author    : Xinguo Liu
 *  E-Mail    : xgliu@cad.zju.edu.cn
 *  Created   : April 2, 2015
 *
 *  A recursive implementation of the maze problem
 */

#include <stdio.h>
#include "maze.h"

/*! the gobal variables (see maze.h) */
char g_map[MaxMAP][MaxMAP];
int  g_mapWidth;
int  g_mapHeight;

/***************************************************
 *  @brief     一个深度优先的迷宫算法
 *
 *  @return    路径长度，如果可以到达出口；
 *             0， 否则。
 *
 *  递归算法描述：
 *
 *  p <== 当前路径终点 （p 作为新的起点）
 *
 *  1] 如果 p 等于 g，那么成功找到路径，返回 pathLen
 *  2] 如果 p 是围墙，无需继续测试，返回 （0）
 *  3] 如果 p 的标记为'已测试', 无需继续测试，返回 （0）
 *  4] 将 p 标记为'已测试'
 *  5] 对于 p 的每一个邻居点 n
 *		5.1] 将np加入到当前路径，并将长度++
 *		5.2] 递归搜索n 到 g 之间的路径。
 *		5.3] 如果找到了 那么返回路径的长度
 *	6] 找不到路径，返回 (0)
****************************************************/
int searchPath( Point g,        /*!<  目的地点(迷宫出口) */
				Point path[],   /*!<  当前搜多的路径 */
				int   pathLen)  /*!<  当前路径的长度 */
{
	int k; /*! counter for the neighbor sites */
	static const int n[][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
	Point p = path[pathLen-1]; /*! 当前路径终点 */
	if( sameSite(p,g) )  /*! 达到目的地 */
		return pathLen;
	if (isWall(p)) /*! wall */
		return (0);
	if (isLocked(p)) /*! 该点已测 */
		return (0);
	lockSite(p);  /*! 锁定该点 */

#ifdef _debug
	/*! 输出一些信息，帮助调试 */
	printMap(g_map, g_mapWidth, g_mapHeight); /*! print the map */
	printPath(path, pathLen); /*! print the path */
#endif // _debug

	/*! 对每一个邻近地点，测试是否可以从它达到出口 */
	for( k=0; k<sizeof(n)/sizeof(n[0][0])/2; k++ )
	{
		int newLength;
		Point np; /*! 邻近点*/
		np.x = p.x + n[k][0];
		np.y = p.y + n[k][1];
		if( outOfBound(np) ) /*! 超出边界 */
			continue; /*! 忽略 */
		path[pathLen] = np; /*! 加入路径（临时）*/
		/*! 尝试从邻近点np的路径*/
		newLength = searchPath(g, path, pathLen+1);
		if( newLength>0 ) /*! 找到可行的路径 */
			return (newLength); /*! 返回此路 */
	}
	/*! 所有的邻近地点都不能达到出口 */
	return (0); /*! 返回0, 宣告失败 */
}

int main(int argc, char *argv[])
{
	int nPathLen;
	Point path[100], pGoal;

	/*! 通过命令行参数，传递地图文件。没有提供文件，
	 * 或者不能成功读取文件，那么创建一个缺省的 */
    if( argc<2 || !readMap(argv[1]) )
		makeDefaultMap();
	/*! 显示初始的map */ 
	printMap(g_map, g_mapWidth, g_mapHeight);
	/*! 设置出发点和目的地出口 */
	path[0].x = path[0].y = 1; /*! 起点 */
	pGoal.x = g_mapWidth-2;    /*! 终点 */
	pGoal.y = g_mapHeight-2;
	/*! 调用路径搜索函数 */
	nPathLen = searchPath(pGoal, path, 1);
	if( nPathLen ) /*! 成功 */
	{
		printf("Find a path to the goal\n");
		/*! 输出路径 */
		printPath(path, nPathLen);
	}
	else /*！失败 */
		printf("Cannot find a path to the goal\n");
	return 0;
}

