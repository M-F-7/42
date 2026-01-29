/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:22:12 by mfernand          #+#    #+#             */
/*   Updated: 2025/11/27 08:23:52 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include "libft/printf/ft_printf.h"
# include <limits.h>
# include <stdbool.h>

typedef struct s_stack_node
{
	int					value;
	int					index;
	struct s_stack_node	*next;
	struct s_stack_node	*previous;
}						t_stack_node;

// parsing & clean
int						only_digit(char *str);
int						error_duplicate(t_stack_node *a, int n);
void					free_stack(t_stack_node **stack);
void					free_tab(char **tab);
void					free_errors(t_stack_node **a, char **av, int flag);

void					init_stack_a(t_stack_node **a, char **argv, int flag);

// algo
void					sort_stacks(t_stack_node **a, t_stack_node **b);
void					set_up_index(t_stack_node **a);
void					start_sort(t_stack_node **a, t_stack_node **b);
void					sort_b(t_stack_node **a, t_stack_node **b);
void					move_max_val_to_top(t_stack_node **b, int pos,
							int size);

// utils
int						stack_size(t_stack_node *stack);
t_stack_node			*find_last(t_stack_node *stack);
bool					is_sorted(t_stack_node *stack);
int						find_pos_by_index(t_stack_node **b);
int						get_range(int size);

// print
void					print_index(t_stack_node **a);
void					print_stack(t_stack_node **stack);
void					check_sorted(t_stack_node **stack);

// little sort
void					little_sort(t_stack_node **a, t_stack_node **b,
							int size);
void					sort_three(t_stack_node **a);
void					sort_four(t_stack_node **a, t_stack_node **b, int size);
void					sort_five(t_stack_node **a, t_stack_node **b, int size);

// little sort utils
t_stack_node			*find_min_idx(t_stack_node **stack);
void					move_min(t_stack_node **a, int pos, int size);
int						find_min_by_idx(t_stack_node **a, t_stack_node *target);
t_stack_node			*find_max(t_stack_node *stack);

// instructions

void					sa(t_stack_node **a, bool print);
void					sb(t_stack_node **b, bool print);
void					ss(t_stack_node **a, t_stack_node **b, bool print);
void					ra(t_stack_node **a, bool print);
void					rb(t_stack_node **b, bool print);
void					rr(t_stack_node **a, t_stack_node **b, bool print);
void					rra(t_stack_node **a, bool print);
void					rrb(t_stack_node **b, bool print);
void					rrr(t_stack_node **a, t_stack_node **b, bool print);
void					pa(t_stack_node **a, t_stack_node **b, bool print);
void					pb(t_stack_node **b, t_stack_node **a, bool print);

#endif