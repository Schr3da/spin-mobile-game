#include "PositionFactory.h"
#include <iostream>
#include "Settings.h"
#include "Logger.h"
#include <sstream>
#include "LocationVariables.h"
#include "Global.h"

PositionFactory PositionFactory::object = PositionFactory(); // initialize Singleton

PositionFactory::PositionFactory(){
    settings.init();
    this->startPosition=NULL;
    this->createPositions();
    Logger::log("PositionFactory initialized.", Logger::DEBUG);
}

PositionFactory::~PositionFactory(){
    int i=0;
    for (std::vector<CameraPosition*>::iterator iter = cameraPositions.begin(); iter!=cameraPositions.end();++iter){
	delete *iter;
	i++;
    }

    std::ostringstream msg;
    msg<<"~PositionFactory: deleted "<<i<<" CameraPosition objects.";
    Logger::log(msg.str(),Logger::DEBUG);
}

CameraPosition* PositionFactory::addBoth(CameraPosition* c, CameraPosition* d,  int direction, bool bothways=true){
    CameraPosition* a=c;
    CameraPosition* b=d;

    if (direction==direction::LEFT){
	if (a->getLeftNeighbour()!=NULL && a->getLeftNeighbour()!=b){
	    a=new CameraPosition(*a);
	    cameraPositions.push_back(a);
	}
	a->setLeftNeighbour(b);
	if (bothways){
	    if (b->getRightNeighbour()!=NULL && b->getRightNeighbour()!=a){
		b=new CameraPosition(*b);
		cameraPositions.push_back(b);
	    }
	    b->setRightNeighbour(a);
	}
    }

    if (direction==direction::RIGHT){
	    if (a->getRightNeighbour()!=NULL && a->getRightNeighbour()!=b){
		a=new CameraPosition(*a);
		cameraPositions.push_back(a);
	    }
	a->setRightNeighbour(b);
	if (bothways){
	    if (b->getLeftNeighbour()!=NULL && b->getLeftNeighbour()!=a){
		b=new CameraPosition(*b);
		cameraPositions.push_back(b);
	    }
	    b->setLeftNeighbour(a);
	}
    }

    if (direction==direction::UP){
	    if (a->getUpNeighbour()!=NULL && a->getUpNeighbour()!=b){
		a=new CameraPosition(*a);
		cameraPositions.push_back(a);
	    }
	a->setUpNeighbour(b);
	if (bothways){
	    if (b->getDownNeighbour()!=NULL && b->getDownNeighbour()!=a){
		b=new CameraPosition(*b);
		cameraPositions.push_back(b);
	    }
	    b->setDownNeighbour(a);
	}
    }


    if (direction==direction::DOWN){
	    if (a->getDownNeighbour()!=NULL && a->getDownNeighbour()!=b){
		a=new CameraPosition(*a);
		cameraPositions.push_back(a);
	    }
	a->setDownNeighbour(b);
	if (bothways){
	    if (b->getUpNeighbour()!=NULL && b->getUpNeighbour()!=a){
		b=new CameraPosition(*b);
		cameraPositions.push_back(b);
	    }
	    b->setUpNeighbour(a);
	}
    }

    return a;
}

CameraPosition* getOrCreateCM(std::vector<CameraPosition*>& vec, ofVec3f p, ofVec3f u){
    for (unsigned int i=0;i<vec.size();++i){
	if (vec[i]->getPosition()==p && vec[i]->getUpVector()==u){
	    return vec[i];
	}
    }
    CameraPosition* cp = new CameraPosition(p,u);
    vec.push_back(cp);
    return cp;
}


CameraPosition* getOrCreateCM(std::vector<CameraPosition*>& vec, CameraPosition* cp){
    return getOrCreateCM(vec,cp->getPosition(),cp->getUpVector());
}

CameraPosition* addFriend(CameraPosition* position, CameraPosition* fPos){
    if ( (*position) != (*fPos)){
        position->friendPosition = fPos;
        fPos->friendPosition = position;
    }
    return position;
}


bool PositionFactory::createPositions(){
    if (this->cameraPositions.size()==0){ //TODO make a script (for example python) to generate a config file with the position infos and read them from the file

	std::vector<ofVec3f> v = this->getPositionVectors();

	/*
	 *  FRONT
	 */
	CameraPosition* cp010_fmm = getOrCreateCM(cameraPositions, v[0], ofVec3f(0,1,0));
	CameraPosition* cp010_flm = getOrCreateCM(cameraPositions, v[7], ofVec3f(0,1,0));
	CameraPosition* cp010_frm = getOrCreateCM(cameraPositions, v[6], ofVec3f(0,1,0));
	CameraPosition* cp010_fmu = getOrCreateCM(cameraPositions, v[15], ofVec3f(0,1,0));
	CameraPosition* cp010_fmd = getOrCreateCM(cameraPositions, v[16], ofVec3f(0,1,0));
	CameraPosition* cp010_flu = getOrCreateCM(cameraPositions, v[20], ofVec3f(0,1,0));
	CameraPosition* cp010_fld = getOrCreateCM(cameraPositions, v[21], ofVec3f(0,1,0));
	CameraPosition* cp010_fru = getOrCreateCM(cameraPositions, v[22], ofVec3f(0,1,0));
	CameraPosition* cp010_frd = getOrCreateCM(cameraPositions, v[23], ofVec3f(0,1,0));
	cp010_fmm = addBoth(cp010_fmm,cp010_flm,direction::LEFT);
	cp010_fmm = addBoth(cp010_fmm,cp010_frm,direction::RIGHT);
	cp010_fmm = addBoth(cp010_fmm,cp010_fmu,direction::UP);
	cp010_fmm = addBoth(cp010_fmm,cp010_fmd,direction::DOWN);
	cp010_flm = addBoth(cp010_flm,cp010_flu,direction::UP);
	cp010_flm = addBoth(cp010_flm,cp010_fld,direction::DOWN);
	cp010_fmu = addBoth(cp010_fmu,cp010_flu,direction::LEFT);
	cp010_fmd = addBoth(cp010_fmd,cp010_fld,direction::LEFT);
	cp010_frm = addBoth(cp010_frm,cp010_fru,direction::UP);
	cp010_frm = addBoth(cp010_frm,cp010_frd,direction::DOWN);
	cp010_fmu = addBoth(cp010_fmu,cp010_fru,direction::RIGHT);
	cp010_fmd = addBoth(cp010_fmd,cp010_frd,direction::RIGHT);



	/*
	 *  LEFT
	 */
	CameraPosition* cp010_lmm = getOrCreateCM(cameraPositions, v[4], ofVec3f(0,1,0));
	CameraPosition* cp010_llm = getOrCreateCM(cameraPositions, v[8], ofVec3f(0,1,0));
	CameraPosition* cp010_lrm = getOrCreateCM(cameraPositions, cp010_flm->getPosition(), ofVec3f(0,1,0));
	CameraPosition* cp010_lmu = getOrCreateCM(cameraPositions, v[10], ofVec3f(0,1,0));
	CameraPosition* cp010_lmd = getOrCreateCM(cameraPositions, v[13], ofVec3f(0,1,0));
	CameraPosition* cp010_llu = getOrCreateCM(cameraPositions, v[19], ofVec3f(0,1,0));
	CameraPosition* cp010_lld = getOrCreateCM(cameraPositions, v[18], ofVec3f(0,1,0));
	CameraPosition* cp010_lru = getOrCreateCM(cameraPositions, cp010_flu->getPosition(), ofVec3f(0,1,0));
	CameraPosition* cp010_lrd = getOrCreateCM(cameraPositions, cp010_fld->getPosition(), ofVec3f(0,1,0));
	cp010_lmm = addBoth(cp010_lmm,cp010_llm,direction::LEFT);
	cp010_lmm = addBoth(cp010_lmm,cp010_lrm,direction::RIGHT);
	cp010_lmm = addBoth(cp010_lmm,cp010_lmu,direction::UP);
	cp010_lmm = addBoth(cp010_lmm,cp010_lmd,direction::DOWN);
	cp010_llm = addBoth(cp010_llm,cp010_llu,direction::UP);
	cp010_llm = addBoth(cp010_llm,cp010_lld,direction::DOWN);
	cp010_lmu = addBoth(cp010_lmu,cp010_llu,direction::LEFT);
	cp010_lmd = addBoth(cp010_lmd,cp010_lld,direction::LEFT);
	cp010_lrm = addBoth(cp010_lrm,cp010_lru,direction::UP);
	cp010_lrm = addBoth(cp010_lrm,cp010_lrd,direction::DOWN);
	cp010_lmu = addBoth(cp010_lmu,cp010_lru,direction::RIGHT);
	cp010_lmd = addBoth(cp010_lmd,cp010_lrd,direction::RIGHT);


	/*
	 *  RIGHT
	 */
	CameraPosition* cp010_rmm = getOrCreateCM(cameraPositions, v[5], ofVec3f(0,1,0));
	CameraPosition* cp010_rlm = getOrCreateCM(cameraPositions, cp010_frm);
	CameraPosition* cp010_rrm = getOrCreateCM(cameraPositions, v[9], ofVec3f(0,1,0));
	CameraPosition* cp010_rmu = getOrCreateCM(cameraPositions, v[11], ofVec3f(0,1,0));
	CameraPosition* cp010_rmd = getOrCreateCM(cameraPositions, v[12], ofVec3f(0,1,0));
	CameraPosition* cp010_rlu = getOrCreateCM(cameraPositions, cp010_fru);
	CameraPosition* cp010_rld = getOrCreateCM(cameraPositions, cp010_frd);
	CameraPosition* cp010_rru = getOrCreateCM(cameraPositions, v[25], ofVec3f(0,1,0));
	CameraPosition* cp010_rrd = getOrCreateCM(cameraPositions, v[24], ofVec3f(0,1,0));
	cp010_rmm = addBoth(cp010_rmm,cp010_rlm,direction::LEFT);
	cp010_rmm = addBoth(cp010_rmm,cp010_rrm,direction::RIGHT);
	cp010_rmm = addBoth(cp010_rmm,cp010_rmu,direction::UP);
	cp010_rmm = addBoth(cp010_rmm,cp010_rmd,direction::DOWN);
	cp010_rlm = addBoth(cp010_rlm,cp010_rlu,direction::UP);
	cp010_rlm = addBoth(cp010_rlm,cp010_rld,direction::DOWN);
	cp010_rmu = addBoth(cp010_rmu,cp010_rlu,direction::LEFT);
	cp010_rmd = addBoth(cp010_rmd,cp010_rld,direction::LEFT);
	cp010_rrm = addBoth(cp010_rrm,cp010_rru,direction::UP);
	cp010_rrm = addBoth(cp010_rrm,cp010_rrd,direction::DOWN);
	cp010_rmu = addBoth(cp010_rmu,cp010_rru,direction::RIGHT);
	cp010_rmd = addBoth(cp010_rmd,cp010_rrd,direction::RIGHT);


	/*
	 *  BACK
	 */
	CameraPosition* cp010_bmm = getOrCreateCM(cameraPositions, v[1], ofVec3f(0,1,0));
	CameraPosition* cp010_blm = getOrCreateCM(cameraPositions, cp010_rrm);
	CameraPosition* cp010_brm = getOrCreateCM(cameraPositions, cp010_llm);
	CameraPosition* cp010_bmu = getOrCreateCM(cameraPositions, v[14], ofVec3f(0,1,0));
	CameraPosition* cp010_bmd = getOrCreateCM(cameraPositions, v[17], ofVec3f(0,1,0));
	CameraPosition* cp010_blu = getOrCreateCM(cameraPositions, cp010_rru);
	CameraPosition* cp010_bld = getOrCreateCM(cameraPositions, cp010_rrd);
	CameraPosition* cp010_bru = getOrCreateCM(cameraPositions, cp010_llu);
	CameraPosition* cp010_brd = getOrCreateCM(cameraPositions, cp010_lld);
	cp010_bmm = addBoth(cp010_bmm,cp010_blm,direction::LEFT);
	cp010_bmm = addBoth(cp010_bmm,cp010_brm,direction::RIGHT);
	cp010_bmm = addBoth(cp010_bmm,cp010_bmu,direction::UP);
	cp010_bmm = addBoth(cp010_bmm,cp010_bmd,direction::DOWN);
	cp010_blm = addBoth(cp010_blm,cp010_blu,direction::UP);
	cp010_blm = addBoth(cp010_blm,cp010_bld,direction::DOWN);
	cp010_bmu = addBoth(cp010_bmu,cp010_blu,direction::LEFT);
	cp010_bmd = addBoth(cp010_bmd,cp010_bld,direction::LEFT);
	cp010_brm = addBoth(cp010_brm,cp010_bru,direction::UP);
	cp010_brm = addBoth(cp010_brm,cp010_brd,direction::DOWN);
	cp010_bmu = addBoth(cp010_bmu,cp010_bru,direction::RIGHT);
	cp010_bmd = addBoth(cp010_bmd,cp010_brd,direction::RIGHT);


	// /*
	//  *  UP  - with up facing to front side (pink)
	//  */
	ofVec3f upVec(1,0,0);
	CameraPosition* cp100_umm = getOrCreateCM(cameraPositions, v[2], upVec);
	CameraPosition* cp100_ulm = getOrCreateCM(cameraPositions, cp010_rmu->getPosition(),upVec);
	CameraPosition* cp100_urm = getOrCreateCM(cameraPositions, cp010_lmu->getPosition(),upVec);
	CameraPosition* cp100_umu = getOrCreateCM(cameraPositions, cp010_fmu->getPosition(),upVec);
	CameraPosition* cp100_umd = addFriend(getOrCreateCM(cameraPositions, cp010_bmu->getPosition(), upVec),cp010_bmu); //TODO
	CameraPosition* cp100_ulu = getOrCreateCM(cameraPositions, cp010_fru->getPosition(),upVec); //left up
	CameraPosition* cp100_uld = getOrCreateCM(cameraPositions, cp010_blu->getPosition(), upVec);
	CameraPosition* cp100_uru = getOrCreateCM(cameraPositions, cp010_flu->getPosition(),upVec); // right up
	CameraPosition* cp100_urd = getOrCreateCM(cameraPositions, cp010_bru->getPosition(), upVec);
	cp100_umm = addBoth(cp100_umm,cp100_ulm,direction::LEFT);
	cp100_umm = addBoth(cp100_umm,cp100_urm,direction::RIGHT);
	cp100_umm = addBoth(cp100_umm,cp100_umu,direction::UP);
	cp100_ulm = addBoth(cp100_ulm,cp100_ulu,direction::UP);
	cp100_urm = addBoth(cp100_urm,cp100_uru,direction::UP);
	cp100_umu = addBoth(cp100_umu,cp100_ulu,direction::LEFT);
	cp100_umd = addBoth(cp100_umd,cp100_uld,direction::LEFT);
	cp100_umu = addBoth(cp100_umu,cp100_uru,direction::RIGHT);
	cp100_umd = addBoth(cp100_umd,cp100_urd,direction::RIGHT);
	//below the order is important
	cp100_urm = addBoth(cp100_urm,cp100_urd,direction::DOWN);
	cp100_ulm = addBoth(cp100_ulm,cp100_uld,direction::DOWN);
	cp100_umd = addBoth(cp100_umd,cp100_urd,direction::RIGHT);
	cp100_umd = addBoth(cp100_umd,cp100_uld,direction::LEFT);
	cp100_umm = addBoth(cp100_umm,cp100_umd,direction::DOWN); //vasta cornerista

      	// /*
	//  *  UP  - with up facing to back location (lila)
	//  */
        upVec = ofVec3f(-1,0,0);
	CameraPosition* cp200_umm = getOrCreateCM(cameraPositions, v[2], upVec);
	CameraPosition* cp200_ulm = getOrCreateCM(cameraPositions, cp010_lmu->getPosition(),upVec);
	CameraPosition* cp200_urm = getOrCreateCM(cameraPositions, cp010_rmu->getPosition(),upVec);
	CameraPosition* cp200_umu = getOrCreateCM(cameraPositions, cp010_bmu->getPosition(),upVec);
	CameraPosition* cp200_umd = addFriend(getOrCreateCM(cameraPositions, cp010_fmu->getPosition(), upVec), cp010_fmu); //TODO
	CameraPosition* cp200_ulu = getOrCreateCM(cameraPositions, cp010_bru->getPosition(),upVec); //left up
	CameraPosition* cp200_uld = getOrCreateCM(cameraPositions, cp010_flu->getPosition(), upVec);
	CameraPosition* cp200_uru = getOrCreateCM(cameraPositions, cp010_blu->getPosition(),upVec); // right up
	CameraPosition* cp200_urd = getOrCreateCM(cameraPositions, cp010_fru->getPosition(), upVec);
	cp200_umm = addBoth(cp200_umm,cp200_ulm,direction::LEFT);
	cp200_umm = addBoth(cp200_umm,cp200_urm,direction::RIGHT);
	cp200_umm = addBoth(cp200_umm,cp200_umu,direction::UP);
	cp200_ulm = addBoth(cp200_ulm,cp200_ulu,direction::UP);
	cp200_urm = addBoth(cp200_urm,cp200_uru,direction::UP);
	cp200_umu = addBoth(cp200_umu,cp200_ulu,direction::LEFT);
	cp200_umd = addBoth(cp200_umd,cp200_uld,direction::LEFT);
	cp200_umu = addBoth(cp200_umu,cp200_uru,direction::RIGHT);
	cp200_umd = addBoth(cp200_umd,cp200_urd,direction::RIGHT);
	//below the order is important
	cp200_urm = addBoth(cp200_urm,cp200_urd,direction::DOWN);
	cp200_ulm = addBoth(cp200_ulm,cp200_uld,direction::DOWN);
	cp200_umd = addBoth(cp200_umd,cp200_urd,direction::RIGHT);
	cp200_umd = addBoth(cp200_umd,cp200_uld,direction::LEFT);
	cp200_umm = addBoth(cp200_umm,cp200_umd,direction::DOWN); //vasta cornerista



      	// /*
	//  *  UP  - with up facing to left side (grey)
	//  */
        upVec = ofVec3f(0,0,1);
	CameraPosition* cp001_umm = getOrCreateCM(cameraPositions, v[2], upVec);
	CameraPosition* cp001_ulm = getOrCreateCM(cameraPositions, cp010_fmu->getPosition(),upVec);
	CameraPosition* cp001_urm = getOrCreateCM(cameraPositions, cp010_bmu->getPosition(),upVec);
	CameraPosition* cp001_umu = getOrCreateCM(cameraPositions, cp010_lmu->getPosition(),upVec);
	CameraPosition* cp001_umd = addFriend(getOrCreateCM(cameraPositions, cp010_rmu->getPosition(), upVec), cp010_rmu); //TODO
	CameraPosition* cp001_ulu = getOrCreateCM(cameraPositions, cp010_lru->getPosition(),upVec); //left up
	CameraPosition* cp001_uld = getOrCreateCM(cameraPositions, cp010_rlu->getPosition(), upVec);
	CameraPosition* cp001_uru = getOrCreateCM(cameraPositions, cp010_llu->getPosition(),upVec); // right up
	CameraPosition* cp001_urd = getOrCreateCM(cameraPositions, cp010_rru->getPosition(), upVec);
	cp001_umm = addBoth(cp001_umm,cp001_ulm,direction::LEFT);
	cp001_umm = addBoth(cp001_umm,cp001_urm,direction::RIGHT);
	cp001_umm = addBoth(cp001_umm,cp001_umu,direction::UP);
	cp001_ulm = addBoth(cp001_ulm,cp001_ulu,direction::UP);
	cp001_urm = addBoth(cp001_urm,cp001_uru,direction::UP);
	cp001_umu = addBoth(cp001_umu,cp001_ulu,direction::LEFT);
	cp001_umd = addBoth(cp001_umd,cp001_uld,direction::LEFT);
	cp001_umu = addBoth(cp001_umu,cp001_uru,direction::RIGHT);
	cp001_umd = addBoth(cp001_umd,cp001_urd,direction::RIGHT);
	//below the order is important
	cp001_urm = addBoth(cp001_urm,cp001_urd,direction::DOWN);
	cp001_ulm = addBoth(cp001_ulm,cp001_uld,direction::DOWN);
	cp001_umd = addBoth(cp001_umd,cp001_urd,direction::RIGHT);
	cp001_umd = addBoth(cp001_umd,cp001_uld,direction::LEFT);
	cp001_umm = addBoth(cp001_umm,cp001_umd,direction::DOWN); //vasta cornerista

      	// /*
	//  *  UP  - with up facing to right side (blue)
	//  */
        upVec = ofVec3f(0,0,-1);
	CameraPosition* cp002_umm = getOrCreateCM(cameraPositions, v[2], upVec);
	CameraPosition* cp002_ulm = getOrCreateCM(cameraPositions, cp010_bmu->getPosition(),upVec);
	CameraPosition* cp002_urm = getOrCreateCM(cameraPositions, cp010_fmu->getPosition(),upVec);
	CameraPosition* cp002_umu = getOrCreateCM(cameraPositions, cp010_rmu->getPosition(),upVec);
	CameraPosition* cp002_umd = addFriend(getOrCreateCM(cameraPositions, cp010_lmu->getPosition(), upVec),cp010_lmu); //TODO
	CameraPosition* cp002_ulu = getOrCreateCM(cameraPositions, cp010_rru->getPosition(),upVec); //left up
	CameraPosition* cp002_uld = getOrCreateCM(cameraPositions, cp010_llu->getPosition(), upVec);
	CameraPosition* cp002_uru = getOrCreateCM(cameraPositions, cp010_rlu->getPosition(),upVec); // right up
	CameraPosition* cp002_urd = getOrCreateCM(cameraPositions, cp010_lru->getPosition(), upVec);
	cp002_umm = addBoth(cp002_umm,cp002_ulm,direction::LEFT);
	cp002_umm = addBoth(cp002_umm,cp002_urm,direction::RIGHT);
	cp002_umm = addBoth(cp002_umm,cp002_umu,direction::UP);
	cp002_ulm = addBoth(cp002_ulm,cp002_ulu,direction::UP);
	cp002_urm = addBoth(cp002_urm,cp002_uru,direction::UP);
	cp002_umu = addBoth(cp002_umu,cp002_ulu,direction::LEFT);
	cp002_umd = addBoth(cp002_umd,cp002_uld,direction::LEFT);
	cp002_umu = addBoth(cp002_umu,cp002_uru,direction::RIGHT);
	cp002_umd = addBoth(cp002_umd,cp002_urd,direction::RIGHT);
	//below the order is important
	cp002_urm = addBoth(cp002_urm,cp002_urd,direction::DOWN);
	cp002_ulm = addBoth(cp002_ulm,cp002_uld,direction::DOWN);
	cp002_umd = addBoth(cp002_umd,cp002_urd,direction::RIGHT);
	cp002_umd = addBoth(cp002_umd,cp002_uld,direction::LEFT);
	cp002_umm = addBoth(cp002_umm,cp002_umd,direction::DOWN); //vasta cornerista


	/*
	 *  DOWN  - with up facing to front side (pink)
	 */
	upVec = ofVec3f(1,0,0);
	CameraPosition* cp100_dmm = getOrCreateCM(cameraPositions, v[3], upVec);
	CameraPosition* cp100_dlm = getOrCreateCM(cameraPositions, cp010_lmd->getPosition(),upVec);
	CameraPosition* cp100_drm = getOrCreateCM(cameraPositions, cp010_rmd->getPosition(),upVec);
	CameraPosition* cp100_dmu = addFriend(getOrCreateCM(cameraPositions, cp010_fmd->getPosition(), upVec), cp010_fmd); //TODO
	CameraPosition* cp100_dmd = getOrCreateCM(cameraPositions, cp010_bmd->getPosition(),upVec);
	CameraPosition* cp100_dlu = getOrCreateCM(cameraPositions, cp010_fld->getPosition(),upVec);
	CameraPosition* cp100_dld = getOrCreateCM(cameraPositions, cp010_brd->getPosition(), upVec);
	CameraPosition* cp100_dru = getOrCreateCM(cameraPositions, cp010_frd->getPosition(), upVec);
 	CameraPosition* cp100_drd = getOrCreateCM(cameraPositions, cp010_bld->getPosition(), upVec);
	cp100_dmm = addBoth(cp100_dmm,cp100_dlm,direction::LEFT);
	cp100_dmm = addBoth(cp100_dmm,cp100_drm,direction::RIGHT);
	//below the order is important - up
	cp100_drm = addBoth(cp100_drm,cp100_dru,direction::UP);
	cp100_dlm = addBoth(cp100_dlm,cp100_dlu,direction::UP);
	cp100_dmu = addBoth(cp100_dmu,cp100_dru,direction::RIGHT);
	cp100_dmu = addBoth(cp100_dmu,cp100_dlu,direction::LEFT);
	cp100_dmm = addBoth(cp100_dmm,cp100_dmu,direction::UP); //vasta cornerista
	//below the order is important - down
	cp100_drm = addBoth(cp100_drm,cp100_drd,direction::DOWN);
	cp100_dlm = addBoth(cp100_dlm,cp100_dld,direction::DOWN);
	cp100_dmd = addBoth(cp100_dmd,cp100_drd,direction::RIGHT);
	cp100_dmd = addBoth(cp100_dmd,cp100_dld,direction::LEFT);
	cp100_dmm = addBoth(cp100_dmm,cp100_dmd,direction::DOWN); //vasta cornerista
	/*
	 *  DOWN  - with up facing to back side (lila
	 */
	upVec = ofVec3f(-1,0,0);
	CameraPosition* cp200_dmm = getOrCreateCM(cameraPositions, v[3], upVec);
	CameraPosition* cp200_dlm = getOrCreateCM(cameraPositions, cp010_rmd->getPosition(),upVec);
	CameraPosition* cp200_drm = getOrCreateCM(cameraPositions, cp010_lmd->getPosition(),upVec);
	CameraPosition* cp200_dmu = addFriend(getOrCreateCM(cameraPositions, cp010_bmd->getPosition(), upVec), cp010_bmd); //TODO
	CameraPosition* cp200_dmd = getOrCreateCM(cameraPositions, cp010_fmd->getPosition(),upVec);
	CameraPosition* cp200_dlu = getOrCreateCM(cameraPositions, cp010_bld->getPosition(),upVec);
	CameraPosition* cp200_dld = getOrCreateCM(cameraPositions, cp010_frd->getPosition(), upVec);
	CameraPosition* cp200_dru = getOrCreateCM(cameraPositions, cp010_brd->getPosition(), upVec);
 	CameraPosition* cp200_drd = getOrCreateCM(cameraPositions, cp010_fld->getPosition(), upVec);
	cp200_dmm = addBoth(cp200_dmm,cp200_dlm,direction::LEFT);
	cp200_dmm = addBoth(cp200_dmm,cp200_drm,direction::RIGHT);
	//below the order is important - up
	cp200_drm = addBoth(cp200_drm,cp200_dru,direction::UP);
	cp200_dlm = addBoth(cp200_dlm,cp200_dlu,direction::UP);
	cp200_dmu = addBoth(cp200_dmu,cp200_dru,direction::RIGHT);
	cp200_dmu = addBoth(cp200_dmu,cp200_dlu,direction::LEFT);
	cp200_dmm = addBoth(cp200_dmm,cp200_dmu,direction::UP); //vasta cornerista
	//below the order is important - down
	cp200_drm = addBoth(cp200_drm,cp200_drd,direction::DOWN);
	cp200_dlm = addBoth(cp200_dlm,cp200_dld,direction::DOWN);
	cp200_dmd = addBoth(cp200_dmd,cp200_drd,direction::RIGHT);
	cp200_dmd = addBoth(cp200_dmd,cp200_dld,direction::LEFT);
	cp200_dmm = addBoth(cp200_dmm,cp200_dmd,direction::DOWN); //vasta cornerista
	/*
	 *  DOWN  - with up facing grey - left side
	 */
	upVec = ofVec3f(0,0,1);
	CameraPosition* cp001_dmm = getOrCreateCM(cameraPositions, v[3], upVec);
	CameraPosition* cp001_dlm = getOrCreateCM(cameraPositions, cp010_bmd->getPosition(),upVec);
	CameraPosition* cp001_drm = getOrCreateCM(cameraPositions, cp010_fmd->getPosition(),upVec);
	CameraPosition* cp001_dmu = addFriend(getOrCreateCM(cameraPositions, cp010_lmd->getPosition(), upVec), cp010_lmd); //TODO
	CameraPosition* cp001_dmd = getOrCreateCM(cameraPositions, cp010_rmd->getPosition(),upVec);
	CameraPosition* cp001_dlu = getOrCreateCM(cameraPositions, cp010_lld->getPosition(),upVec);
	CameraPosition* cp001_dld = getOrCreateCM(cameraPositions, cp010_rrd->getPosition(), upVec);
	CameraPosition* cp001_dru = getOrCreateCM(cameraPositions, cp010_lrd->getPosition(), upVec);
 	CameraPosition* cp001_drd = getOrCreateCM(cameraPositions, cp010_rld->getPosition(), upVec);
	cp001_dmm = addBoth(cp001_dmm,cp001_dlm,direction::LEFT);
	cp001_dmm = addBoth(cp001_dmm,cp001_drm,direction::RIGHT);
	//below the order is important - up
	cp001_drm = addBoth(cp001_drm,cp001_dru,direction::UP);
	cp001_dlm = addBoth(cp001_dlm,cp001_dlu,direction::UP);
	cp001_dmu = addBoth(cp001_dmu,cp001_dru,direction::RIGHT);
	cp001_dmu = addBoth(cp001_dmu,cp001_dlu,direction::LEFT);
	cp001_dmm = addBoth(cp001_dmm,cp001_dmu,direction::UP); //vasta cornerista
	//below the order is important - down
	cp001_drm = addBoth(cp001_drm,cp001_drd,direction::DOWN);
	cp001_dlm = addBoth(cp001_dlm,cp001_dld,direction::DOWN);
	cp001_dmd = addBoth(cp001_dmd,cp001_drd,direction::RIGHT);
	cp001_dmd = addBoth(cp001_dmd,cp001_dld,direction::LEFT);
	cp001_dmm = addBoth(cp001_dmm,cp001_dmd,direction::DOWN); //vasta cornerista
	/*
	 *  DOWN  - with up facing blue - right side
	 */
	upVec = ofVec3f(0,0,-1);
	CameraPosition* cp002_dmm = getOrCreateCM(cameraPositions, v[3], upVec);
	CameraPosition* cp002_dlm = getOrCreateCM(cameraPositions, cp010_fmd->getPosition(),upVec);
	CameraPosition* cp002_drm = getOrCreateCM(cameraPositions, cp010_bmd->getPosition(),upVec);
	CameraPosition* cp002_dmu = addFriend(getOrCreateCM(cameraPositions, cp010_rmd->getPosition(), upVec), cp010_rmd); //TODO
	CameraPosition* cp002_dmd = getOrCreateCM(cameraPositions, cp010_lmd->getPosition(),upVec);
	CameraPosition* cp002_dlu = getOrCreateCM(cameraPositions, cp010_rld->getPosition(),upVec);
	CameraPosition* cp002_dld = getOrCreateCM(cameraPositions, cp010_lrd->getPosition(), upVec);
	CameraPosition* cp002_dru = getOrCreateCM(cameraPositions, cp010_rrd->getPosition(), upVec);
 	CameraPosition* cp002_drd = getOrCreateCM(cameraPositions, cp010_lld->getPosition(), upVec);
	cp002_dmm = addBoth(cp002_dmm,cp002_dlm,direction::LEFT);
	cp002_dmm = addBoth(cp002_dmm,cp002_drm,direction::RIGHT);
	//below the order is important - up
	cp002_drm = addBoth(cp002_drm,cp002_dru,direction::UP);
	cp002_dlm = addBoth(cp002_dlm,cp002_dlu,direction::UP);
	cp002_dmu = addBoth(cp002_dmu,cp002_dru,direction::RIGHT);
	cp002_dmu = addBoth(cp002_dmu,cp002_dlu,direction::LEFT);
	cp002_dmm = addBoth(cp002_dmm,cp002_dmu,direction::UP); //vasta cornerista
	//below the order is important - down
	cp002_drm = addBoth(cp002_drm,cp002_drd,direction::DOWN);
	cp002_dlm = addBoth(cp002_dlm,cp002_dld,direction::DOWN);
	cp002_dmd = addBoth(cp002_dmd,cp002_drd,direction::RIGHT);
	cp002_dmd = addBoth(cp002_dmd,cp002_dld,direction::LEFT);
	cp002_dmm = addBoth(cp002_dmm,cp002_dmd,direction::DOWN); //vasta cornerista

	///////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////

	/*
	 *  FRONT  - with up facing left grey side
	 */
	upVec = ofVec3f(0,0,1);
	CameraPosition* cp001_fmm = getOrCreateCM(cameraPositions, v[0], upVec);
	CameraPosition* cp001_flm = getOrCreateCM(cameraPositions, cp010_fmd->getPosition(),upVec);
	CameraPosition* cp001_frm = getOrCreateCM(cameraPositions, cp010_fmu->getPosition(),upVec);
	CameraPosition* cp001_fmu = getOrCreateCM(cameraPositions, cp010_flm->getPosition(),upVec);
	CameraPosition* cp001_fmd = getOrCreateCM(cameraPositions, cp010_frm->getPosition(),upVec);
	CameraPosition* cp001_flu = getOrCreateCM(cameraPositions, cp010_fld->getPosition(),upVec);
	CameraPosition* cp001_fld = getOrCreateCM(cameraPositions, cp010_frd->getPosition(), upVec);
	CameraPosition* cp001_fru = getOrCreateCM(cameraPositions, cp010_flu->getPosition(), upVec);
 	CameraPosition* cp001_frd = getOrCreateCM(cameraPositions, cp010_fru->getPosition(), upVec);
	cp001_fmm = addBoth(cp001_fmm,cp001_flm,direction::LEFT);
	cp001_fmm = addBoth(cp001_fmm,cp001_frm,direction::RIGHT);
	//below the order is important - up
	cp001_frm = addBoth(cp001_frm,cp001_fru,direction::UP);
	cp001_flm = addBoth(cp001_flm,cp001_flu,direction::UP);
	cp001_fmu = addBoth(cp001_fmu,cp001_fru,direction::RIGHT);
	cp001_fmu = addBoth(cp001_fmu,cp001_flu,direction::LEFT);
	cp001_fmm = addBoth(cp001_fmm,cp001_fmu,direction::UP); //vasta cornerista
	//below the order is important - down
	cp001_frm = addBoth(cp001_frm,cp001_frd,direction::DOWN);
	cp001_flm = addBoth(cp001_flm,cp001_fld,direction::DOWN);
	cp001_fmd = addBoth(cp001_fmd,cp001_frd,direction::RIGHT);
	cp001_fmd = addBoth(cp001_fmd,cp001_fld,direction::LEFT);
	cp001_fmm = addBoth(cp001_fmm,cp001_fmd,direction::DOWN); //vasta cornerista
	/*
	 *  FRONT  - with up facing right blue side
	 */
	upVec = ofVec3f(0,0,-1);
	CameraPosition* cp002_fmm = getOrCreateCM(cameraPositions, v[0], upVec);
	CameraPosition* cp002_flm = getOrCreateCM(cameraPositions, cp010_fmu->getPosition(),upVec);
	CameraPosition* cp002_frm = getOrCreateCM(cameraPositions, cp010_fmd->getPosition(),upVec);
	CameraPosition* cp002_fmu = getOrCreateCM(cameraPositions, cp010_frm->getPosition(),upVec);
	CameraPosition* cp002_fmd = getOrCreateCM(cameraPositions, cp010_flm->getPosition(),upVec);
	CameraPosition* cp002_flu = getOrCreateCM(cameraPositions, cp010_fru->getPosition(),upVec);
	CameraPosition* cp002_fld = getOrCreateCM(cameraPositions, cp010_flu->getPosition(), upVec);
	CameraPosition* cp002_fru = getOrCreateCM(cameraPositions, cp010_frd->getPosition(), upVec);
 	CameraPosition* cp002_frd = getOrCreateCM(cameraPositions, cp010_fld->getPosition(), upVec);
	cp002_fmm = addBoth(cp002_fmm,cp002_flm,direction::LEFT);
	cp002_fmm = addBoth(cp002_fmm,cp002_frm,direction::RIGHT);
	//below the order is important - up
	cp002_frm = addBoth(cp002_frm,cp002_fru,direction::UP);
	cp002_flm = addBoth(cp002_flm,cp002_flu,direction::UP);
	cp002_fmu = addBoth(cp002_fmu,cp002_fru,direction::RIGHT);
	cp002_fmu = addBoth(cp002_fmu,cp002_flu,direction::LEFT);
	cp002_fmm = addBoth(cp002_fmm,cp002_fmu,direction::UP); //vasta cornerista
	//below the order is important - down
	cp002_frm = addBoth(cp002_frm,cp002_frd,direction::DOWN);
	cp002_flm = addBoth(cp002_flm,cp002_fld,direction::DOWN);
	cp002_fmd = addBoth(cp002_fmd,cp002_frd,direction::RIGHT);
	cp002_fmd = addBoth(cp002_fmd,cp002_fld,direction::LEFT);
	cp002_fmm = addBoth(cp002_fmm,cp002_fmd,direction::DOWN); //vasta cornerista
	/*
	 *  FRONT  - with up facing down brown  side
	 */
	upVec = ofVec3f(0,-1,0);
	CameraPosition* cp020_fmm = getOrCreateCM(cameraPositions, v[0], upVec);
	CameraPosition* cp020_flm = getOrCreateCM(cameraPositions, cp010_frm->getPosition(),ofVec3f(0.001,-1,0));//if 0,-1,0 is used - cube disappears..
	CameraPosition* cp020_frm = getOrCreateCM(cameraPositions, cp010_flm->getPosition(),upVec);
	CameraPosition* cp020_fmu = addFriend(getOrCreateCM(cameraPositions, cp200_dmd->getPosition(), upVec),cp200_dmd); //TODO
	CameraPosition* cp020_fmd = addFriend(getOrCreateCM(cameraPositions, cp100_umu->getPosition(), upVec),cp100_umu); //TODO
	CameraPosition* cp020_flu = getOrCreateCM(cameraPositions, cp010_frd->getPosition(),upVec);
	CameraPosition* cp020_fld = getOrCreateCM(cameraPositions, cp010_fru->getPosition(), upVec);
	CameraPosition* cp020_fru = getOrCreateCM(cameraPositions, cp010_fld->getPosition(), upVec);
 	CameraPosition* cp020_frd = getOrCreateCM(cameraPositions, cp010_flu->getPosition(), upVec);
	cp020_fmm = addBoth(cp020_fmm,cp020_flm,direction::LEFT);
	cp020_fmm = addBoth(cp020_fmm,cp020_frm,direction::RIGHT);
	//below the order is important - up
	cp020_frm = addBoth(cp020_frm,cp020_fru,direction::UP);
	cp020_flm = addBoth(cp020_flm,cp020_flu,direction::UP);
	cp020_fmu = addBoth(cp020_fmu,cp020_fru,direction::RIGHT);
	cp020_fmu = addBoth(cp020_fmu,cp020_flu,direction::LEFT);
	cp020_fmm = addBoth(cp020_fmm,cp020_fmu,direction::UP); //vasta cornerista
	//below the order is important - down
	cp020_frm = addBoth(cp020_frm,cp020_frd,direction::DOWN);
	cp020_flm = addBoth(cp020_flm,cp020_fld,direction::DOWN);
	cp020_fmd = addBoth(cp020_fmd,cp020_frd,direction::RIGHT);
	cp020_fmd = addBoth(cp020_fmd,cp020_fld,direction::LEFT);
	cp020_fmm = addBoth(cp020_fmm,cp020_fmd,direction::DOWN); //vasta cornerista

	/////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////

	/*
	 *  BACK  - with up facing left grey side
	 */
	upVec = ofVec3f(0,0,1);
	CameraPosition* cp001_bmm = getOrCreateCM(cameraPositions, v[1], upVec);
	CameraPosition* cp001_blm = getOrCreateCM(cameraPositions, cp010_bmu->getPosition(),upVec);
	CameraPosition* cp001_brm = getOrCreateCM(cameraPositions, cp010_bmd->getPosition(),upVec);
	CameraPosition* cp001_bmu = getOrCreateCM(cameraPositions, cp010_brm->getPosition(),upVec);
	CameraPosition* cp001_bmd = getOrCreateCM(cameraPositions, cp010_blm->getPosition(),upVec);
	CameraPosition* cp001_blu = getOrCreateCM(cameraPositions, cp010_bru->getPosition(),upVec);
	CameraPosition* cp001_bld = getOrCreateCM(cameraPositions, cp010_blu->getPosition(), upVec);
	CameraPosition* cp001_bru = getOrCreateCM(cameraPositions, cp010_brd->getPosition(), upVec);
 	CameraPosition* cp001_brd = getOrCreateCM(cameraPositions, cp010_bld->getPosition(), upVec);
	cp001_bmm = addBoth(cp001_bmm,cp001_blm,direction::LEFT);
	cp001_bmm = addBoth(cp001_bmm,cp001_brm,direction::RIGHT);
	//below the order is important - up
	cp001_brm = addBoth(cp001_brm,cp001_bru,direction::UP);
	cp001_blm = addBoth(cp001_blm,cp001_blu,direction::UP);
	cp001_bmu = addBoth(cp001_bmu,cp001_bru,direction::RIGHT);
	cp001_bmu = addBoth(cp001_bmu,cp001_blu,direction::LEFT);
	cp001_bmm = addBoth(cp001_bmm,cp001_bmu,direction::UP); //vasta cornerista
	//below the order is important - down
	cp001_brm = addBoth(cp001_brm,cp001_brd,direction::DOWN);
	cp001_blm = addBoth(cp001_blm,cp001_bld,direction::DOWN);
	cp001_bmd = addBoth(cp001_bmd,cp001_brd,direction::RIGHT);
	cp001_bmd = addBoth(cp001_bmd,cp001_bld,direction::LEFT);
	cp001_bmm = addBoth(cp001_bmm,cp001_bmd,direction::DOWN); //vasta cornerista
	/*
	 *  BACK  - with up facing right blue side
	 */
	upVec = ofVec3f(0,0,-1);
	CameraPosition* cp002_bmm = getOrCreateCM(cameraPositions, v[1], upVec);
	CameraPosition* cp002_blm = getOrCreateCM(cameraPositions, cp010_bmd->getPosition(),upVec);
	CameraPosition* cp002_brm = getOrCreateCM(cameraPositions, cp010_bmu->getPosition(),upVec);
	CameraPosition* cp002_bmu = getOrCreateCM(cameraPositions, cp010_blm->getPosition(),upVec);
	CameraPosition* cp002_bmd = getOrCreateCM(cameraPositions, cp010_brm->getPosition(),upVec);
	CameraPosition* cp002_blu = getOrCreateCM(cameraPositions, cp010_bld->getPosition(),upVec);
	CameraPosition* cp002_bld = getOrCreateCM(cameraPositions, cp010_brd->getPosition(), upVec);
	CameraPosition* cp002_bru = getOrCreateCM(cameraPositions, cp010_blu->getPosition(), upVec);
 	CameraPosition* cp002_brd = getOrCreateCM(cameraPositions, cp010_bru->getPosition(), upVec);
	cp002_bmm = addBoth(cp002_bmm,cp002_blm,direction::LEFT);
	cp002_bmm = addBoth(cp002_bmm,cp002_brm,direction::RIGHT);
	//below the order is important - up
	cp002_brm = addBoth(cp002_brm,cp002_bru,direction::UP);
	cp002_blm = addBoth(cp002_blm,cp002_blu,direction::UP);
	cp002_bmu = addBoth(cp002_bmu,cp002_bru,direction::RIGHT);
	cp002_bmu = addBoth(cp002_bmu,cp002_blu,direction::LEFT);
	cp002_bmm = addBoth(cp002_bmm,cp002_bmu,direction::UP); //vasta cornerista
	//below the order is important - down
	cp002_brm = addBoth(cp002_brm,cp002_brd,direction::DOWN);
	cp002_blm = addBoth(cp002_blm,cp002_bld,direction::DOWN);
	cp002_bmd = addBoth(cp002_bmd,cp002_brd,direction::RIGHT);
	cp002_bmd = addBoth(cp002_bmd,cp002_bld,direction::LEFT);
	cp002_bmm = addBoth(cp002_bmm,cp002_bmd,direction::DOWN); //vasta cornerista
	/*
	 *  BACK  - with up facing down brown  side
	 */
	upVec = ofVec3f(0,-1,0);
	CameraPosition* cp020_bmm = getOrCreateCM(cameraPositions, v[1], upVec);
	CameraPosition* cp020_blm = getOrCreateCM(cameraPositions, cp010_brm->getPosition(),upVec);//,ofVec3f(0.001,-1,0));//if 0,-1,0 is used - cube disappears..
	CameraPosition* cp020_brm = getOrCreateCM(cameraPositions, cp010_blm->getPosition(),ofVec3f(0.001,-1,0));
	CameraPosition* cp020_bmu = addFriend(getOrCreateCM(cameraPositions, cp100_dmd->getPosition(), upVec),cp100_dmd); //TODO
	CameraPosition* cp020_bmd = addFriend(getOrCreateCM(cameraPositions, cp200_umu->getPosition(), upVec),cp200_umu); //TODO
	CameraPosition* cp020_blu = getOrCreateCM(cameraPositions, cp010_brd->getPosition(),upVec);
	CameraPosition* cp020_bld = getOrCreateCM(cameraPositions, cp010_bru->getPosition(), upVec);
	CameraPosition* cp020_bru = getOrCreateCM(cameraPositions, cp010_bld->getPosition(), upVec);
 	CameraPosition* cp020_brd = getOrCreateCM(cameraPositions, cp010_blu->getPosition(), upVec);
	cp020_bmm = addBoth(cp020_bmm,cp020_blm,direction::LEFT);
	cp020_bmm = addBoth(cp020_bmm,cp020_brm,direction::RIGHT);
	//below the order is important - up
	cp020_brm = addBoth(cp020_brm,cp020_bru,direction::UP);
	cp020_blm = addBoth(cp020_blm,cp020_blu,direction::UP);
	cp020_bmu = addBoth(cp020_bmu,cp020_bru,direction::RIGHT);
	cp020_bmu = addBoth(cp020_bmu,cp020_blu,direction::LEFT);
	cp020_bmm = addBoth(cp020_bmm,cp020_bmu,direction::UP); //vasta cornerista
	//below the order is important - down
	cp020_brm = addBoth(cp020_brm,cp020_brd,direction::DOWN);
	cp020_blm = addBoth(cp020_blm,cp020_bld,direction::DOWN);
	cp020_bmd = addBoth(cp020_bmd,cp020_brd,direction::RIGHT);
	cp020_bmd = addBoth(cp020_bmd,cp020_bld,direction::LEFT);
	cp020_bmm = addBoth(cp020_bmm,cp020_bmd,direction::DOWN); //vasta cornerista

	///////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////




	///////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////

	/*
	 *  LEFT  - with up facing front side
	 */
	upVec = ofVec3f(1,0,0);
	CameraPosition* cp100_lmm = getOrCreateCM(cameraPositions, v[4], upVec);
	CameraPosition* cp100_llm = getOrCreateCM(cameraPositions, cp010_lmu->getPosition(),upVec);
	CameraPosition* cp100_lrm = getOrCreateCM(cameraPositions, cp010_lmd->getPosition(),upVec);
	CameraPosition* cp100_lmu = addFriend(getOrCreateCM(cameraPositions, cp002_fmd->getPosition(), upVec), cp002_fmd); //TODO
	CameraPosition* cp100_lmd = addFriend(getOrCreateCM(cameraPositions, cp001_bmu->getPosition(), upVec), cp001_bmu); //TODO
	CameraPosition* cp100_llu = getOrCreateCM(cameraPositions, cp010_lru->getPosition(),upVec);
	CameraPosition* cp100_lld = getOrCreateCM(cameraPositions, cp010_llu->getPosition(), upVec);
	CameraPosition* cp100_lru = getOrCreateCM(cameraPositions, cp010_lrd->getPosition(), upVec);
 	CameraPosition* cp100_lrd = getOrCreateCM(cameraPositions, cp010_lld->getPosition(), upVec);
	cp100_lmm = addBoth(cp100_lmm,cp100_llm,direction::LEFT);
	cp100_lmm = addBoth(cp100_lmm,cp100_lrm,direction::RIGHT);
	//below the order is important - up
	cp100_lrm = addBoth(cp100_lrm,cp100_lru,direction::UP);
	cp100_llm = addBoth(cp100_llm,cp100_llu,direction::UP);
	cp100_lmu = addBoth(cp100_lmu,cp100_lru,direction::RIGHT);
	cp100_lmu = addBoth(cp100_lmu,cp100_llu,direction::LEFT);
	cp100_lmm = addBoth(cp100_lmm,cp100_lmu,direction::UP); //vasta cornerista
	//below the order is important - down
	cp100_lrm = addBoth(cp100_lrm,cp100_lrd,direction::DOWN);
	cp100_llm = addBoth(cp100_llm,cp100_lld,direction::DOWN);
	cp100_lmd = addBoth(cp100_lmd,cp100_lrd,direction::RIGHT);
	cp100_lmd = addBoth(cp100_lmd,cp100_lld,direction::LEFT);
	cp100_lmm = addBoth(cp100_lmm,cp100_lmd,direction::DOWN); //vasta cornerista

	/*
	 *  LEFT  - with up facing back side
	 */
	upVec = ofVec3f(-1,0,0);
	CameraPosition* cp200_lmm = getOrCreateCM(cameraPositions, v[4], upVec);
	CameraPosition* cp200_llm = getOrCreateCM(cameraPositions, cp010_lmd->getPosition(),upVec);
	CameraPosition* cp200_lrm = getOrCreateCM(cameraPositions, cp010_lmu->getPosition(),upVec);
	CameraPosition* cp200_lmu = addFriend(getOrCreateCM(cameraPositions, cp002_bmd->getPosition(), upVec), cp002_bmd); //TODO
	CameraPosition* cp200_lmd = addFriend(getOrCreateCM(cameraPositions, cp001_fmu->getPosition(), upVec), cp001_fmu); //TODO
	CameraPosition* cp200_llu = getOrCreateCM(cameraPositions, cp010_lld->getPosition(),upVec);
	CameraPosition* cp200_lld = getOrCreateCM(cameraPositions, cp010_lrd->getPosition(), upVec);
	CameraPosition* cp200_lru = getOrCreateCM(cameraPositions, cp010_llu->getPosition(), upVec);
 	CameraPosition* cp200_lrd = getOrCreateCM(cameraPositions, cp010_lru->getPosition(), upVec);
	cp200_lmm = addBoth(cp200_lmm,cp200_llm,direction::LEFT);
	cp200_lmm = addBoth(cp200_lmm,cp200_lrm,direction::RIGHT);
	//below the order is important - up
	cp200_lrm = addBoth(cp200_lrm,cp200_lru,direction::UP);
	cp200_llm = addBoth(cp200_llm,cp200_llu,direction::UP);
	cp200_lmu = addBoth(cp200_lmu,cp200_lru,direction::RIGHT);
	cp200_lmu = addBoth(cp200_lmu,cp200_llu,direction::LEFT);
	cp200_lmm = addBoth(cp200_lmm,cp200_lmu,direction::UP); //vasta cornerista
	//below the order is important - down
	cp200_lrm = addBoth(cp200_lrm,cp200_lrd,direction::DOWN);
	cp200_llm = addBoth(cp200_llm,cp200_lld,direction::DOWN);
	cp200_lmd = addBoth(cp200_lmd,cp200_lrd,direction::RIGHT);
	cp200_lmd = addBoth(cp200_lmd,cp200_lld,direction::LEFT);
	cp200_lmm = addBoth(cp200_lmm,cp200_lmd,direction::DOWN); //vasta cornerista

	/*
	 *  LEFT  - with up facing down side
	 */
	upVec = ofVec3f(0,-1,0);
	CameraPosition* cp020_lmm = getOrCreateCM(cameraPositions, v[4], ofVec3f(0.001,-1,0));
	CameraPosition* cp020_llm = getOrCreateCM(cameraPositions, cp010_lrm->getPosition(),upVec);
	CameraPosition* cp020_lrm = getOrCreateCM(cameraPositions, cp010_llm->getPosition(),upVec);
	CameraPosition* cp020_lmu = addFriend(getOrCreateCM(cameraPositions, cp002_dmd->getPosition(), upVec), cp002_dmd); //TODO
	CameraPosition* cp020_lmd = addFriend(getOrCreateCM(cameraPositions, cp001_umu->getPosition(), upVec), cp001_umu); //TODO
	CameraPosition* cp020_llu = getOrCreateCM(cameraPositions, cp010_lrd->getPosition(),upVec);
	CameraPosition* cp020_lld = getOrCreateCM(cameraPositions, cp010_lru->getPosition(), upVec);
	CameraPosition* cp020_lru = getOrCreateCM(cameraPositions, cp010_lld->getPosition(), upVec);
 	CameraPosition* cp020_lrd = getOrCreateCM(cameraPositions, cp010_llu->getPosition(), upVec);
	cp020_lmm = addBoth(cp020_lmm,cp020_llm,direction::LEFT);
	cp020_lmm = addBoth(cp020_lmm,cp020_lrm,direction::RIGHT);
	//below the order is important - up
	cp020_lrm = addBoth(cp020_lrm,cp020_lru,direction::UP);
	cp020_llm = addBoth(cp020_llm,cp020_llu,direction::UP);
	cp020_lmu = addBoth(cp020_lmu,cp020_lru,direction::RIGHT);
	cp020_lmu = addBoth(cp020_lmu,cp020_llu,direction::LEFT);
	cp020_lmm = addBoth(cp020_lmm,cp020_lmu,direction::UP); //vasta cornerista
	//below the order is important - down
	cp020_lrm = addBoth(cp020_lrm,cp020_lrd,direction::DOWN);
	cp020_llm = addBoth(cp020_llm,cp020_lld,direction::DOWN);
	cp020_lmd = addBoth(cp020_lmd,cp020_lrd,direction::RIGHT);
	cp020_lmd = addBoth(cp020_lmd,cp020_lld,direction::LEFT);
	cp020_lmm = addBoth(cp020_lmm,cp020_lmd,direction::DOWN); //vasta cornerista
	///////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////






	///////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////

	/*
	 *  RIGHT  - with up facing front side
	 */
	upVec = ofVec3f(1,0,0);
	CameraPosition* cp100_rmm = getOrCreateCM(cameraPositions, v[5], upVec);
	CameraPosition* cp100_rlm = getOrCreateCM(cameraPositions, cp010_rmd->getPosition(),upVec);
	CameraPosition* cp100_rrm = getOrCreateCM(cameraPositions, cp010_rmu->getPosition(),upVec);
	CameraPosition* cp100_rmu = addFriend(getOrCreateCM(cameraPositions, cp001_fmd->getPosition(), upVec), cp001_fmd); //TODO
	CameraPosition* cp100_rmd = addFriend(getOrCreateCM(cameraPositions, cp002_bmu->getPosition(), upVec), cp002_bmu); //TODO
	CameraPosition* cp100_rlu = getOrCreateCM(cameraPositions, cp100_dru->getPosition(), upVec);
	CameraPosition* cp100_rld = getOrCreateCM(cameraPositions, cp100_drd->getPosition(), upVec);
	CameraPosition* cp100_rru = getOrCreateCM(cameraPositions, cp100_ulu->getPosition(), upVec);
 	CameraPosition* cp100_rrd = getOrCreateCM(cameraPositions, cp100_uld->getPosition(), upVec);
	cp100_rmm = addBoth(cp100_rmm,cp100_rlm,direction::LEFT);
	cp100_rmm = addBoth(cp100_rmm,cp100_rrm,direction::RIGHT);
	//below the order is important - up
	cp100_rrm = addBoth(cp100_rrm,cp100_rru,direction::UP);
	cp100_rlm = addBoth(cp100_rlm,cp100_rlu,direction::UP);
	cp100_rmu = addBoth(cp100_rmu,cp100_rru,direction::RIGHT);
	cp100_rmu = addBoth(cp100_rmu,cp100_rlu,direction::LEFT);
	cp100_rmm = addBoth(cp100_rmm,cp100_rmu,direction::UP); //vasta cornerista
	//below the order is important - down
	cp100_rrm = addBoth(cp100_rrm,cp100_rrd,direction::DOWN);
	cp100_rlm = addBoth(cp100_rlm,cp100_rld,direction::DOWN);
	cp100_rmd = addBoth(cp100_rmd,cp100_rrd,direction::RIGHT);
	cp100_rmd = addBoth(cp100_rmd,cp100_rld,direction::LEFT);
	cp100_rmm = addBoth(cp100_rmm,cp100_rmd,direction::DOWN); //vasta cornerista

	/*
	 *  RIGHT  - with up facing back side
	 */
	upVec = ofVec3f(-1,0,0);
	CameraPosition* cp200_rmm = getOrCreateCM(cameraPositions, v[5], upVec);
	CameraPosition* cp200_rlm = addFriend(getOrCreateCM(cameraPositions, cp200_urm->getPosition(), upVec), cp200_urm); //TODO
	CameraPosition* cp200_rrm = addFriend(getOrCreateCM(cameraPositions, cp200_dlm->getPosition(), upVec), cp200_dlm); //TODO
	CameraPosition* cp200_rmu = addFriend(getOrCreateCM(cameraPositions, cp001_bmd->getPosition(), upVec), cp001_bmd); //TODO
	CameraPosition* cp200_rmd = addFriend(getOrCreateCM(cameraPositions, cp002_fmu->getPosition(), upVec), cp002_fmu); //TODO
	CameraPosition* cp200_rlu = getOrCreateCM(cameraPositions, cp200_uru->getPosition(), upVec);
	CameraPosition* cp200_rld = getOrCreateCM(cameraPositions, cp200_urd->getPosition(), upVec);
	CameraPosition* cp200_rru = getOrCreateCM(cameraPositions, cp200_dlu->getPosition(), upVec);
	CameraPosition* cp200_rrd = getOrCreateCM(cameraPositions, cp200_dld->getPosition(), upVec);
	cp200_rmm = addBoth(cp200_rmm,cp200_rlm,direction::LEFT);
	cp200_rmm = addBoth(cp200_rmm,cp200_rrm,direction::RIGHT);
	//below the order is important - up
	cp200_rrm = addBoth(cp200_rrm,cp200_rru,direction::UP);
	cp200_rlm = addBoth(cp200_rlm,cp200_rlu,direction::UP);
	cp200_rmu = addBoth(cp200_rmu,cp200_rru,direction::RIGHT);
	cp200_rmu = addBoth(cp200_rmu,cp200_rlu,direction::LEFT);
	cp200_rmm = addBoth(cp200_rmm,cp200_rmu,direction::UP); //vasta cornerista
	//below the order is important - down
	cp200_rrm = addBoth(cp200_rrm,cp200_rrd,direction::DOWN);
	cp200_rlm = addBoth(cp200_rlm,cp200_rld,direction::DOWN);
	cp200_rmd = addBoth(cp200_rmd,cp200_rrd,direction::RIGHT);
	cp200_rmd = addBoth(cp200_rmd,cp200_rld,direction::LEFT);
	cp200_rmm = addBoth(cp200_rmm,cp200_rmd,direction::DOWN); //vasta cornerista

	/*
	 *  RIGHT  - with up facing down side
	 */
	upVec = ofVec3f(0,-1,0);
	CameraPosition* cp020_rmm = getOrCreateCM(cameraPositions, v[5], upVec);
	CameraPosition* cp020_rlm = addFriend(getOrCreateCM(cameraPositions, cp020_brm->getPosition(), ofVec3f(0,-1,0.01)), cp020_brm); //TODO
	CameraPosition* cp020_rrm = addFriend(getOrCreateCM(cameraPositions, cp020_flm->getPosition(), ofVec3f(0,-1,0.01)), cp020_flm); //TODO
	CameraPosition* cp020_rmu = addFriend(getOrCreateCM(cameraPositions, cp001_dmd->getPosition(), upVec), cp001_dmd); //TODO
	CameraPosition* cp020_rmd = addFriend(getOrCreateCM(cameraPositions, cp002_umu->getPosition(), upVec), cp002_umu); //TODO
	CameraPosition* cp020_rlu = getOrCreateCM(cameraPositions, cp020_bru->getPosition(), upVec);
    CameraPosition* cp020_rld = getOrCreateCM(cameraPositions, cp020_brd->getPosition(), upVec);
	CameraPosition* cp020_rru = getOrCreateCM(cameraPositions, cp020_flu->getPosition(), upVec);
	CameraPosition* cp020_rrd = getOrCreateCM(cameraPositions, cp020_fld->getPosition(), upVec);
	cp020_rmm = addBoth(cp020_rmm,cp020_rlm,direction::LEFT);
	cp020_rmm = addBoth(cp020_rmm,cp020_rrm,direction::RIGHT);
	//below the order is important - up
	cp020_rrm = addBoth(cp020_rrm,cp020_rru,direction::UP);
	cp020_rlm = addBoth(cp020_rlm,cp020_rlu,direction::UP);
	cp020_rmu = addBoth(cp020_rmu,cp020_rru,direction::RIGHT);
	cp020_rmu = addBoth(cp020_rmu,cp020_rlu,direction::LEFT);
	cp020_rmm = addBoth(cp020_rmm,cp020_rmu,direction::UP); //vasta cornerista
	//below the order is important - down
	cp020_rrm = addBoth(cp020_rrm,cp020_rrd,direction::DOWN);
	cp020_rlm = addBoth(cp020_rlm,cp020_rld,direction::DOWN);
	cp020_rmd = addBoth(cp020_rmd,cp020_rrd,direction::RIGHT);
	cp020_rmd = addBoth(cp020_rmd,cp020_rld,direction::LEFT);
	cp020_rmm = addBoth(cp020_rmm,cp020_rmd,direction::DOWN); //vasta cornerista


	//Initialize null values that still exist
	for(unsigned int i=0;i<cameraPositions.size();i++){
	    CameraPosition* a = cameraPositions[i];
	    for(unsigned int j=0;j<cameraPositions.size();j++){
		CameraPosition* b = cameraPositions[j];
		if ( (*a)==(*b)){
		    if (a->getLeftNeighbour()==NULL && b->getLeftNeighbour()!=NULL){
			a->setLeftNeighbour(b->getLeftNeighbour());
		    }
		    if (a->getRightNeighbour()==NULL && b->getRightNeighbour()!=NULL){
			a->setRightNeighbour(b->getRightNeighbour());
		    }
		    if (a->getUpNeighbour()==NULL && b->getUpNeighbour()!=NULL){
			a->setUpNeighbour(b->getUpNeighbour());
		    }
		    if (a->getDownNeighbour()==NULL && b->getDownNeighbour()!=NULL){
			a->setDownNeighbour(b->getDownNeighbour());
		    }
		}
	    }
	}
	for(unsigned int i=0;i<cameraPositions.size();i++){
	    CameraPosition* a = cameraPositions[i];
	    if (a->getUpNeighbour()==NULL){
		CameraPosition* up = (a->getRightNeighbour())->getUpNeighbour();
		a->setUpNeighbour(up);
	    }
	    if (a->getDownNeighbour()==NULL){
		CameraPosition* up = (a->getRightNeighbour())->getDownNeighbour();
		a->setDownNeighbour(up);
	    }

	}


        int friendSum=0;
        for(unsigned int i=0;i<cameraPositions.size();i++){
            CameraPosition* a = cameraPositions[i];
            if (a->friendPosition==NULL){
                continue;
            }
            if (a->getLeftNeighbour()==NULL && a->friendPosition->getLeftNeighbour()){
                friendSum++;
                a->setLeftNeighbour(a->friendPosition->getLeftNeighbour());
            }
            if (a->getRightNeighbour()==NULL && a->friendPosition->getRightNeighbour()!=NULL){
                friendSum++;
                a->setRightNeighbour(a->friendPosition->getRightNeighbour());
            }
            if (a->getUpNeighbour()==NULL && a->friendPosition->getUpNeighbour()!=NULL){
                friendSum++;
                a->setUpNeighbour(a->friendPosition->getUpNeighbour());
            }
            if (a->getDownNeighbour()==NULL && a->friendPosition->getDownNeighbour()!=NULL){
                friendSum++;
                a->setDownNeighbour(a->friendPosition->getDownNeighbour());
            }

        }
        cout<<"friends added: "<<friendSum<<endl;


	for(unsigned int i=0;i<cameraPositions.size();i++){
	    CameraPosition* a = cameraPositions[i];
	    if (a->getUpNeighbour()==NULL){
		CameraPosition* up = (a->getRightNeighbour())->getUpNeighbour();
		a->setUpNeighbour(up);
	    }
	    if (a->getDownNeighbour()==NULL){
		CameraPosition* up = (a->getRightNeighbour())->getDownNeighbour();
		a->setDownNeighbour(up);
	    }

	}



	cout<<"Checking if duplicate CameraPositions exist..."<<endl;
	for(unsigned int i=0;i<cameraPositions.size();i++){
	    CameraPosition* a = cameraPositions[i];
            bool found=false;
	    for(unsigned int j=0;j<cameraPositions.size();j++){
		CameraPosition* b = cameraPositions[j];
		if ( (*a)==(*b)){
		    if (i!=j &&
			a->getLeftNeighbour() == b->getLeftNeighbour() &&
			a->getRightNeighbour()==b->getRightNeighbour() &&
			a->getUpNeighbour()==b->getUpNeighbour() &&
			a->getDownNeighbour()==b->getDownNeighbour() ){

		    }
		}

		if (
		    a->getLeftNeighbour() == NULL ||
		    a->getRightNeighbour()== NULL  ||
		    a->getUpNeighbour()== NULL ||
		    a->getDownNeighbour()== NULL
		    ){
                                            found=true;
		}
	    }
            if(found==true){
                cout<<" FOUND INSTANCE WITH A NULL AS NEIGHBOUR!!!!     "<<i<<endl;
            }
	}
	cout<<"Duplicate checking done"<<endl;

	cout<<"size: "<<cameraPositions.size()<<endl;

	this->startPosition= cp020_rmm;
	std::ostringstream msg;
	msg<<"PositionFactory: Created "<< cameraPositions.size()<<" CameraPosition objects!";
	Logger::log(msg.str(),Logger::DEBUG);
	return true;
    }
    return false;
}

CameraPosition* PositionFactory::getStartPosition(){
    return this->startPosition;

















}

const std::vector<ofVec3f>& PositionFactory::getPositionVectors(){ //this should probably be integrated later with
    // generation of CameraPosition objects
    if (this->positionVectors.size()==0){
	float angle45 = float(45*PI/180);
	float angle54 = float(54*PI/180);
	float length = settings.getCameraZOffset();

	ofVec3f xAxis = ofVec3f(1, 0, 0);
	ofVec3f yAxis = ofVec3f(0, 1, 0);
	ofVec3f zAxis = ofVec3f(0, 0, 1);
	                                                                                                          //      side          horiz         vertic
	positionVectors.push_back(ofVec3f(length, 0, 0));                                                         // 0: front(VP)        mid           mid
	positionVectors.push_back(ofVec3f(-length, 0, 0));                                                        // 1: back(lila)       mid           mid
	positionVectors.push_back(ofVec3f(0, length, 0));                                                         // 2: up(white)        mid           mid
	positionVectors.push_back(ofVec3f(0, -length, 0));                                                        // 3: down(brown)      mid           mid
	positionVectors.push_back(ofVec3f(0, 0, length));                                                         // 4: left(grey)       mid           mid
	positionVectors.push_back(ofVec3f(0, 0, -length));                                                        // 5: right(blue)      mid           mid
	positionVectors.push_back(ofVec3f(length, 0, 0).rotateRad(angle45, yAxis));                               // 6: front            right         mid
	positionVectors.push_back(ofVec3f(length, 0, 0).rotateRad(-angle45, yAxis));                              // 7: front           -left          mid
	positionVectors.push_back(ofVec3f(-length, 0, 0).rotateRad(angle45, yAxis));                              // 8: left            -left          mid
	positionVectors.push_back(ofVec3f(-length, 0, 0).rotateRad(-angle45, yAxis));                             // 9: right-           right         mid
	positionVectors.push_back(ofVec3f(0, length, 0).rotateRad(angle45, xAxis));                               // 10: left            mid           up
	positionVectors.push_back(ofVec3f(0, length, 0).rotateRad(-angle45, xAxis));                              // 11: right           mid           up
	positionVectors.push_back(ofVec3f(0, -length, 0).rotateRad(angle45, xAxis));                              // 12: right-          mid          down
	positionVectors.push_back(ofVec3f(0, -length, 0).rotateRad(-angle45, xAxis));                             // 13: left-           mid           down
	positionVectors.push_back(ofVec3f(0, length, 0).rotateRad(angle45, zAxis));                               // 14: back            mid           up
	positionVectors.push_back(ofVec3f(0, length, 0).rotateRad(-angle45, zAxis));                              // 15: front           mid           up
	positionVectors.push_back(ofVec3f(0, -length, 0).rotateRad(angle45, zAxis));                              // 16: front           mid           down
	positionVectors.push_back(ofVec3f(0, -length, 0).rotateRad(-angle45, zAxis));                             // 17: back            mid           down
	positionVectors.push_back(ofVec3f(0, 0, length).rotateRad(-angle54, yAxis).rotateRad(angle45, zAxis));    // 18: left-back-down   corner
	positionVectors.push_back(ofVec3f(0, 0, length).rotateRad(-angle54, yAxis).rotateRad(-angle45, zAxis));   // 19: left-back-up     corner
	positionVectors.push_back(ofVec3f(0, 0, length).rotateRad(angle54, yAxis).rotateRad(angle45, zAxis));     // 20: front-left-up    corner
	positionVectors.push_back(ofVec3f(0, 0, length).rotateRad(angle54, yAxis).rotateRad(-angle45, zAxis));    // 21: front-left-down  corner
	positionVectors.push_back(ofVec3f(0, 0, -length).rotateRad(-angle54, yAxis).rotateRad(angle45, zAxis));   // 22: front-right-up   corner
	positionVectors.push_back(ofVec3f(0, 0, -length).rotateRad(-angle54, yAxis).rotateRad(-angle45, zAxis));  // 23: front-right-down corner
	positionVectors.push_back(ofVec3f(0, 0, -length).rotateRad(angle54, yAxis).rotateRad(angle45, zAxis));    // 24: right-right-down corner
	positionVectors.push_back(ofVec3f(0, 0, -length).rotateRad(angle54, yAxis).rotateRad(-angle45, zAxis));   // 25: right-right-up   corner
    }
    return positionVectors;
}

const std::vector<CameraPosition*>& PositionFactory::getCameraPositions() const{
    return this->cameraPositions;
}

Settings& PositionFactory::getSettings(){
    return settings;
}
