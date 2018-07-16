#include "moveTypes.h"

CMoveTypes* CMoveTypes::m_pMoveTypes = nullptr;

CMoveTypes* CMoveTypes::GetInstance()
{
	if (nullptr == m_pMoveTypes)
	{
		m_pMoveTypes = new CMoveTypes();
	}
	return(m_pMoveTypes);
}

void CMoveTypes::Update(MoveType _moveType, int _iMovementOption, float& _fX, float& _fY, float& _fZ)
{
	switch (_moveType)
	{
	case Translate:
	{
		switch (_iMovementOption)
		{
		case 1:
		{
			TranslateTypeOne(_fX, _fY, _fZ);
			break;
		}
		//For case 0, do nothing, so it also ends here
		default: break;
		}
		break;
	}
	case Rotate:
	{
		switch (_iMovementOption)
		{
		case 1:
		{
			RotateTypeOne(_fX, _fY, _fZ);
			break;
		}
		default: break;
		}
		break;
	}
	case Scale:
	{
		switch (_iMovementOption)
		{
		case 1:
		{
			ScaleTypeOne(_fX, _fY, _fZ);
			break;
		}
		default: break;
		}
		break;
	}
	default: break;
	}
}

void CMoveTypes::DeleteMoveTypes()
{
	delete m_pMoveTypes;
	m_pMoveTypes = 0;
}

void CMoveTypes::TranslateTypeOne(float& _fTranslateX, float& _fTranslateY, float& _fTranslateZ)
{
	//Add code for what this movement type will do on every update
}
void CMoveTypes::RotateTypeOne(float& _fRotateX, float& _fRotateY, float& _fRotateZ)
{
	//Add code for what this movement type will do on every update
}
void CMoveTypes::ScaleTypeOne(float& _fScaleX, float& _fScaleY, float& _fScaleZ)
{
	//Add code for what this movement type will do on every update
	if (1.0f == _fScaleX)
	{
		_fScaleX = 0.85f;
		_fScaleY = 0.85f;
		_fScaleZ = 0.85f;
	}
	else
	{
		_fScaleX = 1.0f;
		_fScaleY = 1.0f;
		_fScaleZ = 1.0f;
	}
}