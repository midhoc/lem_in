/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 12:13:50 by hmidoun           #+#    #+#             */
/*   Updated: 2020/01/12 08:04:01 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"

typedef struct s_all_paths	t_all_paths;
struct	s_all_paths	//list of all paths
{
	int				*path;
	int				size;
};

typedef struct s_node	t_node;
struct	s_node
{
	char			*name;
	int				n_node;
	t_node			*next;
};
typedef struct s_graph	t_graph;
struct	s_graph
{
	int				nbr_f;//fourmie
	int				nbr_n;//nodes
	int				**links;//links matrix

	int				**tmp_path;//current path for bfs
	int				*stack_path;//stack for bfs

	int				nbr_curr_paths;
	t_all_paths		*curr_paths;
	int				nbr_next_paths;
	t_all_paths		*next_paths;

	t_node			*tab_nodes;
};

int			cond_path_change(t_graph *graph, int k, int i_s_stack);
void		init_path(t_graph *graph);
void		bfs_conditions(t_graph *graph, int *i_link, int *tmp, int i[2]);
void		bfs(t_graph *graph);


int			set_matrix(t_graph *graph);


void		block_links(t_graph *graph);
void		fill_paths(t_graph *graph, int i[3], int *n);
int			nbr_paths(t_graph *graph);
int			get_paths(t_graph *graph);

void		free_paths(t_graph *paths, int flag);
int			free_graph(t_graph *graph);

#endif
