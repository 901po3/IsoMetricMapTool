#pragma once
#include"Object.h"

#define SavePos			0
#define LoadPos			397

#define SaveScreenWidth	382
#define SaveScreenHeight	396

#define SlotWidth			328
#define SlotHeight		96

#define FirstSlotPosX		30
#define FirstSlotPosy		65

#define SlotYGap			14

#define MenuOriginPosX		20
#define MenuOriginPosY		140

#define MakeMapOriginPosX	630
#define MakeMapOriginPosY	200

#define None				0
#define FirstSlotChoosen	397
#define SecondSlotChoosen	803
#define ThirdSlotChoosen	1202

class SaveLoadSlot : public Object
{
private:
	int SaveOrLoadPos;
	int CurrentChoosenSlotPos;
	CGPoint OriginPos;
	bool SaveSlotOne;
	bool SaveSlotTwo;
	bool SaveSlotThree;
	bool LoadSlotOne;
	bool LoadSlotTwo;
	bool LoadSlotThree;
public:
	SaveLoadSlot();
	virtual void dealloc();

	void SetSaveOrLoadPos(int _ypos) { SaveOrLoadPos = _ypos;}
	int GetSaveOrLoadPos() {return SaveOrLoadPos;}
	void SetOriginPos(CGPoint pos) { OriginPos = pos;}
	void MarkChoosenSlot(int mark)	{ CurrentChoosenSlotPos = mark;}
	CGPoint GetOriginPos() {return OriginPos;}

	void SetSaveSlotOne(bool _save) { SaveSlotOne = _save;}
	void SetSaveSlotTwo(bool _save) { SaveSlotTwo = _save;}
	void SetSaveSlotThree(bool _save) { SaveSlotThree = _save;}
	bool GetSaveSlotOne() {return SaveSlotOne;}
	bool GetSaveSlotTwo() {return SaveSlotTwo;}
	bool GetSaveSlotThree() {return SaveSlotThree;}
	
	void SetLoadSlotOne(bool _load) {  LoadSlotOne = _load;}
	void SetLoadSlotTwo(bool _load) { LoadSlotTwo = _load;}
	void SetLoadSlotThree(bool _load) { LoadSlotThree = _load;}
	bool GetLoadSlotOne() {return LoadSlotOne;}
	bool GetLoadSlotTwo() {return LoadSlotTwo;}
	bool GetLoadSlotThree() {return LoadSlotThree;}

	static SaveLoadSlot *create()
	{
		SaveLoadSlot *slot = new SaveLoadSlot();
		return slot;
	}
	void render();
	void update(float dt) {}
};