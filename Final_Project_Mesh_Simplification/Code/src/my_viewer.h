# pragma once

# include <sig/sn_poly_editor.h>
# include <sig/sn_lines2.h>
# include <sig/gs_list.h>
# include <sig/gs_array.h>


# include <sigogl/ui_button.h>
# include <sigogl/ws_viewer.h>

// Viewer for this example:
class MyViewer : public WsViewer
{  protected :
	enum MenuEv { EvNormals, EvAnimate, EvExit };
	UiCheckButton* _nbut;
	bool _animating;
   public :
	MyViewer ( int x, int y, int w, int h, const char* l );
	void add_ui ();
	void add_model ( SnShape* s, GsVec p );
	void build_scene (int NUM);
	void show_normals ( bool b );
	void run_animation ();
	virtual int handle_keyboard ( const GsEvent &e ) override;
	virtual int uievent ( int e ) override;

	int limit_num;

};

