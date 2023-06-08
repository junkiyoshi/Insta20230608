#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 60 == 0) {

		this->noise_seed = ofRandom(1000);
	}

	ofSeedRandom(this->noise_seed);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofColor color;
	int hue = ofRandom(255);
	float len = 15;

	for (int radius = 50; radius < 320; radius += 15) {

		ofRotateY(180);

		vector<glm::vec2> vertices_1, vertices_2;
		float direction = radius % 20 == 0 ? 1 : -1;
		float deg_start = ofRandom(360);
		float deg_len = (ofGetFrameNum() * 6) % 540;
		float deg_end = deg_start + deg_len;

		for (float deg = deg_start; deg < deg_end; deg += 1) {

			vertices_1.push_back(glm::vec2((radius - len * 0.5) * cos(deg * DEG_TO_RAD), (radius - len * 0.5) * sin(deg * DEG_TO_RAD)));
			vertices_2.push_back(glm::vec2((radius + len * 0.5) * cos(deg * DEG_TO_RAD), (radius + len * 0.5) * sin(deg * DEG_TO_RAD)));
		}

		reverse(vertices_2.begin(), vertices_2.end());
		
		color.setHsb(hue, 150, 255);

		ofFill();
		ofSetColor(color);

		ofBeginShape();
		ofVertices(vertices_1);
		ofVertices(vertices_2);
		ofEndShape(true);

		ofNoFill();
		ofSetColor(0);

		ofBeginShape();
		ofVertices(vertices_1);
		ofVertices(vertices_2);
		ofEndShape(true);

		hue = (hue + (int)ofRandom(20, 120)) % 255;
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}