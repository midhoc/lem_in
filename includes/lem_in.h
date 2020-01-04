/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 12:13:50 by hmidoun           #+#    #+#             */
/*   Updated: 2020/01/04 03:23:51 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"

typedef struct s_all_path	t_all_path;
struct	s_all_path
{
	int				*path;
	int				size;
	t_all_path		*next;
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
	int				nbr_f;
	int				nbr_n;
	int				**links;
	int				**tmp_path;
	int				*stack_path;
	t_node			*tab_n;
};
#endif
