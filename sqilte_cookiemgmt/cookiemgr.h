#ifndef __COOKIEMANAGER_HEADER__
#define __COOKIEMANAGER_HEADER__

#include <sqlite3.h>
#include <cstring>

#define tblcookie "cookie"
#define cookie_colname "name"
#define cookie_colvalue "value"
#define cookie_colexpirytime "expirytime"
#define cookie_colpath "path"
#define cookie_coldomain "domain"
#define cookie_colflags "flags"

typedef struct
{
	sqlite3_stmt *querystmt, *insertstmt, *updatestmt;
} COOKIEMGR_RECVSTMTs, *PCOOKIEMGR_RECVSTMTs;

typedef struct
{
	sqlite3_stmt *querystmt;
} COOKIEMGR_SENDSTMT, *PCOOKIEMGR_SENDSTMT;

#ifdef __cplusplus
extern "C" {
#endif

int cookiemgr_recvedheader(sqlite3* fs, PCOOKIEMGR_RECVSTMTs* stmts, char* url, char* header);
int cookiemgr_sendingheader(sqlite3* fs, PCOOKIEMGR_SENDSTMT* _stmt, char* url, char* outbuf, size_t* bufsize); //return the number of bytes written
int cookiemgr_freerecvstmts(PCOOKIEMGR_RECVSTMTs stmts, int flags=0);
int cookiemgr_freesendstmt(PCOOKIEMGR_SENDSTMT stmt, int flags=0);

#ifdef __cplusplus
}
#endif

#endif

