/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_tex.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:44:57 by wta               #+#    #+#             */
/*   Updated: 2019/11/07 17:19:10 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_TEX_H
# define GL_TEX_H

# if defined(__APPLE__)
# include <OpenGL/gl3.h>
# else
# include <GLES3/gl3.h>
# endif

# include "tga_loader.h"

typedef struct	s_gl_tex
{
	t_tga_loader	tga_loader;

	uint32_t			width;
	uint32_t			height;

	GLenum				format;
	GLint					internal_format;

	void					*data;

	int						(*load)(struct s_gl_tex *, char *,
		int (*store_data)(t_file *, const char *));
	void					(*destroy)(struct s_gl_tex *);
	void					(*enable_alpha)(void);
}								t_gl_tex;

void						get_gl_format(t_gl_tex *ctx);
t_gl_tex				gl_tex_init(void);

void						enable_alpha(void);


#endif
