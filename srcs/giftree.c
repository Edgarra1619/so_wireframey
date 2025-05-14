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
}

t_giftree	*start_tree(int ct_size)
{
	t_giftree *const	tree = calloc(sizeof(t_giftree), 1);
	int					i;

	if (!tree)
		return (NULL);
	i = 0;
	while (i < ct_size)
	{
		


	}
	(void) i;
	(void) ct_size;
	return (tree);
}
