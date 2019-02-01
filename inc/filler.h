/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 12:50:13 by adayrabe          #+#    #+#             */
/*   Updated: 2018/08/21 12:50:14 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include <libft.h>

typedef struct	s_filler
{
	char	me;
	char	opponent;
	char	**field;
	int		field_rows;
	int		field_cols;
	char	**token;
	int		token_rows;
	int		token_cols;
	int		token_x;
	int		token_y;
	int		dist;
	int		real_token_rows;
	int		real_token_cols;
	int		del_from_top;
	int		del_from_left;
}				t_filler;

void			play(t_filler *f);
void			cut_token(t_filler *f, char **t);

#endif
