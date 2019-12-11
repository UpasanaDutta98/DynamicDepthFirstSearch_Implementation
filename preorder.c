#include<stdio.h>
#include<time.h>
//#include"IniTree.c"
#include"dynamic_dfs1.c"
int count1=0;
int *heap;
int *weight;
int *level;
int *preorderList;
int *preorderList1;
int hs=-1;
int *chain,*chain_head,*chain_tail,*chain_length;
clock_t start,end;
double timetaken;
int curr_chain = 0;
int weight_calc(int n)
{
	int sum=1;
	int i;
	for(i=0;i<tree_degreeList[n];i++)
	{
		sum+=weight_calc(tree_adjList[n][i]);
	}
	weight[n]=sum;
	//printf("\nweight - %d = %d\n",n+1,sum);
	return sum;
}
	
void hld(int curr_node, int *edge_counted, int *curr_chain,
         int n,int count)
{
    /* if the current chain has no head, this node is the first node
     * and also chain head */
	count++;
    if (chain_head[*curr_chain]==-1)
        chain_head[*curr_chain] = curr_node;
 
    /* set chain ID to which the node belongs */
 	chain[curr_node]=*curr_chain;
    /* set position of node in the array acting as the base to
       the segment tree */
	preorderList1[*edge_counted] = curr_node;
 	preorderList[curr_node]=(*edge_counted)++;
	
	//printf("preorderList[%d] = %d \n",curr_node,preorderList[curr_node]);
    /* update array which is the base to the segment tree */
 //  s.base_array[(*edge_counted)++] = edge[id].weight;
 
    /* Find the special child (child with maximum size)  */
    int spcl_chld = -1,j,k;
    for ( j=0; j<n; j++){
	k=tree_adjList[curr_node][j];
        if (spcl_chld==-1 || weight[spcl_chld] < weight[k])
           spcl_chld = k;
 	}
    /* if special child found, extend chain */
    if (spcl_chld!=-1)
      hld(spcl_chld,  edge_counted, curr_chain, tree_degreeList[spcl_chld],count);
	else
	{
		chain_tail[*curr_chain] = curr_node; 
		chain_length[*curr_chain] = count;
	}
    /* for every other (normal) child, do HLD on child subtree as separate
       chain*/
    for (j=0; j<n; j++)
    {
	k=tree_adjList[curr_node][j];
	//printf("k = %d\n",k);
      if (k!=spcl_chld )
      {
	//printf("k is not a special child of %d\n",curr_node);
        (*curr_chain)++;
	count = 0;
        hld(k,edge_counted, curr_chain, tree_degreeList[k],count);
      }
	//else
	//	printf("k is a special child of %d\n",curr_node);		
    }
}

int main1()
{
	int i;
	main2();
	start = clock();
	heap=(int*)malloc(sizeof(int)*maxNode);
	preorderList=(int*)malloc(sizeof(int)*maxNode);
	preorderList1=(int*)malloc(sizeof(int)*maxNode);
	chain=(int*)malloc(sizeof(int)*maxNode);
	chain_head=(int*)malloc(sizeof(int)*maxNode);
	chain_tail = (int*)malloc(sizeof(int)*maxNode);
	chain_length = (int*)calloc(maxNode,sizeof(int));	
	for(i=0;i<maxNode;i++)
	{
		chain_head[i]=-1;
	}
		//printf("%d\n",chain_head[i]);}
	weight=(int*)malloc(sizeof(int)*maxNode);
	int c=weight_calc(root);
	//printf("\nweights\n");
	//for(i=0;i<maxNode;i++)
	//{
	//	printf("%d ",weight[i]);
	//}
	/*printf("level: \n");
	for(i=0;i<maxNode;i++)
	{
		printf("%d\n",i);
		printf("%d ",level[i]);
	}*/
	int edge_counted=0;	//curr_chain is the no. of chains 
	hld(root,&edge_counted,&curr_chain,tree_degreeList[root],0);
	curr_chain++;
	/*
	printf("total no of chains = %d\n",curr_chain);
	
	for(i=0;i<curr_chain;i++)
	{
		printf("chain_head of chain %d = %d\nchain_length of chain %d = %d\n\n",i,chain_head[i],i,chain_length[i]);
	}
	printf("\npreorder:\n");
	for(i=0;i<maxNode;i++)
	{
		printf("%d %d\n",i,preorderList[i]);
	}
	printf("\n");
	//printf("preorderList[0] = %d\n",preorderList[0]);
	*/
	/*printf("\nchain:\n");
	for(i=0;i<maxNode;i++)
	{
		printf("%d %d\n",i,chain[i]);
	}
	printf("\n");*/
	return 0;
}


