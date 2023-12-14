/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 14:30:46 by qtrinh        #+#    #+#                 */
/*   Updated: 2022/10/21 16:53:01 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

/* int	main(void)
{
    char    str;

    str = 'b';
    if (ft_isprint(str))
        printf("own functie: 1\n");
    else
        printf("own functie: 0\n");
    if (isprint(str))
        printf("OG functie: 1\n");
    else
        printf("OG functie: 0\n");
} */