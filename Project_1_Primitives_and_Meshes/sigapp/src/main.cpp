
# include "my_viewer.h"
# include <sigogl/ws_run.h>

int main ( int argc, char** argv )
{
	double t1, t2;
	t1 = gs_time();
	
	MyViewer* v = new MyViewer ( -1, -1, 640, 480, "My SIG Application" );
	v->cmd ( WsViewer::VCmdAxis );

	v->view_all ();
	
	v->show ();
	ws_check();
	t2 = gs_time();
	
	gsout << (t2 - t1) << gsnl;

	ws_run ();
	
	return 1;
}
