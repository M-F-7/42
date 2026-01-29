/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_sort_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 06:13:20 by mfernand          #+#    #+#             */
/*   Updated: 2025/11/27 07:00:33 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_stack_node	*find_min_idx(t_stack_node **stack)
{
	t_stack_node	*res;
	t_stack_node	*node;

	node = *stack;
	res = node;
	while (node)
	{
		if (node->value < res->value)
			res = node;
		node = node->next;
	}
	return (res);
}

t_stack_node	*find_max(t_stack_node *stack)
{
	long			max;
	t_stack_node	*max_node;

	if (!stack)
		return (NULL);
	max = LONG_MIN;
	while (stack)
	{
		if (stack->value > max)
		{
			max = stack->value;
			max_node = stack;
		}
		stack = stack->next;
	}
	return (max_node);
}

void	move_min(t_stack_node **a, int pos, int size)
{
	int	median;

	median = size / 2 + 1;
	if (pos < median)
	{
		while (pos > 0)
		{
			ra(a, false);
			pos--;
		}
	}
	else
	{
		while (pos < size)
		{
			rra(a, false);
			pos++;
		}
	}
}

int	find_min_by_idx(t_stack_node **a, t_stack_node *target)
{
	t_stack_node	*node;
	int				pos;

	node = *a;
	pos = 0;
	while (node != target)
	{
		pos++;
		node = node->next;
	}
	return (pos);
}
