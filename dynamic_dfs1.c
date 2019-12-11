#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NIL -1
char defile[20], dvfile[20], iefile[20], ivfile[20];
struct stack
{
	int v;
	struct stack* next;
};
struct array
{
	int u;
	int v;
};
struct stack* head = NULL;
int maxNode = 0,edgeCount,root=0,d;
int *tree_degreeList, **tree_adjList;
int *degreeList,**adjList;
int *parent,*level;
int desc;
void calculateGraphOrder(char *s)
{
    int sourceNode, destNode;
    FILE *fp = fopen(s, "r+");
    while(fscanf(fp, "%d %d",&sourceNode, &destNode) != EOF)
    {
        if(maxNode > sourceNode && maxNode > destNode)
            continue;
        else if(sourceNode > destNode)
            maxNode = sourceNode;
        else
            maxNode = destNode;
    }
    maxNode++;
    fclose(fp);
}

void buildDegreeList(char *s)
{
    int sourceNode, destNode,i;
    edgeCount = 0;
    FILE *fp = fopen(s, "r+");
	for(i=1;i<maxNode;i++)
	{
		degreeList[i]=1;
	}
    while(fscanf(fp, "%d %d",&sourceNode, &destNode) != EOF)
    {
        degreeList[sourceNode]++;
	degreeList[destNode]++;
        edgeCount++;
    }
	degreeList[0]=maxNode-1;
    fclose(fp);
}

void buildAdjList(char *s)
{
    int *count = (int*)calloc(maxNode, sizeof(int)); //keep a count of how many adjacent nodes have been inserted
    int sourceNode, destNode, i;
    FILE *fp = fopen(s, "r+");

	for(i=1;i<maxNode;i++)
	{
		adjList[0][i-1]=i;
		adjList[i][0]=0;
	}
    while(fscanf(fp, "%d %d",&sourceNode, &destNode) != EOF)
    {
    
        adjList[sourceNode][++count[sourceNode-1]] = destNode;
	adjList[destNode][++count[destNode-1]] = sourceNode;
    }
    fclose(fp);
    free(count);
   
}
void isDescendant(int x,int y)///checks if x is a descendant(return 1)
{
	if(x == y)
	{
		desc = 1;
		return;
	}
	if(level[x]<=level[y])
	{
		desc = 0;
		return;
	}
	int c=x;
	while(c!=root)
	{
		if(c==y)
		{
			desc = 1;
			return;
		}
		c=parent[c];
	}
	if(c==y)
	{
		desc = 1;
		return;
	}
	desc = 0;
}
int Dist_path(int x,int y)//return the no of nodes in b/w
{
	d=level[x]-level[y]+1;
	return level[x]-level[y]+1;

}
   
int* Fpath(int x,int y)
{
    int *path;
	d=0;
    int u=x;
    int d = Dist_path(x,y);
    path=(int*)malloc(sizeof(int)*(d));
    int i=0;
    while(u!=y)
    {
        path[i++]=u;
        u=parent[u];
    }
    path[i]=y;
    return path;
}
void push(int v)
{
	struct stack* temp = (struct stack*)malloc(sizeof(struct stack));
	temp->v = v;
	temp->next = head;
	head = temp;
}
int pop()
{
	struct stack* temp = head;
	int u = temp->v;
	head = head->next;
	free(temp);
	return u;
}
int peek()
{
	return head->v;
}
int isEmpty_stack()
{
	if(head== NULL)
		return 1;
	else
		return 0;
}	
void store_dfs_tree(int *state,int v)
{
	int i,j;
	tree_degreeList = (int*)calloc(maxNode, sizeof(int));
	tree_adjList = (int**)calloc(maxNode, sizeof(int*));
	int *count = (int*)calloc(maxNode, sizeof(int));
	for(i=0; i<maxNode; i++)
    	{
        	tree_adjList[i] = (int*)calloc(degreeList[i], sizeof(int));
   	}
	parent[v]=-1;
	level[v] = 1;
	push(v);
	state[v]=2;
	while(!isEmpty_stack())
	{
		v = pop();
		if (state[v] == 1)
		{
			state[v] = 2;
		}
		
		for(i=degreeList[v]-1;i>=0;i--)
		{
			if(state[(adjList[v][i])]==1)
			{
				
				push(adjList[v][i]);
				parent[(adjList[v][i])] = v;
				level[(adjList[v][i])] = level[parent[(adjList[v][i])]] + 1;
			}
			
		}
	}
	for(i=1;i<maxNode; i++)
    	{
			
				tree_degreeList[parent[i]]++;
			tree_adjList[parent[i]][(count[parent[i]])++] = i;
	}
	/*printf("\nPrinting the parents : i.e. TREE \n");
	for(i=0;i<maxNode;i++)
	{
		printf("parent of %d is %d\n",i,parent[i]);
	}*/
	/*printf("the tree adj List :\n");
	for(i=0; i<maxNode; i++)
    	{
    	    printf("%d(%d): ", i, tree_degreeList[i]);
    	    for(j=0; j<tree_degreeList[i]; j++)
    	    {
    	        printf("%d ", tree_adjList[i][j]);
    	    }
    	    printf("\n");
    	}*/

}


void DF_Traversal(char *filename)
{
	int* state = (int*)calloc(maxNode, sizeof(int));
	parent = (int*)calloc(maxNode, sizeof(int));
	level = (int*)calloc(maxNode, sizeof(int));
	int v;
	for(v=0;v<maxNode;v++)
	{
		state[v]=1;
		parent[v]= NIL;
	}
	store_dfs_tree(state,root);
	
}	
int lca(int x,int y,int root,int *parent,int *level)
{
    int start=x,end=y; // initially I am taking start to be at x and end to be at y
    
    while(level[start-1]!=level[end-1])// I  am traversing if levels are not equal
    {
	    //printf("level[start] = %d, level[end] = %d\n",level[start]level[end]
	    if(level[x-1]>level[y-1])   // if level of x is greater ,I am increasing the start till levels become same
	    {
		start=parent[start-1];
	    }
	    if(level[x-1]<level[y-1])// if level of y is greater ,I am increasing the end till level becomes same
	    {
		end=parent[end-1];
	    }
    }
    while(parent[start-1]!=parent[end-1]) // after the levels become same or if they are same initially,I am just checking the parent of start and end
    {
        start=parent[start-1];    
        end=parent[end-1];
    }
    return parent[start-1];/// returning the parent,as the LCA
}
int checkPath(int x,int y,int root)
{
	int start,end;
	if(x==root || y==root)
		return 1;
	if(level[x-1]==level[y-1])
		return 0;
	if(level[x-1]>level[y-1])
	{
		start = x;
		end = y;
	}
	else
	{
		start = y;
		end = x;
	}
	while(level[start-1]!=level[end-1])
	{
		if(parent[start-1]==end)
			return 1;	
		start=parent[start-1];
	}
	
	return 0;
}
void jaccard()
{
	int i, j = 0;
	float**jaccardArr = (float**)malloc(maxNode*sizeof(float*));
	for(i = 0; i<maxNode; i++)
		jaccardArr[i] = (float*)malloc(maxNode*sizeof(float));
	int* ties = (int*)calloc(999999,sizeof(int));
	int check = 0;
	for(i = 1; i<maxNode; i++)
		for(j = 1; j<degreeList[i]; j++)
		{
			check++;
			int a = i;
			int b = adjList[i][j];
			int count = 0;
			int k, j;
			for(k = 0;k<degreeList[a];k++)
				for(j = 0; j<degreeList[b];j++)
					if(adjList[a][k] == adjList[b][j])
						count++;
			jaccardArr[a][b] = count/(float)((k-1)*(j-1));
			int t = jaccardArr[a][b]*1000000;
			ties[t]++;
			printf("edge between %d and %d has jaccard coeff = %f\n",a,b,jaccardArr[a][b]);
		}
	int countties = 0;
	for(i = 0; i<999999; i++)
	{	
		if(ties[i]>9)
		{
			printf("%d\t",ties[i]);
			countties+=ties[i];
		}
	}
	printf("No of ties = %d\n",countties);
	printf("No of checks = %d\n",check);
	free(ties);
	free(jaccardArr);
}
					
int main2(void)
{
    char fileName[20];
    int i, j;
    /*printf("Provide the name of the edge-list: ");
    scanf("%s", fileName);
	printf("enter the filename for inserted vertices : ");
	scanf("%s",ivfile);
	printf("enter the filename for inserted edges : ");
	scanf("%s",iefile);
	printf("enter the filename for deleted vertices : ");
	scanf("%s",dvfile);
	printf("enter the filename for deleted edges : ");
	scanf("%s",defile);*/
	strcpy(fileName,"df.txt_1");
	//strcpy(fileName,"in10.txt");
	strcpy(ivfile,"iv_count.txt_1to2");
	//strcpy(ivfile,"iv10.txt");
	strcpy(iefile,"ie.txt_1to2");
	//strcpy(iefile,"ie10.txt");
	strcpy(dvfile,"dv.txt_1to2");
	//strcpy(dvfile,"dv10.txt");
	strcpy(defile,"de.txt_1to2");
 	//strcpy(defile,"de10.txt");
    calculateGraphOrder(fileName); 
    //printf("Number of nodes in the graph (n) = %d\n", maxNode); 

    degreeList = (int*)calloc(maxNode, sizeof(int));
    buildDegreeList(fileName);


    adjList = (int**)calloc(maxNode, sizeof(int*));
    for(i=0; i<maxNode; i++)
    {
        adjList[i] = (int*)calloc(degreeList[i], sizeof(int));
    }
    buildAdjList(fileName);
	/*printf("Printing adj list : \n");
	for(i=0;i<maxNode;i++)
	{
		printf("%d - ",i);
		for(j = 0;j<degreeList[i];j++)
			printf("%d ",adjList[i][j]);
		printf("\n\n");
	}
	printf("adj list built\n");*/

    FILE *adjFile;
    char *adjFileName = (char*)calloc(strlen(fileName)+strlen("_adjList.txt"), sizeof(char));
    strcpy(adjFileName, fileName);
    strcat(adjFileName, "_adjList.txt");
    adjFile = fopen(adjFileName, "w+");

    for(i=0; i<maxNode; i++)
    {
        fprintf(adjFile, "%d(%d): ", i, degreeList[i]);
        for(j=0; j<degreeList[i]; j++)
        {
            fprintf(adjFile, "%d ", adjList[i][j]);
        }
        fprintf(adjFile, "\n");
    }

    fclose(adjFile);
    //printf("Adjacency list printed\n");


    DF_Traversal(fileName);
	FILE* treeadjFile = fopen("df.txt_treeadjlist.txt","w+");	
    for(i=0; i<maxNode; i++)
    {
        fprintf(treeadjFile, "%d : ", i);
        for(j=0; j<tree_degreeList[i]; j++)
        {
            fprintf(treeadjFile, "%d ", tree_adjList[i][j]);
        }
        fprintf(treeadjFile, "\n");
    }
	fclose(treeadjFile);
	//jaccard();
    return 0;
}

