#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

#define ROW 12
#define MENU 7

enum navikeys {

	ENTER = 13,
	ESC = 27,
	UP = 72,
	DOWN = 80
};

enum textcolor {

	STANDART = 15,
	HIGHLIGHT = 3
};

class Apartment
{

private:
	struct Flat {
		int square;
		int rooms;
		int price;
	};
	Flat flat;

	static int count;
	static int select;
	static HANDLE hSettings;

	Apartment& operator=(Apartment& object);
	bool operator==(const Apartment& object) const;
	bool operator==(int price) const;
	bool operator<(int price) const;

	void SetSquare(int square);
	void SetRooms(int rooms);
	void SetPrice(int price);

	int GetSquare() const;
	int GetRooms() const;
	int GetPrice() const;

	void SettingsHideCursor(bool hide);
	void SettingsSetCoords(short x, short y);
	void SettingsTextColor(int textcolor);
	void SettingsPause();
	void SettingsSafeInput(int& value, int min, int max);

	void LogicDisplayValues(Flat arr[], int index);
	void LogicSelectValue(Flat arr[], int size);
	void LogicInitItem();
	void LogicAddObject(Apartment*& object);
	void LogicPrintItem();
	void LogicPrintObject(Apartment* object);
	void LogicSearchIndex(Apartment* object, int& index);
	void LogicRemoveObject(Apartment*& object, int index);
	void LogicCompareSquares(Apartment* object);
	void LogicComparePrices(Apartment* object);
	void LogicCleanMemory(Apartment*& object);

	void DisplayMenu(const char* menu[], int select);
	void DisplayAddObject(Apartment*& object);
	void DisplayPrintObject(Apartment* object);
	void DisplayRemoveObject(Apartment*& object);
	void DisplayEditObject(Apartment*& object);
	void DisplayCompareSquares(Apartment* object);
	void DisplayComparePrices(Apartment* object);

	void SaveData(FILE* file, Apartment*& object, const char* filename);
	void ReadData(FILE* file, Apartment*& object, const char* filename);

public:

	Apartment();
	Apartment(const Apartment*& object) = delete;

	void ExecutiveAlgorithm(Apartment*& object);
};

