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
#include "clicker_sniffer.h"

clicker_sniffer_sptr clicker_make_sniffer()
{
	return clicker_sniffer_sptr(new clicker_sniffer());
}

clicker_sniffer::clicker_sniffer() : gr_sync_block ("clicker block",
	      gr_make_io_signature (1, 1, sizeof(char)),
	      gr_make_io_signature (0, 0, 0))
{
	printf("clicker_sniffer constructed");
}

clicker_sniffer::~clicker_sniffer()
{

}

int clicker_sniffer::work(int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	return 1;
}
