#include "header/wolf.h"

void	open_file(t_info *i, char *filename)
{
	int		fd;
	char	*line;
	int		lines;
	int		c;

	c = 0;
	fd = open(filename, O_RDONLY);
	i->tab = (int **)malloc(sizeof(int *) * lines);
	while ((get_next_line(fd, &line)) > 0)
	{
		i->tab[c] = get_int_tab(line, i);
		c++;
	}
	i->tab[c] = NULL;
}

int		*get_int_tab(char *str, t_info *s)
{
	int		i;
	char	**tmp;
	int		*tab;

	tab = NULL;
	i = 0;
	tmp = ft_strsplit(str, ' ');
	tab = (int *)malloc(sizeof(int) * count_col(tmp, s));
	while (tmp[i])
	{
		check_char(*tmp[i]);
		tab[i] = ft_atoi(tmp[i]);
		i++;
	}
	return (tab);
}

int		count_col(char **tab, t_info *s)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	check_char(char c)
{
	if (ft_isdigit(c) || c == ' ' || c == '-')
		;
	else
		FDF_ERROR;
}
