#include <set>
#include <gmsh.h>

void points(double lc){
    gmsh::model::geo::addPoint(-1, -1, -1, lc, 1);
    gmsh::model::geo::addPoint(-1, -1, 1, lc, 2);
    gmsh::model::geo::addPoint(1, -1, 1, lc, 3);
    gmsh::model::geo::addPoint(1, -1, -1, lc, 4);

    gmsh::model::geo::addPoint(-1, 1, -1, lc, 5);
    gmsh::model::geo::addPoint(-1, 1, 1, lc, 6);
    gmsh::model::geo::addPoint(1, 1, 1, lc, 7);
    gmsh::model::geo::addPoint(1, 1, -1, lc, 8);
}

void lines(){
    for(int i = 0; i < 3; i++)
        gmsh::model::geo::addLine(i + 1, i + 2, i + 1);
    gmsh::model::geo::addLine(4, 1, 4);

    for(int i = 0; i < 3; i++)
        gmsh::model::geo::addLine(i + 5, i + 6, i + 5);
    gmsh::model::geo::addLine(8, 5, 8);

    for(int i = 0; i < 4; i++)
        gmsh::model::geo::addLine(i + 1, i + 5, i + 9);
}

void curve_loops(){
    gmsh::model::geo::addCurveLoop({1, 2, 3, 4}, 1);
    gmsh::model::geo::addPlaneSurface({1}, 1);

    gmsh::model::geo::addCurveLoop({5, 6, 7, 8}, 2);
    gmsh::model::geo::addPlaneSurface({2}, 2);

    gmsh::model::geo::addCurveLoop({1, 10, -5, -9}, 3);
    gmsh::model::geo::addPlaneSurface({3},3);

    gmsh::model::geo::addCurveLoop({10, 6, -11, -2}, 4);
    gmsh::model::geo::addPlaneSurface({4},4);

    gmsh::model::geo::addCurveLoop({11, 7, -12, -3}, 5);
    gmsh::model::geo::addPlaneSurface({5},5);

    gmsh::model::geo::addCurveLoop({-12, 4, 9, -8}, 6);
    gmsh::model::geo::addPlaneSurface({6},6);

    gmsh::model::geo::addSurfaceLoop({1, 2, 3, 4, 5, 6}, 1);
    gmsh::model::geo::addVolume({1});
}

int main(int argc, char **argv)
{
    gmsh::initialize();

    gmsh::model::add("t2");

    double lc = 0.1;

    points(lc);

    lines();

    curve_loops();

    gmsh::model::geo::synchronize();

    gmsh::model::mesh::generate(3);

    std::set<std::string> args(argv, argv + argc);
    if(!args.count("-nopopup")) gmsh::fltk::run();

    gmsh::finalize();

    return 0;
}


