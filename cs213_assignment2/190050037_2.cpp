#include<bits/stdc++.h>
using namespace std;

static vector<char> store={'a','b','c','d','e','f'};
typedef long long int ll;
static ll limit_val=1000000000000000000;
map<int,vector<ll>> val_matrix;
map<char,string> f;

int mat_prod(vector<vector<ll>> &m1,vector<vector<ll>> &m2)
{
	ll n=m1.size();
	ll res[n][n];
	for(ll i=0;i<n;i++)
	{
		for(ll j=0;j<n;j++)
		{
			res[i][j]=0;
			for(ll k=0;k<n;k++)
				res[i][j]+=(m1[i][k])*(m2[k][j]);
		}
	}
	for(ll i=0;i<n;i++)
		for (ll j=0;j<n;j++)
			m1[i][j]=res[i][j];
}

void Power(vector<vector<ll>> &F, int n,vector<vector<ll>> M)
{   ll w=F.size();
	if (n==1)
		return;
	Power(F, n/2,M);
	mat_prod(F, F);
	if (n%2 != 0)
		mat_prod(F, M);
}

void vec_mat_prod(vector<vector<ll>> M,vector<ll> &v){
	vector<ll> z;
	long long int n=v.size();
	for(ll i=0;i<n;i++){
		ll temp=0;
		for(ll j=0;j<n;j++){
			temp+=M[i][j]*v[j];
		}
		z.push_back(temp);
	}
	v=z;
}
char fn(char ch,ll j,ll i){
	if(j==1)
		return f[ch][i-1];
	
	else{
		ll s=i;
		for(int w=1;w<=f[ch].length();w++){

			if(s<=val_matrix[j-1][f[ch][w-1]-97])
				return fn(f[ch][w-1],j-1,s);
			else
				s-=val_matrix[j-1][f[ch][w-1]-97];
			
		}
	}
	return ch;
}
bool checker(vector<ll> l){
	bool ans=true;
	for(int i=0;i<l.size();i++){
		ans=ans&(l[i]<limit_val);
	}
	return ans;
}

int lower(ll val,int pos=0)
{
	int start=1,end=val_matrix.size();
	if(val>val_matrix[end][pos])
		return -1; // j=-1 means that the value has exceeded the val_matrix limits
	while(start<=end)
	{
		int mid=(start+end)/2;
		if(val_matrix[mid][pos]==val)
			return mid;
		else if(val_matrix[mid][pos]>val)
			end = mid - 1;
		
		else
			start = mid + 1;
		
	}
	return start;
}

int isSubSequence(string str1, string str2, int m=0, int n=0) 
{ 
	// Base Cases 
	if (m == str1.size()) return n-1; 
	if (n == str2.size()) return -1; 
  
	if (str1[m] == str2[n]) 
		return isSubSequence(str1, str2, m+1, n+1); 
  	
	return isSubSequence(str1, str2, m, n+1); 
}

string gen_fibonacci(int n,char ch)
{
	if(ch=='a')
	{
		if(n==1)
			return "ab";
		else
			return gen_fibonacci(n-1,'a')+gen_fibonacci(n-1,'b');
		
	}
	else
	{
		if(n==1)
			return "a";
		else
			return gen_fibonacci(n-1,'a');
	}
}

string thue_morse(int n,char ch)
{
	if(ch=='a')
	{
		if(n==1)
			return "ab";
		else
			return thue_morse(n-1,'a')+thue_morse(n-1,'b');
	}
	else
	{
		if(n==1)
			return "ba";
		else
			return thue_morse(n-1,'b')+thue_morse(n-1,'a');
	}
}

pair<int,int> Substring(string w,int flag)
{
	int n=lower(w.size());
	int val;
	int flagger=0;
	if(flag==0) //flag=0 fibonacci
	{   int i;
		for(i=n;i<=n+3;i++)
		{
			string s=gen_fibonacci(i,'a');
			size_t found=s.find(w);
			if(found != string::npos)
			{
				val=found;
				flagger=1;
				break;
			}
			
		}
		if(flagger==1)
			return make_pair(i,val);
		else
			return make_pair(-1,-1);
	}
	else if(flag==1)
	{
		int i;
		for(i=n;i<=n+3;i++)
		{
			string s=thue_morse(i,'a');
			size_t found=s.find(w);
			if(found != string::npos)
			{
				val=found;
				flagger=1;
				break;
			}
			
		}
		if(flagger==1)
			return make_pair(i,val);
		else
			return make_pair(-1,-1);
	}
	else
		return make_pair(-1,-1);
}

pair<int,int> Subsequence(string w,int flag)
{
	int n=lower(w.size());
	int n1=lower(4*w.size());
	int val;
	int flagger=0;
	if(flag==0) //flag=0 fibonacci
	{   int i;
		for(i=n;i<=n1;i++)
		{
			string s=gen_fibonacci(i,'a');
			int z=isSubSequence( w,s );
			if(z!=-1)
			{
				flagger=1;
				val=z;
				break;
			} 
			
		}
		if(flagger==1)
			return make_pair(i,val);
		else
			return make_pair(-1,-1);
	}
	else if(flag==1)
	{
		int i;
		for(i=n;i<=n1;i++)
		{
			string s=thue_morse(i,'a');
			int z=isSubSequence( w,s );
			if(z!=-1)
			{
				flagger=1;
				val=z;
				break;
			} 
			
		}
		if(flagger==1)
			return make_pair(i,val);
		else
			return make_pair(-1,-1);
	}
	else
		return make_pair(-1,-1);
}

int main()
{
	int k;
	cin>>k;
	vector<vector<ll>> Fac;
		
	for(int i=0;i<k;i++)
	{
		string w;
		cin>>w;
		f[store[i]]=w;
		vector<ll> v;
		for(int j=0;j<k;j++)
			v.push_back(count(w.begin(),w.end(),store[j]));
		
		Fac.push_back(v);
	}

	int flag=-1;
	if(k==2)
	{
		if(f['a']=="ab" && f['b']=="b")
			flag=0;
		else if(f['a']=="ab" && f['b']=="ba")
			flag=1;
	}

	vector<ll> length(k,1);
	vector<ll> le=length;
	vector<vector<ll>> fac=Fac;
	int i=1;
	while(checker(le)&&(i<200))
	{
		vec_mat_prod(fac,le);
		val_matrix[i]=le;
		i++;
	}
	int t;
	cin>>t;
	for(int i=0;i<t;i++)
	{
	int test;
	cin>>test;
	if(test==0){
	long long int n;
	cin>>n;
	vector<vector<ll>> fc=Fac;
	vector<ll> l=length;
	Power(fc,n,fc);
	vec_mat_prod(fc,l);
	cout<<l[0]<<"\n";
	}
	else if(test==1)
	{
		ll i;
		cin>>i;
		i=i+1;
		if(i==1)
			cout<<store[0]<<"\n";
		else
		{
		int j=0,ln=1;
		j=lower(i);
		cout<<fn(store[0],j,i)<<"\n";
		}
	}
	else if(test==2)
	{
		string s;
		cin>>s;
		pair<int,int> q=Substring(s,flag);
		if(q.first !=-1)
			cout<<q.first<<" "<<q.second<<"\n";
		else
			cout<<-1;
	}
	else if(test==3)
	{
		string s;
		cin>>s;
		pair<int,int> q=Subsequence(s,flag);
		if(q.first !=-1)
			cout<<q.first<<" "<<q.second+1<<"\n";
		else
			cout<<-1;
	}


	}
	return 0;
}
