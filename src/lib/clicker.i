/* -*- c++ -*- */

%feature("autodoc", "1");		// generate python docstrings

%include "exception.i"
%import "gnuradio.i"			// the common stuff

%{
#pragma GCC diagnostic ignored "-Wuninitialized"
#include "gnuradio_swig_bug_workaround.h"	// mandatory bug fix
#include "clicker_sniffer.h"
#include <stdexcept>
%}

// ----------------------------------------------------------------

/*
 * First arg is the package prefix.
 * Second arg is the name of the class minus the prefix.
 */
GR_SWIG_BLOCK_MAGIC(clicker,sniffer);

clicker_sniffer_sptr clicker_make_sniffer();

class clicker_sniffer : public gr_sync_block
{
private:
  clicker_sniffer ();
};
