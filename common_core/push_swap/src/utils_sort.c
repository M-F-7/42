/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 05:16:30 by mfernand          #+#    #+#             */
/*   Updated: 2025/11/27 05:17:13 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	set_up_index(t_stack_node **a)
{
	t_stack_node	*current_node;
	t_stack_node	*other_node;

	current_node = *a;
	while (current_node)
	{
		current_node->index = 1;
		other_node = *a;
		while (other_node)
		{
			if (current_node->value > other_node->value)
				current_node->index++;
			other_node = other_node->next;
		}
		current_node = current_node->next;
	}
}

int	find_pos_by_index(t_stack_node **b)
{
	int				final_pos;
	int				curr_pos;
	t_stack_node	*node;
	int				max_index;

	if (b == NULL || *b == NULL)
		return (-1);
	final_pos = 0;
	node = *b;
	curr_pos = 0;
	max_index = node->index;
	while (node)
	{
		if (node->index > max_index)
		{
			max_index = node->index;
			final_pos = curr_pos;
		}
		curr_pos++;
		node = node->next;
	}
	return (final_pos);
}

int	get_range(int size)
{
	int	res;

	res = 0;
	if (size > 10 && size <= 50)
		res = 5;
	else if (size > 50 && size <= 100)
		res = 11;
	else if (size > 100 && size <= 250)
		res = 25;
	else
		res = 30;
	return (res);
}
