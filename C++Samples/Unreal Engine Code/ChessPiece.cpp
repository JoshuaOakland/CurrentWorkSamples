// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMagicGameRawCPP.h"
#include "ChessPiece.h"


// Sets default values
AChessPiece::AChessPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MovementSpeed = 500.0f;
	PieceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chess Piece Mesh"));
	RootComponent = PieceMesh;
	bIsPieceDead = false;

}
//Check for any move possible
bool AChessPiece::IsAnyMoveAvailable(void)
{
	return true;
}

//Return legal moves available to this piece
TArray<EChessLocation> AChessPiece::GetAvailableMoves(void)
{
	TArray<EChessLocation> AvailableMoves;
	if (ChessBoard)
	{
		AvailableMoves = ChessBoard->GetAllPossibleChessBoardLocations();
		AvailableMoves.Remove(CurrentChessLocation);
	}
	AChessPiece* PotentialAlly = nullptr;
	for (EChessLocation ChessLocation : AvailableMoves)
	{
		PotentialAlly = ChessBoard->FindSquare(ChessLocation)->GetOccupyingPiece();
		if (PotentialAlly != nullptr)
		{
			AvailableMoves.Remove(PotentialAlly->CurrentChessLocation);
		}
	}
	return AvailableMoves;
}
//Checking if a piece is already here, if it is kill it. and return true
bool AChessPiece::AttemptKill(EChessLocation PotentialKillLocation)
{
	AChessPiece* VictimPiece = nullptr;
	if (ChessBoard)
		VictimPiece = ChessBoard->FindSquare(PotentialKillLocation)->GetOccupyingPiece();
	if (VictimPiece == nullptr)
		return false;
	VictimPiece->Die();
	return true;
}
bool AChessPiece::IsSquareBlocked(EChessLocation ChessLocation)
{
	AChessPiece* PotentialPiece = ChessBoard->FindSquare(ChessLocation)->GetOccupyingPiece();
	//If potential piece isn't nullptr check to make sure it is not same team as me
	if (PotentialPiece)
		return PotentialPiece->TeamType == TeamType;
	//If there is no piece there at all it isn't blocked either
	return false;
}
bool AChessPiece::IsKillAvailable(EChessLocation ChessLocation)
{
	AChessPiece* PotentialPiece = ChessBoard->FindSquare(ChessLocation)->GetOccupyingPiece();
	//If there is a piece and it is not on our team we can kill it! else return false no kill available
	if (PotentialPiece)
		return PotentialPiece->TeamType != TeamType;
	return false;
}
bool AChessPiece::IsLeftAvailable(int32 XLocation)
{
	return XLocation < 7;
}
bool AChessPiece::IsRightAvailable(int32 XLocation)
{
	return XLocation > 0;
}
bool AChessPiece::IsForwardAvailable(int32 YLocation)
{
	bool bCanMoveForward = TeamType == EChessTeam::White ? YLocation < 7 : YLocation > 0;
	return bCanMoveForward;
}
bool AChessPiece::IsBackwardAvailable(int32 YLocation)
{
	bool bCanMoveBackward = TeamType == EChessTeam::White ? YLocation > 0 : YLocation < 7;
	return bCanMoveBackward;
}
//Chess-Style movement schema, restricting possible move locations to a 8x8 board
void AChessPiece::Move(EChessLocation ChessLocation)
{
	if (bIsPieceDead)
		return;
	if(CurrentChessLocation != ChessLocation)
		AttemptKill(ChessLocation);
	ChessBoard->FindSquare(CurrentChessLocation)->ClearOccupyingPiece();
	bIsMoving = true;
	FVector CurrentLocation = GetActorLocation();
	Destination = ChessBoard->FindSquare(ChessLocation)->GetCenterOfSquare();
	AbovePoint = FVector(GetActorLocation());
	AbovePoint.Z += 1000.0f;
	float XValue = FMath::Abs(CurrentLocation.X - Destination.X);
	float YValue = FMath::Abs(CurrentLocation.Y - Destination.Y);
	float ZValue = FMath::Abs(CurrentLocation.Z - Destination.Z);
	XValue = CurrentLocation.X > Destination.X ? -XValue : XValue;
	YValue = CurrentLocation.Y > Destination.Y ? -YValue : YValue;
	ZValue = CurrentLocation.Z > Destination.Z ? -ZValue : ZValue;
	//HeadingVector = FVector(XValue / MovementSpeed, YValue / MovementSpeed, ZValue / MovementSpeed);
	float Timelimit = 6.0f;
	HeadingVector = FVector(XValue / Timelimit, YValue / Timelimit, ZValue / Timelimit);
	//SetActorLocation(ChessBoard->FindSquare(ChessLocation)->GetCenterOfSquare());
	CurrentChessLocation = ChessLocation;
	ChessBoard->FindSquare(CurrentChessLocation)->SetOccupyingPiece(this);
}
void AChessPiece::Move(uint8 XLocation, uint8 YLocation)
{
	Move(ChessBoard->GetSquare(XLocation, YLocation)->SquareLocation);
}
FVector AChessPiece::GetHeading(FVector Target)
{
	FVector CurrentLocation = GetActorLocation();
	float XValue = FMath::Abs(CurrentLocation.X - Destination.X);
	float YValue = FMath::Abs(CurrentLocation.Y - Destination.Y);
	float ZValue = FMath::Abs(CurrentLocation.Z - Destination.Z);
	XValue = CurrentLocation.X > Destination.X ? -XValue : XValue;
	YValue = CurrentLocation.Y > Destination.Y ? -YValue : YValue;
	ZValue = CurrentLocation.Z > Destination.Z ? -ZValue : ZValue;
	return(FVector(XValue, YValue, ZValue));
}

void AChessPiece::Reset(void)
{
	bIsPieceDead = false;
	bIsMoving = false;
	bIsAtHeight = false;
	PieceMesh->SetSimulatePhysics(false);
	SetActorTransform(OriginalTransform);
	Move(OriginChessLocation);
}

void AChessPiece::Die(void)
{
	PieceMesh->SetSimulatePhysics(true);
	bIsPieceDead = true;
}
int32 AChessPiece::GetForwardDirection(void)
{
	return TeamType == EChessTeam::White ? 1 : -1;
}
void AChessPiece::JoinBoard(AChessBoard* NewBoard)
{
	ChessBoard = NewBoard;
	FVector PieceLocation = GetActorLocation();
	for (AChessSquare* Square : ChessBoard->ChessSquares)
	{
		if (Square->GetCenterOfSquare() == PieceLocation)
		{
			OriginChessLocation = Square->SquareLocation;
			CurrentChessLocation = OriginChessLocation;
			Square->SetOccupyingPiece(this);
			return;
		}
	}
	UE_LOG(NecroLog,Fatal,TEXT("No Location Matches found for squares to set origin...Perhaps due to engine shifting spawn of pieces...Perhaps not."))
}

// Called when the game starts or when spawned
void AChessPiece::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(7, 7, 7));
	OriginalTransform = GetActorTransform();
	
}
void AChessPiece::SetChessScale(FVector NewScale)
{
	//15000/X = 7
	//100/X = 6
	const double CPXYScale = 1 / 2142;
	const double CPZScale = 1 / 14;

	SetActorScale3D(FVector(NewScale.X/2142, NewScale.Y/2142, NewScale.Z/14));
}

bool AChessPiece::IsPassed(FVector LatestHeading)
{
	LastHeading = NewHeading;
	NewHeading = LatestHeading;
	if (NewHeading.X < 0 && LastHeading.X < 0)// && NewHeading.Y < 0 && LastHeading.Y < 0)
	{
		return false;
	}
	else if (NewHeading.X > 0 && LastHeading.X > 0)// && NewHeading.Y > 0 && LastHeading.Y > 0)
	{
		return false;
	}
	return true;
}

// Called every frame
void AChessPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsMoving)
	{
		if (!bIsAtHeight)
		{
			AddActorWorldOffset(FVector(0, 0, MovementSpeed*DeltaTime));
			if (GetActorLocation().Z >= AbovePoint.Z)
			{
				bIsAtHeight = true;
			}
			//bIsAtHeight = GetActorLocation().Z >= AbovePoint.Z ? true : false;
		}
		else
		{
			//if (!IsPassed(GetHeading(Destination)))
			if(!FVector::PointsAreNear(GetActorLocation(),FVector(Destination.X, Destination.Y,GetActorLocation().Z),150))
			{
				AddActorWorldOffset(FVector(HeadingVector.X * DeltaTime, HeadingVector.Y * DeltaTime, 0));
			}
			else
			{
				if (GetActorLocation().Z > Destination.Z)
				{
					AddActorWorldOffset(FVector(0, 0, -MovementSpeed*DeltaTime));
				}
				else
				{
					SetActorLocation(Destination);
					bIsMoving = false;
					bIsAtHeight = false;
				}
			}
		}
	}
}

int32 AChessPiece::GetForwardLimit(EChessTeam ChessTeam)
{
	return ChessTeam == EChessTeam::White ? 8 : -1;
}

int32 AChessPiece::GetBackwardLimit(EChessTeam ChessTeam)
{
	return ChessTeam == EChessTeam::White ? 0 : 7;
}

//Cast in specified direction, adding spaces to array if it isn't null and returning true if any spaces are available
bool AChessPiece::CastForMovesForward(TArray<EChessLocation> &AvailableLocations, const FIntVector FromLocation)
{
	int32 ForwardDirection = GetForwardDirection();
	int32 ForwardLimit = GetForwardLimit(TeamType);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f * 5, FColor::Cyan, FString::Printf(TEXT("Casting for moves forward, from %d %d F-Direction is %d F-limit is %d"), FromLocation.X, FromLocation.Y, ForwardDirection, ForwardLimit));
	for (int32 i = FromLocation.Y+ForwardDirection; i != ForwardLimit; i+=ForwardDirection)
	{
//		GEngine->AddOnScreenDebugMessage(-1, 5.0f*5, FColor::Cyan, FString::Printf(TEXT("Iterating in forward direction start was %d i is now %d F-Limit is %d"), FromLocation.Y, i, ForwardLimit));
		EChessLocation SquareLocation = ChessBoard->GetSquare(FromLocation.X, i)->SquareLocation;
		if (!IsSquareBlocked(SquareLocation))
			AvailableLocations.Add(SquareLocation);
		else
			return i != FromLocation.Y;
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f * 5, FColor::Cyan, FString::Printf(TEXT("A Square was added")));
	}
	return true;
}

//Cast in specified direction, adding spaces to array if it isn't null and returning true if any spaces are available
bool AChessPiece::CastForMovesBackward(TArray<EChessLocation> &AvailableLocations, const FIntVector FromLocation)
{
	int32 BackwardDirection = GetForwardDirection()*-1;
	int32 BackwardLimit = GetBackwardLimit(TeamType);
	for (int32 i = FromLocation.Y + BackwardDirection; i != BackwardLimit; i += BackwardDirection)
	{
		EChessLocation SquareLocation = ChessBoard->GetSquare(FromLocation.X, i)->SquareLocation;
		if (!IsSquareBlocked(SquareLocation))
			AvailableLocations.Add(SquareLocation);
		else
			return i != FromLocation.Y;
	}
	return true;
}

//Cast in specified direction, adding spaces to array if it isn't null and returning true if any spaces are available
bool AChessPiece::CastForMovesLeft(TArray<EChessLocation> &AvailableLocations, const FIntVector FromLocation)
{
	const int32 LeftLimit = 8;
	for (int32 i = FromLocation.X + 1; i != LeftLimit; i ++)
	{
		EChessLocation SquareLocation = ChessBoard->GetSquare(i,FromLocation.Y)->SquareLocation;
		if (!IsSquareBlocked(SquareLocation))
			AvailableLocations.Add(SquareLocation);
		else
			return i != FromLocation.X;
	}
	return true;
}

//Cast in specified direction, adding spaces to array if it isn't null and returning true if any spaces are available
bool AChessPiece::CastForMovesRight(TArray<EChessLocation> &AvailableLocations, const FIntVector FromLocation)
{
	const int32 RightLimit = -1;
	for (int32 i = FromLocation.X - 1; i != RightLimit; i--)
	{
		EChessLocation SquareLocation = ChessBoard->GetSquare(i, FromLocation.Y)->SquareLocation;
		if (!IsSquareBlocked(SquareLocation))
			AvailableLocations.Add(SquareLocation);
		else
			return i != FromLocation.X;
	}
	return true;
}

//Cast in specified diagonal direction, adding spaces to array if it isn't null and returning true if any spaces are available
bool AChessPiece::CastForMovesAheadRight(TArray<EChessLocation> &AvailableLocations, const FIntVector FromLocation)
{
	const int32 ForwardDirection = GetForwardDirection();
	const int32 RightDirection = -1;
	const int32 RightLimit = -1;
	int32 ForwardLimit = GetForwardLimit(TeamType);
	int32 j = FromLocation.X + RightDirection;
	for (int32 i = FromLocation.Y + ForwardDirection; i != ForwardLimit; i += ForwardDirection)
	{
		if (j != RightLimit)
		{
			EChessLocation SquareLocation = ChessBoard->GetSquare(j, i)->SquareLocation;
			if (!IsSquareBlocked(SquareLocation))
				AvailableLocations.Add(SquareLocation);
			else
				return i != FromLocation.Y;
			j += RightDirection;
		}
	}
	return true;
}

//Cast in specified diagonal direction, adding spaces to array if it isn't null and returning true if any spaces are available
bool AChessPiece::CastForMovesAheadLeft(TArray<EChessLocation> &AvailableLocations, const FIntVector FromLocation)
{
	const int32 ForwardDirection = GetForwardDirection();
	const int32 LeftDirection = 1;
	const int32 LeftLimit = 8;
	int32 ForwardLimit = GetForwardLimit(TeamType);
	int32 j = FromLocation.X + LeftDirection;
	for (int32 i = FromLocation.Y + ForwardDirection; i != ForwardLimit; i += ForwardDirection)
	{
		if (j != LeftLimit)
		{
			EChessLocation SquareLocation = ChessBoard->GetSquare(j, i)->SquareLocation;
			if (!IsSquareBlocked(SquareLocation))
				AvailableLocations.Add(SquareLocation);
			else
				return i != FromLocation.Y;
			j += LeftDirection;
		}
	}
	return true;
}

//Cast in specified diagonal direction, adding spaces to array if it isn't null and returning true if any spaces are available
bool AChessPiece::CastForMovesBehindRight(TArray<EChessLocation> &AvailableLocations, const FIntVector FromLocation)
{
	const int32 BackwardDirection = GetForwardDirection()*-1;
	const int32 RightDirection = -1;
	const int32 RightLimit = -1;
	int32 BackwardLimit = GetBackwardLimit(TeamType);
	int32 j = FromLocation.X + RightDirection;
	for (int32 i = FromLocation.Y + BackwardDirection; i != BackwardLimit; i += BackwardDirection)
	{
		if (j != RightLimit)
		{
			EChessLocation SquareLocation = ChessBoard->GetSquare(j, i)->SquareLocation;
			if (!IsSquareBlocked(SquareLocation))
				AvailableLocations.Add(SquareLocation);
			else
				return i != FromLocation.Y;
			j += RightDirection;
		}
	}
	return true;
}

//Cast in specified diagonal direction, adding spaces to array if it isn't null and returning true if any spaces are available
bool AChessPiece::CastForMovesBehindLeft(TArray<EChessLocation> &AvailableLocations, const FIntVector FromLocation)
{
	const int32 BackwardDirection = GetForwardDirection()*-1;
	const int32 LeftDirection = 1;
	const int32 LeftLimit = 8;
	int32 BackwardLimit = GetBackwardLimit(TeamType);
	int32 j = FromLocation.X + LeftDirection;
	for (int32 i = FromLocation.Y + BackwardDirection; i != BackwardLimit; i += BackwardDirection)
	{
		if (j != LeftLimit)
		{
			EChessLocation SquareLocation = ChessBoard->GetSquare(j, i)->SquareLocation;
			if (!IsSquareBlocked(SquareLocation))
				AvailableLocations.Add(SquareLocation);
			else
				return i != FromLocation.Y;
			j += LeftDirection;
		}
	}
	return true;
}

EChessLocation AChessPiece::GetSquareAhead(const FIntVector &ArrayLocation)
{
	EChessLocation ReturnLocation = ChessBoard->GetSquare(ArrayLocation.X, ArrayLocation.Y + GetForwardDirection())->SquareLocation;
	return ReturnLocation;
}
EChessLocation AChessPiece::GetSquareBehind(const FIntVector &ArrayLocation)
{
	EChessLocation ReturnLocation = ChessBoard->GetSquare(ArrayLocation.X, ArrayLocation.Y + GetForwardDirection()*-1)->SquareLocation;
	return ReturnLocation;
}
EChessLocation AChessPiece::GetSquareLeft(const FIntVector &ArrayLocation)
{
	EChessLocation ReturnLocation = ChessBoard->GetSquare(ArrayLocation.X+1, ArrayLocation.Y)->SquareLocation;
	return ReturnLocation;
}
EChessLocation AChessPiece::GetSquareRight(const FIntVector &ArrayLocation)
{
	EChessLocation ReturnLocation = ChessBoard->GetSquare(ArrayLocation.X-1, ArrayLocation.Y)->SquareLocation;
	return ReturnLocation;
}
EChessLocation AChessPiece::GetSquareAheadLeft(const FIntVector &ArrayLocation)
{
	EChessLocation ReturnLocation = ChessBoard->GetSquare(ArrayLocation.X+1, ArrayLocation.Y + GetForwardDirection())->SquareLocation;
	return ReturnLocation;
}
EChessLocation AChessPiece::GetSquareAheadRight(const FIntVector &ArrayLocation)
{
	EChessLocation ReturnLocation = ChessBoard->GetSquare(ArrayLocation.X-1, ArrayLocation.Y + GetForwardDirection())->SquareLocation;
	return ReturnLocation;
}
EChessLocation AChessPiece::GetSquareBehindLeft(const FIntVector &ArrayLocation)
{
	EChessLocation ReturnLocation = ChessBoard->GetSquare(ArrayLocation.X+1, ArrayLocation.Y + GetForwardDirection()*-1)->SquareLocation;
	return ReturnLocation;
}
EChessLocation AChessPiece::GetSquareBehindRight(const FIntVector &ArrayLocation)
{
	EChessLocation ReturnLocation = ChessBoard->GetSquare(ArrayLocation.X-1, ArrayLocation.Y + GetForwardDirection()*-1)->SquareLocation;
	return ReturnLocation;
}