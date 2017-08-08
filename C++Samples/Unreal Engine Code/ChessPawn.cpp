// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMagicGameRawCPP.h"
#include "ChessPawn.h"

AChessPawn::AChessPawn()
{
	bIsFirstMove = true;
	PieceMesh->SetStaticMesh(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("StaticMesh'/Game/Meshes/Pawn.Pawn'"))));
}

void AChessPawn::BeginPlay(void)
{
	Super::BeginPlay();
	bIsFirstMove = true;
}

void AChessPawn::Move(EChessLocation ChessLocation)
{
	bIsFirstMove = false;
	Super::Move(ChessLocation);
}
//Y index is the forward backward index
AChessSquare* AChessPawn::GetSquareAhead(FIntVector CurrentArrayStyleLocation)
{
	int32 ForwardDirection = TeamType == EChessTeam::White ? 1 : -1;
	AChessSquare* FoundSquare = ChessBoard->GetSquare(CurrentArrayStyleLocation.X, CurrentArrayStyleLocation.Y + ForwardDirection);
	return FoundSquare;
}

//Special Pawn move that can only be executed on it's first turn to move ahead two spaces
AChessSquare* AChessPawn::GetSquareAheadSpecial(FIntVector CurrentArrayStyleLocation)
{
	int32 ForwardDirection = TeamType == EChessTeam::White ? 1 : -1;
	AChessSquare* FoundSquare = ChessBoard->GetSquare(CurrentArrayStyleLocation.X, CurrentArrayStyleLocation.Y + ForwardDirection*2);
	return FoundSquare;
}

//X index is the left and right index
AChessSquare* AChessPawn::GetSquareAheadToLeft(FIntVector CurrentArrayStyleLocation)
{
	int32 ForwardDirection = TeamType == EChessTeam::White ? 1 : -1;
	AChessSquare* FoundSquare = ChessBoard->GetSquare(CurrentArrayStyleLocation.X+1, CurrentArrayStyleLocation.Y + ForwardDirection);
	return FoundSquare;
}

//X index is the left and right index
AChessSquare* AChessPawn::GetSquareAheadToRight(FIntVector CurrentArrayStyleLocation)
{
	int32 ForwardDirection = TeamType == EChessTeam::White ? 1 : -1;
	AChessSquare* FoundSquare = ChessBoard->GetSquare(CurrentArrayStyleLocation.X-1, CurrentArrayStyleLocation.Y + ForwardDirection);
	return FoundSquare;
}
bool AChessPawn::IsAnyMoveAvailable(void)
{
	FIntVector ArrayLocation = ChessBoard->FindSquare(CurrentChessLocation)->GetArrayLocation();
	//Is the move even spatially possible.
	bool bIsForwardPossible = IsForwardAvailable(ArrayLocation.Y);
	if (!bIsForwardPossible)
		return bIsForwardPossible;
	//if left is possible check for kill in that square
	bool bIsLeftPossible = IsLeftAvailable(ArrayLocation.X);
	if (bIsLeftPossible)
		bIsLeftPossible = IsKillAvailable(GetSquareAheadToLeft(ArrayLocation)->SquareLocation);

	//if right is possible check for block and combine possiblities with previous possibilities
	bool bIsRightPossible = IsRightAvailable(ArrayLocation.X);
	if (bIsRightPossible)
		bIsRightPossible = IsKillAvailable(GetSquareAheadToRight(ArrayLocation)->SquareLocation);

	//since forward is available check if blocked and combine with previous checks
	bool AnyMovePossible = !IsSquareBlocked(GetSquareAhead(ArrayLocation)->SquareLocation) || bIsLeftPossible || bIsRightPossible;
	return AnyMovePossible;
}
//A Pawn can move in one of three ways, empty forward space, or enemy occupied diagnol space
TArray<EChessLocation> AChessPawn::GetAvailableMoves(void)
{
	//TArray<EChessLocation> AvailableMoves = Super::GetAvailableMoves();
	TArray<EChessLocation> AvailableMoves = TArray<EChessLocation>();
	FIntVector ArrayLocation = ChessBoard->FindSquare(CurrentChessLocation)->GetArrayLocation();

	//Disgusting I know...
	if (IsForwardAvailable(ArrayLocation.Y + GetForwardDirection()) && bIsFirstMove)
	{
		EChessLocation SpecialForwardMove = GetSquareAheadSpecial(ArrayLocation)->SquareLocation;
		if (!IsSquareBlocked(SpecialForwardMove))
		{
			AvailableMoves.Add(SpecialForwardMove);
		}
	}
	if (IsForwardAvailable(ArrayLocation.Y))
	{
		//Pawn can move forward?
		EChessLocation ForwardMove = GetSquareAhead(ArrayLocation)->SquareLocation;
		if (!IsSquareBlocked(ForwardMove))
		{
			AvailableMoves.Add(ForwardMove);
		}
	}
	if (IsRightAvailable(ArrayLocation.X) && IsForwardAvailable(ArrayLocation.Y))
	{
		//Pawn can move forward and right only if kill is available
		EChessLocation RightDiagonal = GetSquareAheadToRight(ArrayLocation)->SquareLocation;
		if (IsKillAvailable(RightDiagonal))
		{
			AvailableMoves.Add(RightDiagonal);
		}
	}
	if (IsLeftAvailable(ArrayLocation.X) && IsForwardAvailable(ArrayLocation.Y))
	{
		//Pawn can move forward and left only if kill is available
		EChessLocation LeftDiagonal = GetSquareAheadToLeft(ArrayLocation)->SquareLocation;
		if (IsKillAvailable(LeftDiagonal))
		{
			AvailableMoves.Add(LeftDiagonal);
		}
	}

	return AvailableMoves;
}
