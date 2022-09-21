#include "binary_trees.h"
#include <stdio.h>
/**
 * array_to_heap - builds a Max Binary Heap tree from an array
 * @array: Array with numbers to create in to Max Binary heap
 * @size: Size of array
 * Return: root of binary tree
 */
heap_t *array_to_heap(int *array, size_t size)
{
	heap_t *tree = NULL;
	size_t i = 0;

	if (!array || size < 1)
		return (NULL);

	heap_insert(&tree, array[0]);

	for (i = 1; i < size; i++)
		heap_insert(&tree, array[i]);

	return (tree);

}
