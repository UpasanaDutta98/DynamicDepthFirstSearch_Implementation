#include<stdio.h>
#include"merge_bst.c"
double sum3=0;
struct array* path_intervals;
struct array* path_intervals1;
int find_count=0;
int find_interval(int x,int y)
{
	
	
	int i=0;
	while(chain[x]!=chain[y])
	{
		
		path_intervals[i].v=preorderList[x];
		path_intervals[i].u=preorderList[chain_head[chain[x]]];
		i++;
		x=parent[chain_head[chain[x]]];
	}
	path_intervals[i].v=preorderList[x];
	path_intervals[i].u=preorderList[y];
	i++;
	//printf("%d ",i);
	return i;
}

int find_interval1(int x,int y)//divides path into continuous interval in preorder and here x is desc and y is ances
{
	if(x==y)
	{
		path_intervals[0].u = preorderList[x];
		path_intervals[0].v = preorderList[y];
		return 1;
	}
	
	int NoOfIntervals=0;
	int s=x;
	int r=preorderList[s];
	int l=r;
	while(parent[s]!=y)
	{
		if(chain[parent[s]]==chain[s])
		{
			l--;
		}
		else
		{
			path_intervals[NoOfIntervals].u=l;
			path_intervals[NoOfIntervals].v=r;
			NoOfIntervals++;
			r=l=preorderList[parent[s]];
		}
		s=parent[s];
	}
	if(chain[parent[s]]==chain[s])
		{
			l--;
			path_intervals[NoOfIntervals].u=l;
			path_intervals[NoOfIntervals].v=r;
			NoOfIntervals++;
		}
	else
		{ 
			path_intervals[NoOfIntervals].u=l;
			path_intervals[NoOfIntervals].v=r;
			NoOfIntervals++;
			r=l=preorderList[parent[s]];
			path_intervals[NoOfIntervals].u=l;
			path_intervals[NoOfIntervals].v=r;
			NoOfIntervals++;
		}	
		
	return NoOfIntervals;
}
struct array* find_edge(struct bstnode* node,int l,int r,int flag)//returns edge closest to r from tree 'node' if flag=1,,,else closest to l
{
	struct array* edge=NULL;
	if(node==NULL)
		return NULL;
	//printf("inside find_edge, node->v = %d\n",node->v);
	if(preorderList[node->v] > r)
		return find_edge(node->left,l,r,flag);
	if(preorderList[node->v]<l)
		return find_edge(node->right,l,r,flag);
	
	else
	{
		if(flag==1){//find_count++;
			edge=find_edge(node->right,preorderList[node->v],r,1);}
		if(flag==0){//find_count++;
			edge=find_edge(node->left,l,preorderList[node->v],0);}
		if(edge!=NULL)
			return edge;	
		edge=(struct array*)malloc(sizeof(struct array));
		edge->u=node->u;
		edge->v=node->v;
		return edge;
	}
}
int main4()
{
	main3();
	path_intervals=(struct array*)malloc(sizeof(struct array)*maxNode);
	//path_intervals1=(struct array*)malloc(sizeof(struct array)*maxNode);
	
	return 0;
}

