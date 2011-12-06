#include "Match.h"

Match::Match( int a = 0 , int b = 0 ) : nx(a) , ny(b)
{
	memset( mat , -1 , sizeof(mat) );
}

Match* Match::Instance( int a , int b ) 
{
	static Match* ins = new Match(a,b);
	return ins;
}

void Match::clear() 
{
	memset( mat , -1 , sizeof(mat) );
}

void Match::addEdge( int x , int y , int cost ) 
{
	if ( !cost ) return;
	mat[x][y] = cost;
}

int Match::find( int x ) 
{
	for ( int i = 0; i < ny; i++ ) {
		if ( new_mat[x][i] != -1 && sy[i] == -1 ) {
			sy[i] = 1;
			if ( cy[i] == -1 || find(cy[i]) ) {
				cy[i] = x;
				cx[x] = i;
				return 1;
			}
		}
	}
	return 0;
}

void Match::build( int limit ) 
{
	for ( int i = 0; i < nx; i++ ) {
		for ( int j = 0; j < ny; j++ ) {
			if ( mat[i][j] <= limit && mat[i][j] != -1 ) new_mat[i][j] = 1;
			else new_mat[i][j] = -1;
		}
	}
}

void Match::solve( int *ans ) 
{
/*
	for ( int i = 0; i < nx; i++ ) {
		for ( int j = 0; j < ny; j++ ) {
			printf( "%d " , mat[i][j] );
		}
		printf( "\n" );
	}
*/
	int lower = 0 , upper = GRID_WIDTH*2 , ret = 0 , tg = nx < ny ? nx : ny;
	while ( lower <= upper ) {
		int mid = ( lower + upper ) >> 1 , t = 0;
		build(mid);
		memset( cx , -1 , sizeof(cx) );
		memset( cy , -1 , sizeof(cy) );
		for ( int i = 0; i < nx; i++ ) {
			if ( cx[i] == -1 ) {
				memset( sy , -1 , sizeof(sy) );
				t += find(i);
			}
		}
		if ( cx[1] != -1 && cx[3] != -1 && cx[4] != -1 && cx[6] != -1 ) {
			ret = mid;
			upper = mid - 1;
			memcpy( ans , cx , sizeof(cx) );
		} else lower = mid + 1;
	}
/*
	for ( int i = 0; i < nx; i++ ) printf( "%d " , ans[i] );
	printf( "\n" );
	*/
}

