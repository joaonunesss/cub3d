/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_game_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:35:11 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/06 16:03:08 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_check_if_line_is_blank(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

void	ft_copy_game_map(t_mlx *mlx)
{
	int		i;
	int		fd;
	char	*line;

	mlx->map.game_map = ft_calloc(sizeof(char *), mlx->map.total_lines);
	if (!mlx->map.game_map)
		ft_perror ("ERROR\nMalloc for mlx->map.game_map failed\n", mlx);
	fd = open(mlx->file, O_RDONLY);
	if (fd < 0)
		ft_perror("ERROR\nCouldn't open requested file\n", mlx);
	line = get_next_line(fd);
	i = -1;
	while (++i < mlx->map.lines_to_map)
	{
		free (line);
		line = get_next_line(fd);
	}
	i = -1;
	while (line)
	{
		if (ft_check_if_line_is_blank(line))
		{
			free (line);
			break ;
		}
		mlx->map.game_map[++i] = ft_strdup(line);
		free (line);
		line = get_next_line(fd);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_check_if_line_is_blank(line))
		{
			while (line)
			{
				free (line);
				line = get_next_line(fd);
			}
			close(fd);
			ft_perror("ERROR\nInvalid Map\n", mlx);
		}
		free (line);
		line = get_next_line(fd);
	}
	mlx->map.game_map[i + 1] = NULL;
	close(fd);
}
