#include "DeployWin.h"
#ifdef WIN32
#include "windows.h"
#endif // WIN32

int main()
{
    if(DeployWinIsRunning())
    {
#ifdef WIN32
        //����MessageBox���Զ�����һЩdll
        MessageBoxA(NULL,"this is a messagebox","test",MB_OK|MB_SYSTEMMODAL);
#endif // WIN32
        printf("pause any key to exit!\n");
        getchar();
    }
    else
    {
        printf("DeployWin is not running!\n");
    }

    return 0;
}
