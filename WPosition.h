#ifndef WPosition_H
#define WPosition_H


class WPosition{
public:
	WPosition():x(0),y(0),DroneCount(1){	}

	~WPosition(){delete this;}

	WPosition(const WPosition &pos){
		this->x=pos.x;
		this->y=pos.y;
		this->DroneCount=pos.DroneCount;
	}

	void setX(double xval){x=xval;}

	void setY(double yval){y=yval;}

	void setDC(int cnt){DroneCount=cnt;}

	double getX() const{return x;}

	double getY() const{return y;}

	int getDC() const{return DroneCount;}


	WPosition& operator ++(){
		DroneCount++;
		return *this;}

	WPosition operator ++(int){
		WPosition temp = *this;
		++*this;
		return temp;}

	WPosition& operator --(){
		DroneCount--;
		return *this;}

	WPosition operator --(int){
		WPosition temp = *this;
		--*this;
		return temp;}




private:
	double x;
	double y;
	int DroneCount;


};


#endif /* WPosition_H */
