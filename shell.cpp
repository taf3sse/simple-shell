#include <iostream>
#include <cstring>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/mount.h>
#include <sys/statvfs.h>

using namespace std;

// define input character capacity
int MAXIMUM = 100;

// removes spaces from string and return it
string removeSpace(string str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	str.erase(remove(str.begin(), str.end(), '\t'), str.end());

	return str;
}

// displays file type
void funT(struct stat fileInfo)
{
	if ((fileInfo.st_mode & S_IFMT) == S_IFDIR)
	{
		cout << "Type			: Directory\n";
	}
	else if ((fileInfo.st_mode & S_IFMT) == S_IFREG)
	{
		cout << "Type			: Regular\n";
	}

	else if ((fileInfo.st_mode & S_IFMT) == S_IFLNK)
	{
		cout << "Type					: Symbolic link\n";
	}
	else
	{
		cout << "IDK file type\n";
	}
}

// displays inode number
void funI(struct stat fileInfo)
{
	cout << "inode             	: " << (int)fileInfo.st_ino << endl;
}

// displays time last modified
void funM(struct stat fileInfo)
{
	cout << "Last Modified      	: " << ctime(&fileInfo.st_mtime) << endl;
}

// displays type of file system
void fileType(struct statfs sbuf)
{
	cout << "file type:		";
	if (sbuf.f_type == 0x137D)
	{
		cout << "EXT\n";
	}
	else if (sbuf.f_type == 0xEF53)
	{
		cout << "EXT2\n";
	}

	else if (sbuf.f_type == 0x4d44)
	{
		cout << "MSDOS\n";
	}

	else
	{
		cout << "others\n";
	}
}

// fileinfo help
void fileinfo_man()
{
	cout << "NAME\n";
	cout << "	fileinfo\n";
	cout << "SYNOPSIS\n";
	cout << "	fileinfo -switch filename\n";
	cout << "DESCRIPTION\n";
	cout << "	Displays file informations\n";
	cout << "	all possible valid switches are:\n";
	cout << "\n-i		inode number";
	cout << "\n-t		type of file";
	cout << "\n-m		modification date\n";
}
// clear help
void clear_man()
{
	cout << "NAME\n";
	cout << "	clear\n";
	cout << "SYNOPSIS\n";
	cout << "	clear\n";
	cout << "DESCRIPTION\n";
	cout << "	clears the entire screen \n";
}

// exit help
void exit_man()
{
	cout << "NAME\n";
	cout << "	exit\n";
	cout << "SYNOPSIS\n";
	cout << "	exit [n]\n";
	cout << "DESCRIPTION\n";
	cout << "	terminates the shell\n";
	cout << "	typing prompt returns to default. if argument (n)\n";
	cout << "	it will be the exit value of the execution.\n";
}

// prompt help
void prompt_man()
{
	cout << "NAME\n";
	cout << "	prompt\n";
	cout << "SYNOPSIS\n";
	cout << "	prompt [new_prompt]\n";
	cout << "DESCRIPTION\n";
	cout << "	changes current shell prompt to the new_prompt\n";
	cout << "	typing prompt returns to default.\n";
}

// osifo help
void osifo_man()
{
	cout << "NAME\n";
	cout << "	osifo\n";
	cout << "SYNOPSIS\n";
	cout << "	osifo -switch\n";
	cout << "DESCRIPTION\n";
	cout << "	Displays system related informations based on the switch\n";
	cout << "	all possible valid switches are:\n";
	cout << "\n-t		type of file system";
	cout << "\n-b		total number of block in the file system";
	cout << "\n-s		maximum number of characters to be used in a filename\n";
}

int main()
{
	// int count = 3;
	string prompt = "cwushell> ";
	char *token;

	struct stat fileInfo;

	while (true)
	{
		cout << prompt;
		char input[MAXIMUM];
		// print prompt and get input from user
		cin.getline(input, MAXIMUM);
		cout << endl;

		// tokenize input
		token = strtok(input, " ");

		// convert first token into string and remove spaces
		string command;
		command = input;
		command = removeSpace(command);

		// clear command
		if (command == "clear")
		{
			// clear the page if no token left
			token = strtok(NULL, " ");
			if (token == NULL)
			{
				cout << "\033[H\033[J";
			}
			else
			{
				string arg = token;
				arg = removeSpace(arg);
				// call clear help
				if (arg == "-h" || arg == "-help")
				{
					clear_man();
					continue;
				}

				cout << " --- no argument needed,\n did you mean 'clear'? (y/n): ";
				string clear;
				cin >> clear;

				if (clear == "y" || clear == "Y")
					cout << "\033[H\033[J";

				else
				{
					continue;
				}
			}
		}

		else if (command == "exit")
		{

			token = strtok(NULL, " ");

			// if argument is provided
			if (token != NULL)
			{

				string str = token;
				str = removeSpace(str);

				if (str == "-h" || str == "-help")
				{
					exit_man();
					continue;
				}

				// checks if argument contains non digits
				int flag = 0;
				bool negative = false;
				for (int i = 0; i < str.length(); i++)
				{
					if (!isdigit(str[i]))
					{
						if (i == 0 && str[i] == '-')
						{
							negative = true;
							continue;
						}
						cout << " Error: only numeric argument is allowed";
						flag = 1;
						break;
					}
				}

				if (flag == 1)
				{
					continue;
				}

				int val;
				if (negative)
				{
					str = str.substr(1, str.length());
					val = stoi(str);
					val = val * -1;
				}
				else
				{
					val = stoi(str);
				}
				return val;
			}

			else
			{
				break;
			}
		}
		// prompt command
		else if (command == "prompt")
		{
			// if argument is provided
			token = strtok(NULL, " ");
			if (token != NULL)
			{
				string arg = token;
				arg = removeSpace(arg);

				// calls prompt help
				if (arg == "-h" || arg == "-help")
				{
					prompt_man();
					continue;
				}

				// updates new prompt
				prompt = arg + "> ";
			}

			else
			{
				prompt = "cwushell> ";
			}
		}

		// fileinfo command
		else if (command == "fileinfo")
		{
			string fName;
			struct stat fileInfo;
			string arg;

			// check if switch is provided
			token = strtok(NULL, " ");
			if (token != NULL)
			{
				arg = token;
				arg = removeSpace(arg);

				// checking if file is provided
				token = strtok(NULL, " ");
				if (token != NULL)
				{
					fName = token;
					fName = removeSpace(fName);
					// calls fileinfo help
					if (fName == "-h" || fName == "-help")
					{
						fileinfo_man();
						continue;
					}
					// check if file exist
					if (stat(fName.c_str(), &fileInfo) != 0)
					{
						cout << "Error: No such file or directory\n";

						continue;
					}
				}
				// calls fileinfo help
				else if (arg == "-h" || arg == "-help")
				{
					fileinfo_man();
					continue;
				}

				else
				{
					// display all info if no specific switch
					if (stat(arg.c_str(), &fileInfo) == 0)
					{
						funT(fileInfo);
						funI(fileInfo);
						funM(fileInfo);
						continue;
					}
					cout << " Error: filename expected \n";
					cout << "See 'fileinfo -help'\n";
					continue;
				}

				if (arg == "-t")
				{
					funT(fileInfo);
				}
				else if (arg == "-i")
				{
					funI(fileInfo);
				}
				else if (arg == "-m")
				{
					funM(fileInfo);
				}

				else
				{
					cout << "\n--no such argument--\n";
					cout << "See 'fileinfo -help'\n";
				}
			}

			// if no specific switch
			else
			{
				cout << "--arguments required--\n";
				cout << "See 'fileinfo -help'\n";
			}
		}

		// osifo commmand
		else if (command == "osifo")
		{
			struct statfs sbuf;
			struct statvfs buf;
			string arg;
			// if switch provided
			token = strtok(NULL, " ");
			if (token != NULL)
			{
				// check if statvs fails
				if (statvfs(".", &buf) == -1)
				{
					perror("statvfs() error");
				}

				arg = token;
				arg = removeSpace(arg);

				if (arg == "-t")
				{
					fileType(sbuf);
				}
				else if (arg == "-b")
				{
					cout << " total blocks: 		" << buf.f_blocks << endl;
				}
				else if (arg == "-s")
				{
					cout << " maximum name length: 	" << buf.f_namemax << endl;
				}

				else if (arg == "-h" || arg == "-help")
				{
					osifo_man();
				}
				else
				{
					cout << "-- no such argument --\n";
					cout << "see 'osifo -help'\n";
				}
			}
			else
			{
				fileType(sbuf);
				cout << "total blocks:		" << buf.f_blocks << endl;
				cout << "maximum name length: 	" << buf.f_namemax << endl;
			}
		}

		// man command
		else if (command == "man")
		{
			string arg;
			token = strtok(NULL, " ");
			string newInput;
			if (token == NULL)
			{
				cout << "What manual page do you want? ";
				cin >> newInput;
				arg = newInput;
			}
			else
			{
				arg = token;
			}
			arg = removeSpace(arg);
			if (arg == "exit")
			{
				exit_man();
			}
			else if (arg == "clear")
			{
				clear_man();
			}
			else if (arg == "prompt")
			{
				prompt_man();
			}
			else if (arg == "fileinfo")
			{
				fileinfo_man();
			}
			else if (arg == "osifo")
			{
				osifo_man();
			}

			else
			{

				cout << "\nNo manual entry for " << arg << "\n";
			}
		}

		// every other commands
		else
		{
			system(input);
		}
	}

	return 0;
}
