#include<stdio.h>
#include<stdlib.h>
#include"D_T_P1.c"
int dist;
//double sum1=0,sum2=0;


int* dfs_in_path(int u)
{
	//printf("Doing dfs in path for u = %d\n",u);
	//clock_t s1, e1;
	//double 	TT1;
	//s1 = clock();
	int *w;
	/*
	if(u>=maxNode)
	{
		delete_from_P(u);
		w = (int*)malloc(sizeof(int));
		w[0] = u;
		dist = 1;
		//printf("Since u>=maxNode, returning path %d - %d\n",w[0],w[0]);
		return w;
	}*/
	struct pathnode*t=find_param(hash[pathparam[u].down],level[u]); 
	
	int v= t->u,de = t->v,temp,flag=0,flag1=0,flag_v= 0;
	//printf("u=%d ,v=%d ,de=%d",u,v,de);
	//printf("level[de] = %d\nlevel[u] = %d\nlevel[v] = %d\n",level[de],level[u],level[v])
		//printf("\n\nt->u = %d, t->v = %d\n",t->u,t->v);
	int c=parent[u];
	if(u == de)
		c = u;
	//printf("u = %d\nparent[u] = %d\nc = parent[u] = %d\n",u,parent[u],c);
	delete_from_P(v);
	//int l1 = abs(level[u] - level[de]);
	//int l2 = abs(level[v] - level[u]);
	//printf("before first dist, u = %d\n",u);
	//Dist_path(u,de);
	//	printf("\n\nfirst one is cool\n\n");
	//printf("v = %d\n",v);
	//Dist_path(v,u);
//		printf("\n\nsecond one is cool\n\n");
	if(Dist_path(u,de)>Dist_path(v,u))
	{
		temp=v;
		v=de;
		de=temp;
		flag1=1;
		flag_v=1;//v is ancestor
		w=Fpath(de,u);
		if(d>1)
		c=w[d-2];
	}
	if(flag_v==1)//v is ancestor
	{
		if(d>1)
		{
			//printf("de = %d,  c = %d in 55\n",de,c);
			int h,x=-1;
			for(h=0;h<tree_degreeList[u];h++)
			{
				if(pathparam[tree_adjList[u][h]].down==pathparam[u].down)
				{
					x=tree_adjList[u][h];
					break;
				}
			}
			//insert_pathtree(t,level[u],de,x,0);
			insert_in_P(de,x);
		}
		w=Fpath(u,v);
		dist = Dist_path(u,v);
	}
	else//u is ancestor
	{
		if(c!=u)
		{
				//printf("de = %d,  c = %d in 66\n",de,c);
				//insert_pathtree(t,level[u],c,de,1);
				insert_in_P(c,de);			
		}
		w=Fpath(v,u);
		dist = Dist_path(v,u);
		
	}

	int i,m;
	
	m = P_first;
	while(m!=-5)
	{

		for(i=dist-1;i>=0;i--)
		{
			struct array *qedge=QUERY2(w[i],m,P[m].a,0);	//1 means closest to descendant

			if(qedge!=NULL)
			{		
				/*flag=0;
				//printf("The edge from vertex %d closest to %d on the path from %d to %d is (%d, %d)\n",w[i],P_ch->u,P_ch->u,P_ch->v,qedge->u,qedge->v);
				int j;
				for(j=0;j<degree_L[qedge->u];j++)
				{
					if(L[qedge->u][j]==qedge->v)
						{flag=1;
						//printf("%d already there in L(%d) \n",qedge->v, qedge->u);
						break;}
				}
				if(flag==0)
				{
					//printf("degree_L[%d] = %d\n",qedge->u,degree_L[qedge->u]);*/
					L[qedge->u][degree_L[qedge->u]++]=qedge->v;
					//printf("degree_L[%d] = %d\n",qedge->u,degree_L[qedge->u]);
					//printf("inserting %d in L(%d) for query on path %d - %d\n",qedge->v,qedge->u,P_ch->u,P_ch->v);
					//printf("L[%d][%d] = %d\n",qedge->u,degree_L[qedge->u] -1, L[qedge->u][degree_L[qedge->u]-1]);
				//}
			}
			//else 
				//printf("no edge from vertex %d to path %d - %d\n",w[i],P_ch->u,P_ch->v);

				
			
		}
		m=P[m].c;
	}
	m = T_first;
	int j;
	while(m!=-5)
	{
		//printf("\n\nChecking for subtree rooted at %d\n",T_ch->vertex);
				//printf("m inside dfs_in_path  = %d\n",m);
		struct array* qedge;
		if(flag_v == 1)	//v is ancestor
		{
			
			qedge=QUERY(m,u,v,1);	//1 means closer to the 3rd parameter
		}
		else
		{
			
			qedge=QUERY(m,v,u,0);	//0 means closer to the 2nd parameter
		}
		if(qedge!=NULL)
		{
			/*flag=0;
			for(j=0;j<degree_L[qedge->v];j++)
			{
				if(L[qedge->v][j]==qedge->u)
					{flag=1;
							//printf("%d already there in L(%d) \n",qedge->v, qedge->u);
					break;}
			}
			if(flag==0)
			{*/
				L[qedge->v][degree_L[qedge->v]++]=qedge->u;
				//printf("inserting %d in L(%d) \n",qedge->u,qedge->v);
				//printf("L[%d][%d] = %d\n",qedge->v,degree_L[qedge->v] -1, L[qedge->v][degree_L[qedge->v]-1]);
				//}
			
			
		}
				//printf("T[m].v inside dfs_in_path  = %d\n",T[m].v);
		m=T[m].v;
		//printf("m->next inside dfs_in_path  = %d\n",m);
		
	}
	//e1 = clock();
	//TT1 = (double)(e1 - s1)/CLOCKS_PER_SEC;
	//sum1+=TT1;
	if(flag1 == 0)
	{
		int k;int *w1 = (int*)malloc(sizeof(int)*dist);
		for(k=0;k<dist;k++)
		{
			w1[k]=w[dist-k-1];
		}
		return w1;
	}
	
	return w;
}













int* dfs_in_tree(int u)
{
	//printf(" u = %d\n",u);
	//clock_t s2,e2;
	//double TT2;
	//s2 = clock();
	int m;
	int v=u,flag=0,i,j;
	m = P_first;
	//printf("info of u = %d\n\n",info[u]);
	//if(isroot[v]!=1)
	while(isroot[v]!=1)
	{
		//printf("parent = %d\n",v);
		v=parent[v];
	}	
	
	
	
	//deleting from T
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
		
	//deleting from T ends
	
	
	
	int *w=Fpath(u,v);
	dist = (abs)(level[u]-level[v]+1);
	struct array* qedge;
	struct array* qedge2;
	//printf("dist pf path %d - %d =%d",u,v,dist);
	for(i=0;i<dist;i++)
	{
		//printf("\ndoing for vertex %d\n",w[i]);
		m = P_first;
		while(m!=-5)
		{
			
			qedge2=QUERY2(w[i],m,P[m].a,0);
				//printf("checking for %d to path %d - %d\n",w[i],m,P[m].a);
			
			if(qedge2!=NULL)
			{		
			/*	flag=0;
			
				//printf("The edge from vertex %d closest to %d on the path from %d to %d is (%d, %d)\n",w[i],P_ch->u,P_ch->u,P_ch->v,qedge2->u,qedge2->v);
			/*	for(j=0;j<degree_L[qedge2->u];j++)
				{
					if(L[qedge2->u][j]==qedge2->v)
						{flag=1;
			//			printf("%d already there in L(%d) \n",qedge2->v, qedge2->u);
						break;}
				}
				if(flag==0)
				{*/
					L[qedge2->u][degree_L[qedge2->u]++]=qedge2->v;
					//printf("inserting %d in L(%d) \n",qedge2->v,qedge2->u);
					//printf("L[%d][%d] = %d\n",qedge2->u,degree_L[qedge2->u] -1, L[qedge2->u][degree_L[qedge2->u]-1]);
					//printf("printing L[%d]\n",qedge2->u);
					/*for(j=0;j<degree_L[qedge2->u];j++)
						printf("%d ",L[qedge2->u][j]);
					printf("\n\n");*/
		//		}
			}
			//else 
				//printf("no edge from vertex %d to path %d - %d\n",w[i],P_ch->u,P_ch->v);
			
			m=P[m].c;
		}
	
		//int k;
		for(j=0;j<tree_degreeList[w[i]];j++)
		{
			if(i==0 ||  tree_adjList[w[i]][j]!=w[i-1])
			{
								//printf("checking for subtree at %d to path %d - %d\n",tree_adjList[w[i]][j],u,v);
				qedge=QUERY(tree_adjList[w[i]][j],u,v,1);	//0 means closest to ancestor
				if(qedge!=NULL)
				{
					/*flag=0;
					for(k=0;k<degree_L[qedge->v];k++)
					{
						if(L[qedge->v][k]==qedge->u)
							{flag=1;//printf("%d already there in L(%d) \n",qedge->v, qedge->u);
							break;}
					}
					if(flag==0)
					{*/
						L[qedge->v][degree_L[qedge->v]++]=qedge->u;
						//printf("inserting %d in L(%d) \n",qedge->u,qedge->v);
						//printf("L[%d][%d] = %d\n",qedge->v,degree_L[qedge->v] -1, L[qedge->v][degree_L[qedge->v]-1]);
				//	}
				
				
					//insertion in T
					isroot[tree_adjList[w[i]][j]]=1;
					if(T_first==-5)
					{
						T_first=tree_adjList[w[i]][j];
						T_last=tree_adjList[w[i]][j];
						T[T_first].u = -5;
						T[T_first].v = -5;
						//T[P_first].u = -5;
						//T[P_first].v = -5;
					}
					else{
					T[T_last].v =tree_adjList[w[i]][j];	
					T[tree_adjList[w[i]][j]].u = T_last;
					T[tree_adjList[w[i]][j]].v=-5;
					//printf(" %d inserted\n",tree_adjList[w[i]][j]);
					T_last=tree_adjList[w[i]][j];
					}
					
					
				}
			}
		}
		
	
	}
	//e2 = clock();
	//TT2 = (double)(e2 - s2)/CLOCKS_PER_SEC;
	//sum2+=TT2;
	return w;
	return NULL;
	
}
int main7()
{
	main6();
	/*int* path = dfs_in_path(12);
	printf("Printing the path returned \n");
	for(i = 0; i<dist; i++)
		printf("%d ",path[i]);
	printf("\n\n");
	printf(" after calling dfs in tree :\n\n");
	printf("path : \n");
	
	struct node_T* T_ch=T_head;
	struct node_P* P_ch= P_head;
	while(P_ch!=NULL)
	{
		printf("%d %d\n",P_ch->u,P_ch->v);
		P_ch=P_ch->next;
	}
	printf("tree\n");
	while(T_ch!=NULL)
	{
		printf("%d ",T_ch->vertex);
		T_ch=T_ch->next;
	}
	printf("\nprinting L\n");
	for(i=0;i<maxNode;i++)
	{
		printf("L(%d) : ",i);
		for(j=0;j<degree_L[i];j++)
			printf("%d ",L[i][j]);
		printf("\n");
	}*/
	return 0;
}

