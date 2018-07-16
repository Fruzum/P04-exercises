#pragma once

#ifndef __MOVETYPE_H__
#define __MOVETYPE_H__

enum MoveType
{
	Translate,
	Rotate,
	Scale
};

class CMoveTypes
{
public:
	static CMoveTypes* GetInstance();

	void Update(MoveType _moveType, int _iMovementOption, float& _fX, float& _fY, float& _fZ);

	void DeleteMoveTypes();

protected:
	CMoveTypes() {};
	~CMoveTypes() {};

private:
	static CMoveTypes* m_pMoveTypes;


	CMoveTypes(CMoveTypes const&);
	CMoveTypes& operator=(CMoveTypes const&);

	void TranslateTypeOne(float& _fTranslateX, float& _fTranslateY, float& _fTranslateZ);
	void ScaleTypeOne(float& _fScaleX, float& _fScaleY, float& _fScaleZ);
	void RotateTypeOne(float& _fRotateX, float& _fRotateY, float& _fRotateZ);
};

#endif // __MOVETYPE_H__