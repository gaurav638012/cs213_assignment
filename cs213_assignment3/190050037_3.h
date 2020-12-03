#include<iostream>
using namespace std;
typedef long long int ll;
class quad_tree
{
	public:
		int label,n;

		quad_tree* left_up;
		quad_tree* right_up;
		quad_tree* left_down;
		quad_tree* right_down;

	quad_tree(int h)
	{
		label=0;
		n=h;
		left_up=NULL;
		right_up=NULL;
		left_down=NULL;
		right_down=NULL;
	}

	int size () const
	{
		return n;
	}

	~quad_tree()
	{	if(label==-1)
		{
		delete left_up;
		delete right_up;
		delete left_down;
		delete right_down;
		}
	}

	quad_tree(quad_tree const &Q);
	void set(int x1, int y1, int x2, int y2, int b);
	void total_set(int b);
	void check_total();
	int get(int x1,int y1);
	void overlap(quad_tree const &Q);
	quad_tree& operator=(const quad_tree &Q);
	void intersect(quad_tree &Q);
	void complement();
	void resize(int m);
	void extract(int x1, int y1, int m);
	//void intersect_ptr(quad_tree *Q);
	quad_tree* temp_extract(int x1,int y1,int m);
	ll count_zeros();
};

quad_tree& quad_tree::operator=(const quad_tree &Q)
{
	if(Q.label==-1)
	{
		delete left_up;
		left_up=new quad_tree(*Q.left_up);

		delete right_up;	
		right_up=new quad_tree(*Q.right_up);
		
		delete left_down;
		left_down=new quad_tree(*Q.left_down);
		
		delete right_down;
		right_down=new quad_tree(*Q.right_down);
		
		n=Q.n;
		label=-1;
	}

	else
	{
		n=Q.n;
		left_down=NULL;
		right_down=NULL;
		left_up=NULL;
		right_up=NULL;
		label=Q.label;
	}

	return *this;
}

quad_tree::quad_tree(quad_tree const &Q)
{
	if(Q.label==-1)
	{
		left_up=new quad_tree(*Q.left_up);
		right_up=new quad_tree(*Q.right_up);
		left_down=new quad_tree(*Q.left_down);
		right_down=new quad_tree(*Q.right_down);
		n=Q.n;
		label=-1;
	}

	else
	{
		n=Q.n;
		left_down=NULL;
		right_down=NULL;
		left_up=NULL;
		right_up=NULL;
		label=Q.label;
	}

}

ll quad_tree::count_zeros()
{
	if(label==1)
		return 0;
	else if(label==0)
		return 1ll<<(2*n);
	else
		return left_up->count_zeros()+left_down->count_zeros()
	    +right_up->count_zeros()+right_down->count_zeros();
}

void quad_tree::extract(int x1,int y1,int m)
{
	
	quad_tree* tempo1=temp_extract(x1,y1,m);
	total_set(tempo1->label);

	left_up=tempo1->left_up;
	right_up=tempo1->right_up;
	left_down=tempo1->left_down;
	right_down=tempo1->right_down;
	n=m;	

	tempo1=NULL;
	delete tempo1;
}

quad_tree* quad_tree::temp_extract(int x1,int y1,int m)
{	//cout<<"started"<<"\n";
	if(m==0)
	{
		int label_temp=get(x1,y1);
		quad_tree* temp=new quad_tree(0);
		temp->label=label_temp;
		//cout<<"null size"<<"\n";
		return temp;
		
	}
	
	if(n==m)
	{	//cout<<"total"<<"\n";
		quad_tree* temp=new quad_tree(*this);
		return temp;
		//return this;
	}

	if(label!=-1)
	{	//cout<<"all same"<<"\n";
		quad_tree* temp=new quad_tree(*this);
		temp->n=m;
		return temp;	
	}

	ll v=1<<(n-1);
	ll w=1<<m;

	if(m==n-1)
	{	//cout<<"hai"<<"\n";
		if(x1==0 && y1==0)
		{
			quad_tree* temp=new quad_tree(*this->left_up);
			return temp;
			//cout<<"nw"<<"\n";
			//return this->left_up;

		}

		else if(x1==0 && y1==v)
		{
			quad_tree* temp=new quad_tree(*this->left_down);
			return temp;
			//cout<<"sw"<<"\n";
			//return this->left_down;
		}

		else if(x1==v && y1==0)
		{
			quad_tree* temp=new quad_tree(*this->right_up);
			return temp;
			//cout<<"ne"<<"\n";
			//return this->right_up;
		}

		else if(x1==v && y1==v)
		{
			quad_tree* temp=new quad_tree(*this->right_down);
			return temp;
			//cout<<"se"<<"\n";
			//return this->right_down;
		}
	}
	//cout<<"in quadrant"<<"\n";
	
	if(x1+w<=v)
	{	
		if(y1+w<=v)
		{	/*quad_tree* temp=new quad_tree(*(this->left_up->temp_extract(x1,y1,m)));
			return temp;*/
			quad_tree* temp=this->left_up->temp_extract(x1,y1,m);
			quad_tree* temp1=new quad_tree(*temp);
			delete temp;
			return temp1;
			//cout<<"lu extract"<<"\n";
			//return this->left_up->temp_extract(x1,y1,m);
		}
		else if(y1>=v)
		{
			/*quad_tree* temp=new quad_tree(*(this->left_down->temp_extract(x1,y1-v,m)));
			return temp;*/
			quad_tree* temp=this->left_down->temp_extract(x1,y1-v,m);
			quad_tree* temp1=new quad_tree(*temp);
			delete temp;
			return temp1;
			//cout<<"ld extract"<<"\n";
			//return this->left_down->temp_extract(x1,y1-v,m);
		}
	}

	else if(x1>=v)
	{	
		if(y1+w<=v)
		{	/*quad_tree* temp=new quad_tree(*(this->right_up->temp_extract(x1-v,y1,m)));
			return temp;*/
			quad_tree* temp=this->right_up->temp_extract(x1-v,y1,m);
			quad_tree* temp1=new quad_tree(*temp);
			delete temp;
			return temp1;
			//cout<<"ru extract"<<"\n";
			//return this->right_up->temp_extract(x1-v,y1,m);
		}
		else if(y1>=v)
		{
			/*quad_tree* temp=new quad_tree(*(this->right_down->temp_extract(x1-v,y1-v,m)));
			return temp;*/

			quad_tree* temp=this->right_down->temp_extract(x1-v,y1-v,m);
			quad_tree* temp1=new quad_tree(*temp);
			delete temp;
			return temp1;

			//cout<<"rd extract"<<"\n";
			//return this->right_down->temp_extract(x1-v,y1-v,m);
		}
	}
	//cout<<"general"<<"\n";
	quad_tree* temp=new quad_tree(m);
	
	//temp->left_up=this->temp_extract(x1,y1,m-1);
	quad_tree* nw=this->temp_extract(x1,y1,m-1);
	temp->left_up=new quad_tree(*nw);
	delete nw;

	quad_tree *sw=this->temp_extract(x1,y1+w/2,m-1);
	temp->left_down=new quad_tree(*sw);
	delete sw;

	//temp->left_down=this->temp_extract(x1,y1+w/2,m-1);

	quad_tree *ne=this->temp_extract(x1+w/2,y1,m-1);
	temp->right_up=new quad_tree(*ne);
	delete ne;

	quad_tree *se=this->temp_extract(x1+w/2,y1+w/2,m-1);
	temp->right_down=new quad_tree(*se);
	delete se;

	//temp->right_up=this->temp_extract(x1+w/2,y1,m-1);
	//temp->right_down=this->temp_extract(x1+w/2,y1+w/2,m-1);
	temp->check_total();
	
	return temp;
}

void quad_tree::resize(int m)
{
	if(n==m)
		return;

	if(label!=-1)
	{n=m;
	 return ;
	}

	else
	{
		if(m>n)
		{
			/*if(n==0)
			{
				n=m;
				return ;
			}*/

			left_up->resize(m-1);
			left_down->resize(m-1);
			right_up->resize(m-1);
			right_down->resize(m-1);
			n=m;

		}

		else
		{
			if(m==0)
			{
				ll no_of_zeros=count_zeros();

				if(no_of_zeros> 1ll<<(2*n-1))
					total_set(0);
				else
					total_set(1);


				n=m;
				return ;
			}

			left_up->resize(m-1);
			left_down->resize(m-1);
			right_up->resize(m-1);
			right_down->resize(m-1);
			n=m;
			check_total();
		}

	}

}

void quad_tree::complement()
{
	if(label!=-1)
		label=label^1;

	else
	{
		left_up->complement();
		right_up->complement();
		right_down->complement();
		left_down->complement();
	}
}


void quad_tree::intersect(quad_tree &Q)
{
	if(Q.label==1)
		return ;
	
	if(Q.label==0)
		total_set(0);
	
	else
	{
		if(label!=-1)
		{
	
			left_up=new quad_tree(n-1);
			right_up=new quad_tree(n-1);
			right_down=new quad_tree(n-1);
			left_down=new quad_tree(n-1);

			if(label==1)
			{
				left_down->label=1;
				left_up->label=1;
				right_down->label=1;
				right_up->label=1;
			}
			label=-1;

		}

		left_up->intersect(*Q.left_up);
		left_down->intersect(*Q.left_down);
		right_up->intersect(*Q.right_up);
		right_down->intersect(*Q.right_down);
		check_total();
	}
}

void quad_tree::overlap(quad_tree const &Q)
{
	
	if(Q.label==0)
		return ;

	else if(Q.label==1)
		total_set(1);
	
	else
	{	

		if(label!=-1)
		{
	
			left_up=new quad_tree(n-1);
			right_up=new quad_tree(n-1);
			right_down=new quad_tree(n-1);
			left_down=new quad_tree(n-1);

			if(label==1)
			{
				left_down->label=1;
				left_up->label=1;
				right_down->label=1;
				right_up->label=1;
			}
			label=-1;

		}

		left_up->overlap(*Q.left_up);
		left_down->overlap(*Q.left_down);
		right_up->overlap(*Q.right_up);
		right_down->overlap(*Q.right_down);
		check_total();
	}

}

void quad_tree::check_total()
{
	
	//if(left_up==NULL)
	//	return ;

	if(left_down->label==right_down->label && right_down->label==right_up->label && right_up->label==left_up->label && left_up->label!=-1)
		total_set(left_up->label);
		
	else
		label=-1;
	
		
}

void quad_tree::total_set(int b)
{
	label=b;
	
	delete left_up;
	left_up=NULL;

	delete right_up;
	right_up=NULL;
	

	delete left_down;
	left_down=NULL;
	

	delete right_down;
	right_down=NULL;
			
}

void quad_tree::set(int x1, int y1, int x2, int y2, int b)
{   	
	if(n==0)
	{
		
		label=b;
		return ;
	}

	if(label==b)
		return;

	int v=1<<(n-1);

	if(x1==0 && x2==2*v-1 && y1==0 && y2==2*v-1)
	{
		
		total_set(b);
		return ;
	}

	if(label!=-1)
	{
	
		left_up=new quad_tree(n-1);
		right_up=new quad_tree(n-1);
		right_down=new quad_tree(n-1);
		left_down=new quad_tree(n-1);

		if(label==1)
		{
			left_down->label=1;
			left_up->label=1;
			right_down->label=1;
			right_up->label=1;
		}
		label=-1;

	}

	if(x1<v)
	{
		if(y1<v)
		{
			
			if(x2<v)
			{
				if(y2<v)
					left_up->set(x1,y1,x2,y2,b);
				else
				{	
					left_up->set(x1,y1,x2,v-1,b);
					left_down->set(x1,0,x2,y2-v,b);
					
				}
			}

			else
			{
				
				if(y2<v)
				{	
					left_up->set(x1,y1,v-1,y2,b);
					right_up->set(0,y1,x2-v,y2,b);
					
				}
				else
				{
					
					left_up->set(x1,y1,v-1,v-1,b);
					right_up->set(0,y1,x2-v,v-1,b);
					left_down->set(x1,0,v-1,y2-v,b);
					right_down->set(0,0,x2-v,y2-v,b);
					

				}

			}
		}

		else
		{
			if(x2<v)
				left_down->set(x1,y1-v,x2,y2-v,b);

			else
			{
				left_down->set(x1,y1-v,v-1,y2-v,b);
				right_down->set(0,y1-v,x2-v,y2-v,b);
			}
			
		}
	}

	else
	{
		if(y1<v)
		{	
			if(y2<v)
			right_up->set(x1-v,y1,x2-v,y2,b);

			else
			{			
				right_up->set(x1-v,y1,x2-v,v-1,b);
				right_down->set(x1-v,0,x2-v,y2-v,b);
			}
			
		}

		else
		{
			
			right_down->set(x1-v,y1-v,x2-v,y2-v,b);			
		}
	}

	check_total();

}

int quad_tree::get(int x1,int y1)
{
	int v=1<<(n-1);

	if(label!=-1)
		return label;
	

	if(x1<v && y1<v)
		return left_up->get(x1,y1);
	

	if(x1>=v && y1<v)
		return right_up->get(x1-v,y1);
	

	if(x1<v && y1>=v)
		return left_down->get(x1,y1-v);
	
	return right_down->get(x1-v,y1-v);
	
}

//check total
//resize
