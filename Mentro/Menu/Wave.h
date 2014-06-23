#pragma once
#include <oslib/oslib.h>
#include <pspsdk.h>

class Wave
{
public:
	static void Setup(u32 col1, u32 col2, u32 col3, u32 col4);
	static void Update();
	static void Render();
};

