#include<stdio.h>
#include "disjoint_subtrees.c"


struct path
{
	int down;
	int *up;
};
int a=0,b=0;	//number of elements in T and P respectively
struct array *T;
struct triple *P;
int *failedV;
int countV=0;	//count of failed vertices
int countIV = 0;	//count of inserted vertices
int **L;
int *degree_L;
int T_first=-5, T_last=-5, P_first = -5, P_last = -5;
int *pointers;
int p_count;
/*
struct node_T
{
	int vertex;
	struct node_T* next;
};*/
//struct node_P* P_head = NULL;
//struct node_T* T_head = NULL;
int* isroot,*info;
struct path* pathparam;


struct pathnode
{       
	int u;
	int v;
	struct pathnode *left;
	struct pathnode *right;
	int sep;
};
struct pathnode** hash;
struct pathnode* root_node;
int root_count=0;
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct pathnode* node;
struct pathnode* newpathNode(int v1, int v2)
{
    node = (struct pathnode*)malloc(sizeof(struct pathnode));
	//printf("\naddress of newnode = %p\n",&node);
node->u   = v1;
node->v = v2;
node->left   = NULL;
node->right  = NULL;
node->sep = -1;
return(node);
}

// function to insert key in subtree rooted      constant time
// with node and returns new root of subtree.
void insert_pathtree(struct pathnode* node, int level,int v1, int v2,int k)
{
	 struct pathnode* node1 = (struct pathnode*)malloc(sizeof(struct pathnode));
    node->sep=level;
	node1->sep=-1;
	node1->u=v1;
	node1->v=v2;
	node1->left=node1->right=NULL;
	if(k==1)
		node->left=node1;
	else
		node->right=node1;
}
 
 void inOrder(struct pathnode *root)
{
    if(root->sep!=-1)
    {
        inOrder(root->left);
	printf("%d %d %d\n", root->u, root->v,root->sep);
        inOrder(root->right);
    }
	else
		printf("%d %d %d\n", root->u, root->v,root->sep);
}
 struct pathnode* find_param(struct pathnode* root, int key)
{
	//printf(" %d %d \n",root->u,root->v);
    if (root->sep==-1)
     {
		//printf(" %d %d \n",root->u,root->v);
	  return root;
    }
    // Key is greater than root's key
    if (root->sep < key)
       return find_param(root->right, key);
 
    // Key is smaller than root's key
    return find_param(root->left, key);
}
void delete_from_P(int u)
{
	int k = P[u].a;
	if(P[u].b!=-5)
		P[P[u].b].c=P[u].c;
	if(P[u].c!=-5)
		P[P[u].c].b=P[u].b;
	if(P_last==u)
		P_last=P[u].b;
	if(P_first == u)
		P_first = P[u].c;
	P[u].b=-1;
	P[u].c=-1;
	P[u].a=-1;
	/*printf("\n\nDeleting...\n");
	while(u!=k)
	{
		info[u] = 2;
		printf("%d ",u);
		u = parent[u];
	}
	info[k] = 2;
	printf("%d\n",k);*/	
}
void insert_in_P(int u,int v)
{
	/*if(v>=maxNode ||u<=0)
		printf("\n\nhey\n\n");*/
	/*isDescendant(u,v);
		if(desc!=1)
			printf("insertion of a non ances desc path in 131\n");	*/
	P[u].a=v;
	P[u].b=P_last;
	P[u].c=-5;	
	if(P_last!=-5)
		P[P_last].c=u;
	else
		P_first = u;
	P_last =u;
	while(u!=v)
	{
		/*if(info[u]==1)
		{
			printf("overwriting on an already existing path - u = %d\n",u);
			printf("what\n");
			exit(0);
		}*/
		info[u] = 1;
		u = parent[u];
	}
}


/*void alter_P_for_e(int x,int y)
{
	
	//printf("pathparam of %d = %d %d\nhash= %d %d %d\n",x,pathparam[x].down,*pathparam[x].up,hash[pathparam[x].down]->u,hash[pathparam[x].down]->v,hash[pathparam[x].down]->sep);
	struct pathnode*t=find_param(hash[pathparam[x].down],level[x]);
	struct pathnode*m=find_param(hash[pathparam[y].down],level[y]);
	printf("x = %d, y = %d\n",x,y);
	if((t->u!=m->u || t->v!=m->v) && y == parent[x])
	{
		printf("x and y belong to diff paths even though it is a tree edge\n");
		isDescendant(m->u, t->u);
	if(desc==1)
		printf("path inside path\n");
	}
	else
		printf("x and y belong to same paths\n");	
	//printf("find param returns %d %d \n",t->u,t->v);
	isDescendant(t->u, t->v);
	if(desc!=1)
		printf("x's path in P is not an ances desc path\n");
	isDescendant(m->u, m->v);
	if(desc!=1)
		printf("y's path in P is not an ances desc path\n");
	printf("y's path is from level = %d to level = %d and x's path is from level = %d to level = %d\n",level[m->u], level[m->v],level[t->u],level[t->v]);
	
	delete_from_P(t->u);
	if(parent[x]==y)
	{
		printf("154, y = %d, t->v = %d\n",y,t->v);
		isDescendant(y, t->v);
		if(desc!=1)
			printf("insertion of a non ances desc path in 177\n");	
		isDescendant(t->u, x);
		if(desc!=1)
			printf("insertion of a non ances desc path in 180\n");	
		insert_in_P(y,t->v);
		printf("156, t->u = %d, x = %d\n",t->u,x);
		insert_in_P(t->u,x);
		//printf(" y = %d ,level[y] = %d\n",y,level[y]);
		insert_pathtree(t,level[y],y,t->v,1);//1 for insertion on left side 0 for right
		insert_pathtree(t,level[y],t->u,x,0);
	}
	/*else
	{
		printf("failed v = parent %d to child %d\n\n",y,x);
		isDescendant(x,t->v);
		if(desc == 0)
			printf("\n\nwrong insertion in 149\n\n");
		insert_in_P(x,t->v);
		isDescendant(t->u,y);
		if(desc == 0)
			printf("\n\nwrong insertion in 153\n\n");
		insert_in_P(t->u,y);
		insert_pathtree(t,level[y],x,t->v,1);
		insert_pathtree(t,level[y],t->u,y,0);
	}
}*/
void alter_P_for_e(int x,int y)
{
	
	//printf("pathparam of %d = %d %d\nhash= %d %d %d\n",x,pathparam[x].down,*pathparam[x].up,hash[pathparam[x].down]->u,hash[pathparam[x].down]->v,hash[pathparam[x].down]->sep);
	struct pathnode*t=find_param(hash[pathparam[x].down],level[y]);
	//printf("find param returns %d %d \n",t->u,t->v);
	
	delete_from_P(t->u);
	if(parent[x]==y)
	{
		insert_in_P(y,t->v);

		insert_in_P(t->u,x);
		//printf(" y = %d ,level[y] = %d\n",y,level[y]);
		insert_pathtree(t,level[y],y,t->v,1);//1 for insertion on left side 0 for right
		insert_pathtree(t,level[y],t->u,x,0);
	}
	/*else
	{
		printf("failed v = parent %d to child %d\n\n",y,x);
		isDescendant(x,t->v);
		if(desc == 0)
			printf("\n\nwrong insertion in 149\n\n");
		insert_in_P(x,t->v);
		isDescendant(t->u,y);
		if(desc == 0)
			printf("\n\nwrong insertion in 153\n\n");
		insert_in_P(t->u,y);
		insert_pathtree(t,level[y],x,t->v,1);
		insert_pathtree(t,level[y],t->u,y,0);
	}*/
}

void alter_P_for_v(int v)
{	
	struct pathnode*t=find_param(hash[pathparam[v].down],level[v]);
	
	delete_from_P(t->u);
	info[v] = -1;
	
	//to know the child of v in path in P
	//x= ^ child;

	
	if(v!=t->v)
	{
		//printf("191, parent[v] = %d and t->v = %d\n",parent[v], t->v);
		insert_in_P(parent[v],t->v);
		insert_pathtree(t,level[v],parent[v],t->v,1);
	}
	if(v!=t->u)
	{
		int i,x=-1;
		for(i=0;i<tree_degreeList[v];i++)
		{
			if(pathparam[tree_adjList[v][i]].down==pathparam[v].down)
			{
				x=tree_adjList[v][i];
				break;
			}
		}
		//printf("206, t->u =  %d and x = %d\n",t->u,x);
		insert_in_P(t->u,x);
		insert_pathtree(t,level[v],t->u,x,0);
	}
	
}

void initialize()
{
	int i;
	b = 0;
	//printf("Initialising\n");
	//printf("T_first = %d\n",tree_adjList[0][0]);
	T[tree_adjList[0][0]].u = -5;
	T_first = tree_adjList[0][0];
	isroot[T_first] = 1;
	T[tree_adjList[0][0]].v = -5;
	for(i=1; i<tree_degreeList[0]; i++)
	{
	//	printf("%d\n",tree_adjList[0][i]);
		isroot[tree_adjList[0][i]] = 1;
		T[tree_adjList[0][i-1]].v = tree_adjList[0][i];
		T[tree_adjList[0][i]].u = tree_adjList[0][i-1];
		T[tree_adjList[0][i]].v = -5;
	}
		
	T_last = tree_adjList[0][tree_degreeList[0]-1];
	/*
	printf("Printing T : ");
	for(i = 0;i<maxNode;i++)
	{
		printf("T[%d].u = %d\nT[%d].v = %d\n\n",i,T[i].u,i,T[i].v);
	}
	printf("Printing p : ");
	for(i = 0;i<maxNode;i++)
	{
		printf("P[%d].a = %d\nP[%d].b = %d\nP[%d].c = %d\n\n",i,P[i].a,i,P[i].b,i,P[i].c);
	}
	printf("T_first = %d\n",T_first);
	printf("T_last = %d\n",T_last);
	printf("P_first = %d\n",P_first);
	printf("P_last = %d\n",P_last);
	printf("Initialisation over \n\n");*/

}

void alter_T_for_e(int u, int v)	//u is the child of v and u,v lies in T
{
	int i = 0;
	// children of v to T
	if(tree_degreeList[v]!=0)
	{
		T[T_last].v = tree_adjList[v][0];
		isroot[tree_adjList[v][0]] = 1;
		T[tree_adjList[v][0]].u = T_last;
		T[tree_adjList[v][0]].v = -5;
		for(i=1;i<tree_degreeList[v];i++)
		{
			isroot[tree_adjList[v][i]] = 1;
			T[tree_adjList[v][i-1]].v = tree_adjList[v][i];
			T[tree_adjList[v][i]].u = tree_adjList[v][i-1];
			T[tree_adjList[v][i]].v = -5;
		}
		T_last = tree_adjList[v][tree_degreeList[v] - 1];
	}
	//changing pathparam of v
	pathparam[v].down = v;
	pathparam[v].up = &pointers[p_count];
	info[v] = 1;
	//x = 10;
	//printf("%d\n",*(pathparam[v].up));
	int k = v;
	while(isroot[v]!=1)
	{
		for(i=0;i<tree_degreeList[parent[v]];i++)
		{
			if(tree_adjList[parent[v]][i]!=v)
			{
				isroot[tree_adjList[parent[v]][i]] = 1;
				T[T_last].v = tree_adjList[parent[v]][i];
				T[tree_adjList[parent[v]][i]].u = T_last;
				T[tree_adjList[parent[v]][i]].v = -5;
				T_last = tree_adjList[parent[v]][i];
			}
		

		}
		pathparam[parent[v]].down = k;
		pathparam[parent[v]].up = &pointers[p_count];
		info[parent[v]] = 1;
		v = parent[v];		
	}
	pointers[p_count] = v;
	p_count++;
	hash[k]=&root_node[root_count++];
	hash[k]->left=hash[k]->right=NULL;
	hash[k]->sep=-1;
	hash[k]->u=k;
	hash[k]->v=v;
	//newpathNode(k,v);
	//inserting path in P
	P[k].a = v;
	if(P_first == -5)
	{
		P_first = k;
		P_last = k;
		P[k].b = -5;
	} 
	else
	{
		P[P_last].c = k;
		P[k].b = P_last;
		P_last = k;
	}
	P[k].c = -5;
	while(k!=v)
	{
		info[k] = 1;
		k = parent[k];
	}
	//deleting vertex 'v' from T
	if(T[v].u == -5 && T[v].v == -5)
	{
		T[v].u = -1;
		T[v].v = -1;
		
		T_first = -5;
		T_last = -5;
		isroot[v] = -1;
		return;
	}
	if(T[v].u == -5)
	{	
		T[T[v].v].u = -5;
		T_first = T[v].v;
	}
	else if(T[v].v == -5)
	{
		T_last = T[v].u;
		T[T[v].u].v = -5;
	}
	else
	{
		T[T[v].u].v = T[v].v;
		
		T[T[v].v].u = T[v].u;
	}
	isroot[v] = -1;
	T[v].u = -1;
	T[v].v = -1;
	/*
	printf("after alter T for e\n\n");
	printf("Printing T : ");
	for(i = 0;i<maxNode;i++)
	{
		printf("T[%d].u = %d\nT[%d].v = %d\n\n",i,T[i].u,i,T[i].v);
	}
	printf("Printing p : ");
	for(i = 0;i<maxNode;i++)
	{
		printf("P[%d].a = %d\nP[%d].b = %d\nP[%d].c = %d\n\n",i,P[i].a,i,P[i].b,i,P[i].c);
	}
	printf("T_first = %d\n",T_first);
	printf("T_last = %d\n",T_last);
	printf("P_first = %d\n",P_first);
	printf("P_last = %d\n",P_last);*/
}

void alter_T_for_v(int v)
{
	int i = 0;
	//inserting children of v to T
	if(tree_degreeList[v]!=0)
	{
		T[T_last].v = tree_adjList[v][0];
		
		isroot[tree_adjList[v][0]] = 1;
		T[tree_adjList[v][0]].u = T_last;
		T[tree_adjList[v][0]].v = -5;
		for(i=1;i<tree_degreeList[v];i++)
		{
			isroot[tree_adjList[v][i]] = 1;
			T[tree_adjList[v][i-1]].v = tree_adjList[v][i];
			
			T[tree_adjList[v][i]].u = tree_adjList[v][i-1];
			T[tree_adjList[v][i]].v = -5;
		}
		T_last = tree_adjList[v][tree_degreeList[v] - 1];
	}
	
	int k = v;
	//inserting hanging subtrees
	if(isroot[k]!=1)
	{
		while(isroot[v]!=1)
		{
			for(i=0;i<tree_degreeList[parent[v]];i++)
			{
				if(tree_adjList[parent[v]][i]!=v)
				{
					isroot[tree_adjList[parent[v]][i]] = 1;
					T[T_last].v = tree_adjList[parent[v]][i];
					
					T[tree_adjList[parent[v]][i]].u = T_last;
					T[tree_adjList[parent[v]][i]].v = -5;
					T_last = tree_adjList[parent[v]][i];
				}
			}
			pathparam[parent[v]].down = parent[k];
			pathparam[parent[v]].up = &pointers[p_count];
			info[parent[v]] = 1;
			v = parent[v];		
		}
		pointers[p_count] = v;
		p_count++;
		hash[parent[k]]=&root_node[root_count++];
		hash[parent[k]]->left=hash[parent[k]]->right=NULL;
		hash[parent[k]]->sep=-1;
		hash[parent[k]]->u=parent[k];
		hash[parent[k]]->v=v;
		//printf("inserting in hash %d , %d\n",parent[k],v);
		//inserting path in P
		P[parent[k]].a = v;
		if(P_first == -5)
		{
			P_first = parent[k];
			P_last = parent[k];
			P[parent[k]].b = -5;
		} 
		else
		{
			P[P_last].c = parent[k];
			P[parent[k]].b = P_last;
			P_last = parent[k];
		}
		P[parent[k]].c = -5;
	}
	//deleting vertex from T
	if(T[v].u == -5 && T[v].v == -5)
	{
		T[v].u = -1;
		T[v].v = -1;
		
		T_first=-5;
		T_last=-5;
		isroot[v]=-1;
	}
	else if(T[v].u == -5)	//if it is the first vertex in T
	{	
		T[T[v].v].u = -5;
		T_first = T[v].v;
		T[v].u = -1;
		T[v].v = -1;
		
		isroot[v]=-1;
	}
	else if(T[v].v == -5)
	{
		T_last = T[v].u;
		T[T[v].u].v = -5;
		T[v].u = -1;
		T[v].v = -1;
		
		isroot[v]=-1;
	}
	else
	{
		T[T[v].u].v = T[v].v;
		
		T[T[v].v].u = T[v].u;
		T[v].u = -1;
		T[v].v = -1;
		
		isroot[v]=-1;
	}
	
	/*
	printf("after alter T for v\n\n");
	printf("Printing T : ");
	for(i = 0;i<maxNode;i++)
	{
		printf("T[%d].u = %d\nT[%d].v = %d\n\n",i,T[i].u,i,T[i].v);
	}
	printf("Printing p : ");
	for(i = 0;i<maxNode;i++)
	{
		printf("P[%d].a = %d\nP[%d].b = %d\nP[%d].c = %d\n\n",i,P[i].a,i,P[i].b,i,P[i].c);
	}
	printf("T_first = %d\n",T_first);
	printf("T_last = %d\n",T_last);
	printf("P_first = %d\n",P_first);
	printf("P_last = %d\n",P_last);*/
}
	
struct array* filterEdge(struct array* arr,int sno,int *count)	//the filter edges are from child to parent
{
	int i,j;
	struct array* failEdges=(struct array*)malloc(sizeof(struct array)*sno);
	for(i=0;i<sno;i++)
	{
		if(parent[arr[i].u]==arr[i].v)
		{
			failEdges[(*count)].u=arr[i].u;		//child is stored in failedges[i].u and parent in failedges[i].v
			failEdges[(*count)++].v=arr[i].v;
		}
		else if(parent[arr[i].v]==arr[i].u)
		{
			
			failEdges[(*count)].u=arr[i].v;
			failEdges[(*count)++].v=arr[i].u;
		}
	}
	return failEdges;
}
int* Failed_V_input(int *countVe)
{
	int v,i=0;
	FILE *fp=fopen(dvfile,"r+");
	
	while(fscanf(fp,"%d\n",&v)!=EOF)
	{
		(*countVe)++;
	}
	//*countVe=3;
	int* failedV=(int*)malloc(sizeof(int)*(*countVe));
	rewind(fp);
	
	while(fscanf(fp,"%d",&v)!=EOF)
	{	
		failedV[i]=v;
		i++;
	}
	fclose(fp);
	return failedV;
}

struct array* Failed_E_input(int *countE)
{
	int v,u,i=0;
	
	FILE *fp=fopen(defile,"r+");
	while(fscanf(fp,"%d %d",&v,&u)!=EOF)
	{
		(*countE)++;
	}
	//*countE=3;
	struct array* failedE=(struct array*)malloc(sizeof(struct array)*(*countE));
	 rewind(fp);
	while(fscanf(fp,"%d %d",&u,&v)!=EOF)
	{	
		failedE[i].v=v;
		failedE[i].u=u;
		i++;
	}
	fclose(fp);
	return failedE;
}
struct array* initialize_L(int *countIE)
{
	int u, v,i=0;
	FILE *fp=fopen(iefile,"r+");
	(*countIE) = 0;
	while(fscanf(fp,"%d %d\n",&u,&v)!=EOF)
	{
		(*countIE)++;
	}
	
	struct array* insertedE=(struct array*)malloc(sizeof(struct array)*(*countIE));
	rewind(fp);
	
	while(fscanf(fp,"%d %d",&u,&v)!=EOF)
	{	
		insertedE[i].u = u;
		insertedE[i].v = v;
		//printf("Reading edge %d - %d from file\n",insertedE[i].u,insertedE[i].v);
		i++;
	}
	fclose(fp);
	return insertedE;
}
void inserted_vertices()
{
	//countIV = 0;
	int v;
	FILE *fp=fopen(ivfile,"r+");
	
	//int* insertedV=(int*)malloc(sizeof(int)*(maxNode));*/
	
	while(fscanf(fp,"%d\n",&v)!=EOF)
	{	
		countIV = v;
	}
	//countIV = i;
	fclose(fp);
	//return insertedV;	
}
int main6()
{
	main5();
	start = clock();
	int i,j;
	inserted_vertices();
	info = (int *)calloc(maxNode+countIV,sizeof(int));
	isroot = (int *)calloc(maxNode+countIV,sizeof(int));
	pathparam = (struct path *)malloc((maxNode+countIV)*sizeof(struct path));
	hash=(struct pathnode**)malloc(maxNode*sizeof(struct pathnode*));
	root_node=(struct pathnode*)malloc(maxNode*sizeof(struct pathnode));
	T = (struct array*)malloc((maxNode+countIV)*sizeof(struct array));
	P = (struct triple*)malloc((maxNode+countIV)*sizeof(struct triple));
	for(i=0;i<maxNode+countIV;i++)
	{
		pathparam[i].down = -1;
		j = -1;
		(pathparam[i].up) = &j;
		//printf("pathparam[%d].up = %d\n\n",i,*(pathparam[i].up));
	}
	pointers = (int *)malloc(maxNode*(sizeof(int)));
	p_count = 0;
	initialize();
	
	
	degree_L=(int *)malloc(sizeof(int)*(maxNode+countIV));
	L=(int **)malloc(sizeof(int *)*(maxNode+countIV));
	for(i=0;i<maxNode+countIV;i++)
	{
		degree_L[i]=0;
		L[i]=(int *)malloc(sizeof(int)*(maxNode+countIV));	
	}
	for(i=1;i<maxNode+countIV;i++)
	{
		L[0][maxNode+countIV-i-1]=i;
		
	}
	/*for(i=0;i<countIV;i++)
	{
		L[0][i]=maxNode+i;		
	}*/
	degree_L[0]=maxNode+countIV-1;
	//inserting singleton paths of inserted vertices i.e insert_in_P(addedV[i],addedV[i]);
	/*if(countIV!=0)
	{
		if(P_first == -5)
		{
			P_first = addedV[0];
			P_last = addedV[0];
			P[addedV[0]].b = -5;
		} 
		else
		{
			P[P_last].c = addedV[0];
			P[addedV[0]].b = P_last;
			P_last = addedV[0];
		}
		P[addedV[0]].c = -5;
				P[addedV[0]].a = addedV[0];
		for(i=1;i<countIV;i++)
		{
			P[addedV[i]].a = addedV[i];
			P[P_last].c = addedV[i];
			P[addedV[i]].b = P_last;
			P_last = addedV[i];
			P[addedV[i]].c = -5;
		}
	}*/

	int countIE;
	struct array* addedE = initialize_L(&countIE);
	for(i=0;i<countIE;i++)
	{
		L[addedE[i].u][(degree_L[addedE[i].u])++] = addedE[i].v;
		L[addedE[i].v][(degree_L[addedE[i].v])++] = addedE[i].u;
	}
	
	failedV=Failed_V_input(&countV);
	int countE=0;
	struct array* failedE=Failed_E_input(&countE);
	
	//change started
	
	//printf("\n\nhere \n");
	
	int ind;//u desc and v ansc
	for(i=0;i<countE;i++)	//countE is no of deleted edges
	{
		//seg_count=0;
		//disjoint_subtrees(1,maxNode-1,0,preorderList[failedE[i].u], preorderList[failedE[i].u]);
		seg_nodes[0]=leaf_index[failedE[i].u];
		ind=2*seg_nodes[0]+1;
		//printf("..index = %d %d for u = %d position = %d/n",ind,seg_nodes[0],failedE[i].u,preorderList[failedE[i].u]);
		while(ind!=0)
		{
			ind=(ind-1)/2;
			//printf("deleting index %d ,edge %d %d\n",ind,failedE[i].u,failedE[i].v);
			segTree[ind].bst=delete_bst(segTree[ind].bst,failedE[i].u,failedE[i].v);
		}
		
		//seg_count=0;
		seg_nodes[0]=leaf_index[failedE[i].v];
		//disjoint_subtrees(1,maxNode-1,0,preorderList[failedE[i].v], preorderList[failedE[i].v]);
		ind=2*seg_nodes[0]+1;
		//printf("..index = %d %dfor u = %d position = %d/n",ind,seg_nodes[0],failedE[i].v,preorderList[failedE[i].v]);
		while(ind!=0)
		{
			ind=(ind-1)/2;
			//printf("deleting index %d ,edge %d %d\n",ind,failedE[i].v,failedE[i].u);
			segTree[ind].bst=delete_bst(segTree[ind].bst,failedE[i].v,failedE[i].u);
			
		}

	}
	
	//change ended
	int countEd=0;
	failedE=filterEdge(failedE,countE,&countEd);
	for(i=0;i<countV;i++)	//countV is no. of deleted vertices
	{
		if(pathparam[failedV[i]].down == -1)
			alter_T_for_v(failedV[i]);
		else
			alter_P_for_v(failedV[i]);			
	}
	for(i=0;i<countEd;i++)	//countEd is no. of deleted edges after filtering
	{
		if(pathparam[failedE[i].u].down == -1 && pathparam[failedE[i].v].down == -1) //this means that this entire edge is in a tree
			alter_T_for_e(failedE[i].u,failedE[i].v);
		else if(pathparam[failedE[i].u].down == -1 || pathparam[failedE[i].v].down == -1)
			continue;
		else
		{
			struct pathnode*t=find_param(hash[pathparam[failedE[i].u].down],level[failedE[i].u]);
	struct pathnode*m=find_param(hash[pathparam[failedE[i].v].down],level[failedE[i].u]);
			 if(t->u == m->u && t->v == m->v)
			alter_P_for_e(failedE[i].u,failedE[i].v);
		}
	}
	end = clock();
	timetaken = (double)(end - start)/CLOCKS_PER_SEC;
	printf("Time taken in D_T_P = %lf\n",timetaken);
	/*
	printf("printing T : ");
	i = T_first;
	while(i!=-5)
	{
		printf("%d ",i);
		i = T[i].v;
	}
	printf("\nT ends\n");
	printf("\nprinting P : ");
	i = P_first;
	printf("%d\n",i);
	while(i!=-5)
	{
		//printf("fdbsedgseg\ngeager\nergeg\neggewgew\n");
		printf("\n\n%d - %d\nPrev = %d\nnext = %d",i,P[i].a,P[i].b,P[i].c);
		i = P[i].c;
	}*/
	
	return 0;
}

