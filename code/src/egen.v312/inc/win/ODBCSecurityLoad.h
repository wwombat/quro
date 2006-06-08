/*
*	(c) Copyright 2002-2003, Microsoft Corporation
*	Provided to the TPC under license.
*	Written by Sergey Vasilevskiy.
*/

/*
*	Database loader class for SECURITY table.
*/
#ifndef ODBC_SECURITY_LOAD_H
#define ODBC_SECURITY_LOAD_H

namespace TPCE
{

class CODBCSecurityLoad : public CDBLoader <SECURITY_ROW>
{	
	DBDATETIME	ODBC_S_START_DATE;
	DBDATETIME	ODBC_S_EXCH_DATE;

	BCPDOUBLE		ODBC_S_52WK_LOW;
	BCPDBDATETIME	ODBC_S_52WK_LOW_DATE;
	BCPDOUBLE		ODBC_S_52WK_HIGH;
	BCPDBDATETIME	ODBC_S_52WK_HIGH_DATE;

	virtual inline void CopyRow(PT row)
	{
		memcpy(&m_row, row, sizeof(m_row));

		m_row.S_START_DATE.GetDBDATETIME(&ODBC_S_START_DATE);
		m_row.S_EXCH_DATE.GetDBDATETIME(&ODBC_S_EXCH_DATE);

		if( OLTP_VALUE_IS_NULL == m_row.S_52WK.iIndicator )
		{
			ODBC_S_52WK_LOW.iIndicator = SQL_NULL_DATA;
			ODBC_S_52WK_LOW.value = m_row.S_52WK.LOW;	//Do we care about this assignment??

			ODBC_S_52WK_LOW_DATE.iIndicator = SQL_NULL_DATA;
			m_row.S_52WK.LOW_DATE.GetDBDATETIME(&ODBC_S_52WK_LOW_DATE.value);	//Do we care about this assignment??

			ODBC_S_52WK_HIGH.iIndicator = SQL_NULL_DATA;
			ODBC_S_52WK_HIGH.value = m_row.S_52WK.HIGH;	//Do we care about this assignment??

			ODBC_S_52WK_HIGH_DATE.iIndicator = SQL_NULL_DATA;
			m_row.S_52WK.HIGH_DATE.GetDBDATETIME(&ODBC_S_52WK_HIGH_DATE.value);	//Do we care about this assignment??
		}
		else
		{
			ODBC_S_52WK_LOW.iIndicator = sizeof(ODBC_S_52WK_LOW.value);
			ODBC_S_52WK_LOW.value = m_row.S_52WK.LOW;

			ODBC_S_52WK_LOW_DATE.iIndicator = sizeof(ODBC_S_52WK_LOW_DATE.value);
			m_row.S_52WK.LOW_DATE.GetDBDATETIME(&ODBC_S_52WK_LOW_DATE.value);

			ODBC_S_52WK_HIGH.iIndicator = sizeof(ODBC_S_52WK_HIGH.value);
			ODBC_S_52WK_HIGH.value = m_row.S_52WK.HIGH;

			ODBC_S_52WK_HIGH_DATE.iIndicator = sizeof(ODBC_S_52WK_HIGH_DATE.value);
			m_row.S_52WK.HIGH_DATE.GetDBDATETIME(&ODBC_S_52WK_HIGH_DATE.value);
		}
	};

public:
	CODBCSecurityLoad(char *szServer, char *szDatabase, char *szTable = "SECURITY")
		: CDBLoader<SECURITY_ROW>(szServer, szDatabase, szTable)
	{
	};

	virtual void BindColumns()
	{
		//Binding function we have to implement.
		int i = 0;
		if (   //bcp_bind(m_hdbc, (BYTE *) &m_row.S_ID, 0, SQL_VARLEN_DATA, NULL, 0, SQLINT4, ++i) != SUCCEED
			bcp_bind(m_hdbc, (BYTE *) &m_row.S_SYMB, 0, SQL_VARLEN_DATA, (BYTE *)"", 1, SQLCHARACTER, ++i) != SUCCEED
			|| bcp_bind(m_hdbc, (BYTE *) &m_row.S_ISSUE, 0, SQL_VARLEN_DATA, (BYTE *)"", 1, SQLCHARACTER, ++i) != SUCCEED
			|| bcp_bind(m_hdbc, (BYTE *) &m_row.S_ST_ID, 0, SQL_VARLEN_DATA, (BYTE *)"", 1, SQLCHARACTER, ++i) != SUCCEED			
			|| bcp_bind(m_hdbc, (BYTE *) &m_row.S_NAME, 0, SQL_VARLEN_DATA, (BYTE *)"", 1, SQLCHARACTER, ++i) != SUCCEED
			|| bcp_bind(m_hdbc, (BYTE *) &m_row.S_EX_ID, 0, SQL_VARLEN_DATA, (BYTE *)"", 1, SQLCHARACTER, ++i) != SUCCEED
			|| bcp_bind(m_hdbc, (BYTE *) &m_row.S_CO_ID, 0, SQL_VARLEN_DATA, NULL, 0, IDENT_BIND, ++i) != SUCCEED
			|| bcp_bind(m_hdbc, (BYTE *) &m_row.S_NUM_OUT, 0, SQL_VARLEN_DATA, NULL, 0, SQLFLT8, ++i) != SUCCEED
			|| bcp_bind(m_hdbc, (BYTE *) &ODBC_S_START_DATE, 0, SQL_VARLEN_DATA, NULL, 0, SQLDATETIME, ++i) != SUCCEED
			|| bcp_bind(m_hdbc, (BYTE *) &ODBC_S_EXCH_DATE, 0, SQL_VARLEN_DATA, NULL, 0, SQLDATETIME, ++i) != SUCCEED
			|| bcp_bind(m_hdbc, (BYTE *) &m_row.S_PE, 0, SQL_VARLEN_DATA, NULL, 0, SQLFLT8, ++i) != SUCCEED
			|| bcp_bind(m_hdbc, (BYTE *) &ODBC_S_52WK_HIGH.iIndicator, 4, SQL_VARLEN_DATA, NULL, 0, SQLFLT4, ++i) != SUCCEED
			|| bcp_bind(m_hdbc, (BYTE *) &ODBC_S_52WK_HIGH_DATE.iIndicator, 4, SQL_VARLEN_DATA, NULL, 0, SQLDATETIME, ++i) != SUCCEED
			|| bcp_bind(m_hdbc, (BYTE *) &ODBC_S_52WK_LOW.iIndicator, 4, SQL_VARLEN_DATA, NULL, 0, SQLFLT4, ++i) != SUCCEED
			|| bcp_bind(m_hdbc, (BYTE *) &ODBC_S_52WK_LOW_DATE.iIndicator, 4, SQL_VARLEN_DATA, NULL, 0, SQLDATETIME, ++i) != SUCCEED
			|| bcp_bind(m_hdbc, (BYTE *) &m_row.S_DIVIDEND, 0, SQL_VARLEN_DATA, NULL, 0, SQLFLT8, ++i) != SUCCEED
			|| bcp_bind(m_hdbc, (BYTE *) &m_row.S_YIELD, 0, SQL_VARLEN_DATA, NULL, 0, SQLFLT8, ++i) != SUCCEED
			)
			ThrowError(CODBCERR::eBcpBind);

		//if ( bcp_control(m_hdbc, BCPHINTS, "TABLOCK" ) != SUCCEED )	
		//	ThrowError(CODBCERR::eBcpControl);
	};

};

}	// namespace TPCE

#endif //ODBC_SECURITY_LOAD_H