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
//#include <ncurses.h>
#include <iostream>

clicker_sniffer_sptr clicker_make_sniffer()
{
	return clicker_sniffer_sptr(new clicker_sniffer());
}

clicker_sniffer::clicker_sniffer() : gr_sync_block ("clicker_sniffer",
	      gr_make_io_signature (1, 1, sizeof(char)),
	      gr_make_io_signature (0, 0, 0))
{
	set_history(43);
	//initscr();
}

clicker_sniffer::~clicker_sniffer()
{
	//endwin();
}

int clicker_sniffer::work(int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	//const char *in = (const char *) input_items[0];
	char* in = (char*) input_items[0];
	//char *out = (char *) output_items[0];
	//for (int i = 0; i < noutput_items; i++){
	//	out[i] = in[i] * in[i];
	//}

	if (in[0] & (char)0x02)
	{
		clicker_packet_sptr packet = clicker_make_packet(in, 43);
		search_responses(packet);
		//cout<<(packet->get_response_code())<<endl;
		print_responses();
		return 43;
	}
	return 1;
}

void clicker_sniffer::print_responses()
{
	float mult = 100/(d_a + d_b + d_c + d_d + d_e);
	printf("Registered IDs: %d A: %4.2f, B: %4.2f, C: %4.2f, D: %4.2f, E: %4.2f\n", d_responses.size(), d_a*mult, d_b*mult, d_c*mult, d_d*mult, d_e*mult);
	//refresh();
}

int clicker_sniffer::search_responses(clicker_packet_sptr packet)
{
	int resp = 0;
	
	d_a = 0;
	d_b = 0;
	d_c = 0;
	d_d = 0;
	d_e = 0;

	uint32_t id = packet->get_id();
	if (!d_responses[id])
		d_responses[id] = packet;
	else
	{
		d_responses[id]->inc_count();
		d_responses[id]->set_response_code(packet->get_response_code());
	}

	map<uint32_t, clicker_packet_sptr>::iterator i;
	for(i=d_responses.begin(); i != d_responses.end(); ++i)
	{
		if(i->second->get_count() < 2) continue;
		
		switch(i->second->get_response_code())
		{
		case 'A':
			inc_a();
			break;
		case 'B':
			inc_b();
			break;
		case 'C':
			inc_c();
			break;
		case 'D':
			inc_d();
			break;
		case 'E':
			inc_e();
			break;
		}
	}
	
	return resp;
}
