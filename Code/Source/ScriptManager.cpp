#include "ScriptManager.h"

int Alert(lua_State *State);
int TestCFunction(lua_State *State);

CScriptManager::CScriptManager()
//TO DO : Inicializar la variable miembro m_LS a NULL
{
}

void CScriptManager::Initialize()
{
	//TO DO : Construye el lua_State m_LS utilizando la función luaL_newstate de la librería de Lua
	//TO DO : Inicializa las librerías de lua utilizando la función luaL_openlibs de la librería de Lua
	//TO DO : Registrar la función TestCFunction con nombre en lua "TestCFunction" utilizando la función lua_register de la librería de Lua
	//TO DO : Registrar la función Alert con nombre en lua "_ALERT" utilizando la función lua_register de la librería de Lua
	//TO DO : Ejecuta el archivo "./data/scripting/init.lua" utilizando el método RunFile
	//TO DO : Ejecuta el script "Test()" utilizando el método RunCode
}

//Código de la función Alert que se llamará al generarse algún error de LUA
//INFO : Esta función reescribe la función de lua Alert para que cuando se genere un error al ejecutar código Lua extraer el texto del error en la variable local l_Text, deberíamos entonces mostrar la traza del error de alguna forma al desarrollador
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
	//TO DO : Cerrar la librería de lua utilizando la función lua_close pasándole el lua_State m_LS
}

//Para ejecutar un fragmento de código LUA
void CScriptManager::RunCode(const std::string &Code) const
{
	//TO DO : Llamar a la función luaL_dostring pasando el lua_State m_LS para que ejecute el string lua que recibimos como parámetro, si devuelve diferente de 0 es que no se ha ejecutado correctamente
	if()
	{
		//TO DO : En caso que no se haya leído correctamente el fichero recoger del lua_State el string del error con la función lua_tostring e índice -1
	}
}

//Para ejecutar un fichero de código LUA
void CScriptManager::RunFile(const std::string &FileName) const
{
	//TO DO : Llamar a la función luaL_dofile pasando el lua_State m_LS para que lea el fichero lua que recibimos como parámetro, si devuelve diferente de 0 es que no se ha cargado correctamente
	if())
	{
		//TO DO : En caso que no se haya leído correctamente el fichero recoger del lua_State el string del error con la función lua_tostring e índice -1
	}
}

//Si quisieramos implementar una función que en C fuese
//void SetSpeedPlayer(int Speed);
int TestCFunction(lua_State *State)
{
	//TO DO : Recoger el valor del parámetro 1 que nos llega de la llamada a la función en lua SetSpeedPlayer de tipo int utilizando la función lua_tointeger de la librería de Lua
	//TO DO : Devolver un valor de tipo entero a la llamada a la función en lua SetSpeedPlayer de tipo int utilizando la función lua_pushinteger de la librería de Lua
	//TO DO : Devolver 1 con return ya que esta función devuelve un valor a la llamda de la función de lua
}