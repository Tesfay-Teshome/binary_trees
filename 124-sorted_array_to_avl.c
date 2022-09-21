#include "binary_trees.h"

/**
 * sort_insert - Auxiliary Function for sort insertion
 * @array: pointer to the first element of the array to be converted
 * @min: lower limit
 * @max: upper limit
 *
 * Return: pointer to the root node of the created AVL tree, or NULL on failure
 */
avl_t *sort_insert(int *array, int min, int max)
{
	int half;
	avl_t *tree;

	if (min > max)
		return (NULL);

	half = (max + min) / 2;

	tree = binary_tree_node(NULL, array[half]);
	if (!tree)
		return (NULL);

	tree->left = sort_insert(array, min, half - 1);

	tree->right = sort_insert(array, half + 1, max);

	if (tree->left)
		tree->left->parent = tree;

	if (tree->right)
		tree->right->parent = tree;

	return (tree);
}

/**
 * sorted_array_to_avl - builds an AVL tree from an array
 * @array: pointer to the first element of the array to be converted
 * @size: number of element in the array
 *
 * Return: pointer to the root node of the created AVL tree, or NULL on failure
 */
avl_t *sorted_array_to_avl(int *array, size_t size)
{
	avl_t *root = NULL;

	if (!array || size < 1)
		return (NULL);

	root = sort_insert(array, 0, size - 1);

	return (root);
}
