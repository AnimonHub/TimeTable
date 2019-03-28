#include "winorlinux.h"

WinOrLinux::WinOrLinux()
{

}

QString WinOrLinux::returnPathForDb()
{
#if defined (Q_OS_LINUX)
    return QString("/home/animon/spravochnikSubject.db");
#elif defined (Q_OS_WIN32)
    return QString("C:\\Users\\spravochnikSubject.db");
#endif
}
