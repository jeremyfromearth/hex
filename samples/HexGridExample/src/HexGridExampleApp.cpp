#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "hex.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace hex;

class HexGridExampleApp : public App {
public:
	void setup() override;
	void draw() override;
    
private:
    lattice l;
    void draw_hex(cell c, float cell_radius, orientation o);
};

void HexGridExampleApp::draw_hex(cell c, float cell_radius, orientation o) {
    gl::begin(GL_LINE_LOOP);
    point p = lattice::cell_to_point(c, o, cell_radius);
    std::vector<point> vertices = o == orientation::flat ? cell::flat_vertices() : cell::sharp_vertices();
    for(auto vertex : vertices) {
        gl::vertex(p.x + vertex.x * cell_radius, p.y + vertex.y * cell_radius);
    }
    gl::end();
}

void HexGridExampleApp::setup() {
    //l = hex::layout::hexagonal(3);
    l = hex::layout::rectangular(10, 5);
}

void HexGridExampleApp::draw() {
    gl::pushMatrices();
    gl::translate(getWindowCenter());
	gl::clear(Color( 1, 1, 1 ));
    gl::color(Color(0.1, 0.1, 0.4));
    for(auto c : l) {
        draw_hex(c, 10, orientation::sharp);
    }
    gl::popMatrices();
}

CINDER_APP(HexGridExampleApp, RendererGl)
