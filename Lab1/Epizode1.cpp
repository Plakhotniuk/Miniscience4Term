#include <set>
#include <gmsh.h>
#include <iostream>
using namespace std;

void Points(double lc, double z, int index, double r){
    gmsh::model::geo::addPoint(0, 0, z, lc, index);

    gmsh::model::geo::addPoint(r, 0, z, lc, index + 1);

    gmsh::model::geo::addPoint(0, r, z, lc, index + 2);

    gmsh::model::geo::addPoint(-r, 0, z, lc, index + 3);

    gmsh::model::geo::addPoint(0, -r, z, lc, index + 4);
}

void CircleArcs(int index){
    gmsh::model::geo::addCircleArc(index + 1, index, index + 2, index);

    gmsh::model::geo::addCircleArc(index + 2, index, index + 3, index + 1);

    gmsh::model::geo::addCircleArc(index + 3, index, index + 4, index + 2);

    gmsh::model::geo::addCircleArc(index + 4, index, index + 1, index + 3);

    gmsh::model::geo::addCurveLoop({index, index+1, index+2, index+3}, index);

    gmsh::model::geo::addSurfaceLoop({index}, index);


};

int main(int argc, char **argv)
{
    gmsh::initialize();

    gmsh::model::add("t2");

    double lc = 0.1;

    Points(lc, 0, 1, 2);
    CircleArcs(1);

    Points(lc, 0, 6, 1);
    CircleArcs(6);

    gmsh::model::geo::addPlaneSurface({1, 6},1);

//    std::vector<std::pair<int, int> > ov2;

    std::vector<std::pair<int, int> > ov1;
//    gmsh::model::geo::copy({{2, 1}}, ov1);
    gmsh::model::geo::revolve({{2, 1}}, 3., 0., 0., 0, 1, 0, -M_PI/2, ov1,
                              {5}, {1});
    std::vector<std::pair<int, int> > ov2;
    gmsh::model::geo::revolve({{2, 1}}, 3., 0., 0., 0, 1, 0, M_PI/2, ov2,
                              {5}, {1});
//    gmsh::model::mesh::optimize("HighOrder", true);
    std::vector<std::pair<int, int> > ov3;
    gmsh::model::geo::copy({ov1}, ov3);
    gmsh::model::geo::mirror({ov3}, -6., 0., 0., 18.);
    std::vector<std::pair<int, int> > ov4;
    gmsh::model::geo::copy({ov2}, ov4);
    gmsh::model::geo::mirror({ov4}, -6., 0., 0., 18.);

//    gmsh::model::mesh::recombine();


    gmsh::model::geo::synchronize();

    gmsh::model::mesh::generate(3);

    gmsh::write("t3.msh");
    std::set<std::string> args(argv, argv + argc);
    if(!args.count("-nopopup")) gmsh::fltk::run();

    gmsh::finalize();


    return 0;
}




