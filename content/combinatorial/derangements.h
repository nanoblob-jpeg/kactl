/**
 * Author:
 * Date: 2010-11-15
 * Source: tinyKACTL
 * Description: Generates the $i$:th (lexicographically) derangement of $S_n$.
 */
#pragma once

#include <cstring>
using namespace std;

template <class T, int N> struct derangements {
	T dgen[N][N], choose[N][N], fac[N];
	derangements() {
		fac[0] = choose[0][0] = 1;
		memset(dgen, 0, sizeof(dgen));
		rep(m,1,N) {
			
			fac[m] = fac[m-1] * m;
			
			choose[m][0] = choose[m][m] = 1;
			rep(k,1,m)
				choose[m][k] = choose[m-1][k-1] + choose[m-1][k];
		}
	}
	T DGen(int n, int k) {
		T ans = 0;
		if (dgen[n][k]) return dgen[n][k];
		rep(i,0,k+1)
			ans += (i&1?-1:1) * choose[k][i] * fac[n-i];
		return dgen[n][k] = ans;
	}
	void generate(int n, T idx, int *res) {
		int vals[N];
		rep(i,0,n) vals[i] = i;
		rep(i,0,n) {
			int j, k = 0, m = n - i;
			rep(j,0,m) if (vals[j] > i) ++k;
			rep(j,0,m) {
				T l = 0;
				if (vals[j] > i) l = DGen(m-1, k-1);
				else if (vals[j] < i) l = DGen(m-1, k);
				if (idx <= l) break;
				idx -= l;
			}
			res[i] = vals[j];
			memmove(vals + j, vals + j + 1, sizeof(int)*(m-j-1));
		}
	}
};