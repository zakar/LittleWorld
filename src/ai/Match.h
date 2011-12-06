#include "../resources/Conf.h"
#include <cstring>
#include <cstdio>

class Match {
	public:
		static Match* Instance( int a , int b );
		void solve( int *ans );
		void addEdge( int x , int y , int cost );
		void clear();
		void build( int limit );
		Match( int a , int b );
	private:
		int nx , ny , mat[MAX_PT][MAX_EMY] , new_mat[MAX_PT][MAX_EMY];
		int cx[MAX_PT] , cy[MAX_EMY] , sy[MAX_EMY];
		int find( int x );
};
