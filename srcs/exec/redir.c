/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:32:07 by machouba          #+#    #+#             */
/*   Updated: 2024/09/02 18:15:10 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui cree une redirection*/
static t_redirect	*init_redirect(void)
{
	t_redirect	*redirect;

	redirect = malloc(sizeof(t_redirect));
	if (!redirect)
		return (NULL);
	redirect->input_fd = STDIN_FILENO;
	redirect->output_fd = STDOUT_FILENO;
	redirect->infile = NULL;
	redirect->outfile = NULL;
	return (redirect);
}

/*Fonction qui ouvre tous les fichiers necessaires je pense*/
static int	open_all(t_data *data, t_redirect *redirect, int flag_append)
{
	if (redirect->infile)
	{
		redirect->input_fd = open(redirect->infile, O_RDONLY);
		if (redirect->input_fd == -1 || redirect->input_fd > MAXFDS)
		{
			data->exit_return = 1;
			return (ft_putstr_fd("minichill: ", 2), perror(redirect->infile),
				free(redirect), -1);
		}
	}
	if (redirect->outfile)
	{
		if (flag_append == TRUE)
			redirect->output_fd = open(redirect->outfile,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			redirect->output_fd = open(redirect->outfile,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (redirect->output_fd == -1 || redirect->output_fd > MAXFDS)
			return (data->exit_return = 1, close(redirect->input_fd),
				perror(redirect->outfile), free(redirect), -1);
	}
	return (SUCCESS);
}

/*Fonction qui gere les outfiles pour les redirects*/
static int	outfile_for_redirs(t_data *data, t_redirect *redir,
		t_token *current, int flag)
{
	if (flag == TRUE)
		redir->output_fd = open(current->value, O_CREAT | O_WRONLY | O_APPEND,
				0644);
	else
		redir->output_fd = open(current->value, O_CREAT | O_WRONLY | O_TRUNC,
				0644);
	if (redir->output_fd == -1 || redir->output_fd > MAXFDS)
	{
		data->exit_return = 1;
		return (ft_putstr_fd("minichill : ", 2), perror(current->value), FAIL);
	}
	if (redir->output_fd != STDOUT_FILENO)
		close(redir->output_fd);
	redir->outfile = current->value;
	return (SUCCESS);
}
/*Fonction qui gere les tokens*/

static int	token_for_redirs(t_data *data, t_token *current, t_redirect *redir,
		t_command *cmd)
{
	int	flag;

	flag = FALSE;
	if (current->infile_flag == TRUE || current->type == LIM)
	{
		redir->infile = current->value;
		if (current->heredoc)
			redir->infile = current->heredoc;
		if (access(redir->infile, F_OK | R_OK) == -1)
		{
			data->exit_return = 1;
			return (ft_putstr_fd("minichill : ", 2), perror(redir->infile), -1);
		}
	}
	if (current->outfile_flag == TRUE)
	{
		flag = append_check(cmd, current->value);
		if (flag == -1)
			return (-1);
		if (outfile_for_redirs(data, redir, current, flag) == -1)
			return (-1);
		return (flag);
	}
	return (FALSE);
}

/*Fonction qui redirect*/
t_redirect	*redir(t_data *data, t_command *cmd)
{
	t_token		*token;
	t_redirect	*redir;
	int			flag;

	flag = FALSE;
	token = cmd->tokens;
	redir = init_redirect();
	if (!redir || !token)
		return (NULL);
	while (token != NULL)
	{
		flag = token_for_redirs(data, token, redir, cmd);
		if (flag == -1)
			return (free(redir), NULL);
		token = token->next;
	}
	if (open_all(data, redir, flag) == -1)
		return (free(redir), NULL);
	return (redir);
}
