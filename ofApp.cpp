#include "ofApp.h"
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetFrameRate(60);
  count = 0;
   ofEnableAntiAliasing();
  ofEnableBlendMode(OF_BLENDMODE_ALPHA);
  // voronoi.setMinDist(std::epsilon<float>());
    back.load("merged.png");
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    alpha = 1;
    a = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // Voronoi Canvas
  if(pts.size() != count){
    voronoi.compute(pts, ofRectangle(200, 250, ofGetWidth() - 200, 350), 100);
    count = pts.size();
    // rebuild mesh
    mesh.clear();
    voronoi.buildMesh(mesh);

// Colors
    unsigned int N = mesh.getIndices().size(), M = mesh.getVertices().size();
    vector<ofFloatColor> colors;
    colors.resize(M);
    for(unsigned int i = 0; i < N; i += 3){
        for (int y = 0; y < 100; y ++){
            float time = ofGetElapsedTimef() / 2;
            float r = 1 + 0.3 * sin (y * 0.1 + time);
            float b = 1 + 0.3 * sin (y * 0.11 + time);
            std::cout<<r<<std::endl;
            std::cout<<b<<std::endl;

      colors[mesh.getIndex(i + 0)] = ofFloatColor(1, 1, 1, alpha);// c; // cell center
      colors[mesh.getIndex(i + 1)] = ofFloatColor(r, 1, 1.0f, alpha); // cell border
      colors[mesh.getIndex(i + 2)] = ofFloatColor(0, 0, b, alpha); // cell border
    }
    }
    for(unsigned int i = 0; i < M; ++i) mesh.addColor(colors[i]);
  }
    
// Developement
    float time = ofGetElapsedTimef() / 5;
    float noise1 = ofNoise(10 * time);
    float noise2 = ofNoise(15 * time);
    float vX = ofMap(noise1, 0.3, 0.7, 0, ofGetWidth());
    float vY = ofMap(noise2, 0.3, 0.7, 0, ofGetHeight());

// Push and erase
    int num = ofGetFrameNum();
    int n = ofNoise(time * 10) * 9;
    if (num % n == 0){
        pts.push_back(ofVec2f(vX, vY));
        a = !a;
        alpha = 1;
    }
    if (pts.size() >= 10){
        pts.erase(pts.begin());
        pts.erase(pts.begin() + 1);
        pts.erase(pts.begin() + 2);
        pts.erase(pts.begin() + 3);
    }
    
//    if (a){
//        float t = ofGetElapsedTimef();
//        float phase = sin (time);
//        alpha = ofMap(phase, -1, 1, 1, 0.9);
//    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    
//    back.draw(0,0);
    ofBackground(0);
    if(count < 1) return;
    
// FBO START

//    fbo.begin();
//    ofClear(255,255,255, 0);


// Modes
//  switch(dispMode){
//    case '1':
//      glPointSize(5.0f);
//      mesh.drawVertices();
//      // mesh.draw(OF_MESH_POINTS);
//      break;
//    case '2':
//      mesh.drawWireframe();
//      break;
//    case '3':
//      //mesh.draw(OF_MESH_FILL);
//      mesh.drawFaces();
//      break;
//    default:
    
// Draw cells
    mesh.draw();
//    ofxSegmentIterator it = voronoi.edges();
//      for(; it; ++it){
//        ofxSegment e = *it;
//          ofSetLineWidth(5);
//        ofDrawLine(e.p1, e.p2);
//      }
    
// FBO END
    
//    fbo.end();
//
//    ofPixels pix;
//    fbo.readToPixels(pix);
//    ofSaveImage(pix, ofToString(counter)+".png", OF_IMAGE_QUALITY_BEST);
  }


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  std::cout << "Pressed " << char(key) << " (int=" << key << ")\n";
  switch(key){
    case 'c':
      pts.clear();
      mesh.clear();
      count = 0; // commented to trigger voronoi update

      break;
    case 'f':
      ofToggleFullscreen();
      break;
    case '1':
    case '2':
    case '3':
    case '4':
      dispMode = key;
      break;
  }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
//  pts.push_back(ofVec2f(float(x), float(y)));
}

