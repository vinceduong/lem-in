#include "lem_in.h"

/*
start = [0];
end = [1];
ant = [2];
tube = [3];
room = [4];
*/

/*void ft_clear_1(char **tab, int i)
{
	while (i)
		free(tab[i--]);
	free(tab);
}*/

static int ft_se(char *str)
{
	if (ft_chrstr(str, ' ') == 1 && ft_chrstr(str, '-') == 0)
		return (1);
	return (0);
}


static void ft_read_data(char **tab, t_lemin *lemin, int i, int **error_tab)
{
	while (tab[++i])
	{
		if (ft_strcmp(tab[i], "##start") == 0)
			ft_se(tab[i + 1]) == 1 ? error_tab[0][0] = i + 1 : 0;
		else if (ft_strcmp(tab[i], "##end") == 0)
			ft_se(tab[i + 1]) == 1 ? error_tab[1][0] = i + 1 : 0;
		else if (ft_chrstr(tab[i], ' ') == 0 && ft_chrstr(tab[i], '-') == 1)
			error_tab[3][0]++;
		else if (ft_chrstr(tab[i], ' ') == 1 && ft_chrstr(tab[i], '-') == 0)
			error_tab[4][0]++;
		else if (tab[i][0] == '#')
			;
		else if (ft_isdigit(tab[i][0]) == 1 && lemin->a.nbants == 0 &&
				ft_chrstr(tab[i], ' ') == 0 && ft_chrstr(tab[i], '-') == 0)
		{
			error_tab[2][0]++;
		}
		else
			; //ft_error();
	}
	lemin->m.nbcases = error_tab[4][0];
	lemin->nb_link = error_tab[3][0];
	ft_check_value(error_tab) == 0 ? exit(0) : 0;
	ft_create_matrice(tab, lemin, error_tab);
}

static char **ft_read(char *str, char *line)
{
	while (get_next_line(0, &line) > 0)
	{
		str = ft_strjoin(str, line);
		str = ft_strjoin(str, "\n\0");
		ft_strdel(&line);
	}
	return (ft_strsplit(str, '\n'));
}

static int **ft_create_error_tab(void)
{
	int i;
	int **tab;

	i = 0;
	if (!(tab = (int**)malloc(sizeof(int*) * 6)))
		exit(0);
	while (i != 6)
	{
		if (!(tab[i] = (int*)malloc(sizeof(int) * 1)))
		{
			//ft_clear_1(tab, i);
			exit (0);
		}
		tab[i][0] = 0;
		tab[i][1] = 0;
		i++;
	}
	return (tab);
}

int parser(t_lemin *lemin)
{
	char **tab;
	char *str;
	char *line;
	int **error_tab;

	tab = NULL;
	lemin->r.nbturns = 3;
	if (!(str = ft_memalloc(0)))
		return (0);
	line = NULL;
	error_tab = ft_create_error_tab();
	tab = ft_read(str, line);
	ft_read_data(tab, lemin, -1, error_tab);
	printf("%s\n", "salut");
	return (1);
}
