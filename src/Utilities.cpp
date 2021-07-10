#include"Utilities.h"

bool operator==(const Position& lVal, const Position& rVal)
{
	if (lVal.col == rVal.col && lVal.row == rVal.row)
	{
		return true;
	}
	return false;
}