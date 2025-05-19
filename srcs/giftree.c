/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   giftree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:24:23 by edgribei          #+#    #+#             */
/*   Updated: 2025/05/14 15:45:30 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gif_parse.h>
#include <stdlib.h>

static t_giftree	*new_treenode(int content)
{
	t_giftree *const	tree = calloc(sizeof(t_giftree), 1);

	if (!tree)
		return (NULL);
	tree->content = content;
	return (tree);
};

t_ctable *start_ctable(size_t ctsize)
{
	
}



void	free_tree(t_giftree *const tree)
{
	int	i;

	i = 0;
	while (tree->branches[i])
	{
		free_tree(tree->branches[i]);
		i++;
	}
	free(tree);
}

//head of the tree keeps the max instruction
t_giftree	*start_tree(int ct_size)
{
	t_giftree *const	tree = new_treenode(ct_size + 2);
	int					i;

	if (!tree)
		return (NULL);
	i = 0;
	while (i < ct_size)
	{
		tree->branches[i] = new_treenode(i);
		if (!tree->branches[i])
			free_tree(tree);
		i++;
	}
	return (tree);
}
