/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 12:46:41 by adayrabe          #+#    #+#             */
/*   Updated: 2018/08/21 12:46:45 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		parce_field(t_filler *f)
{
	char	*temp;
	int		i;
	char	*line;

	get_next_line(0, &line);
	f->field_rows = ft_atoi(ft_strstr(line, " ") + 1);
	temp = ft_strnew(2);
	temp[0] = f->field_rows % 10 + '0';
	temp[1] = ' ';
	f->field_cols = ft_atoi(ft_strstr(line, temp) + 2);
	ft_strdel(&temp);
	ft_strdel(&line);
	get_next_line(0, &temp);
	ft_strdel(&temp);
	f->field = (char **)malloc(sizeof(char *) * f->field_rows);
	i = 0;
	while (i < f->field_rows && ++i)
	{
		get_next_line(0, &temp);
		f->field[i - 1] = ft_strdup(ft_strstr(temp, " ") + 1);
		ft_strdel(&temp);
	}
}

void		parce_token(t_filler *f)
{
	char	*temp;
	int		i;
	char	*line;
	char	**t;

	get_next_line(0, &line);
	f->real_token_rows = ft_atoi(ft_strstr(line, " ") + 1);
	temp = ft_strdup("  ");
	temp[0] = f->real_token_rows % 10 + '0';
	f->real_token_cols = ft_atoi(ft_strstr(line, temp) + 2);
	ft_strdel(&line);
	ft_strdel(&temp);
	t = (char **)malloc(sizeof(char *) * f->real_token_rows);
	i = 0;
	while (i < f->real_token_rows && ++i)
	{
		get_next_line(0, &temp);
		t[i - 1] = ft_strdup(temp);
		ft_strdel(&temp);
	}
	cut_token(f, t);
	i = 0;
	while (i < f->real_token_rows && ++i)
		ft_strdel(&t[i - 1]);
	free(t);
}

t_filler	*create_struc(void)
{
	t_filler	*res;
	char		*temp;

	res = (t_filler *)malloc(sizeof(t_filler));
	res->me = 'X';
	res->opponent = 'X';
	res->field = NULL;
	res->field_rows = 0;
	res->field_cols = 0;
	res->token = NULL;
	res->token_rows = 0;
	res->token_cols = 0;
	res->token_x = -1;
	res->token_y = -1;
	res->dist = -1;
	res->real_token_rows = 0;
	res->real_token_cols = 0;
	res->del_from_left = 0;
	res->del_from_top = 0;
	get_next_line(0, &temp);
	(ft_strchr(temp, '1')) ? (res->me = 'O') :
	(res->opponent = 'O');
	ft_strdel(&temp);
	return (res);
}

void		refresh_struct(t_filler *f)
{
	int i;

	i = 0;
	if (f->field)
	{
		while (i < f->field_rows && ++i)
			ft_strdel(&(f->field[i - 1]));
		free(f->field);
		f->field = NULL;
	}
	i = 0;
	if (f->token)
	{
		while (i < f->token_rows && ++i)
			ft_strdel(&(f->token[i - 1]));
		free(f->token);
		f->token = NULL;
	}
	f->token_x = -1;
	f->token_y = -1;
	f->dist = -1;
}

int			main(void)
{
	t_filler *f;

	f = create_struc();
	while (1)
	{
		parce_field(f);
		parce_token(f);
		play(f);
		ft_putnbr((f->token_x != -1) * (f->token_x - f->del_from_top));
		ft_putchar(' ');
		ft_putnbr((f->token_y != -1) * (f->token_y - f->del_from_left));
		ft_putchar('\n');
		if (f->token_x == -1)
		{
			refresh_struct(f);
			free(f);
			f = NULL;
			exit(1);
		}
		refresh_struct(f);
	}
	return (0);
}
