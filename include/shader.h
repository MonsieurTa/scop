/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 10:30:59 by wta               #+#    #+#             */
/*   Updated: 2019/10/25 16:40:16 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

# define SHADER_BUFF_SIZE	2048
# define MAX_SHADER			16

# include "scop.h"

typedef struct	s_shader
{
	GLuint	id;
	GLuint	shader_ids[MAX_SHADER];
	GLuint	active;
	void	(*create)(struct s_shader *, const GLenum, const GLchar *);
	void	(*attach_shaders)(struct s_shader *);
	void	(*link_program)(struct s_shader *);
	void	(*set_int)(struct s_shader *, GLchar *, GLint);
	void	(*set_float)(struct s_shader *, GLchar *, GLfloat);
	void	(*set_3fv)(struct s_shader *, GLchar *, GLfloat [3]);
}				t_shader;

/*
**	shader constructor
*/

t_shader	new_shader(void);

/*
**	shader's methods
*/

void		set_int(t_shader *ctx, GLchar *name, GLint value);
void		set_float(t_shader *ctx, GLchar *name, GLfloat value);
void		set_3fv(t_shader *ctx, GLchar *name, GLfloat value[3]);
void		create_shader(t_shader *ctx, const GLenum type, const GLchar *src);
void		attach_shaders(t_shader *ctx);
void		link_program(t_shader *ctx);


#endif
