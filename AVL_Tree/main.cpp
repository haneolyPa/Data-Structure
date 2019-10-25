#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define max(a,b)    (((a) > (b)) ? (a) : (b))

typedef int NODE_DATA_TYPE;

typedef struct _node {		// 트리의 노드
	_node * left;
	_node * right;
	NODE_DATA_TYPE info;
} TREE_NODE;
typedef TREE_NODE * TREE_NODE_PTR;

typedef struct _Tree {			// 트리 자료 구조
	TREE_NODE_PTR root;
} BIN_TREE;
typedef BIN_TREE * BIN_TREE_PTR;

// 이진트리 노드 생성
TREE_NODE_PTR createBNode(NODE_DATA_TYPE data, TREE_NODE_PTR left, TREE_NODE_PTR right)
{
	TREE_NODE_PTR newBNode = (TREE_NODE_PTR)malloc(sizeof(TREE_NODE));

	newBNode->info = data;
	newBNode->left = left;
	newBNode->right = right;

	return newBNode;
}

// 이진트리 노드 제거
void deleteBNode(TREE_NODE_PTR node)
{
	if (node == NULL)
		return;

	deleteBNode(node->left);
	deleteBNode(node->right);
	free(node);
}

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
	TREE_NODE_PTR child = parent->left;
	parent->left = child->right;
	child->right = parent;
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
	TREE_NODE_PTR child = parent->right;
	parent->right = child->left;
	child->left = parent;
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
	TREE_NODE_PTR child = parent->right;
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
	TREE_NODE_PTR child = parent->left;
	parent->left = rotate_RR(child);
	return rotate_LL(parent);
}

// 트리의 높이 측정 함수
// 순환호출로 각각의 높이를 구하고 이들 중에서 더 큰값에 1을 더하면 트리의 높이가 된다.
int get_height(TREE_NODE_PTR node)
{
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}

// 노드의 균형인수 반환 함수
// 왼쪽 서브트리 높이 - 오른쪽 서브트리 높이
int get_balance(TREE_NODE_PTR node)
{
	if (node == NULL) return 0;
	return get_height(node->left) - get_height(node->right);
}

// 균형 트리를 만드는 함수
TREE_NODE_PTR balance_tree(TREE_NODE_PTR node)
{
	int height_diff = get_balance(node);

	if (height_diff > 1) // 왼쪽 서브트리의 균형을 맞춘다
	{
		if (get_balance(node->left) > 0)
			node = rotate_LL(node);
		else
			node = rotate_LR(node);
	}
	else if (height_diff < -1) // 오른쪽 서브트리의 균형을 맞춘다
	{
		if (get_balance(node->right) < 0)
			node = rotate_RR(node);
		else
			node = rotate_RL(node);
	}
	return node;
}

// AVL 트리의 삽입 연산
// key에 대해 순환호출을 반복하므로써 트리에 삽입 한 후 균형화 함수를 호출한다.
TREE_NODE_PTR avl_add(TREE_NODE_PTR* node, int key)
{
	if (node == NULL)
		return NULL;

	if ((*node) == NULL)
	{
		(*node) = createBNode(key, NULL, NULL);
		return *node;
	}

	if (key < (*node)->info)
		(*node)->left = avl_add(&(*node)->left, key);
	else if (key > (*node)->info)
		(*node)->right = avl_add(&(*node)->right, key);
	
	(*node) = balance_tree((*node));
	return (*node);
}

// AVL 트리 탐색 함수
// 일반 적인 이진 트리의 탐색 함수와 같다. AVL도 이진 탐색 트리의 일종이다.
TREE_NODE_PTR avl_search(TREE_NODE_PTR node, int key)
{
	if (node == NULL) return NULL;

	printf("%d->", node->info);

	if (key == node->info)
		return node;
	else if (key < node->info)
		return avl_search(node->left, key);
	else
		avl_search(node->right, key);

	return node;
}

// 레벨 순회
void levelorder(TREE_NODE_PTR node)
{
	QUEUE_PTR queue = Create_q(5 * 2);
	TREE_NODE_PTR temp_Node;
	if (node == NULL)
		return;

	Add_q(queue, node);
	while (!IsEmpty_q(queue))
	{
		temp_Node = (TREE_NODE_PTR)Delete_q(queue);

		if (temp_Node) {
			printf("%d ", temp_Node->info);
			Add_q(queue, temp_Node->left);
			Add_q(queue, temp_Node->right);
		}
		else {
			printf("NULL ");
		}
	}

	printf("\n");

	delete_q(queue);
}

int main()
{
	BIN_TREE_PTR pBTree = createBTree();
	//TREE_NODE_PTR node;

	avl_add(&pBTree->root, 1);
	avl_add(&pBTree->root, 2);
	avl_add(&pBTree->root, 3);
	avl_add(&pBTree->root, 4);
	avl_add(&pBTree->root, 5);
	avl_add(&pBTree->root, 6);
	avl_add(&pBTree->root, 7);
	avl_add(&pBTree->root, 8);
	avl_add(&pBTree->root, 9);
	avl_add(&pBTree->root, 10);
	avl_add(&pBTree->root, 11);
	avl_add(&pBTree->root, 12);

	//node = avl_search(pBTree->root, 12);

	levelorder(pBTree->root);

	return 0;
}
