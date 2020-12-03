#include <bits/stdc++.h>
#include <chrono>
#include"./Assignment3.h"
using namespace std;
typedef long long ll;
#define pb push_back
const ll INF = 1e18;

int pro(int n, int aray[])
{
	vector<int> v;
	int visit[n] = {0}, c = 0;
	for(int i=0;i<n;i++)
	{
		if(visit[i])
			continue;
		c = 1;
		int curr = aray[i];
		while(curr != i)
		{
			c++;
			curr = aray[curr];
		}
		v.pb(c);
	}
	int ans = 1;
	for(auto x: v)
		ans = ans/__gcd(ans, x)*x;
	return ans;
}
int main()
{
	srand(time(0));
	int n = 100;
	int aray[n];
	for(ll i=0;i<n;i++)
		aray[i] = i;
	int t = 1000000;
	int c = 0, high = 0, same = 0;
	int total = 0;
	while(t--)
	{
		ll raise = rand()%(INF);
		random_shuffle(aray, aray+n);
		permutation p = permutation(n, aray);
		int lcm = pro(n, aray);
		auto start = std::chrono::high_resolution_clock::now();
		permutation q = p*p;
		p = q.square_root();
		p = p*p;
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		total += duration.count();
		int *arr = q.to_array(), *a = p.to_array();
		for(int i=0;i<n;i++)
		{
			if(a[i] != arr[i])
			{
				c++;
				break;
			}
		}
	}
	cout<<"Number of wrong answers: "<<c<<"\n";
	cout<<"Execution time (in microseconds): "<<total<<"\n";
	return 0;
}
