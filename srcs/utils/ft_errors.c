/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:05:54 by machouba          #+#    #+#             */
/*   Updated: 2024/09/04 16:24:59 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	error_pipe_at_end(t_token *lst)
{
	t_token	*current;

	current = lst;
	while (current->next)
	{
		if (current->pipe_flag == 1 && current->next->type == PIPE
			&& current->next->next == NULL)
		{
			ft_print_err(PIPE);
			return (-1);
		}
		current = current->next;
	}
	return (1);
}

void	error_token(t_token *token, int error_model)
{
	if (error_model == PIPE_AT_END)
		token->pipe_flag = true;
	else
	{
		token->flag_error = 1;
		token->type_error = error_model;
	}
}

void	ft_print_err(int error)
{
	if (error == APPEND)
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
	else if (error == HEREDOC)
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
	else if (error == RT)
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
	else if (error == LT)
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	else if (error == PIPE)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (error == NEWLINE_ERROR)
		ft_putstr_fd("minishell: syntax error near unexpected token `newlin'\n",
			2);
	else if (error == QUOTES_ERROR)
		ft_putstr_fd("minishell: unclosed single or double quote\n", 2);
	else if (error == DOUBLE_PIPE_ERROR)
		ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
	else if (error == HDEXEC)
		ft_putstr_fd("minishell: heredoc execution failed\n", 2);
}

int	ft_isdirectory(char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
			return (1);
		else
			return (0);
	}
	return (0);
}

void	ft_check_errors(t_data *data, t_command *cmd)
{
	if (ft_isdirectory(cmd->path) == 1)
	{
		ft_putstr_fd("minichill: ", 2);
		ft_putstr_fd(cmd->args_lst->value, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free_all(data);
		exit(126);
	}
	if (!cmd->path || (cmd->path && cmd->path[0] == '\0'))
	{
		ft_putstr_fd("minichill: ", 2);
		ft_putstr_fd(cmd->args_lst->value, 2);
		ft_putstr_fd(": command not found\n", 2);
		free_all(data);
		exit(127);
	}
	if (access(cmd->path, F_OK) == -1)
	{
		ft_putstr_fd("minichill: ", 2);
		ft_putstr_fd(cmd->args_lst->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free_all(data);
		exit(127);
	}
}
