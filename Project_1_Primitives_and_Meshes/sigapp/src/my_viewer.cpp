
# include "my_viewer.h"
# include <sigogl/ui_button.h>
# include <sigogl/ui_radio_button.h>
# include <sig/sn_primitive.h>
# include <sig/sn_transform.h>
# include <sig/sn_manipulator.h>
# include <cmath>
# include <iostream>
# include <sigogl/ws_run.h>

#define PI 3.14159265

MyViewer::MyViewer ( int x, int y, int w, int h, const char* l ) : WsViewer(x,y,w,h,l)
{
	_nbut=0;
	_animating=false;
	add_ui ();
	build_scene ();
	

}

void MyViewer::add_ui ()
{
	UiPanel *p, *sp;
	UiManager* uim = WsWindow::uim();
	p = uim->add_panel ( "", UiPanel::HorizLeft );
	p->add ( new UiButton ( "View", sp=new UiPanel() ) );
	{	UiPanel* p=sp;
		p->add ( _nbut=new UiCheckButton ( "Normals", EvNormals ) ); 
	}
	p->add ( new UiButton ( "Animate", EvAnimate ) );
	p->add ( new UiButton ( "Exit", EvExit ) ); p->top()->separate();
}

void MyViewer::add_model ( SnShape* s, GsVec p )
{
	SnManipulator* manip = new SnManipulator;
	GsMat m;
	m.translation ( p );
	manip->initial_mat ( m );

	SnGroup* g = new SnGroup;
	SnLines* l = new SnLines;
	l->color(GsColor::orange);
	g->add(s);
	g->add(l);
	manip->child(g);

	rootg()->add(manip);
}

void MyViewer::make_my_hand(GsModel* m, double length, double width){

	SnModel* _model;
	_model = new SnModel;

	m->V.size(6);

	m->V[0].set(width, -10.0, 0.0);
	m->V[1].set(0.0, length, 0.0);
	m->V[2].set(-width, -10.0, 0.0);

	m->V[3].set(width, -10.0, 1.0);
	m->V[4].set(0.0, length, 1.0);
	m->V[5].set(-width, -10.0, 1.0);

	m->F.push().set(0, 1, 2);
	m->F.push().set(3, 4, 5);

	m->F.push().set(3, 0, 1);
	m->F.push().set(1, 4, 3);
	m->F.push().set(4, 1, 2);
	m->F.push().set(2, 5, 4);
	m->F.push().set(2, 0, 5);
	m->F.push().set(5, 0, 3);

}

void MyViewer::make_my_clock(GsModel* m, double radius, double theta) {

	SnModel* _model;
	_model = new SnModel;

	m->V.size(86);

	for (int i = 1; i <= 36; i = i + 7) {
		m->V[0].set(0, 0, 0);
		m->V[i].set(radius*std::cos(theta), radius*std::sin(theta), 0.0);
		m->V[i+1].set(radius*std::cos(theta + PI / 36), radius*std::sin(theta + PI / 36), 0.0);
		m->V[i+2].set(radius*std::cos(theta + 2*PI / 36), radius*std::sin(theta + 2*PI / 36), 0.0);
		m->V[i+3].set(radius*std::cos(theta + 3*PI / 36), radius*std::sin(theta + 3*PI / 36), 0.0);
		m->V[i+4].set(radius*std::cos(theta + 4*PI / 36), radius*std::sin(theta + 4*PI / 36), 0.0);
		m->V[i+5].set(radius*std::cos(theta + 5 * PI / 36), radius*std::sin(theta + 5 * PI / 36), 0.0);
		m->V[i+6].set(radius*std::cos(theta + 6 * PI / 36), radius*std::sin(theta + 6 * PI / 36), 0.0);

		theta = theta + PI / 3;
	}
	for (int i = 44; i <= 79; i = i + 7) {
		m->V[43].set(0.0, 0.0, 1.0);
		m->V[i].set(radius*std::cos(theta), radius*std::sin(theta), 1.0);
		m->V[i + 1].set(radius*std::cos(theta + PI / 36), radius*std::sin(theta + PI / 36), 1.0);
		m->V[i + 2].set(radius*std::cos(theta + 2 * PI / 36), radius*std::sin(theta + 2 * PI / 36), 1.0);
		m->V[i + 3].set(radius*std::cos(theta + 3 * PI / 36), radius*std::sin(theta + 3 * PI / 36), 1.0);
		m->V[i + 4].set(radius*std::cos(theta + 4 * PI / 36), radius*std::sin(theta + 4 * PI / 36), 1.0);
		m->V[i + 5].set(radius*std::cos(theta + 5 * PI / 36), radius*std::sin(theta + 5 * PI / 36), 1.0);
		m->V[i + 6].set(radius*std::cos(theta + 6 * PI / 36), radius*std::sin(theta + 6 * PI / 36), 1.0);
		m->F.push().set(43, i, i + 1);
		m->F.push().set(43, i+1, i + 2);
		m->F.push().set(43, i+2, i + 3);
		m->F.push().set(43, i+3, i + 4);
		m->F.push().set(43, i+4, i + 5);
		m->F.push().set(43, i+5, i + 6);
		theta = theta + PI / 3;
	}
	for (int i = 0; i <= 40; i++) {
		m->F.push().set(i+44, i + 1, i + 2);
		m->F.push().set(i + 2, i + 45, i + 44);
	}

}

void MyViewer::make_my_cylinder(GsModel* m, double length) {

	SnModel* _model;
	_model = new SnModel;
	double theta = 0.0;

	m->V.size(290);

	for (int i = 1; i <=143; i=i+2) {
		m->V[0].set(0, 0, 0);
		m->V[i].set(std::cos(theta), std::sin(theta), 0.0);
		m->V[i+1].set(std::cos(theta + PI / 36), std::sin(theta + PI / 36), 0.0);
		m->F.push().set(0, i+1, i);
		theta = theta + PI / 36;
	}
	for (int i = 146; i <= 288; i = i + 2) {
		m->V[145].set(0.0, 0.0, length);
		m->V[i].set(std::cos(theta), std::sin(theta), length);
		m->V[i + 1].set(std::cos(theta + PI / 36), std::sin(theta + PI / 36), length);
		m->F.push().set(145, i, i +1);
		theta = theta + PI / 36;
	}
	for (int i = 0; i <=142; i++) {
		m->F.push().set(i+146, i+1, i+2);
		m->F.push().set(i+2, i+147, i+146);
	}
}

void MyViewer::make_my_cylinder_cs(GsModel* m, double length, double rad) {

	SnModel* _model;
	_model = new SnModel;
	double theta = 0.0;

	m->V.size(290);

	for (int i = 1; i <= 143; i = i + 2) {
		m->V[0].set(0, 0, 0);
		m->V[i].set(rad*std::cos(theta), rad*std::sin(theta), 0.0);
		m->V[i + 1].set(rad*std::cos(theta + PI / 36), rad*std::sin(theta + PI / 36), 0.0);
		m->F.push().set(0, i + 1, i);
		theta = theta + PI / 36;
	}
	for (int i = 146; i <= 288; i = i + 2) {
		m->V[145].set(0.0, 0.0, length);
		m->V[i].set(rad*std::cos(theta), rad*std::sin(theta), length);
		m->V[i + 1].set(rad*std::cos(theta + PI / 36), rad*std::sin(theta + PI / 36), length);
		m->F.push().set(145, i, i + 1);
		theta = theta + PI / 36;
	}
	for (int i = 0; i <= 142; i++) {
		m->F.push().set(i + 146, i + 1, i + 2);
		m->F.push().set(i + 2, i + 147, i + 146);
	}
}

void MyViewer::make_my_cylinder_hole(GsModel* m, double length, double irad, double orad) {

	SnModel* _model;
	_model = new SnModel;
	double theta = 0.0;

	m->V.size(580);

	for (int i = 1; i <= 143; i = i + 2) {
		m->V[0].set(0, 0, 0);
		m->V[i].set(orad*std::cos(theta), orad*std::sin(theta), 0.0);
		m->V[i + 1].set(orad*std::cos(theta + PI / 36), orad*std::sin(theta + PI / 36), 0.0);
		//m->F.push().set(0, i + 1, i);
		theta = theta + PI / 36;
	}
	for (int i = 146; i <= 288; i = i + 2) {
		m->V[145].set(0.0, 0.0, length);
		m->V[i].set(orad*std::cos(theta), orad*std::sin(theta), length);
		m->V[i + 1].set(orad*std::cos(theta + PI / 36), orad*std::sin(theta + PI / 36), length);
		//m->F.push().set(145, i, i + 1);
		theta = theta + PI / 36;
	}
	for (int i = 291; i <= 433; i = i + 2) {
		m->V[290].set(0, 0, 0);
		m->V[i].set(irad*std::cos(theta), irad*std::sin(theta), 0.0);
		m->V[i + 1].set(irad*std::cos(theta + PI / 36), irad*std::sin(theta + PI / 36), 0.0);
		//m->F.push().set(0, i + 1, i);
		theta = theta + PI / 36;
	}
	for (int i = 436; i <= 578; i = i + 2) {
		m->V[435].set(0.0, 0.0, length);
		m->V[i].set(irad*std::cos(theta), irad*std::sin(theta), length);
		m->V[i + 1].set(irad*std::cos(theta + PI / 36), irad*std::sin(theta + PI / 36), length);
		//m->F.push().set(145, i, i + 1);
		theta = theta + PI / 36;
	}

	for (int i = 0; i <= 142; i++) {
		m->F.push().set(i + 291, i + 2, i + 1);
		m->F.push().set(i + 2, i + 291, i + 292);
	}

	for (int i = 0; i <= 142; i++) {
		m->F.push().set(i + 146, i + 1, i + 2);
		m->F.push().set(i + 2, i + 147, i + 146);
	}

	for (int i = 145; i <= 287; i++) {
		m->F.push().set(i + 291, i + 1, i + 2);
		m->F.push().set(i + 2, i + 292, i + 291);
	}

	for (int i = 290; i <= 432; i++) {
		m->F.push().set(i + 146, i + 2, i + 1);
		m->F.push().set(i + 2, i + 146, i + 147);
	}

}

void MyViewer::make_my_gear(GsModel* m, double radius, double thickness, double cradius)
{
	SnModel* _model;
	_model = new SnModel;

	if (cradius > (radius - 3.0)) {
		cradius = (radius - 3.0);
	}

	int i;
	double theta = 0.0;

	m->V.size(196);//one:98,two:196

	m->V[0].set(0, 0, 0);
	m->V[97].set((radius)* std::cos(theta), (radius)* std::sin(theta), 0.0);

	m->V[98].set(0.0, 0.0, (thickness));
	m->V[195].set((radius)* std::cos(theta), (radius)* std::sin(theta), (thickness));

	for (i = 1; i <= 89; i = i + 8) {
		m->V[i].set((radius)* std::cos(theta), (radius)* std::sin(theta), 0.0);
		m->V[i + 1].set((radius)* std::cos(theta + PI / 36), (radius)* std::sin(theta + PI / 36), 0.0);
		m->V[i + 2].set((radius - 1.0)* std::cos(theta + 2 * PI / 36), (radius - 1.0)* std::sin(theta + 2 * PI / 36), 0.0);
		m->V[i + 3].set((cradius)* std::cos(theta + 2 * PI / 36), (cradius)* std::sin(theta + 2 * PI / 36), 0.0);
		m->V[i + 4].set((cradius)* std::cos(theta + 3 * PI / 36), (cradius)* std::sin(theta + 3 * PI / 36), 0.0);
		m->V[i + 5].set((cradius)* std::cos(theta + 4 * PI / 36), (cradius)* std::sin(theta + 4 * PI / 36), 0.0);
		m->V[i + 6].set((radius - 1.0)* std::cos(theta + 4 * PI / 36), (radius - 1.0)* std::sin(theta + 4 * PI / 36), 0.0);
		m->V[i + 7].set((radius)* std::cos(theta + 5 * PI / 36), (radius)* std::sin(theta + 5 * PI / 36), 0.0);
		theta += PI / 6;
	}

	for (i = 1; i <= 89; i = i + 8) {
		m->F.push().set(0, i, i + 1);
		m->F.push().set(0, i + 1, i + 2);
		m->F.push().set(0, i + 3, i + 4);
		m->F.push().set(0, i + 4, i + 5);
		m->F.push().set(0, i + 6, i + 7);
		m->F.push().set(0, i + 7, i + 8);
		m->F.push().set(0, i + 1, i);
		m->F.push().set(0, i + 2, i + 1);
		m->F.push().set(0, i + 4, i + 3);
		m->F.push().set(0, i + 5, i + 4);
		m->F.push().set(0, i + 7, i + 6);
		m->F.push().set(0, i + 8, i + 7);
	}

	for (i = 99; i <= 187; i = i + 8) {
		m->V[i].set((radius)* std::cos(theta), (radius)* std::sin(theta), (thickness));
		m->V[i + 1].set((radius)* std::cos(theta + PI / 36), (radius)* std::sin(theta + PI / 36), (thickness));
		m->V[i + 2].set((radius - 1)* std::cos(theta + 2 * PI / 36), (radius - 1)* std::sin(theta + 2 * PI / 36), (thickness));
		m->V[i + 3].set((cradius)* std::cos(theta + 2 * PI / 36), (cradius)* std::sin(theta + 2 * PI / 36), (thickness));
		m->V[i + 4].set((cradius)* std::cos(theta + 3 * PI / 36), (cradius)* std::sin(theta + 3 * PI / 36), (thickness));
		m->V[i + 5].set((cradius)* std::cos(theta + 4 * PI / 36), (cradius)* std::sin(theta + 4 * PI / 36), (thickness));
		m->V[i + 6].set((radius - 1)* std::cos(theta + 4 * PI / 36), (radius - 1)* std::sin(theta + 4 * PI / 36), (thickness));
		m->V[i + 7].set((radius)* std::cos(theta + 5 * PI / 36), (radius)* std::sin(theta + 5 * PI / 36), (thickness));
		theta += PI / 6;
	}

	for (i = 99; i <= 187; i = i + 8) {
		m->F.push().set(98, i, i + 1);
		m->F.push().set(98, i + 1, i + 2);
		m->F.push().set(98, i + 3, i + 4);
		m->F.push().set(98, i + 4, i + 5);
		m->F.push().set(98, i + 6, i + 7);
		m->F.push().set(98, i + 7, i + 8);
		m->F.push().set(98, i + 1, i);
		m->F.push().set(98, i + 2, i + 1);
		m->F.push().set(98, i + 4, i + 3);
		m->F.push().set(98, i + 5, i + 4);
		m->F.push().set(98, i + 7, i + 6);
		m->F.push().set(98, i + 8, i + 7);
	}

	for (i = 1; i <= 96; i++) {
		m->F.push().set(i, i + 99, i + 98);
		m->F.push().set(i + 1, i + 99, i);
	}

}

void MyViewer::make_my_gear_cs(GsModel* m, double radius, double thickness, double cradius, double gradius)
{
	SnModel* _model;
	_model = new SnModel;

	if (cradius > (radius - 3.0)) {
		cradius = (radius - 3.0);
	}

	double pluslength;
	if (radius >= gradius) {
		pluslength = radius - gradius;
	}

	if (cradius < (gradius - 3.0)) {
		cradius = (gradius - 3.0);
	}

	int i;
	double theta = 0.0;

	m->V.size(320);

	m->V[0].set(0.0, 0.0, 0.0);
	m->V[97].set((gradius)* std::cos(theta), (gradius)* std::sin(theta), 0.0);

	m->V[98].set(0.0, 0.0, (thickness));
	m->V[195].set((gradius)* std::cos(theta), (gradius)* std::sin(theta), (thickness));

	for (i = 1; i <= 89; i = i + 8) {
		m->V[i].set({ (gradius)* std::cos(theta)}, { (gradius)* std::sin(theta)}, 0.0);
		m->V[i + 1].set({ (gradius)* std::cos(theta + PI / 36)}, { (gradius)* std::sin(theta + PI / 36)}, 0.0);
		m->V[i + 2].set({ (gradius - 1.0)* std::cos(theta + 2 * PI / 36)}, { (gradius - 1.0)* std::sin(theta + 2 * PI / 36)}, 0.0);
		m->V[i + 3].set((cradius)* std::cos(theta), (cradius)* std::sin(theta), 0.0);
		m->V[i + 4].set((cradius)* std::cos(theta + 3 * PI / 36), (cradius)* std::sin(theta + 3 * PI / 36), 0.0);
		m->V[i + 5].set((cradius)* std::cos(theta + 6 * PI / 36), (cradius)* std::sin(theta + 6 * PI / 36), 0.0);
		m->V[i + 6].set({ (gradius - 1.0)* std::cos(theta + 4 * PI / 36)}, { (gradius - 1.0)* std::sin(theta + 4 * PI / 36)}, 0.0);
		m->V[i + 7].set({ (gradius)* std::cos(theta + 5 * PI / 36) }, { (gradius)* std::sin(theta + 5 * PI / 36)}, 0.0);
		theta += PI / 6;
	}

	for (i = 1; i <= 89; i = i + 8) {
		m->F.push().set(0, i, i + 1);
		m->F.push().set(0, i + 1, i + 2);
		m->F.push().set(0, i + 3, i + 4);
		m->F.push().set(0, i + 4, i + 5);
		m->F.push().set(0, i + 6, i + 7);
		m->F.push().set(0, i + 7, i + 8);
		m->F.push().set(0, i + 1, i);
		m->F.push().set(0, i + 2, i + 1);
		m->F.push().set(0, i + 4, i + 3);
		m->F.push().set(0, i + 5, i + 4);
		m->F.push().set(0, i + 7, i + 6);
		m->F.push().set(0, i + 8, i + 7);
	}

	for (i = 99; i <= 187; i = i + 8) {
		m->V[i].set((gradius)* std::cos(theta), (gradius)* std::sin(theta), (thickness));
		m->V[i + 1].set((gradius)* std::cos(theta + PI / 36), (gradius)* std::sin(theta + PI / 36), (thickness));
		m->V[i + 2].set((gradius-1)* std::cos(theta + 2 * PI / 36), (gradius-1)* std::sin(theta + 2 * PI / 36), (thickness));
		m->V[i + 3].set((cradius)* std::cos(theta), (cradius)* std::sin(theta), (thickness));
		m->V[i + 4].set((cradius)* std::cos(theta + 3 * PI / 36), (cradius)* std::sin(theta + 3 * PI / 36), (thickness));
		m->V[i + 5].set((cradius)* std::cos(theta + 6 * PI / 36), (cradius)* std::sin(theta + 6 * PI / 36), (thickness));
		m->V[i + 6].set((gradius-1)* std::cos(theta + 4 * PI / 36), (gradius-1)* std::sin(theta + 4 * PI / 36), (thickness));
		m->V[i + 7].set((gradius)* std::cos(theta + 5 * PI / 36), (gradius)* std::sin(theta + 5 * PI / 36), (thickness));
		theta += PI / 6;
	}

	for (i = 99; i <= 187; i = i + 8) {
		m->F.push().set(98, i, i + 1);
		m->F.push().set(98, i + 1, i + 2);
		m->F.push().set(98, i + 3, i + 4);
		m->F.push().set(98, i + 4, i + 5);
		m->F.push().set(98, i + 6, i + 7);
		m->F.push().set(98, i + 7, i + 8);
		m->F.push().set(98, i + 1, i);
		m->F.push().set(98, i + 2, i + 1);
		m->F.push().set(98, i + 4, i + 3);
		m->F.push().set(98, i + 5, i + 4);
		m->F.push().set(98, i + 7, i + 6);
		m->F.push().set(98, i + 8, i + 7);
	}
	
	for (i=1;i<=96;i++) {
		m->F.push().set(i,i+99,i+98);
		m->F.push().set(i+1,i+99,i);
	}

	m->V[196].set(0.0, 0.0, 0.0);
	m->V[257].set((gradius)* std::cos(theta) + (pluslength)* std::cos(theta), (gradius)* std::sin(theta) + (pluslength)* std::sin(theta), 0.0);
	m->V[258].set(0.0, 0.0, (thickness));
	m->V[319].set((gradius)* std::cos(theta) + (pluslength)* std::cos(theta), (gradius)* std::sin(theta) + (pluslength)* std::sin(theta), (thickness));

	for (i = 197; i <= 252; i = i + 5) {
		m->V[i].set({ (gradius)* std::cos(theta) + (pluslength)* std::cos(theta) }, { (gradius)* std::sin(theta) + (pluslength)* std::sin(theta) }, 0.0);
		m->V[i + 1].set({ (gradius)* std::cos(theta + PI / 36) + (pluslength)* std::cos(theta) }, { (gradius)* std::sin(theta + PI / 36) + (pluslength)* std::sin(theta) }, 0.0);
		m->V[i + 2].set({ (gradius - 1.0)* std::cos(theta + 2 * PI / 36) + (pluslength)* std::cos(theta) }, { (gradius - 1.0)* std::sin(theta + 2 * PI / 36) + (pluslength)* std::sin(theta) }, 0.0);
		m->V[i + 3].set({ (gradius - 1.0)* std::cos(theta + 4 * PI / 36) + (pluslength)* std::cos(theta + 6 * PI / 36) }, { (gradius - 1.0)* std::sin(theta + 4 * PI / 36) + (pluslength)* std::sin(theta + 6 * PI / 36) }, 0.0);
		m->V[i + 4].set({ (gradius)* std::cos(theta + 5 * PI / 36) + (pluslength)* std::cos(theta + 6 * PI / 36) }, { (gradius)* std::sin(theta + 5 * PI / 36) + (pluslength)* std::sin(theta + 6 * PI / 36) }, 0.0);
		theta += PI / 6;
	}

	for (i = 259; i <= 314; i = i + 5) {
		m->V[i].set((gradius)* std::cos(theta) + (pluslength)* std::cos(theta), (gradius)* std::sin(theta) + (pluslength)* std::sin(theta), (thickness));
		m->V[i + 1].set((gradius)* std::cos(theta + PI / 36) + (pluslength)* std::cos(theta), (gradius)* std::sin(theta + PI / 36) + (pluslength)* std::sin(theta), (thickness));
		m->V[i + 2].set((gradius - 1)* std::cos(theta + 2 * PI / 36) + (pluslength)* std::cos(theta), (gradius - 1)* std::sin(theta + 2 * PI / 36) + (pluslength)* std::sin(theta), (thickness));
		m->V[i + 3].set((gradius - 1)* std::cos(theta + 4 * PI / 36) + (pluslength)* std::cos(theta + 6 * PI / 36), (gradius - 1)* std::sin(theta + 4 * PI / 36) + (pluslength)* std::sin(theta + 6 * PI / 36), (thickness));
		m->V[i + 4].set((gradius)* std::cos(theta + 5 * PI / 36) + (pluslength)* std::cos(theta + 6 * PI / 36), (gradius)* std::sin(theta + 5 * PI / 36) + (pluslength)* std::sin(theta + 6 * PI / 36), (thickness));
		theta += PI / 6;
	}

	int k = 99;
	int j = 259;
	while (k<=187) {
		m->F.push().set(k, j, j + 1);
		m->F.push().set(j + 1, k + 2, k);
		m->F.push().set(k + 1, j + 1, j + 2);
		m->F.push().set(j + 2, k + 2, k + 1);
		m->F.push().set(k + 6, j + 3, j + 4);
		m->F.push().set(j + 4, k + 7, k + 6);
		m->F.push().set(k + 7, j + 4, j + 5);
		m->F.push().set(j + 5, k + 8, k + 7);
		m->F.push().set(k, j + 1, j);
		m->F.push().set(j + 1, k, k + 2);
		m->F.push().set(k + 1, j + 2, j + 1);
		m->F.push().set(j + 2, k + 1, k + 2);
		m->F.push().set(k + 6, j + 4, j + 3);
		m->F.push().set(j + 4, k + 6, k + 7);
		m->F.push().set(k + 7, j + 5, j + 4);
		m->F.push().set(j + 5, k + 7, k + 8);
		k = k + 8;
		j = j + 5;
	}

	k = 1;
	j = 197;
	while (k <= 89) {
		m->F.push().set(k, j+1, j );
		m->F.push().set(j + 1, k , k+2);
		m->F.push().set(k + 1, j +2, j + 1);
		m->F.push().set(j + 2, k + 1, k + 2);
		m->F.push().set(k + 6, j + 4, j + 3);
		m->F.push().set(j + 4, k + 6, k + 7);
		m->F.push().set(k + 7, j + 5, j + 4);
		m->F.push().set(j + 5, k + 7, k + 8);
		m->F.push().set(k, j, j + 1);
		m->F.push().set(j + 1, k + 2, k);
		m->F.push().set(k + 1, j + 1, j + 2);
		m->F.push().set(j + 2, k + 2, k + 1);
		m->F.push().set(k + 6, j + 3, j + 4);
		m->F.push().set(j + 4, k + 7, k + 6);
		m->F.push().set(k + 7, j + 4, j + 5);
		m->F.push().set(j + 5, k + 8, k + 7);
		k = k + 8;
		j = j + 5;
	}

	int a, b, c, d;
	a = 197; 
	b = 259;
	c = 3;
	d = 101;

	while(a<=252) {
		m->F.push().set(b, a, a + 1);//(259, 197, 198);
		m->F.push().set(a + 1, b + 1, b);//(198, 260, 259);
		m->F.push().set(b + 1, a + 1, a + 2);//(260, 198, 199);
		m->F.push().set(a + 2, b + 2, b + 1);//(199, 261, 260);
		m->F.push().set(b + 2, a + 2, c);//(261, 199, 3);
		m->F.push().set(c, d, b + 2);//(3, 101, 261);

		m->F.push().set(d + 4, c + 4, a + 3);//(105, 7, 200);
		m->F.push().set(a + 3, b + 3, d + 4);//(200, 262, 105);
		m->F.push().set(b + 3, a + 3, a + 4);//(262, 200, 201);
		m->F.push().set(a + 4, b + 4, b + 3);//(201, 263, 262);
		m->F.push().set(b + 4, a + 4, a + 5);//(263, 201, 202);
		m->F.push().set(a + 5, b + 5, b + 4);//(202, 264, 263);

		a = a + 5;
		b = b + 5;
		c = c + 8;
		d = d + 8;
	}
}

void MyViewer::make_my_gear_four(GsModel* m, double radius, double thickness, double cradius, double gradius)
{
	SnModel* _model;
	_model = new SnModel;

	if (cradius > (radius - 3.0)) {
		cradius = (radius - 3.0);
	}

	double pluslength;
	if (radius >= gradius) {
		pluslength = radius - gradius;
	}

	if (cradius < (gradius - 3.0)) {
		cradius = (gradius - 3.0);
	}

	int i;
	double theta = 0.0;

	m->V.size(112);

	m->V[0].set(0, 0, 0);
	m->V[33].set((gradius)* std::cos(theta), (gradius)* std::sin(theta), 0.0);

	m->V[34].set(0.0, 0.0, (thickness));
	m->V[67].set((gradius)* std::cos(theta), (gradius)* std::sin(theta), (thickness));

	for (i = 1; i <= 25; i = i + 8) {
		m->V[i].set({ (gradius)* std::cos(theta) }, { (gradius)* std::sin(theta) }, 0.0);
		m->V[i + 1].set({ (gradius)* std::cos(theta + PI / 36) }, { (gradius)* std::sin(theta + PI / 36) }, 0.0);
		m->V[i + 2].set({ (gradius - 1.0)* std::cos(theta + 2 * PI / 36) }, { (gradius - 1.0)* std::sin(theta + 2 * PI / 36) }, 0.0);
		m->V[i + 3].set((cradius)* std::cos(theta), (cradius)* std::sin(theta), 0.0);
		m->V[i + 4].set((cradius)* std::cos(theta + 9 * PI / 36), (cradius)* std::sin(theta + 9 * PI / 36), 0.0);
		m->V[i + 5].set((cradius)* std::cos(theta + 18 * PI / 36), (cradius)* std::sin(theta + 18 * PI / 36), 0.0);
		m->V[i + 6].set({ (gradius - 1.0)* std::cos(theta + 16 * PI / 36) }, { (gradius - 1.0)* std::sin(theta + 16 * PI / 36) }, 0.0);
		m->V[i + 7].set({ (gradius)* std::cos(theta + 17 * PI / 36) }, { (gradius)* std::sin(theta + 17 * PI / 36) }, 0.0);
		theta += PI / 2;
	}

	for (i = 1; i <= 25; i = i + 8) {
		m->F.push().set(0, i, i + 1);
		m->F.push().set(0, i + 1, i + 2);
		m->F.push().set(0, i + 3, i + 4);
		m->F.push().set(0, i + 4, i + 5);
		m->F.push().set(0, i + 6, i + 7);
		m->F.push().set(0, i + 7, i + 8);
		m->F.push().set(0, i + 1, i);
		m->F.push().set(0, i + 2, i + 1);
		m->F.push().set(0, i + 4, i + 3);
		m->F.push().set(0, i + 5, i + 4);
		m->F.push().set(0, i + 7, i + 6);
		m->F.push().set(0, i + 8, i + 7);
	}
	
	for (i = 35; i <= 59; i = i + 8) {
		m->V[i].set((gradius)* std::cos(theta), (gradius)* std::sin(theta), (thickness));
		m->V[i + 1].set((gradius)* std::cos(theta + PI / 36), (gradius)* std::sin(theta + PI / 36), (thickness));
		m->V[i + 2].set((gradius - 1)* std::cos(theta + 2 * PI / 36), (gradius - 1)* std::sin(theta + 2 * PI / 36), (thickness));
		m->V[i + 3].set((cradius)* std::cos(theta), (cradius)* std::sin(theta), (thickness));
		m->V[i + 4].set((cradius)* std::cos(theta + 9 * PI / 36), (cradius)* std::sin(theta + 9 * PI / 36), (thickness));
		m->V[i + 5].set((cradius)* std::cos(theta + 18 * PI / 36), (cradius)* std::sin(theta + 18 * PI / 36), (thickness));
		m->V[i + 6].set((gradius - 1)* std::cos(theta + 16 * PI / 36), (gradius - 1)* std::sin(theta + 16 * PI / 36), (thickness));
		m->V[i + 7].set((gradius)* std::cos(theta + 17 * PI / 36), (gradius)* std::sin(theta + 17 * PI / 36), (thickness));
		theta += PI / 2;
	}

	for (i = 35; i <= 59; i = i + 8) {
		m->F.push().set(34, i, i + 1);
		m->F.push().set(34, i + 1, i + 2);
		m->F.push().set(34, i + 3, i + 4);
		m->F.push().set(34, i + 4, i + 5);
		m->F.push().set(34, i + 6, i + 7);
		m->F.push().set(34, i + 7, i + 8);
		m->F.push().set(34, i + 1, i);
		m->F.push().set(34, i + 2, i + 1);
		m->F.push().set(34, i + 4, i + 3);
		m->F.push().set(34, i + 5, i + 4);
		m->F.push().set(34, i + 7, i + 6);
		m->F.push().set(34, i + 8, i + 7);
	}
	
	for (i = 1; i <= 32; i++) {
		m->F.push().set(i, i + 35, i + 34);
		m->F.push().set(i + 1, i + 35, i);
	}

	
	m->V[68].set(0, 0, 0);
	m->V[89].set((gradius)* std::cos(theta) + (pluslength)* std::cos(theta), (gradius)* std::sin(theta) + (pluslength)* std::sin(theta), 0.0);
	m->V[90].set(0.0, 0.0, (thickness));
	m->V[111].set((gradius)* std::cos(theta) + (pluslength)* std::cos(theta), (gradius)* std::sin(theta) + (pluslength)* std::sin(theta), (thickness));

	for (i = 69; i <= 84; i = i + 5) {
		m->V[i].set({ (gradius)* std::cos(theta) + (pluslength)* std::cos(theta) }, { (gradius)* std::sin(theta) + (pluslength)* std::sin(theta) }, 0.0);
		m->V[i + 1].set({ (gradius)* std::cos(theta + PI / 36) + (pluslength)* std::cos(theta) }, { (gradius)* std::sin(theta + PI / 36) + (pluslength)* std::sin(theta) }, 0.0);
		m->V[i + 2].set({ (gradius - 1.0)* std::cos(theta + 2 * PI / 36) + (pluslength)* std::cos(theta) }, { (gradius - 1.0)* std::sin(theta + 2 * PI / 36) + (pluslength)* std::sin(theta) }, 0.0);
		m->V[i + 3].set({ (gradius - 1.0)* std::cos(theta + 16 * PI / 36) + (pluslength)* std::cos(theta + 18 * PI / 36) }, { (gradius - 1.0)* std::sin(theta + 16 * PI / 36) + (pluslength)* std::sin(theta + 18 * PI / 36) }, 0.0);
		m->V[i + 4].set({ (gradius)* std::cos(theta + 17 * PI / 36) + (pluslength)* std::cos(theta + 18 * PI / 36) }, { (gradius)* std::sin(theta + 17 * PI / 36) + (pluslength)* std::sin(theta + 18 * PI / 36) }, 0.0);
		theta += PI / 2;
	}
	
	for (i = 91; i <= 106; i = i + 5) {
		m->V[i].set((gradius)* std::cos(theta) + (pluslength)* std::cos(theta), (gradius)* std::sin(theta) + (pluslength)* std::sin(theta), (thickness));
		m->V[i + 1].set((gradius)* std::cos(theta + PI / 36) + (pluslength)* std::cos(theta), (gradius)* std::sin(theta + PI / 36) + (pluslength)* std::sin(theta), (thickness));
		m->V[i + 2].set((gradius - 1)* std::cos(theta + 2 * PI / 36) + (pluslength)* std::cos(theta), (gradius - 1)* std::sin(theta + 2 * PI / 36) + (pluslength)* std::sin(theta), (thickness));
		m->V[i + 3].set((gradius - 1)* std::cos(theta + 16 * PI / 36) + (pluslength)* std::cos(theta + 18 * PI / 36), (gradius - 1)* std::sin(theta + 16 * PI / 36) + (pluslength)* std::sin(theta + 18 * PI / 36), (thickness));
		m->V[i + 4].set((gradius)* std::cos(theta + 17 * PI / 36) + (pluslength)* std::cos(theta + 18 * PI / 36), (gradius)* std::sin(theta + 17 * PI / 36) + (pluslength)* std::sin(theta + 18 * PI / 36), (thickness));
		theta += PI / 2;
	}
	
	
	int k = 35;
	int j = 91;
	while (k <= 59) {
		m->F.push().set(k, j, j+1);
		m->F.push().set(j + 1, k + 2, k);
		m->F.push().set(k + 1, j + 1, j + 2);
		m->F.push().set(j + 2, k + 2, k + 1);
		m->F.push().set(k + 6, j + 3, j + 4);
		m->F.push().set(j + 4, k + 7, k + 6);
		m->F.push().set(k + 7, j + 4, j + 5);
		m->F.push().set(j + 5, k + 8, k + 7);
		m->F.push().set(k, j + 1, j);
		m->F.push().set(j + 1, k, k + 2);
		m->F.push().set(k + 1, j + 2, j + 1);
		m->F.push().set(j + 2, k + 1, k + 2);
		m->F.push().set(k + 6, j + 4, j + 3);
		m->F.push().set(j + 4, k + 6, k + 7);
		m->F.push().set(k + 7, j + 5, j + 4);
		m->F.push().set(j + 5, k + 7, k + 8);
		k = k + 8;
		j = j + 5;
	}

	
	k = 1;
	j = 69;
	while (k <= 25) {
		m->F.push().set(k, j + 1, j);
		m->F.push().set(j + 1, k, k + 2);
		m->F.push().set(k + 1, j + 2, j + 1);
		m->F.push().set(j + 2, k + 1, k + 2);
		m->F.push().set(k + 6, j + 4, j + 3);
		m->F.push().set(j + 4, k + 6, k + 7);
		m->F.push().set(k + 7, j + 5, j + 4);
		m->F.push().set(j + 5, k + 7, k + 8);
		m->F.push().set(k, j, j + 1);
		m->F.push().set(j + 1, k + 2, k);
		m->F.push().set(k + 1, j + 1, j + 2);
		m->F.push().set(j + 2, k + 2, k + 1);
		m->F.push().set(k + 6, j + 3, j + 4);
		m->F.push().set(j + 4, k + 7, k + 6);
		m->F.push().set(k + 7, j + 4, j + 5);
		m->F.push().set(j + 5, k + 8, k + 7);
		k = k + 8;
		j = j + 5;
	}
	
	int a, b, c, d;
	a = 69;
	b = 91;
	c = 3;
	d = 37;

	while (a <= 84) {
		m->F.push().set(b, a, a + 1);
		m->F.push().set(a + 1, b + 1, b);
		m->F.push().set(b + 1, a + 1, a + 2);
		m->F.push().set(a + 2, b + 2, b + 1);
		m->F.push().set(b + 2, a + 2, c);
		m->F.push().set(c, d, b + 2);

		m->F.push().set(d + 4, c + 4, a + 3);
		m->F.push().set(a + 3, b + 3, d + 4);
		m->F.push().set(b + 3, a + 3, a + 4);
		m->F.push().set(a + 4, b + 4, b + 3);
		m->F.push().set(b + 4, a + 4, a + 5);
		m->F.push().set(a + 5, b + 5, b + 4);

		a = a + 5;
		b = b + 5;
		c = c + 8;
		d = d + 8;
	}
}

void MyViewer::make_my_belt(GsModel* m, int teeth, double bthickness)
{
	SnModel* _model;
	_model = new SnModel;
	double k = 0.0;
	double sizeX = 2 * (5 * std::cos(17 * PI / 36) + 7 * std::cos(16 *PI / 36));

	for (int i = 0; i<teeth * 22; i = i + 22) {
		m->V.size(i + 22);

		m->V[i].set(k*sizeX, 0.0, 0.0);
		m->V[i + 1].set(5 * std::cos(17 * PI / 36) + k*sizeX, 0.0, 0.0);
		m->V[i + 2].set(5 * std::cos(17 * PI / 36) + k*sizeX, 3.0, 0.0);
		m->V[i + 3].set(k*sizeX, 3.0, 0.0);
		m->V[i + 4].set(5 * std::cos(19 * PI / 36) + k*sizeX, 3.0, 0.0);
		m->V[i + 5].set(5 * std::cos(19 * PI / 36) + k*sizeX, 0.0, 0.0);
		m->V[i + 6].set(5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36) + k*sizeX, 0.0, 0.0);
		m->V[i + 7].set(5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36) + k*sizeX, -2.0, 0.0);
		m->V[i + 8].set(k*sizeX, -2.0, 0.0);
		m->V[i + 9].set(5 * std::cos(17 * PI / 36) + 7 * std::cos(16 * PI / 36) + k*sizeX, -2.0, 0.0);
		m->V[i + 10].set(5 * std::cos(17 * PI / 36) + 7 * std::cos(16 * PI / 36) + k*sizeX, 0.0, 0.0);

		m->V[i + 11].set(k*sizeX, 0.0, (bthickness));
		m->V[i + 12].set(5 * std::cos(17 * PI / 36) + k*sizeX, 0.0, (bthickness));
		m->V[i + 13].set(5 * std::cos(17 * PI / 36) + k*sizeX, 3.0, (bthickness));
		m->V[i + 14].set(k*sizeX, 3.0, (bthickness));
		m->V[i + 15].set(5 * std::cos(19 * PI / 36) + k*sizeX, 3.0, (bthickness));
		m->V[i + 16].set(5 * std::cos(19 * PI / 36) + k*sizeX, 0.0, (bthickness));
		m->V[i + 17].set(5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36) + k*sizeX, 0.0, (bthickness));
		m->V[i + 18].set(5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36) + k*sizeX, -2.0, (bthickness));
		m->V[i + 19].set(k*sizeX, -2.0, (bthickness));
		m->V[i + 20].set(5 * std::cos(17 * PI / 36) + 7 * std::cos(16 * PI / 36) + k*sizeX, -2.0, (bthickness));
		m->V[i + 21].set(5 * std::cos(17 * PI / 36) + 7 * std::cos(16 * PI / 36) + k*sizeX, 0.0, (bthickness));

		//face
		m->F.push().set(i, i + 1, i + 2);
		m->F.push().set(i, i + 2, i + 3);
		m->F.push().set(i, i + 3, i + 4);
		m->F.push().set(i, i + 4, i + 5);
		m->F.push().set(i, i + 5, i + 6);
		m->F.push().set(i, i + 6, i + 7);
		m->F.push().set(i, i + 7, i + 8);
		m->F.push().set(i, i + 8, i + 9);
		m->F.push().set(i, i + 9, i + 10);
		m->F.push().set(i + 11, i + 12, i + 13);
		m->F.push().set(i + 11, i + 13, i + 14);
		m->F.push().set(i + 11, i + 14, i + 15);
		m->F.push().set(i + 11, i + 15, i + 16);
		m->F.push().set(i + 11, i + 16, i + 17);
		m->F.push().set(i + 11, i + 17, i + 18);
		m->F.push().set(i + 11, i + 18, i + 19);
		m->F.push().set(i + 11, i + 19, i + 20);
		m->F.push().set(i + 11, i + 20, i + 21);

		//backface
		m->F.push().set(i, i + 2, i + 1);
		m->F.push().set(i, i + 3, i + 2);
		m->F.push().set(i, i + 4, i + 3);
		m->F.push().set(i, i + 5, i + 4);
		m->F.push().set(i, i + 6, i + 5);
		m->F.push().set(i, i + 7, i + 6);
		m->F.push().set(i, i + 8, i + 7);
		m->F.push().set(i, i + 9, i + 8);
		m->F.push().set(i, i + 10, i + 9);
		m->F.push().set(i + 11, i + 13, i + 12);
		m->F.push().set(i + 11, i + 14, i + 13);
		m->F.push().set(i + 11, i + 15, i + 14);
		m->F.push().set(i + 11, i + 16, i + 15);
		m->F.push().set(i + 11, i + 17, i + 16);
		m->F.push().set(i + 11, i + 18, i + 17);
		m->F.push().set(i + 11, i + 19, i + 18);
		m->F.push().set(i + 11, i + 20, i + 19);
		m->F.push().set(i + 11, i + 21, i + 20);


		//thickness
		m->F.push().set(i + 1, i + 13, i + 12);
		m->F.push().set(i + 13, i + 1, i + 2);
		m->F.push().set(i + 2, i + 15, i + 13);
		m->F.push().set(i + 15, i + 2, i + 4);
		m->F.push().set(i + 4, i + 16, i + 15);
		m->F.push().set(i + 16, i + 4, i + 5);
		m->F.push().set(i + 5, i + 17, i + 16);
		m->F.push().set(i + 17, i + 5, i + 6);
		m->F.push().set(i + 6, i + 18, i + 17);
		m->F.push().set(i + 18, i + 6, i + 7);
		m->F.push().set(i + 7, i + 20, i + 18);
		m->F.push().set(i + 20, i + 7, i + 9);
		m->F.push().set(i + 9, i + 21, i + 20);
		m->F.push().set(i + 21, i + 9, i + 10);
		m->F.push().set(i + 10, i + 12, i + 21);
		m->F.push().set(i + 12, i + 10, i + 1);
		k = k + 1;
	}


}

void MyViewer::make_my_belt_lp(GsModel* m, int teeth, double bthickness, int initial)
{
	SnModel* _model;
	_model = new SnModel;
	double k = 0.0;
	double sizeX = 2 * (5 * std::cos(17 * PI / 36) + 7 * std::cos(16 * PI / 36));

	for (int i = initial*23; i<teeth * 22; i = i + 22) {
		m->V.size(i + 22);

		m->V[i].set(k*sizeX, 0.0, 0.0);
		m->V[i + 1].set(5 * std::cos(17 * PI / 36) + k*sizeX, 0.0, 0.0);
		m->V[i + 2].set(5 * std::cos(17 * PI / 36) + k*sizeX, 3.0, 0.0);
		m->V[i + 3].set(k*sizeX, 3.0, 0.0);
		m->V[i + 4].set(5 * std::cos(19 * PI / 36) + k*sizeX, 3.0, 0.0);
		m->V[i + 5].set(5 * std::cos(19 * PI / 36) + k*sizeX, 0.0, 0.0);
		m->V[i + 6].set(5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36) + k*sizeX, 0.0, 0.0);
		m->V[i + 7].set(5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36) + k*sizeX, -2.0, 0.0);
		m->V[i + 8].set(k*sizeX, -2.0, 0.0);
		m->V[i + 9].set(5 * std::cos(17 * PI / 36) + 7 * std::cos(16 * PI / 36) + k*sizeX, -2.0, 0.0);
		m->V[i + 10].set(5 * std::cos(17 * PI / 36) + 7 * std::cos(16 * PI / 36) + k*sizeX, 0.0, 0.0);

		m->V[i + 11].set(k*sizeX, 0.0, (bthickness));
		m->V[i + 12].set(5 * std::cos(17 * PI / 36) + k*sizeX, 0.0, (bthickness));
		m->V[i + 13].set(5 * std::cos(17 * PI / 36) + k*sizeX, 3.0, (bthickness));
		m->V[i + 14].set(k*sizeX, 3.0, (bthickness));
		m->V[i + 15].set(5 * std::cos(19 * PI / 36) + k*sizeX, 3.0, (bthickness));
		m->V[i + 16].set(5 * std::cos(19 * PI / 36) + k*sizeX, 0.0, (bthickness));
		m->V[i + 17].set(5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36) + k*sizeX, 0.0, (bthickness));
		m->V[i + 18].set(5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36) + k*sizeX, -2.0, (bthickness));
		m->V[i + 19].set(k*sizeX, -2.0, (bthickness));
		m->V[i + 20].set(5 * std::cos(17 * PI / 36) + 7 * std::cos(16 * PI / 36) + k*sizeX, -2.0, (bthickness));
		m->V[i + 21].set(5 * std::cos(17 * PI / 36) + 7 * std::cos(16 * PI / 36) + k*sizeX, 0.0, (bthickness));

		//face
		m->F.push().set(i, i + 1, i + 2);
		m->F.push().set(i, i + 2, i + 3);
		m->F.push().set(i, i + 3, i + 4);
		m->F.push().set(i, i + 4, i + 5);
		m->F.push().set(i, i + 5, i + 6);
		m->F.push().set(i, i + 6, i + 7);
		m->F.push().set(i, i + 7, i + 8);
		m->F.push().set(i, i + 8, i + 9);
		m->F.push().set(i, i + 9, i + 10);
		m->F.push().set(i + 11, i + 12, i + 13);
		m->F.push().set(i + 11, i + 13, i + 14);
		m->F.push().set(i + 11, i + 14, i + 15);
		m->F.push().set(i + 11, i + 15, i + 16);
		m->F.push().set(i + 11, i + 16, i + 17);
		m->F.push().set(i + 11, i + 17, i + 18);
		m->F.push().set(i + 11, i + 18, i + 19);
		m->F.push().set(i + 11, i + 19, i + 20);
		m->F.push().set(i + 11, i + 20, i + 21);

		//backface
		m->F.push().set(i, i + 2, i + 1);
		m->F.push().set(i, i + 3, i + 2);
		m->F.push().set(i, i + 4, i + 3);
		m->F.push().set(i, i + 5, i + 4);
		m->F.push().set(i, i + 6, i + 5);
		m->F.push().set(i, i + 7, i + 6);
		m->F.push().set(i, i + 8, i + 7);
		m->F.push().set(i, i + 9, i + 8);
		m->F.push().set(i, i + 10, i + 9);
		m->F.push().set(i + 11, i + 13, i + 12);
		m->F.push().set(i + 11, i + 14, i + 13);
		m->F.push().set(i + 11, i + 15, i + 14);
		m->F.push().set(i + 11, i + 16, i + 15);
		m->F.push().set(i + 11, i + 17, i + 16);
		m->F.push().set(i + 11, i + 18, i + 17);
		m->F.push().set(i + 11, i + 19, i + 18);
		m->F.push().set(i + 11, i + 20, i + 19);
		m->F.push().set(i + 11, i + 21, i + 20);


		//thickness
		m->F.push().set(i + 1, i + 13, i + 12);
		m->F.push().set(i + 13, i + 1, i + 2);
		m->F.push().set(i + 2, i + 15, i + 13);
		m->F.push().set(i + 15, i + 2, i + 4);
		m->F.push().set(i + 4, i + 16, i + 15);
		m->F.push().set(i + 16, i + 4, i + 5);
		m->F.push().set(i + 5, i + 17, i + 16);
		m->F.push().set(i + 17, i + 5, i + 6);
		m->F.push().set(i + 6, i + 18, i + 17);
		m->F.push().set(i + 18, i + 6, i + 7);
		m->F.push().set(i + 7, i + 20, i + 18);
		m->F.push().set(i + 20, i + 7, i + 9);
		m->F.push().set(i + 9, i + 21, i + 20);
		m->F.push().set(i + 21, i + 9, i + 10);
		m->F.push().set(i + 10, i + 12, i + 21);
		m->F.push().set(i + 12, i + 10, i + 1);
		k = k + 1;
	}


}

void MyViewer::make_my_cube(GsModel* m, double width, double thickness) {

	SnModel* _model;
	_model = new SnModel;

	m->V.size(10);

	m->V[0].set(0.0, 0.0, 0.0);
	m->V[1].set(width, -width, 0.0);
	m->V[2].set(width, width, 0.0);
	m->V[3].set(-width, width, 1.0);
	m->V[4].set(-width, -width, 1.0);

	m->V[5].set(0.0, 0.0, thickness);
	m->V[6].set(width, -width, thickness);
	m->V[7].set(width, width, thickness);
	m->V[8].set(-width, width, thickness);
	m->V[9].set(-width, -width, thickness);

	m->F.push().set(0, 2, 1);
	m->F.push().set(0, 3, 2);
	m->F.push().set(0, 4, 3);
	m->F.push().set(0, 1, 4);

	m->F.push().set(5, 6, 7);
	m->F.push().set(5, 7, 8);
	m->F.push().set(5, 8, 9);
	m->F.push().set(5, 9, 6);

	m->F.push().set(6, 1, 2);
	m->F.push().set(2, 7, 6);
	m->F.push().set(7, 2, 3);
	m->F.push().set(3, 8, 7);
	m->F.push().set(8, 3, 4);
	m->F.push().set(4, 9, 8);
	m->F.push().set(9, 4, 1);
	m->F.push().set(1, 6, 9);
}

void MyViewer::build_scene ()
{
		
		float pi = (float)PI;
		
		//1. Building Clock

		//Plate1

		SnModel* _model;
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_cylinder_cs(_model->model(), 5, 125);

		SnGroup *p1 = new SnGroup;
		p1->separator(true);
		p1->add(_tp1 = new SnTransform); 
		p1->add(_model); 
		_tp1->get().translation(0,0 ,130);

		//Hand1-Second

		_model = new SnModel;
		_model->color(GsColor::red);
		make_my_hand(_model->model(), 115, 2);

		SnGroup *h1 = new SnGroup;
		h1->separator(true);
		h1->add(_th1 = new SnTransform); 
		h1->add(_model); 
		_th1->get().translation(0, 0, 160);

		//Hand2-Minute

		_model = new SnModel;
		_model->color(GsColor::black);
		make_my_hand(_model->model(), 115, 5);

		SnGroup *h2 = new SnGroup;
		h2->separator(true);
		h2->add(_th2 = new SnTransform); 
		h2->add(_model); 
		_th2->get().translation(0, 0, 150);

		//Hand3-Hour

		_model = new SnModel;
		_model->color(GsColor::black);
		make_my_hand(_model->model(), 90, 5);

		SnGroup *h3 = new SnGroup;
		h3->separator(true);
		h3->add(_th3 = new SnTransform); 
		h3->add(_model); 
		_th3->get().translation(0, 0, 140);

		//Clock1

		_model = new SnModel;
		_model->color(GsColor::lightgray);
		make_my_clock(_model->model(), 115, 0.0);

		SnGroup *cl1 = new SnGroup;
		cl1->separator(true);
		cl1->add(_cl1 = new SnTransform); 
		cl1->add(_model);
		_cl1->get().translation(0, 0, 135);

		//Clock2

		_model = new SnModel;
		_model->color(GsColor::white);
		make_my_clock(_model->model(), 115, PI/6);

		SnGroup *cl2 = new SnGroup;
		cl2->separator(true);
		cl2->add(_cl2 = new SnTransform); 
		cl2->add(_model); 
		_cl2->get().translation(0, 0, 135);

		//~Building Clocks
		//2. Building Gears
		
		//Gear1
		double G1rad = 8.0; //radius of Gear1
		double G1thick = 5.0; //thickness of Gear1
		double G1crad = 8.0; //radius of inner circle of Gear1
		double G1grad = 8.0;
		float G1cpx = 0;//center point-x of gear1
		float G1cpy = 0;//center point-y of gear1
		float G1cpz = (float)(G1thick) / 2 * (-1);//center point-z of gear1
		
		_model = new SnModel;
		_model->color(GsColor::black);
		make_my_gear_cs(_model->model(), (G1rad), (G1thick), (G1crad),(G1grad));

		SnGroup *g1 = new SnGroup;
		g1->separator(true);
		g1->add(_t1 = new SnTransform); // _t1 is a member variable, to save a direct access pointer to the transformation
		g1->add(_model); // gear 1
		_t1->get().translation(G1cpx, G1cpy, G1cpz);
		
		//Gear2
		double G2rad = 8.0; //radius of Gear2
		double G2thick = 5.0; //thickness of Gear2
		double G2crad = 5.0; //radius of inner circle of Gear2

		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_gear(_model->model(), (G2rad), (G2thick), (G2crad));

		SnGroup *g2 = new SnGroup;
		g2->separator(true);
		g2->add(_t2 = new SnTransform); // _t2 is a member variable, to save a direct access pointer to the transformation
		g2->add(_model); // gear 2
		_t2->get().translation(0, 0, (float)(G2thick) / 2 * (-1)+30);
		//_t2->get().rotx(pi / 2);

		GsVec t2;
		_t2->get().getrans(t2);
		_t2->get().rotz(pi/12);
		_t2->get().setrans(t2);

		//Gear3
		double G3rad = 16.0-7*std::cos(pi/9); //radius of Gear3
		double G3thick = 5.0; //thickness of Gear3
		double G3crad = 8.0; //radius of inner circle of Gear3

		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_gear(_model->model(), (G3rad), (G3thick), (G3crad));

		SnGroup *g3 = new SnGroup;
		g3->separator(true);
		g3->add(_t3 = new SnTransform); // _t3 is a member variable, to save a direct access pointer to the transformation
		g3->add(_model); // gear 3
		_t3->get().translation(16, 0, (float)(G3thick) / 2 * (-1) + 30);

		//Gear4
		double G4rad = 8.0; //radius of Gear4
		double G4thick =5.0; //thickness of Gear4
		double G4crad = 8.0; //radius of inner circle of Gear4

		_model = new SnModel;
		_model->color(GsColor::blue);
		make_my_gear(_model->model(), (G4rad), (G4thick), (G4crad));

		SnGroup *g4 = new SnGroup;
		g4->separator(true);
		g4->add(_t4 = new SnTransform); // _t4 is a member variable, to save a direct access pointer to the transformation
		g4->add(_model); // gear 4
		_t4->get().translation(16, 0, (float)(G4thick) / 2 * (-1)+40);
		
		GsVec t4;
		_t4->get().getrans(t4);
		_t4->get().rotz(pi / 12);
		_t4->get().setrans(t4);

		//Gear5
		double G5rad = 32-7*std::cos(pi/9); //radius of Gear5
		double G5thick = 5.0; //thickness of Gear5
		double G5crad = 24.0; //radius of inner circle of Gear5
		double G5grad = 8.0; //teeth size of that radius gear

		_model = new SnModel;
		_model->color(GsColor::blue);
		make_my_gear_cs(_model->model(), (G5rad), (G5thick), (G5crad), (G5grad));

		SnGroup *g5 = new SnGroup;
		g5->separator(true);
		g5->add(_t5 = new SnTransform); // _t5 is a member variable, to save a direct access pointer to the transformation
		g5->add(_model); // gear 5
		_t5->get().translation(48, 0, (float)(G5thick) / 2 * (-1)+40);
		
		//Gear5-2

		_model = new SnModel;
		_model->color(GsColor::blue);
		make_my_gear_cs(_model->model(), (G5rad), (G5thick), (G5crad), (G5grad));

		SnGroup *g5_2 = new SnGroup;
		g5_2->separator(true);
		g5_2->add(_t5_2 = new SnTransform); // _t5 is a member variable, to save a direct access pointer to the transformation
		g5_2->add(_model); // gear 5
		_t5_2->get().translation(48, 0, (float)(G5thick) / 2 * (-1) + 40);

		GsVec t5_2;
		_t5_2->get().getrans(t5_2);
		_t5_2->get().rotz(pi / 18);
		_t5_2->get().setrans(t5_2);

		//Gear5-3

		_model = new SnModel;
		_model->color(GsColor::blue);
		make_my_gear_cs(_model->model(), (G5rad), (G5thick), (G5crad), (G5grad));

		SnGroup *g5_3 = new SnGroup;
		g5_3->separator(true);
		g5_3->add(_t5_3 = new SnTransform); // _t5 is a member variable, to save a direct access pointer to the transformation
		g5_3->add(_model); // gear 5
		_t5_3->get().translation(48, 0, (float)(G5thick) / 2 * (-1) + 40);

		GsVec t5_3;
		_t5_3->get().getrans(t5_3);
		_t5_3->get().rotz(pi / 9);
		_t5_3->get().setrans(t5_3);

		//Gear6
		double G6rad = 16.0; //radius of Gear6
		double G6thick = 5.0; //thickness of Gear6
		double G6crad = 16.0; //radius of inner circle of Gear6
		double G6grad = 8.0;

		_model = new SnModel;
		_model->color(GsColor::gray);
		make_my_gear_cs(_model->model(), (G6rad), (G6thick), (G6crad),(G6grad));

		SnGroup *g6 = new SnGroup;
		g6->separator(true);
		g6->add(_t6 = new SnTransform); // _t6 is a member variable, to save a direct access pointer to the transformation
		g6->add(_model); // gear 6
		_t6->get().translation(48, 0, (float)(G6thick) / 2 * (-1)+50);
		
		GsVec t6;
		_t6->get().getrans(t6);
		_t6->get().rotz(pi / 8);
		_t6->get().setrans(t6);

		//Gear7
		double G7rad = 48-15*std::cos(pi/9); //radius of Gear7
		double G7thick = 5.0; //thickness of Gear7
		double G7crad = 32.0; //radius of inner circle of Gear7
		double G7grad = 8.0;

		_model = new SnModel;
		_model->color(GsColor::gray);
		make_my_gear_cs(_model->model(), (G7rad), (G7thick), (G7crad), (G7grad));

		SnGroup *g7 = new SnGroup;
		g7->separator(true);
		g7->add(_t7 = new SnTransform); // _t7 is a member variable, to save a direct access pointer to the transformation
		g7->add(_model); // gear 7
		_t7->get().translation(0, 0, (float)(G7thick) / 2 * (-1)+50);
		
		//Gear7-2
		
		_model = new SnModel;
		_model->color(GsColor::gray);
		make_my_gear_cs(_model->model(), (G7rad), (G7thick), (G7crad), (G7grad));

		SnGroup *g7_2 = new SnGroup;
		g7_2->separator(true);
		g7_2->add(_t7_2 = new SnTransform); // _t7 is a member variable, to save a direct access pointer to the transformation
		g7_2->add(_model); // gear 7
		_t7_2->get().translation(0, 0, (float)(G7thick) / 2 * (-1) + 50);

		GsVec t7_2;
		_t7_2->get().getrans(t7_2);
		_t7_2->get().rotz(pi / 24);
		_t7_2->get().setrans(t7_2);

		//Gear7-3

		_model = new SnModel;
		_model->color(GsColor::gray);
		make_my_gear_cs(_model->model(), (G7rad), (G7thick), (G7crad), (G7grad));

		SnGroup *g7_3 = new SnGroup;
		g7_3->separator(true);
		g7_3->add(_t7_3 = new SnTransform); // _t7 is a member variable, to save a direct access pointer to the transformation
		g7_3->add(_model); // gear 7
		_t7_3->get().translation(0, 0, (float)(G7thick) / 2 * (-1) + 50);

		GsVec t7_3;
		_t7_3->get().getrans(t7_3);
		_t7_3->get().rotz(pi / 12);
		_t7_3->get().setrans(t7_3);

		//Gear7-4

		_model = new SnModel;
		_model->color(GsColor::gray);
		make_my_gear_cs(_model->model(), (G7rad), (G7thick), (G7crad), (G7grad));

		SnGroup *g7_4 = new SnGroup;
		g7_4->separator(true);
		g7_4->add(_t7_4 = new SnTransform); // _t7 is a member variable, to save a direct access pointer to the transformation
		g7_4->add(_model); // gear 7
		_t7_4->get().translation(0, 0, (float)(G7thick) / 2 * (-1) + 50);

		GsVec t7_4;
		_t7_4->get().getrans(t7_4);
		_t7_4->get().rotz(pi / 8);
		_t7_4->get().setrans(t7_4);

		//Gear8
		double G8rad = 8.0; //radius of Gear8
		double G8thick = 5.0; //thickness of Gear8
		double G8crad = 8.0; //radius of inner circle of Gear8

		_model = new SnModel;
		_model->color(GsColor::green);
		make_my_gear(_model->model(), (G8rad), (G8thick), (G8crad));

		SnGroup *g8 = new SnGroup;
		g8->separator(true);
		g8->add(_t8 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		g8->add(_model); // gear 8
		_t8->get().translation(0, 0, (float)(G8thick) / 2 * (-1) + 60);

		GsVec t8;
		_t8->get().getrans(t8);
		_t8->get().rotz(pi / 12);
		_t8->get().setrans(t8);

		//Gear9
		double G9rad = 48-7*std::cos(pi/9); //radius of Gear8
		double G9thick = 5.0; //thickness of Gear8
		double G9crad = 40.0; //radius of inner circle of Gear8
		double G9grad = 8.0;

		_model = new SnModel;
		_model->color(GsColor::green);
		make_my_gear_cs(_model->model(), (G9rad), (G9thick), (G9crad),(G9grad));

		SnGroup *g9 = new SnGroup;
		g9->separator(true);
		g9->add(_t9 = new SnTransform); // _t9 is a member variable, to save a direct access pointer to the transformation
		g9->add(_model); // gear 9
		_t9->get().translation(48, 0, (float)(G9thick) / 2 * (-1) + 60);

		//Gear9-2
		
		_model = new SnModel;
		_model->color(GsColor::green);
		make_my_gear_cs(_model->model(), (G9rad), (G9thick), (G9crad), (G9grad));

		SnGroup *g9_2 = new SnGroup;
		g9_2->separator(true);
		g9_2->add(_t9_2 = new SnTransform); // _t9 is a member variable, to save a direct access pointer to the transformation
		g9_2->add(_model); // gear 9
		_t9_2->get().translation(48, 0, (float)(G9thick) / 2 * (-1) + 60);

		GsVec t9_2;
		_t9_2->get().getrans(t9_2);
		_t9_2->get().rotz(pi / 30);
		_t9_2->get().setrans(t9_2);

		//Gear9-3

		_model = new SnModel;
		_model->color(GsColor::green);
		make_my_gear_cs(_model->model(), (G9rad), (G9thick), (G9crad), (G9grad));

		SnGroup *g9_3 = new SnGroup;
		g9_3->separator(true);
		g9_3->add(_t9_3 = new SnTransform); // _t9 is a member variable, to save a direct access pointer to the transformation
		g9_3->add(_model); // gear 9
		_t9_3->get().translation(48, 0, (float)(G9thick) / 2 * (-1) + 60);

		GsVec t9_3;
		_t9_3->get().getrans(t9_3);
		_t9_3->get().rotz(pi / 15);
		_t9_3->get().setrans(t9_3);

		//Gear9-4

		_model = new SnModel;
		_model->color(GsColor::green);
		make_my_gear_cs(_model->model(), (G9rad), (G9thick), (G9crad), (G9grad));

		SnGroup *g9_4 = new SnGroup;
		g9_4->separator(true);
		g9_4->add(_t9_4 = new SnTransform); // _t9 is a member variable, to save a direct access pointer to the transformation
		g9_4->add(_model); // gear 9
		_t9_4->get().translation(48, 0, (float)(G9thick) / 2 * (-1) + 60);

		GsVec t9_4;
		_t9_4->get().getrans(t9_4);
		_t9_4->get().rotz(pi / 10);
		_t9_4->get().setrans(t9_4);

		//Gear9-5

		_model = new SnModel;
		_model->color(GsColor::green);
		make_my_gear_cs(_model->model(), (G9rad), (G9thick), (G9crad), (G9grad));

		SnGroup *g9_5 = new SnGroup;
		g9_5->separator(true);
		g9_5->add(_t9_5 = new SnTransform); // _t9 is a member variable, to save a direct access pointer to the transformation
		g9_5->add(_model); // gear 9
		_t9_5->get().translation(48, 0, (float)(G9thick) / 2 * (-1) + 60);

		GsVec t9_5;
		_t9_5->get().getrans(t9_5);
		_t9_5->get().rotz(2*pi / 15);
		_t9_5->get().setrans(t9_5);

		//Gear10
		double G10rad = 16.0; //radius of Gear10
		double G10thick = 5.0; //thickness of Gear10
		double G10crad = 16.0; //radius of inner circle of Gear10
		double G10grad = 8.0;

		_model = new SnModel;
		_model->color(GsColor::lightgray);
		make_my_gear_cs(_model->model(), (G10rad), (G10thick), (G10crad), (G10grad));

		SnGroup *g10 = new SnGroup;
		g10->separator(true);
		g10->add(_t10 = new SnTransform); // _t10 is a member variable, to save a direct access pointer to the transformation
		g10->add(_model); // gear 10
		_t10->get().translation(48, 0, (float)(G10thick) / 2 * (-1) + 70);

		GsVec t10;
		_t10->get().getrans(t10);
		_t10->get().rotz(pi / 8);
		_t10->get().setrans(t10);

		//Gear11
		double G11rad = 48-15*std::cos(pi/9); //radius of Gear11
		double G11thick = 5.0; //thickness of Gear11
		double G11crad = 32.0; //radius of inner circle of Gear11
		double G11grad = 8.0;

		_model = new SnModel;
		_model->color(GsColor::lightgray);
		make_my_gear_cs(_model->model(), (G11rad), (G11thick), (G11crad), (G11grad));

		SnGroup *g11 = new SnGroup;
		g11->separator(true);
		g11->add(_t11 = new SnTransform); // _t11 is a member variable, to save a direct access pointer to the transformation
		g11->add(_model); // gear 11
		_t11->get().translation(0, 0, (float)(G11thick) / 2 * (-1) + 70);

		//Gear11-2

		_model = new SnModel;
		_model->color(GsColor::lightgray);
		make_my_gear_cs(_model->model(), (G11rad), (G11thick), (G11crad), (G11grad));

		SnGroup *g11_2 = new SnGroup;
		g11_2->separator(true);
		g11_2->add(_t11_2 = new SnTransform); // _t11 is a member variable, to save a direct access pointer to the transformation
		g11_2->add(_model); // gear 11
		_t11_2->get().translation(0, 0, (float)(G11thick) / 2 * (-1) + 70);

		GsVec t11_2;
		_t11_2->get().getrans(t11_2);
		_t11_2->get().rotz(pi / 24);
		_t11_2->get().setrans(t11_2);

		//Gear11-3

		_model = new SnModel;
		_model->color(GsColor::lightgray);
		make_my_gear_cs(_model->model(), (G11rad), (G11thick), (G11crad), (G11grad));

		SnGroup *g11_3 = new SnGroup;
		g11_3->separator(true);
		g11_3->add(_t11_3 = new SnTransform); // _t11 is a member variable, to save a direct access pointer to the transformation
		g11_3->add(_model); // gear 11
		_t11_3->get().translation(0, 0, (float)(G11thick) / 2 * (-1) + 70);

		GsVec t11_3;
		_t11_3->get().getrans(t11_3);
		_t11_3->get().rotz(pi / 12);
		_t11_3->get().setrans(t11_3);

		//Gear11-4

		_model = new SnModel;
		_model->color(GsColor::lightgray);
		make_my_gear_cs(_model->model(), (G11rad), (G11thick), (G11crad), (G11grad));

		SnGroup *g11_4 = new SnGroup;
		g11_4->separator(true);
		g11_4->add(_t11_4 = new SnTransform); // _t11 is a member variable, to save a direct access pointer to the transformation
		g11_4->add(_model); // gear 11
		_t11_4->get().translation(0, 0, (float)(G11thick) / 2 * (-1) + 70);

		GsVec t11_4;
		_t11_4->get().getrans(t11_4);
		_t11_4->get().rotz(pi / 8);
		_t11_4->get().setrans(t11_4);

		//Gear12
		double G12rad = 24-7*std::cos(pi/9); //radius of Gear12
		double G12thick = 5.0; //thickness of Gear12
		double G12crad = 16.0; //radius of inner circle of Gear12
		double G12grad = 8.0;

		_model = new SnModel;
		_model->color(GsColor::blue);
		make_my_gear_cs(_model->model(), (G12rad), (G12thick), (G12crad), (G12grad));

		SnGroup *g12 = new SnGroup;
		g12->separator(true);
		g12->add(_t12 = new SnTransform); // _t12 is a member variable, to save a direct access pointer to the transformation
		g12->add(_model); // gear 12
		_t12->get().translation(0, 0, (float)(G12thick) / 2 * (-1) + 80);

		//Gear12-2

		_model = new SnModel;
		_model->color(GsColor::blue);
		make_my_gear_cs(_model->model(), (G12rad), (G12thick), (G12crad), (G12grad));

		SnGroup *g12_2 = new SnGroup;
		g12_2->separator(true);
		g12_2->add(_t12_2 = new SnTransform); // _t12 is a member variable, to save a direct access pointer to the transformation
		g12_2->add(_model); // gear 12
		_t12_2->get().translation(0, 0, (float)(G12thick) / 2 * (-1) + 80);

		GsVec t12_2;
		_t12_2->get().getrans(t12_2);
		_t12_2->get().rotz(pi / 12);
		_t12_2->get().setrans(t12_2);

		//Gear13
		double G13rad = 8.0; //radius of Gear13
		double G13thick = 5.0; //thickness of Gear13
		double G13crad = 8.0; //radius of inner circle of Gear13

		_model = new SnModel;
		_model->color(GsColor::blue);
		make_my_gear(_model->model(), (G13rad), (G13thick), (G13crad));

		SnGroup *g13 = new SnGroup;
		g13->separator(true);
		g13->add(_t13 = new SnTransform); // _t13 is a member variable, to save a direct access pointer to the transformation
		g13->add(_model); // gear 13
		_t13->get().translation(24, 0, (float)(G13thick) / 2 * (-1) + 80);

		GsVec t13;
		_t13->get().getrans(t13);
		_t13->get().rotz(pi / 12);
		_t13->get().setrans(t13);

		//Gear14
		double G14rad = 24-7*std::cos(pi/9); //radius of Gear14
		double G14thick = 5.0; //thickness of Gear14
		double G14crad = 16.0; //radius of inner circle of Gear14
		double G14grad = 8.0;

		_model = new SnModel;
		_model->color(GsColor::blue);
		make_my_gear_cs(_model->model(), (G14rad), (G14thick), (G14crad),(G14grad));

		SnGroup *g14 = new SnGroup;
		g14->separator(true);
		g14->add(_t14 = new SnTransform); // _t14 is a member variable, to save a direct access pointer to the transformation
		g14->add(_model); // gear 14
		_t14->get().translation(48, 0, (float)(G14thick) / 2 * (-1) + 80);

		//Gear14-2
		
		_model = new SnModel;
		_model->color(GsColor::blue);
		make_my_gear_cs(_model->model(), (G14rad), (G14thick), (G14crad), (G14grad));

		SnGroup *g14_2 = new SnGroup;
		g14_2->separator(true);
		g14_2->add(_t14_2 = new SnTransform); // _t14 is a member variable, to save a direct access pointer to the transformation
		g14_2->add(_model); // gear 14
		_t14_2->get().translation(48, 0, (float)(G14thick) / 2 * (-1) + 80);

		GsVec t14_2;
		_t14_2->get().getrans(t14_2);
		_t14_2->get().rotz(pi / 12);
		_t14_2->get().setrans(t14_2);

		//Gear15
		double G15rad = 16.0; //radius of Gear15
		double G15thick = 5.0; //thickness of Gear15
		double G15crad = 16.0; //radius of inner circle of Gear15
		double G15grad = 8.0;

		_model = new SnModel;
		_model->color(GsColor::gray);
		make_my_gear_cs(_model->model(), (G15rad), (G15thick), (G15crad), (G15grad));

		SnGroup *g15 = new SnGroup;
		g15->separator(true);
		g15->add(_t15 = new SnTransform); // _t15 is a member variable, to save a direct access pointer to the transformation
		g15->add(_model); // gear 15
		_t15->get().translation(48, 0, (float)(G15thick) / 2 * (-1) + 90);

		GsVec t15;
		_t15->get().getrans(t15);
		_t15->get().rotz(pi / 8);
		_t15->get().setrans(t15);

		//Gear16
		double G16rad = 48-15*std::cos(pi/9); //radius of Gear16
		double G16thick = 5.0; //thickness of Gear16
		double G16crad = 32.0; //radius of inner circle of Gear16
		double G16grad = 8.0;

		_model = new SnModel;
		_model->color(GsColor::gray);
		make_my_gear_cs(_model->model(), (G16rad), (G16thick), (G16crad), (G16grad));

		SnGroup *g16 = new SnGroup;
		g16->separator(true);
		g16->add(_t16 = new SnTransform); // _t16 is a member variable, to save a direct access pointer to the transformation
		g16->add(_model); // gear 16
		_t16->get().translation(0, 0, (float)(G16thick) / 2 * (-1) + 90);

		//Gear16-2

		_model = new SnModel;
		_model->color(GsColor::gray);
		make_my_gear_cs(_model->model(), (G16rad), (G16thick), (G16crad), (G16grad));

		SnGroup *g16_2 = new SnGroup;
		g16_2->separator(true);
		g16_2->add(_t16_2 = new SnTransform); // _t16 is a member variable, to save a direct access pointer to the transformation
		g16_2->add(_model); // gear 16
		_t16_2->get().translation(0, 0, (float)(G16thick) / 2 * (-1) + 90);

		GsVec t16_2;
		_t16_2->get().getrans(t16_2);
		_t16_2->get().rotz(pi / 24);
		_t16_2->get().setrans(t16_2);

		//Gear16-3

		_model = new SnModel;
		_model->color(GsColor::gray);
		make_my_gear_cs(_model->model(), (G16rad), (G16thick), (G16crad), (G16grad));

		SnGroup *g16_3 = new SnGroup;
		g16_3->separator(true);
		g16_3->add(_t16_3 = new SnTransform); // _t16 is a member variable, to save a direct access pointer to the transformation
		g16_3->add(_model); // gear 16
		_t16_3->get().translation(0, 0, (float)(G16thick) / 2 * (-1) + 90);

		GsVec t16_3;
		_t16_3->get().getrans(t16_3);
		_t16_3->get().rotz(pi / 12);
		_t16_3->get().setrans(t16_3);

		//Gear16-4

		_model = new SnModel;
		_model->color(GsColor::gray);
		make_my_gear_cs(_model->model(), (G16rad), (G16thick), (G16crad), (G16grad));

		SnGroup *g16_4 = new SnGroup;
		g16_4->separator(true);
		g16_4->add(_t16_4 = new SnTransform); // _t16 is a member variable, to save a direct access pointer to the transformation
		g16_4->add(_model); // gear 16
		_t16_4->get().translation(0, 0, (float)(G16thick) / 2 * (-1) + 90);

		GsVec t16_4;
		_t16_4->get().getrans(t16_4);
		_t16_4->get().rotz(pi / 8);
		_t16_4->get().setrans(t16_4);

		//Gear17
		double G17rad = 8.0; //radius of Gear17
		double G17thick = 5.0; //thickness of Gear17
		double G17crad = 8.0; //radius of inner circle of Gear17
		
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_gear(_model->model(), (G17rad), (G17thick), (G17crad));

		SnGroup *g17 = new SnGroup;
		g17->separator(true);
		g17->add(_t17 = new SnTransform); // _t17 is a member variable, to save a direct access pointer to the transformation
		g17->add(_model); // gear 17
		_t17->get().translation(0, 0, (float)(G17thick) / 2 * (-1) + 100);

		GsVec t17;
		_t17->get().getrans(t17);
		_t17->get().rotz(pi / 12);
		_t17->get().setrans(t17);

		//Gear18
		double G18rad = 16-7*std::cos(pi/9); //radius of Gear18
		double G18thick = 5.0; //thickness of Gear18
		double G18crad = 8.0; //radius of inner circle of Gear18

		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_gear(_model->model(), (G18rad), (G18thick), (G18crad));

		SnGroup *g18 = new SnGroup;
		g18->separator(true);
		g18->add(_t18 = new SnTransform); // _t18 is a member variable, to save a direct access pointer to the transformation
		g18->add(_model); // gear 18
		_t18->get().translation(16, 0, (float)(G18thick) / 2 * (-1) + 100);

		//Gear19
		double G19rad = 8.0; //radius of Gear19
		double G19thick = 5.0; //thickness of Gear19
		double G19crad = 8.0; //radius of inner circle of Gear19

		_model = new SnModel;
		_model->color(GsColor::green);
		make_my_gear(_model->model(), (G19rad), (G19thick), (G19crad));

		SnGroup *g19 = new SnGroup;
		g19->separator(true);
		g19->add(_t19 = new SnTransform); // _t19 is a member variable, to save a direct access pointer to the transformation
		g19->add(_model); // gear 19
		_t19->get().translation(16, 0, (float)(G19thick) / 2 * (-1) + 110);

		GsVec t19;
		_t19->get().getrans(t19);
		_t19->get().rotz(pi / 12);
		_t19->get().setrans(t19);

		//Gear20
		double G20rad = 32-7*std::cos(pi/9); //radius of Gear20
		double G20thick = 5.0; //thickness of Gear20
		double G20crad = 24.0; //radius of inner circle of Gear20
		double G20grad = 8.0;

		_model = new SnModel;
		_model->color(GsColor::green);
		make_my_gear_cs(_model->model(), (G20rad), (G20thick), (G20crad),(G20grad));

		SnGroup *g20 = new SnGroup;
		g20->separator(true);
		g20->add(_t20 = new SnTransform); // _t20 is a member variable, to save a direct access pointer to the transformation
		g20->add(_model); // gear 20
		_t20->get().translation(48, 0, (float)(G20thick) / 2 * (-1) + 110);

		//Gear20-2
		
		_model = new SnModel;
		_model->color(GsColor::green);
		make_my_gear_cs(_model->model(), (G20rad), (G20thick), (G20crad), (G20grad));

		SnGroup *g20_2 = new SnGroup;
		g20_2->separator(true);
		g20_2->add(_t20_2 = new SnTransform); // _t20 is a member variable, to save a direct access pointer to the transformation
		g20_2->add(_model); // gear 20
		_t20_2->get().translation(48, 0, (float)(G20thick) / 2 * (-1) + 110);

		GsVec t20_2;
		_t20_2->get().getrans(t20_2);
		_t20_2->get().rotz(pi / 18);
		_t20_2->get().setrans(t20_2);

		//Gear20-3

		_model = new SnModel;
		_model->color(GsColor::green);
		make_my_gear_cs(_model->model(), (G20rad), (G20thick), (G20crad), (G20grad));

		SnGroup *g20_3 = new SnGroup;
		g20_3->separator(true);
		g20_3->add(_t20_3 = new SnTransform); // _t20 is a member variable, to save a direct access pointer to the transformation
		g20_3->add(_model); // gear 20
		_t20_3->get().translation(48, 0, (float)(G20thick) / 2 * (-1) + 110);

		GsVec t20_3;
		_t20_3->get().getrans(t20_3);
		_t20_3->get().rotz(pi / 9);
		_t20_3->get().setrans(t20_3);

		//Gear21
		double G21rad = 16.0; //radius of Gear21
		double G21thick = 5.0; //thickness of Gear21
		double G21crad = 16.0; //radius of inner circle of Gear21
		double G21grad = 8.0;

		_model = new SnModel;
		_model->color(GsColor::lightgray);
		make_my_gear_cs(_model->model(), (G21rad), (G21thick), (G21crad), (G21grad));

		SnGroup *g21 = new SnGroup;
		g21->separator(true);
		g21->add(_t21 = new SnTransform); // _t21 is a member variable, to save a direct access pointer to the transformation
		g21->add(_model); // gear 21
		_t21->get().translation(48, 0, (float)(G21thick) / 2 * (-1) + 120);

		GsVec t21;
		_t21->get().getrans(t21);
		_t21->get().rotz(pi / 8);
		_t21->get().setrans(t21);

		//Gear22
		double G22rad = 48-15*std::cos(pi/9); //radius of Gear22
		double G22thick = 5.0; //thickness of Gear22
		double G22crad = 32.0; //radius of inner circle of Gear22
		double G22grad = 8.0;

		_model = new SnModel;
		_model->color(GsColor::lightgray);
		make_my_gear_cs(_model->model(), (G22rad), (G22thick), (G22crad), (G22grad));

		SnGroup *g22 = new SnGroup;
		g22->separator(true);
		g22->add(_t22 = new SnTransform); // _t22 is a member variable, to save a direct access pointer to the transformation
		g22->add(_model); // gear 22
		_t22->get().translation(0, 0, (float)(G22thick) / 2 * (-1) + 120);

		//Gear22-2

		_model = new SnModel;
		_model->color(GsColor::lightgray);
		make_my_gear_cs(_model->model(), (G22rad), (G22thick), (G22crad), (G22grad));

		SnGroup *g22_2 = new SnGroup;
		g22_2->separator(true);
		g22_2->add(_t22_2 = new SnTransform); // _t22 is a member variable, to save a direct access pointer to the transformation
		g22_2->add(_model); // gear 22
		_t22_2->get().translation(0, 0, (float)(G22thick) / 2 * (-1) + 120);

		GsVec t22_2;
		_t22_2->get().getrans(t22_2);
		_t22_2->get().rotz(pi / 24);
		_t22_2->get().setrans(t22_2);

		//Gear22-3

		_model = new SnModel;
		_model->color(GsColor::lightgray);
		make_my_gear_cs(_model->model(), (G22rad), (G22thick), (G22crad), (G22grad));

		SnGroup *g22_3 = new SnGroup;
		g22_3->separator(true);
		g22_3->add(_t22_3 = new SnTransform); // _t22 is a member variable, to save a direct access pointer to the transformation
		g22_3->add(_model); // gear 22
		_t22_3->get().translation(0, 0, (float)(G22thick) / 2 * (-1) + 120);

		GsVec t22_3;
		_t22_3->get().getrans(t22_3);
		_t22_3->get().rotz(pi / 12);
		_t22_3->get().setrans(t22_3);

		//Gear22-4

		_model = new SnModel;
		_model->color(GsColor::lightgray);
		make_my_gear_cs(_model->model(), (G22rad), (G22thick), (G22crad), (G22grad));

		SnGroup *g22_4 = new SnGroup;
		g22_4->separator(true);
		g22_4->add(_t22_4 = new SnTransform); // _t22 is a member variable, to save a direct access pointer to the transformation
		g22_4->add(_model); // gear 22
		_t22_4->get().translation(0, 0, (float)(G22thick) / 2 * (-1) + 120);

		GsVec t22_4;
		_t22_4->get().getrans(t22_4);
		_t22_4->get().rotz(pi / 8);
		_t22_4->get().setrans(t22_4);

		//Gear23
		double G23rad = 24-7*std::cos(pi/9); //radius of Gear23
		double G23thick = 5.0; //thickness of Gear23
		double G23crad = 16.0; //radius of inner circle of Gear23
		double G23grad = 8.0;

		_model = new SnModel;
		_model->color(GsColor::green);
		make_my_gear_cs(_model->model(), (G23rad), (G23thick), (G23crad), (G23grad));

		SnGroup *g23 = new SnGroup;
		g23->separator(true);
		g23->add(_t23 = new SnTransform); // _t23 is a member variable, to save a direct access pointer to the transformation
		g23->add(_model); // gear 23
		_t23->get().translation(0, 0, (float)(G23thick) / 2 * (-1) + 20);


		//Gear23-2

		_model = new SnModel;
		_model->color(GsColor::green);
		make_my_gear_cs(_model->model(), (G23rad), (G23thick), (G23crad), (G23grad));

		SnGroup *g23_2 = new SnGroup;
		g23_2->separator(true);
		g23_2->add(_t23_2 = new SnTransform); // _t23 is a member variable, to save a direct access pointer to the transformation
		g23_2->add(_model); // gear 23
		_t23_2->get().translation(0, 0, (float)(G23thick) / 2 * (-1) + 20);

		GsVec t23_2;
		_t23_2->get().getrans(t23_2);
		_t23_2->get().rotz(pi / 12);
		_t23_2->get().setrans(t23_2);

		//Gear24
		double G24rad = 8.0; //radius of Gear24
		double G24thick = 5.0; //thickness of Gear24
		double G24crad = 8.0; //radius of inner circle of Gear24

		_model = new SnModel;
		_model->color(GsColor::green);
		make_my_gear(_model->model(), (G24rad), (G24thick), (G24crad));

		SnGroup *g24 = new SnGroup;
		g24->separator(true);
		g24->add(_t24 = new SnTransform); // _t24 is a member variable, to save a direct access pointer to the transformation
		g24->add(_model); // gear 24
		_t24->get().translation(24, 0, (float)(G24thick) / 2 * (-1) + 20);

		GsVec t24;
		_t24->get().getrans(t24);
		_t24->get().rotz(pi / 12);
		_t24->get().setrans(t24);

		//Gear25
		double G25rad = 24-7*std::cos(pi/9); //radius of Gear25
		double G25thick = 5.0; //thickness of Gear25
		double G25crad = 16.0; //radius of inner circle of Gear25
		double G25grad = 8.0;

		_model = new SnModel;
		_model->color(GsColor::green);
		make_my_gear_cs(_model->model(), (G25rad), (G25thick), (G25crad),(G25grad));

		SnGroup *g25 = new SnGroup;
		g25->separator(true);
		g25->add(_t25 = new SnTransform); // _t25 is a member variable, to save a direct access pointer to the transformation
		g25->add(_model); // gear 25
		_t25->get().translation(48, 0, (float)(G25thick) / 2 * (-1) + 20);

		//Gear25-2

		_model = new SnModel;
		_model->color(GsColor::green);
		make_my_gear_cs(_model->model(), (G25rad), (G25thick), (G25crad), (G25grad));

		SnGroup *g25_2 = new SnGroup;
		g25_2->separator(true);
		g25_2->add(_t25_2 = new SnTransform); // _t25 is a member variable, to save a direct access pointer to the transformation
		g25_2->add(_model); // gear 25
		_t25_2->get().translation(48, 0, (float)(G25thick) / 2 * (-1) + 20);

		GsVec t25_2;
		_t25_2->get().getrans(t25_2);
		_t25_2->get().rotz(pi / 12);
		_t25_2->get().setrans(t25_2);

		//Gear26
		double G26rad = 24.0; //radius of Gear26
		double G26thick = 5.0; //thickness of Gear26
		double G26crad = 24.0; //radius of inner circle of Gear26
		double G26grad = 8.0;

		_model = new SnModel;
		_model->color(GsColor::gray);
		make_my_gear_cs(_model->model(), (G26rad), (G26thick), (G26crad), (G26grad));

		SnGroup *g26 = new SnGroup;
		g26->separator(true);
		g26->add(_t26 = new SnTransform); // _t26 is a member variable, to save a direct access pointer to the transformation
		g26->add(_model); // gear 26
		_t26->get().translation(48, 0, (float)(G26thick) / 2 * (-1) + 10);
		
		GsVec t26;
		_t26->get().getrans(t26);
		_t26->get().rotz(pi/(float)30);
		_t26->get().setrans(t26);

		//Gear27
		double G27rad = 48-23*std::cos(pi/9); //radius of Gear27
		double G27thick = 5.0; //thickness of Gear27
		double G27crad = 24.0; //radius of inner circle of Gear27
		double G27grad = 8.0;

		_model = new SnModel;
		_model->color(GsColor::gray);
		make_my_gear_cs(_model->model(), (G27rad), (G27thick), (G27crad), (G27grad));

		SnGroup *g27 = new SnGroup;
		g27->separator(true);
		g27->add(_t27 = new SnTransform); // _t27 is a member variable, to save a direct access pointer to the transformation
		g27->add(_model); // gear 27
		_t27->get().translation(0, 0, (float)(G27thick) / 2 * (-1) + 10);
		
		//~Building Gears
		//3.Building Shafts

		//Shaft1
		_model = new SnModel;
		_model->color(GsColor::orange);
		make_my_cylinder(_model->model(), 19+150);

		SnGroup *s1 = new SnGroup;
		s1->separator(true);
		s1->add(_ts1 = new SnTransform);
		s1->add(_model); // shaft1
		_ts1->get().translation(0, 0,-4.5);

		//Shaft2
		_model = new SnModel;
		_model->color(GsColor::orange);
		make_my_cylinder(_model->model(), 19);

		SnGroup *s2 = new SnGroup;
		s2->separator(true);
		s2->add(_ts2 = new SnTransform); 
		s2->add(_model); // shaft2
		_ts2->get().translation(48, 0, 5.5);

		//Shaft3
		_model = new SnModel;
		_model->color(GsColor::orange);
		make_my_cylinder_hole(_model->model(), 19, 1.5, 2);

		SnGroup *s3 = new SnGroup;
		s3->separator(true);
		s3->add(_ts3 = new SnTransform); // _t11 is a member variable, to save a direct access pointer to the transformation
		s3->add(_model); // shaft3
		_ts3->get().translation(0, 0, 15.5);

		//Shaft4
		_model = new SnModel;
		_model->color(GsColor::orange);
		make_my_cylinder(_model->model(), 19);

		SnGroup *s4 = new SnGroup;
		s4->separator(true);
		s4->add(_ts4 = new SnTransform); // _t11 is a member variable, to save a direct access pointer to the transformation
		s4->add(_model); // shaft3
		_ts4->get().translation(16, 0, 25.5);

		//Shaft5
		_model = new SnModel;
		_model->color(GsColor::orange);
		make_my_cylinder(_model->model(), 19);

		SnGroup *s5 = new SnGroup;
		s5->separator(true);
		s5->add(_ts5 = new SnTransform); // _t11 is a member variable, to save a direct access pointer to the transformation
		s5->add(_model); // shaft3
		_ts5->get().translation(48, 0, 35.5);

		//Shaft6
		_model = new SnModel;
		_model->color(GsColor::orange);
		make_my_cylinder_hole(_model->model(), 19, 1.5,2);

		SnGroup *s6 = new SnGroup;
		s6->separator(true);
		s6->add(_ts6 = new SnTransform); // _t11 is a member variable, to save a direct access pointer to the transformation
		s6->add(_model); // shaft6
		_ts6->get().translation(0, 0, 45.5);

		//Shaft7
		_model = new SnModel;
		_model->color(GsColor::orange);
		make_my_cylinder(_model->model(), 19);

		SnGroup *s7 = new SnGroup;
		s7->separator(true);
		s7->add(_ts7 = new SnTransform); // _t11 is a member variable, to save a direct access pointer to the transformation
		s7->add(_model); // shaft6
		_ts7->get().translation(48, 0, 55.5);

		//Shaft8
		_model = new SnModel;
		_model->color(GsColor::orange);
		make_my_cylinder_hole(_model->model(), 19+70,1.5,2);

		SnGroup *s8 = new SnGroup;
		s8->separator(true);
		s8->add(_ts8 = new SnTransform); // _t11 is a member variable, to save a direct access pointer to the transformation
		s8->add(_model); // shaft8
		_ts8->get().translation(0, 0, 65.5);

		//Shaft9
		_model = new SnModel;
		_model->color(GsColor::orange);
		make_my_cylinder(_model->model(), 19);

		SnGroup *s9 = new SnGroup;
		s9->separator(true);
		s9->add(_ts9 = new SnTransform); // _t11 is a member variable, to save a direct access pointer to the transformation
		s9->add(_model); // shaft9
		_ts9->get().translation(48, 0, 75.5);

		//Shaft10
		_model = new SnModel;
		_model->color(GsColor::orange);
		make_my_cylinder_hole(_model->model(), 19, 2.5,3);

		SnGroup *s10 = new SnGroup;
		s10->separator(true);
		s10->add(_ts10 = new SnTransform); // _t11 is a member variable, to save a direct access pointer to the transformation
		s10->add(_model); // shaft10
		_ts10->get().translation(0, 0, 85.5);

		//Shaft11
		_model = new SnModel;
		_model->color(GsColor::orange);
		make_my_cylinder(_model->model(), 19);

		SnGroup *s11 = new SnGroup;
		s11->separator(true);
		s11->add(_ts11 = new SnTransform); // _t11 is a member variable, to save a direct access pointer to the transformation
		s11->add(_model); // shaft11
		_ts11->get().translation(16, 0, 95.5);

		//Shaft12
		_model = new SnModel;
		_model->color(GsColor::orange);
		make_my_cylinder(_model->model(), 19);

		SnGroup *s12 = new SnGroup;
		s12->separator(true);
		s12->add(_ts12 = new SnTransform); // _t11 is a member variable, to save a direct access pointer to the transformation
		s12->add(_model); // shaft12
		_ts12->get().translation(48, 0, 105.5);

		//Shaft13
		_model = new SnModel;
		_model->color(GsColor::orange);
		make_my_cylinder_hole(_model->model(), 19, 2.5,3);

		SnGroup *s13 = new SnGroup;
		s13->separator(true);
		s13->add(_ts13 = new SnTransform); // _t11 is a member variable, to save a direct access pointer to the transformation
		s13->add(_model); // shaft13
		_ts13->get().translation(0, 0, 125.5);

		//~Building Shafts
		//4. Building Linear Gear System
		
		//Belt
		double mid = 5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36);

		//Belt1
		int bteeth1 = 1;
		double bthickness1 = 8.0;

		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b1 = new SnGroup;
		b1->separator(true);
		b1->add(_tb1 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b1->add(_model); // belt 1
		_tb1->get().translation((float)(mid + (14) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt2
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b2 = new SnGroup;
		b2->separator(true);
		b2->add(_tb2 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b2->add(_model); // belt 1
		_tb2->get().translation((float)(mid + (13) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt3
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b3 = new SnGroup;
		b3->separator(true);
		b3->add(_tb3 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b3->add(_model); // belt 1
		_tb3->get().translation((float)(mid + (12) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt4
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b4 = new SnGroup;
		b4->separator(true);
		b4->add(_tb4 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b4->add(_model); // belt 1
		_tb4->get().translation((float)(mid + (11) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt5
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b5 = new SnGroup;
		b5->separator(true);
		b5->add(_tb5 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b5->add(_model); // belt 1
		_tb5->get().translation((float)(mid + (10) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt6
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b6 = new SnGroup;
		b6->separator(true);
		b6->add(_tb6 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b6->add(_model); // belt 1
		_tb6->get().translation((float)(mid + (9) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt7
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b7 = new SnGroup;
		b7->separator(true);
		b7->add(_tb7 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b7->add(_model); // belt 1
		_tb7->get().translation((float)(mid + (8) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt8
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b8 = new SnGroup;
		b8->separator(true);
		b8->add(_tb8 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b8->add(_model); // belt 1
		_tb8->get().translation((float)(mid + (7) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt9
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b9 = new SnGroup;
		b9->separator(true);
		b9->add(_tb9 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b9->add(_model); // belt 1
		_tb9->get().translation((float)(mid + (6) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt10
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b10 = new SnGroup;
		b10->separator(true);
		b10->add(_tb10 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b10->add(_model); // belt 1
		_tb10->get().translation((float)(mid + (5) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt11
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b11 = new SnGroup;
		b11->separator(true);
		b11->add(_tb11 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b11->add(_model); // belt 1
		_tb11->get().translation((float)(mid + (4) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt12
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b12 = new SnGroup;
		b12->separator(true);
		b12->add(_tb12 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b12->add(_model); // belt 1
		_tb12->get().translation((float)(mid + (3) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt13
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b13 = new SnGroup;
		b13->separator(true);
		b13->add(_tb13 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b13->add(_model); // belt 1
		_tb13->get().translation((float)(mid + (2) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt14
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b14 = new SnGroup;
		b14->separator(true);
		b14->add(_tb14 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b14->add(_model); // belt 1
		_tb14->get().translation((float)(mid + (1) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt15
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b15 = new SnGroup;
		b15->separator(true);
		b15->add(_tb15 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b15->add(_model); // belt 1
		_tb15->get().translation((float)(mid + (0) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt16
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b16 = new SnGroup;
		b16->separator(true);
		b16->add(_tb16 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b16->add(_model); // belt 1
		_tb16->get().translation((float)(mid + (-1) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt17
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b17 = new SnGroup;
		b17->separator(true);
		b17->add(_tb17 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b17->add(_model); // belt 1
		_tb17->get().translation((float)(mid + (-2) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt18
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b18 = new SnGroup;
		b18->separator(true);
		b18->add(_tb18 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b18->add(_model); // belt 1
		_tb18->get().translation((float)(mid + (-3) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt19
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b19 = new SnGroup;
		b19->separator(true);
		b19->add(_tb19 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b19->add(_model); // belt 1
		_tb19->get().translation((float)(mid + (-4) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt20
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b20 = new SnGroup;
		b20->separator(true);
		b20->add(_tb20 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b20->add(_model); // belt 1
		_tb20->get().translation((float)(mid + (-5) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt21
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b21 = new SnGroup;
		b21->separator(true);
		b21->add(_tb21 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b21->add(_model); // belt 1
		_tb21->get().translation((float)(mid + (-6) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt22
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b22 = new SnGroup;
		b22->separator(true);
		b22->add(_tb22 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b22->add(_model); // belt 1
		_tb22->get().translation((float)(mid + (-7) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt23
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b23 = new SnGroup;
		b23->separator(true);
		b23->add(_tb23 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b23->add(_model); // belt 1
		_tb23->get().translation((float)(mid + (-8) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt24
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b24 = new SnGroup;
		b24->separator(true);
		b24->add(_tb24 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b24->add(_model); // belt 1
		_tb24->get().translation((float)(mid + (-9) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt25
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b25 = new SnGroup;
		b25->separator(true);
		b25->add(_tb25 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b25->add(_model); // belt 1
		_tb25->get().translation((float)(mid + (-10) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt26
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b26 = new SnGroup;
		b26->separator(true);
		b26->add(_tb26 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b26->add(_model); // belt 1
		_tb26->get().translation((float)(mid + (-11) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt27
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b27 = new SnGroup;
		b27->separator(true);
		b27->add(_tb27 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b27->add(_model); // belt 1
		_tb27->get().translation((float)(mid + (-12) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt28
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b28 = new SnGroup;
		b28->separator(true);
		b28->add(_tb28 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b28->add(_model); // belt 1
		_tb28->get().translation((float)(mid + (-13) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt29
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b29 = new SnGroup;
		b29->separator(true);
		b29->add(_tb29 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b29->add(_model); // belt 1
		_tb29->get().translation((float)(mid + (-14) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt30
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b30 = new SnGroup;
		b30->separator(true);
		b30->add(_tb30 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b30->add(_model); // belt 1
		_tb30->get().translation((float)(mid + (-15) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Belt31
		_model = new SnModel;
		_model->color(GsColor::darkgray);
		make_my_belt(_model->model(), bteeth1, bthickness1);

		SnGroup *b31 = new SnGroup;
		b31->separator(true);
		b31->add(_tb31 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		b31->add(_model); // belt 1
		_tb31->get().translation((float)(mid + (-16) * 2 * mid), -9.5, (float)(bthickness1) / 2 * (-1));

		//Cube1
		_model = new SnModel;
		_model->color(GsColor::gray);
		make_my_cube(_model->model(), 6, 12);

		SnGroup *c1 = new SnGroup;
		c1->separator(true);
		c1->add(_tc1 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		c1->add(_model); // belt 1
		_tc1->get().translation((float)(mid + (14) * 2 * mid),-8.5, (float)12 / 2 * (-1));

		//Cube2
		_model = new SnModel;
		_model->color(GsColor::gray);
		make_my_cube(_model->model(), 6, 12);

		SnGroup *c2 = new SnGroup;
		c2->separator(true);
		c2->add(_tc2 = new SnTransform); // _t8 is a member variable, to save a direct access pointer to the transformation
		c2->add(_model); // belt 1
		_tc2->get().translation((float)(mid + (-16) * 2 * mid), -8.5, (float)12 / 2 * (-1));
		
		//~Building Linear Gear System

		//Adding the Groups
		
		rootg()->add(p1);

		rootg()->add(h1);
		rootg()->add(h2);
		rootg()->add(h3);
		
		rootg()->add(cl1);
		rootg()->add(cl2);
		
		
		rootg()->add(g1);	
		rootg()->add(g2);
		rootg()->add(g3);
		rootg()->add(g4);
		rootg()->add(g5); rootg()->add(g5_2); rootg()->add(g5_3);
		rootg()->add(g6);
		rootg()->add(g7); rootg()->add(g7_2); rootg()->add(g7_3); rootg()->add(g7_4); 
		rootg()->add(g8);
		rootg()->add(g9); rootg()->add(g9_2); rootg()->add(g9_3); rootg()->add(g9_4); rootg()->add(g9_5);		
		rootg()->add(g10);
		rootg()->add(g11); rootg()->add(g11_2); rootg()->add(g11_3); rootg()->add(g11_4);		
		rootg()->add(g12); rootg()->add(g12_2);
		rootg()->add(g13);
		rootg()->add(g14); rootg()->add(g14_2);		
		rootg()->add(g15);
		rootg()->add(g16); rootg()->add(g16_2); rootg()->add(g16_3); rootg()->add(g16_4);		
		rootg()->add(g17);
		rootg()->add(g18);
		rootg()->add(g19);
		rootg()->add(g20); rootg()->add(g20_2); rootg()->add(g20_3);		
		rootg()->add(g21);
		rootg()->add(g22); rootg()->add(g22_2); rootg()->add(g22_3); rootg()->add(g22_4);		
		rootg()->add(g23); rootg()->add(g23_2);
		rootg()->add(g24);
		rootg()->add(g25); rootg()->add(g25_2);
		rootg()->add(g26);
		rootg()->add(g27);
		
		
		rootg()->add(s1);
		rootg()->add(s2);
		rootg()->add(s3);
		rootg()->add(s4);
		rootg()->add(s5);
		rootg()->add(s6);
		rootg()->add(s7);
		rootg()->add(s8);
		rootg()->add(s9);
		rootg()->add(s10);
		rootg()->add(s11);
		rootg()->add(s12);
		rootg()->add(s13);
		
		
		rootg()->add(b1);
		rootg()->add(b2);
		rootg()->add(b3);
		rootg()->add(b4);
		rootg()->add(b5);
		rootg()->add(b6);
		rootg()->add(b7);
		rootg()->add(b8);
		rootg()->add(b9);
		rootg()->add(b10);
		rootg()->add(b11);
		rootg()->add(b12);
		rootg()->add(b13);
		rootg()->add(b14);
		rootg()->add(b15);
		rootg()->add(b16);
		rootg()->add(b17);
		rootg()->add(b18);
		rootg()->add(b19);
		rootg()->add(b20);
		rootg()->add(b21);
		rootg()->add(b22);
		rootg()->add(b23);
		rootg()->add(b24);
		rootg()->add(b25);
		rootg()->add(b26);
		rootg()->add(b27);
		rootg()->add(b28);
		rootg()->add(b29);
		rootg()->add(b30);
		rootg()->add(b31);
		
		rootg()->add(c1);
		rootg()->add(c2);
		
		}

void MyViewer::run_animation ()
{
	if (_animating) return; // avoid recursive calls
	_animating = true;

	int ind = gs_random(0, rootg()->size() - 1); // pick one child
	SnManipulator* manip = rootg()->get<SnManipulator>(ind); // access one of the manipulators
	GsMat m = manip->mat();

	_curang1 = 0;
	_curang2 = 0;
	_curang3 = 0;
	_curang4 = 0;
	_curang5 = 0;
	_curang6 = 0;
	_curang7 = 0;
	_curang8 = 0;
	_curang9 = 0;
	_curang10 = 0;
	_curang11 = 0;
	_curang12 = 0;
	_curang13 = 0;
	_curang14 = 0;
	_curang15 = 0;
	_curang16 = 0;
	_curang17 = 0;
	_curang18 = 0;
	_curang19 = 0;
	_curang20 = 0;
	_curang21 = 0;
	_curang22 = 0;
	_curang23 = 0;
	_curang24 = 0;
	_curang25 = 0;
	_curang26 = 0;
	_curang27 = 0;
	_curang28 = 0;
	_curang29 = 0;
	_curang30 = 0;

	_curx1 = 0;
	_curx2 = 0;
	_curx3 = 0;
	_curx4 = 0;
	_curx5 = 0;
	_curx6 = 0;
	_curx7 = 0;
	_curx8 = 0;
	_curx9 = 0;
	_curx10 = 0;
	_curx11 = 0;
	_curx12 = 0;
	_curx13 = 0;
	_curx14 = 0;
	_curx15 = 0;
	_curx16 = 0;
	_curx17 = 0;
	_curx18 = 0;
	_curx19 = 0;
	_curx20 = 0;
	_curx21 = 0;
	_curx22 = 0;
	_curx23 = 0;
	_curx24 = 0;
	_curx25 = 0;
	_curx26 = 0;
	_curx27 = 0;
	_curx28 = 0;
	_curx29 = 0;
	_curx30 = 0;
	_curx31 = 0;

	float pi = (float)PI;
	double frdt = 1.0 / 30.0; // delta time to reach given number of frames per second
	double v = 4; // target velocity is 1 unit per second
	double t = 0, lt = 0, t0 = gs_time(); 
	do // run for a while:
	{   
		while (t - lt<frdt) t = gs_time() - t0; // wait until it is time for next frame
		lt = t;
		GsVec tr1;
		_t1->get().getrans(tr1);
		_t1->get().rotz(_curang1);
		_t1->get().setrans(tr1);

		GsVec tr2;
		_t2->get().getrans(tr2);
		_t2->get().rotz(_curang2 + pi/12);
		_t2->get().setrans(tr2);
		
		GsVec tr3;
		_t3->get().getrans(tr3);
		_t3->get().rotz(_curang3);
		_t3->get().setrans(tr3);

		GsVec tr4;
		_t4->get().getrans(tr4);
		_t4->get().rotz(_curang4 + pi / 12);
		_t4->get().setrans(tr4);

		GsVec tr5;
		_t5->get().getrans(tr5);
		_t5->get().rotz(_curang5);
		_t5->get().setrans(tr5);

		GsVec tr5_2;
		_t5_2->get().getrans(tr5_2);
		_t5_2->get().rotz(_curang5+pi/18);
		_t5_2->get().setrans(tr5_2);

		GsVec tr5_3;
		_t5_3->get().getrans(tr5_3);
		_t5_3->get().rotz(_curang5 + pi / 9);
		_t5_3->get().setrans(tr5_3);

		GsVec tr6;
		_t6->get().getrans(tr6);
		_t6->get().rotz(_curang6 + pi / 8);
		_t6->get().setrans(tr6);

		GsVec tr7;
		_t7->get().getrans(tr7);
		_t7->get().rotz(_curang7);
		_t7->get().setrans(tr7);
		
		GsVec tr7_2;
		_t7_2->get().getrans(tr7_2);
		_t7_2->get().rotz(_curang7+pi/24);
		_t7_2->get().setrans(tr7_2);

		GsVec tr7_3;
		_t7_3->get().getrans(tr7_3);
		_t7_3->get().rotz(_curang7+pi/12);
		_t7_3->get().setrans(tr7_3);

		GsVec tr7_4;
		_t7_4->get().getrans(tr7_4);
		_t7_4->get().rotz(_curang7+pi/8);
		_t7_4->get().setrans(tr7_4);

		GsVec tr8;
		_t8->get().getrans(tr8);
		_t8->get().rotz(_curang8 + pi / 12);
		_t8->get().setrans(tr8);

		GsVec tr9;
		_t9->get().getrans(tr9);
		_t9->get().rotz(_curang9);
		_t9->get().setrans(tr9);

		GsVec tr9_2;
		_t9_2->get().getrans(tr9_2);
		_t9_2->get().rotz(_curang9 + pi / 30);
		_t9_2->get().setrans(tr9_2);

		GsVec tr9_3;
		_t9_3->get().getrans(tr9_3);
		_t9_3->get().rotz(_curang9 + pi / 15);
		_t9_3->get().setrans(tr9_3);

		GsVec tr9_4;
		_t9_4->get().getrans(tr9_4);
		_t9_4->get().rotz(_curang9 + pi / 10);
		_t9_4->get().setrans(tr9_4);

		GsVec tr9_5;
		_t9_5->get().getrans(tr9_5);
		_t9_5->get().rotz(_curang9 + 2*pi / 15);
		_t9_5->get().setrans(tr9_5);

		GsVec tr10;
		_t10->get().getrans(tr10);
		_t10->get().rotz(_curang10 + pi / 8);
		_t10->get().setrans(tr10);
		
		GsVec tr11;
		_t11->get().getrans(tr11);
		_t11->get().rotz(_curang11);
		_t11->get().setrans(tr11);

		GsVec tr11_2;
		_t11_2->get().getrans(tr11_2);
		_t11_2->get().rotz(_curang11 + pi / 24);
		_t11_2->get().setrans(tr11_2);

		GsVec tr11_3;
		_t11_3->get().getrans(tr11_3);
		_t11_3->get().rotz(_curang11 + pi / 12);
		_t11_3->get().setrans(tr11_3);

		GsVec tr11_4;
		_t11_4->get().getrans(tr11_4);
		_t11_4->get().rotz(_curang11 + pi / 8);
		_t11_4->get().setrans(tr11_4);

		GsVec tr12;
		_t12->get().getrans(tr12);
		_t12->get().rotz(_curang12);
		_t12->get().setrans(tr12);

		GsVec tr12_2;
		_t12_2->get().getrans(tr12_2);
		_t12_2->get().rotz(_curang12+pi/12);
		_t12_2->get().setrans(tr12_2);

		GsVec tr13;
		_t13->get().getrans(tr13);
		_t13->get().rotz(_curang13 + pi / 12);
		_t13->get().setrans(tr13);
		
		GsVec tr14;
		_t14->get().getrans(tr14);
		_t14->get().rotz(_curang14);
		_t14->get().setrans(tr14);

		GsVec tr14_2;
		_t14_2->get().getrans(tr14_2);
		_t14_2->get().rotz(_curang14+pi/12);
		_t14_2->get().setrans(tr14_2);

		GsVec tr15;
		_t15->get().getrans(tr15);
		_t15->get().rotz(_curang15 + pi / 8);
		_t15->get().setrans(tr15);

		GsVec tr16;
		_t16->get().getrans(tr16);
		_t16->get().rotz(_curang16);
		_t16->get().setrans(tr16);

		GsVec tr16_2;
		_t16_2->get().getrans(tr16_2);
		_t16_2->get().rotz(_curang16+pi/24);
		_t16_2->get().setrans(tr16);

		GsVec tr16_3;
		_t16_3->get().getrans(tr16_3);
		_t16_3->get().rotz(_curang16+pi/12);
		_t16_3->get().setrans(tr16_3);

		GsVec tr16_4;
		_t16_4->get().getrans(tr16_4);
		_t16_4->get().rotz(_curang16+pi/8);
		_t16_4->get().setrans(tr16_4);

		GsVec tr17;
		_t17->get().getrans(tr17);
		_t17->get().rotz(_curang17 + pi / 12);
		_t17->get().setrans(tr17);

		GsVec tr18;
		_t18->get().getrans(tr18);
		_t18->get().rotz(_curang18);
		_t18->get().setrans(tr18);

		GsVec tr19;
		_t19->get().getrans(tr19);
		_t19->get().rotz(_curang19 + pi / 12);
		_t19->get().setrans(tr19);
		
		GsVec tr20;
		_t20->get().getrans(tr20);
		_t20->get().rotz(_curang20);
		_t20->get().setrans(tr20);

		GsVec tr20_2;
		_t20_2->get().getrans(tr20_2);
		_t20_2->get().rotz(_curang20+pi/18);
		_t20_2->get().setrans(tr20_2);

		GsVec tr20_3;
		_t20_3->get().getrans(tr20_3);
		_t20_3->get().rotz(_curang20+pi/9);
		_t20_3->get().setrans(tr20_3);

		GsVec tr21;
		_t21->get().getrans(tr21);
		_t21->get().rotz(_curang21 + pi / 8);
		_t21->get().setrans(tr21);

		GsVec tr22;
		_t22->get().getrans(tr22);
		_t22->get().rotz(_curang22);
		_t22->get().setrans(tr22);

		GsVec tr22_2;
		_t22_2->get().getrans(tr22_2);
		_t22_2->get().rotz(_curang22+pi/24);
		_t22_2->get().setrans(tr22_2);

		GsVec tr22_3;
		_t22_3->get().getrans(tr22_3);
		_t22_3->get().rotz(_curang22+pi/12);
		_t22_3->get().setrans(tr22_3);

		GsVec tr22_4;
		_t22_4->get().getrans(tr22_4);
		_t22_4->get().rotz(_curang22+pi/8);
		_t22_4->get().setrans(tr22_4);

		GsVec tr23;
		_t23->get().getrans(tr23);
		_t23->get().rotz(_curang23);
		_t23->get().setrans(tr23);

		GsVec tr23_2;
		_t23_2->get().getrans(tr23_2);
		_t23_2->get().rotz(_curang23+pi/12);
		_t23_2->get().setrans(tr23_2);

		GsVec tr24;
		_t24->get().getrans(tr24);
		_t24->get().rotz(_curang24 + pi / 12);
		_t24->get().setrans(tr24);

		GsVec tr25;
		_t25->get().getrans(tr25);
		_t25->get().rotz(_curang25);
		_t25->get().setrans(tr25);

		GsVec tr25_2;
		_t25_2->get().getrans(tr25_2);
		_t25_2->get().rotz(_curang25+pi/12);
		_t25_2->get().setrans(tr25_2);

		GsVec tr26;
		_t26->get().getrans(tr26);
		_t26->get().rotz(_curang26 + pi / 30);
		_t26->get().setrans(tr26);

		GsVec tr27;
		_t27->get().getrans(tr27);
		_t27->get().rotz(_curang27);
		_t27->get().setrans(tr27);

		GsVec ts1;
		_ts1->get().getrans(ts1);
		_ts1->get().rotz(_curang27);
		_ts1->get().setrans(ts1);

		GsVec ts2;
		_ts2->get().getrans(ts2);
		_ts2->get().rotz(_curang25);
		_ts2->get().setrans(ts2);
		
		GsVec ts3;
		_ts3->get().getrans(ts3);
		_ts3->get().rotz(_curang2);
		_ts3->get().setrans(ts3);

		GsVec ts4;
		_ts4->get().getrans(ts4);
		_ts4->get().rotz(_curang4);
		_ts4->get().setrans(ts4);

		GsVec ts5;
		_ts5->get().getrans(ts5);
		_ts5->get().rotz(_curang6);
		_ts5->get().setrans(ts5);
		
		GsVec ts6;
		_ts6->get().getrans(ts6);
		_ts6->get().rotz(_curang8);
		_ts6->get().setrans(ts6);

		GsVec ts7;
		_ts7->get().getrans(ts7);
		_ts7->get().rotz(_curang10);
		_ts7->get().setrans(ts7);
		
		GsVec ts8;
		_ts8->get().getrans(ts8);
		_ts8->get().rotz(_curang12);
		_ts8->get().setrans(ts8);
		
		GsVec ts9;
		_ts9->get().getrans(ts9);
		_ts9->get().rotz(_curang15);
		_ts9->get().setrans(ts9);
		
		GsVec ts10;
		_ts10->get().getrans(ts10);
		_ts10->get().rotz(_curang17);
		_ts10->get().setrans(ts10);
		
		GsVec ts11;
		_ts11->get().getrans(ts11);
		_ts11->get().rotz(_curang19);
		_ts11->get().setrans(ts11);
		
		GsVec ts12;
		_ts12->get().getrans(ts12);
		_ts12->get().rotz(_curang21);
		_ts12->get().setrans(ts12);

		GsVec th1;
		_th1->get().getrans(th1);
		_th1->get().rotz(_curang27);
		_th1->get().setrans(th1);

		GsVec th2;
		_th2->get().getrans(th2);
		_th2->get().rotz(_curang12);
		_th2->get().setrans(th2);

		GsVec th3;
		_th3->get().getrans(th3);
		_th3->get().rotz(_curang22);
		_th3->get().setrans(th3);

		GsVec tb1;
		_tb1->get().getrans(tb1);
		if (tb1.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx1 = (float)(1.25*(-0.1805)+(-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb1->get().translation(tb1.x + _curx1, tb1.y, tb1.z);

		GsVec tb2;
		_tb2->get().getrans(tb2);
		if (tb2.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx2 = (float)(1.25*(-0.1805)+(-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb2->get().translation(tb2.x + _curx2, tb2.y, tb2.z);

		GsVec tb3;
		_tb3->get().getrans(tb3);
		if (tb3.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx3 = (float)(1.25*(-0.1805)+(-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb3->get().translation(tb3.x + _curx3, tb3.y, tb3.z);
		
		GsVec tb4;
		_tb4->get().getrans(tb4);
		if (tb4.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx4 = (float)(1.25*(-0.1805)+(-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb4->get().translation(tb4.x + _curx4, tb4.y, tb4.z);
		
		GsVec tb5;
		_tb5->get().getrans(tb5);
		if (tb5.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx5 = (float)(1.25*(-0.1805)+(-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb5->get().translation(tb5.x + _curx5, tb5.y, tb5.z);
		
		GsVec tb6;
		_tb6->get().getrans(tb6);
		if (tb6.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx6 = (float)(1.25*(-0.1805)+(-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb6->get().translation(tb6.x + _curx6, tb6.y, tb6.z);

		GsVec tb7;
		_tb7->get().getrans(tb7);
		if (tb7.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx7 = (float)(1.25*(-0.1805)+(-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb7->get().translation(tb7.x + _curx7, tb7.y, tb7.z);

		GsVec tb8;
		_tb8->get().getrans(tb8);
		if (tb8.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx8 = (float)(1.25*(-0.1805)+(-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb8->get().translation(tb8.x + _curx8, tb8.y, tb8.z);

		GsVec tb9;
		_tb9->get().getrans(tb9);
		if (tb9.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx9 = (float)(1.25*(-0.1805)+(-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb9->get().translation(tb9.x + _curx9, tb9.y, tb9.z);

		GsVec tb10;
		_tb10->get().getrans(tb10);
		if (tb10.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx10 = (float)(1.25*(-0.1805)+(-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb10->get().translation(tb10.x + _curx10, tb10.y, tb10.z);

		GsVec tb11;
		_tb11->get().getrans(tb11);
		if (tb11.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx11 = (float)(1.25*(-0.1805)+(-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb11->get().translation(tb11.x + _curx11, tb11.y, tb11.z);

		GsVec tb12;
		_tb12->get().getrans(tb12);
		if (tb12.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx12 = (float)(1.25*(-0.1805)+(-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb12->get().translation(tb12.x + _curx12, tb12.y, tb12.z);

		GsVec tb13;
		_tb13->get().getrans(tb13);
		if (tb13.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx13 = (float)(1.25*(-0.1805)+(-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb13->get().translation(tb13.x + _curx13, tb13.y, tb13.z);

		GsVec tb14;
		_tb14->get().getrans(tb14);
		if (tb14.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx14 = (float)(1.25*(-0.1805)+(-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb14->get().translation(tb14.x + _curx14, tb14.y, tb14.z);

		GsVec tb15;
		_tb15->get().getrans(tb15);
		if (tb15.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx15 = (float)(1.25*(-0.1805)+(-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb15->get().translation(tb15.x + _curx15, tb15.y, tb15.z);

		GsVec tb16;
		_tb16->get().getrans(tb16);
		if (tb16.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx16 = (float)(1.25*(-0.1805) + (-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb16->get().translation(tb16.x + _curx16, tb16.y, tb16.z);

		GsVec tb17;
		_tb17->get().getrans(tb17);
		if (tb17.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx17 = (float)(1.25*(-0.1805) + (-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb17->get().translation(tb17.x + _curx17, tb17.y, tb17.z);

		GsVec tb18;
		_tb18->get().getrans(tb18);
		if (tb18.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx18 = (float)(1.25*(-0.1805) + (-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb18->get().translation(tb18.x + _curx18, tb18.y, tb18.z);
		
		GsVec tb19;
		_tb19->get().getrans(tb19);
		if (tb19.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx19 = (float)(1.25*(-0.1805) + (-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb19->get().translation(tb19.x + _curx19, tb19.y, tb19.z);
		
		GsVec tb20;
		_tb20->get().getrans(tb20);
		if (tb20.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx20 = (float)(1.25*(-0.1805) + (-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb20->get().translation(tb20.x + _curx20, tb20.y, tb20.z);
		
		GsVec tb21;
		_tb21->get().getrans(tb21);
		if (tb21.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx21 = (float)(1.25*(-0.1805) + (-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb21->get().translation(tb21.x + _curx21, tb21.y, tb21.z);

		GsVec tb22;
		_tb22->get().getrans(tb22);
		if (tb22.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx22 = (float)(1.25*(-0.1805) + (-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb22->get().translation(tb22.x + _curx22, tb22.y, tb22.z);

		GsVec tb23;
		_tb23->get().getrans(tb23);
		if (tb23.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx23 = (float)(1.25*(-0.1805) + (-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb23->get().translation(tb23.x + _curx23, tb23.y, tb23.z);

		GsVec tb24;
		_tb24->get().getrans(tb24);
		if (tb24.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx24 = (float)(1.25*(-0.1805) + (-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb24->get().translation(tb24.x + _curx24, tb24.y, tb24.z);

		GsVec tb25;
		_tb25->get().getrans(tb25);
		if (tb25.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx25 = (float)(1.25*(-0.1805) + (-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb25->get().translation(tb25.x + _curx25, tb25.y, tb25.z);

		GsVec tb26;
		_tb26->get().getrans(tb26);
		if (tb26.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx26 = (float)(1.25*(-0.1805) + (-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb26->get().translation(tb26.x + _curx26, tb26.y, tb26.z);

		GsVec tb27;
		_tb27->get().getrans(tb27);
		if (tb27.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx27 = (float)(1.25*(-0.1805) + (-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb27->get().translation(tb27.x + _curx27, tb27.y, tb27.z);

		GsVec tb28;
		_tb28->get().getrans(tb28);
		if (tb28.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx28 = (float)(1.25*(-0.1805) + (-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb28->get().translation(tb28.x + _curx28, tb28.y, tb28.z);

		GsVec tb29;
		_tb29->get().getrans(tb29);
		if (tb29.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx29 = (float)(1.25*(-0.1805) + (-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb29->get().translation(tb29.x + _curx29, tb29.y, tb29.z);

		GsVec tb30;
		_tb30->get().getrans(tb30);
		if (tb30.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx30 = (float)(1.25*(-0.1805) + (-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb30->get().translation(tb30.x + _curx30, tb30.y, tb30.z);

		GsVec tb31;
		_tb31->get().getrans(tb31);
		if (tb31.x <= 31 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36))) {
			_curx31 = (float)(1.25*(-0.1805) + (-31) * 2 * (5 * std::cos(19 * PI / 36) + 7 * std::cos(20 * PI / 36)));
		}
		_tb31->get().translation(tb31.x + _curx31, tb31.y, tb31.z);

		float speed = (float)0.02864;
		float dis = (float)(0.18*180*speed/1.64/3.14);

		_curang1 -= speed; //rad//0.02864
		_curang2 += speed;
		_curang3 -= speed;
		_curang4 -= speed;
		_curang5 += (float)(speed /3.0);
		_curang6 += (float)(speed /3.0);
		_curang7 -= (float)(speed /6.0);
		_curang8 -= (float)(speed /6.0);
		_curang9 += (float)(speed /30.0);
		_curang10 += (float)(speed /30.0);
		_curang11 -= (float)(speed /60.0);
		_curang12 -= (float)(speed /60.0);
		_curang13 += (float)(speed /30.0);
		_curang14 -= (float)(speed /60.0);
		_curang15 -= (float)(speed /60.0);
		_curang16 += (float)(speed /120.0);
		_curang17 += (float)(speed /120.0);
		_curang18 -= (float)(speed /120.0);
		_curang19 -= (float)(speed /120.0);
		_curang20 += (float)(speed /360.0);
		_curang21 += (float)(speed /360.0);
		_curang22 -= (float)(speed /720.0);
		_curang23 += speed;
		_curang24 -= 2*speed;
		_curang25 += speed;
		_curang26 += speed;
		_curang27 -= speed;
		

		_curx1 = -dis;//distance
		_curx2 = -dis;//distance
		_curx3 = -dis;//distance
		_curx4 = -dis;//distance
		_curx5 = -dis;//distance
		_curx6 = -dis;//distance
		_curx7 = -dis;//distance
		_curx8 = -dis;//distance
		_curx9 = -dis;//distance
		_curx10 = -dis;//distance
		_curx11 = -dis;//distance
		_curx12 = -dis;//distance
		_curx13 = -dis;//distance
		_curx14 = -dis;//distance
		_curx15 = -dis;//distance
		_curx16 = -dis;//distance
		_curx17 = -dis;//distance
		_curx18 = -dis;//distance
		_curx19 = -dis;//distance
		_curx20 = -dis;//distance
		_curx21 = -dis;//distance
		_curx22 = -dis;//distance
		_curx23 = -dis;//distance
		_curx24 = -dis;//distance
		_curx25 = -dis;//distance
		_curx26 = -dis;//distance
		_curx27 = -dis;//distance
		_curx28 = -dis;//distance
		_curx29 = -dis;//distance
		_curx30 = -dis;//distance
		_curx31 = -dis;//distance

		render(); // notify it needs redraw
		ws_check(); // redraw now
	} while (true);// m.e24 > 0 );
	_animating = false;
	/**
	if ( _animating ) return; // avoid recursive calls
	_animating = true;
	
	int ind = gs_random ( 0, rootg()->size()-1 ); // pick one child
	SnManipulator* manip = rootg()->get<SnManipulator>(ind); // access one of the manipulators
	GsMat m = manip->mat();

	double frdt = 1.0/30.0; // delta time to reach given number of frames per second
	double v = 4; // target velocity is 1 unit per second
	double t=0, lt=0, t0=gs_time();
	do // run for a while:
	{	while ( t-lt<frdt ) t = gs_time()-t0; // wait until it is time for next frame
		double yinc = (t-lt)*v;
		if ( t>2 ) yinc=-yinc; // after 2 secs: go down
		lt = t;
		m.e24 += (float)yinc;
		if ( m.e24<0 ) m.e24=0; // make sure it does not go below 0
		manip->initial_mat ( m );
		render(); // notify it needs redraw
		ws_check(); // redraw now
	}	while ( m.e24>0 );
	_animating = false;
	**/
}

void MyViewer::show_normals ( bool b )
{
	// Note that primitives are only converted to meshes in GsModel
	// at the first draw call.
	GsArray<GsVec> fn;
	SnGroup* r = (SnGroup*)root();
	for ( int k=0; k<r->size(); k++ )
	{	SnManipulator* manip = r->get<SnManipulator>(k);
		SnShape* s = manip->child<SnGroup>()->get<SnShape>(0);
		SnLines* l = manip->child<SnGroup>()->get<SnLines>(1);
		if ( !b ) { l->visible(false); continue; }
		l->visible ( true );
		if ( !l->empty() ) continue; // build only once
		l->init();
		if ( s->instance_name()==SnPrimitive::class_name )
		{	GsModel& m = *((SnModel*)s)->model();
			m.get_normals_per_face ( fn );
			const GsVec* n = fn.pt();
			float f = 0.33f;
			for ( int i=0; i<m.F.size(); i++ )
			{	const GsVec& a=m.V[m.F[i].a]; l->push ( a, a+(*n++)*f );
				const GsVec& b=m.V[m.F[i].b]; l->push ( b, b+(*n++)*f );
				const GsVec& c=m.V[m.F[i].c]; l->push ( c, c+(*n++)*f );
			}
		}  
	}
}

int MyViewer::handle_keyboard ( const GsEvent &e )
{
	int ret = WsViewer::handle_keyboard ( e ); // 1st let system check events
	if ( ret ) return ret;

	switch ( e.key )
	{	case GsEvent::KeyEsc : gs_exit(); return 1;
		case 'n' : { bool b=!_nbut->value(); _nbut->value(b); show_normals(b); return 1; }
		default: gsout<<"Key pressed: "<<e.key<<gsnl;
	}

	return 0;
}

int MyViewer::uievent ( int e )
{
	switch ( e )
	{	case EvNormals: show_normals(_nbut->value()); return 1;
		case EvAnimate: run_animation(); return 1;
		case EvExit: gs_exit();
	}
	return WsViewer::uievent(e);
}
