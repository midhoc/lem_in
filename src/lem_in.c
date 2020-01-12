/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:24:35 by hmidoun           #+#    #+#             */
/*   Updated: 2020/01/12 08:19:07 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			set_matrix(t_graph *graph)
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

int 	main()
{
	t_graph	graph;
	graph.nbr_n = 14;
	if (!set_matrix(&graph))
		return(free_graph(&graph));

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

	if (!get_paths(&graph))
		return(free_graph(&graph));
	// if (!graph.curr_paths)
	// 	graph.curr_paths = graph.next_paths;
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
	for(int i= 0; i < graph.nbr_next_paths; i++)
	{
		for (int j = 0; j < graph.next_paths[i].size; j++)
		{
			ft_putnbr(graph.next_paths[i].path[j]);
			ft_putchar('\t');
		}
		ft_putchar('\n');
	}
	free_graph(&graph);
	while(1);
	return (0);
}
