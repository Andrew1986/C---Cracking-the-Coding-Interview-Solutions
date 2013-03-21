#include <iostream>

struct Node {
	int data;
	struct Node *left, *right;
};

struct LinkedListNode {
	int data;
	struct LinkedListNode *next;
};

LinkedListNode *createLinkedListNode(int data) {
	LinkedListNode *node = new LinkedListNode;
	node->data = data;
	node->next = 0;
	return node;
}

Node *createNode(int data) {
	Node *node = new Node;
	node->data = data;
	node->left = 0;
	node->right = 0;
	return node;
}

/*
	Chapter 4 - Problem 1
*/
int height(Node *tree, int accum = 0) {
	if (!tree) {
		return accum;
	}
	int left = height(tree->left, accum + 1);
	int right = height(tree->right, accum + 1);
	return left > right ? left : right;
}

bool isBalanced(Node *tree) {
	if (!tree) {
		return false;
	}
	int left = height(tree->left);
	int right = height(tree->right);
	int diff = left - right;
	return (diff >= -1) && (diff <= 1);
}

/*
	Chapter 4 - Problem 3
*/
int length(int *data) {
	int i = 0;
	while (*data) {
		i++;
		data++;
	}
	return i;
}

Node *_createMinBST(int data[], int start, int end) {
	if (end - start <= 0) {
		return 0;
	}
	int middle = (start + end) / 2;
	Node *tree = createNode(data[middle]);
	tree->left = _createMinBST(data, start, middle);
	tree->right = _createMinBST(data, middle + 1, end);
	return tree;
}

Node *createMinBST(int *data) {
	if (!*data) {
		return 0;
	}
	return _createMinBST(data, 0, length(data));
}

/*
	Chapter 4 - Problem 4
*/
void _createLevelLists(Node *tree, LinkedListNode **lists, int level) {
	if (!tree) {
		return;
	}
	if (lists[level]) {
		LinkedListNode *node = createLinkedListNode(tree->data);
		node->next = lists[level];
		lists[level] = node;
	} else {
		lists[level] = createLinkedListNode(tree->data);
	}
	_createLevelLists(tree->left, lists, level + 1);
	_createLevelLists(tree->right, lists, level + 1);
}

LinkedListNode **createLevelLists(Node *tree) {
	if (!tree) {
		return 0;
	}
	int depth = height(tree);
	LinkedListNode **lists = new LinkedListNode *[depth + 1];
	_createLevelLists(tree, lists, 0);
	return lists;
}

/*
	Chapter 4 - Problem 5
*/
bool isBST(Node *tree) {
	if (!tree) {
		return true;
	}
	int data = tree->data;
	if (tree->left && tree->left->data >= data) {
		return false;
	}
	if (tree->right && tree->right->data < data) {
		return false;
	}
	return isBST(tree->left) && isBST(tree->right);
}

/*
	Chapter 4 - Problem 6

	Find a common ancestor between two nodes
*/
Node *findAncestor(Node *tree, Node *A, Node *B) {
	if (!tree || !A || !B) {
		return 0;
	}
	if (tree == A || tree == B) {
		return tree;
	}
	int data = tree->data;
	if (A->data >= data && B->data >= data) {
		return findAncestor(tree->right, A, B);
	} else if (A->data < data && B->data < data) {
		return findAncestor(tree->left, A, B);
	}
	return tree;
}


void printTree(Node *tree) {
	if (!tree) {
		return;
	}
	std::cout << tree->data << std::endl;
	printTree(tree->left);
	printTree(tree->right);
}

void printLinkedList(LinkedListNode *list) {
	if (!list) {
		return;
	}
	LinkedListNode *node = list;
	while (node) {
		std::cout << node->data;
		if (node->next) {
			std::cout << " -> ";
		}
		node = node->next;
	}
	std::cout << std::endl;
}

/*
	Debugging/Testing
*/
int main(int argc, char *argv[]) {
	//Testing problem 1
	Node *tree = createNode(4);
	tree->left = createNode(2);
	tree->left->left = createNode(3);
	std::cout << isBalanced(tree) << std::endl;
	tree->right = createNode(1);
	std::cout << isBalanced(tree) << std::endl;
	std::cout << std::endl;
	//Testing problem 3
	int data[10] = {1, 3, 5, 6, 7, 8, 10, 12, 14};
	Node *bst = createMinBST(data);
	printTree(bst);
	std::cout << std::endl;
	//Testing problem 5
	std::cout << isBST(bst) << std::endl;
	std::cout << isBST(tree) << std::endl;
	std::cout << std::endl;
	//Testing problem 4
	LinkedListNode ** lists = createLevelLists(bst);
	int i = 0;
	while (lists[i]) {
		printLinkedList(lists[i]);
		i++;
	}
	//Testing problem 6
	Node *leftN = bst->left->left;
	Node *rightN = bst->left->right;
	Node *ancestor = findAncestor(bst, leftN, rightN);
	if (ancestor) {
		std::cout << ancestor->data << std::endl;
	}
	return 0;
}