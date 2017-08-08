// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChessPiece.h"
#include "ChessPawn.generated.h"

/**
 * 
 */
UCLASS()
class THEMAGICGAMERAWCPP_API AChessPawn : public AChessPiece
{
	GENERATED_BODY()
	public:
		AChessPawn();
		//Special Pawn Only property to use double forward move 
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Chess Piece Properties")
		bool bIsFirstMove;

		virtual void BeginPlay() override;
		virtual TArray<EChessLocation> GetAvailableMoves() override;
		virtual bool IsAnyMoveAvailable() override;
		//Pawn addition to move is that it sets first move to false, can special move only the first time it moves.
		virtual void Move(EChessLocation MoveLocation) override;
		AChessSquare* GetSquareAhead(FIntVector CurrentArrayStyleLocation);
		AChessSquare* GetSquareAheadSpecial(FIntVector CurrentArrayStyleLocation);
		AChessSquare* GetSquareAheadToLeft(FIntVector CurrentArrayStyleLocation);
		AChessSquare* GetSquareAheadToRight(FIntVector CurrentArrayStyleLocation);
	
	
	
};
