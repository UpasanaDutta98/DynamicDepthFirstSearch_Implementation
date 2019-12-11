#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"preorder.c"
struct triple
{
	int a;
	int b;
	int c;
};
int* segnode_bst_size;
struct bstnode
{       
	int u;
	int v;
	struct bstnode *left;
	struct bstnode *right;
	int height;
};
/*
struct seg
{
	int * seg_indices;	//array containing the indices of seg tree need to  cover a range
	int cover_size;		//no of seg tree nodes need to cover the range
};*/
struct segnode
{
	int vertex;
	struct bstnode *bst;
}*segTree;
int* seg_nodes;
int seg_count;
//struct seg ** seg_cover;
int* segnode_bst_size;
int* leaf_index;
void disjoint_subtrees(int ss, int se, int si,int u, int v)	//u and v are peorder positions
{
	if (u <= ss && v >= se)
        {
		seg_nodes[seg_count++] = si;
		return;
	}

	if (se < u || ss > v)
        	return;

	int mid = ss+(se-ss)/2;
	disjoint_subtrees(ss, mid, 2*si+1,u,v);
        disjoint_subtrees( mid+1, se, 2*si+2,u,v);
}
// A utility function to get height of the tree
int height(struct bstnode *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct bstnode* newNode(int v1, int v2)
{
    struct bstnode* node = (struct bstnode*)malloc(sizeof(struct bstnode));
	//printf("\naddress of new bst node = %p\n",&node);
node->u   = v1;
node->v = v2;
node->left   = NULL;
node->right  = NULL;
node->height = 1;  // new node is initially added at leaf
return(node);
}
 
// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct bstnode *rightRotate(struct bstnode *y)
{
    struct bstnode *x = y->left;
    struct bstnode *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct bstnode *leftRotate(struct bstnode *x)
{
    struct bstnode *y = x->right;
    struct bstnode *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(struct bstnode *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
// Recursive function to insert key in subtree rooted
// with node and returns new root of subtree.
struct bstnode* insert(struct bstnode* node, int v1, int v2)
{
	//printf("inserting in bst -  %d-%d\n",v1,v2);
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return newNode(v1,v2);
 
    if (preorderList[v2] < preorderList[node->v ])
        node->left  = insert(node->left, v1, v2);
    else
        node->right = insert(node->right, v1,v2);
    //else // Equal keys are not allowed in BST
       // return node;
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));
 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 case
    // Left Left Case
    if (balance > 1 && preorderList[v2] < preorderList[node->left->v])
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && preorderList[v2] > preorderList[node->right->v])
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && preorderList[v2] > preorderList[node->left->v])
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && preorderList[v2] < preorderList[node->right->v])
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return (node);
}

struct bstnode* create_bst(int vrtx) 
{
	int j;
	struct bstnode *root = NULL;
	for(j=0;j<degreeList[vrtx];j++)
	{
		root = insert(root,vrtx,adjList[vrtx][j]);
	
	}
	//printf("Inorder traversal of the bst for vertex %d\n",vrtx);
	  //InOrder(root);
	return root;
}
struct bstnode* delete_bst(struct bstnode* node,int u, int v)
{
	struct bstnode*par, *ptr, *child, *succ, *parsucc;
	ptr = node;
	par = NULL;
	while(ptr!=NULL)
	{

		if(v == ptr->v)
		{
			if(u == ptr->u)
				break;
			else
			{
				if(preorderList[u]<preorderList[ptr->u])
				{
					par = ptr;
					ptr = ptr->left;
					continue;
				}
				else
				{
					par = ptr;
					ptr = ptr->right;
					continue;
				}
			}
		}
		par = ptr;
		if(preorderList[v] < preorderList[ptr->v])
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	/*printf("The node deleted has value %d - %d\n",ptr->u,ptr->v);
	if(par!=NULL)
		printf("The parent node has value %d - %d\n",par->u,par->v);
	else
		printf("parent of root value is null\n\n");*/
	if(ptr->left!=NULL && ptr->right!=NULL)
	{
		parsucc = ptr;
		succ = ptr->right;
	//	printf("right subtree has the head value of %d %d\n",succ->u,succ->v);
		while(succ->left!=NULL)
		{
			parsucc = succ;
			succ = succ->left;
		}
		ptr->u = succ->u;
		ptr->v = succ->v;
		ptr = succ;
		par = parsucc;
	}
	if(ptr->left!=NULL)
		child = ptr->left;
	else
		child = ptr->right;
	/*if(child == NULL)
		printf("null child\n");
	else 
		printf("child = %d %d\n",child->u,child->v);*/
	if(par == NULL)
		node = child;
	else if(ptr == par->left)
		par->left = child;
	else
	{
		//printf("ptr is right child of parent\n");
		par->right = child;
	}
	//printf("The node deleted has value %d - %d\n",ptr->u,ptr->v);
	free(ptr);
	return node;
}
struct array *merge(struct array arr1[], struct array arr2[], int m, int n) //change
{
	struct array *mergedarray=(struct array*)malloc(sizeof (struct array)*(m+n)); //change
	int i = 0, j = 0, k = 0;
	while (i < m && j < n)
	{
		if (preorderList[arr1[i].v] < preorderList[arr2[j].v]) //error
		{
		    mergedarray[k].u = arr1[i].u;
		    mergedarray[k].v = arr1[i].v;
		    i++;
		}
		else if(preorderList[arr1[i].v] > preorderList[arr2[j].v])
		{
		   mergedarray[k].u = arr2[j].u;
		   mergedarray[k].v = arr2[j].v;
		   j++;
		}
		else
		{
			if(preorderList[arr1[i].u] < preorderList[arr2[j].u])
			{
			    mergedarray[k].u = arr1[i].u;
			    mergedarray[k].v = arr1[i].v;
			    i++;
			}
			else
			{
				  mergedarray[k].u = arr2[j].u;
				  mergedarray[k].v = arr2[j].v;
				  j++;
			}
		}
		k++;
	}
	while (i < m)
	{
		mergedarray[k].u = arr1[i].u;
		mergedarray[k].v = arr1[i].v;
		i++; k++;
	}
	while (j < n)
	{
		mergedarray[k].u = arr2[j].u;
		mergedarray[k].v = arr2[j].v;
		j++; k++;
	}
	return mergedarray;
}

void storeInorder(struct bstnode* node, struct array inorder[], int *index_ptr) //change
{
	if (node != NULL)
	{
		storeInorder(node->left, inorder,index_ptr);
		inorder[*index_ptr].u = node->u; //change
		inorder[*index_ptr].v = node->v;

		(*index_ptr)++;  
		storeInorder(node->right, inorder, index_ptr);
	}
}
struct bstnode* sortedArrayToBST(struct array arr[], int start, int end) //change
{
	if (start > end)
	return NULL;

	int mid = (start + end)/2;
	struct bstnode *root = newNode(arr[mid].u, arr[mid].v); //change

	root->left =  sortedArrayToBST(arr, start, mid-1);
	root->right = sortedArrayToBST(arr, mid+1, end);
	return root;
}
 
struct bstnode* mergeTrees(struct bstnode *root1, struct bstnode *root2, int k)//error
{
    	struct array *arr1;
	int i=0, m = segnode_bst_size[2*k+1], n = segnode_bst_size[2*k+2];//change
	arr1=(struct array*)malloc(sizeof (struct array)*m); //change
	storeInorder(root1,arr1,&i);
	/*printf("Printing the inorder of 1st bst for i = %d:\n",k);
	for(i=0;i<m;i++)
	printf("%d %d\n",arr1[i].u,arr1[i].v);*/
	struct array *arr2;
	int j=0;
	arr2=(struct array*)malloc(sizeof (struct array)*n);

	storeInorder(root2,arr2,&j);
	//printf("Printing the inorder of 2nd bst for i = %d :\n",k);
	/*printf("second bst size = %d\n",n);
	for(i=0;i<n;i++)
	printf("%d %d\n",arr2[i].u,arr2[i].v);*/
	struct array *mergedarray= merge(arr1,arr2,m,n);
	/*printf("Printing the inorder of merged bst for node number %d :\n",k);
	for(i=0;i<n+m;i++)
	printf("%d %d\n",mergedarray[i].u,mergedarray[i].v);*/
	free(arr1);
	free(arr2);
    	return sortedArrayToBST (mergedarray, 0, m+n-1);
}

struct bstnode* create_segTree(int ss, int se, int si)
{

	if(ss==se)
	{
		segTree[si].bst=create_bst(preorderList1[ss]);
		//printf("segtree[%d].bst-> u = %d\nsegtree[%d].bst-> v = %d\n",si,segTree[si].bst->u,si,segTree[si].bst->v);
		segTree[si].vertex=preorderList1[ss];
		segnode_bst_size[si]=degreeList[preorderList1[ss]];
		leaf_index[preorderList1[ss]] = si;	//index of the segment tree that covers the vertex - preorderList[ss] is si.
		return segTree[si].bst;
	}

	int mid=ss+(se-ss)/2;
	struct bstnode *e2=create_segTree(mid+1,se,si*2+2);
	struct bstnode *e1=create_segTree(ss,mid,si*2+1);
	segTree[si].bst=mergeTrees(e1,e2,si);
	//printf("segtree[%d].bst-> u = %d\nsegtree[%d].bst-> v = %d\n",si,segTree[si].bst->u,si,segTree[si].bst->v);	
	segTree[si].vertex=-1;
	segnode_bst_size[si]=segnode_bst_size[2*si+1]+segnode_bst_size[2*si+2];
	return segTree[si].bst;
	
}/*
void calc_seg_index()
{
	int i,j,k;
	//printf("\nhey\n\n");
	seg_cover = (struct seg **)malloc((maxNode) * sizeof(struct seg *));
    	for (i=0; i<maxNode; i++)
        	seg_cover[i] = (struct seg *)malloc((maxNode) * sizeof(struct seg));
	//printf("\n\nhey end\n\n");
	for(i = 0;i<maxNode;i++)
		for(j=i;j<(maxNode);j++)
		{
			seg_count = 0;
			seg_nodes = (int*)malloc(sizeof(int)*maxNode);
			disjoint_subtrees(0,maxNode-1,0,i,j);
			
			seg_cover[i][j].seg_indices = (int*)malloc(sizeof(int) * seg_count);
			/*
			if(seg_cover[i][j].seg_indices)
				printf("\nnot null %d %d\n",i,j);
			else
			{
				printf("\nnull malloc\n");
				return;
			}
			seg_cover[i][j].cover_size = seg_count;
			for(k = 0;k<seg_count;k++)
				seg_cover[i][j].seg_indices[k] = seg_nodes[k];
			free(seg_nodes);
		}
	/*
	printf("\nPrinting seg cover \n");
	for(i = 0;i<maxNode;i++)
		for(j = i;j<maxNode;j++)
		{
			printf("from %d to %d - ",i,j);
			for(k = 0;k<seg_cover[i][j].cover_size;k++)
				printf("%d ",seg_cover[i][j].seg_indices[k]);
			printf("\n\n");
		}
	
	//disjoint_subtrees(0,maxNode-1,0,1,1);
}*/

int main3()
{
	main1();
	leaf_index = (int*)malloc(sizeof(int)*(maxNode-1));
	int x=(int)(ceil(log2(maxNode-1)));
	int size=2*(int)pow(2,x)-1;
	//printf("size of seg tree : %d\n",size);
	segTree=(struct segnode*)malloc(sizeof(struct segnode)*size);
	segnode_bst_size=(int*)malloc(sizeof(int)*size);
	create_segTree(1,maxNode-1,0);
	//calc_seg_index();
	seg_nodes = (int*)malloc(sizeof(int)*(maxNode-1));
	end = clock();
	timetaken = (double)(end - start)/CLOCKS_PER_SEC;
	printf("Time taken upto creating seg_tree = %lf\n",timetaken);//range as first two param , the index of root
	/*segnode_bst_size = (int*)malloc(3*sizeof(int));
	segnode_bst_size[0] = 12;
	segnode_bst_size[1] = 6;
	segnode_bst_size[2] = 6;
	struct bstnode* bst1 = create_bst(0);
	printf("\n\nRoot of bst for node value 0 is %d %d\n\n",bst1->u,bst1->v);
	struct bstnode* bst2 = create_bst(1);
	printf("\n\nRoot of bst for node value 1 is %d %d\n\n",bst2->u,bst2->v);
	struct bstnode* bst = mergeTrees(bst1, bst2, 0);
	printf("\n\nRoot of merged bst is %d %d\n\n",bst->u,bst->v);
	bst1 = delete_bst(bst1,0,4);
	printf("Printing after deleting 0,4 from bst of node 0\n");
	InOrder(bst1);
	bst = delete_bst(bst,0,4);
	printf("Printing after deleting 0,4 from bst of mergined node\n");
	InOrder(bst);
	struct bstnode* bst3 = delete_bst(bst2,1,6);
	printf("Printing after deleting 1,6 from bst of node 1\n");
	InOrder(bst3);
	bst = delete_bst(bst,1,6);
	printf("Printing after deleting 1,6 from bst of merged node\n");
	InOrder(bst);*/
	return 0;
}

