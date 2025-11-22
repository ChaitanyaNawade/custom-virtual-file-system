////////////////////////////////////////////////////////////////////////////////
//
//Header Fiele Inclusion
//
///////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
// #include<unistd.h>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
//
//User Defined Macros
//
///////////////////////////////////////////////////////////////////////////////

# define MAXFILESIZE 100
# define MAXINODE 5

# define READ 1
# define WRITE 2
# define EXECUTE 4

# define REGULARFILE 1
# define SPECIALFILE 2

# define START 0
# define CURRENT 1
# define END 2

////////////////////////////////////////////////////////////////////////////////
//
//User Defined Macros for error handling
//
///////////////////////////////////////////////////////////////////////////////

# define ERR_INVALID_PARAMETERS -1
# define ERR_NO_INODES -2
# define ERR_FILE_ALREADY_EXISTS -3

//////////////////////////////////////////////////////////////////////////////
//
//Structre Name : BootBlock
//Description :   Holds information to boot the operating system
//
//////////////////////////////////////////////////////////////////////////////

struct BootBlock
{
    char Information[100];
};



//////////////////////////////////////////////////////////////////////////////
//
//Structre Name : SuperBlock
//Description :   Holds information about the file system
//
//////////////////////////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};


//////////////////////////////////////////////////////////////////////////////
//
//Structre Name : Inode
//Description :   Holds information about the file 
//
//////////////////////////////////////////////////////////////////////////////

typedef struct Inode
{
    char Filename[50];
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int FileType;
    int ReferenceCount;
    int Permission;
    int LinkCount;
    char *Buffer;
    struct Inode *next;
}INODE,*PINODE,**PPINODE;



//////////////////////////////////////////////////////////////////////////////
//
//Structre Name : FileTable
//Description :   Holds information about the opened file
//
//////////////////////////////////////////////////////////////////////////////


typedef struct FileTable
{
    int REadOffset;
    int WriteOffset;
    int Count;
    int Mode;
    PINODE ptrinode;

}FILETABLE,*PFILETABLE;


//////////////////////////////////////////////////////////////////////////////
//
//Structre Name : UAREA
//Description :   Holds information about the Process
//
//////////////////////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[50];
    PFILETABLE UFDT[MAXINODE];
};


//////////////////////////////////////////////////////////////////////////////
//
//Global variables for object used in the projcet
//
//////////////////////////////////////////////////////////////////////////////
SuperBlock superobj;
PINODE head = NULL;
UAREA uareaobj;
BootBlock bootobj;


//////////////////////////////////////////////////////////////////////////////
//
//Function Name : InitialisUAREA
//Description : Ir is used to initiaxlie the contents of super UFDT
//Author :       
//Date :
//////////////////////////////////////////////////////////////////////////////

void InitialisUAREA()
{
    strcpy(uareaobj.ProcessName,"Myexe");

    int i = 0;
     while( i < MAXINODE)
     {
        uareaobj.UFDT[i] = NULL;
        i++;
     }
     cout<<"Marvellos CVFS : UAREAD  Initialized succussfully\n";
}


//////////////////////////////////////////////////////////////////////////////
//
//Function Name : InitialiseSuperblock
//Description : Ir is used to initialiase the contents of super block
//Author :       
//Date :
//////////////////////////////////////////////////////////////////////////////

void InitialiseSuperblock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    cout<<"Marvellos CVFS : DILS  created succussfully\n";

}

//////////////////////////////////////////////////////////////////////////////
//
//Function Name : CreateDILB
//Description : It is used to create Linked List of iNODs
//Author :       
//Date :
//////////////////////////////////////////////////////////////////////////////


void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    while(i <= MAXINODE)
    {
        newn = new INODE;
        newn ->InodeNumber = i;
        newn ->FileSize = 0;
        newn ->ActualFileSize = 0;
        newn ->LinkCount= 0;
        newn ->Permission = 0;
        newn ->Buffer = NULL;
        newn ->next = NULL;

        if(temp == NULL)
        {
            head  = newn;
            temp = head;
        }
        else 
        {
            temp ->next = newn;
            temp = temp ->next;
        }
        i++;
    }

    cout<<"Marvellos CVFS : CreateDILB data  created succussfully\n";
}


//////////////////////////////////////////////////////////////////////////////
//
//Function Name : StartAuxillaryDataInitialisation
//Description : It is used to initialise the Auxilarry  data
//Author :       
//Date :
//////////////////////////////////////////////////////////////////////////////

void StartAuxillaryDataInitialisation()
{
    strcpy(bootobj.Information,"Boot process of Operating System done\n");

    cout<<bootobj.Information<<"\n";

    CreateDILB();

    InitialiseSuperblock();

    InitialisUAREA();
}


//////////////////////////////////////////////////////////////////////////////
//
//Function Name : DisplayHelp
//Description :   It is used to Display the information aobut commands
//Author :       
//Date :          11 
//////////////////////////////////////////////////////////////////////////////

void DisplayHelp()
{
    printf("___________________________________________________________________\n");
    printf("______________________Command manual of marvellous CVFS____________\n");
    printf("___________________________________________________________________\n");
;
    printf("It is used to terminate the shell of marvellous CVFS\n");
    printf("It is used to clear the console of marvellous cvfs\n");

    printf("___________________________________________________________________\n");
}


//////////////////////////////////////////////////////////////////////////////
//
//Function Name :    ManPage
//Description :      It is used to Display the manual page of the commands
//Input :            It Accepts The Command Name
//Output :           Displays the manual details of the command
//Author :       
//Date :             11/08/2025 
//////////////////////////////////////////////////////////////////////////////


void ManPage(
    char *name //Name of command
             )
{
    if(strcmp(name,"creat") == 0)
    {
        printf("Description : This command is used to create new regular file on our file system\n");

        printf("Usage : Create File_Name Permissions\n");
        printf("File_name : the namae of file that you want to create\n");
        printf("Permissions : \n1 : read , \n2 : write , \n3 : read and write\n");
    }
    else if(strcmp(name,"exit") == 0)
    {
        printf("Description : This command is used to terminate Marvellous CVFS\n");

        printf("usage : exit\n");
    }

    //Add more options here
    else 
    {
        printf("No manual entry for %s",name);
    }
}


//////////////////////////////////////////////////////////////////////////////
//
//Function Name :    IsFileExist
//Description :      It is used to check whether the given file  name is exist or not
//Input :            It Accepts The file name 
//Output :           It returns boolean value (True : if present  false : if not present)
//Author :       
//Date :             11/08/2025 
//////////////////////////////////////////////////////////////////////////////

bool IsFileExist(
    char *name  //Name of file that we want to check
                )
{
    PINODE temp = head;
    bool bFlag = false;

    while(temp != NULL)
    {
        if(temp->FileType != 0)
        {
            if((strcmp(name,temp->Filename) == 0)  && (temp ->FileType == REGULARFILE))
            {
                bFlag = true;
                break;
            }
        }

        temp = temp ->next;
    }
    return bFlag;
}


//////////////////////////////////////////////////////////////////////////////
//
//Function Name :    CreateFile
//Description :      It is used to create a new regular file
//Input :            It Accepts The file name and permission
//Output :           It Displays the file descritpor
//Author :       
//Date :             11/08/2025 
//////////////////////////////////////////////////////////////////////////////

int CreateFile(
    char *name,   // Name of File
     int permission  //Permission to create file
               )
{
    PINODE temp = head;
    int i  = 0;
     //Filters


    //if file name is missing
 if(name == NULL)
 {
    return ERR_INVALID_PARAMETERS;
 }   

   //if Entered permission is invalid
 if(permission < 1 || permission > 3)
 {
    return ERR_INVALID_PARAMETERS;
 }

 //Check whether empty inode is there or not
 if(superobj.FreeInodes == 0)
 {
    return ERR_NO_INODES;
 }

  //Check whether File is already exits or not

 if(IsFileExist(name) == true)
 {
    return ERR_FILE_ALREADY_EXISTS;
 }


 //Loop to search inode
 
 while (temp != NULL)
 {
    if(temp ->FileType == 0)
    {
        break;
    }
    temp = temp ->next;
 }
 
//Inode not found
 if(temp == NULL)
 {
    printf("Inode not found\n");
    return -1;
 }

 // Search first non null from UFDT 
 for( i = 0; i < MAXINODE ; i++)
 {
    if(uareaobj.UFDT == NULL)
    {
        break;
    }
 }

 if(i == MAXINODE)
 {
    printf("Unable to create file as MAX OPENED file limit Reahed\n");
    return -1;
 }

 //Initialize elements of file table
 uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FILETABLE));

//Initialze elements of false table
 uareaobj.UFDT[i]->REadOffset = 0;
 uareaobj.UFDT[i]->WriteOffset = 0;
 uareaobj.UFDT[i]->Count =1;
 uareaobj.UFDT[i]->Mode = permission;

 //Connect file table with IIT
 uareaobj.UFDT[i]->ptrinode = temp;

 strcpy(uareaobj.UFDT[i]->ptrinode->Filename,name);

 uareaobj.UFDT[i]->ptrinode->FileSize = MAXFILESIZE;

 uareaobj.UFDT[i]->ptrinode->ActualFileSize  = 0;
 uareaobj.UFDT[i]->ptrinode->FileType = REGULARFILE;
 uareaobj.UFDT[i]->ptrinode->ReferenceCount = 1;
 uareaobj.UFDT[i]->ptrinode->LinkCount = 1;
 uareaobj.UFDT[i]->ptrinode->Permission = permission;


 //Allocate memory for buffer
uareaobj.UFDT[i]->ptrinode->Buffer = (char *) malloc(MAXFILESIZE);

return i;
}




////////////////////////////////////////////////////////////////////////////////
//
//Entry point function of project (main)
//
///////////////////////////////////////////////////////////////////////////////

int main()
{
    int iRet = 0;
    char str[80] = {'\0'};
    int iCount = 0;
    char Command[5][80];

    StartAuxillaryDataInitialisation(); 

    cout<<"______________________________________________________________________________________________\n";
    cout<<"______________________________Marvellous CVFS Started Successfully____________________________\n";
    cout<<"______________________________________________________________________________________________\n";


    while(1)   //shell
    {
        fflush(stdin);

        printf("\nMarvellous CVFS>");
        fgets(str,sizeof(str),stdin);

        iCount = sscanf(str,"%s %s %s %s",Command[0],Command[1],Command[2],Command[3]);
        
        if(iCount == 1)
        {
            if(strcmp(Command[0],"exit") == 0)
            {
                printf("thank you for using marvellous CVFS\n");
                printf("Deallocating all resources...\n");

                break;
            }

             //Marvellous CVFS >HELP
            else if(strcmp(Command[0],"Help") == 0)
            {
                DisplayHelp();
            }
           
             //Marvellous CVFS >cls
            else if(strcmp(Command[0],"clear") == 0)
            {
                system("cls");
            }

        }//End of if iCount == 1


        else if(iCount == 2)
        {
            //Marvellous CVFS >Man

            if(strcmp(Command[0],"man") == 0)
            {
                ManPage(Command[1]);
            }
        }//End of if iCount == 2


        else if(iCount == 3)
        {

            //Marvellous CVFS creat Ganesh.txt 3

            if(strcmp(Command[0],"creat") == 0)
            {
                iRet = CreateFile(Command[1],atoi(Command[2]));

                if(iRet == ERR_INVALID_PARAMETERS)
                {
                    printf("Error : Invalid paramters for the function\n");
                    printf("Please check man page for more details\n");
                }

                else if(iRet == ERR_NO_INODES)
                {
                    printf("Error : Unable to create file as there is no inodes\n");
                }
            }


            else if(iRet == ERR_FILE_ALREADY_EXISTS)
            {
                printf("Error : Unable to create file as file is already exits\n");
            }
            else 
            {
                printf("File is successfully created with FD : %d\n",iRet);
            }

        }//End of if iCount == 3


        else if(iCount == 4)
        {

        }//End of if iCount == 4


        else
        {
            printf("Command not found\n");
            printf("Please refer Help option or man command\n");
        }//End of invalid command part

    }//End of while(Custom Shell)

    return 0;
} //End of main