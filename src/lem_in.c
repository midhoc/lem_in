/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:24:35 by hmidoun           #+#    #+#             */
/*   Updated: 2020/01/17 20:50:43 by hmidoun          ###   ########.fr       */
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
	graph->count_next_paths = 0;
	return (1);
}

 int		cp_paths(t_graph *graph)
 {
	int	i;
	int	j;

	i = -1;
	free_paths(graph, 0);
	graph->nbr_curr_paths = graph->nbr_next_paths;
	graph->count_curr_paths = graph->count_next_paths;
	if (!(graph->curr_paths = malloc(sizeof(t_all_paths) * graph->nbr_curr_paths)))
		return (0);
	while (++i < graph->nbr_curr_paths)
	{
		if (!(graph->curr_paths[i].path = malloc(sizeof(int) * graph->next_paths[i].size)))
			return (0);
		j = -1;
		while (++j < graph->next_paths[i].size)
			graph->curr_paths[i].path[j] = graph->next_paths[i].path[j];
	//	graph->curr_paths[i].path[j] = 0;
		graph->curr_paths[i].size = graph->next_paths[i].size;
	}
	free_paths(graph, 1);
	return (1);
 }

int		optimal_path(t_graph *graph)
{
	bfs(graph);
	if(block_links(graph)) //no path found from bfs to block it
	{
		if (!get_paths(graph))   //malloc prblm
			return(0);
		ft_count(graph);
		if (!graph->curr_paths)
		{
			if (!cp_paths(graph))			//malloc prblm
				return(0);
		}
		else if(graph->count_curr_paths > graph->count_next_paths)
		{
			if (!cp_paths(graph))			//malloc prblm
				return(0);
		}
		else
			return (-1);
	}
	else
		return (-1);
	return (1);
}

int 	main()
{
	t_graph	graph;


	graph.nbr_n = 8;

	// for(int l = 0; l < 30; l++)
	// {
	graph.nbr_f = 5;

	// ft_putnbr(l);
	//ft_putstr("**********\n");
		//ft_putchar('\n');


	if (!set_matrix(&graph))
		return(free_graph(&graph));

	for (int i=0;i<graph.nbr_n ; i++)
	{
			for (int j=0;j<graph.nbr_n ; j++)
			{
				graph.links[i][j] = graph.nbr_n + 1;
			}
	}
	// graph.links[0][2] = 1;
	// graph.links[0][6] = 1;
	// graph.links[0][10] = 1;
	// graph.links[0][14] = 1;

	// graph.links[2][3] = 1;
	// graph.links[3][4] = 1;
	// graph.links[4][5] = 1;

	// graph.links[6][7] = 1;
	// graph.links[7][8] = 1;
	// graph.links[8][9] = 1;

	// graph.links[10][11] = 1;
	// graph.links[11][12] = 1;
	// graph.links[12][13] = 1;

	// graph.links[14][15] = 1;
	// graph.links[15][16] = 1;
	// graph.links[16][17] = 1;
	// graph.links[17][18] = 1;
	// graph.links[18][1] = 1;

	// graph.links[10][7] = 1;
	// graph.links[7][5] = 1;

	// graph.links[5][1] = 1;
	// graph.links[9][1] = 1;
	// graph.links[13][1] = 1;


	graph.links[0][2] = 1;
	graph.links[0][3] = 1;
	graph.links[2][7] = 1;
	graph.links[2][4] = 1;
	graph.links[3][5] = 1;
	graph.links[3][4] = 1;
	graph.links[7][1] = 1;
	graph.links[7][6] = 1;
	graph.links[4][1] = 1;
	graph.links[4][7] = 1;
	graph.links[5][6] = 1;
	graph.links[6][1] = 1;

	for (int i=0;i<graph.nbr_n ; i++)
	{
			for (int j=0;j<graph.nbr_n ; j++)
			{
				if (graph.links[i][j] == 1)
					graph.links[j][i] = 1;
			}
	}
	graph.links[0][2] = graph.nbr_n + 1;
	graph.links[2][4] = graph.nbr_n + 1;
	graph.links[4][1] = graph.nbr_n + 1;


bfs(&graph);
block_links(&graph);

bfs(&graph);
block_links(&graph);

bfs(&graph);
block_links(&graph);
get_paths(&graph);

cp_paths(&graph);


	// bfs(&graph);
	// if(block_links(&graph)) //no path found from bfs to block it
	// {
	// 	if (!get_paths(&graph))   //malloc prblm
	// 		return(free_graph(&graph));
	// 	/*
	// 	shoud we use the new path
	// 	*/
	// 	if (!cp_paths(&graph))			//malloc prblm
	// 		return(free_graph(&graph));
	// }
	// 	bfs(&graph);
	// if(block_links(&graph)) //no path found from bfs to block it
	// {
	// 	if (!get_paths(&graph))   //malloc prblm
	// 		return(free_graph(&graph));
	// 	/*
	// 	shoud we use the new path
	// 	*/
	// 	if (!cp_paths(&graph))			//malloc prblm
	// 		return(free_graph(&graph));
	// }
	// 	bfs(&graph);
	// if(block_links(&graph)) //no path found from bfs to block it
	// {
	// 	if (!get_paths(&graph))   //malloc prblm
	// 		return(free_graph(&graph));
	// 	/*
	// 	shoud we use the new path
	// 	*/
	// 	if (!cp_paths(&graph))			//malloc prblm
	// 		return(free_graph(&graph));
	// }




	// else
	// {
	// 	ft_putstr("no more paths\n");
	// }
	// bfs(&graph);
	// block_links(&graph);

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
	// graph.curr_paths = malloc(sizeof(t_all_paths));
	// ft_memcpy(graph.curr_paths, graph.next_paths, sizeof(graph.next_paths));
	// graph.nbr_curr_paths = graph.nbr_next_paths;

	// int	ret;

	// while ((ret = optimal_path(&graph)) > 0);
	// if (ret == 0)
	// 	return (free_graph(&graph)); //malloc prblm
	// else if (ret == -1 && graph.count_next_paths == 0)
	// {
	// 	ft_putstr("no possible path\n");
	// 	return (free_graph(&graph));
	// }
	// else if (ret == -1)
	// 	ft_distrib_f(&graph);

	// ft_putnbr(graph.count_curr_paths);
	// ft_putstr("................count \n");
	for(int i = 0; i < graph.nbr_curr_paths; i++)
	{
		for (int j = 0; j < graph.curr_paths[i].size; j++)
		{
			ft_putnbr(graph.curr_paths[i].path[j]);
			ft_putchar('\t');
		}
		ft_putchar('\n');
		ft_putnbr(graph.curr_paths[i].f);
		ft_putchar('\n');
	}
	free_graph(&graph);
	ft_putchar('\n');
	// }
	// while(1);
	return (0);
}
