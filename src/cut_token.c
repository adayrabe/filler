/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 19:09:35 by adayrabe          #+#    #+#             */
/*   Updated: 2018/09/11 19:09:36 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		cut_token_columns(t_filler *f, char **t, int i)
{
	int start;
	int end;
	int j;
	int temp;

	start = -1;
	end = 0;
	while (i < f->real_token_cols && ++i && (temp = -1))
	{
		j = 0;
		while (j < f->real_token_rows && ++j)
			if (t[j - 1][i - 1] == '*' && (temp = j - 1) != -1 && start == -1)
				start = i - 1;
		(temp != -1) ? end++ : 0;
	}
	f->token_cols = end;
	f->del_from_left = start;
	i = 0;
	while (i < f->token_rows && ++i)
	{
		f->token[i - 1] = ft_strnew(f->token_cols);
		f->token[i - 1] = ft_strncpy(f->token[i - 1],
				&t[i - 1 + f->del_from_top][f->del_from_left], f->token_cols);
	}
}

void		cut_token(t_filler *f, char **t)
{
	int i;
	int j;
	int start;
	int end;
	int temp;

	i = 0;
	start = -1;
	end = 0;
	while (i < f->real_token_rows && ++i)
	{
		j = 0;
		temp = -1;
		while (j < f->real_token_cols && ++j)
			if (t[i - 1][j - 1] == '*' && (temp = i - 1) != -1)
				(start == -1) ? (start = i - 1) : 0;
		(temp != -1) ? end++ : 0;
	}
	f->token_rows = end;
	f->del_from_top = start;
	f->token = (char **)malloc(end * sizeof(char *));
	cut_token_columns(f, t, 0);
}
