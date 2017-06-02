#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "hex.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HexGridExampleApp : public App {
public:
	void setup() override;
	void draw() override;
    void mouseMove(MouseEvent e) override;
    
private:
    hex::lattice l;
    int radius;
    hex::cell hover;
    hex::orientation orientation;
    void draw_hex(GLenum mode, hex::cell c, float cell_radius, enum hex::orientation o);
};

void HexGridExampleApp::draw_hex(GLenum mode, hex::cell c, float cell_radius, hex::orientation o) {
    hex::point p = hex::lattice::cell_to_point(c, o, cell_radius);
    std::vector<hex::point> vertices = o == hex::orientation::flat ? hex::cell::flat_vertices : hex::cell::sharp_vertices;
    gl::begin(mode);
    for(auto vertex : vertices) {
        gl::vertex(p.x + vertex.x * cell_radius, p.y + vertex.y * cell_radius);
    }
    gl::end();
}

void HexGridExampleApp::setup() {
    radius = 16;
    orientation = hex::orientation::sharp;
    
    l = hex::layout::hexagonal(6);
    l -= hex::layout::hexagonal(3);
    l += hex::layout::parallelogram(10, 10, hex::layout::options::vertical);
    l += hex::layout::parallelogram(10, 10, hex::layout::options::standard);
    l -= hex::layout::hexagonal(3);
    l += hex::layout::hexagonal(1);
}

void HexGridExampleApp::mouseMove(MouseEvent e) {
    vec2 v = vec2(e.getPos()) - getWindowCenter();
    hex::point p(v.x, v.y);
    hover = hex::lattice::point_to_cell(p, orientation, radius);
}

void HexGridExampleApp::draw() {
    gl::clear(Color(1, 1, 1));
    gl::ScopedMatrices matrix;
    gl::translate(getWindowCenter());
    gl::ScopedBlendAlpha alpha;
    gl::ScopedColor color1(0.1, 0.1, 0.1, 1.0);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LINE_SMOOTH_HINT);
    for(auto const& c : l) {
        draw_hex(GL_TRIANGLE_FAN, c, radius, orientation);
    }
    
    if(l.count(hover)) {
        gl::ScopedColor color3(1, 0, 0);
        draw_hex(GL_TRIANGLE_FAN, hover, radius, orientation);
    }
    
    gl::ScopedColor color2(1, 1, 1, 1.0);
    for(auto const& c : l) {
        draw_hex(GL_LINE_LOOP, c, radius, orientation);
    }
    
    
}

CINDER_APP(HexGridExampleApp, RendererGl)
