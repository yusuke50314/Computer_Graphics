# pragma once

# include <sig/sn_poly_editor.h>
# include <sig/sn_lines2.h>
# include <sig/sn_manipulator.h>

# include <sigogl/ui_button.h>
# include <sigogl/ui_slider.h>
# include <sigogl/ws_viewer.h>

// Viewer for this example:
class MyViewer : public WsViewer
{  protected :
	enum MenuEv { EvTr1, EvTr2, EvTr3, EvTr4, EvTr5, EvTr6, EvTr7, EvTr8, EvTr9, EvTr10, EvTr11, EvTr12, EvNormals, EvShadow, EvCage1, EvCage2, EvSmooth, EvLight, EvExit };
	UiCheckButton* _nbut;
	bool _animating;
    public :
	MyViewer ( int x, int y, int w, int h, const char* l );
	void add_ui ();
	void add_model ( SnShape* s, GsVec p );
	void build_scene(int check, int div, int put, int button, int change, float lightx, float lighty, float lightz);
	void show_normals ( bool b );
	void run_animation ();
	virtual int handle_keyboard ( const GsEvent &e ) override;
	virtual int uievent ( int e ) override;

	int state;
	int nstate;
	int cstate;
	int bstate;
	int smoothing;

	int on_off;

	int shadowstate = 0;
	
	UiSlider* SliderX;
	UiSlider* SliderY;
	UiSlider* SliderZ;

	double st1;
	double fi1;
	double st2;
	double fi2;

	SnLines* cagehead = new SnLines;
};

