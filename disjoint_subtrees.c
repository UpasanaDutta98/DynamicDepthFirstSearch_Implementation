
#include<stdio.h>
#include"query.c"
//int dis_count = 0;
struct array* find_range(int w)
{
	struct array* temp = (struct array*)malloc(sizeof(struct array));
	temp->u = preorderList[w];
	temp->v = temp->u + weight[w] -1;
	return temp;
}

struct array* QUERY(int w,int x,int y, int flag)//subtree T(w) and path XY...closest to x
{
	if(x>=maxNode || y>=maxNode)
		return NULL;

	//isDescendant(x,y);
	//printf("desc = %d\n",desc);
	int NoOfIntervals,i,j;
	seg_count=0;
	struct array* range=find_range(w);
	struct array* temp=NULL;
	if(range->u == range->v)
	{
		seg_count = 1;
		seg_nodes[0] = leaf_index[w];
	}
	else
	disjoint_subtrees(1,maxNode-1,0,range->u,range->v);
	//int * segarray = (int *)malloc(sizeof(int)*seg_cover[range->u][range->v].cover_size);
	//for(i = 0;i<seg_cover[range->u][range->v].cover_size;i++)
		//segarray[i] = seg_cover[range->u][range->v].seg_indices[i];
	struct array* min=NULL;

	if(flag==1)
	{
		//newinter = find_interval_new(x,y);
		NoOfIntervals=find_interval(x,y);
		//printf("%d ",NoOfIntervals);
		for(i=0;i<seg_count;i++)
		{
			temp=NULL;
			for(j = 0;j<NoOfIntervals && temp==NULL;j++)
			{
				//find_count++;
				//clock_t s1, e1;
				//double 	TT1;
				//s1 = clock();			
				temp=find_edge(segTree[seg_nodes[i]].bst,path_intervals[j].u,path_intervals[j].v,0);	//closest to path_intervals[j].v		
				//e1 = clock();
				//TT1 = (double)(e1 - s1)/CLOCKS_PER_SEC;
				//sum3+=TT1;
				//if(temp==NULL)
				//	null_count++;
				if((min==NULL) || (temp!=NULL && preorderList[min->v] < preorderList[temp->v]))
					min=temp;
			}
		}
	}
	else
	{
		//newinter = find_interval_new(x,y);
		NoOfIntervals=find_interval(x,y);
		//printf("%d ",NoOfIntervals);
			//printf("\n\nintervals not equal\n\n");
		for(i=0;i<seg_count;i++)
		{
	
		temp=NULL;
			for(j=NoOfIntervals-1;j>=0 && temp==NULL;j--)
			{
				//find_count++;
				//clock_t s1, e1;
				//double 	TT1;
				//s1 = clock();			

				temp=find_edge(segTree[seg_nodes[i]].bst,path_intervals[j].u,path_intervals[j].v,1);	//closest to path_intervals[j].v
				//e1 = clock();
				//TT1 = (double)(e1 - s1)/CLOCKS_PER_SEC;
				//sum3+=TT1;
				//if(temp==NULL)
				//	null_count++;
				if((min==NULL) || (temp!=NULL && preorderList[min->v] > preorderList[temp->v]))
					min=temp;
			}
		}
	}
	return min;
} 
struct array* QUERY2(int w,int x,int y,int flag)//w and path XY...closest to x...where y is ancestor
{
	if(x>=maxNode || y>=maxNode)
		return NULL;
	int i = preorderList[w],j,NoOfIntervals;
	//isDescendant(x,y);
	seg_count = 0;
	struct array* temp1=NULL;
	seg_nodes[0] = leaf_index[w];
	//disjoint_subtrees(0,maxNode-1,0,i,i);
	if(flag==1)
	{
		//newinter = find_interval_new(x,y);
		NoOfIntervals = find_interval(x,y);
		//printf("%d ",NoOfIntervals);		
		for(j=0;j<NoOfIntervals && temp1==NULL;j++)
		{
			//find_count++;
			//clock_t s1, e1;
			//double 	TT1;
			//s1 = clock();			

			temp1=find_edge(segTree[seg_nodes[0]].bst,path_intervals[j].u,path_intervals[j].v,0);
			//e1 = clock();
			//TT1 = (double)(e1 - s1)/CLOCKS_PER_SEC;
			//sum3+=TT1;
			//if(temp1==NULL)
			//	null_count++;	
		}
	}
	else
	{
		//newinter = find_interval_new(x,y);
		NoOfIntervals = find_interval(x,y);
		//printf("%d ",NoOfIntervals);		
		for(j=NoOfIntervals-1;j>=0 && temp1==NULL;j--)
		{
			//find_count++;
			//clock_t s1, e1;
			//double 	TT1;
			//s1 = clock();			

			temp1=find_edge(segTree[seg_nodes[0]].bst,path_intervals[j].u,path_intervals[j].v,1);
			//e1 = clock();
			//TT1 = (double)(e1 - s1)/CLOCKS_PER_SEC;
			//sum3+=TT1;
			//if(temp1==NULL)
			//	null_count++;	
		}
	}
	return temp1;
}
int main5()
{
	main4();
	/*struct array* queryans=QUERY2(14,4,2);
	if(queryans!=NULL)
		printf("final = %d %d",queryans->u,queryans->v);
	else
		printf("no edge");*/
	return 0;
}

