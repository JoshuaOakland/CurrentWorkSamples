#pragma once
class Gatherer
{
	enum class GatherLimitation
	{
		TimeLimit,
		ItemLimit,
		CollectorLimit,
		DelayLimit,
		SignalLimit
	};

	typedef struct
	{
		float TimeLimit;
		float DelayLimit;
		unsigned int ItemLimit;
		unsigned int CollectorLimit;
		bool SignalLimit;
	} GatherLimitationInformation;
/*	typedef struct
	{
		unsigned int NumberOfItems;
	} ItemEnumeration;
*/

public:
	Gatherer();

	void setLimitations(GatherLimitationInformation* gatheringLimitations);
	void setLimitations(float TimeLimit, float DelayLimit, unsigned int ItemLimit, unsigned int CollectorLimit, bool SignalLimit);
	
	void setTimeLimit(float TimeLimit);
	void setDelayLimit(float DelayLimit);
	void setItemLimit(unsigned int ItemLimit);
	void setCollectorLimit(unsigned int CollectorLimit);
	void setSignalLimit(bool SignalLimit);

	void beginCollecting();

	GatherLimitationInformation* getLimitations();
	GatherLimitationInformation* GLI;
	~Gatherer();
private:
	unsigned int itemsToGather;
	unsigned int collectorsToUse;
	//Search for items and enumerate them
	virtual void searchForItems() = 0;
	//Plan on how best to collect the items identified within the enumeration
	virtual void strategizeCollection() = 0;
	//dispatch collectors with individual targets
	virtual void collectItems() = 0;
	//collector task, each collector will do this to collect the target.
	virtual void collectionTask() = 0;
};

