#pragma once

namespace dude {
	void __declspec() hook_move();
	void __declspec() hook_run();
	void __stdcall run(int actionPoints);
	void __stdcall move(int actionPoints);
}