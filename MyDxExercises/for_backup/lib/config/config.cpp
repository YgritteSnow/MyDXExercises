#include "lib/config/config.h"

static const int g_i_screenPixelWidth = 400;
static const int g_i_screenPixelHeight = 400;

int N_Config::F_GetScreenPixelWidth()
{
	return g_i_screenPixelWidth;
}

int N_Config::F_GetScreenPixelHeight()
{
	return g_i_screenPixelHeight;
}