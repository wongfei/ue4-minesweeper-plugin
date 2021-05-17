#pragma once

#include "CoreMinimal.h"

enum class EMinefieldFlag
{
	None,
	PossibleMine,
	Unknown,
	_COUNT
};

enum class EDigResult
{
	DigSuccess,
	SapperWin,
	MinesWin,
	InvalidCell
};

struct MinefieldCell
{
	int Id = 0;
	int X = 0;
	int Y = 0;
	int NumAdjacentMines = 0;
	EMinefieldFlag Flag = EMinefieldFlag::None;
	bool IsMine;
	bool IsBlown;
	bool IsVisible;
};

class MinefieldState
{
public:
	MinefieldState();

	void Resize(int NumX, int NumY, int NumMines);
	EDigResult Dig(int X, int Y);
	void RevealMinefield();

	inline bool IsValid(int X, int Y) const { return ((X >= 0 && X < SizeX) && (Y >= 0 && Y < SizeY)); }
	inline const MinefieldCell& GetCell(int X, int Y) const { check(IsValid(X, Y)); return Minefield[Y * SizeX + X]; }

	inline bool IsMine(int X, int Y) const { return GetCell(X, Y).IsMine; }
	inline bool IsBlown(int X, int Y) const { return GetCell(X, Y).IsBlown; }
	inline bool IsVisible(int X, int Y) const { return GetCell(X, Y).IsVisible; }

	inline EMinefieldFlag GetFlag(int X, int Y) const { return GetCell(X, Y).Flag; }
	inline int GetAdjacentMineCount(int X, int Y) const { return GetCell(X, Y).NumAdjacentMines; }

	inline void SetFlag(int X, int Y, EMinefieldFlag Flag) { GetCellPriv(X, Y).Flag = Flag; }

private:
	void RevealRecursive(int X, int Y, bool Force = false);
	int ComputeAdjacentMineCount(int X, int Y) const;
	bool AllMinesFound() const;

	inline MinefieldCell& GetCellPriv(int X, int Y) { check(IsValid(X, Y)); return Minefield[Y * SizeX + X]; }
	
	TArray<MinefieldCell> Minefield;
	int SizeX = 0;
	int SizeY = 0;
};
