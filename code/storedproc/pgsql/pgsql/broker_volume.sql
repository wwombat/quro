/*
 * Copyright (C) 2006-2007 Rilson Nascimento
 *
 * Broker Volume transaction
 * -------------------------
 * This transaction produces a descending list of the total potential 
 * volume generated by a list of brokers for all trade requests in a given
 * sector
 *
 * Based on TPC-E Standard Specification Revision 1.3.0.
 */

CREATE OR REPLACE FUNCTION BrokerVolumeFrame1 (
		IN broker_list VARCHAR[],
		IN sector_name VARCHAR,
		OUT broker_name VARCHAR(100)[],
		OUT list_len INTEGER,
		OUT status INTEGER,
		OUT volume NUMERIC(14, 2)[])
RETURNS SETOF record AS $$
DECLARE
	r RECORD;
BEGIN
	list_len := 0;
	FOR r IN
			SELECT b_name, SUM(tr_qty * tr_bid_price) AS vol
			FROM trade_request, sector, industry, company, broker, security
			WHERE tr_b_id = b_id
	  		AND tr_s_symb = s_symb
	  		AND s_co_id = co_id
	  		AND co_in_id = in_id
	  		AND sc_id = in_sc_id
	  		AND b_name = ANY (broker_list)
	  		AND sc_name = sector_name
			GROUP BY b_name
			ORDER BY 2 DESC
	LOOP
		list_len := list_len + 1;
		broker_name[list_len] = r.b_name;
		volume[list_len] = r.vol;
	END LOOP;

	status := 0;

	RETURN NEXT;
END;
$$ LANGUAGE 'plpgsql';
