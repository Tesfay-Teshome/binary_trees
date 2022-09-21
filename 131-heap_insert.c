#include "binary_trees.h"
/**
 * _height - measures the sum of heights of a binary tree
 * @tree: pointer to the root node of the tree to measure the height
 *
 * Return: Height or 0 if tree is NULL
 */
int _height(const binary_tree_t *tree)
{
	size_t height_l = 0;
	size_t height_r = 0;

	if (!tree)
		return (-1);

	height_l = _height(tree->left);
	height_r = _height(tree->right);

	if (height_l > height_r)
		return (height_l + 1);
	return (height_r + 1);
}
/**
 * greater_than_parent - check if child is greather than parent to check
 * @father: Node parent of the inserting node
 * @son: Node inserted to check with the parent
 * Return: Not return, only order the tree in a heap
 */
void greater_than_parent(heap_t **father, heap_t **son)
{
	heap_t *f, *child, *n_child, *n_left, *n_right, *parent;
	int gtp;

	f = *father, child = *son;
	if (child->n > f->n)
	{
		if (child->left)
			child->left->parent = f;
		if (child->right)
			child->right->parent = f;
		if (f->left == child)
			n_child = f->right, gtp = 0;
		else
			n_child = f->left, gtp = 1;
		n_left = child->left, n_right = child->right;
		if (gtp == 0)
		{
			child->right = n_child;
			if (n_child)
				n_child->parent = child;
			child->left = f;
		}
		else
		{
			child->left = n_child;
			if (n_child)
				n_child->parent = child;
			child->right = f;
		}
		if (f->parent)
		{
			if (f->parent->left == f)
				f->parent->left = child;
			else
				f->parent->right = child;
		}
		parent = f->parent, child->parent = parent;
		f->parent = child, f->left = n_left;
		f->right = n_right, *father = child;
	}
}
/**
 * is_perfect - check if the subtrees has the same height
 * and check for each subtree be perfect
 * @root: Tree or subtree to check
 * Return: 1 if subtree or tree is perfect or not
 */
int is_perfect(const binary_tree_t *root)
{
	if (root && _height(root->left) == _height(root->right))
	{
		if (_height(root->left) == -1)
			return (1);
		if ((root->left && !((root->left)->left)
		     && !((root->left)->right))
		    && (root->right && !((root->right)->left)
			&& !((root->right)->right)))
			return (1);
		if (root && root->left && root->right)
			return (is_perfect(root->left)
				&& is_perfect(root->right));
	}
	return (0);
}
/**
 * heap_insert - function that inserts a value in Max Binary Heap
 * @root: double pointer to the root f of the Heap to insert the value
 * @value: is the value to store in the f to be inserted
 * Return: NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *new;

	if (*root == NULL)
	{
		*root = binary_tree_node(NULL, value);
		return (*root);
	}
	if (is_perfect(*root) || !is_perfect((*root)->left))
	{
		if ((*root)->left)
		{
			new = heap_insert(&((*root)->left), value);
			greater_than_parent(root, &((*root)->left));
			return (new);
		}
		else
		{
			new = (*root)->left = binary_tree_node(*root, value);
			greater_than_parent(root, &((*root)->left));
			return (new);
		}
	}
	if ((*root)->right)
	{
		new = heap_insert(&((*root)->right), value);
		greater_than_parent(root, (&(*root)->right));
		return (new);
	}
	else
	{
		new = (*root)->right = binary_tree_node(*root, value);
		greater_than_parent(root, &((*root)->right));
		return (new);
	}
	return (NULL);
}
