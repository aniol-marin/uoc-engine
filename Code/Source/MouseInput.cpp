#include "MouseInput.h"
#include "defines.h"

CMouseInput::CMouseInput(HWND hWnd) :
	//TO DO : Inicializar a cero la variable miembro m_MovementX
	m_MovementX{ 0 },
	//TO DO : Inicializar a cero la variable miembro m_MovementY
	m_MovementY{ 0 },
	//TO DO : Inicializar a cero la variable miembro m_MovementZ
	m_MovementZ{ 0 },
	//TO DO : Inicializar a false la variable miembro m_ButtonLeft
	m_ButtonLeft{ false },
	//TO DO : Inicializar a false la variable miembro m_ButtonMiddle
	m_ButtonMiddle{ false },
	//TO DO : Inicializar a false la variable miembro m_ButtonRight
	m_ButtonRight{ false },
	//TO DO : Inicializar a false la variable miembro m_PreviousButtonLeft
	m_PreviousButtonLeft{ false },
	//TO DO : Inicializar a false la variable miembro m_PreviousButtonMiddle
	m_PreviousButtonMiddle{ false },
	//TO DO : Inicializar a false la variable miembro m_PreviousButtonRight
	m_PreviousButtonRight{ false },
	m_Mouse{ NULL }
{
	//NOTA : Inicialización del device de ratón utilizando DirectInput8 de DirectX
	HRESULT l_HR;
	DWORD l_CoopFlags = 0;

	if (FAILED(l_HR = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_DI, NULL)))
		return;
	if (FAILED(l_HR = m_DI->CreateDevice(GUID_SysMouse, &m_Mouse, NULL)))
		return;
	if (FAILED(l_HR = m_Mouse->SetDataFormat(&c_dfDIMouse2)))
		return;
	if (FAILED(l_HR = m_Mouse->SetCooperativeLevel(hWnd, l_CoopFlags)))
		return;

	if (m_Mouse != NULL)
		m_Mouse->Acquire();
	else
		MessageBox(hWnd, L"Problem with de mouse input!", L"Mouse", MB_ICONERROR | MB_OK);
}

CMouseInput::~CMouseInput()
{
	//TO DO : Si la variable miembro m_Mouse es diferente de NULL llamar al mï¿½todo Unacquire de m_Mouse
	if (m_Mouse != NULL) {
		m_Mouse->Unacquire();
	}
	//TO DO : Destruye la variable miembro m_Mouse utilizando la macro CHECKED_RELEASE
	CHECKED_RELEASE(m_Mouse);
	//TO DO : Destruye la variable miembro m_DI utilizando la macro CHECKED_RELEASE
	CHECKED_RELEASE(m_DI);
}

bool CMouseInput::Update()
{
	DIMOUSESTATE2 l_DIMouseState;

	if (m_Mouse == NULL)
		return false;

	//TO DO : Inicializar a cero la memoria utilizando la funciï¿½n ZeroMemory la variable l_DIMouseState
	ZeroMemory(&l_DIMouseState, sizeof(DIMOUSESTATE2));

	//NOTA : El siguiente fragmento de código recoge el estado del ratón actual utilizando la función de DirectX GetDeviceState, a continuación comprueba si el ratón se ha desconectado; en caso de estar desconectado espera a que se vuelva a reconectar
	HRESULT l_HR = m_Mouse->GetDeviceState(sizeof(DIMOUSESTATE2), &l_DIMouseState);
	if (FAILED(l_HR))
	{
		l_HR = m_Mouse->Acquire();
		while (l_HR == DIERR_INPUTLOST)
			l_HR = m_Mouse->Acquire();
		return true;
	}

	//TO DO : Establecer en la variable miembro m_MovementX el valor de l_DIMouseState.lX
	//TO DO : Establecer en la variable miembro m_MovementY el valor de l_DIMouseState.lY
	//TO DO : Establecer en la variable miembro m_MovementZ el valor de l_DIMouseState.lZ
	m_MovementX = l_DIMouseState.lX;
	m_MovementY = l_DIMouseState.lY;
	m_MovementZ = l_DIMouseState.lZ;

	//TO DO : Establecer en la variable miembro m_PreviousButtonLeft el valor de m_ButtonLeft
	//TO DO : Establecer en la variable miembro m_PreviousButtonMiddle el valor de m_ButtonMiddle
	//TO DO : Establecer en la variable miembro m_PreviousButtonRight el valor de m_ButtonRight
	m_PreviousButtonLeft = m_ButtonLeft;
	m_PreviousButtonMiddle = m_ButtonMiddle;
	m_PreviousButtonRight = m_ButtonRight;

	//NOTA : Asigna en la variable miembro m_ButtonRight si el botón derecho del ratón con Id 1 está pulsado

	m_ButtonRight = (l_DIMouseState.rgbButtons[1] & 0x80) != 0;
	//TO DO : Establecer en la variable miembro m_ButtonLeft si el botï¿½n izquierdo del ratï¿½n con Id 0 estï¿½ pulsado. Basarse en cï¿½mo asigna el valor a la variable miembro m_ButtonRight
	m_ButtonLeft = (l_DIMouseState.rgbButtons[0] & 0x80) != 0;
	//TO DO : Establecer en la variable miembro m_ButtonMiddle si el botï¿½n izquierdo del ratï¿½n con Id 2 estï¿½ pulsado. Basarse en cï¿½mo asigna el valor a la variable miembro m_ButtonRight
	m_ButtonMiddle = (l_DIMouseState.rgbButtons[2] & 0x80) != 0;

	return true;
}

int CMouseInput::GetMovementX() const
{
	//TO DO : Devolver el valor de m_MovementX
	return m_MovementX;
}

int CMouseInput::GetMovementY() const
{
	//TO DO : Devolver el valor de m_MovementY
	return m_MovementY;
}

int CMouseInput::GetMovementZ() const
{
	//TO DO : Devolver el valor de m_MovementZ
	return m_MovementZ;
}

//TO DO : Devolver el valor de m_ButtonRight
bool CMouseInput::IsRightButtonPressed() const
{
	//TO DO : Devolver el valor de m_ButtonRight
	return m_ButtonRight;
}

bool CMouseInput::IsLeftButtonPressed() const
{
	//TO DO : Devolver el valor de m_ButtonLeft
	return m_ButtonLeft;
}

bool CMouseInput::IsMiddleButtonPressed() const
{
	//TO DO : Devolver el valor de m_ButtonMiddle
	return m_ButtonMiddle;
}

bool CMouseInput::LeftButtonBecomesPressed() const
{
	//TO DO : Devolver verdadero si el botï¿½n izquierdo del ratï¿½n estï¿½ pulsado actualmente y no estaba pulsado anteriormente utilizando las variables miembro m_ButtonLeft y m_PreviousButtonLeft
	return m_ButtonLeft && !m_PreviousButtonLeft;
}

bool CMouseInput::MiddleButtonBecomesPressed() const
{
	//TO DO : Devolver verdadero si el botï¿½n intermedio del ratï¿½n estï¿½ pulsado actualmente y no estaba pulsado anteriormente utilizando las variables miembro m_ButtonMiddle y m_PreviousButtonMiddle
	return m_ButtonMiddle && !m_PreviousButtonMiddle;
}

bool CMouseInput::RightButtonBecomesPressed() const
{
	//TO DO : Devolver verdadero si el botï¿½n derecho del ratï¿½n estï¿½ pulsado actualmente y no estaba pulsado anteriormente utilizando las variables miembro m_ButtonRight y m_PreviousButtonRight
	return m_ButtonRight && !m_PreviousButtonRight;
}

bool CMouseInput::LeftButtonBecomesReleased() const
{
	//TO DO : Devolver verdadero si el botï¿½n izquierdo del ratï¿½n no estï¿½ pulsado actualmente y estaba pulsado anteriormente utilizando las variables miembro m_ButtonLeft y m_PreviousButtonLeft
	return !m_ButtonLeft && m_PreviousButtonLeft;
}

bool CMouseInput::MiddleButtonBecomesReleased() const
{
	//TO DO : Devolver verdadero si el botï¿½n intermedio del ratï¿½n no estï¿½ pulsado actualmente y estaba pulsado anteriormente utilizando las variables miembro m_ButtonMiddle y m_PreviousButtonMiddle
	return !m_ButtonMiddle && m_PreviousButtonMiddle;
}

bool CMouseInput::RightButtonBecomesReleased() const
{
	//TO DO : Devolver verdadero si el botï¿½n derecho del ratï¿½n no estï¿½ pulsado actualmente y estaba pulsado anteriormente utilizando las variables miembro m_ButtonRight y m_PreviousButtonRight
	return !m_ButtonRight && m_PreviousButtonRight;
}