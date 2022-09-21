#include "binary_trees.h"


/**
 * minValue - Return Leftmost node (minimum value for BST)
 * @node: node to start from
 *
 * Return: Leftmost Node
 */
avl_t *minValue(avl_t *node)
{
	avl_t *current;

	current = node;

	while (current->left)
		current = current->left;

	return (current);
}

/**
 * avl_rotation_D - applies rotation for removal
 * @tree: double pointer to the root node of the AVL tree for
 * removing the value
 *
 * Return: No return
 */
void avl_rotation_D(avl_t **tree)
{
	int balance, bl = 0, br = 0, check = 1;

	balance = binary_tree_balance(*tree);

	if ((*tree)->left)
		bl = binary_tree_balance((*tree)->left);
	if ((*tree)->right)
		br = binary_tree_balance((*tree)->left);

	if (balance > 1 && bl >= 0 && check)
		*tree = binary_tree_rotate_right(*tree), check = 0;

	if (balance > 1 && bl < 0 && check)
	{
		(*tree)->left = binary_tree_rotate_left((*tree)->left);
		*tree = binary_tree_rotate_right(*tree);
		check = 0;
	}

	if (balance < -1 && br <= 0 && check)
		*tree = binary_tree_rotate_left(*tree), check = 0;

	if (balance < -1 && br > 0 && check)
	{
		(*tree)->right = binary_tree_rotate_right((*tree)->right);
		*tree = binary_tree_rotate_left(*tree);
		check = 0;
	}
}

/**
 * avl_remove - removes a node from an AVL tree
 * @root: pointer to the root node of the tree for removing a node
 * @value: value to remove in the tree
 *
 * Return: pointer to the created node, or NULL on failure
 */
avl_t *avl_remove(avl_t *root, int value)
{
	avl_t *tmp = NULL;

	if (!root)
		return (root);

	if (value < root->n)
		root->left = avl_remove(root->left, value);

	else if (value > root->n)
		root->right = avl_remove(root->right, value);

	else
		if (!(root->left) || !(root->right))
		{
			if (root->left)
				tmp = root->left;
			else
				tmp = root->right;

			if (!tmp)
				tmp = root, root = NULL;
			else
			{
				root->parent = tmp->parent->parent;
				root->n = tmp->n;
				root->left = tmp->left;
				root->right = tmp->right;
			}

			free(tmp);
		}
		else
		{
			tmp = minValue(root->right);
			root->n = tmp->n;
			root->right = avl_remove(root->right, tmp->n);
		}
	if (root)
		avl_rotation_D(&root);
	return (root);
}
