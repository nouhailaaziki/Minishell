#include <stdio.h>
#include <stdlib.h>

// Binary tree node structure
typedef struct TreeNode
{
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

// Function to create a new node
TreeNode *createNode(int data)
{
	TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
	if (newNode == NULL)
	{
		printf("Memory allocation failed!\n");
		return NULL;
	}
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

// Recursive function to insert a node into the binary search tree
TreeNode *insert(TreeNode *root, int data)
{
	// Base case: if tree is empty, create a new node
	if (root == NULL)
	{
		return createNode(data);
	}

	// Recursive case: insert in the appropriate subtree
	if (data < root->data)
	{
		root->left = insert(root->left, data);
	}
	else if (data > root->data)
	{
		root->right = insert(root->right, data);
	}
	// If data equals root->data, we don't insert duplicates

	return root;
}

// Recursive function to search for a value in the tree
TreeNode *search(TreeNode *root, int data)
{
	// Base cases: root is NULL or data is found
	if (root == NULL || root->data == data)
	{
		return root;
	}

	// Recursive cases: search in left or right subtree
	if (data < root->data)
	{
		return search(root->left, data);
	}
	return search(root->right, data);
}

// Recursive function to find the minimum value node
TreeNode *findMin(TreeNode *root)
{
	if (root == NULL)
	{
		return NULL;
	}

	// Keep going left until we find the leftmost node
	if (root->left == NULL)
	{
		return root;
	}
	return findMin(root->left);
}

// Recursive function to delete a node
TreeNode *deleteNode(TreeNode *root, int data)
{
	// Base case: tree is empty
	if (root == NULL)
	{
		return root;
	}

	// Recursive cases: find the node to delete
	if (data < root->data)
	{
		root->left = deleteNode(root->left, data);
	}
	else if (data > root->data)
	{
		root->right = deleteNode(root->right, data);
	}
	else
	{
		// Node to be deleted found

		// Case 1: Node has no children (leaf node)
		if (root->left == NULL && root->right == NULL)
		{
			free(root);
			return NULL;
		}
		// Case 2: Node has one child
		else if (root->left == NULL)
		{
			TreeNode *temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			TreeNode *temp = root->left;
			free(root);
			return temp;
		}
		// Case 3: Node has two children
		else
		{
			TreeNode *temp = findMin(root->right);
			root->data = temp->data;
			root->right = deleteNode(root->right, temp->data);
		}
	}
	return root;
}

// Recursive inorder traversal (Left, Root, Right)
void inorderTraversal(TreeNode *root)
{
	if (root != NULL)
	{
		inorderTraversal(root->left);
		printf("%d ", root->data);
		inorderTraversal(root->right);
	}
}

// Recursive preorder traversal (Root, Left, Right)
void preorderTraversal(TreeNode *root)
{
	if (root != NULL)
	{
		printf("%d ", root->data);
		preorderTraversal(root->left);
		preorderTraversal(root->right);
	}
}

// Recursive postorder traversal (Left, Right, Root)
void postorderTraversal(TreeNode *root)
{
	if (root != NULL)
	{
		postorderTraversal(root->left);
		postorderTraversal(root->right);
		printf("%d ", root->data);
	}
}

// Recursive function to calculate tree height
int height(TreeNode *root)
{
	if (root == NULL)
	{
		return -1; // Height of empty tree is -1
	}

	int leftHeight = height(root->left);
	int rightHeight = height(root->right);

	return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Recursive function to count total nodes
int countNodes(TreeNode *root)
{
	if (root == NULL)
	{
		return 0;
	}
	return 1 + countNodes(root->left) + countNodes(root->right);
}

// Recursive function to free all nodes in the tree
void freeTree(TreeNode *root)
{
	if (root != NULL)
	{
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}

// Function to print the tree structure (for visualization)
void printTree(TreeNode *root, int space)
{
	const int COUNT = 10;
	if (root == NULL)
	{
		return;
	}

	space += COUNT;
	printTree(root->right, space);

	printf("\n");
	for (int i = COUNT; i < space; i++)
	{
		printf(" ");
	}
	printf("%d\n", root->data);

	printTree(root->left, space);
}

// Main function to demonstrate the binary tree
int mai6n()
{
	TreeNode *root = NULL;

	printf("=== Recursive Binary Search Tree Demo ===\n\n");

	// Insert nodes
	printf("Inserting nodes: 50, 30, 70, 20, 40, 60, 80\n");
	root = insert(root, 50);
	root = insert(root, 30);
	root = insert(root, 70);
	root = insert(root, 20);
	root = insert(root, 40);
	root = insert(root, 60);
	root = insert(root, 80);

	// Display tree structure
	printf("\nTree structure:\n");
	printTree(root, 0);

	// Tree traversals
	printf("\nInorder traversal (sorted): ");
	inorderTraversal(root);
	printf("\n");

	printf("Preorder traversal: ");
	preorderTraversal(root);
	printf("\n");

	printf("Postorder traversal: ");
	postorderTraversal(root);
	printf("\n");

	// Tree statistics
	printf("\nTree height: %d\n", height(root));
	printf("Total nodes: %d\n", countNodes(root));

	// Search operations
	printf("\nSearching for 40: ");
	TreeNode *found = search(root, 40);
	if (found)
	{
		printf("Found!\n");
	}
	else
	{
		printf("Not found!\n");
	}

	printf("Searching for 100: ");
	found = search(root, 100);
	if (found)
	{
		printf("Found!\n");
	}
	else
	{
		printf("Not found!\n");
	}

	// Delete a node
	printf("\nDeleting node 30...\n");
	root = deleteNode(root, 30);
	printf("Inorder traversal after deletion: ");
	inorderTraversal(root);
	printf("\n");

	// Clean up memory
	freeTree(root);

	return 0;
}
