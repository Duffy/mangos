/*
 * Copyright (C) 2005-2010 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _DatabasePostgre_H
#define _DatabasePostgre_H

#include "Policies/Singleton.h"
#include <stdarg.h>

#ifdef WIN32
#define FD_SETSIZE 1024
#include <winsock2.h>
#include <postgre/libpq-fe.h>
#else
#include <libpq-fe.h>
#endif

class DatabasePostgre : public Database
{
    friend class MaNGOS::OperatorNew<DatabasePostgre>;

    public:
        DatabasePostgre();
        ~DatabasePostgre();

        //! Initializes Postgres and connects to a server.
        /*! infoString should be formated like hostname;username;password;database. */
        bool Initialize(const char *infoString);
        void InitDelayThread();
        void HaltDelayThread();
        QueryResult* Query(const char *sql);
        QueryNamedResult* QueryNamed(const char *sql);
        bool Execute(const char *sql);
        bool DirectExecute(const char* sql);
        bool BeginTransaction();
        bool CommitTransaction();
        bool RollbackTransaction();

        operator bool () const { return mPGconn != NULL; }

        unsigned long escape_string(char *to, const char *from, unsigned long length);
        using Database::escape_string;

        // must be call before first query in thread
        void ThreadStart();
        // must be call before finish thread run
        void ThreadEnd();
    private:
        ACE_Thread_Mutex mMutex;
        ACE_Based::Thread * tranThread;

        PGconn *mPGconn;

        static size_t db_count;

        bool _TransactionCmd(const char *sql);
        bool _Query(const char *sql, PGresult **pResult, uint64* pRowCount, uint32* pFieldCount);
};
#endif
