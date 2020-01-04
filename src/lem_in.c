/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:24:35 by hmidoun           #+#    #+#             */
/*   Updated: 2020/01/04 05:50:04 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			cond_path_change(t_graph *graph, int k, int i_s_stack)
{
	if ((graph->links[graph->stack_path[i_s_stack]][k] == 1) &&
			((graph->tmp_path[k][0] == -1 && graph->tmp_path[k][1] == -1) ||
			graph->tmp_path[k][1] > graph->tmp_path[graph->stack_path[i_s_stack]][1]))
		return (1);
	return (0);
}
void		set_path(t_graph *graph)
{
	int		i;
	i = -1;
	while (++i < graph->nbr_n)
	{
		graph->tmp_path[i][0] = -1;
		graph->tmp_path[i][1] = -1;
		graph->tmp_path[i][2] = 0;
	}
	graph->stack_path[0] = 0;
	graph->tmp_path[0][0] = 0;
	graph->tmp_path[0][1] = 0;
}
void		bfs(t_graph *graph)
{
	int		i_s_stack;
	int		i_e_stack;
	int		i_link;
	int		tmp;

	set_path(graph);
	i_s_stack = 0;
	i_e_stack = 1;
	while (i_s_stack < i_e_stack)
	{
		i_link = -1;
		tmp = 0;
		while (++i_link < graph->nbr_n && tmp >= 0 )
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
				if (!graph->tmp_path[i_link][2])
				{
					graph->stack_path[i_e_stack] = i_link;
					i_e_stack++;
					graph->tmp_path[i_link][2] = 1;
				}
				graph->tmp_path[i_link][0] = graph->stack_path[i_s_stack];
				tmp++;
			}
		}
		i_s_stack++;
	}
}

int		set_matrix(t_graph *graph)
{
	if (!(graph->links = malloc(sizeof(int*) * graph->nbr_n)))
		return(0);
	int i = -1;
	while (++i < graph->nbr_n)
	{
		if (!(graph->links[i] = malloc(sizeof(int) * graph->nbr_n)))
			return (0);
	}
	if (!(graph->tmp_path = malloc(sizeof(int*) * graph->nbr_n)))
		return (0);
	if (!(graph->stack_path = malloc(sizeof(int) * graph->nbr_n)))
		return (0);
	i = -1;
	while (++i < graph->nbr_n)
	{
		if(!(graph->tmp_path[i] = malloc(sizeof(int) * 3)))
			return (0);
		graph->tmp_path[i][0] = -1;
		graph->tmp_path[i][1] = -1;
		graph->tmp_path[i][2] = 0;
	}

	return (1);
}

void	block_links(t_graph *graph)
{
	int		i;
	int		j,k;
	i = 1;
	while (i)
	{
		j = graph->tmp_path[i][0];
		graph->links[j][i] = graph->nbr_n + 1;
		k = graph->links[j][i];
		i = graph->tmp_path[i][0];
	}
}


// int		*get_path(t_graph *graph)
// {
// 	int *res;
// 	int	n = graph->tmp_path[1][1];
// 	int	i = 1;
// 	res = malloc(sizeof(int) * n);
// 	while(--n >= 0)
// 	{
// 		res[n] = i;
// 		i =
// 	}
// 	return (res);
// }

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
	graph.links[0][4] = 1;
	graph.links[0][2] = 1;
	graph.links[4][3] = 1;
	graph.links[4][5] = 1;
	graph.links[3][1] = 1;
	graph.links[2][5] = 1;
	graph.links[5][1] = 1;


	graph.links[4][0] = 1;
	graph.links[2][0] = 1;
	graph.links[3][4] = 1;
	graph.links[5][4] = 1;
	graph.links[1][3] = 1;
	graph.links[5][2] = 1;
	graph.links[1][5] = 1;

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
	ft_putchar('\n');
	block_links(&graph);
	for (int i=0;i<graph.nbr_n ; i++)
	{
			for (int j=0;j<graph.nbr_n ; j++)
			{
				ft_putnbr(graph.links[i][j]);
				ft_putchar('\t');
			}
			ft_putchar('\n');
	}
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
