/** File name : maze.h
 *  Author    : Xinguo Liu
 *  E-Mail    : xgliu@cad.zju.edu.cn
 *  Created   : April 2, 2015
 *
 *  The header file for maze problem
 *
 */

/** Some predefined Macros.
 */
#define MaxMAP  20 /*!< The maximum size for map */
#define WALL   '#' /*!< a wall that is not walkable */
#define ROAD   ' ' /*!< a walkable site in the map */
#define LOCK   'L' /*!< a locking flag to avoid path retesting */
#define NaM    'N' /*!< not a map */

/** Point */
typedef struct {
	int x, y; /*!< x and y coodinate of a 2D point */
} Point;

/** Gobal variables defining the map.
 *  The map is stored in a 2D array of char,
 *  together with two integer numbers
 *          map_width, map_height
 */
extern char g_map[MaxMAP][MaxMAP]; /*!< A 2D array storing the sites of the map */
extern int  g_mapWidth;          /*!< the width of the map */
extern int  g_mapHeight;         /*!< the hight of the map */

/*! utility for printing the map */
void printMap(char map[MaxMAP][MaxMAP], int width, int height);
/*! mark a path in the map */
void markPath(Point p[],     /*!< point array on the path */
              int   pLength, /*!< length of the path (number of point) */
              char  map[MaxMAP][MaxMAP], /*!< input map */
              int   width,   /*!< width of the map */
              int   height); /*!< height of the map */
/*! print a path */
void printPath(Point p[],     /*!< point array of the path */
               int   pLength);/*!< path length (number of point) */
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
      0  1  2  3  4  5  6  7  8  9 */
int makeDefaultMap();
/*! test if site (x,y) is out of the map boundary */
int outOfBound(Point p);
/*! lock site (x,y) to prevent from retesting */
void lockSite(Point p);
/*! test if site (x,y) is locked */
int isLocked(Point p);
/*! test if site (x,y) is wall */
int isWall(Point p);
/*! test if two sites are the same : p==q */
int sameSite(Point p, Point q);
/*! read a map */
int readMap(const char fname[]);
/*! find a path to the goal point *g* 
 *  from an existing path */
int searchPath(Point g,     /*!< the goal point */
			Point path[],   /*!< current path to begin with */
			int   pathLen); /*!< the length of the current path */

/* end of file */

