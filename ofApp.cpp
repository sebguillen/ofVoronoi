#include "ofApp.h"
#include <iostream>

//--------------------------------------------------------------

// "The Voronoi Tessellation de- scribes a system of the self-organization of biological struc- tures visible on the wing of a dragonfly, the turtle shell, honeycomb or the shell of a sea urchin".
// Application of Voronoi diagrams in contemporary architecture and town planning written by Anna Nowak

//The Voronoi diagram is defined for a given set of n points as plain divided into n areas in such a manner that each point in any cell is closer to a specific point from a set of n points than the remaining n-1 points.

// While this technique is now mainly used for desiging buildings, I figured it was interesting to implement the voronoi diagram for the projection mapping to create visuals which hint at pattern found in nature.
// Made with the ofxVoronoi2d addon

void ofApp::setup(){
    ofSetFrameRate(60);
    count = 0;
    ofEnableAntiAliasing();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    alpha = 1;
    a = false;
    
// Set up the buffer
// I use a buffer to export the sketch in several pngs
// In this way I can export the visuals with no background and edit it in After effect afterwards to make it match the uv map of the 3D structure.
fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

}

//--------------------------------------------------------------
void ofApp::update(){
    
// Voronoi Canvas
  if(pts.size() != count){
    // Size of the canvas
    voronoi.compute(pts, ofRectangle(200, 250, ofGetWidth() - 200, 350), 100);
    count = pts.size();
    // Rebuild mesh
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

// cell center
      colors[mesh.getIndex(i + 0)] = ofFloatColor(1, 1, 1, alpha);
// cell border
      colors[mesh.getIndex(i + 1)] = ofFloatColor(r, 1, 1.0f, alpha);
      colors[mesh.getIndex(i + 2)] = ofFloatColor(0, 0, b, alpha);
    }
    }
    for(unsigned int i = 0; i < M; ++i) mesh.addColor(colors[i]);
  }
    
// Animation
// Using perlin noise to create a smooth random effect
    float time = ofGetElapsedTimef() / 5;
    float noise1 = ofNoise(10 * time);
    float noise2 = ofNoise(15 * time);
    // vX and vY are the coordinates of the points : ofVec2f(vX, vY)
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
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    
// FBO START
//    fbo.begin();
//    ofClear(255,255,255, 0);

// Draw cells
    mesh.draw();

// Possibility to draw the contours of the diagram
//    ofxSegmentIterator it = voronoi.edges();
//      for(; it; ++it){
//        ofxSegment e = *it;
//          ofSetLineWidth(5);
//        ofDrawLine(e.p1, e.p2);
//      }
    
// FBO END
    
//    fbo.end();
//    ofPixels pix;
//    fbo.readToPixels(pix);
//    ofSaveImage(pix, ofToString(counter)+".png", OF_IMAGE_QUALITY_BEST);
  }


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

