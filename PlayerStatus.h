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
	int Whipslevel;
	int EnemyHp;
	bool ZA_WARUDO;
public:
	static PlayerStatus* getInstance();
	PlayerStatus();
	void getPlayerHp(int& playerhp) { playerhp = this->PlayerHp; }
	void getPlayerMana(int& playermana) { playermana = this->PlayerMana; }
	void getSubWeaponIndex(int& subweapon) { 
		subweapon = this->SubWeaponIndex; 
	}
	void getStateIndex(int& stateindex) { stateindex = this->StateIndex; }
	void getScore(int& score) { score = this->Score; }
	void getWhipsLevel(int& level) { level = this->Whipslevel; }
	void getEnemyHp(int& enemyhp) { enemyhp = this->EnemyHp;  }
	void increaseScore(int score) { 
		this->Score = this->Score + score;
	}
	bool isZAWARUDO() { return ZA_WARUDO; }
	void SubHp(int minusHp) { this->PlayerHp -= minusHp; }
	void IncreaseMana(int mana) { this->PlayerMana += mana; }
	void SubMana(int minuMana) { this->PlayerMana -= minuMana;  }
	void SetSubWeapon(int subwp) { 
		this->SubWeaponIndex = subwp; 
	}
	void SetStateIndex(int stateindex) { this->StateIndex = stateindex; }
	void SetScore(int score) { this->Score = score; }
	void SetWhipsLevel(int level) { this->Whipslevel = level; }
	void SetEnemyHp(int hp) { this->EnemyHp = hp; }
	void ZAWARUDO(bool tokkitomare) { 
		this->ZA_WARUDO = tokkitomare;
	}
	~PlayerStatus();
};

