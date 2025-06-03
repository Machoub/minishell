/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:01:30 by machouba          #+#    #+#             */
/*   Updated: 2024/09/02 18:00:05 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*ft_init_token(char *str, int type, int i, bool exp_flag)
/*Cree et initialise un nouveau token*/
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = str;
	new->next = NULL;
	new->pos = i;
	new->expand_flag = exp_flag;
	new->type_error = -1;
	new->flag_error = 0;
	new->pipe_flag = 0;
	new->infile_flag = 0;
	new->outfile_flag = 0;
	new->heredoc = NULL;
	new->refered_flag = 0;
	return (new);
}

/*parsing de la str en input*/

static int	get_size_of_token(char *input)
{
	int	token_type;
	int	i;

	if (!input)
		return (FAIL);
	token_type = gettype(input);
	if (token_type == HEREDOC || token_type == APPEND)
		return (SKIP);
	if (token_type == PIPE || token_type == RT || token_type == LT)
		return (SUCCESS);
	i = 0;
	while (input[i] && !is_space(input[i]) && !ft_isop(&input[i])
		&& input[i] != '|' && input[i] != '<' && input[i] != '>')
	{
		if (ft_isquote(input[i]) && input[i + 1])
			i += ft_strchr(&input[i + 1], input[i]) - &input[i] + 1;
		else
			i++;
	}
	return (i);
}

/*chopper (str) le input*/

static char	*get_str(char *input)
{
	char	*str;
	int		len;

	len = get_size_of_token(input);
	if (len == FAIL)
		return (NULL);
	str = ft_strndup(input, len);
	if (!str)
		return (NULL);
	return (str);
}

void	addlast_token(t_token **token_lst, t_token *new)
/*ajouter un token a la liste chinee*/
{
	t_token	*lst;

	if (!new)
		return ;
	if (*token_lst == NULL)
		*token_lst = new;
	else
	{
		lst = *token_lst;
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new;
	}
}

/*Remplis la liste de tokens*/

t_token	*ft_tokenization(char *input)
{
	t_token	*token;
	t_token	*new;
	int		i;
	char	*str;

	i = 0;
	token = NULL;
	while (*input)
	{
		if (is_space(*input) == TRUE)
			input++;
		else
		{
			str = get_str(input);
			if (!str)
				return (free_token(&token), NULL);
			new = ft_init_token(str, gettype(str), i, true);
			if (!new)
				return (free(str), free_token(&token), NULL);
			addlast_token(&token, new);
			input += ft_strlen(str);
			i++;
		}
	}
	return (token);
}
