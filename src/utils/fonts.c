#include "../fb.h"
#include "primitives.h"
#include "../fonts/font8x8_basic.h"

void	write_char(uint32_t *buffer, size_t pos, char c, uint32_t color)
{
	if (c < 0 || c >= 128)	return ;
	for (uint8_t y = 0; y < 8; y++) {
		uint8_t	line = font8x8_basic[(int)c][y];
		for (uint8_t x = 0; x < 8; x++) {
			if (line & (1 << x))
				plot(buffer, POS(x + X(pos), y + Y(pos)), color);
		}
	}
}

void	write_str(uint32_t *buffer, size_t pos, char *str, uint32_t color)
{
	size_t	i = 0;

	while (str[i])
		write_char(buffer, POS(X(pos) + (8 * i), Y(pos)), str[i++], color);
}

void	write_unb(uint32_t *buffer, size_t pos, size_t nb, uint32_t color)
{
	size_t	nb_length = 0;

	for (int i = nb; i; i /= 10)
		nb_length++;

	for (int total_length = nb_length; nb_length; nb_length--) {
		write_char(buffer, POS(X(pos) - total_length * 8 + nb_length * 8, Y(pos)), nb % 10 + '0', color);
		nb /= 10;
	}
}

