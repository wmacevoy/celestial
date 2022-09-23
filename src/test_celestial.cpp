#include <gtest/gtest.h>

#include <celestial.h>

TEST(Celestial, Position)
{
    celestial::Position<double> p(1, 2, 3, 4);
    EXPECT_EQ(p.x(), 1);
    EXPECT_EQ(p.y(), 2);
    EXPECT_EQ(p.z(), 3);
    EXPECT_EQ(p.w(), 4);
}

TEST(Celestial, Vector)
{
    celestial::Vector<double> v(1, 2, 3);
    EXPECT_EQ(v.x(), 1);
    EXPECT_EQ(v.y(), 2);
    EXPECT_EQ(v.z(), 3);
}

TEST(Celestial, CoordinateSystem)
{
    celestial::CoordinateSystem<double> cs;
    EXPECT_EQ(cs[0][0], 1);
    EXPECT_EQ(cs[0][1], 0);
    EXPECT_EQ(cs[0][2], 0);
    EXPECT_EQ(cs[0][3], 0);
    EXPECT_EQ(cs[1][0], 0);
    EXPECT_EQ(cs[1][1], 1);
    EXPECT_EQ(cs[1][2], 0);
    EXPECT_EQ(cs[1][3], 0);
    EXPECT_EQ(cs[2][0], 0);
    EXPECT_EQ(cs[2][1], 0);
    EXPECT_EQ(cs[2][2], 1);
    EXPECT_EQ(cs[2][3], 0);
    EXPECT_EQ(cs[3][0], 0);
    EXPECT_EQ(cs[3][1], 0);
    EXPECT_EQ(cs[3][2], 0);
    EXPECT_EQ(cs[3][3], 1);
}

TEST(Celestial, CoodinateSystemMultiply)
{
    celestial::CoordinateSystem<double> cs;
    cs[0][0] = 1;
    cs[0][1] = 2;
    cs[0][2] = 3;
    cs[0][3] = 4;
    cs[1][0] = 5;
    cs[1][1] = 6;
    cs[1][2] = 7;
    cs[1][3] = 8;
    cs[2][0] = 9;
    cs[2][1] = 10;
    cs[2][2] = 11;
    cs[2][3] = 12;
    cs[3][0] = 13;
    cs[3][1] = 14;
    cs[3][2] = 15;
    cs[3][3] = 16;
    cs *= cs;
    EXPECT_EQ(cs[0][0], 90);
    EXPECT_EQ(cs[0][1], 100);
    EXPECT_EQ(cs[0][2], 110);
    EXPECT_EQ(cs[0][3], 120);
    EXPECT_EQ(cs[1][0], 202);
    EXPECT_EQ(cs[1][1], 228);
    EXPECT_EQ(cs[1][2], 254);
    EXPECT_EQ(cs[1][3], 280);
    EXPECT_EQ(cs[2][0], 314);
    EXPECT_EQ(cs[2][1], 356);
    EXPECT_EQ(cs[2][2], 398);
    EXPECT_EQ(cs[2][3], 440);
    EXPECT_EQ(cs[3][0], 426);
    EXPECT_EQ(cs[3][1], 484);
    EXPECT_EQ(cs[3][2], 542);
    EXPECT_EQ(cs[3][3], 600);
}

TEST(Celestial, CoordinateSystemInverse)
{
    celestial::CoordinateSystem<double> cs;
    cs[0][0] = 1;
    cs[0][1] = 2;
    cs[0][2] = 3;
    cs[0][3] = 1;
    cs[1][0] = 4;
    cs[1][1] = 3;
    cs[1][2] = 2;
    cs[1][3] = 1;
    cs[2][0] = 2;
    cs[2][1] = 1;
    cs[2][2] = 4;
    cs[2][3] = 3;
    cs[3][0] = 1;
    cs[3][1] = 3;
    cs[3][2] = 2;
    cs[3][3] = 4;

    auto cs0 = cs;
    bool invertable = cs.invert();
    EXPECT_EQ(invertable, true);
    double eps = 1e-12;
    EXPECT_NEAR(cs[0][0], -1.0 / 3.0, eps);
    EXPECT_NEAR(cs[0][1], 5.0 / 18.0, eps);
    EXPECT_NEAR(cs[0][2], 1.0 / 6.0, eps);
    EXPECT_NEAR(cs[0][3], -1.0 / 9.0, eps);
    EXPECT_NEAR(cs[1][0], 1.0 / 3.0, eps);
    EXPECT_NEAR(cs[1][1], 1.0 / 18.0, eps);
    EXPECT_NEAR(cs[1][2], -11.0 / 30.0, eps);
    EXPECT_NEAR(cs[1][3], 8.0 / 45.0, eps);
    EXPECT_NEAR(cs[2][0], 1.0 / 3.0, eps);
    EXPECT_NEAR(cs[2][1], -1.0 / 9.0, eps);
    EXPECT_NEAR(cs[2][2], 2.0 / 15.0, eps);
    EXPECT_NEAR(cs[2][3], -7.0 / 45.0, eps);
    EXPECT_NEAR(cs[3][0], -1.0 / 3.0, eps);
    EXPECT_NEAR(cs[3][1], -1.0 / 18.0, eps);
    EXPECT_NEAR(cs[3][2], 1.0 / 6.0, eps);
    EXPECT_NEAR(cs[3][3], 2.0 / 9.0, eps);

    cs0 *= cs;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (i == j)
            {
                EXPECT_NEAR(cs0[i][j], 1, eps);
            }
            else
            {
                EXPECT_NEAR(cs0[i][j], 0, eps);
            }
        }
    }
}

TEST(Celestial, CoordinateSystemTranslate)
{
    celestial::CoordinateSystem<double> cs;
    cs.translate(1, 2, 3);
    EXPECT_EQ(cs[0][0], 1);
    EXPECT_EQ(cs[0][1], 0);
    EXPECT_EQ(cs[0][2], 0);
    EXPECT_EQ(cs[0][3], 0);
    EXPECT_EQ(cs[1][0], 0);
    EXPECT_EQ(cs[1][1], 1);
    EXPECT_EQ(cs[1][2], 0);
    EXPECT_EQ(cs[1][3], 0);
    EXPECT_EQ(cs[2][0], 0);
    EXPECT_EQ(cs[2][1], 0);
    EXPECT_EQ(cs[2][2], 1);
    EXPECT_EQ(cs[2][3], 0);
    EXPECT_EQ(cs[3][0], 1);
    EXPECT_EQ(cs[3][1], 2);
    EXPECT_EQ(cs[3][2], 3);
    EXPECT_EQ(cs[3][3], 1);
}

TEST(Celestial, CoordinateSystemScale)
{
    celestial::CoordinateSystem<double> cs;
    cs.scale(1, 2, 3);
    EXPECT_EQ(cs[0][0], 1);
    EXPECT_EQ(cs[0][1], 0);
    EXPECT_EQ(cs[0][2], 0);
    EXPECT_EQ(cs[0][3], 0);
    EXPECT_EQ(cs[1][0], 0);
    EXPECT_EQ(cs[1][1], 2);
    EXPECT_EQ(cs[1][2], 0);
    EXPECT_EQ(cs[1][3], 0);
    EXPECT_EQ(cs[2][0], 0);
    EXPECT_EQ(cs[2][1], 0);
    EXPECT_EQ(cs[2][2], 3);
    EXPECT_EQ(cs[2][3], 0);
    EXPECT_EQ(cs[3][0], 0);
    EXPECT_EQ(cs[3][1], 0);
    EXPECT_EQ(cs[3][2], 0);
    EXPECT_EQ(cs[3][3], 1);
}

TEST(Celestial, CoordinateSystemRotateX)
{
    celestial::CoordinateSystem<double> cs;
    cs.rotate(celestial::Vector<double>(1, 0, 0), 90.0);

    double eps = 1e-12;
    EXPECT_NEAR(cs[0][0], 1, eps);
    EXPECT_NEAR(cs[0][1], 0, eps);
    EXPECT_NEAR(cs[0][2], 0, eps);
    EXPECT_NEAR(cs[0][3], 0, eps);
    EXPECT_NEAR(cs[1][0], 0, eps);
    EXPECT_NEAR(cs[1][1], 0, eps);
    EXPECT_NEAR(cs[1][2], -1, eps);
    EXPECT_NEAR(cs[1][3], 0, eps);
    EXPECT_NEAR(cs[2][0], 0, eps);
    EXPECT_NEAR(cs[2][1], 1, eps);
    EXPECT_NEAR(cs[2][2], 0, eps);
    EXPECT_NEAR(cs[2][3], 0, eps);
    EXPECT_NEAR(cs[3][0], 0, eps);
    EXPECT_NEAR(cs[3][1], 0, eps);
    EXPECT_NEAR(cs[3][2], 0, eps);
    EXPECT_NEAR(cs[3][3], 1, eps);
}

TEST(Celestial, CoordinateSystemRotateY)
{
    celestial::CoordinateSystem<double> cs;
    cs.rotate(celestial::Vector<double>(0, 1, 0), 90.0);

    double eps = 1e-12;
    EXPECT_NEAR(cs[0][0], 0, eps);
    EXPECT_NEAR(cs[0][1], 0, eps);
    EXPECT_NEAR(cs[0][2], 1, eps);
    EXPECT_NEAR(cs[0][3], 0, eps);
    EXPECT_NEAR(cs[1][0], 0, eps);
    EXPECT_NEAR(cs[1][1], 1, eps);
    EXPECT_NEAR(cs[1][2], 0, eps);
    EXPECT_NEAR(cs[1][3], 0, eps);
    EXPECT_NEAR(cs[2][0], -1, eps);
    EXPECT_NEAR(cs[2][1], 0, eps);
    EXPECT_NEAR(cs[2][2], 0, eps);
    EXPECT_NEAR(cs[2][3], 0, eps);
    EXPECT_NEAR(cs[3][0], 0, eps);
    EXPECT_NEAR(cs[3][1], 0, eps);
    EXPECT_NEAR(cs[3][2], 0, eps);
    EXPECT_NEAR(cs[3][3], 1, eps);
}

TEST(Celestial, CoordinateSystemRotateZ)
{
    celestial::CoordinateSystem<double> cs;
    cs.rotate(celestial::Vector<double>(0, 0, 1), 90.0);

    double eps = 1e-12;
    EXPECT_NEAR(cs[0][0], 0, eps);
    EXPECT_NEAR(cs[0][1], -1, eps);
    EXPECT_NEAR(cs[0][2], 0, eps);
    EXPECT_NEAR(cs[0][3], 0, eps);
    EXPECT_NEAR(cs[1][0], 1, eps);
    EXPECT_NEAR(cs[1][1], 0, eps);
    EXPECT_NEAR(cs[1][2], 0, eps);
    EXPECT_NEAR(cs[1][3], 0, eps);
    EXPECT_NEAR(cs[2][0], 0, eps);
    EXPECT_NEAR(cs[2][1], 0, eps);
    EXPECT_NEAR(cs[2][2], 1, eps);
    EXPECT_NEAR(cs[2][3], 0, eps);
    EXPECT_NEAR(cs[3][0], 0, eps);
    EXPECT_NEAR(cs[3][1], 0, eps);
    EXPECT_NEAR(cs[3][2], 0, eps);
    EXPECT_NEAR(cs[3][3], 1, eps);
}