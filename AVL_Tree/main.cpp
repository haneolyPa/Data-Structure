#include<stdio.h>
#include<malloc.h>

#define FALSE 0
#define TRUE 1

typedef char BOOL;

struct Node {
	void* key;
	int height;   // 서브트리 높이

	struct Node* left;
	struct Node* right;
};

struct Tree {
	unsigned int count;
	BOOL(*compare)(void* argu1, void* argu2);  // 왼쪽으로 보내야 되면 TRUE

	struct Node* root;
};

struct Tree* CreateTree(BOOL *(compFunc)(void* argu1, void* argu2));
void addNode(struct Tree*, void*);
BOOL _insert(struct Tree*, struct Node**, struct Node*);  // 트리의 높이가 높아졌는지를 BOOL 타입으로 리턴한다. 높이가 높아지면 TRUE를 리턴.
				// 루트는 NULL이 아니라고 가정한다.
BOOL Compare(void*, void*);
void Traverse(struct Node*);
struct Node* leftBalance(struct Node*);
struct Node* rightBalance(struct Node*);
struct Node* rottLeft(struct Node*);
struct Node* rottRight(struct Node*);
int GetHeightDiff(struct Node*);

struct Tree* CreateTree(BOOL(compFunc)(void*, void*))
{
	struct Tree* newTree;

	newTree = (struct Tree*)malloc(sizeof(struct Tree));
	newTree->count = 0;
	newTree->root = NULL;
	newTree->compare = compFunc;

	return newTree;
}

void AddNode(struct Tree* tree, void* data)
{
	struct Node* node;

	node = (struct Node*)malloc(sizeof(struct Node));
	node->height = 1;
	node->key = data;
	node->left = NULL;
	node->right = NULL;

	if (tree->count == 0) {
		tree->root = node;
		tree->count++;
	}
	else
		_insert(tree, &(tree->root), node);
}

BOOL _insert(struct Tree* tree, struct Node** root, struct Node* node)
{
	if (tree->compare((*root)->key, node->key)) {
		if ((*root)->left == NULL) {
			(*root)->left = node;
			tree->count++;
			if ((*root)->right == NULL) {
				(*root)->height++;

				return TRUE;
			}
			else {
				return FALSE;
			}
		}
		else {
			if (_insert(tree, &((*root)->left), node)) {
				(*root)->height++;
				if (GetHeightDiff((*root)) > 0)     // 왼쪽이 더 높으면
					(*root) = leftBalance((*root));    // 밸런싱
				return TRUE;
			}
			else {
				return FALSE;
			}
		}
	}
	else {
		if ((*root)->right == NULL) {
			(*root)->right = node;
			tree->count++;
			if ((*root)->left == NULL) {
				(*root)->height++;

				return TRUE;
			}
			else {
				return FALSE;
			}
		}
		else {
			if (_insert(tree, &((*root)->right), node)) {
				(*root)->height++;
				if (GetHeightDiff((*root)) < 0)
					(*root) = rightBalance((*root));
				return TRUE;
			}
			else {
				return FALSE;
			}
		}
	}
}

int GetHeightDiff(struct Node* root)
{
	int left = 0;
	int right = 0;

	if (root->left != NULL)
		left = root->left->height;

	if (root->right != NULL)
		right = root->right->height;

	return left - right;
}

struct Node* leftBalance(struct Node* root)
{

	if (GetHeightDiff(root->left) > 0)
		root = rottRight(root);
	else {
		root->left = rottLeft(root->left);
		root = rottRight(root);
	}

	return root;
}

struct Node* rightBalance(struct Node* root)
{

	if (GetHeightDiff(root->right) < 0)
		root = rottLeft(root);
	else {
		root->right = rottRight(root->right);
		root = rottLeft(root);
	}

	return root;
}

int getHeight(struct Node* node)
{
	if (node == NULL)
		return 0;
	else
		return node->height;
}

struct Node* rottRight(struct Node* root)
{
	struct Node* tmp;

	tmp = root->left;
	root->left = tmp->right;
	tmp->right = root;

	if (getHeight(root->left) > getHeight(root->right)) {
		root->height = getHeight(root->left) + 1;
	}
	else {
		root->height = getHeight(root->right) + 1;
	}

	if (getHeight(tmp->left) > getHeight(tmp->right)) {
		tmp->height = getHeight(tmp->left) + 1;
	}
	else {
		tmp->height = getHeight(tmp->right) + 1;
	}

	return tmp;
}

struct Node* rottLeft(struct Node* root)
{
	struct Node* tmp;

	tmp = root->right;
	root->right = tmp->left;
	tmp->left = root;

	if (getHeight(root->left) > getHeight(root->right)) {
		root->height = getHeight(root->left) + 1;
	}
	else {
		root->height = getHeight(root->right) + 1;
	}

	if (getHeight(tmp->left) > getHeight(tmp->right)) {
		tmp->height = getHeight(tmp->left) + 1;
	}
	else {
		tmp->height = getHeight(tmp->right) + 1;
	}

	return tmp;
}

BOOL Compare(void* argu1, void* argu2)
{
	if ((*(int*)(argu1)) > (*(int*)(argu2)))
		return TRUE;
	else
		return FALSE;
}

void Traverse(struct Node* root)
{
	if (root == NULL)
		return;

	printf("%d(%d)\n", *(int*)(root->key), GetHeightDiff(root));
	Traverse(root->left);
	Traverse(root->right);
}

int main()
{
	struct Tree* tree;
	int* key;

	tree = CreateTree(Compare);

	key = (int*)malloc(sizeof(int));
	*key = 3;
	AddNode(tree, (void*)key);

	Traverse(tree->root);
	printf("\n");

	key = (int*)malloc(sizeof(int));
	*key = 4;
	AddNode(tree, (void*)key);

	Traverse(tree->root);
	printf("\n");

	key = (int*)malloc(sizeof(int));
	*key = 5;
	AddNode(tree, (void*)key);

	Traverse(tree->root);
	printf("\n");

	key = (int*)malloc(sizeof(int));
	*key = 2;
	AddNode(tree, (void*)key);

	Traverse(tree->root);
	printf("\n");

	key = (int*)malloc(sizeof(int));
	*key = 7;
	AddNode(tree, (void*)key);

	Traverse(tree->root);
	printf("\n");

	key = (int*)malloc(sizeof(int));
	*key = 9;
	AddNode(tree, (void*)key);

	Traverse(tree->root);
	printf("\n");

	key = (int*)malloc(sizeof(int));
	*key = 11;
	AddNode(tree, (void*)key);

	Traverse(tree->root);
	printf("\n");
	return 1;
}