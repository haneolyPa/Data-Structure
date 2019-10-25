#include <stdio.h>
#include <stdlib.h>

// 노드의 키 자료형
typedef int NODE_DATA_TYPE;

// 노드 색
typedef enum _node_color {
	RED,
	BLACK
} N_Color;

// 노드 자료 구조
typedef struct _node {
	_node * parent;				// 부모 노드
	_node * left;				// 왼쪽 자식 노드
	_node * right;				// 오른쪽 자식 노드
	N_Color color;				// 노드 색
	
	NODE_DATA_TYPE key;			// 키 값
} TREE_NODE;

// 노드 포인터 
typedef TREE_NODE * TREE_NODE_PTR;

// 트리 자료 구조
typedef struct _Tree {		
	TREE_NODE_PTR root;
} BIN_TREE;
typedef BIN_TREE * BIN_TREE_PTR;

// 부모 노드를 구하는 함수
TREE_NODE_PTR getParent(TREE_NODE_PTR node)
{
	return node == NULL ? NULL : node->parent;
}

// 조부모 노드를 구하는 함수
TREE_NODE_PTR getGrandParent(TREE_NODE_PTR node)
{
	return getParent(getParent(node));
}

// 형제 노드를 구하는 함수
TREE_NODE_PTR getSibling(TREE_NODE_PTR node)
{
	TREE_NODE_PTR parent = getParent(node);

	if (parent == NULL)
		return NULL;

	return node == parent->left ? parent->right : parent->left;
}

// 부모의 형제 노드(삼촌?)를 구하는 함수
TREE_NODE_PTR getParentSibling(TREE_NODE_PTR node)
{
	return getSibling(getParent(node));
}

// 이진트리 노드 생성
TREE_NODE_PTR createBNode(NODE_DATA_TYPE key, TREE_NODE_PTR left, TREE_NODE_PTR right)
{
	TREE_NODE_PTR newNode = (TREE_NODE_PTR)malloc(sizeof(TREE_NODE));

	newNode->key = key;
	newNode->left = left;
	newNode->right = right;

	newNode->color = RED;
	newNode->parent = NULL;

	return newNode;
}

#define NewNode(Key) createBNode((Key), NULL, NULL)

// 트리 생성
BIN_TREE_PTR createBTree()
{
	BIN_TREE_PTR newTree = (BIN_TREE_PTR)malloc(sizeof(BIN_TREE));
	newTree->root = NULL;
	return newTree;
}

// LL 회전 (오른쪽으로 회전한다)
//     A
//    /                B
//   B        ->      / \
//  /                C   A
// C
//
// ±2를 가지는 A가 부모가 되고 A->left인 B가 child가 된다.
// A->left에 B가 가지고 있는 right를 대입하고 B의 right에 A을 대입한다.
TREE_NODE_PTR rotate_LL(TREE_NODE_PTR parent)
{
	TREE_NODE_PTR child = NULL;

	if (parent == NULL)
		return NULL;

	child = parent->left;
	if (child == NULL)
		return NULL;

	parent->left = child->right;
	child->right = parent;

	child->parent = parent->parent;
	parent->parent = child;

	if (parent->left != NULL)
		parent->left->parent = parent;

	return child;
}

// RR 회전 (왼쪽으로 회전한다)
//     A
//      \               B
//       B     ->      / \
//        \           A   C
//         C
//
// ±2를 가지는 A가 부모가 되고 A->right인 B가 child가 된다.
// A->right에 B가 가지고 있는 left를 대입하고 B의 left에 A을 대입한다.
TREE_NODE_PTR rotate_RR(TREE_NODE_PTR parent)
{
	TREE_NODE_PTR child = NULL;

	if (parent == NULL)
		return NULL;

	child = parent->right;
	if (child == NULL)
		return NULL;

	parent->right = child->left;
	child->left = parent;

	child->parent = parent->parent;
	parent->parent = child;

	if (parent->right != NULL)
	parent->right->parent = parent;

	return child;
}

// RL 회전 (오른쪽-왼쪽으로 회전한다)
//     A                A              
//      \                \                C
//       B      ->        C      ->      / \
//      /                  \            A   B
//     C                    B
//
// ±2를 가지는 A가 부모가 되고 A->right인 B가 child가 된다.
// A->right에 rotate_LL(B)가 반환하는 값을 대입한다. (B,C에 대해 오른쪽 회전)
// rotate_LL(B)호출시 B와 C가 변화가 생기고 다시 rotate_RR(A)을 호출하면 균형트리가 된다. 
TREE_NODE_PTR rotate_RL(TREE_NODE_PTR parent)
{
	TREE_NODE_PTR child = NULL;
	if (parent == NULL)
		return NULL;

	child = parent->right;
	if (child == NULL)
		return NULL;

	parent->right = rotate_LL(child);
	return rotate_RR(parent);
}

// LR 회전 (왼쪽-오른쪽으로 회전한다)
//     A                 A              
//	  /                 /                  C
//   B         ->      C          ->      / \
//    \               /                  A   B
//     C             B      
//
// ±2를 가지는 A가 부모가 되고 A->left인 B가 child가 된다.
// A->left에 rotate_RR(B)가 반환하는 값을 대입한다. (B,C에 대해 왼쪽 회전)
// rotate_RR(B)호출시 B와 C가 변화가 생기고 다시 rotate_LL(A)을 호출하면 균형트리가 된다. 
TREE_NODE_PTR rotate_LR(TREE_NODE_PTR parent)
{
	TREE_NODE_PTR child = NULL;
	if (parent == NULL)
		return NULL;

	child = parent->left;
	if (child == NULL)
		return NULL;

	parent->left = rotate_RR(child);
	return rotate_LL(parent);
}

// 균형 트리를 만드는 함수
TREE_NODE_PTR balance_tree(TREE_NODE_PTR node)
{
	TREE_NODE_PTR parent = getParent(node);

	if (parent == NULL)	// 루트 노드인 경우
	{
		if (node != NULL)
			node->color = BLACK;
	}
	else if(parent->color == BLACK)
	{
		node = parent;
	}
	else		// 부모 노드가  레드(RED)인 경우
	{
		// 부모의 형제 노드가 레드(RED)인 경우
		if (getParentSibling(node) != NULL && getParentSibling(node)->color == RED)
		{
			parent->color = BLACK;
			getParentSibling(node)->color = BLACK;
			getGrandParent(node)->color = RED;
			node = balance_tree(getGrandParent(node));
		}
		else // 부모의 형제 노드가 없거나 블랙(BLACK)인 경우
		{
			TREE_NODE_PTR tempNode = NULL;

			if (node == parent->right && getGrandParent(node) != NULL && parent == getGrandParent(node)->left) {
				node = rotate_LR(parent);
				tempNode = node->left;
			}
			else if (node == parent->left && parent == getGrandParent(node)->right) {
				node = rotate_RL(parent);
				tempNode = node->right;
			}
			else
				tempNode = node;

			if (tempNode != NULL)
			{
				TREE_NODE_PTR temp_Parent = getParent(tempNode);
				TREE_NODE_PTR temp_GrandParent = getGrandParent(tempNode);

				if (tempNode == temp_Parent->left) {
					node = rotate_LL(temp_GrandParent);
				}
				else {
					node = rotate_RR(temp_GrandParent);
				}

				temp_Parent->color = BLACK;
				temp_GrandParent->color = RED;
				node = balance_tree(node);
			}
		}
	}

	return node;
}

// 트리의 삽입 연산
// key에 대해 순환호출을 반복하므로써 트리에 삽입 한 후 균형화 함수를 호출한다.
TREE_NODE_PTR RBTree_Insert(TREE_NODE_PTR* root, TREE_NODE_PTR node)
{
	if (root == NULL || node == NULL)
		return NULL;

	if ((*root) == NULL)	// 루트에 추가하는 경우				
	{
		(*root) = node;
		node->color = BLACK;
	} 
	else if (node->key < (*root)->key)	// 왼쪽에 추가하는 경우
	{
		if ((*root)->left == NULL)	// 왼쪽이 비어 있으면
		{
			(*root)->left = node;
			node->parent = (*root);
		}
		else
		{
			RBTree_Insert(&(*root)->left, node);
		}
	}
	else if (node->key > (*root)->key)	// 오른쪽에 추가하는 경우
	{
		if ((*root)->right == NULL)	// 오른쪽이 비어 있으면
		{
			(*root)->right = node;
			node->parent = (*root);
		}
		else
		{
			RBTree_Insert(&(*root)->right, node);
		}
	}

	return (node);
}

TREE_NODE_PTR RBTree_add(TREE_NODE_PTR* root, NODE_DATA_TYPE key)
{
	TREE_NODE_PTR node = NewNode(key);
	RBTree_Insert(root, node);

	(*root) = balance_tree(node);

	return (*root);
}

int main()
{
	BIN_TREE_PTR pBTree = createBTree();

	RBTree_add(&pBTree->root, 1);
	RBTree_add(&pBTree->root, 2);
	RBTree_add(&pBTree->root, 3);
	RBTree_add(&pBTree->root, 4);
	RBTree_add(&pBTree->root, 5);
	RBTree_add(&pBTree->root, 6);
	RBTree_add(&pBTree->root, 7);
	RBTree_add(&pBTree->root, 8);
	RBTree_add(&pBTree->root, 9);
	RBTree_add(&pBTree->root, 10);
	RBTree_add(&pBTree->root, 11);


	return 0;
}