#include <systemc.h>
#include "dff.h"
#include "driver.h"
#include "monitor.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<bool> s_din,s_dout,clear;
	sc_clock clock("clk",10,SC_NS,0.5,false);

	dff dff1("dff");
	driver dr("driver");
	monitor mon("monitor");

	dr.d_din(s_din);
	dff1.din(s_din);
	mon.m_din(s_din);
	

	dff1.dout(s_dout);
	mon.m_dout(s_dout);
	
	dr.d_clr(clear);
	mon.m_clr(clear);
	
	dff1.clr(clear);
	dff1.clk(clock);
	
	
	sc_trace_file *fp;
	fp=sc_create_vcd_trace_file("vcd_trace");
	fp->set_time_unit(1, SC_NS);
	
	sc_trace(fp, s_din, "D");
	sc_trace(fp, clock, "CLK");
	sc_trace(fp, clear, "CLR");
	sc_trace(fp, s_dout, "dout");

	
	sc_start(120, SC_NS);
	sc_close_vcd_trace_file(fp);
	return 0;
}
