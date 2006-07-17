/*
 * DMSUT.cpp
 *
 * 2006 Rilson Nascimento
 *
 * 17 July 2006
 */

#include "transactions.h"
#include "harness.h"

using namespace TPCE;

CDMSUT::CDMSUT(CDBConnection *pDBConn)
: m_pDBConnection(pDBConn)
{
}

CDMSUT::~CDMSUT()
{
}

bool CDMSUT::DataMaintenance( PDataMaintenanceTxnInput pTxnInput )
{
	// Data Maintenance harness code (TPC provided)
	// this class uses our implementation of CDataMaintenanceDB class
	CDataMaintenance		m_DataMaintenance(m_pDBConnection);

	// Data Maintenance output parameters
	TDataMaintenanceTxnOutput	m_DataMaintenanceTxnOutput;
	
	m_DataMaintenance.DoTxn( pTxnInput, &m_DataMaintenanceTxnOutput); // Perform Data Maintenance
}

bool CDMSUT::TradeCleanup( PTradeCleanupTxnInput pTxnInput )
{
}
