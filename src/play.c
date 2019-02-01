/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 12:48:57 by adayrabe          #+#    #+#             */
/*   Updated: 2018/08/21 12:48:59 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int			dist(t_filler *f, int pos_x, int pos_y)
{
	int i;
	int j;
	int res;

	i = 0;
	res = -1;
	while (i < f->field_rows && !(j = 0) && ++i)
		while (j < f->field_cols && ++j)
			if (f->field[i - 1][j - 1] == f->opponent && (res == -1
				|| (ft_abs(pos_x + 1 - i) + ft_abs(pos_y + 1 - j) < res)))
				res = ft_abs(pos_x + 1 - i) + ft_abs(pos_y + 1 - j);
	return (res);
}

int			find_distance(t_filler *f, int pos_x, int pos_y)
{
	int i;
	int j;
	int res;
	int temp;

	i = 0;
	res = -1;
	while (i < f->token_rows && i + pos_x < f->field_rows && ++i && !(j = 0))
		while (j < f->token_cols && j + pos_y < f->field_cols && ++j)
			if (f->token[i - 1][j - 1] == '*')
			{
				temp = dist(f, pos_x + i - 1, pos_y + j - 1);
				if (temp < res || res == -1)
					res = temp;
			}
	return (res);
}

int			can_put_token(t_filler *f, int pos_x, int pos_y)
{
	int		i;
	int		j;
	int		overlays;
	char	temp;

	i = 0;
	overlays = 0;
	if (pos_x + f->token_rows > f->field_rows ||
		pos_y + f->token_cols > f->field_cols)
		return (0);
	while (i < f->token_rows && i + pos_x < f->field_rows && ++i && !(j = 0))
		while (j < f->token_cols && j + pos_y < f->field_cols && ++j)
		{
			temp = f->field[pos_x + i - 1][pos_y + j - 1];
			if (f->token[i - 1][j - 1] == '*' && temp == f->opponent)
				return (0);
			if (f->token[i - 1][j - 1] == '*' && temp == f->me)
			{
				if (overlays)
					return (0);
				else
					++overlays;
			}
		}
	return (overlays);
}

void		play(t_filler *f)
{
	int i;
	int j;
	int temp;

	i = 0;
	while (i < f->field_rows && !(j = 0) && ++i)
		while (j < f->field_cols && ++j)
			if (can_put_token(f, i - 1, j - 1))
			{
				temp = find_distance(f, i - 1, j - 1);
				if (f->dist == -1 || temp < f->dist)
				{
					f->dist = temp;
					f->token_x = i - 1;
					f->token_y = j - 1;
				}
			}
}
