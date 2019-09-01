#pragma once

namespace dude {
	void __declspec() hook_move();
	void __declspec() hook_run();
	void run(int actionPoints);
	void move(int actionPoints);
	int check_move(int actionPoints);
}