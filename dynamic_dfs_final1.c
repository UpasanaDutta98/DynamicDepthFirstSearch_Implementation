#include "dfs_in_tree.c"
# define initial 1
# define visited 2
int *fparent;
int *flevel;
int *ftree_degreeList;
int **ftree_adjList;
void Dfs_final()
{ 
	head=NULL;
	int i,w,u;
	fparent = (int*)malloc((maxNode+countIV)* sizeof(int));
	flevel = (int*)malloc((maxNode+countIV)* sizeof(int));
	ftree_degreeList = (int*)calloc(maxNode+countIV, sizeof(int));
	
	int status[maxNode+countIV];

	for(i=0;i<maxNode+countIV;i++)
	{
		status[i]=initial;
	}
	for(i=0;i<countV;i++)
	{
		status[failedV[i]]=visited;
		fparent[failedV[i]]=-1;
	}
	int r=0,j;
	int *path;

	push(r);
	status[r]=visited;
	fparent[0]=-1;
	flevel[0]=1;
	/*for(i=0;i<maxNode+countIV;i++)
	{
		printf("L(%d) : ",i);
		for(j=0;j<degree_L[i];j++)
		printf("%d ",L[i][j]);
		printf("\n");
	}*/
	//start = clock();
	while(!isEmpty_stack())
	{
		w=peek();
		//printf("present vertex = %d \n",w);
		if(degree_L[w]==0)
		{
		//	printf("degree_L[%d] == 0\n",w);
			/*printf("printing the stack : ");
			struct stack* temp = head;
			while(temp!=NULL)
			{
				printf("%d ",temp->v);
				temp = temp->next;
			}*/
			//printf("\nPopping %d\n",w);
			pop();
		}
		else
		{
		//	printf("\nPrinting L of w=%d : ",w);
		//	for(j=0;j<degree_L[w];j++)
		//		printf("%d ",L[w][j]);
		//	printf("\n");
			u=L[w][degree_L[w]-1];
		//	printf(" u = %d\n",u);
			//printf("pathparam[%d].u = %d\npathparam[%d].v = %d\n",u,pathparam[u].u,u,pathparam[u].v);
			degree_L[w]--;
			if(u>=maxNode)
			{
				info[u]=-1;
				dist=1;
				/*fparent[u]=w;
				flevel[u]=flevel[fparent[u]]+1;
				info[u]=-1;
				status[u]=visited;
				push(u);*/
		//		printf("fparent of %d = %d\n",u,w);
			}
			//check++;
			if(status[u]==initial && u!=0)
			{
				//v_count++;
				if(pathparam[u].down!=-1 && *(pathparam[u].up)!=-1 && info[u]==1)//to check if u belongs to path
				{
					//printf("Doing dfs in path for u = %d\n",u);}
					path=dfs_in_path(u);
				}
				else if(info[u]==0)//if its a tree
				{
					//printf("Doing dfs in tree for u = %d\n",u);
					path=dfs_in_tree(u);
				}
		//		else
		//			printf("%d neither in path nor in tree\n",u);
		//		printf("'path returned : \n");
		//		for(i=0;i<dist;i++)
		//		{
		//			printf("%d \n\n",path[i]);
		//		}
				fparent[u]=w;
				info[u]=-1; 
				flevel[u]=flevel[fparent[u]]+1;
		//		printf("fparent[%d] = %d\n",u,fparent[u]);
				status[u]=visited;
		//		printf("Pushing %d in stack\n",u);
				push(u);
		//		printf("inserting the remaining path into stack and setting their parents\n\n");
				for(i=1;i<dist;i++)
				{
					
					fparent[path[i]]=path[i-1];
					 
					flevel[path[i]]=flevel[fparent[path[i]]]+1;
					info[path[i]]=-1;
					//printf("\nFor remaining part of the path\n");
		//			printf("fparent[%d] = %d\n",path[i],fparent[path[i]]);
					status[path[i]]=visited;
		//			printf("Pushing %d in stack\n",path[i]);
					push(path[i]);
				}
		//		printf("insertion of the path ends here.\n");
			
				
			}	

						
		}
		
	}
}
int main()
{
	main7();
	/*printf("Printing L :");
	/*int i,j;
	for(i=0;i<maxNode+countIV;i++)
	{
		printf("L(%d) : ",i);
		for(j=0;j<degree_L[i];j++)
		printf("%d ",L[i][j]);
		printf("\n");
	}*/

	//printf("\n\n\nStarting Dfs_final()\n\n\n");
	start = clock();
	Dfs_final();
	end = clock();
	//end = clock();
	int i;
	ftree_adjList = (int**)malloc((maxNode+countIV)*sizeof(int*));
	for(i=0; i<maxNode+countIV; i++)
    	{
		//if((int*)malloc(maxNode+countIV*sizeof(int)) == NULL)
		//	printf("null return\n");
        	ftree_adjList[i] = (int*)malloc((maxNode+countIV)*sizeof(int));
		
   	}
	int *fcount=(int *)calloc(maxNode+countIV,sizeof(int));
	for(i=1;i<maxNode+countIV; i++)
    	{
			if(fparent[i]!=-1)
			{
				ftree_degreeList[fparent[i]]++;
				ftree_adjList[fparent[i]][(fcount[fparent[i]])++] = i;
			}
	}
	//printf("size = %d",seg_cover[4][4].cover_size);
	//printf("fparent of 21 : %d\n",fparent[21]);
	//end = clock();
	timetaken = (double)(end - start)/CLOCKS_PER_SEC;
	//printf("Time taken in total dfs_in_tree = %lf\n",sum2);
	//printf("Time taken in total dfs_in_path = %lf\n",sum1);
	//printf("Time taken in total find_edge = %lf\n",sum3);
	printf("Time taken in DFS_Final = %lf\n",timetaken);
	
	//printf("check = %d\n",check);
	//printf("if condition satisfied = %d\n",v_count);
	//printf("null count for find edge = %d\n",null_count);
	//printf(" no of times x is not desc of y for query(w,x,y) = %d\n",desc_count);	
	//printf("final dfs tree\n");
	int j;
	/*for(i=0;i<maxNode+countIV;i++)
	{
		printf("fparent of %d is : %d \n",i,fparent[i]);
	}*/
	
	/*int x,y,count = 0;
	char s1[15],s2[15];
	FILE *fmap = fopen("inv_map.txt","r+");
	while(fscanf(fmap,"%s\n",s1) != EOF)
	{
		count++;
	}
	rewind(fmap);
	int** inv_map = (int**)malloc(count*sizeof(int*));
	for(i=0;i<count;i++)
		inv_map[i] = (int*)malloc(2*sizeof(int));

	//printf("\n\nprinting inv map \n\n");
	i=0;
	while(fscanf(fmap, "%s %s",s1,s2)!=EOF)
	{
		//fscanf(fmap, "%s",s1);
		//fscanf(fmap, "%s",s2);
		x = atoi(s1);
		y = atoi(s2);
		//printf("%s %s\n",s1,s2);
		inv_map[i][0] = x;
		inv_map[i][1] = y;
		i++;
	}*/

	/*fclose(treeadjFile);
	for(i=0;i<maxNode+countIV;i++)
	{
		for(j=0;j<ftree_degreeList[i];j++)
		{
			ftree_adjList[i][j] = inv_map[ftree_adjList[i][j]-1][1];	
		}
	}
	treeadjFile = fopen("ftree_adjList_final.txt","w+");
	int a;	
    for(i=0; i<maxNode+countIV; i++)
    {
	if(i==0);
		a = 0;
	else
		a = inv_map[i-1][1];
        fprintf(treeadjFile, "%d : ", a);	//change i as inv_map[i-1][1] but not when i = 0
        for(j=0; j<ftree_degreeList[i]; j++)
        {
            fprintf(treeadjFile, "%d ", ftree_adjList[i][j]);
        }
        fprintf(treeadjFile, "\n");
    }
	fclose(treeadjFile);*/
	/*end = clock();
	timetaken = (double)(end - start)/CLOCKS_PER_SEC;
	printf("Time taken = %lf\n",timetaken);*/

	//printf("\n\n%d %d\n\n",preorderList[4],preorderList[39]);
	
	FILE* treeadjFile = fopen("ftree_adjList.txt","w+");	
    for(i=0; i<maxNode+countIV; i++)
    {
        fprintf(treeadjFile, "%d : ", i);
        for(j=0; j<ftree_degreeList[i]; j++)
        {
            fprintf(treeadjFile, "%d ", ftree_adjList[i][j]);
        }
        fprintf(treeadjFile, "\n");
    }
	FILE *ftree_deg_File = fopen("ftree_degreeList.txt", "w+");

    for(i=0; i<maxNode+countIV; i++)
    {
        fprintf(ftree_deg_File, "%d %d\n", i, ftree_degreeList[i]);
    }

    fclose(ftree_deg_File);
}
