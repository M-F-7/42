/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 03:18:35 by mfernand          #+#    #+#             */
/*   Updated: 2025/11/27 06:27:45 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sort_stacks(t_stack_node **a, t_stack_node **b)
{
	set_up_index(a);
	start_sort(a, b);
}

void	start_sort(t_stack_node **a, t_stack_node **b)
{
	int				range;
	int				size_a;
	int				start;
	t_stack_node	*node;

	size_a = stack_size(*a);
	range = get_range(size_a);
	start = 0;
	while (size_a != 0)
	{
		node = *a;
		if (node->index <= range + start)
		{
			pb(b, a, false);
			if (node->index <= start)
				rb(b, false);
			start++;
			size_a--;
		}
		else
			ra(a, false);
	}
	sort_b(a, b);
}

void	sort_b(t_stack_node **a, t_stack_node **b)
{
	int	position_vmax;
	int	size_b;

	position_vmax = find_pos_by_index(b);
	size_b = stack_size(*b);
	while (size_b != 0)
	{
		move_max_val_to_top(b, position_vmax, size_b);
		pa(a, b, false);
		size_b--;
		position_vmax = find_pos_by_index(b);
	}
}

void	move_max_val_to_top(t_stack_node **b, int pos, int size)
{
	int	median;

	median = size / 2 + 1;
	if (pos < median)
	{
		while (pos > 0)
		{
			rb(b, false);
			pos--;
		}
	}
	else
	{
		while (pos < size)
		{
			rrb(b, false);
			pos++;
		}
	}
}
