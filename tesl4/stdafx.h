// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#include "resource.h"

// Windows 헤더 파일:
#include<windows.h>
#include <iostream>
#include <ctime>
#include <thread>
//d3d
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include <dxfile.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <list>
#include <vector>


//Tesl4->Framework Part
#include "structs.h"
#include "RenderDX11.h" 
#include "Scene.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Actor.h"
#include "TimeMgr.h" 
#include "ShaderObj.h" 


//Tesl4->Content Part
#include "Triangles.h"
#include "TriangleActor.h"






//typedefs
#define null	nullptr



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#define PATH_KAROK_X L"res/kalok.x";