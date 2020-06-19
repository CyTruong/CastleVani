#pragma once
class PlayerStatus
{
	static PlayerStatus* ___instance;
private:
	int PlayerHp;
	int PlayerMana;
	int SubWeaponIndex;
	int StateIndex;
	int Score;
public:
	static PlayerStatus* getInstance();
	PlayerStatus();
	void getPlayerHp(int& playerhp) { playerhp = this->PlayerHp; }
	void getPlayerMana(int& playermana) { playermana = this->PlayerMana; }
	void getSubWeaponIndex(int& subweapon) { 
		subweapon = this->SubWeaponIndex; 
	}
	void getStateIndex(int& stateindex) { StateIndex = stateindex; }
	void getScore(int& score) { Score = score; }
	void SubHp(int minusHp) { this->PlayerHp -= minusHp; }
	void SubMana(int minuMana) { this->PlayerHp -= minuMana;  }
	void SetSubWeapon(int subwp) { 
		this->SubWeaponIndex = subwp; 
	}
	void SetStateIndex(int stateindex) { this->StateIndex = stateindex; }
	void SetScore(int score) { this->Score = score; }
	~PlayerStatus();
};

