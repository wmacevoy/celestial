#pragma once

namespace celestial {

  template <typename Number>
  struct Position : std::array<Number,4> {
    const Number &x() const { return std::get<0>(*this); }
    const Number &y() const { return std::get<1>(*this); }
    const Number &z() const { return std::get<2>(*this); }
    const Number &w() const { return std::get<3>(*this); }
    Position(const std::array<Number,4> &dup) std::array<Number,4>(dup) {}
    Position(const Number & _x,const Number &_y, const Number &_z=0, const Number & 1)
      : std::array<Number,4>{_x,_y,_z,_w} {};
  };

  struct Vector : std::array<Number,3> {
    Number x() const { return std::get<0>(*this); }
    Number y() const { return std::get<1>(*this); }
    Number z() const { return std::get<2>(*this); }
    Vector(Number _x,Number _y, Number _z = 0)
      : std::array<double,3>{_x,_y,_z} {};
  };
  
  typedef Real  Time;

  struct CoordinateSystem : std::array < std::array < Real , 4 >, 4> {
  CoordinateSystem() : std::array < std::array < Real , 4 >, 4> { { 1, 0, 0, 0, 1}, { 0, 1, 0, 0 }, { 0, 0, 1, 0}, { 0, 0, 0, 1} } {}

    //    https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
#define mat(i) ((*this)[(i)/4][(i)%4])
    bool invert() {
      std::array < std::array < Real , 4 > , 4 > inv;

      inv[0][0] = mat(5)  * mat(10) * mat(15) - 
	mat(5)  * mat(11) * mat(14) - 
	mat(9)  * mat(6)  * mat(15) + 
	mat(9)  * mat(7)  * mat(14) +
	mat(13) * mat(6)  * mat(11) - 
	mat(13) * mat(7)  * mat(10);
      
      inv[1][0] = -mat(4)  * mat(10) * mat(15) + 
	mat(4)  * mat(11) * mat(14) + 
	mat(8)  * mat(6)  * mat(15) - 
	mat(8)  * mat(7)  * mat(14) - 
	mat(12) * mat(6)  * mat(11) + 
	mat(12) * mat(7)  * mat(10);
      
      inv[2][0] = mat(4)  * mat(9) * mat(15) - 
	mat(4)  * mat(11) * mat(13) - 
	mat(8)  * mat(5) * mat(15) + 
	mat(8)  * mat(7) * mat(13) + 
	mat(12) * mat(5) * mat(11) - 
	mat(12) * mat(7) * mat(9);
      
      inv[3][0] = -mat(4)  * mat(9) * mat(14) + 
	mat(4)  * mat(10) * mat(13) +
	mat(8)  * mat(5) * mat(14) - 
	mat(8)  * mat(6) * mat(13) - 
	mat(12) * mat(5) * mat(10) + 
	mat(12) * mat(6) * mat(9);
      
      inv[0][1] = -mat(1)  * mat(10) * mat(15) + 
	mat(1)  * mat(11) * mat(14) + 
	mat(9)  * mat(2) * mat(15) - 
	mat(9)  * mat(3) * mat(14) - 
	mat(13) * mat(2) * mat(11) + 
	mat(13) * mat(3) * mat(10);
      
      inv[1][1] = mat(0)  * mat(10) * mat(15) - 
	mat(0)  * mat(11) * mat(14) - 
	mat(8)  * mat(2) * mat(15) + 
	mat(8)  * mat(3) * mat(14) + 
	mat(12) * mat(2) * mat(11) - 
	mat(12) * mat(3) * mat(10);
      
      inv[2][1] = -mat(0)  * mat(9) * mat(15) + 
	mat(0)  * mat(11) * mat(13) + 
	mat(8)  * mat(1) * mat(15) - 
	mat(8)  * mat(3) * mat(13) - 
	mat(12) * mat(1) * mat(11) + 
	mat(12) * mat(3) * mat(9);

    inv[3][1] = mat(0)  * mat(9) * mat(14) - 
      mat(0)  * mat(10) * mat(13) - 
      mat(8)  * mat(1) * mat(14) + 
      mat(8)  * mat(2) * mat(13) + 
      mat(12) * mat(1) * mat(10) - 
      mat(12) * mat(2) * mat(9);

    inv[0][2] = mat(1)  * mat(6) * mat(15) - 
      mat(1)  * mat(7) * mat(14) - 
      mat(5)  * mat(2) * mat(15) + 
      mat(5)  * mat(3) * mat(14) + 
      mat(13) * mat(2) * mat(7) - 
      mat(13) * mat(3) * mat(6);
    
    inv[1][2] = -mat(0)  * mat(6) * mat(15) + 
      mat(0)  * mat(7) * mat(14) + 
      mat(4)  * mat(2) * mat(15) - 
      mat(4)  * mat(3) * mat(14) - 
      mat(12) * mat(2) * mat(7) + 
      mat(12) * mat(3) * mat(6);

    inv[2][2] = mat(0)  * mat(5) * mat(15) - 
      mat(0)  * mat(7) * mat(13) - 
      mat(4)  * mat(1) * mat(15) + 
      mat(4)  * mat(3) * mat(13) + 
      mat(12) * mat(1) * mat(7) - 
      mat(12) * mat(3) * mat(5);
    
    inv[3][2] = -mat(0)  * mat(5) * mat(14) + 
      mat(0)  * mat(6) * mat(13) + 
      mat(4)  * mat(1) * mat(14) - 
      mat(4)  * mat(2) * mat(13) - 
      mat(12) * mat(1) * mat(6) + 
      mat(12) * mat(2) * mat(5);
    
    inv[0][3] = -mat(1) * mat(6) * mat(11) + 
      mat(1) * mat(7) * mat(10) + 
      mat(5) * mat(2) * mat(11) - 
      mat(5) * mat(3) * mat(10) - 
      mat(9) * mat(2) * mat(7) + 
      mat(9) * mat(3) * mat(6);

    inv[1][3] = mat(0) * mat(6) * mat(11) - 
      mat(0) * mat(7) * mat(10) - 
      mat(4) * mat(2) * mat(11) + 
      mat(4) * mat(3) * mat(10) + 
      mat(8) * mat(2) * mat(7) - 
      mat(8) * mat(3) * mat(6);

    inv[2][3] = -mat(0) * mat(5) * mat(11) + 
      mat(0) * mat(7) * mat(9) + 
      mat(4) * mat(1) * mat(11) - 
      mat(4) * mat(3) * mat(9) - 
      mat(8) * mat(1) * mat(7) + 
      mat(8) * mat(3) * mat(5);
    
    inv[3][3] = mat(0) * mat(5) * mat(10) - 
      mat(0) * mat(6) * mat(9) - 
      mat(4) * mat(1) * mat(10) + 
      mat(4) * mat(2) * mat(9) + 
      mat(8) * mat(1) * mat(6) - 
      mat(8) * mat(2) * mat(5);
    
    Real det = mat(0) * inv[0][0] + mat(1) * inv[1][0] + mat(2) * inv[2][0] + mat(3) * inv[3][0];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        (this)[i][j] = det*inv[i][j];
      }
    }

    return true;
}
    void scale(Real sx,double long sy,double long sz) {
      (*this)[0][0] *= sx;
      (*this)[0][1] *= sx;
      (*this)[0][2] *= sx;      

      (*this)[1][0] *= sy;
      (*this)[1][1] *= sy;
      (*this)[1][2] *= sy;      

      (*this)[2][0] *= sz;
      (*this)[2][1] *= sz;
      (*this)[2][2] *= sz;
    }
    
    void scale(Real s) { scale(s,s,s); }
    
    void translate(double tx,double ty, double tz) {
      (*this)[3][0] += tx;
      (*this)[3][1] += ty;
      (*this)[3][2] += tz;      

    }
    
  };

  

  struct Transform : std::array<double,

  typedef std::array< std::array<double,5> , 5 > Transform;

  struct Object {
    virtual Position global(const Position &locals
    virtual void coordinates(Object &reference, Time time);
    std::set < std::shared_ptr < Object > > children;
    
  }
  
  struct Sphere {
    double radius;
    double rotation,phase;
    std::array<double,3> origin;
    std::array<double,3> north;
    std::array<double,3>

  };
  

}
