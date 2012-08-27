// acupdater.cc
// 8/16/2012

#include "project/common/acupdater.h"
#include "project/common/acglobal.h"
#include "project/common/acipc.h"

#define APP_NAME        AC_UPDATER
#define APP_ID          AC_UPDATER_ID

#ifdef Q_OS_WIN
# define APP_PATH       "../[ Update ]"
#else
# define APP_PATH       APP_NAME
#endif // Q_OS_WIN

// - Queries -

bool
AcUpdater::isRunning() const
{ return AcIpcController::isProcessRunning(APP_NAME); }

// - Actions -

void
AcUpdater::open()
{ AcIpcController::open(APP_PATH); }

void
AcUpdater::openArguments(const QStringList &args)
{ AcIpcController::open(APP_PATH, args); }

// EOF
