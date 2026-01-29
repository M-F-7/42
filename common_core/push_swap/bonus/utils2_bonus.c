/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:34:54 by mfernand          #+#    #+#             */
/*   Updated: 2025/11/27 10:35:58 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

long	ft_atol(const char *s)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while ((*s == 32) || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (ft_isdigit(*s))
		result = result * 10 + (*s++ - '0');
	return (result * sign);
}

int	stack_size(t_stack_node *stack)
{
	int	count;

	if (!stack)
		return (0);
	count = 0;
	while (stack)
	{
		stack = stack->next;
		count++;
	}
	return (count);
}

t_stack_node	*find_last(t_stack_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

bool	is_instructions(char *str)
{
	if (!ft_strncmp(str, "sa\n", ft_strlen(str)))
		return (true);
	else if (!ft_strncmp(str, "sb\n", ft_strlen(str)))
		return (true);
	else if (!ft_strncmp(str, "ss\n", ft_strlen(str)))
		return (true);
	else if (!ft_strncmp(str, "pb\n", ft_strlen(str)))
		return (true);
	else if (!ft_strncmp(str, "pa\n", ft_strlen(str)))
		return (true);
	else if (!ft_strncmp(str, "ra\n", ft_strlen(str)))
		return (true);
	else if (!ft_strncmp(str, "rb\n", ft_strlen(str)))
		return (true);
	else if (!ft_strncmp(str, "rr\n", ft_strlen(str)))
		return (true);
	else if (!ft_strncmp(str, "rra\n", ft_strlen(str)))
		return (true);
	else if (!ft_strncmp(str, "rrb\n", ft_strlen(str)))
		return (true);
	else if (!ft_strncmp(str, "rrr\n", ft_strlen(str)))
		return (true);
	else
		return (false);
}

void	exec_instructions(char *str, t_stack_node **a, t_stack_node **b)
{
	if (!ft_strncmp(str, "sa\n", ft_strlen(str)))
		sa(a, true);
	else if (!ft_strncmp(str, "sb\n", ft_strlen(str)))
		sb(a, true);
	else if (!ft_strncmp(str, "ss\n", ft_strlen(str)))
		ss(a, b, true);
	else if (!ft_strncmp(str, "pb\n", ft_strlen(str)))
		pb(b, a, true);
	else if (!ft_strncmp(str, "pa\n", ft_strlen(str)))
		pa(a, b, true);
	else if (!ft_strncmp(str, "ra\n", ft_strlen(str)))
		ra(a, true);
	else if (!ft_strncmp(str, "rb\n", ft_strlen(str)))
		rb(b, true);
	else if (!ft_strncmp(str, "rr\n", ft_strlen(str)))
		rr(a, b, true);
	else if (!ft_strncmp(str, "rra\n", ft_strlen(str)))
		rra(a, true);
	else if (!ft_strncmp(str, "rrb\n", ft_strlen(str)))
		rrb(b, true);
	else if (!ft_strncmp(str, "rrr\n", ft_strlen(str)))
		rrr(a, b, true);
}
