
#include "../cub3d.h"

char	*deblank(char *input)
{
	char	*output;
	int		i;
	int		j;
	output = ft_calloc(sizeof(char), ft_strlen(input) + 1);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			output[j] = input[i];
		else
			j--;
		i++;
		j++;
	}
	return (output);
}
