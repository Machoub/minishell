/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gino <gino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:42:43 by gino              #+#    #+#             */
/*   Updated: 2024/08/06 18:49:16 by gino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui initialise une nouvelle commande*/
static t_command	*init_new_command(t_data *data, t_token *current, int pos)
{
	t_command	*new;

	if (!current)
		return (NULL);
	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_command));
	new->pos = pos;
	new->tokens = get_token(current);
	new->infiles = create_infile_list(data, new->tokens);
	new->outfiles = create_outfiles_list(new->tokens);
	new->args_lst = create_args_list(new->tokens);
	new->args = tab_of_args(new->args_lst);
	new->path = NULL;
	new->next = NULL;
	return (new);
}

/*Fonction qui renvoie le prochain pipe sous forme de token*/
static t_token	*gnp(t_token *current)
{
	if (!current)
		return (NULL);
	while (current)
	{
		if (current->type == PIPE)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/*Fonction qui ajoute une commande a la liste des commandes*/
static void	add_command(t_command **lst, t_command *new)
{
	t_command	*cmd;

	if (!(*lst))
		*lst = new;
	else
	{
		cmd = *lst;
		while (cmd->next)
			cmd = cmd->next;
		cmd->next = new;
	}
}

int	parse_command(t_data *data)
{
	t_token		*current;
	t_command	*new;

	current = data->tokens;
	data->commands = NULL;
	data->cmd_nbr = 0;
	while (current)
	{
		if (current->type != PIPE)
		{
			new = init_new_command(data, current, data->cmd_nbr);
			if (!new)
				return (free_commands_list(&data->commands), FAIL);
			data->cmd_nbr++;
			add_command(&data->commands, new);
			current = gnp(current);
			if (!current)
				break ;
		}
		current = current->next;
	}
	return (SUCCESS);
}
