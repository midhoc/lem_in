/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 12:13:50 by hmidoun           #+#    #+#             */
/*   Updated: 2020/01/04 03:58:48 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"

typedef struct s_all_paths	t_all_paths;
struct	s_all_path	//list of all paths
{
	int				*path;
	int				size;
	t_all_paths		*next;
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
	t_node			*tab_n;
};
#endif
