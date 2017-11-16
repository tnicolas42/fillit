/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 algo.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: pmilan <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2017/11/15 15:08:20 by pmilan			   #+#	  #+#			  */
/*	 Updated: 2017/11/15 15:08:20 by pmilan			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <serge.h>

int			ft_int_sqrt(int n)
{
	int i;

	i = 1;
	while (i * i < n)
		i++;
	return (i);
}

int			ft_size_min_square(t_tetris **t)
{
	int size;

	size = ft_int_sqrt(t[0]->nb_form * 4);
	if (size < 4)
		size = 4;
	return (size);
}

int			ft_init_tab(int **tab, int size)
{
	int i;

	free(*tab);
	i = size * size;
	if (!(*tab = (int *)malloc(sizeof(**tab) * i)))
		return (FAILURE);
	while (--i >= 0)
		(*tab)[i] = -1;
	return (SUCCESS);
}

int			ft_is_possible(t_tetris **t, int *tab, int count, int size)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if ((j + (t[count])->y >= size && (t[count])->form[i][j] == 1) ||
					((t[count])->form[i][j] == 1 &&
						tab[((t[count])->x + i) * size + (t[count])->y + j] != -1))
					return (FAILURE);
		}
	}
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (t[count]->form[i][j] == 1)
				tab[((t[count])->x + i) * size + (t[count])->y + j] = count;
		}
	}
	return (SUCCESS);
}

int			ft_put_top_left(t_tetris **t, int *tab, int count, int size)
{
	int i;
	int j;
	int last_x;

	last_x = (t[count])->x;
	i = (last_x == -1) ? -1 : last_x - 1;
	while (++i < size)
	{
		j = (i == last_x) ? (t[count])->y - 1 : -1;
		while (++j < size)
		{
			(t[count])->x = i;
			(t[count])->y = j;
			if (ft_is_possible(t, tab, count, size) == SUCCESS)
				return (SUCCESS);
		}
	}
	(t[count])->x = -1;
	(t[count])->y = -1;
	return (FAILURE);
}

void		ft_print(int *tab, int size)
{
	int i;
	int j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (tab[i * size + j] == -1)
				ft_putchar('.');
			else
			{
				printf("\x1b[%dm%c"NORMAL, tab[i * size + j] % 6 + 31,
						tab[i * size + j] + 'A');///////////////////////////////
				fflush(stdout);/////////////////////////////////////////////////
				//ft_putchar(tab[i * size + j] + 'A');
			}
		}
		ft_putchar('\n');
	}
	printf("\n");///////////////////////////////////////////////////////////////
}

void		ft_rekt_form(t_tetris **t, int *tab, int count, int size)
{
	int i;
	int sq;

	i = -1;
	sq = size * size;
	while (++i < sq)
	{
		if (tab[i] == count)
			tab[i] = -1;
	}
	if ((t[count])->y == size - 1)
	{
		(t[count])->x++;
		(t[count])->y = 0;
	}
	else
		(t[count])->y++;
}

void		ft_reset(t_tetris **t)
{
	int		i;

	i = -1;
	while (++i < (t[0])->nb_form)
	{
		(t[i])->x = -1;
		(t[i])->y = -1;
	}
}

void		ft_resolve(t_tetris **t)
{
	int size;
	int *tab;
	int count;

	tab = NULL;
	count = 0;
	size = ft_size_min_square(t);
	while (count < (t[0])->nb_form)
	{
		ft_reset(t);
		if (ft_init_tab(&tab, size) == FAILURE)
			return ;
		count = 0;
		while (count < (t[0])->nb_form)
		{
			if (ft_put_top_left(t, tab, count, size) == SUCCESS)
				count++;
			else
			{
				//ft_print(tab, size);
				if (count <= 0)
				{
					size++;
					break;
				}
				ft_rekt_form(t, tab, --count, size);
			}
			if (count < 0)
			{
				size++;
				break;
			}
		}
	}
	if (count == (t[0])->nb_form)
	{
	int l = -1;////////////////////
		ft_putstr("OK\n");
		while (++l < (t[0])->nb_form)
			printf("%c\n\tx -> %d\n\ty-> %d\n", l + 'A', (t[l])->x, (t[l])->y);
	}
	ft_print(tab, size);
}