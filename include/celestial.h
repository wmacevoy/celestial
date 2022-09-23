#pragma once

#include <tgmath.h>
#include <array>

namespace celestial
{

  template <typename Number>
  struct Position : std::array<Number, 4>
  {
    const Number &x() const { return std::get<0>(*this); }
    const Number &y() const { return std::get<1>(*this); }
    const Number &z() const { return std::get<2>(*this); }
    const Number &w() const { return std::get<3>(*this); }
    Position(const std::array<Number, 4> &dup) : std::array<Number, 4>(dup) {}
    Position(const Number &_x, const Number &_y, const Number &_z = Number(0), const Number &_w = Number(1))
        : std::array<Number, 4>{_x, _y, _z, _w} {};
  };

  template <typename Number>
  struct Vector : std::array<Number, 3>
  {
    Number x() const { return std::get<0>(*this); }
    Number y() const { return std::get<1>(*this); }
    Number z() const { return std::get<2>(*this); }
    Vector(Number _x, Number _y, Number _z = 0)
        : std::array<double, 3>{_x, _y, _z} {};
  };

  template <typename Number>
  struct CoordinateSystem : std::array<std::array<Number, 4>, 4>
  {
    CoordinateSystem()
    {
      for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
          (*this)[i][j] = Number(i == j);
    }

    CoordinateSystem &operator*=(const std::array<std::array<Number, 4>, 4> &mat)
    {
      CoordinateSystem tmp;
      for (int i = 0; i < 4; ++i)
      {
        for (int j = 0; j < 4; ++j)
        {
          tmp[i][j] = 0;
          for (int k = 0; k < 4; ++k)
          {
            tmp[i][j] += (*this)[i][k] * mat[k][j];
          }
        }
      }
      *this = tmp;
      return *this;
    }

    const Number& mat(int i) const { return (*this)[(i) / 4][(i) % 4]; }
    Number& mat(int i) { return (*this)[(i) / 4][(i) % 4]; }

    //    https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
    bool invert()
    {
      std::array<std::array<Number, 4>, 4> inv;

      inv[0][0] = mat(5) * mat(10) * mat(15) -
                  mat(5) * mat(11) * mat(14) -
                  mat(9) * mat(6) * mat(15) +
                  mat(9) * mat(7) * mat(14) +
                  mat(13) * mat(6) * mat(11) -
                  mat(13) * mat(7) * mat(10);

      inv[1][0] = -mat(4) * mat(10) * mat(15) +
                  mat(4) * mat(11) * mat(14) +
                  mat(8) * mat(6) * mat(15) -
                  mat(8) * mat(7) * mat(14) -
                  mat(12) * mat(6) * mat(11) +
                  mat(12) * mat(7) * mat(10);

      inv[2][0] = mat(4) * mat(9) * mat(15) -
                  mat(4) * mat(11) * mat(13) -
                  mat(8) * mat(5) * mat(15) +
                  mat(8) * mat(7) * mat(13) +
                  mat(12) * mat(5) * mat(11) -
                  mat(12) * mat(7) * mat(9);

      inv[3][0] = -mat(4) * mat(9) * mat(14) +
                  mat(4) * mat(10) * mat(13) +
                  mat(8) * mat(5) * mat(14) -
                  mat(8) * mat(6) * mat(13) -
                  mat(12) * mat(5) * mat(10) +
                  mat(12) * mat(6) * mat(9);

      inv[0][1] = -mat(1) * mat(10) * mat(15) +
                  mat(1) * mat(11) * mat(14) +
                  mat(9) * mat(2) * mat(15) -
                  mat(9) * mat(3) * mat(14) -
                  mat(13) * mat(2) * mat(11) +
                  mat(13) * mat(3) * mat(10);

      inv[1][1] = mat(0) * mat(10) * mat(15) -
                  mat(0) * mat(11) * mat(14) -
                  mat(8) * mat(2) * mat(15) +
                  mat(8) * mat(3) * mat(14) +
                  mat(12) * mat(2) * mat(11) -
                  mat(12) * mat(3) * mat(10);

      inv[2][1] = -mat(0) * mat(9) * mat(15) +
                  mat(0) * mat(11) * mat(13) +
                  mat(8) * mat(1) * mat(15) -
                  mat(8) * mat(3) * mat(13) -
                  mat(12) * mat(1) * mat(11) +
                  mat(12) * mat(3) * mat(9);

      inv[3][1] = mat(0) * mat(9) * mat(14) -
                  mat(0) * mat(10) * mat(13) -
                  mat(8) * mat(1) * mat(14) +
                  mat(8) * mat(2) * mat(13) +
                  mat(12) * mat(1) * mat(10) -
                  mat(12) * mat(2) * mat(9);

      inv[0][2] = mat(1) * mat(6) * mat(15) -
                  mat(1) * mat(7) * mat(14) -
                  mat(5) * mat(2) * mat(15) +
                  mat(5) * mat(3) * mat(14) +
                  mat(13) * mat(2) * mat(7) -
                  mat(13) * mat(3) * mat(6);

      inv[1][2] = -mat(0) * mat(6) * mat(15) +
                  mat(0) * mat(7) * mat(14) +
                  mat(4) * mat(2) * mat(15) -
                  mat(4) * mat(3) * mat(14) -
                  mat(12) * mat(2) * mat(7) +
                  mat(12) * mat(3) * mat(6);

      inv[2][2] = mat(0) * mat(5) * mat(15) -
                  mat(0) * mat(7) * mat(13) -
                  mat(4) * mat(1) * mat(15) +
                  mat(4) * mat(3) * mat(13) +
                  mat(12) * mat(1) * mat(7) -
                  mat(12) * mat(3) * mat(5);

      inv[3][2] = -mat(0) * mat(5) * mat(14) +
                  mat(0) * mat(6) * mat(13) +
                  mat(4) * mat(1) * mat(14) -
                  mat(4) * mat(2) * mat(13) -
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

      Number det = mat(0) * inv[0][0] + mat(1) * inv[1][0] + mat(2) * inv[2][0] + mat(3) * inv[3][0];

      if (det == Number(0))
        return false;

      det = Number(1) / det;

      for (int i = 0; i < 4; ++i)
      {
        for (int j = 0; j < 4; ++j)
        {
          (*this)[i][j] = det * inv[i][j];
        }
      }

      return true;
    }
    void scale(const Number &sx, const Number &sy, const Number &sz)
    {
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

    void scale(const Number &s) { scale(s, s, s); }

    void translate(const Number &tx, const Number &ty, const Number &tz)
    {
      (*this)[3][0] += tx;
      (*this)[3][1] += ty;
      (*this)[3][2] += tz;
    }

    void rotate(const Vector<Number> &axis, const Number &degrees)
    {
      const Number toRadians = Number(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089L)/Number(180.0L);

      Number radians = toRadians*fmod(degrees,Number(360));


      Number c = cos(radians);
      Number s = sin(radians);
      Number t = 1 - c;
      Number x = axis[0];
      Number y = axis[1];
      Number z = axis[2];
      Number w = Number(1) / sqrt(x * x + y * y + z * z);

      x *= w;
      y *= w;
      z *= w;

      std::array<std::array<Number, 4>, 4> rot;

      rot[0][0] = t * x * x + c;
      rot[0][1] = t * x * y - s * z;
      rot[0][2] = t * x * z + s * y;
      rot[0][3] = 0;

      rot[1][0] = t * x * y + s * z;
      rot[1][1] = t * y * y + c;
      rot[1][2] = t * y * z - s * x;
      rot[1][3] = 0;

      rot[2][0] = t * x * z - s * y;
      rot[2][1] = t * y * z + s * x;
      rot[2][2] = t * z * z + c;
      rot[2][3] = 0;

      rot[3][0] = 0;
      rot[3][1] = 0;
      rot[3][2] = 0;
      rot[3][3] = 1;

      *this *= rot;
    }
  };

  template <typename Number>
  CoordinateSystem Sphere() {

  }
  template <typename Number>
  struct Ellpsiod
  {
    Vector<Number> radii;

    Ellpsiod(const Vector<Number> &_radii) : radii(_radii) {}


    CoordinateSystem<Number> getCoordinateSystem(const Number &latitude, const Number &longitude, const Number &elevation) 
    {
        const Number toRadians = Number(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089L)/Number(180.0L);
        Number radlat = toRadians*fmod(latitude,Number(360));
        Number radlon = toRadians*fmod(longitude,Number(360));

        Number coslat = cos(radlat);
        Number sinlat = sin(radlat);
        Number coslon = cos(radlon);
        Number sinlon = sin(radlon);

        Vector<Number> xaxis = {coslat*coslon,coslat*sinlon,-sinlat};
        Vector<Number> yaxis = {-sinlon,coslon,0};
        Vector<Number> zaxis = {sinlat*coslon,sinlat*sinlon,coslat};
        Position<Number> pos = {radii[0]*coslat*coslon,radii[1]*coslat*sinlon,radii[2]*sinlat};

      Number x = 
      CoordinateSystem<Number> cs;
      cs.origin = center;
      cs.xAxis = Vector<Number>(radii[0], 0, 0);
      cs.yAxis = Vector<Number>(0, radii[1], 0);
      cs.zAxis = Vector<Number>(0, 0, radii[2]);
      return cs;
    }
  };

  template <typename Number>
  struct Object
  {
    virtual CoordinateSystem<Number> coordinates(const Number &time) const = 0;
    std::set<std::shared_ptr<Object>> children;
  };

}
