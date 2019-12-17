/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    lem_in.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 12:13:50 by hmidoun           #+#    #+#             */
/*   Updated: 2019/12/17 21:10:09 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"

typedef struct s_node	t_node;
struct	s_node
{
	char			*name;
	int				n_node;
	int				free;
};

typedef struct s_graph	t_graph;
struct	s_graph
{
	int				nbr_f;
	int				nbr_n;
	int				**links;
	t_node			*tab_n;
};
#endif
