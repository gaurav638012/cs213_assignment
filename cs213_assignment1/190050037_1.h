#include <bits/stdc++.h>
using namespace std;
#define VAL 1000000007;
typedef long long int ll;

class permutation{   
    private:
    int n;
    vector<vector<int>>v;
    vector<int>arr;
    void func();
    
    public:
    permutation(int n1,int a[]);
    permutation(permutation const &q); 
    permutation const operator=(permutation const &q);
    
    int size() const;
    int* to_array() const;
    permutation const operator-() const;
    permutation const operator*(permutation const &q) const;
    permutation const square_root() const;
    permutation const operator^(long long int i) const;
    bool is_power(permutation const &q) const;
    int log(permutation const &q) const; 
    
    ~ permutation()
    {
        arr.clear();
        v.clear();
    }
   
    
};

void permutation::func()
{
    int flag[n+1]={0};
    int start=0;
    while(start<n)
    {  
       vector<int>temp;
       temp.push_back(start);
       flag[start]=-1;
       int ptr=arr[start];
       while(ptr!=start)
       {  temp.push_back(ptr);
          flag[ptr]=-1;
          ptr=arr[ptr];
       }
       while(start<n-1 && flag[start]==-1)
       start++;
       
       if(flag[start]==-1)
       start++;
       
       v.push_back(temp);
    }
}
permutation::permutation(int n1,int a[])
{
    n=n1;
    for(int i=0;i<n1;i++)
    arr.push_back(a[i]);
    
    func();
}

int permutation::size() const{
    return n;
}

int* permutation::to_array() const{
    int* temp=new int[n];
    for(int i=0;i<n;i++)
    temp[i]=arr[i];
    return temp;
}

permutation::permutation(permutation const &q)
{
    n=q.n;
    arr=q.arr;
    v=q.v;
}

permutation const permutation:: operator=(permutation const &q)
 {   
     n=q.n;
     arr=q.arr;
     v=q.v;
     return *this;
 }

permutation const permutation:: operator-() const{
    int b[n];
    for(int i=0;i<n;i++)
    b[arr[i]]=i;
    permutation ob=permutation(n,b);
    return ob;
}

permutation const permutation::operator*(permutation const &q) const
{
    int b[n];
    for(int i=0;i<n;i++)
    b[i]=arr[q.arr[i]];
    
    permutation ob=permutation(n,b);
    return ob;
    
}
permutation const permutation :: square_root() const
{   int power[n];
    vector<int>eve[n];
    int flagger=1;
    for(int i=0;i<v.size();i++)
    {   int s=v[i].size();
        if(s%2==1)
        {
        for(int j=0;j<s;j++)
        power[v[i][j]]=v[i][(j+(s+1)/2)%s];
        }
        else
        {
            if(eve[s-1].size()==0)
            {
                flagger=0;
                eve[s-1]=v[i];
            }
            else
            {
                flagger=1;
                for(int j=0;j<s;j++)
                {
                    power[eve[s-1][j]]=v[i][j];
                    power[v[i][j]]=eve[s-1][(j+1)%s];
                }
                eve[s-1].clear();
                
            }
        }
    }
    if(flagger==0)
    {
        for(int i=0;i<n;i++)
        power[i]=i;
    }
    permutation ob=permutation(n,power);
    return ob;
}

const permutation permutation:: operator^(long long int m) const{
    int power[n];
    for(int i=0;i<v.size();i++)
    {   int s=v[i].size();
        for(int j=0;j<s;j++)
        power[v[i][j]]=v[i][(j+m)%s];
        
    }
    permutation ob=permutation(n,power);
    return ob;
}


int permutation::log(permutation const &q) const{
    
    int iden=1;
    for(int i=0;i<n;i++)
    {
        if(arr[i]!=i)
        {
            iden=0;
            break;
        }
    }
    if(iden==1)
    return 0;
    
    
    
    vector<vector<int>>v_temp=q.v;    //vector that contains q.v
    int flagger=1;                 // flag to check if q.cycle power lies in p
    
    vector<pair<int,int>>chin;         // to store cycle size of q and power to obtain p cycle
    for(int i=0;i<v_temp.size();i++)    // moving through every cycle of q
    {   int siz=v_temp[i].size();
        
        int flag=0;
        int pos;
        for(int k=0;k<v.size();k++)
        {
            if(v[k][0]==v_temp[i][0])
            {
                pos=k;
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            flagger=0;
            //cout<<"SORRY1";
            break;
        }
        
        
        int flag5=1;
        for(int zer=1;zer<v_temp[i].size();zer++)
        {   int flag6=0;
            for(int k=0;k<v.size();k++)
            {
                if(v[k][0]==v_temp[i][zer])
                {
                    flag6=1;
                    break;
                }
            }
            if(flag6==0)
            {
                flag5=0;
                break;
            }
        }
        if(flag5==1)
        {
            chin.push_back(make_pair(siz,0));
            continue;
        }
        
        int c_flag=0;
        for(int j=1;j<siz;j++)      // power is from 0 to q cycle -1
        {   
           if(v_temp[i][j]==v[pos][1])
           {   int flag3=1;
               int g=__gcd(j,siz);
               if(v[pos].size()!=siz/g)
               {
                   flag=0;
                   //cout<<"sorry2"<<"\n";
                   break;
               }
               for(int k=2;k<siz/g;k++)
               {
                   if(v_temp[i][(k*j)%siz]!=v[pos][k])
                   {
                       flag3=0;
                       //cout<<"sorry3"<<"\n";
                       break;
                   }
               }
               
               if(flag3==0)
               {
                   flag=0;
                   //cout<<"sorry4"<<"n";
                   break;
               }
               
               for(int l=1;l<g;l++)
               {
                vector<int>temp;
                temp.push_back(v_temp[i][l]);
                
                for(int q=1;q<siz/g;q++)
                temp.push_back(v_temp[i][(l+q*j)%siz]);
                
                int Index = std::min_element(temp.begin(),temp.end()) - temp.begin();
                Index= (temp.size()-Index)%temp.size();
                
                int arr_temp[temp.size()];
                for(int ptr=0;ptr<temp.size();ptr++)
                arr_temp[(ptr+Index)%temp.size()]=temp[ptr];
                
                int flag4=0;
                int posi;
                for(int k=0;k<v.size();k++)
                {
                 if(v[k][0]==arr_temp[0])
                  {
                  posi=k;
                  flag4=1;
                  break;
                  //cout<<"sorry5"<<"\n";
                  }
                }
                if(flag4==0)
                {
                   flag3=0;
                   //cout<<"sorry6"<<"\n";
                   break;
                }
                
                for(int k=1;k<siz/g;k++)
                {
                   if(arr_temp[k]!=v[posi][k])
                   {
                       flag4=0;
                       //cout<<"sorry7"<<"\n";
                       break;
                   }
                }
                
                if(flag4==0)
                {
                   flag3=0;
                   //cout<<"sorry8"<<"\n";
                   break;
                }
                
                
               }
               
               if(flag3==0)
               {
                   flag=0;
                   break;
                   //cout<<"sorry9"<<"\n";
               }
               c_flag=1;
               chin.push_back(make_pair(siz,j));
               break;
               
           }
            
        }
        if(c_flag==0)
        {
            flagger=0;
            //cout<<"Big"<<"\n";
            break;
        }
        if(flag==0)                   // this must hold for every cycle if not then not possible
        {
            flagger=0;
            break;
            //cout<<"Biggie"<<"\n";
        }
        
    }
    
    if(flagger==0)
    return -1;
    
    else
    {   int flag=1;
        ll r,divide;
        divide=chin[0].first;
        r=chin[0].second;
        for(int i=1;i<chin.size();i++)
        {
            ll g=__gcd((ll)chin[i].first,divide);
            if( abs(r-chin[i].second)%g != 0)
            {
                flag=0;
                break;
            }
            else
            {
                ll x = 1, y = 0;
                ll x1 = 0, y1= 1, a1= divide, b1 = chin[i].first;
               while (b1) 
               {
               int q = a1 / b1;
               tie(x, x1) = make_tuple(x1, x - q * x1);
               tie(y, y1) = make_tuple(y1, y - q * y1);
               tie(a1, b1) = make_tuple(b1, a1 - q * b1);
               }
               ll value=(x*divide*chin[i].second+y*chin[i].first*r)/g;
               divide=(divide*chin[i].first)/g;
               value=value%divide;
               if(value<0)
               value=value+divide;
               
               
               divide=divide%VAL;
               r=value%VAL;
            }
        }
        if(flag==0)
        return -1;
        else
        return int(r);
        
    }
   
}

bool permutation::is_power(permutation const &q) const
{   int val=log(q);
    if(val==-1)
    return false;
    else
    return true;
}
