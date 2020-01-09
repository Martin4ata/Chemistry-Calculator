#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

const int FileLen = 86;//118
const int FileWidth = 18;//18
const int FileHeight = 7;//7


int main()
{
	int Z, Per = 0, Gr = 0, Neu, Pr, El, OutLayEl = 0;
	float atm = 0;
	string name, fullname;
	cout << "Input Atom Number: ";
	cin >> Z;//Atom Number
	Pr = Z;//Protons
	El = Z;//Electrons
	cout << endl;

	cout << "Testing" << endl;

	//Fill name.txt
	//Name
	ifstream on("name.txt");
	string tilename[FileLen];

	for (int i = 0; i < FileLen; i++)
	{
		on >> tilename[i];
	}

	for (int i = 0; i < FileLen; i++)
	{
		if (i + 1 == Z)
		{
			name = tilename[i];
		}
	}
	cout << name << endl;

	//Fill fullname.txt
	//Full Name
	ifstream of("fullname.txt");
	string fulltilename[FileLen];

	for (int i = 0; i < FileLen; i++)
	{
		of >> fulltilename[i];
	}

	for (int i = 0; i < FileLen; i++)
	{
		if (i + 1 == Z)
		{
			fullname = fulltilename[i];
		}
	}
	cout << fullname << endl;


	//Fill mass.txt
	//Mass
	ifstream in("mass.txt");
	float tiles[FileLen];

	for (int i = 0; i < FileLen; i++)
	{
		in >> tiles[i];
	}

	for (int i = 0; i < FileLen; i++)
	{
		if (i + 1 == Z)
		{
			atm = tiles[i];
		}
	}
	cout << atm << endl;

	//Neutrons
	Neu = round(atm) - Pr;
	cout << Neu << endl;

	//Period
	Per = 0;
	if (Z >= 1 and Z <= 2)
	{//1
		Per = 1;
	}
	else if (Z >= 3 and Z <= 10)
	{//2
		Per = 2;
	}
	else if (Z >= 11 and Z <= 18)
	{//3
		Per = 3;
	}
	else if (Z >= 19 and Z <= 36)
	{//4
		Per = 4;
	}
	else if (Z >= 37 and Z <= 54)
	{//5
		Per = 5;
	}
	else if (Z >= 55 and Z <= 86)
	{//6
		Per = 6;
	}
	else if (Z >= 87 and Z <= 118)
	{//7
		Per = 7;
	}
	cout << Per << endl;

	//Group
	ifstream gr("group.txt");
	int tilesgr[FileHeight][2];

	for (int i = 0; i < FileHeight; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			gr >> tilesgr[i][j];
		}
	}

	if (Z >= 58 and Z <= 71)
	{
		Gr = 0;
	}
	else if (Z >= 90 and Z <= 103)
	{
		Gr = 0;
	}
	else
	{
		for (int i = tilesgr[Per - 1][0]; i < tilesgr[Per - 1][1]; i++)
		{
			if (i == Z)
			{
				break;
			}
			Gr++;
		}

		if (Per == 1)
		{
			if (Z == 2)
			{
				Gr = 18;
				OutLayEl = Gr - 10;
			}
			else
			{
				Gr += 1;
				OutLayEl = Gr;
			}
		}
		else if (Per == 2 or Per == 3)
		{
			if (Z >= 5 and Z <= 10)
			{
				Gr += 11;
				OutLayEl = Gr - 10;
			}
			else if (Z >= 13 and Z <= 18)
			{
				Gr += 11;
				OutLayEl = Gr - 10;
			}
			else if (Z == 4 or Z == 3 or Z == 11 or Z == 12)
			{
				Gr += 1;
				OutLayEl = Gr;
			}
		}
		else if (Per == 6 or Per == 7)
		{
			Gr += 1;
			if (Z >= 58 and Z <= 86)
			{
				Gr -= 14;
			}
			else if (Z >= 90 and Z <= 118)
			{
				Gr -= 13;
			}
		}
		else
		{
			Gr += 1;
		}

	}
	cout << Gr << endl;

	//Metal/Nonmetal/Metaloid/Other
	ifstream inone("type0.txt");
	ifstream intwo("type1.txt");
	ifstream inthree("type2.txt");
	int tilestyOne[17], tilestyTwo[7], tilestyThree[8];
	int type = 3;
	// 0 - nonmetal, 1 - metaloid, 2 - unknown, 3 - metal
	bool check = false;
	string strtype;

	for (int i = 0; i < 17; i++)
	{
		inone >> tilestyOne[i];
	}
	for (int i = 0; i < 7; i++)
	{
		intwo >> tilestyTwo[i];
	}
	for (int i = 0; i < 8; i++)
	{
		inthree >> tilestyThree[i];
	}

	for (int i = 0; i < 17; i++)
	{
		if (check != false)
		{
			break;
		}
		else
		{

			if (Z == tilestyOne[i])
			{
				type = 0;
				check == true;
				break;
			}
		}
	}
	for (int i = 0; i < 7; i++)
	{
		if (check != false)
		{
			break;
		}
		else
		{

			if (Z == tilestyTwo[i])
			{
				type = 1;
				check == true;
				break;
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (check != false)
		{
			break;
		}
		else
		{

			if (Z == tilestyThree[i])
			{
				type = 2;
				check == true;
				break;
			}
		}
	}

	if (type == 0)
	{
		strtype = "Nonmetal";
	}
	else if (type == 1)
	{
		strtype = "Metaloid";
	}
	else if (type == 2)
	{
		strtype = "Unknown";
	}
	else if (type == 3)
	{
		strtype = "Metal";
	}

	//State at 23C\296K
	//Liquid Gas Unknown Solid
	ifstream inonest("liquid.txt");
	ifstream intwost("gas.txt");
	ifstream inthreest("unknown.txt");
	int stateOne[2], stateTwo[11], stateThree[15];
	int state = 3;
	// 0 - liquid, 1 - gas, 2 - unknown, 3 - solid
	bool checkstate = false;
	string strstate;

	for (int i = 0; i < 2; i++)
	{
		inonest >> stateOne[i];
	}
	for (int i = 0; i < 11; i++)
	{
		intwost >> stateTwo[i];
	}
	for (int i = 0; i < 15; i++)
	{
		inthreest >> stateThree[i];
	}

	for (int i = 0; i < 2; i++)
	{
		if (checkstate != false)
		{
			break;
		}
		else
		{

			if (Z == stateOne[i])
			{
				state = 0;
				checkstate == true;
				break;
			}
		}
	}
	for (int i = 0; i < 11; i++)
	{
		if (checkstate != false)
		{
			break;
		}
		else
		{

			if (Z == stateTwo[i])
			{
				state = 1;
				checkstate == true;
				break;
			}
		}
	}
	for (int i = 0; i < 15; i++)
	{
		if (checkstate != false)
		{
			break;
		}
		else
		{

			if (Z == stateThree[i])
			{
				state = 2;
				checkstate == true;
				break;
			}
		}
	}

	if (state == 0)
	{
		strstate = "Liquid";
	}
	else if (state == 1)
	{
		strstate = "Gas";
	}
	else if (state == 2)
	{
		strstate = "Unknown";
	}
	else if (state == 3)
	{
		strstate = "Solid";
	}

	//Valence Group A(1,2,13,14,15,16,17,18)
	int Val[10];
	int ValLen = 0;
	int Gtemp = Gr - 10;
	if (Gr == 1)
	{
		Val[0] = 1;
		ValLen = 1;
	}
	else if (Gr == 2)
	{
		Val[0] = 2;
		ValLen = 1;
	}
	else if (Gr == 13)
	{
		Val[0] = 3;
		ValLen = 1;
	}
	else if (Gr == 18)
	{
		Val[0] = 0;
		ValLen = 1;
	}
	else if (Gr == 14)
	{
		Val[0] = 8 - Gr + 10 - 2;
		Val[1] = Gr - 10;
		ValLen = 2;
	}
	else if (Gr == 15)
	{
		Val[0] = 8 - Gr + 10;
		Val[1] = Gr - 10;
		ValLen = 2;
	}
	else if (Gr == 16 or Gr == 17)
	{
		int count = 0;
		for (int i = 0; 8 - Gtemp + i <= Gtemp; i += 2)
		{
			Val[count] = 8 - Gtemp + i;
			ValLen++;
			count++;
		}
	}

	cout << endl << "End of Test";
	cout << endl;
	cout << endl;

	//THE Couting
	cout << "Name: " << name << ";" << endl; //Done
	cout << "Full Name: " << fullname << ";" << endl; //Done 86/118
	cout << "Atomic Number: " << Z << ";" << endl; //Done 86/118
	cout << "Protons+: " << Pr << ";" << endl; //Done
	cout << "Electrons-: " << El << ";" << endl; //Done
	cout << "Neutrons0: " << Neu << ";" << endl; //Done 86/118
	cout << "Atomic Mass: " << atm << ";" << endl; //Done
	cout << "Number of Electron- Layers: " << Per << ";" << endl; //Done
//	cout << "Number of Elecrons- in Outwards most Layer: " << OutLayEl << endl; //Needs more work
	cout << "Period: " << Per << ";" << endl; //Done
	if (Gr != 0)
	{
		cout << "Group: " << Gr << ";" << endl; //Done
	}
	else
	{
		cout << "Group: n/a" << ";" << endl; //Done
	}
	cout << "Type: " << strtype << ";" << endl; //Done
	cout << "State: " << strstate << ";" << endl;
	if (Gr >= 3 and Gr <= 12)
	{
		cout << "Valence: " << "Not Programmed yet;"; //Done
	}
	else
	{
		if (ValLen == 1)
		{
			cout << "Valence: " << Val[0] << ";"; //Done
		}
		else
		{
			cout << "Valence: ";
			for (int i = 0; i < ValLen; i++)
			{
				cout << Val[i]; //Done
				if (i < ValLen - 1)
				{
					cout << ", ";
				}
				else
				{
					cout << ";";
				}
			}
		}
	}
	cout << endl;
	// 0 - nonmetal, 1 - metaloid, 2 - unknown, 3 - metal
	cout << "Chemical bond with H2: ";
	if (Z == 1)
	{
		cout << "H2";
	}
	else if (Gr == 0)
	{
		cout << "n/a" << ";" << endl; //Done
	}
	else
	{
		if (type == 0)//nonmetal
		{
			int ValH = 1;
			int TempValH = Val[0];
			int NumH = 1, NumE = 1;

			if (TempValH == 0)
			{
				cout << "Bond not possible;";
			}
			else
			{
				NumH = TempValH;
				NumE = ValH;

				if (NumH == 1)
				{
					if (NumE == 1)
					{
						cout << "H" << name;
					}
					else
					{
						cout << "H" << name << NumE;
					}
				}
				else if (NumE == 1)
				{
					cout << "H" << NumH << name;
				}
				else
				{
					cout << "H" << NumH << name << NumE;
				}
			}
		}
		else if (type == 1)//metaloid
		{
			int ValH = 1;
			int TempValH = Val[0];
			int NumH = 1, NumE = 1;

			if (TempValH == 0)
			{
				cout << "Bond not possible;";
			}
			else
			{
				NumH = TempValH;
				NumE = ValH;

				if (NumH == 1)
				{
					if (NumE == 1)
					{
						cout << name << "H";
					}
					else
					{
						cout << name << NumE << "H";
					}
				}
				else if (NumE == 1)
				{
					cout << name << "H" << NumH;
				}
				else
				{
					cout << name << NumE << "H" << NumH << name << NumE;
				}
			}
		}
		else if (type == 2)
		{
			cout << "Unknown";
		}
		else if (type == 3)//metal
		{
			if (Gr >= 3 and Gr <= 12)
			{
				cout << "Not Programmed yet;"; //Done
			}
			else
			{
				int ValH = 1;
				int TempValH = Val[0];
				int NumH = 1, NumE = 1;

				if (TempValH == 0)
				{
					cout << "Bond not possible;";
				}
				else
				{
					NumH = TempValH;
					NumE = ValH;

					if (NumH == 1)
					{
						if (NumE == 1)
						{
							cout << name << "H";
						}
						else
						{
							cout << name << NumE << "H";
						}
					}
					else if (NumE == 1)
					{
						cout << name << "H" << NumH;
					}
					else
					{
						cout << name << NumE << "H" << NumH << name << NumE;
					}
				}
			}
		}
	}
	cout << endl;

	// 0 - nonmetal, 1 - metaloid, 2 - unknown, 3 - metal
	cout << "Chemical bond with O2: ";
	if (Z == 8)
	{
		cout << "O2";
	}
	else if (Gr == 0)
	{
		cout << "n/a" << ";" << endl; //Done
	}
	else
	{
		if (type == 0)//nonmetal
		{
			int ValO = 2;
			int TempValO = Val[0];
			int NumO = 1, NumE = 1;

			if (TempValO == 0)
			{
				cout << "Bond not possible;";
			}
			else
			{
				NumO = TempValO;
				NumE = ValO;

				if (NumO == 1)
				{
					if (NumE == 1)
					{
						cout << name << "O";
					}
					else
					{
						cout << name << NumE << "O";
					}
				}
				else if (NumE == 1)
				{
					cout << name << "O" << NumO;
				}
				else
				{
					cout << name << NumE << "O" << NumO;
				}
			}
		}
		else if (type == 1)//metaloid
		{
			int ValO = 2;
			int TempValO = Val[0];
			int NumO = 1, NumE = 1;

			if (TempValO == 0)
			{
				cout << "Bond not possible;";
			}
			else
			{
				NumO = TempValO;
				NumE = ValO;

				if (NumO == 1)
				{
					if (NumE == 1)
					{
						cout << name << "O";
					}
					else
					{
						cout << name << NumE << "O";
					}
				}
				else if (NumE == 1)
				{
					cout << name << "O" << NumO;
				}
				else
				{
					cout << name << NumE << "O" << NumO;
				}
			}
		}
		else if (type == 2)
		{
			cout << "Unknown";
		}
		else if (type == 3)//metal
		{
			if (Gr >= 3 and Gr <= 12)
			{
				cout << "Not Programmed yet;" << endl; //Done
			}
			else
			{
				int ValO = 2;
				int TempValO = Val[0];
				int NumO = 1, NumE = 1;

				if (TempValO == 0)
				{
					cout << "Bond not possible;";
				}
				else
				{
					NumO = TempValO;
					NumE = ValO;

					if (NumO == 1)
					{
						if (NumE == 1)
						{
							cout << name << "O";
						}
						else
						{
							cout << name << NumE << "O";
						}
					}
					else if (NumE == 1)
					{
						cout << name << "O" << NumO;
					}
					else
					{
						cout << name << NumE << "O" << NumO;
					}
				}
			}
		}
	}
	cout << endl;

	//add: atomic model, luic model, vallence->somewhat done

}