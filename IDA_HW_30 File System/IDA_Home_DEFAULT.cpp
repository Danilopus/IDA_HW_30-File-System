#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include <fstream>

// Service functions prototypes ------------------------------------
int Get_Int_SA();				// String-analysis вариант фильтра INTEGER
int Get_Int_Positive();			// String-Analysis вариант проверки ввода INTEGER_POSITIVE		


// Homework 30 ----------------------------------------------------	

//Task 1
int Write_str_to_file(const std::string& File_path, std::string& user_string_input)
{
	
	std::ofstream write_to_file_stream;
	write_to_file_stream.open(File_path, std::ios::app);

	if (write_to_file_stream.is_open())
	
	{ 
		write_to_file_stream << user_string_input << "\n";
		return 1;
	}
	//write_to_file_stream.close(); - деструктор сработает при закрытии области видимости функции
	user_string_input = "New value";
	return 0;
}
int File_COUT(const std::string& File_path)
{
	std::ifstream read_file_stream;
	read_file_stream.open(File_path);
	if (read_file_stream.is_open())
	{
		char sybmbol;
		//std::string file_content;
		while (read_file_stream.get(sybmbol))
		{
			//file_content << sybmbol;
			std::cout << sybmbol;			
		}
		//std::cout << file_content;
		return 1;
	}
	return 0;
}
void File_DELETE(const std::string& File_path)
{
	std::remove(File_path.c_str());
}

void Home_Task_1()
{
	std::string File_path = "file with strings.txt";

	File_DELETE(File_path); //Файл может существовать на момент запуска и тогда все новые строки просто добавятся в него, а вывод будет неверный
	// Поэтому попробуем стереть файл сразу на запуске

	std::string user_string_input;
	int string_iterator = 0;
	std::cout << "Enter a string to write in file:\n";
	while (true)
	{
		string_iterator++;
		std::cout << "String " <<string_iterator <<": ";
		getline(std::cin, user_string_input);   
		if (user_string_input == "end") break;
		if (Write_str_to_file(File_path, user_string_input))
			std::cout << "\t\t*** writing to file: ok ***\n";
		else std::cout << "\t\t*** writing to file: error ***";
	}
	std::cout << "\n\nReading from file:\n";
	File_COUT(File_path);
	File_DELETE(File_path);
	std::cout << "\n\n\t\t*** Deleting file: ок ***\n";

}
//Task 2
bool overwrite(const std::string& File_path, std::string& user_string_input)
{
	//Check existing of a file
	std::fstream file_stream;
	file_stream.open(File_path);
	if (file_stream.is_open())
	{
		file_stream << user_string_input;
		return 1;
	}
	else return 0;
}
void Home_Task_2()
{
	std::string File_path = "file_for_overwrite.delete_me";
	std::cout << "Enter a string to overwrite file:\n";
	std::string user_string_input;
	getline(std::cin, user_string_input);
	if (overwrite(File_path, user_string_input))
		std::cout << "\nOverwriting complete\n";
	else std::cout << "\nError overwriting\n";
}

// MAIN ------- MAIN ------- MAIN ------- MAIN ------- MAIN --------
int main()
{
	setlocale(LC_CTYPE, "Russian");
	//system("mode con cols=110 lines=40"); 
	std::string Name_of_Work = { "Home Work 30: File system" };
	std::string Menu_Element_1 = { "Write strings into a file, then read, then delete" };
	std::string Menu_Element_2 = { "Overwrite function" };
	//std::string Menu_Element_3 = { "Sort_Array_from_N(arr[], Size, N): Search first encaunter of N in array, then sort from this position" };
	//std::string Menu_Element_4 = { "Search_First_Ordinary_in_Array(arr[], Size): Returns first ordinary number in an array" };

	do 
	{		
		system("cls");
		std::cout << "\n\t***\t" << Name_of_Work << "\t***\n\n\t\n\nChoose an option: \n";
		std::cout << "\n 1. " << Menu_Element_1;
		std::cout << "\n 2. " << Menu_Element_2;
		//std::cout << "\n 3. " << Menu_Element_3;
		//std::cout << "\n 4. " << Menu_Element_4;
		std::cout << "\n\n 0. Exit\n";
		int choice = 0;
		std::cout << "\nYour choice: ";
		choice = Get_Int_Positive();		
		std::cout << "\n";
		// Обработка выбора пользователя
		if (choice == 0) { std::cout << "\nGood By"; for (int j = 0; j < 50; j++) { Sleep(50 - j); std::cout << "y"; } std::cout << "e!"; Sleep(850);  return 0; }
		else if (choice == 1) Home_Task_1();
		else if (choice == 2) Home_Task_2();
		//else if (choice == 3) Sort_Array_from_N_demo();
		//else if (choice == 4) Search_First_Ordinary_in_Array_demo();
			
		else { std::cout << "\nSuch choice does not exist yet\n"; Sleep(1000); }
		std::cout << "\n\n";
		system("pause");
	} while (true);
	return 0;
}

// Service functions -----------------------------------------
int Get_Int_SA() {
	std::string a;
	std::cin.sync(); 
	std::cin.clear(); 
	getline(std::cin, a);
	if (a != "")
	{

		if ((a.find_first_not_of("-0123456789") == -1))
		{
			for (int i = 1; i < a.size(); i++) // определяем есть ли минусы кроме первого символа
			{
				if (a[i] == '-') 
				{
					std::cout << "Input Error: Minus misstanding. [INTEGER] expected.\n";
					return Get_Int_SA();
				}
			}
			try
			{
				return stoi(a);
			}
			catch (std::out_of_range)
			{
				std::cout << "Input Error: Data type overflow. [INTEGER] expected.\n";
				return Get_Int_SA();
			}


		}
		else
		{
			std::cout << "Input Error: Incorrect symbol. [INTEGER] expected.\n";
			return Get_Int_SA();
		}
	}
	else
	{
		std::cout << "Input Error: NULL input. [INTEGER] expected.\n";
		return Get_Int_SA();
	}
}
int Get_Int_Positive()
{
	std::string a;
	std::cin.sync();
	std::cin.clear();
	getline(std::cin, a);
	if (a != "") 
	{

		if ((a.find_first_not_of("0123456789") == -1))
		{
			try{
				return stoi(a);
			}
			catch (std::out_of_range){
				std::cout << "Input Error: overflow. Positive [INTEGER] expected.\n";
			}
		}
		else
		{
			std::cout << "Input Error: Positive [INTEGER] expected.\n";
			return Get_Int_Positive();
		}		
	}
	else
		std::cout << "Input Error: NULL input. Positive [INTEGER] expected.\n";
	return Get_Int_Positive();
}

