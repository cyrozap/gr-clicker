/* -*- c++ -*- */
/*
 * Copyright 2009 Jordan Riggs
 * Copyright 2005, 2006 Free Software Foundation, Inc.
 * 
 * This file is part of gr-clicker
 * 
 * gr-clicker is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * gr-clicker is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with gr-clicker; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gr_io_signature.h>
#include "clicker_packet.h"
#include "clicker_sniffer.h"

clicker_sniffer_sptr clicker_make_sniffer()
{
	return clicker_sniffer_sptr(new clicker_sniffer());
}

clicker_sniffer::clicker_sniffer() : gr_sync_block ("clicker_sniffer",
	      gr_make_io_signature (1, 1, sizeof(char)),
	      gr_make_io_signature (0, 0, 0))
{
	set_history(43);
}

clicker_sniffer::~clicker_sniffer()
{

}

int clicker_sniffer::work(int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	//const char *in = (const char *) input_items[0];
	char* in = (char*) input_items[0];
	char *out = (char *) output_items[0];
	//for (int i = 0; i < noutput_items; i++){
	//	out[i] = in[i] * in[i];
	//}

	if (in[0] & (char)0x02)
	{
		clicker_packet* packet = clicker_make_packet(in, 43);
		search_reponses(packet);
		return 43;
	}
	return 1;
}

int clicker_sniffer::search_responses(clicker_packet* packet)
{
	list<clicker_packet>::iterator i;
	for(i=responses.begin(); i != responses.end(); ++i)
	{
		// need to implement compare_ids
		if(clicker_packet.compare_ids(packet->get_id(), i.get_id()))
		{
			i.set_response_code(packet->get_id());
			return 1;
		}
	}
	return 0;
}
