// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ChessBoard.h"
#include "ChessPiece.generated.h"

UENUM(BlueprintType)
enum class EChessTeam : uint8
{
	White,
	Black
};



UCLASS()
class THEMAGICGAMERAWCPP_API AChessPiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChessPiece();

	//Team that the chess piece is on
	UPROPERTY(BlueprintReadWrite, Category = "Chess Properties")
	EChessTeam TeamType;

	UPROPERTY(BlueprintReadWrite, Category = "Chess Properties")
	EChessLocation OriginChessLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Chess Properties")
	EChessLocation CurrentChessLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Chess Properties")
	bool bIsPieceDead;

	UPROPERTY(BlueprintReadWrite, Category = "Chess Properties")
	bool bIsMoving;

	UPROPERTY(BlueprintReadWrite, Category = "Chess Properties")
	bool bIsAtHeight;

	//UPROPERTY(BlueprintReadWrite, Category = "Chess Properties")
	//bool bIsAboveDestination;

	UPROPERTY(BlueprintReadWrite, Category = "Chess Properties")
	FVector Destination;

	UPROPERTY(BlueprintReadWrite, Category = "Chess Properties")
	FVector AbovePoint;

	UPROPERTY(BlueprintReadWrite, Category = "Chess Properties")
	FVector HeadingVector;

	UPROPERTY(BlueprintReadWrite, Category = "Chess Properties")
	FTransform OriginalTransform;

	//Call to move from current square to new one using chess-style location schema
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	virtual void Move(EChessLocation ChessLocation);

	//Call to move from current square to new one using array-style schema
	//UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	virtual void Move(uint8 XLocation, uint8 YLocation);

	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	FVector GetHeading(FVector Target);

	FVector LastHeading;
	FVector NewHeading;

	bool IsPassed(FVector LatestHeading);

	//Called upon to remove piece from game
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	virtual void Die();

	//Speed with which the piece moves through 3d space.
	UPROPERTY(BlueprintReadWrite, Category = "Chess Properties")
	float MovementSpeed;

	//Called to add piece to game
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	virtual void JoinBoard(AChessBoard* Board);

	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	void Reset();

	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	virtual TArray<EChessLocation> GetAvailableMoves();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Display")
	UStaticMeshComponent* PieceMesh;

	AChessBoard* ChessBoard;

	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	virtual bool AttemptKill(EChessLocation PotentialKillLocation);

	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	virtual bool IsLeftAvailable(int32 XLocation);
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	virtual bool IsRightAvailable(int32 XLocation);
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	virtual bool IsForwardAvailable(int32 YLocation);
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	virtual bool IsBackwardAvailable(int32 YLocation);
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	virtual bool IsAnyMoveAvailable();
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	virtual bool IsSquareBlocked(EChessLocation ChessLocation);
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	virtual bool IsKillAvailable(EChessLocation ChessLocation);
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	int32 GetForwardDirection();
	
	//Cast for moves in a straight line forward and fill array with found moves, if any found return true else false
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	bool CastForMovesForward(TArray<EChessLocation> &AvailableMovesArray, const FIntVector FromLocation);

	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	bool CastForMovesBackward(TArray<EChessLocation> &AvailableMovesArray, const FIntVector FromLocation);

	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	bool CastForMovesLeft(TArray<EChessLocation> &AvailableMovesArray, const FIntVector FromLocation);
	
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	bool CastForMovesRight(TArray<EChessLocation> &AvailableMovesArray, const FIntVector FromLocation);
	
	//Cast for moves in a diagonal filling array with possible moves in all directions until blocked from each
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	bool CastForMovesAheadRight(TArray<EChessLocation> &AvailableMovesArray, const FIntVector FromLocation);
	
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	bool CastForMovesAheadLeft(TArray<EChessLocation> &AvailableMovesArray, const FIntVector FromLocation);

	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	bool CastForMovesBehindLeft(TArray<EChessLocation> &AvailableMovesArray, const FIntVector FromLocation);

	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	bool CastForMovesBehindRight(TArray<EChessLocation> &AvailableMovesArray, const FIntVector FromLocation);

	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	static int32 GetForwardLimit(EChessTeam ChessTeam);
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	static int32 GetBackwardLimit(EChessTeam ChessTeam);

	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	EChessLocation GetSquareAhead(const FIntVector &ArrayLocation);
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	EChessLocation GetSquareBehind(const FIntVector &ArrayLocation);
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	EChessLocation GetSquareLeft(const FIntVector &ArrayLocation);
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	EChessLocation GetSquareRight(const FIntVector &ArrayLocation);
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	EChessLocation GetSquareAheadLeft(const FIntVector &ArrayLocation);
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	EChessLocation GetSquareAheadRight(const FIntVector &ArrayLocation);
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	EChessLocation GetSquareBehindLeft(const FIntVector &ArrayLocation);
	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	EChessLocation GetSquareBehindRight(const FIntVector &ArrayLocation);

	UFUNCTION(BlueprintCallable, Category = "Chess Initialization")
	void SetChessScale(FVector NewScale);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
