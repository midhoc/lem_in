/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:24:35 by hmidoun           #+#    #+#             */
/*   Updated: 2020/01/04 03:46:32 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// int		one_d_path(t_graph	*graph, int stack_i, int k)
// {
// 	if (graph->links[k][stack_i])
// 		return (1);
// 	return (0);
// }

int			cond_path_change(t_graph *graph, int k, int i_s_stack)
{
	if ((graph->links[graph->stack_path[i_s_stack]][k] == 1) &&
			((graph->tmp_path[k][0] == -1 && graph->tmp_path[k][1] == -1) ||
			graph->tmp_path[k][1] > graph->tmp_path[graph->stack_path[i_s_stack]][1]))
		return (1);
	return (0);
}

void		bfs(t_graph *graph)
{
	int		i_s_stack;
	int		i_e_stack;
	int		i_link;
	int		tmp;

	i_s_stack = 0;
	i_e_stack = 1;
	while (i_s_stack < i_e_stack)
	{
		i_link = -1;
		tmp = 0;
		while (i_link++ < graph->nbr_n && tmp >= 0 )
		{
			if (cond_path_change(graph, i_link, i_s_stack))
			{
				if (graph->links[i_link][graph->stack_path[i_s_stack]] == graph->nbr_n + 1)
				{
					i_e_stack -= tmp;
					tmp = -2;
					graph->tmp_path[i_link][1] = graph->tmp_path[graph->stack_path[i_s_stack]][1] - 1;
				}
				else
					graph->tmp_path[i_link][1] = graph->tmp_path[graph->stack_path[i_s_stack]][1] + 1;
				graph->stack_path[i_e_stack] = i_link;
				graph->tmp_path[i_link][0] = graph->stack_path[i_s_stack];
				i_e_stack++;
				tmp++;
			}
		}
		i_s_stack++;
	}
}

// int		**bfs(t_graph *graph)
// {
// 	int		**path;
// 	int		i;
// 	int		*stack;

// 	i = -1;
// 	if (!(path = malloc(sizeof(int*) * graph->nbr_n)))
// 		return (NULL);
// 	if (!(stack = malloc(sizeof(int) * graph->nbr_n)))
// 		return (NULL);
// 	while (i++ < graph->nbr_n)
// 	{
// 		if(!(path[i] = malloc(sizeof(int) * 2)))
// 			return (NULL);
// 		path[i][0] = -1;
// 		path[i][1] = -1;
// 	}
// 	return (bfs_2(graph, path, stack));
// }

int		set_matrix(t_graph *graph)
{
	if (!(graph->links = malloc(sizeof(int*) * graph->nbr_n)))
		return(0);
	int i = -1;
	while (i++ < graph->nbr_n)
	{
		if (!(graph->links[i] = malloc(sizeof(int) * graph->nbr_n)))
			return (0);
	}
	if (!(graph->tmp_path = malloc(sizeof(int*) * graph->nbr_n)))
		return (0);
	if (!(graph->stack_path = malloc(sizeof(int) * graph->nbr_n)))
		return (0);
	i = -1;
	while (i++ < graph->nbr_n)
	{
		if(!(graph->tmp_path[i] = malloc(sizeof(int) * 2)))
			return (0);
		graph->tmp_path[i][0] = -1;
		graph->tmp_path[i][1] = -1;
	}
	graph->stack_path[0] = 0;
	graph->tmp_path[0][0] = 0;
	graph->tmp_path[0][1] = 0;
	return (1);
}

int 	main()
{
	t_graph	graph;
	graph.nbr_n = 6;
	set_matrix(&graph);

	for (int i=0;i<graph.nbr_n ; i++)
	{
			for (int j=0;j<graph.nbr_n ; j++)
			{
				graph.links[i][j] = graph.nbr_n + 1;
			}
	}
	//graph.links[0][4] = 1;
	graph.links[0][2] = 1;
	graph.links[4][3] = 1;
	//graph.links[4][1] = 1;
	graph.links[3][5] = 1;
	graph.links[2][1] = 1;
	graph.links[1][5] = 1;


	graph.links[4][0] = 1;
	graph.links[2][0] = 1;
	graph.links[3][4] = 1;
	graph.links[1][4] = 1;
	graph.links[5][3] = 1;
	graph.links[1][2] = 1;
	graph.links[5][1] = 1;

	bfs(&graph);
	for (int i=0;i<graph.nbr_n ; i++)
		{
			ft_putnbr(i);
			ft_putchar('\t');
			ft_putnbr(graph.tmp_path[i][0]);
			ft_putchar('\t');
			ft_putnbr(graph.tmp_path[i][1]);
			ft_putchar('\n');
		}
	return (0);
}
