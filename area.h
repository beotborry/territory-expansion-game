#pragma once
	int occupied[605][605]; // -1 : black, 0 :line, 1:white 
	int time_constant = 0; // when use srand()
	int player_life = 3; // life
	int zombie_killed = 0; 
	int last_key[2] = { 0,0 }; // ���� two directions
	int direction; // ���� direction

	float ratio() { // area/��ü(%)
		int r = 0;
		for (int i = 0; i < 601; i+= 5) {
			for (int j = 0; j < 601; j+= 5)
				if(occupied[i][j] ==1) r++;// -1 : black, 0 :line, 1:white 
		}
		return r / (100.0 * 120.0) * 100;
	}