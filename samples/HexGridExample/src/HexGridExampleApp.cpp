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
    void draw_hex(GLenum mode, cell c, float cell_radius, orientation o);
};

void HexGridExampleApp::draw_hex(GLenum mode, cell c, float cell_radius, orientation o) {
    point p = lattice::cell_to_point(c, o, cell_radius);
    std::vector<point> vertices = o == orientation::flat ? cell::flat_vertices : cell::sharp_vertices;
    gl::begin(mode);
    for(auto vertex : vertices) {
        gl::vertex(p.x + vertex.x * cell_radius, p.y + vertex.y * cell_radius);
    }
    gl::end();
}

void HexGridExampleApp::setup() {
    l = hex::layout::hexagonal(3);
    l -= hex::layout::hexagonal(1);
    //l = hex::layout::parallelogram(10, 20, layout::options::vertical);
    //l = hex::layout::triangular(3, layout::options::flipped);
}

void HexGridExampleApp::draw() {
    gl::clear(Color(0, 0, 0));
    gl::ScopedMatrices matrix;
    gl::translate(getWindowCenter());
    gl::ScopedBlendAlpha alpha;
    
    gl::ScopedColor color1(0.25, 0.9, 0.95, 0.2);
    for(auto const& c : l) {
        draw_hex(GL_TRIANGLE_FAN, c, 16, orientation::flat);
    }
    
    gl::ScopedColor color2(0.25, 0.9, 1.0, 1.0);
    for(auto const& c : l) {
        draw_hex(GL_LINE_LOOP, c, 16, orientation::flat);
    }
}

CINDER_APP(HexGridExampleApp, RendererGl)
