#pragma once

#include "graphics.hpp"

class	Console
{
	public:
		static const int kRows = 25, kColumns = 80;
		Console(PixelWriter &writer, const PixelColor &fore_color, const PixelColor &back_color);
		void	PutString(const char *s);
	private:
		void				Newline();
		PixelWriter			&writer_;
		const PixelColor	fore_color_, back_color_;
		char				buffer_[kRows][kColumns + 1];
		int					cursor_row_, cursor_column_;
};