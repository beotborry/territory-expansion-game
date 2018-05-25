#pragma once
#include <vector>
	int occupied[605][605]; // -1 : black, 0 :line, 1:white(occupied area) 
	int time_constant = 0; // when use srand()
	int player_life = 3; // life
	int zombie_killed = 0; 
	int direction; // 현재 direction


	float ratio() { // area/전체(%)
		int r = 0;
		for (int i = 0; i < 601; i+= 5) {
			for (int j = 0; j < 601; j+= 5)
				if(occupied[i][j] ==1) r++;// -1 : black, 0 :line, 1:white 
		}
		return r / (100.0 * 120.0) * 100;
	}
