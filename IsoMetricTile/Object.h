#pragma once
#include"Header.h"

class Object 
{
protected:
	CGPoint	m_Position;
	CGPoint	m_SrcSize;
	CGPoint	m_OffSet;
	bool		m_Active;
	HBITMAP	m_HResource;
	CGPoint	IsoPos;
	//모든 오브젝트의 위치를 표기.. 꼭 타일에만 관련된게 아님
	int		TileHeight;
	int		TileXth;
	int		TileYth;
	int		NumberTag;
	bool		Made;

public:
	Object();
	virtual void dealloc() {}

	void SetPosition(CGPoint pos) {m_Position = pos;}
	CGPoint GetPosition() {return m_Position;}
	void SetSrcSize(CGPoint sz) {m_SrcSize = sz;}
	CGPoint GetSrcSize() {return m_SrcSize;}
	void SetOffSet(CGPoint offset) { m_OffSet = offset;}
	CGPoint GetOffSet() {return m_OffSet;}
	void SetActive(bool active) { m_Active = active;}
	bool GetActive() {return m_Active;}
	void SetResource(HBITMAP resource) { m_HResource = resource;}
	HBITMAP GetResource() {return m_HResource;}
	void SetIsoPos(CGPoint Ipt) { IsoPos = Ipt;}
	CGPoint GetIsoPos() { return IsoPos;}
	void SetMade(bool _made) {Made = _made;}
	bool GetMade() {return Made;}

	virtual void render() {}
	virtual void update(float dt) {}
	
	//tile
	virtual void ChangeTile(TileStruct type) {}
	virtual void SetTileHeight(int h) {TileHeight = h;}
	virtual void SetTileXth(int x)	{TileXth = x;}
	virtual void SetTileYth(int y)	{TileYth = y;}
	virtual int	GetTileHeight() {return TileHeight;}
	virtual int  GetTileXth() {return TileXth;}
	virtual int	GetTileYth() {return TileYth;}
	virtual void SetNumberTag(int n) { NumberTag = n;}
	virtual int  GetNumberTag() {return NumberTag;}
};