/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:24:35 by hmidoun           #+#    #+#             */
/*   Updated: 2020/01/08 02:44:56 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			cond_path_change(t_graph *graph, int k, int i_s_stack)
{
	if ((graph->links[graph->stack_path[i_s_stack]][k] == 1) &&
			 ((/*graph->tmp_path[k][0] == -1 &&*/ graph->tmp_path[k][1] == -1) ||
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
				if (graph->links[graph->stack_path[i_s_stack]][graph->tmp_path[graph->stack_path[i_s_stack]][0]] == graph->nbr_n + 1)
					graph->tmp_path[i_link][1] = graph->tmp_path[graph->stack_path[i_s_stack]][1] + 1;
				else if (graph->links[i_link][graph->stack_path[i_s_stack]] == graph->nbr_n + 1)
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

void	nbr_paths(t_graph *graph)
{
	int	i;

	graph->nbr_paths = 0;
	i = -1;
	while (++i < graph->nbr_n)
	{
		if (graph->links[1][i] == 1 && graph->links[i][1] == graph->nbr_n + 1)
			graph->nbr_paths++;
	}
}

int		get_paths(t_graph *graph)
{
	int	n;
	int	i0;
	int i1;
	int	i;

	nbr_paths(graph);
	n = graph->nbr_paths;
	if (!(graph->next_paths = malloc(sizeof(t_all_paths) * n)))
		return (0);
	n--;
	i = -1;
	while (n >= 0 && ++i < graph->nbr_n)
	{
		if (!(graph->next_paths[n].path = malloc(sizeof(int) * graph->nbr_n)))
			return (0);
		i0 = 0;
		i1 = i;
		graph->next_paths[n].size = 0;
		while (++i1 < graph->nbr_n && i0 != 1)
		{
			if (graph->links[i1][i0] == 1 && graph->links[i0][i1] == graph->nbr_n + 1)
			{
				if (i0 == 0)
					i = i1;
				graph->next_paths[n].path[graph->next_paths[n].size] = i1;
				graph->next_paths[n].size++;
				i0 = i1;
				i1 = 0;
			}
			if (i0 == 1)
				n--;
		}
	}
	return (1);
}

int 	main()
{
	t_graph	graph;
	graph.nbr_n = 14;
	set_matrix(&graph);

	for (int i=0;i<graph.nbr_n ; i++)
	{
			for (int j=0;j<graph.nbr_n ; j++)
			{
				graph.links[i][j] = graph.nbr_n + 1;
			}
	}
	graph.links[0][2] = 1;
	graph.links[0][6] = 1;
	graph.links[0][10] = 1;

	graph.links[2][3] = 1;
	graph.links[3][4] = 1;
	graph.links[4][5] = 1;

	graph.links[6][7] = 1;
	graph.links[7][8] = 1;
	graph.links[8][9] = 1;

	graph.links[10][11] = 1;
	graph.links[11][12] = 1;
	graph.links[12][13] = 1;

	graph.links[10][7] = 1;
	graph.links[7][5] = 1;

	graph.links[5][1] = 1;
	graph.links[9][1] = 1;
	graph.links[13][1] = 1;

	for (int i=0;i<graph.nbr_n ; i++)
	{
			for (int j=0;j<graph.nbr_n ; j++)
			{
				if (graph.links[i][j] == 1)
					graph.links[j][i] = 1;
			}
	}
	// graph.links[6][7] = 15;
	// graph.links[7][5] = 15;
	// graph.links[5][1] = 15;


	bfs(&graph);
	block_links(&graph);


	bfs(&graph);
	block_links(&graph);

	 //bfs(&graph);
	// block_links(&graph);

	// for (int i=0;i<graph.nbr_n ; i++)
	// {
	// 	ft_putnbr(i);
	// 	ft_putchar('\t');
	// 	ft_putnbr(graph.tmp_path[i][0]);
	// 	ft_putchar('\t');
	// 	ft_putnbr(graph.tmp_path[i][1]);
	// 	ft_putchar('\n');
	// }
	// 	ft_putchar('\n');

	get_paths(&graph);
	if (!graph.curr_paths)
		graph.curr_paths = graph.next_paths;
	// else
	// {
	// 	if(test(next_paths, curr_path))
	// 	{
	// 		free(curr_paths);
	// 		copy next to curr
	// 		free (next);
	// 	}
	// 	else
	// 	{
	// 		finish bfs
	// 	}

	// }
	for(int i= 0; i < graph.nbr_paths; i++)
	{
		for (int j = 0; j < graph.curr_paths[i].size; j++)
		{
			ft_putnbr(graph.curr_paths[i].path[j]);
			ft_putchar('\t');
		}
		ft_putchar('\n');
	}
	return (0);
}
