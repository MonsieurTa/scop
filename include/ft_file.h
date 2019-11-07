/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:47:36 by wta               #+#    #+#             */
/*   Updated: 2019/11/07 15:54:05 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILE_H
# define FT_FILE_H

# define MAX_FILEPATH	2048

# include <sys/stat.h>

typedef struct	s_file
{
	int					fd;
	char				filepath[MAX_FILEPATH];
	struct stat	file_stat;
	void				*content;
}				t_file;

int		store_data(t_file *data, const char *filepath);

#endif