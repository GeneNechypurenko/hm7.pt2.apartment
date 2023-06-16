#include "Apartment.h"



int Apartment::count = 0;
int Apartment::select = 0;
HANDLE Apartment::hSettings = GetStdHandle(STD_OUTPUT_HANDLE);



Apartment& Apartment::operator=(Apartment& object) {

	flat.square = object.flat.square;
	flat.rooms = object.flat.rooms;
	flat.price = object.flat.price;

	return*this;
}
bool Apartment::operator==(const Apartment& object) const {

	return this->flat.square == object.flat.square;
}
bool Apartment::operator==(int price) const {

	return this->flat.price == price;
}
bool Apartment::operator<(int price) const {

	return flat.price < price;
}



void Apartment::SetSquare(int square) {

	this->flat.square = square;
}
void Apartment::SetRooms(int rooms) {

	this->flat.rooms = rooms;
}
void Apartment::SetPrice(int price) {

	this->flat.price = price;
}



int Apartment::GetSquare() const {

	return flat.square;
}
int Apartment::GetRooms() const {

	return flat.rooms;
}
int Apartment::GetPrice() const {

	return flat.price;
}



void Apartment::SettingsHideCursor(bool hide) {

	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hSettings, &structCursorInfo);
	structCursorInfo.bVisible = hide;
	SetConsoleCursorInfo(hSettings, &structCursorInfo);
}
void Apartment::SettingsSetCoords(short x, short y) {

	SetConsoleCursorPosition(hSettings, { x,y });
}
void Apartment::SettingsTextColor(int textcolor) {

	SetConsoleTextAttribute(hSettings, textcolor);
}
void Apartment::SettingsPause() {

	const short x = 40, y = 26;
	SetConsoleCursorPosition(hSettings, { x,y });
	system("pause");
}
void Apartment::SettingsSafeInput(int& value, int min, int max) {

	short x = 8, y = 1;
	SettingsSetCoords(x, y);

	while (!(cin >> value) || value < min || value > max) {
		cout << "помилка, невірно задане значення.. спробуйте знову: ";
		cin.clear();
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
	}
}



void Apartment::LogicDisplayValues(Flat arr[], int index) {

	short x = 0, y = 0;

	system("cls");
	SettingsTextColor(STANDART);

	SettingsSetCoords(x, y);
	cout << "square: " << arr[index].square;
	SettingsSetCoords(x, y + 1);
	cout << "rooms : " << arr[index].rooms;
	SettingsSetCoords(x, y + 2);
	cout << "price : " << arr[index].price;
}
void Apartment::LogicSelectValue(Flat arr[], int size) {

	int index = 0;

	LogicDisplayValues(arr, index);

	while (true) {

		char action = _getch();
		if (action == 0 || action == 224)
			action = _getch();

		if (action == UP) {
			index = (index - 1 + ROW) % ROW;
			LogicDisplayValues(arr, index);
		}

		else if (action == DOWN) {
			index = (index + 1) % ROW;
			LogicDisplayValues(arr, index);
		}

		else if (action == ENTER) {
			SetSquare(arr[index].square);
			SetRooms(arr[index].rooms);
			SetPrice(arr[index].price);
			break;
		}
	}
}
void Apartment::LogicInitItem() {

	const int size = 12;
	Flat arr[size] =
	{
		 {28, 1, 30000}, {30, 1, 32000}, {32, 1, 34000}, {34, 1, 36000},
		 {40, 2, 42000}, {42, 2, 44000}, {44, 2, 46000}, {48, 2, 50000},
		 {52, 3, 53000}, {56, 3, 57000}, {60, 3, 63000}, {68, 3, 72000}
	};

	LogicSelectValue(arr, size);
}
void Apartment::LogicAddObject(Apartment*& object) {

	Apartment* temp = new Apartment[count + 1];

	for (int i = 0; i < count; i++)
		if (object != nullptr)
			temp[i] = object[i];

	temp[count].LogicInitItem();

	delete[]object;
	object = temp;
	++count;
}
void Apartment::LogicPrintItem() {

	cout << "square: " << flat.square << endl;
	cout << "rooms : " << flat.rooms << endl;
	cout << "price : " << flat.price << endl << endl;
}
void Apartment::LogicPrintObject(Apartment* object) {

	if (count != 0) 
		for (int i = 0; i < count; i++)
			object[i].LogicPrintItem();
	else 
		cout << "список порожній";
}
void Apartment::LogicSearchIndex(Apartment* object, int& index) {

	cout << "введіть індекс для пошуку\nіндекс: ";
	SettingsSafeInput(index, 1, count);
	index -= 1;
}
void Apartment::LogicRemoveObject(Apartment*& object, int index) {

	Apartment* temp = new Apartment[count - 1];
	int j = 0;

	for(int i = 0; i < count; i++)
		if (i != index) {
			temp[j] = object[i];
			j++;
		}

	delete[]object;
	object = temp;
	--count;
}
void Apartment::LogicCompareSquares(Apartment* object) {

	if (count != 0) {

		Apartment temp;
		temp.LogicInitItem();

		system("cls");

		cout << "за данним запитом доступні слідуючи квартири: \n\n";

		for (int i = 0; i < count; i++)
			if (temp.flat.square == object[i].flat.square)
				object[i].LogicPrintItem();
	}
	else cout << "список порожній";
}
void Apartment::LogicComparePrices(Apartment* object) {

	if (count != 0) {

		int min = object[0].flat.price;

		for (int i = 0; i < count; i++) 
			if (object[i].flat.price < min) 
				min = object[i].flat.price;


		cout << "Список кращіх за ціною квартир: \n\n";

		for (int i = 0; i < count; i++)
			if (object[i].flat.price == min) 
				object[i].LogicPrintItem();
	}
	else cout << "Список порожній\n";
}
void Apartment::LogicCleanMemory(Apartment*& object) {

	delete[]object;
}



void Apartment::DisplayMenu(const char* menu[], int select) {

	char marker = 149;
	system("cls");

	for (int i = 0; i < MENU; i++) {

		SettingsTextColor(STANDART);

		if (i == select) {
			SettingsTextColor(HIGHLIGHT);
			cout << " " << marker << " ";
			cout << menu[i] << endl;
		}

		else {
			SettingsTextColor(STANDART);
			cout << "   ";
			cout << menu[i] << endl;
		}
	}
}
void Apartment::DisplayAddObject(Apartment*& object) {

	system("cls");
	LogicAddObject(object);
	SettingsPause();
}
void Apartment::DisplayPrintObject(Apartment* object) {

	system("cls");
	LogicPrintObject(object);
	SettingsPause();
}
void Apartment::DisplayRemoveObject(Apartment*& object) {

	system("cls");
	LogicPrintObject(object);
	SettingsPause();

	system("cls");
	if (count != 0) {
		int index = 0;
		LogicSearchIndex(object, index);
		LogicRemoveObject(object, index);
		SettingsPause();
	}
}
void Apartment::DisplayEditObject(Apartment*& object) {

	system("cls");
	LogicPrintObject(object);
	SettingsPause();

	system("cls");
	if (count != 0) {
		int index = 0;
		LogicSearchIndex(object, index);
		object[index].LogicInitItem();
		SettingsPause();
	}
}
void Apartment::DisplayCompareSquares(Apartment* object) {

	system("cls");
	LogicCompareSquares(object);
	SettingsPause();
}
void Apartment::DisplayComparePrices(Apartment* object) {

	system("cls");
	LogicComparePrices(object);
	SettingsPause();
}



void Apartment::SaveData(FILE* file, Apartment*& object, const char* filename) {

	fopen_s(&file, filename, "wb");

	if (file == nullptr) {
		cout << "Помилка відкриття файлу!" << endl;
		return;
	}

	fwrite(&count, sizeof(count), 1, file);

	for (int i = 0; i < count; i++) {

		int square = object[i].GetSquare();
		int rooms = object[i].GetRooms();
		int price = object[i].GetPrice();

		fwrite(&square, sizeof(square), 1, file);
		fwrite(&rooms, sizeof(rooms), 1, file);
		fwrite(&price, sizeof(price), 1, file);
	}

	fclose(file);
}
void Apartment::ReadData(FILE* file, Apartment*& object, const char* filename) {

	fopen_s(&file, filename, "rb");

	if (file == nullptr) {
		cout << "Помилка відкриття файлу!" << endl;
		return;
	}

	fread(&count, sizeof(count), 1, file);

	Apartment* data = new Apartment[count];

	for (int i = 0; i < count; i++) {

		int square;
		int rooms;
		int price;

		fread(&square, sizeof(square), 1, file);
		fread(&rooms, sizeof(rooms), 1, file);
		fread(&price, sizeof(price), 1, file);

		data[i].SetSquare(square);
		data[i].SetRooms(rooms);
		data[i].SetPrice(price);
	}

	fclose(file);
	object = data;
}



Apartment::Apartment()
	:flat{ 0,0,0 } {}

void Apartment::ExecutiveAlgorithm(Apartment*& object) {

	char filename[MAX_PATH] = "save.bin";
	FILE* file = nullptr;
	ReadData(file, object, filename);

	const char* menu[]
	{
		"Додати апартаменти   ",
		"Вивести список       ",
		"Видалити апартаменти ",
		"Редагувати           ",
		"Порівняти за площиною",
		"Порівняти за ціною   ",
		"Вихід                "
	};

	while (true) {

		SettingsHideCursor(FALSE);
		DisplayMenu(menu, select);

		char action = _getch();
		if (action == 0 || action == 224)
			action = _getch();

		switch (action) {

		case UP:
			select = (select - 1 + MENU) % MENU;
			break;

		case DOWN:
			select = (select + 1) % MENU;
			break;

		case ENTER:
			switch (select) {

			case 0:
				DisplayAddObject(object);
				break;

			case 1:
				DisplayPrintObject(object);
				break;

			case 2:
				DisplayRemoveObject(object);
				break;

			case 3:
				DisplayEditObject(object);
				break;

			case 4:
				DisplayCompareSquares(object);
				break;

			case 5:
				DisplayComparePrices(object);
				break;

			case 6:
				SaveData(file, object, filename);
				LogicCleanMemory(object);
				return;
			}
			break;

		case ESC:
			SaveData(file, object, filename);
			LogicCleanMemory(object);
			return;
		}
	}
}