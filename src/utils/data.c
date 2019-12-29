/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:54:51 by wta               #+#    #+#             */
/*   Updated: 2019/11/06 18:06:02 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_printf.h"
#include "scop.h"

int	store_data(t_file *data, const char *filepath)
{
	ft_memcpy(data->filepath, filepath, MIN(MAX_FILEPATH, ft_strlen(filepath)));
	if ((data->fd = open(filepath, O_RDONLY)) == -1)
	{
		ft_printf("storing error (%s): open failed\n", filepath);
		return (-1);
	}
	if (fstat(data->fd, &data->file_stat) == -1)
	{
		ft_printf("fstat (%s): fstat failed\n", filepath);
		return (-1);
	}
	data->content = (char*)mmap(NULL, data->file_stat.st_size,
		PROT_READ, MAP_PRIVATE, data->fd, 0);
	if (data->content == NULL)
	{
		ft_printf("mmap (%s): content is NULL\n", filepath);
		return (-1);
	}
	close(data->fd);
	return (0);
}
