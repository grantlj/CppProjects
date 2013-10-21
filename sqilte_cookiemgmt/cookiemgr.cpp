#include "cookiemgr.h"
#include "dbinit.h"
#include <cstdlib>
#include <cstdio>
#include <cctype>


static inline int cookiemgr_initrecvstmts(sqlite3* fs, PCOOKIEMGR_RECVSTMTs stmts)
{
	//printf("before initrecvstmts\n");
	int rtn;
	memset(stmts, 0, sizeof(COOKIEMGR_RECVSTMTs));
	rtn=sqlite3_prepare_v2(fs, "SELECT * FROM "tblcookie" WHERE (("cookie_colname"=?1) AND ("cookie_coldomain"=?2) AND("cookie_colpath"=?3))", -1, &(stmts->querystmt), 0);
	//printf("prepare querystmt: %d\n",rtn);
	rtn=sqlite3_prepare_v2(fs, "INSERT INTO "tblcookie" VALUES (?1, ?2, ?3, ?4, ?5, ?6)", -1, &(stmts->insertstmt), 0);
	//printf("prepare insertstmt: %d\n",rtn);
	rtn=sqlite3_prepare_v2(fs, "UPDATE "tblcookie" SET "
					cookie_colvalue"=?2, "
					cookie_colexpirytime"=?3, "
					cookie_colpath"=?4, "
					cookie_coldomain"=?5, "
					cookie_colflags"=?6 "
					"WHERE "cookie_colname"=?1", -1, &(stmts->updatestmt), 0);
	//printf("prepare updatestmt: %d\n",rtn);
	return rtn;
}

int cookiemgr_freerecvstmts(PCOOKIEMGR_RECVSTMTs stmts, int flags)
{
	int rtn;
	rtn=sqlite3_finalize(stmts->querystmt);
	rtn=sqlite3_finalize(stmts->insertstmt);
	rtn=sqlite3_finalize(stmts->updatestmt);
	if (!flags)
		free(stmts);
	return rtn;
}

static void cookiemgr_month3todigit2(char* month3, char* digit2)
{
	if (memcmp(month3, "Jan", 3)==0)
	{
		digit2[0]='0';
		digit2[1]='1';
		return;
	}
	if (memcmp(month3, "Feb", 3)==0)
	{
		digit2[0]='0';
		digit2[1]='2';
		return;
	}
	if (memcmp(month3, "Mar", 3)==0)
	{
		digit2[0]='0';
		digit2[1]='3';
		return;
	}
	if (memcmp(month3, "Apr", 3)==0)
	{
		digit2[0]='0';
		digit2[1]='4';
		return;
	}
	if (memcmp(month3, "May", 3)==0)
	{
		digit2[0]='0';
		digit2[1]='5';
		return;
	}
	if (memcmp(month3, "Jun", 3)==0)
	{
		digit2[0]='0';
		digit2[1]='6';
		return;
	}
	if (memcmp(month3, "Jul", 3)==0)
	{
		digit2[0]='0';
		digit2[1]='7';
		return;
	}
	if (memcmp(month3, "Aug", 3)==0)
	{
		digit2[0]='0';
		digit2[1]='8';
		return;
	}
	if (memcmp(month3, "Sep", 3)==0)
	{
		digit2[0]='0';
		digit2[1]='9';
		return;
	}
	if (memcmp(month3, "Oct", 3)==0)
	{
		digit2[0]='1';
		digit2[1]='0';
		return;
	}
	if (memcmp(month3, "Nov", 3)==0)
	{
		digit2[0]='1';
		digit2[1]='1';
		return;
	}
	if (memcmp(month3, "Dec", 3)==0)
	{
		digit2[0]='1';
		digit2[1]='2';
		return;
	}
}

int strncicmp(char* str1, char* str2, size_t len)
{
	for (size_t i=0; i<len; i++, str1++, str2++)
	{
		if (*str2==0)
			if (*str1)
				return 1;
			else
				return 0;
		else
			if (*str1==0)
				return -1;
		if (toupper(*str1)>toupper(*str2))
			return 1;
		else if (toupper(*str1)<toupper(*str2))
			return -1;
	}
	return 0;
}

#define parseflag_domain 1
#define parseflag_path 2
static int cookiemgr_parsebindcol(sqlite3_stmt* stmt, char** psos, int* flags)
{
	//printf("	cookiemgr_parsecol: %s\n", *psos);
	int rtn;
	char* eos=strchr(*psos, ';');
	if (eos==0)
	{
		eos=*psos+strlen(*psos);
	}
	if (strncicmp(*psos, "Expires=", 8)==0)
	{
		//Expires=Wed, 13 Jan 2021 22:23:01 GMT;
		char datetime[19]={0};
		*psos+=13;
		memcpy(datetime, *psos+7, 4);
		datetime[4]='-';
		//printf("yyyy- %s\n", datetime);
		cookiemgr_month3todigit2(*psos+3, datetime+5);
		datetime[7]='-';
		memcpy(datetime+8, *psos, 2);
		memcpy(datetime+10, *psos+11, 9);
		rtn=sqlite3_bind_text(stmt, 3, datetime, 19, SQLITE_TRANSIENT);
		goto finishNreturn;
	}
	if (strncicmp(*psos, "Domain=", 7)==0)
	{
		*psos+=7;
		rtn=sqlite3_bind_text(stmt, 5, *psos, int(eos-*psos), SQLITE_STATIC);
		*flags|=parseflag_domain;
		goto finishNreturn;
	}
	if (strncicmp(*psos, "Path=", 5)==0)
	{
		*psos+=5;
		rtn=sqlite3_bind_text(stmt, 4, *psos, int(eos-*psos), SQLITE_STATIC);
		*flags|=parseflag_path;
		goto finishNreturn;
	}
	if (strncicmp(*psos, "Secure", 6)==0)
	{
		eos=*psos+strlen(*psos);
		rtn=sqlite3_bind_text(stmt, 6, *psos, int(eos-*psos), SQLITE_STATIC);
		goto finishNreturn;
	}

	finishNreturn:
	*psos=eos+2;
	return rtn;
}

static inline int cookiemgr_parsebindline(sqlite3_stmt* stmt, char* url, char* sos, char* eos, char* eoln)
{
	//printf("cookiemgr_parseline: %s\n", sos);
	int rtn;
	char tempchar;
	tempchar=*eoln;
	*eoln=0;

	sqlite3_reset(stmt);
	sqlite3_clear_bindings(stmt);
	// cookie name
	sqlite3_bind_text(stmt, 1, sos, int(eos-sos), SQLITE_STATIC);
	// cookie value
	sos=eos+1;
	eos=strchr(sos, ';');
	if (eos==0)
		eos=eoln;
	sqlite3_bind_text(stmt, 2, sos, int(eos-sos), SQLITE_STATIC);

	int flags=0;
	if (eos<eoln)
	{
		sos=eos+2;
		while (*sos==' ') sos++;
		while (sos<eoln)
		{
			cookiemgr_parsebindcol(stmt, &sos, &flags);
		}
	}
	if (!(flags&parseflag_domain))
	{
		sos=strstr(url, "://")+3;
		eos=strchr(sos, '/');
		rtn=sqlite3_bind_text(stmt, 5, sos, int(eos-sos), SQLITE_STATIC);
		/*
		*eos=0;	
		printf("manually set domain (%s): %d\n", sos, rtn);
		*eos='/';
		*/
	}
	if (!(flags&parseflag_path))
	{
		sos=strstr(url, "://")+3;
		sos=strchr(sos, '/');
		eos=strchr(sos, '?');
		if (eos==0)
		{
			eos=sos+strlen(sos);
		}
		rtn=sqlite3_bind_text(stmt, 4, sos, size_t(eos-sos), SQLITE_STATIC);
		//printf("manually set path (%s): %d\n", sos, rtn);
	}
	rtn=sqlite3_step(stmt);
	*eoln=tempchar;
	return rtn;
}

int cookiemgr_recvedheader(sqlite3* fs, PCOOKIEMGR_RECVSTMTs* _stmts, char* url, char* header)
{
	int rtn;
	char *soln, *eoln, *sos2, *eos2;
	COOKIEMGR_RECVSTMTs stmts;
	if (_stmts==0) // no reuse of previous handles
	{
		rtn=cookiemgr_initrecvstmts(fs, &stmts);
	}
	else if (*_stmts==0) // create a new handle
	{
		rtn=cookiemgr_initrecvstmts(fs, &stmts);
		*_stmts=(PCOOKIEMGR_RECVSTMTs)malloc(sizeof(COOKIEMGR_RECVSTMTs));
		memcpy(*_stmts, &stmts, sizeof(COOKIEMGR_RECVSTMTs));
	}
	else //reuse previous handles
	{
		memcpy(&stmts, *_stmts, sizeof(COOKIEMGR_RECVSTMTs));
	}
	
	soln=header;
	eoln=strchr(soln, 13);
	while ((soln!=eoln)&&(eoln!=0))
	{
		if (int(eoln-soln)>12)
			if (memcmp(soln, "Set-Cookie: ", 12)==0)
			{
				sos2=soln+12;
				while (*sos2==' ') sos2++;
				eos2=strchr(sos2, '=');
				// now sos2 is the name of cookie
				sqlite3_reset(stmts.querystmt);
				sqlite3_clear_bindings(stmts.querystmt);
				sqlite3_bind_text(stmts.querystmt, 1, sos2, int(eos2-sos2), SQLITE_STATIC);
				// work around only
				char *sos3, *eos3;
				*eoln=0;
				sos3=strstr(soln, "Domain=");
				if (!sos3)
					sos3=strstr(soln, "domain=");
				if (!sos3)
				{
					sos3=strstr(url, "://")+3;
					eos3=strchr(sos3, '/');
					sqlite3_bind_text(stmts.querystmt, 2, sos3, int(eos3-sos3), SQLITE_STATIC);
				}
				else
				{
					sos3+=7;
					eos3=strchr(sos3, ';');
					sqlite3_bind_text(stmts.querystmt, 2, sos3, int(eos3-sos3), SQLITE_STATIC);
				}

				sos3=strstr(soln, "Path=");
				if (!sos3)
					sos3=strstr(soln, "path=");
				if (!sos3)
				{
					sos3=strstr(url, "://")+3;
					sos3=strchr(sos3, '/');
					eos3=strchr(sos3, '?');
					if (eos3==0)
					{
						sqlite3_bind_text(stmts.querystmt, 3, sos3, -1, SQLITE_STATIC);
					}
					else
					{
						sqlite3_bind_text(stmts.querystmt, 3, sos3, int(eos3-sos3), SQLITE_STATIC);
					}
				}
				else
				{
					sos3+=5;
					eos3=strchr(sos3, ';');
					sqlite3_bind_text(stmts.querystmt, 3, sos3, int(eos3-sos3), SQLITE_STATIC);
				}
				*eoln=13;
				// //
				rtn=sqlite3_step(stmts.querystmt);
				if (rtn!=SQLITE_ROW) // entry does not exist. insert a new one
				{
					rtn=cookiemgr_parsebindline(stmts.insertstmt, url, sos2, eos2, eoln);
				}
				else // update existing entry
				{
					rtn=cookiemgr_parsebindline(stmts.updatestmt, url, sos2, eos2, eoln);
				}
			}
		soln=eoln+2;
		eoln=strchr(soln, 13);
	}

	if (_stmts==0) // no reuse of previous handles
	{
		cookiemgr_freerecvstmts(&stmts, 1);
	}

	return rtn;
}

int cookiemgr_initsendstmt(sqlite3* fs, PCOOKIEMGR_SENDSTMT stmt)
{
	int rtn;
	memset(stmt, 0, sizeof(COOKIEMGR_SENDSTMT));
	/*
	rtn=sqlite3_prepare_v2(fs, "SELECT "cookie_colname", "cookie_colvalue" "
				"FROM "tblcookie" "
				"WHERE ("
				"(CASE ("cookie_coldomain" LIKE '.%') "
					"WHEN 1 THEN (?1 LIKE '%'||"cookie_coldomain") "
					"ELSE (?1 LIKE "cookie_coldomain")"
				"END)"
				"AND (?2 LIKE "cookie_colpath"||'%') "
				"AND (CASE ("cookie_colexpirytime" ISNULL) "
				"	WHEN 1 THEN 1 "
					"ELSE ("cookie_colexpirytime">=CURRENT_TIMESTAMP)"
				"END)"
				")",
				-1, &(stmt->querystmt), 0);
	*/
	rtn=sqlite3_prepare_v2(fs, "SELECT "cookie_colname", "cookie_colvalue" "
				"FROM "tblcookie" "
				"WHERE ("
				"(?1 LIKE '%'||"cookie_coldomain") "
				"AND (?2 LIKE "cookie_colpath"||'%') "
				"AND (CASE ("cookie_colexpirytime" ISNULL) "
				"	WHEN 1 THEN 1 "
					"ELSE ("cookie_colexpirytime">=CURRENT_TIMESTAMP)"
				"END)"
				")",
				-1, &(stmt->querystmt), 0);
	return rtn;
}

int cookiemgr_freesendstmt(PCOOKIEMGR_SENDSTMT stmt, int flags)
{
	int rtn;
	rtn=sqlite3_finalize(stmt->querystmt);
	if (!flags)
		free(stmt);
	return rtn;
}

int cookiemgr_sendingheader(sqlite3* fs, PCOOKIEMGR_SENDSTMT* _stmt, char* url, char* outbuf, size_t* bufsize)
{
	int rtn=0;
	char *sos, *eos;
	COOKIEMGR_SENDSTMT stmt;
	if (_stmt==0) // no reuse of previous handles
	{
		rtn=cookiemgr_initsendstmt(fs, &stmt);
	}
	else if (*_stmt==0) // create a new handle
	{
		rtn=cookiemgr_initsendstmt(fs, &stmt);
		*_stmt=(PCOOKIEMGR_SENDSTMT)malloc(sizeof(COOKIEMGR_SENDSTMT));
		memcpy(*_stmt, &stmt, sizeof(COOKIEMGR_SENDSTMT));
	}
	else //reuse previous handles
	{
		memcpy(&stmt, *_stmt, sizeof(COOKIEMGR_SENDSTMT));
	}
	sos=strstr(url, "://")+3;
	eos=strchr(sos, '/');
	//
	//printf("cookiemgr_sendingheader (%s), stmtinit: %d\n", sos, rtn);
	rtn=sqlite3_reset(stmt.querystmt);
	//printf("sqlite3_reset: %d\n", rtn);
	rtn=sqlite3_clear_bindings(stmt.querystmt);
	//printf("sqlite3_clear_bindings: %d\n", rtn);
	sqlite3_bind_text(stmt.querystmt, 1, sos, int(eos-sos), SQLITE_STATIC);
	sos=eos;
	sqlite3_bind_text(stmt.querystmt, 2, sos, -1, SQLITE_STATIC);
	rtn=sqlite3_step(stmt.querystmt);
	char* currpos=outbuf;
	*outbuf=0;
	size_t overflowmask=(size_t)-1;
	while (rtn==SQLITE_ROW)
	{
		char* cookiename=(char*)sqlite3_column_text(stmt.querystmt, 0);
		char* cookievalue=(char*)sqlite3_column_text(stmt.querystmt, 1);
		if (currpos!=outbuf) // not the first cookie
		{
			currpos+=snprintf(currpos, (*bufsize-size_t(currpos-outbuf))&overflowmask, "; ");
			if (currpos>=outbuf+*bufsize)
			{
				overflowmask=0;
			}
		}
		/*
		else // first invocation
		{
			currpos+=snprintf(currpos, (*bufsize-size_t(currpos-outbuf))&overflowmask, "Cookie: ");
			if (currpos>=outbuf+*bufsize)
			{
				overflowmask=0;
			}
		}
		*/
		currpos+=snprintf(currpos, (*bufsize-size_t(currpos-outbuf))&overflowmask, "%s=%s", cookiename, cookievalue);
		if (currpos>=outbuf+*bufsize)
		{
			overflowmask=0;
		}
		rtn=sqlite3_step(stmt.querystmt);
	}
	*bufsize=(size_t)(currpos-outbuf)+1;  // 0-terminator
	if (_stmt==0) // no reuse of previous handles
	{
		rtn=cookiemgr_freesendstmt(&stmt, 1);
	}
	if (overflowmask==0)
	{
		return -1;
	}
	else
	{
		return rtn;
	}
}

