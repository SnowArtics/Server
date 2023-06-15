#pragma once

//DummyClient, GameServer에서도 참조가 가능하게끔 CorePch를 만듬

#include <iostream>
#include "Types.h"
#include "CoreMacro.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"
#include "Container.h"

#include <windows.h>
using namespace std;

#include "Lock.h"

#include "ObjectPool.h"
#include "TypeCast.h"