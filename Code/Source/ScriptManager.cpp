#include "ScriptManager.h"

int Alert(lua_State *State);
int TestCFunction(lua_State *State);

CScriptManager::CScriptManager()
//TO DO : Inicializar la variable miembro m_LS a NULL
	: m_LS{NULL}
{
}

void CScriptManager::Initialize()
{
	//TO DO : Construye el lua_State m_LS utilizando la funci�n luaL_newstate de la librer�a de Lua
	m_LS = luaL_newstate();
	//TO DO : Inicializa las librer�as de lua utilizando la funci�n luaL_openlibs de la librer�a de Lua
	luaL_openlibs(m_LS);
	//TO DO : Registrar la funci�n TestCFunction con nombre en lua "TestCFunction" utilizando la funci�n lua_register de la librer�a de Lua
	lua_register(m_LS, "TestCFunction", TestCFunction);
	//TO DO : Registrar la funci�n Alert con nombre en lua "_ALERT" utilizando la funci�n lua_register de la librer�a de Lua
	lua_register(m_LS, "_ALERT", Alert);
	//TO DO : Ejecuta el archivo "./data/scripting/init.lua" utilizando el m�todo RunFile
	RunFile("./data/scripting/init.lua");
	//TO DO : Ejecuta el script "Test()" utilizando el m�todo RunCode
	RunCode("Test()");
}

//C�digo de la funci�n Alert que se llamar� al generarse alg�n error de LUA
//INFO : Esta funci�n reescribe la funci�n de lua Alert para que cuando se genere un error al ejecutar c�digo Lua extraer el texto del error en la variable local l_Text, deber�amos entonces mostrar la traza del error de alguna forma al desarrollador
int Alert(lua_State *State)
{
	std::string l_Text;
	int n = lua_gettop(State);
	int i;
	lua_getglobal(State, "tostring");
	for(i=1; i<=n; i++)
	{
		const char *s;
		lua_pushvalue(State, -1);
		lua_pushvalue(State, i);
		lua_call(State, 1, 1);
		s = lua_tostring(State, -1);
		if(s == NULL)
			return luaL_error(State, "`tostring' must return a string to `print'");
		if(i>1) l_Text += '\t';
		l_Text += s;
		lua_pop(State, 1);
	}
	l_Text += '\n';
	//Info(l_Text.c_str());
	return true;
}

//Para desinicializar el motor de LUA
void CScriptManager::Destroy()
{
	//TO DO : Cerrar la librer�a de lua utilizando la funci�n lua_close pas�ndole el lua_State m_LS
	lua_close(m_LS);
}

//Para ejecutar un fragmento de c�digo LUA
void CScriptManager::RunCode(const std::string &Code) const
{
	//TO DO : Llamar a la funci�n luaL_dostring pasando el lua_State m_LS para que ejecute el string lua que recibimos como par�metro, si devuelve diferente de 0 es que no se ha ejecutado correctamente
	if(luaL_dostring(m_LS, Code.c_str()))
	{
		//TO DO : En caso que no se haya le�do correctamente el fichero recoger del lua_State el string del error con la funci�n lua_tostring e �ndice -1
		const char* _ { lua_tostring(m_LS, -1) };
	}
}

//Para ejecutar un fichero de c�digo LUA
void CScriptManager::RunFile(const std::string &FileName) const
{
	//TO DO : Llamar a la funci�n luaL_dofile pasando el lua_State m_LS para que lea el fichero lua que recibimos como par�metro, si devuelve diferente de 0 es que no se ha cargado correctamente
	if(luaL_dofile(m_LS, FileName.c_str()))
	{
		//TO DO : En caso que no se haya le�do correctamente el fichero recoger del lua_State el string del error con la funci�n lua_tostring e �ndice -1
		const char* _ { lua_tostring(m_LS, -1) };
	}
}

//Si quisieramos implementar una funci�n que en C fuese
//void SetSpeedPlayer(int Speed);
int TestCFunction(lua_State *State)
{
	//TO DO : Recoger el valor del par�metro 1 que nos llega de la llamada a la funci�n en lua SetSpeedPlayer de tipo int utilizando la funci�n lua_tointeger de la librer�a de Lua
	int l_RetVal{ (int)lua_tointeger(State, 1) };
	//TO DO : Devolver un valor de tipo entero a la llamada a la funci�n en lua SetSpeedPlayer de tipo int utilizando la funci�n lua_pushinteger de la librer�a de Lua
	lua_pushinteger(State, l_RetVal);
	//TO DO : Devolver 1 con return ya que esta funci�n devuelve un valor a la llamda de la funci�n de lua
	return 1;
}