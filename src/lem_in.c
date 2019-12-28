/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:24:35 by hmidoun           #+#    #+#             */
/*   Updated: 2019/12/28 05:04:54 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


int		**bfs_2(t_graph *graph, int **path, int *stack)
{
	int		i;
	int		j;
	int		k;

	stack[0] = 0;
	 path[0][0] = 0;
		 path[0][1] = 0;
	i = 0;
	j = 1;
	while (i < j)
	{
		k = -1;
		while (k++ < graph->nbr_n)
		{
			if (graph->links[stack[i]][k] == 1)
			{
				stack[j] = k;
				if ((path[k][0] == 0 && path[k][1] == 0) || path[k][1] < path[stack[i]][1])
				{
					path[k][0] = stack[i];
					path[k][1] = path[stack[i]][1] + 1;
				}
				j++;
			}
		}
		i++;
	}
	return (path);
}
int		**bfs(t_graph *graph)
{
	int		**path;
	int		i;
	int		*stack;

	i = -1;
	path = malloc(sizeof(int*) * graph->nbr_n);
	stack = malloc(sizeof(int) * graph->nbr_n);
	while (i++ < graph->nbr_n)
		path[i] = malloc(sizeof(int) * 2);
	//ft_bzero(path, sizeof(path));
	return (bfs_2(graph, path, stack));
}

void	set_matrix(t_graph *graph)
{
	graph->links = malloc(sizeof(int*) * graph->nbr_n);
	int i = -1;
	while (i++ < graph->nbr_n)
		graph->links[i] = malloc(sizeof(int) * graph->nbr_n);
	//ft_bzero(graph->links, sizeof(graph->links));
}

int 	main()
{
	t_graph	graph;
	int		**path;
	graph.nbr_n = 5;
	set_matrix(&graph);

	for (int i=0;i<5; i++)
	{
			for (int j=0;j<5; j++)
			{
				graph.links[i][j] = graph.nbr_n + 1;
			}
	}
	graph.links[0][2] = 1;
	graph.links[2][3] = 1;
	graph.links[2][1] = 1;
	graph.links[3][4] = 1;
	graph.links[3][1] = 1;
	path = bfs(&graph);
	for (int i=0;i<5; i++)
		{
			ft_putnbr(i);
			ft_putchar('\t');
			ft_putnbr(path[i][0]);
			ft_putchar('\t');
			ft_putnbr(path[i][1]);
			ft_putchar('\n');
		}
	return (0);
}
