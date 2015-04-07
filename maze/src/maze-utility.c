/** File Name : maze-utility.c
 *  Author    : Xinguo Liu
 *  E-Mail    : xgliu@cad.zju.edu.cn
 *  Created   : April 2, 2015
 *
 *  some utility functions for solving the maze problem
 */

#include <stdio.h>
#include "maze.h"

/*! utility for printing the map */
void printMap(char map[MaxMAP][MaxMAP], int width, int height)
{
	int j, k;
	for( j=0; j<height; j++ )
	{
		for (k=0; k<width; k++ )
			printf("%c ", map[j][k]);
		printf("\n");
	}
	printf("\n");
}

/*! mark a path in the map */
void markPath(Point p[],    /*!< point array on the path */
              int   pLength,/*!< length of the path (number of point) */
              char  map[MaxMAP][MaxMAP], /*!< input map */
              int   width,  /*!< width of the map */
              int   height) /*!< height of the map */
{
    char ch = 0;
	int k, dx, dy;
	/** for all points on the path */
	for(k=0; k<pLength; k++)
	{
		if( k==pLength-1)
            ch = '*'; /** use star for the end site */
		else
		{
		    /** calc the direction of the path at the k-th point */
			dx = p[k+1].x - p[k].x;
			dy = p[k+1].y - p[k].y;
			if( dx<0 )      ch = '<'; /** go left */
			else if( dx>0 ) ch = '>'; /** go right */
			else if( dy<0 ) ch = '^'; /** go up */
			else if( dy>0 ) ch = '!'; /** go down */
		}
		map[p[k].y][p[k].x] = ch;
	}
}

/*! print a path */
void printPath(Point p[],    /*!< point array of the path */
               int   pLength)/*!< path length (number of point) */
{
	char tempMap[MaxMAP][MaxMAP];
	int x, y;

    /** make a copy of the current map */
    /** only keeping the WALL and the ROAD sites */
	for( y=0; y<MaxMAP; y++ )
	for( x=0; x<MaxMAP; x++ )
    {
        if( g_map[y][x]==WALL )
            tempMap[y][x] = WALL;
        else
            tempMap[y][x] = ROAD;
    }
    /** mark path in the map, and then print the map */
	markPath(p, pLength, tempMap, g_mapWidth, g_mapHeight);
	printMap(tempMap, g_mapWidth, g_mapHeight);
}

/*! An utility for creating a default map. */
/**   0  1  2  3  4  5  6  7  8  9
  0 { W, W, W, W, W, W, W, W, W, W },
  1 { W, O, O, W, O, O, O, W, O, W },
  2 { W, O, O, W, O, O, O, W, O, W },
  3 { W, O, O, O, O, W, W, O, O, W },
  4 { W, O, W, W, W, O, O, O, O, W },
  5 { W, O, O, O, W, O, O, O, O, W },
  6 { W, O, W, O, O, O, W, O, O, W },
  7 { W, O, W, W, W, O, W, W, O, W },
  8 { W, W, O, O, O, O, O, O, O, W },
  9 { W, W, W, W, W, W, W, W, W, W },
      0  1  2  3  4  5  6  7  8  9
 */
int makeDefaultMap()
{
    int x = 0, y = 0;
    g_mapWidth = 10;
    g_mapHeight = 10;

    /*! initialize all sites to be walkable ROAD */
    for( y=0; y<g_mapHeight; y++ )
        for( x=0; x<g_mapWidth; x++ )
            g_map[y][x] = ROAD;
    /*! set the boundary WALLs */
    for( x=0; x<g_mapWidth; x++ )
        g_map[0][x] = g_map[g_mapHeight-1][x] = WALL;
    for( y=0; y<g_mapHeight; y++ )
        g_map[y][0] = g_map[y][g_mapWidth-1] = WALL;
    /*! set internal WALLs  */
    g_map[1][3] = g_map[1][7] = WALL;
    g_map[2][3] = g_map[2][7] = WALL;
    g_map[3][5] = g_map[3][6] = WALL;
    g_map[4][2] = g_map[4][3] = g_map[4][4] = WALL;
    g_map[5][4] = WALL;
    g_map[6][2] = g_map[6][6] = WALL;
    g_map[7][2] = g_map[7][3] = g_map[7][4] = g_map[7][6] = g_map[7][7] = WALL;
    g_map[8][1] = WALL;
	return 1;
}

/*! test if site (x,y) is out of the map boundary */
int outOfBound(Point p)
{
	return (p.x<0 || p.x>=g_mapWidth || p.y<0 || p.y>=g_mapHeight);
}

/*! lock site (x,y) to prevent from retesting */
void lockSite(Point p)
{
	g_map[p.y][p.x] = LOCK;
}

/*! test if site (x,y) is locked */
int isLocked(Point p)
{
	return g_map[p.y][p.x]==LOCK;
}

/*! test if site (x,y) is wall */
int isWall(Point p)
{
	return g_map[p.y][p.x]==WALL;
}

/*! test if two sites are the same : p==q */
int sameSite(Point p, Point q)
{
	return ( p.x==q.x && p.y==q.y );
}
