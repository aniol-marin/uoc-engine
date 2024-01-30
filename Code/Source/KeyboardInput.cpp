#include "KeyboardInput.h"
#include "defines.h"

CKeyboardInput::CKeyboardInput(HWND hWnd)
{
	//TO DO : Inicializar a cero la memoria utilizando la funci�n ZeroMemory la variable miembro m_Diks
	//TO DO : Inicializar a cero la memoria utilizando la funci�n ZeroMemory la variable miembro m_PreviousDiks

	//NOTA : Inicializaci�n del device de teclado utilizando DirectInput8 de DirectX

	HRESULT l_HR;
    DWORD l_CoopFlags=DISCL_NONEXCLUSIVE | DISCL_FOREGROUND;
   
    if(FAILED(l_HR=DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_DI, NULL ) ) )
        return;
    
	if(FAILED(l_HR=m_DI->CreateDevice(GUID_SysKeyboard, &m_Keyboard, NULL)))
        return;
    
	if(FAILED(l_HR=m_Keyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
        return;
    
    l_HR=m_Keyboard->SetCooperativeLevel(hWnd, l_CoopFlags);
 
    if(FAILED(l_HR))
        return;

	//TO DO : Llamar al m�todo Acquire de la variable miembro m_Keyboard
}

CKeyboardInput::~CKeyboardInput()
{
	//TO DO : Si la variable miembro m_Keyboard es diferente de NULL llamar al m�todo Unacquire de m_Keyboard
	//TO DO : Destruye la variable miembro m_Keyboard utilizando la macro CHECKED_RELEASE
	//TO DO : Destruye la variable miembro m_DI utilizando la macro CHECKED_RELEASE
}

bool CKeyboardInput::Update()
{
	HRESULT l_HR;
	
    if(NULL==m_Keyboard)
        return false;
    
	//TO DO : Copiar la variable miembro m_Diks en m_PreviousDiks utilizando la funci�n memcpy
	//TO DO : Inicializar a cero la memoria utilizando la funci�n ZeroMemory la variable miembro m_Diks
	//NOTA : El siguiente fragmento de c�digo recoge el estado del teclado actual utilizando la funci�n de DirectX GetDeviceState, a continuaci�n comprueba si el teclado se ha desconectado; en caso de estar desconectado espera a que se vuelva a reconectar
    l_HR=m_Keyboard->GetDeviceState(sizeof(m_Diks), (LPVOID)&m_Diks);
    if(FAILED(l_HR)) 
    {
        l_HR=m_Keyboard->Acquire();
        while(l_HR==DIERR_INPUTLOST)
            l_HR=m_Keyboard->Acquire();

        return true;
    }
    return true;
}

bool CKeyboardInput::IsKeyPressed(int KeyCode)
{
	//NOTA : Comprobaci�n si la tecla con KeyCode est� pulsada
	return (m_Diks[KeyCode]&0x80)!=0;
}

bool CKeyboardInput::KeyBecomesPressed(int KeyCode)
{
	//TO DO : Devolver verdadero si la tecla KeyCode est� pulsada actualmente y la tecla KeyCode no estaba pulsada previamente, basarse en el m�todo IsKeyPressed. Para comprobar el estado anterior del teclado utilizar la variable miembro m_PreviousDiks
}

bool CKeyboardInput::KeyBecomesReleased(int KeyCode)
{
	//TO DO : Devolver verdadero si la tecla KeyCode no est� pulsada actualmente y la tecla KeyCode estaba pulsada previamente, basarse en el m�todo IsKeyPressed. Para comprobar el estado anterior del teclado utilizar la variable miembro m_PreviousDiks
}
