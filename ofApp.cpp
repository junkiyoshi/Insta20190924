#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(1);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(255);

	auto path = filesystem::path("PhotoDirectoryPath");
	vector<string> file_name_list;
	for (auto entry : filesystem::recursive_directory_iterator(path)) {

		file_name_list.push_back(entry.path().string());
	}

	this->image_size = 60;
	ofImage image = ofImage();
	while (this->image_list.size() < 150) {

		int random_index = ofRandom(file_name_list.size());

		auto image = ofImage();
		image.loadImage(file_name_list[random_index]);

		this->image_list.push_back(image);
	}
}


//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->draw_rectangle(3, glm::vec2(), ofGetWidth());
}

//--------------------------------------------------------------
void ofApp::draw_rectangle(int level, glm::vec2 location, int size){

	auto param = ofRandom(100);
	if (level > 2 || param < 50) {

		if (level > 0) {

			this->draw_rectangle(level - 1, location, size * 0.5);
			this->draw_rectangle(level - 1, location + glm::vec2(size * 0.5, 0), size * 0.5);
			this->draw_rectangle(level - 1, location + glm::vec2(0, size * 0.5), size * 0.5);
			this->draw_rectangle(level - 1, location + glm::vec2(size * 0.5, size * 0.5), size * 0.5);
		}
		else {

			int random_index = ofRandom(this->image_list.size());
			auto draw_image = this->image_list[random_index];
			draw_image.resize(size, size);
			draw_image.draw(location);
		}
	}
	else {

		int random_index = ofRandom(this->image_list.size());
		auto draw_image = this->image_list[random_index];
		draw_image.resize(size, size);
		draw_image.draw(location);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}