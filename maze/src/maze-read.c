/** File Name : maze-read.c
 *  Author    : Xinguo Liu
 *  E-Mail    : xgliu@cad.zju.edu.cn
 *  Created   : April 2, 2015
 *
 *  some utility functions for solving the maze problem
 */

#include <stdio.h>
#include "maze.h"

/*! 从文件中读取一个地图位置信息
 *    墙（WALL）：表示为字符w，W
 *    路（Road）：表示为字符r，R，o, O, 0, 空格, 句点 
 *
 *    !!其他的字符将视作非法，被忽略
 *    !!非法字符的数量不能超过 MaxMAP*10
 */
static int readSite(FILE *fp)
{
	int ch, ntest = 0;
	int invalidLimit = MaxMAP;
	while( (ch=getc(fp))!=EOF && ntest++ < invalidLimit )
	{
		if( ch=='W' || ch=='w' )
			return WALL; /** wall */
		else if( ch=='.' || ch==' ' || ch== '0' 
				|| ch=='R' || ch=='r' || ch=='O' || ch=='o'  )
			return ROAD; /** road */
	}
	/** process error */
	if( ntest > invalidLimit )
	{	/** invalid number */
		printf("There are too many non-recognized characters\n");
		printf("   in reading the map file\n");
	}
	return EOF;
}

/******************************************************************
 *  @brief     Input method for maze map
 *
 *  @return    1 if success; or 0 if failed.
 *
 ******************************************************************/

int readMap(const char fname[]) /*!< name of the input maze map */
{
	int x, y, errorFound=0;
	FILE * fp;

	if( (fp = fopen(fname,"rt"))==NULL )
	{
		printf("\tCannot open file %s", fname);
		return 0;
	}

	/** read in the size of the map */
	fscanf(fp, "%d%d", &g_mapWidth, &g_mapHeight);
	if ( g_mapWidth<1 || g_mapWidth>MaxMAP || g_mapHeight<1 || g_mapHeight>MaxMAP )
	{	/** invalid number */
		printf("Error in reading the map from file %s\n", fname);
		printf("\tInvalide size:%d %d\n", g_mapWidth, g_mapHeight);
		errorFound = 1;
	}
	/** read in the sites of the map */
	for( y=0; y<g_mapHeight && !errorFound; y++ )
		for( x=0; x<g_mapWidth && !errorFound; x++ )
			if( (g_map[y][x] = readSite(fp))==EOF )
				errorFound= 1;
	fclose(fp);
	return( ! errorFound );
}
