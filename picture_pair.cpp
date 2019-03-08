#include "picture.h"
#include "picture_pair.h"




Picture_Pair::Picture_Pair(const Picture_Pair& pp){

	this->pp[0]=pp.pp[0];

	this->pp[1]=pp.pp[1];

}

Picture_Pair::Picture_Pair(Picture* p1, Picture* p2) {


	if(p1 ==nullptr)

		pp[0]=nullptr;

	if(p2 ==nullptr)

			pp[1]=nullptr;



	pp[0] = p1;
	pp[1]= p2;

}

Picture* Picture_Pair::get_picture(int n) const{
	if(n==1 || n==0)
	return pp[n];

	return nullptr;


}

Picture_Pair::~Picture_Pair(){
}


void Picture_Pair::draw() const
{

	if(pp[0]!= nullptr)
	pp[0]->draw();

	if(pp[1]!= nullptr)
	pp[1]->draw();


}
