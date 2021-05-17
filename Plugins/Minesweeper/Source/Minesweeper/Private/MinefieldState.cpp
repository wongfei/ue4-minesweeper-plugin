#include "MinefieldState.h"
#include "PluginShared.h"

MinefieldState::MinefieldState()
{
	Resize(8, 8, 10);
}

void MinefieldState::Resize(int NumX, int NumY, int NumMines)
{
	const int MineLimit = (int)((NumX * NumY) * 0.5f);
	if (NumMines < 1 || NumMines > MineLimit)
	{
		PLUGIN_LOG(Error, TEXT("Invalid NumMines=%d"), NumMines);
		NumMines = MineLimit;
	}

	SizeX = NumX;
	SizeY = NumY;
	Minefield.SetNum(NumX * NumY);

	// reset state
	for (int Y = 0; Y < NumY; ++Y)
	{
		for (int X = 0; X < NumX; ++X)
		{
			auto& Cell = GetCellPriv(X, Y);
			Cell.Id = Y * NumX + X;
			Cell.X = X;
			Cell.Y = Y;
			Cell.NumAdjacentMines = 0;
			Cell.Flag = EMinefieldFlag::None;
			Cell.IsMine = false;
			Cell.IsBlown = false;
			Cell.IsVisible = false;
		}
	}

	// generate mines
	for (int MineId = 0; MineId < NumMines; ++MineId)
	{
		for (int R = 0; R < 10; ++R) // lame, but simple
		{
			int X = rand() % SizeX;
			int Y = rand() % SizeY;

			if (IsMine(X, Y))
				continue;

			GetCellPriv(X, Y).IsMine = true;
			break;
		}
	}

	// count adjacent mines
	for (int Y = 0; Y < NumY; ++Y)
	{
		for (int X = 0; X < NumX; ++X)
		{
			GetCellPriv(X, Y).NumAdjacentMines = ComputeAdjacentMineCount(X, Y);
		}
	}
}

EDigResult MinefieldState::Dig(int X, int Y)
{
	if (!IsValid(X, Y))
		return EDigResult::InvalidCell;

	auto& Cell = GetCellPriv(X, Y);

	if (Cell.IsMine)
	{
		Cell.IsBlown = true;
		Cell.IsVisible = true;
		return EDigResult::MinesWin;
	}

	RevealRecursive(X, Y, true);

	const bool Done = AllMinesFound();
	if (Done)
		return EDigResult::SapperWin;

	return EDigResult::DigSuccess;
}

void MinefieldState::RevealRecursive(int X, int Y, bool Force)
{
	if (!IsValid(X, Y))
		return;

	auto& Cell = GetCellPriv(X, Y);

	if (Cell.IsVisible || Cell.IsMine)
		return;

	Cell.IsVisible = true;

	if (Cell.NumAdjacentMines == 0)
	{
		RevealRecursive(X - 1, Y - 1);
		RevealRecursive(X,     Y - 1);
		RevealRecursive(X + 1, Y - 1);

		RevealRecursive(X - 1, Y);
		RevealRecursive(X + 1, Y);

		RevealRecursive(X - 1, Y + 1);
		RevealRecursive(X,     Y + 1);
		RevealRecursive(X + 1, Y + 1);
	}
}

int MinefieldState::ComputeAdjacentMineCount(int X, int Y) const
{
	int Count = 0;

	#define COUNT_IMPL(PX, PY)\
		if (IsValid(PX, PY) && GetCell(PX, PY).IsMine) Count++;

	COUNT_IMPL(X - 1, Y - 1);
	COUNT_IMPL(X,     Y - 1);
	COUNT_IMPL(X + 1, Y - 1);

	COUNT_IMPL(X - 1, Y);
	COUNT_IMPL(X + 1, Y);

	COUNT_IMPL(X - 1, Y + 1);
	COUNT_IMPL(X,     Y + 1);
	COUNT_IMPL(X + 1, Y + 1);

	#undef COUNT_IMPL

	return Count;
}

bool MinefieldState::AllMinesFound() const
{
	int MineCount = 0;
	int DefusedCount = 0;

	for (int Y = 0; Y < SizeY; ++Y)
	{
		for (int X = 0; X < SizeX; ++X)
		{
			const auto& Cell = GetCell(X, Y);

			if (Cell.IsMine)
				MineCount++;

			if (Cell.IsVisible && !Cell.IsMine)
				DefusedCount++;
		}
	}

	return (MineCount + DefusedCount == SizeX * SizeY);
}

void MinefieldState::RevealMinefield()
{
	for (int Y = 0; Y < SizeY; ++Y)
	{
		for (int X = 0; X < SizeX; ++X)
		{
			GetCellPriv(X, Y).IsVisible = true;
		}
	}
}
