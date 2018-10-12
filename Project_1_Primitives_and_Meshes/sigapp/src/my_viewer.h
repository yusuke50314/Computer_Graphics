# pragma once

# include <sig/sn_poly_editor.h>
# include <sig/sn_lines2.h>

# include <sigogl/ui_button.h>
# include <sigogl/ws_viewer.h>
# include <sig/gs_model.h>

class MyViewer : public WsViewer
{  protected :
	enum MenuEv { EvNormals, EvAnimate, EvExit };
	UiCheckButton* _nbut;
	bool _animating;
   public :
	MyViewer ( int x, int y, int w, int h, const char* l );
	void add_ui ();

	SnTransform* _t1;
	SnTransform* _t2;
	SnTransform* _t3;
	SnTransform* _t4;
	SnTransform* _t5;
	SnTransform* _t6;
	SnTransform* _t7;
	SnTransform* _t8;
	SnTransform* _t9;
	SnTransform* _t10;
	SnTransform* _t11;
	SnTransform* _t12;
	SnTransform* _t13;
	SnTransform* _t14;
	SnTransform* _t15;
	SnTransform* _t16;
	SnTransform* _t17;
	SnTransform* _t18;
	SnTransform* _t19;
	SnTransform* _t20;
	SnTransform* _t21;
	SnTransform* _t22;
	SnTransform* _t23;
	SnTransform* _t24;
	SnTransform* _t25;
	SnTransform* _t26;
	SnTransform* _t27;
	SnTransform* _t28;
	SnTransform* _t29;
	SnTransform* _t30;
	SnTransform* _t31;
	SnTransform* _t32;
	SnTransform* _t33;
	SnTransform* _t34;
	SnTransform* _t35;
	SnTransform* _t36;
	SnTransform* _t37;
	SnTransform* _t38;
	SnTransform* _t39;
	SnTransform* _t40;
	SnTransform* _t41;
	SnTransform* _t42;

	SnTransform* _ts1;
	SnTransform* _ts2;
	SnTransform* _ts3;
	SnTransform* _ts4;
	SnTransform* _ts5;
	SnTransform* _ts6;
	SnTransform* _ts7;
	SnTransform* _ts8;
	SnTransform* _ts9;
	SnTransform* _ts10;
	SnTransform* _ts11;
	SnTransform* _ts12;
	SnTransform* _ts13;
	SnTransform* _ts14;
	SnTransform* _ts15;
	SnTransform* _ts16;
	SnTransform* _ts17;
	SnTransform* _ts18;
	SnTransform* _ts19;
	SnTransform* _ts20;
	SnTransform* _ts21;
	SnTransform* _ts22;
	SnTransform* _ts23;
	SnTransform* _ts24;
	SnTransform* _ts25;
	SnTransform* _ts26;
	SnTransform* _ts27;
	SnTransform* _ts28;
	SnTransform* _ts29;
	SnTransform* _ts30;
	SnTransform* _ts31;
	SnTransform* _ts32;
	SnTransform* _ts33;
	SnTransform* _ts34;
	SnTransform* _ts35;
	SnTransform* _ts36;
	SnTransform* _ts37;
	SnTransform* _ts38;
	SnTransform* _ts39;
	SnTransform* _ts40;
	SnTransform* _ts41;
	SnTransform* _ts42;

	SnTransform* _tp1;
	SnTransform* _tp2;
	SnTransform* _tp3;
	SnTransform* _tp4;
	SnTransform* _tp5;
	SnTransform* _tp6;
	SnTransform* _tp7;
	SnTransform* _tp8;
	SnTransform* _tp9;
	SnTransform* _tp10;

	SnTransform* _cl1;
	SnTransform* _cl2;

	SnTransform* _th1;
	SnTransform* _th2;
	SnTransform* _th3;
	SnTransform* _th4;
	SnTransform* _th5;
	SnTransform* _th6;
	SnTransform* _th7;
	SnTransform* _th8;
	SnTransform* _th9;
	SnTransform* _th10;

	SnTransform* _tb1;
	SnTransform* _tb2;
	SnTransform* _tb3;
	SnTransform* _tb4;
	SnTransform* _tb5;
	SnTransform* _tb6;
	SnTransform* _tb7;
	SnTransform* _tb8;
	SnTransform* _tb9;
	SnTransform* _tb10;
	SnTransform* _tb11;
	SnTransform* _tb12;
	SnTransform* _tb13;
	SnTransform* _tb14;
	SnTransform* _tb15;
	SnTransform* _tb16;
	SnTransform* _tb17;
	SnTransform* _tb18;
	SnTransform* _tb19;
	SnTransform* _tb20;
	SnTransform* _tb21;
	SnTransform* _tb22;
	SnTransform* _tb23;
	SnTransform* _tb24;
	SnTransform* _tb25;
	SnTransform* _tb26;
	SnTransform* _tb27;
	SnTransform* _tb28;
	SnTransform* _tb29;
	SnTransform* _tb30;
	SnTransform* _tb31;

	SnTransform* _tc1;
	SnTransform* _tc2;

	SnTransform* _t5_2; SnTransform* _t5_3;
	SnTransform* _t7_2; SnTransform* _t7_3; SnTransform* _t7_4;
	SnTransform* _t9_2; SnTransform* _t9_3; SnTransform* _t9_4; SnTransform* _t9_5;
	SnTransform* _t11_2; SnTransform* _t11_3; SnTransform* _t11_4;
	SnTransform* _t12_2;
	SnTransform* _t14_2;
	SnTransform* _t16_2; SnTransform* _t16_3; SnTransform* _t16_4;
	SnTransform* _t20_2; SnTransform* _t20_3;
	SnTransform* _t22_2; SnTransform* _t22_3; SnTransform* _t22_4;
	SnTransform* _t23_2;
	SnTransform* _t25_2;

	float _curang1;
	float _curang2;
	float _curang3;
	float _curang4;
	float _curang5;
	float _curang6;
	float _curang7;
	float _curang8;
	float _curang9;
	float _curang10;
	float _curang11;
	float _curang12;
	float _curang13;
	float _curang14;
	float _curang15;
	float _curang16;
	float _curang17;
	float _curang18;
	float _curang19;
	float _curang20;
	float _curang21;
	float _curang22;
	float _curang23;
	float _curang24;
	float _curang25;
	float _curang26;
	float _curang27;
	float _curang28;
	float _curang29;
	float _curang30;
	float _curang31;
	float _curang32;

	float _curx1;
	float _curx2;
	float _curx3;
	float _curx4;
	float _curx5;
	float _curx6;
	float _curx7;
	float _curx8;
	float _curx9;
	float _curx10;
	float _curx11;
	float _curx12;
	float _curx13;
	float _curx14;
	float _curx15;
	float _curx16;
	float _curx17;
	float _curx18;
	float _curx19;
	float _curx20;
	float _curx21;
	float _curx22;
	float _curx23;
	float _curx24;
	float _curx25;
	float _curx26;
	float _curx27;
	float _curx28;
	float _curx29;
	float _curx30;
	float _curx31;

	void add_model ( SnShape* s, GsVec p );
	void make_my_hand(GsModel* m, double length, double width);
	void make_my_clock(GsModel* m, double radius, double theta);
	void make_my_cylinder(GsModel* m, double length);
	void make_my_cylinder_cs(GsModel* m, double length, double rad);
	void make_my_cylinder_hole(GsModel* m, double length, double irad, double orad);
	void make_my_gear(GsModel* m, double radius, double thickness, double cradius); //generate gear (original)
	void make_my_gear_cs(GsModel* m, double radius, double thickness, double cradius, double gradius); //change size with practical gear teeth
	void make_my_gear_four(GsModel* m, double radius, double thickness, double cradius, double gradius); //change teeth number
	void make_my_belt(GsModel* m, int teeth, double bthickness); //generate belt (original)
	void make_my_belt_lp(GsModel* m, int teeth, double bthickness, int initial); //generate belt (original)
	void make_my_cube(GsModel* m, double width, double thickness);
	void build_scene ();
	void show_normals ( bool b );
	void run_animation ();
	virtual int handle_keyboard ( const GsEvent &e ) override;
	virtual int uievent ( int e ) override;
	
};

