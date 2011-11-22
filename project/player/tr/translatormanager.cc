// translatormanager.cc
// 9/16/2011

#include "translatormanager.h"
#include "tr.h"
#include "rc.h" // This breaks the modularity of this pri
#include <QtCore>

// - Constructions -

// Use C as an invalid entry
namespace { enum { INVALID_LANGUAGE = 0 }; }

int TranslatorManager::language_ = INVALID_LANGUAGE;

TranslatorManager*
TranslatorManager::globalInstance()
{ static Self global; return &global; }

TranslatorManager::TranslatorManager(QObject *parent)
  : Base(parent),
    tr_en_(0), tr_ja_(0), tr_tw_(0), tr_zh_(0)
{
  //setLanguage(QLocale::system().language());
}

int
TranslatorManager::language() const
{ return language_; }

void
TranslatorManager::setLanguage(int language, bool updateTranslator)
{
  if (language_ != language) {
    if (updateTranslator)
      removeCurrentTranslator(qApp);
    language_ = language;
    if (updateTranslator)
      installCurrentTranslator(qApp);

    emit languageChanged();
  }
}

#define MAKE_TRANSLATOR(_tr, _TR) \
  QTranslator* \
  TranslatorManager::tr_##_tr() const \
  { \
    if (!tr_##_tr##_) { \
      tr_##_tr##_ = new QTranslator(const_cast<Self*>(this)); \
      tr_##_tr##_->load(RC_TR_##_TR); \
    } \
    return tr_##_tr##_; \
  }

  MAKE_TRANSLATOR(en, EN)
  MAKE_TRANSLATOR(ja, JA)
  MAKE_TRANSLATOR(tw, TW)
  MAKE_TRANSLATOR(zh, ZH)

#undef MAKE_TRANSLATOR

QTranslator*
TranslatorManager::currentTranslatorManager() const
{
  switch (language_) {
  case INVALID_LANGUAGE:   return 0;
  case QLocale::English:   return tr_en();
  case QLocale::Japanese:  return tr_ja();
  case TraditionalChinese: return tr_tw();
  case QLocale::Chinese:   return tr_zh();
  default: return tr_en();
  }
}

void
TranslatorManager::installCurrentTranslator(QCoreApplication *a)
{
  if (a) {
    QTranslator *t = currentTranslatorManager();
    if (t)
      a->installTranslator(t);
  }
}

void
TranslatorManager::removeCurrentTranslator(QCoreApplication *a)
{
  if (a) {
    QTranslator *t = currentTranslatorManager();
    if (t)
      a->removeTranslator(t);
  }
}

// - Translations -

QString
TranslatorManager::translate(int tid) const
{
#define SELF(_t)      translate(_t)
  switch (tid) {
  case T_NULL:          return QString();

  case T_WINDOWS:       return tr("Windows");
  case T_BLACKLIST:     return tr("Blacklist");
  case T_DEFAULT:       return tr("Default");
  case T_RANDOM:        return tr("Random");
  case T_POSITION:      return tr("Progress");
  case T_VOLUME:        return tr("Volume");
  case T_USER:          return tr("User");
  case T_LOGIN:         return tr("Login");
  case T_OK:            return tr("OK");
  case T_SAVE:          return tr("Save");
  case T_CANCEL:        return tr("Cancel");
  case T_ADD:           return tr("Add");
  case T_REMOVE:        return tr("Remove");
  case T_ENABLE:        return tr("Enable");
  case T_CLEAR:         return tr("Clear");
  case T_MENU:          return tr("Menu");
  case T_HTML:          return tr("HTML");
  case T_RICH:          return tr("Rich");
  case T_CODE:          return tr("Code");
  case T_TIMESLOT:      return tr("Slot");
  case T_PREVIOUS:      return tr("Previous");
  case T_NEXT:          return tr("Next");
  case T_VERBATIM:      return tr("Verbatim");
  case T_SUBTITLE:      return tr("Subtitle");
  case T_SECTION:       return tr("Section");
  case T_WORDCOUNT:     return tr("Word count");
  case T_UNKNOWN:       return tr("unknown");
  case T_BLESS:         return tr("Bless");
  case T_CURSE:         return tr("Curse");
  case T_BLOCK:         return tr("Block");

  case T_COLOR:         return tr("Color");
  case T_FOREGROUNDCOLOR: return tr("Foreground color");
  case T_BACKGROUNDCOLOR: return tr("Background color");
  case T_BOLD:          return tr("Bold");
  case T_STRIKEOUT:     return tr("Strike out");
  case T_ITALIC:        return tr("Italic");
  case T_UNDERLINE:     return tr("Underline");

  case T_BLACK:         return tr("Black");
  case T_BLUE:          return tr("Blue");
  case T_BROWN:         return tr("Brown");
  case T_CYAN:          return tr("Cyan");
  case T_GRAY:          return tr("Gray");
  case T_GREEN:         return tr("Green");
  case T_MAGENTA:       return tr("Magenta");
  case T_ORANGE:        return tr("Orange");
  case T_PINK:          return tr("Pink");
  case T_PURPLE:        return tr("Purple");
  case T_RED:           return tr("Red");
  case T_WHITE:         return tr("White");
  case T_YELLOW:        return tr("Yellow");
  case T_LIGHTBLUE:     return tr("Light blue");

  case T_ALIEN:         return tr("Alien");
  case T_ENGLISH:       return tr("English");
  case T_JAPANESE:      return tr("Japanese");
  case T_CHINESE:       return tr("Chinese");
  case T_TRADITIONALCHINESE: return tr("Traditional Chinese");
  case T_SIMPLIFIEDCHINESE:  return tr("Simplified Chinese");
  case T_KOREAN:        return tr("Korean");

  case T_ATTACH:        return tr("Attach");
  case T_DETACH:        return tr("Detach");
  case T_ATTACHED:      return tr("Attached");
  case T_DETACHED:      return tr("Detached");
  case T_REFRESH:       return tr("Refresh");
  case T_RESET:         return tr("Reset");

  // Defaults:
  case T_DEFAULT_USERNAME:      return "yin";
  case T_DEFAULT_PASSWORD:      return "pandora";

  // Titles:

  case T_TITLE_PROGRAM:         return tr("Annot Player");
  case T_TITLE_USER:            return tr("User");
  case T_TITLE_LOGIN:           return tr("Login");
  case T_TITLE_SEEK:            return tr("Seek");

  case T_TITLE_OPENFILE:        return tr("Open media file");
  case T_TITLE_OPENDEVICE:      return tr("Open media device");
  case T_TITLE_OPENSUBTITLE:    return tr("Open subtitle");
  case T_TITLE_ANNOTATIONBROWSER:       return tr("Annots");
  case T_TITLE_ANNOTATIONEDITOR:        return tr("Annot Editor");
  case T_TITLE_TOKENVIEW:       return tr("Token");
  case T_TITLE_COMMENTVIEW:     return tr("Comments");
  case T_TITLE_CLOUDVIEW:       return tr("Annot Cloud");
  case T_TITLE_SIGNALVIEW:      return tr("Select process signal");
  case T_TITLE_LIVE:            return tr("Live Mode");
  case T_TITLE_SYNC:            return tr("Sync Mode");

  // Messages:

  case T_ERROR_UNKNOWN_COMMAND:         return tr("unrecognized command");
  case T_ERROR_SNAPSHOT_FAILED:         return tr("failed to take snapshots");
  case T_ERROR_HASH_TOKEN:              return tr("failed to hash token");
  case T_ERROR_BAD_USERNAME:            return tr("invalid username");
  case T_ERROR_BAD_PASSWORD:            return tr("invalid password");
  case T_ERROR_BAD_POS:                 return tr("invalid time format");
  case T_ERROR_BAD_TOKEN:               return tr("invalid token");
  case T_ERROR_BAD_DEVICEPATH:          return tr("invalid device path");
  case T_ERROR_BAD_FILEPATH:            return tr("file not existed");
  case T_ERROR_BAD_SUBTITLE:            return tr("failed to load subtitle");
  case T_ERROR_CLIPBOARD_UNAVAILABLE:   return tr("clipboard not available");
  case T_ERROR_SUBMIT_TOKEN:            return tr("failed to submit token");
  case T_ERROR_SUBMIT_ANNOTATION:       return tr("failed to submit annotation");
  case T_ERROR_SYNC_FAILURE:            return tr("failed to synchronize offline queue,:return try later");

  case T_SUCCEED_SNAPSHOT_SAVED:        return tr("snapshot saved on desktop");
  case T_SUCCEED_ANNOTATION_COPIED:     return tr("comment copied to clipboard");

  case T_WARNING_LONG_STRING_TRUNCATED:  return tr("long string got truncated");
  case T_MESSAGE_ENABLE_WINDOWSTAYSONTOP:       return tr("window always on top");

  case T_MESSAGE_TRY_LOGINFROMCACHE:    return tr("try to get user information from cache");
  case T_SUCCEED_LOGINFROMCACHE:        return tr("succeeded to login user from cache");
  case T_ERROR_LOGINFROMCACHE_FAILURE:  return tr("failed to login user from cache");

  // Widgets:
  case T_USERNAME:              return tr("Username");
  case T_PASSWORD:              return tr("Password");

  case T_TOOLTIP_ANNOTATIONITEM:return tr("Comment"); // TO BE GENERATED DYNAMICALL
  case T_TOOLTIP_COMMANDLINE:   return tr("Input command");
  case T_TOOLTIP_PREFIXLINE:    return tr("Input prefix");

  case T_SEEK:                  return tr("Seek");

  // Formats:
  case T_FORMAT_ALL:            return tr("All files");
  case T_FORMAT_SUPPORTED:      return tr("All supported");
  case T_FORMAT_VIDEO:          return tr("Video");
  case T_FORMAT_AUDIO:          return tr("Audio");
  case T_FORMAT_PICTURE:        return tr("Picture");
  case T_FORMAT_SUBTITLE:       return tr("Subtitle");
  case T_FORMAT_PROGRAM:        return tr("Program");

  // Actions:

  case T_MENUTEXT_OPEN:         return tr("Open");
  case T_TIP_OPEN:              return tr("Open media file or game process");

  case T_MENUTEXT_OPENFILE:     return tr("Open file");
  case T_TIP_OPENFILE:          return tr("Open media file");

  case T_MENUTEXT_OPENDEVICE:   return tr("Open CD/DVD");
  case T_TIP_OPENDEVICE:        return tr("Open media device");

  case T_MENUTEXT_OPENSUBTITLE: return tr("Open subtitle");
  case T_TIP_OPENSUBTITLE:      return tr("Load subtitle from file");

  case T_MENUTEXT_OPENCONTEXTMENU: return tr("Open ...");
  case T_TIP_OPENCONTEXTMENU:      return tr("Open ...");

  case T_MENUTEXT_PLAY:         return tr("Play");
  case T_TIP_PLAY:              return tr("Play media");

  case T_MENUTEXT_MENU:         return tr("Menu");
  case T_TIP_MENU:              return tr("Show menu");

  case T_MENUTEXT_PAUSE:        return tr("Pause");
  case T_TIP_PAUSE:             return tr("Pause playing");

  case T_MENUTEXT_STOP:         return tr("Stop");
  case T_TIP_STOP:              return tr("Stop playing");

  case T_MENUTEXT_NEXTFRAME:    return tr("Next frame");
  case T_TIP_NEXTFRAME:         return tr("Next frame");

  case T_MENUTEXT_REPLAY:       return tr("Replay");
  case T_TIP_REPLAY:            return tr("Restart playing");

  case T_MENUTEXT_MINI:         return tr("Mini player");
  case T_TIP_MINI:              return tr("Show mini player");

  case T_MENUTEXT_LIVE:         return tr("Live mode");
  case T_TIP_LIVE:              return tr("Toggle live mode");

  case T_MENUTEXT_SYNC:         return tr("Sync mode");
  case T_TIP_SYNC:              return tr("Toggle Sync mode");

  case T_MENUTEXT_FULLSCREEN:   return tr("Fullscreen");
  case T_TIP_FULLSCREEN:        return tr("Show fullscreen");

  case T_MENUTEXT_SNAPSHOT:     return tr("Snapshot");
  case T_TIP_SNAPSHOT:          return tr("Taks a snapshot of current frame");

  case T_MENUTEXT_ANNOT:        return tr("Toggle annot");
  case T_TIP_ANNOT:             return tr("Toggle annotations");
  case T_MENUTEXT_SHOWANNOT:    return tr("Show annots");
  case T_TIP_SHOWANNOT:         return tr("Show annots");
  case T_MENUTEXT_HIDEANNOT:    return tr("Hide annots");
  case T_TIP_HIDEANNOT:         return tr("Hide annotations");

  case T_MENUTEXT_QUIT:         return tr("Exit");
  case T_TIP_QUIT:              return tr("Quit the application");

  case T_MENUTEXT_USER:         return tr("User panel");
  case T_TIP_USER:              return tr("Show user panel");

  case T_MENUTEXT_SEEK:         return tr("Seek");
  case T_TIP_SEEK:              return tr("Seek position");

  case T_MENUTEXT_LOGIN:        return tr("Login");
  case T_TIP_LOGIN:             return tr("Show login dialog");

  case T_MENUTEXT_LOGOUT:       return tr("Logout");
  case T_TIP_LOGOUT:            return tr("Logout");

  case T_MENUTEXT_LOGINDIALOG:  return tr("Login");
  case T_TIP_LOGINDIALOG:       return tr("Show login dialog");

  case T_MENUTEXT_LIVEDIALOG:   return tr("Choose live time");
  case T_TIP_LIVEDIALOG:        return tr("Show live mode dialog");

  case T_MENUTEXT_SYNCDIALOG:   return tr("Choose sync time");
  case T_TIP_SYNCDIALOG:        return tr("Show sync mode dialog");

  case T_MENUTEXT_SEEKDIALOG:   return tr("Seek");
  case T_TIP_SEEKDIALOG:        return tr("Show seek dialog");

  case T_MENUTEXT_PICKDIALOG:   return tr("Pick window");
  case T_TIP_PICKDIALOG:        return tr("Show pick dialog");

  case T_MENUTEXT_PROCESSPICKDIALOG:   return tr("Open window");
  case T_TIP_PROCESSPICKDIALOG:        return tr("Select process window");

  case T_MENUTEXT_WINDOWPICKDIALOG:   return tr("Select annots window");
  case T_TIP_WINDOWPICKDIALOG:        return tr("Select window to show annots");

  case T_TITLE_ABOUT:           return tr("About");
  case T_MENUTEXT_ABOUT:        return tr("About");
  case T_TIP_ABOUT:             return tr("About us");

  case T_TITLE_HELP:            return tr("Help");
  case T_MENUTEXT_HELP:         return tr("Help");
  case T_TIP_HELP:              return tr("Help");

  case T_MENUTEXT_COPY:         return tr("Copy");
  case T_TIP_COPY:              return tr("Copy");

  case T_MENUTEXT_PASTE:        return tr("Paste");
  case T_TIP_PASTE:             return tr("Paste");

  case T_MENUTEXT_SUBTITLE:     return tr("Subtitle");
  case T_TIP_SUBTITLE:          return tr("Subtitle");

  case T_MENUTEXT_SECTION:      return tr("DVD sections");
  case T_TIP_SECTION:           return tr("Select DVD sections");

  case T_MENUTEXT_SHOWSUBTITLE: return tr("Show subtitle");
  case T_TIP_SHOWSUBTITLE:      return tr("Show subtitle");

  case T_MENUTEXT_HIDESUBTITLE: return tr("Hide subtitle");
  case T_TIP_HIDESUBTITLE:      return tr("Hide subtitle");

  case T_MENUTEXT_REMOVEANNOTATION:   return tr("Hide");
  case T_TIP_REMOVEANNOTATION:        return tr("Hide");

  case T_MENUTEXT_ENABLEAUTOCLEARCONSOLE: return tr("Auto clear console");
  case T_TIP_ENABLEAUTOCLEARCONSOLE:      return tr("Enable auto clear console");

  case T_MENUTEXT_DISABLEAUTOCLEARCONSOLE: return tr("Stick console");
  case T_TIP_DISABLEAUTOCLEARCONSOLE:      return tr("Disable auto clear console");

  case T_MENUTEXT_WINDOWSTAYSONTOP:   return tr("Always on top");
  case T_TIP_WINDOWSTAYSONTOP:        return tr("Show window on top");

  case T_MENUTEXT_ADVANCED:     return tr("Advanced");
  case T_TIP_ADVANCED:          return tr("Advanced menu");

  case T_MENUTEXT_EDITTHISANNOT:return tr("Edit annot");
  case T_TIP_EDITTHISANNOT:     return tr("Edit annotation");

  case T_MENUTEXT_BLOCKTHISANNOT:return tr("Block annot");
  case T_TIP_BLOCKTHISANNOT:    return tr("Block annotation");

  case T_MENUTEXT_BLESSTHISANNOT:return tr("Bless annot");
  case T_TIP_BLESSTHISANNOT:    return tr("Bless annotation");

  case T_MENUTEXT_CURSETHISANNOT:return tr("Curse annot");
  case T_TIP_CURSETHISANNOT:    return tr("Curse annotation");

  case T_MENUTEXT_BLESSTHISTOKEN:return tr("Bless token");
  case T_TIP_BLESSTHISTOKEN:    return tr("Bless token");

  case T_MENUTEXT_CURSETHISTOKEN:return tr("Curse token");
  case T_TIP_CURSETHISTOKEN:    return tr("Curse token");

  case T_MENUTEXT_HIDETHISANNOT:return tr("Hide annot");
  case T_TIP_HIDETHISANNOT:     return tr("Hide annotation");

  case T_MENUTEXT_SHOWTHISANNOT:return tr("Show annot");
  case T_TIP_SHOWTHISANNOT:     return tr("Show annotation");

  case T_MENUTEXT_COPYTHISANNOT:return tr("Copy annot");
  case T_TIP_COPYTHISANNOT:     return tr("Copy annotation");

  case T_MENUTEXT_VIEWTHISUSER: return tr("Display user");
  case T_TIP_VIEWTHISUSER:      return tr("Display user");

  case T_MENUTEXT_BLOCKTHISUSER:return tr("Block user");
  case T_TIP_BLOCKTHISUSER:     return tr("Block user");

  case T_MENUTEXT_CLEARCACHE:   return tr("Clear offline cache");
  case T_TIP_CLEARCACHE:        return tr("Remove offline cache");

  case T_MENUTEXT_CONNECT:      return tr("Synchronize with server");
  case T_TIP_CONNECT:           return tr("Connect to server and synchronize local cache");
  case T_MENUTEXT_DISCONNECT:   return tr("Disconnect from server");
  case T_TIP_DISCONNECT:        return tr("Disconnect from server and use local cache only");

  case T_MENUTEXT_ANNOTATIONBROWSER: return tr("Annots");
  case T_TIP_ANNOTATIONBROWSER: return tr("Show annotation browser");

  case T_MENUTEXT_ANNOTATIONEDITOR: return tr("Annot editor");
  case T_TIP_ANNOTATIONEDITOR: return tr("Show annotation editor");

  case T_MENUTEXT_TOKENVIEW:    return tr("Token");
  case T_TIP_TOKENVIEW:         return tr("Show token view");

  case T_MENUTEXT_COMMENTVIEW:  return tr("Comments");
  case T_TIP_COMMENTVIEW:       return tr("Show comment browser");

  // case T_MENUTEXT_CLOUDVIEW:    return tr("Cloud");
  case T_MENUTEXT_CLOUDVIEW:    return tr("Register");
  case T_TIP_CLOUDVIEW:         return tr("Show cloud browser");

  case T_MENUTEXT_EDIT:         return tr("Edit");
  case T_TIP_EDIT:              return tr("Edit");

  case T_MENUTEXT_ADDALIAS:     return tr("Add alias");
  case T_TIP_ADDALIAS:          return tr("Add alias");

  case T_MENUTEXT_SIGNALVIEW:     return tr("Select process");
  case T_TIP_SIGNALVIEW:          return tr("Select process signal");

  case T_MENUTEXT_ATTACHPROCESS: return tr("Attach process");
  case T_TIP_ATTACHPROCESS:     return tr("Attach process");

  case T_MENUTEXT_DETACHPROCESS: return tr("Detach process");
  case T_TIP_DETACHPROCESS:     return tr("Detach process");

  case T_MENUTEXT_REFRESHPROCESS: return tr("Refresh process");
  case T_TIP_REFRESHPROCESS:    return tr("Refresh process");

  case T_MENUTEXT_RECENTMESSAGES: return tr("Select channel");
  case T_TIP_RECENTMESSAGES:    return tr("Select channel");

  case T_MENUTEXT_APPLANGUAGE:  return tr("Application language");
  case T_TIP_APPLANGUAGE:       return tr("Choose application language");

  case T_ANYLANGUAGE:           return tr("Any language");
  case T_MENUTEXT_ANYLANGUAGE:  return tr("All");
  case T_TIP_ANYLANGUAGE:       return tr("Choose all languages");

  case T_MENUTEXT_ANNOTATIONLANGUAGE:  return tr("Annot languages");
  case T_TIP_ANNOTATIONLANGUAGE:       return tr("Choose annotation language");

  case T_MENUTEXT_USERLANGUAGE:  return tr("User language");
  case T_TIP_USERLANGUAGE:       return tr("Choose user language");

  case T_MENUTEXT_ANONYMOUS:  return tr("Anonymous");
  case T_TIP_ANONYMOUS:       return tr("User anonymous");

  case T_MENUTEXT_TRANSLATE:  return tr("Show translation");
  case T_TIP_TRANSLATE:       return tr("Display translation");

  case T_MENUTEXT_SUBTITLEONTOP:  return tr("Subtitle on top");
  case T_TIP_SUBTITLEONTOP:       return tr("Display subtitle on the top/bottom");

  case T_MENUTEXT_SUBTITLESTYLE:  return tr("Subtitle color");
  case T_TIP_SUBTITLESTYLE:       return tr("Select subtitle color");

  case T_MENUTEXT_THEME:  return tr("Theme");
  case T_TIP_THEME:       return tr("Select GUI theme");

  case T_LABEL_CREATEDATE:      return tr("Create");
  case T_TIP_CREATEDATE:        return tr("Create date");
  case T_LABEL_UPDATEDATE:      return tr("Update");
  case T_TIP_UPDATEDATE:        return tr("Update date");
  case T_LABEL_BLESSEDCOUNT:    return tr("Blessed");
  case T_TIP_BLESSEDCOUNT:      return tr("Blessed count");
  case T_LABEL_CURSEDCOUNT:     return tr("Cursed");
  case T_TIP_CURSEDCOUNT:       return tr("Cursed count");
  case T_LABEL_BLOCKEDCOUNT:    return tr("Blocked");
  case T_TIP_BLOCKEDCOUNT:      return tr("Blocked count");
  case T_LABEL_VISITEDCOUNT:    return tr("Visited");
  case T_TIP_VISITEDCOUNT:      return tr("Visited count");
  case T_LABEL_ANNOTCOUNT:      return tr("Annot");
  case T_TIP_ANNOTCOUNT:        return tr("Annotation count");

  case T_LABEL_ALIAS:           return tr("Alias");
  case T_TIP_ALIAS:             return tr("Alias");

  case T_MENUTEXT_BACKWARD:     return tr("Backward");
  case T_MENUTEXT_FORWARD:      return tr("Forward");
  case T_MENUTEXT_FORWARD5S:    return tr("Forward 5 sec");
  case T_MENUTEXT_BACKWARD5S:   return tr("Backward 5 sec");
  case T_MENUTEXT_FORWARD10S:   return tr("Forward 10 sec");
  case T_MENUTEXT_BACKWARD10S:  return tr("Backward 10 sec");
  case T_MENUTEXT_FORWARD30S:   return tr("Forward 30 sec");
  case T_MENUTEXT_BACKWARD30S:  return tr("Backward 30 sec");
  case T_MENUTEXT_FORWARD60S:   return tr("Forward 60 sec");
  case T_MENUTEXT_BACKWARD60S:  return tr("Backward 60 sec");
  case T_MENUTEXT_FORWARD90S:   return tr("Forward 90 sec");
  case T_MENUTEXT_BACKWARD90S:  return tr("Backward 90 sec");
  case T_MENUTEXT_FORWARD1M:    return tr("Forward 1 min");
  case T_MENUTEXT_BACKWARD1M:   return tr("Backward 1 min");
  case T_MENUTEXT_FORWARD5M:    return tr("Forward 5 min");
  case T_MENUTEXT_BACKWARD5M:   return tr("Backward 5 min");
  case T_MENUTEXT_FORWARD10M:   return tr("Forward 10 min");
  case T_MENUTEXT_BACKWARD10M:  return tr("Backward 10 min");

  case T_MENUTEXT_RECENT:       return tr("Recent");
  case T_TIP_RECENT:            return tr("Recent file");
  case T_MENUTEXT_CLEARRECENT:  return tr("Clear");
  case T_TIP_CLEARRECENT:       return tr("Clear recent files");

  case T_MENUTEXT_BROWSE:      return tr("Browse");
  case T_TIP_BROWSE:           return tr("Files in the same folder");

  case T_MENUTEXT_BLACKTHEME1:  return SELF(T_BLACK) + "1";
  case T_MENUTEXT_BLACKTHEME2:  return SELF(T_BLACK) + "2";
  case T_MENUTEXT_BLUETHEME1:  return SELF(T_BLUE) + "1";
  case T_MENUTEXT_BLUETHEME2:  return SELF(T_BLUE) + "2";
  case T_MENUTEXT_BROWNTHEME1:  return SELF(T_BROWN) + "1";
  case T_MENUTEXT_BROWNTHEME2:  return SELF(T_BROWN) + "2";
  case T_MENUTEXT_GREENTHEME1:  return SELF(T_GREEN) + "1";
  case T_MENUTEXT_GREENTHEME2:  return SELF(T_GREEN) + "2";
  case T_MENUTEXT_LIGHTBLUETHEME1:  return SELF(T_LIGHTBLUE) + "1";
  case T_MENUTEXT_LIGHTBLUETHEME2:  return SELF(T_LIGHTBLUE) + "2";
  case T_MENUTEXT_ORANGETHEME1:  return SELF(T_ORANGE) + "1";
  case T_MENUTEXT_ORANGETHEME2:  return SELF(T_ORANGE) + "2";
  case T_MENUTEXT_PINKTHEME1:  return SELF(T_PINK) + "1";
  case T_MENUTEXT_PINKTHEME2:  return SELF(T_PINK) + "2";
  case T_MENUTEXT_PURPLETHEME1:  return SELF(T_PURPLE) + "1";
  case T_MENUTEXT_PURPLETHEME2:  return SELF(T_PURPLE) + "2";
  case T_MENUTEXT_REDTHEME1:  return SELF(T_RED) + "1";
  case T_MENUTEXT_REDTHEME2:  return SELF(T_RED) + "2";
  case T_MENUTEXT_YELLOWTHEME1:  return SELF(T_YELLOW) + "1";
  case T_MENUTEXT_YELLOWTHEME2:  return SELF(T_YELLOW) + "2";
  case T_MENUTEXT_WINDOWSTHEME1:  return SELF(T_WINDOWS) + "1";
  case T_MENUTEXT_WINDOWSTHEME2:  return SELF(T_WINDOWS) + "2";

  case T_FILTER_PATTERN:        return tr("Filter pattern");
  case T_FILTER_SYNTAX:         return tr("Filter syntax");
  case T_FILTER_COLUMN:         return tr("Filter column");
  case T_FILTER_REGEX:          return tr("Regular expression");
  case T_FILTER_WILDCARD:       return tr("Wildcard");
  case T_FILTER_FIXED:          return tr("Fixed string");

  case T_ID:            return tr("ID");
  case T_NAME:          return tr("Name");
  case T_TYPE:          return tr("Type");
  case T_TAG:           return tr("Tag");
  case T_ANNOTATION:    return tr("Annotation");
  case T_ALIAS:         return tr("Alias");
  case T_USER_ID:       return tr("UserID");
  case T_USER_ALIAS:    return tr("UserAlias");
  case T_TOKEN_ID:      return tr("TokenId");
  case T_HASH:          return tr("Hash");
  case T_TEXT:          return tr("Text");
  case T_POS:           return tr("Pos");
  case T_CREATETIME:    return tr("CreateTime");
  case T_UPDATETIME:    return tr("UpdateTime");
  case T_LANGUAGE:      return tr("Language");
  case T_STATUS:        return tr("Status");
  case T_FLAGS:         return tr("Flags");
  case T_BLESSEDCOUNT:  return tr("BlessedCount");
  case T_CURSEDCOUNT:   return tr("CursedCount");
  case T_BLOCKEDCOUNT:  return tr("BlockedCount");
  case T_ANNOTCOUNT:    return tr("AnnotCount");
  case T_VISITEDCOUNT:  return tr("VisitedCount");

  case T_PID:           return tr("PID");
  case T_FOLDER:        return tr("Folder");
  case T_PATH:          return tr("Path");

  case T_ACTIVE:        return tr("Active");
  case T_DELETED:       return tr("Deleted");
  case T_BLOCKED:       return tr("Blocked");
  case T_ANNOT:         return tr("Annot");
  case T_NA:            return tr("n/a");
  case T_ANONYMOUS:     return tr("Anonymous");

  default:
    qWarning() << "TranslatorManager:translate: Unknown tid =" << tid;
    Q_ASSERT(0);
    return QString();
  }
#undef SELF
}

// EOF