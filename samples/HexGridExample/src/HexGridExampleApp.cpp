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
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    hex::cell c;
};

void HexGridExampleApp::setup()
{
}

void HexGridExampleApp::mouseDown( MouseEvent event )
{
}

void HexGridExampleApp::update()
{
}

void HexGridExampleApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( HexGridExampleApp, RendererGl )
