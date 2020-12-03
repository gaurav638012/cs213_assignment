#include <bits/stdc++.h>
#include "./190050037_1.h"
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	srand(time(NULL));
	int n = 100;
	int s[n];
	for (int i = 0; i < n; i++)
		s[i] = i;
	int corr = 0;
	for (int i = 0; i < 1000; i++) {
		random_shuffle(s,s+n);
		permutation p(n,s);
		int last = -1;
		bool b = true;
		for (int j = 0; j < n; j++) {
			permutation q = p^j;
			int t = q.log(p);
			if (t != last+1 && t != 0)
				{b  = false;
				 int *valer=p.to_array();
				 cout<<j<<"\n";
				 for(int l=0;l<n;l++)
				 cout<<valer[l]<<" ";
				 cout<<"\n";
				}
			last = t;
		}
			if (b) corr++;
	}
	cout << "CORRECT: " << corr << '\n';
	cout << "WRONG: " << 1000-corr << '\n';
	return 0;
}
