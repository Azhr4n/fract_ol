/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 14:49:33 by pivanovi          #+#    #+#             */
/*   Updated: 2016/09/21 14:49:33 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

#include "fract_ol.h"

t_node	*create_new_node(float x, float y)
{
	t_node	*ptr;

	if ((ptr = (t_node *)malloc(sizeof(t_node))) == NULL)
	{
		ft_putendl("Failed to create node.");
		exit(1);
	}
	ptr->next = NULL;
	ptr->pos.x = x;
	ptr->pos.y = y;
	return (ptr);
}

t_node	*insert_node_at_end(t_node *node, t_node *new)
{
	t_node	*ptr;

	if (node == NULL)
		return (new);
	else
	{
		ptr = node;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (node);
}

void	clear_list(t_node **node)
{
	t_node	*next;

	while (*node != NULL)
	{
		next = (*node)->next;
		free(*node);
		*node = NULL;
		*node = next;
	}
}
