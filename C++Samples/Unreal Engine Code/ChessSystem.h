// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ChessBoard.h"
#include "ChessPiece.h"
#include "ChessFactory.h"
#include "ChessPlayer.h"
#include "ChessSystem.generated.h"

UCLASS()
class THEMAGICGAMERAWCPP_API AChessSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChessSystem();

	UFUNCTION(BlueprintCallable, Category = "Chess Functions")
	void FlipTable();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Game Properties")
	FVector GameLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Game Properties")
	FVector GameScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Game Properties")
	float TurnTime;

	float ElapsedTimeSinceLastTurn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Game Properties")
	bool bIsAutoPlaying;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Game Properties")
	bool bNeedsRegeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chess Components")
	AChessBoard* ChessBoard;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chess Components")
	TArray<AChessPiece*> ChessPieces;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chess Components")
	bool bIsWhiteTurn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Components")
	AChessPlayer* WhitePlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Components")
	AChessPlayer* BlackPlayer;

	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void LoadChessPieces();
	
	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void LoadChessBoard();

	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void AssociateComponents();

	UFUNCTION(BlueprintCallable, Category = "Chess Gameplay")
	void MovePiece();

	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void LoadChessPlayers();

	UFUNCTION(BlueprintCallable, Category = "Chess Gameplay")
	void TakeTurn();

	UFUNCTION(BlueprintCallable, Category = "Chess Gameplay")
	bool IsPromotionAvailable();

	UFUNCTION(BlueprintCallable, Category = "Chess Utilities")
	void RegeneratePieces();

	UFUNCTION(BlueprintCallable, Category = "Chess Utilities")
	void RequestRegeneration();

	int32 MaintainList();
	
	uint8 MoveDebuggerX;
	uint8 MoveDebuggerY;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	AChessFactory* ChessFactory;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
